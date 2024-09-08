#include "Bullet.h"
#include "Canvas.h"
#include "IDamageable.h"
#include "Iterator.h"

Bullet::Bullet(bool penetrable) : GameObject(nullptr, 0), penetrable(penetrable)
{
	setDirection(Direction::None);
}

void Bullet::init(const GameObject* from, const GameObject* to)
{
	int from_start, from_end;
	int to_start, to_end;

	from->getStartEndPositions(&from_start, &from_end);
	Direction heading = (Direction)(1 + rand() % 2);
	if (to != nullptr) {
		to->getStartEndPositions(&to_start, &to_end);
		if (from_start <= to_start)
			heading = Direction::Right;
		else heading = Direction::Left;
	}
	init(from, heading);
}

void Bullet::init(const GameObject* from, Direction heading)
{
	int from_start, from_end;

	from->getStartEndPositions(&from_start, &from_end);
	setDirection(heading);
	if (heading == Direction::Right) {
		setPos(from_end);
		setShape("-->");
	}
	else if (heading == Direction::Left) {
		setPos(from_start - (int)strlen("<--"));
		setShape("<--");
	}
}

void Bullet::update(const Canvas* canvas)
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

bool Bullet::isOutOfScreen(const Canvas* canvas) const
{
	return canvas->isOutOfScreen(getPos(), getShapeSize());
}