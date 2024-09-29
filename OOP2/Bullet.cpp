#include "Bullet.h"
#include "IDamageable.h"
#include "Canvas.h"


void Bullet::update() 
{
	if (canvas->isOutOfScreen(getPos(), getShapeSize())) {
		setDead();
		return;
	}
	int start = getStartPosition();
	int end = getEndPosition();

	// check collision 
	// if so, make the bullet dead.
	bool collided = false;
	int max_jump = 1;

	Iterator it(GameObject::Objects, GameObject::MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {
		if (obj == this) continue;

		IDamageable* damageable = dynamic_cast<IDamageable*>(obj);
		if (damageable == nullptr) continue;

		// if not colliding, move on next.
		if (isOverlap(obj) == false) continue;

		damageable->getDamaged(5.0f);

		if (penetrable == true) {
			collided = true;

			max_jump = obj->getShapeSize() + 2 > max_jump ? obj->getShapeSize() + 2 : max_jump;
			continue;
		}

		setDead();
		return;
	}
	if (collided == true) move(max_jump);
	else move(1);
}


bool Bullet::isOutOfScreen() const
{
	return canvas->isOutOfScreen(getPos(), getShapeSize());
}