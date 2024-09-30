#include "GameObject.h"
#include "Canvas.h"
#include "Player.h"
#include "Enemy.h"
#include "Iterator.h"

vector<GameObject*> GameObject::Objects;
vector<GameObject*> GameObject::PendingObjects;
int GameObject::MaxAllocSize = 0;

GameObject::GameObject(const char* str, int pos)
	: canvas(Canvas::GetInstance()),
	shape(nullptr), pos(pos), alive(true), direction(Direction::None)	
{
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
	Canvas* canvas = Canvas::GetInstance();
	
	Add(new Player{ "(^_^)", 0, 10000.0f });
	Add(new Enemy{ "(+*_*)", 20, 50.0f, 10.0f / canvas->getFrameRate() });
	Add(new Enemy{ "(+*_*+)", 60, 50.0f, 10.0f / canvas->getFrameRate() });
}

void GameObject::Destroy()
{
	while (Objects.empty() == false)
	{
		auto back = Objects.back();
		Objects.pop_back();
		delete back;
	}

	Objects.clear();
}

void GameObject::Add(GameObject* obj)
{
	if (obj == nullptr) return;

	// 중복된 요소 제거하기
	auto it = find(Objects.begin(), Objects.end(), obj);
	if (it != Objects.end()) return;

	Objects.push_back(obj);
}

void GameObject::Remove(GameObject* obj)
{
	if (obj == nullptr) return;

	auto it = find(Objects.begin(), Objects.end(), obj);
	if (it == Objects.end()) return;

	auto target = *it;
	Objects.erase(it);
	// erase는 포인터 정보만 날려주는 것이다.
	//동적해제는 사용자가 해주어야 한다.
	delete target;
}

bool GameObject::HasAnEmptySlot()
{
	return true;
}

bool GameObject::Contains(GameObject* obj)
{
	auto it = find(Objects.begin(), Objects.end(), obj);
	return it != Objects.end();
}

void GameObject::Draw()
{
	for (auto obj : Objects)
	{
		obj->internalDraw();
	}
}

void GameObject::Update()
{
	for (auto obj : Objects)
		obj->internalUpdate();
	
	for (auto obj : Objects)
	{
		if (obj->isAlive() == true) continue;
		delete obj;
	}

	Objects.erase(remove_if(Objects.begin(), Objects.end(),
		[](auto obj) 
		{
			return obj->isAlive() == false;
		}), 
		Objects.end());

	while (PendingObjects.empty() == false)
	{
		auto back = PendingObjects.back();
		PendingObjects.pop_back();
		Objects.push_back(back);
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

	for(auto obj: Objects) {
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

