#pragma once
#include "GameObject.h"
#include "IDamageable.h"
#include "Iterator.h"

class Player;
class TextUI;
class Canvas;

class Enemy : public GameObject, public IDamageable {
	float	hp;
	float	dpf;

	int		nRemainingFire;

	Canvas* canvas;

	// enemy-related functions

	GameObject* findPlayer();

public:

	Enemy(const char* shape, int pos, float hp, float dpf);

	~Enemy()
	{}

	void move(int inc)
	{
		setPos(getPos() + inc);
	}

	void move_automatically(int player_pos)
	{
		int pos = getPos();
		if (player_pos < pos) {
			move(-1);
		}
		else if (player_pos > pos) {
			move(1);
		}
	}

	void update() override;

	float getHealth() const override { return hp; }

	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f) setDead();
		return getHealth();
	}

	void processInput(int key) override {
		if (key == 'j') {
			move(-1);
		}
		else if (key == 'l') {
			move(1);
		}
	}
};


