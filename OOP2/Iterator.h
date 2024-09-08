#pragma once
class GameObject;

class Iterator {
	GameObject** container;
	int current;
	int maxCapacity;

	GameObject* deadEnd;

public:
	Iterator(GameObject** container, int max) : container(container), current(-1), maxCapacity(max), deadEnd((GameObject*)0xdeaddeaddeaddead) {}

	const GameObject* cend() const { return deadEnd; }
	GameObject* end() const { return deadEnd; }

	GameObject* getNext();

	void reset() { current = -1; }
};

