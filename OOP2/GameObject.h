#pragma once

#include "Utils.h"
#include <vector>
#include <algorithm>

class Canvas;

using namespace std;

class GameObject {

	
	char* shape;
	int		pos;
	bool	alive;

	Direction	direction;

protected:

	static vector<GameObject*> Objects;
	static vector<GameObject*> PendingObjects;

	Canvas* canvas;

	vector<GameObject*> children;

	void addChild(GameObject* child)
	{
		if (child != nullptr)
			children.push_back(child);
	}

	void internalUpdate()
	{
		if (isAlive() == false) return;
		update();
		for (auto it = children.begin(); it != children.end(); it++) {
			auto child = *it;
			if (child->isAlive() == false) continue;
			child->internalUpdate();
		}
	}

	void internalDraw() const
	{
		if (isAlive() == false) return;
		draw();
		for (auto child : children) {
			if (child->isAlive() == false) continue;
			child->draw();
		}
	}

public:

	static void Init(int size);
	static void Destroy();
	static void Add(GameObject* obj);
	static void Remove(GameObject* obj);
	static bool HasAnEmptySlot();
	static bool Contains(GameObject* obj);
	static GameObject* FindClosestTarget(const GameObject* source, const char* target_tag);

	static void Draw();
	static void Update();
	static void ProcessInput(int key);

	GameObject(const char* str, int pos);

	virtual ~GameObject()
	{
		while (children.empty() == false) {
			auto child = children.back();
			delete child;
			children.pop_back();
		}

		if (this->shape != nullptr)
			delete[] this->shape;
		this->shape = nullptr;
	}

	virtual bool isAlive() const { return alive; }

	void setDead() { alive = false; }

	Direction getDirection() const { return direction; }

	void setDirection(Direction direction) { this->direction = direction; }

	void setShape(const char* str)
	{
		if (str == nullptr) {
			if (this->shape != nullptr) {
				delete[] this->shape;
				this->shape = nullptr;
			}
			return;
		}

		if (this->shape != nullptr) {
			delete[] this->shape;
			this->shape = nullptr;
		}
		this->shape = new char[strlen(str) + 1];
		strcpy(this->shape, str);
	}

	int getShapeSize() const { return (int)strlen(this->shape); }

	const char* getShape() const { return this->shape; }

	int getPos() const { return this->pos; }

	void setPos(int pos) { this->pos = pos; }

	int getStartPosition() const { return pos; }

	int getEndPosition() const { return pos + (int)strlen(shape); }

	void getStartEndPositions(int* start, int* end) const
	{
		*start = getStartPosition();
		*end = getEndPosition();
	}

	bool isOverlap(const GameObject* other) const
	{
		if (other == nullptr) return false;

		int target_start, target_end, start, end;
		getStartEndPositions(&start, &end);
		other->getStartEndPositions(&target_start, &target_end);
		return ::isOverlap(start, end, target_start, target_end); // calling global function
	}

	virtual void draw() const;

	virtual void update() {}

	virtual void processInput(int key) {}
};



