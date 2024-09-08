#pragma once
#include "GameObject.h"
#include "IDamageable.h"

class Canvas;

class Player : public GameObject, public IDamageable {

	float	hp;
	int		blink_period;

public:

	Player(const char* shape, int pos, float hp);

	~Player()
	{}


	float getHealth() const override { return hp; }
	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f) setDead();
		return getHealth();
	}

	void draw(Canvas* canvas) const override;

	void move(int inc)
	{
		setPos(getPos() + inc);
	}

	void fireBullet(const Canvas* canvas);

	void update(const Canvas* canvas) override;

	void processInput(int key, const Canvas* canvas) override;
};

