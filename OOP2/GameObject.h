#pragma once

#include "Utils.h"
#include <iostream>
#include <vector>

class Canvas;

class GameObject {

	char* shape;
	int		pos;
	bool	alive;

	Direction	direction;
	
protected:

	static GameObject** Objects;
	static vector<GameObject*> Objects;
	static int MaxAllocSize;

	GameObject** children;
	int	  maxChildren;

	void addChild(GameObject* child)
	{

		for (int i = 0; i < maxChildren; i++)
		{
			if (children[i] != nullptr) continue;
			children[i] = child;
			return;
		}
	}

	void internalUpdate(const Canvas* canvas)
	{
		if (isAlive() == false) return;
		update(canvas);
		for (int i = 0; i < maxChildren && isAlive() == true; i++) {
			if (children[i] == nullptr) continue;
			children[i]->internalUpdate(canvas);
		}
	}

	void internalDraw(Canvas* canvas) const
	{
		if (isAlive() == false) return;
		draw(canvas);
		for (int i = 0; i < maxChildren && isAlive() == true; i++) {
			if (children[i] == nullptr) continue;
			children[i]->draw(canvas);
		}
	}

public:

	static void Init(const Canvas* canvas, int size);
	static void Destroy();
	static void Add(GameObject* obj);
	static void Remove(GameObject* obj);
	static bool HasAnEmptySlot();
	static bool Contains(GameObject* obj);
	static GameObject* FindClosestTarget(const GameObject* source, const char* target_tag);

	static void Draw(Canvas* canvas);
	static void Update(const Canvas* canvas);
	static void ProcessInput(int key, const Canvas* canvas);

	GameObject(const char* str, int pos);

	virtual ~GameObject()
	{
		for (int i = 0; i < maxChildren; i++) {
			if (children[i] == nullptr) continue;
			delete children[i];
		}
		delete[] children;

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

	virtual void draw(Canvas* canvas) const;

	virtual void update(const Canvas* canvas) {}

	virtual void processInput(int key, const Canvas* canvas) {}
};

