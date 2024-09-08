#include "Iterator.h"
#include "GameObject.h"

GameObject* Iterator::getNext() {
	while (++current < maxCapacity && (container[current] == nullptr || container[current]->isAlive() == false)) {
		// move next
		;
	}
	if (current >= maxCapacity) return end();
	return container[current];
}