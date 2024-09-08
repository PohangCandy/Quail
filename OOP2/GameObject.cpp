#include "GameObject.h"
#include "Canvas.h"
#include "Iterator.h"
#include "Player.h"
#include "Enemy.h"

GameObject** GameObject::Objects = nullptr;
int GameObject::MaxAllocSize = 0;

GameObject::GameObject(const char* str, int pos)
	: shape(nullptr), pos(pos), alive(true), direction(Direction::None),
	maxChildren(10), children(new GameObject* [10])
{
	setShape(str);

	for (int i = 0; i < maxChildren; i++)
		children[i] = nullptr;
}

void GameObject::Init(const Canvas* canvas, int size = 10)
{
	Objects = new GameObject * [size];
	MaxAllocSize = size;

	for (int i = 0; i < MaxAllocSize; i++)
		Objects[i] = nullptr;

	Add(new Player{ "(^_^)", 0, 10000.0f });
	Add(new Enemy{ "(+*_*)", 20, 50.0f, 10.0f / canvas->getFrameRate() });
	Add(new Enemy{ "(+*_*+)", 60, 50.0f, 10.0f / canvas->getFrameRate() });
}

void GameObject::Destroy()
{
	for (int i = 0; i < MaxAllocSize; i++)
	{
		if (Objects[i] == nullptr) continue;

		delete Objects[i];
		Objects[i] = nullptr;
	}
	delete[] Objects;
}

void GameObject::Add(GameObject* obj)
{
	if (obj == nullptr) return;

	for (int i = 0; i < MaxAllocSize; i++)
	{
		if (Objects[i] != nullptr) continue;

		Objects[i] = obj;
		return;
	}
}

void GameObject::Remove(GameObject* obj)
{
	if (obj == nullptr) return;

	for (int i = 0; i < MaxAllocSize; i++)
	{
		if (Objects[i] != obj) continue;

		// Objects[i] == obj
		delete Objects[i];
		Objects[i] = nullptr;
		return;
	}
}

bool GameObject::HasAnEmptySlot()
{
	for (int i = 0; i < MaxAllocSize; i++)
		if (Objects[i] == nullptr) return true;
	return false;
}

bool GameObject::Contains(GameObject* obj)
{
	for (int i = 0; i < MaxAllocSize; i++)
		if (obj != nullptr && Objects[i] == obj) return true;
	return false;
}

void GameObject::Draw(Canvas* canvas)
{
	Iterator it(Objects, MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		obj->internalDraw(canvas);
	}
}

void GameObject::Update(const Canvas* canvas)
{
	Iterator it(Objects, MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		obj->internalUpdate(canvas);
	}

	// remove dying objects
	for (int i = 0; i < MaxAllocSize; i++)
	{
		if (Objects[i] == nullptr) continue;

		if (Objects[i]->isAlive() == true) continue;

		delete Objects[i];
		Objects[i] = nullptr;
	}
}

void GameObject::ProcessInput(int ch, const Canvas* canvas)
{
	Iterator it(Objects, MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		obj->processInput(ch, canvas);
	}
}

GameObject* GameObject::FindClosestTarget(const GameObject* source, const char* target_tag)
{
	GameObject* closest = nullptr;
	if (source == nullptr) return closest;

	int closestDistance = 0;

	Iterator it(GameObject::Objects, GameObject::MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		if (strcmp(target_tag, "enemy") == 0 && dynamic_cast<Enemy*>(obj) == nullptr) continue;
		if (strcmp(target_tag, "player") == 0 && dynamic_cast<Player*>(obj) == nullptr) continue;

		if (closest == nullptr) {
			closest = obj;
			closestDistance = abs(source->getPos() - closest->getPos());
			continue;
		}

		int dist = abs(source->getPos() - obj->getPos());
		if (dist < closestDistance) {
			closest = obj;
			closestDistance = dist;
		}
	}
	return closest;
}

void GameObject::draw(Canvas* canvas) const {
	if (canvas == nullptr) return;
	canvas->draw(this);
	switch (direction) {
	case Direction::Left:
		canvas->draw("<", getStartPosition());
		break;
	case Direction::Right:
		canvas->draw(">", getEndPosition() - 1);
		break;
	}
}