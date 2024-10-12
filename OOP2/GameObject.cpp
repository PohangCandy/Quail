#include "GameObject.h"
#include "Canvas.h"
#include "Player.h"
#include "Enemy.h"
#include "TextUI.h"

vector<GameObject*> GameObject::Objects;
vector<GameObject*> GameObject::PendingObjects;

GameObject::GameObject(const char* str, int pos)
	: canvas(Canvas::GetInstance()),
	shape(nullptr), pos(pos), alive(true), direction(Direction::None) {
	setShape(str);
}

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
	Player* p1 = new Player{ "(^_^)", 0, 10000.0f };
	Enemy* e1 = new Enemy{ "(+*_*)", 20, 5.0f, 10.0f / Canvas::GetInstance()->getFrameRate() };
	Enemy* e2 = new Enemy{ "(+*_*+)", 60, 50.0f, 10.0f / Canvas::GetInstance()->getFrameRate() };
	//TextUI* t1 = new TextUI{ p1 };
	//TextUI* t2 = new TextUI{ e1 };
	//TextUI* t3 = new TextUI{ e2 };
	Add(p1);
	Add(e1);
	Add(e2);
	//Add(t1);
	//Add(t2);
	//Add(t3);
}

void GameObject::Destroy()
{
	while (PendingObjects.empty() == false) {
		auto obj = PendingObjects.back();
		delete obj;
		PendingObjects.pop_back();
	}
	while (Objects.empty() == false) {
		auto obj = Objects.back();
		delete obj;
		Objects.pop_back();
	}

}

void GameObject::Add(GameObject* obj)
{
	if (obj == nullptr) return;
	PendingObjects.push_back(obj);
}

void GameObject::Remove(GameObject* obj)
{
	auto it = find(Objects.begin(), Objects.end(), obj);
	if (it != Objects.end())
		Objects.erase(it);
	delete obj;
}

bool GameObject::HasAnEmptySlot()
{
	return true;
}

bool GameObject::Contains(GameObject* obj)
{
	auto it = find(Objects.cbegin(), Objects.cend(), obj);
	return it != Objects.cend();
}

void GameObject::Draw()
{
	for (auto obj : Objects)
		obj->internalDraw();
}

void GameObject::Update()
{
	int i = 0;
	for (auto obj : Objects) {
		obj->internalUpdate();
		i++;
	}

	// remove dying objects
	for (auto it = Objects.begin(); it != Objects.end(); )
	{
		auto obj = *it;
		if (obj->isAlive()) {
			it++;
			continue;
		}

		delete obj;
		it = Objects.erase(it);
	}

	// add pending objects to regular objects
	while (PendingObjects.empty() == false) {
		auto obj = PendingObjects.back();
		PendingObjects.pop_back();
		Objects.push_back(obj);
	}
}

void GameObject::ProcessInput(int ch)
{
	for (auto obj : Objects)
		obj->processInput(ch);
}

GameObject* GameObject::FindClosestTarget(const GameObject* source, const char* target_tag)
{
	GameObject* closest = nullptr;
	if (source == nullptr) return closest;

	int closestDistance = 0;

	for (auto obj : Objects) {
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

