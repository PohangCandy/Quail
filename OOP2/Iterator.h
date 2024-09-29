#pragma once
#include <vector>
using namespace std;

class GameObject;

class Iterator {
	vector<GameObject*>& container;
	int current;
	int maxCapacity;

	GameObject* deadEnd;

public:
	Iterator(vector<GameObject*>& container, int max) : container(container), current(-1), maxCapacity(max), deadEnd((GameObject*)0xdeaddeaddeaddead) {}

	const GameObject* cend() const { return deadEnd; }
	GameObject* end() const { return deadEnd; }

	GameObject* getNext();

	void reset() { current = -1; }
};

