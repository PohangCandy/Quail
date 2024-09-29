#include "Canvas.h"
#include "Player.h"
#include "TextUI.h"
#include "Bullet.h"

Player::Player(const char* shape, int pos, float hp)
	: GameObject(shape, pos), hp(hp), blink_period(-1),canvas(GetCanvas())
{
	addChild(new TextUI(this));
}

void Player::update()
{
	Iterator it(GameObject::Objects, GameObject::MaxAllocSize);
	GameObject* obj = nullptr;
	while ((obj = it.getNext()) != it.end()) {

		// be careful the following is not obj->isAlive() == false

		if (this->isAlive() == false) break;

		if (obj == this) continue;

		IDamageable* damageable = dynamic_cast<IDamageable*>(obj);
		if (damageable == nullptr) continue;

		if (isOverlap(obj) == true) {
			damageable->getDamaged(0.1f);
		}
	}
	if (hp < 10.0f) {
		blink_period = (int)hp; // intentionally
		if (blink_period == 0) blink_period = 1;
	}
}

void Player::fireBullet()
{
	if (canvas == nullptr) return;

	if (GameObject::HasAnEmptySlot() == false) return;

	Bullet* bullet = new Bullet(true);
	GameObject::Add(bullet);

	GameObject* closestEnemy = nullptr;
	switch (getDirection()) {
	case Direction::None:
		closestEnemy = GameObject::FindClosestTarget(this, "enemy");
		bullet->init(this, closestEnemy);
		break;
	case Direction::Left:
	case Direction::Right:
		bullet->init(this, getDirection());
		break;
	}
}

void Player::processInput(int key) {
	switch (key) {
	case 'a':
		if (getDirection() == Direction::Left) move(-4);
		else setDirection(Direction::Left);
		break;
	case 'd':
		if (getDirection() == Direction::Right) move(4);
		else setDirection(Direction::Right);
		break;
	case ' ':
		fireBullet();
		break;
	}
}
