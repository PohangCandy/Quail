#include "Enemy.h"
#include "Bullet.h"
#include "Canvas.h"
#include "Player.h"
#include "TextUI.h"
#include "Canvas.h"

Enemy::Enemy(const char* shape, int pos, float hp, float dpf)
	: GameObject(shape, pos), hp(hp), dpf(dpf), nRemainingFire(rand() % 30)
{
	//addChild(new TextUI(this));
	text = new TextUI(this);
	Add(text);
}

Enemy::~Enemy()
{
	text->setDead();
}

GameObject* Enemy::findPlayer()
{
	for (auto obj : Objects) {
		if (obj == this) continue;
		if (dynamic_cast<Player*>(obj) != nullptr) return obj;
	}
	return nullptr;
}


void Enemy::update()
{
	// check whether it is time to attack.
	if (nRemainingFire > 0) {
		nRemainingFire--;
	}
	else if (nRemainingFire == 0) {
		if (GameObject::HasAnEmptySlot()) {
			GameObject* player = GameObject::FindClosestTarget(this, "player");
			Bullet* bullet = new Bullet();
			bullet->init(this, player);
			GameObject::Add(bullet);
			nRemainingFire = canvas->getFrameRate() * 5 + rand() % canvas->getFrameRate();
		}
	}
	int start = getStartPosition();
	int end = getEndPosition();

	// detect any collision and handle the collision.
	for (auto obj : Objects) {
		if (obj == this) continue;
		IDamageable* damageable = dynamic_cast<IDamageable*>(obj);
		if (damageable == nullptr) continue;

		int target_start;
		int target_end;
		obj->getStartEndPositions(&target_start, &target_end);
		if (::isOverlap(start, end + 1, target_start, target_end)
			|| ::isOverlap(start - 1, end, target_start, target_end)) {
			damageable->getDamaged(dpf);
		}
	}
}
