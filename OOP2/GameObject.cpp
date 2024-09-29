#include "GameObject.h"
#include "Canvas.h"
#include "Player.h"
#include "Enemy.h"
#include "Iterator.h"

vector<GameObject*> GameObject::Objects;
int GameObject::MaxAllocSize = 0;

void GameObject::draw() const {
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



void GameObject::Init(int size = 10)
{
	Canvas* canvas = Canvas::GetInstance();
	Objects.resize(size);
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
	Objects.clear();
}

void GameObject::Add(GameObject* obj)
{
	if (obj == nullptr) return;

	//for (int i = 0; i < MaxAllocSize; i++)
	//{
	//	if (Objects[i] != nullptr) continue;

	//	Objects[i] = obj;
	//	//Objects.push_back(obj);
	//	return;
	//}

	// MaxAllocSize를 벗어나지 않도록 확인
	for (int i = 0; i < MaxAllocSize; i++)
	{
		// 빈 공간이 있는지 체크
		if (i < Objects.size() && Objects[i] == nullptr) {
			Objects[i] = obj; // 빈 공간에 객체 추가
			return;
		}
	}

	// 모든 공간이 가득 차 있다면 push_back을 사용하여 추가
	Objects.push_back(obj);
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

void GameObject::Draw()
{
	Iterator it(Objects, MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		obj->internalDraw();
	}
}

void GameObject::Update()
{
	Iterator it(Objects, MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		obj->internalUpdate();
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

void GameObject::ProcessInput(int ch)
{
	Iterator it(Objects, MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		obj->processInput(ch);
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

