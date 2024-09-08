#pragma once
#include "GameObject.h"

class Canvas;

//class Direction;

class Bullet : public GameObject {

	bool	penetrable;

public:

	Bullet(bool penetrable = false);

	~Bullet()
	{}

	void move(int inc = 1)
	{
		switch (getDirection())
		{
		case Direction::Left:
			setPos(getPos() - inc);
			break;
		case Direction::Right:
			setPos(getPos() + inc);
			break;
		}
	}

	void update(const Canvas* canvas) override;

	bool isOutOfScreen(const Canvas* canvas) const;

	void init(const GameObject* from, Direction heading);

	void init(const GameObject* from, const GameObject* to);
};

