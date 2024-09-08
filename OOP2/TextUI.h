#pragma once
#include "GameObject.h"

class IDamageable;

class Canvas;

class TextUI : public GameObject {
	GameObject* parent;
	IDamageable* damageable;
	float	hp;
	int		n_remaining_frames;

public:
	TextUI(GameObject* parent);

	void draw(Canvas* canvas) const override;

	void update(const Canvas* canvas) override;
};

