#include "Canvas.h"
#include "GameObject.h"


Canvas* Canvas::Instance = nullptr;

Canvas* Canvas::GetInstance()
{
	if (Instance == nullptr) {
		Instance = new Canvas;
	}
	return Instance;
}

void Canvas::draw(const GameObject* obj)
{
	if (obj == nullptr) return;

	draw(obj->getShape(), obj->getPos());
}
