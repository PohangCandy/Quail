#include "Canvas.h"
#include "GameObject.h"

void Canvas::draw(const GameObject* obj)
{
	if (obj == nullptr) return;

	draw(obj->getShape(), obj->getPos());
}