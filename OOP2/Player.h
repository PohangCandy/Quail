#pragma once
#include "GameObject.h"
#include "Canvas.h"
#include "IDamageable.h"

class TextUI;

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

	void draw() const override
	{
		if (blink_period >= 0
			&& canvas->getCurrentFrameNumber() % blink_period == 0)
			return;

		GameObject::draw();
	}

	void move(int inc)
	{
		setPos(getPos() + inc);
	}

	void fireBullet();

	void update() override;

	void processInput(int key) override;
};


