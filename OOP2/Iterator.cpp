#include "Iterator.h"
#include "GameObject.h"

GameObject* Iterator::getNext() {
	while (++current < container.size() && (container[current] == nullptr || container[current]->isAlive() == false)) {
		// move next
		;
	}
	if (current >= container.size()) return end();
	return container[current];
}