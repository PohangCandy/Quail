#pragma once
#include "GameObject.h"
#include "Iterator.h"

class Canvas;

class Bullet : public GameObject {

	Canvas* canvas;
	bool	penetrable;

public:

	Bullet(bool penetrable = false) : GameObject(nullptr, 0), penetrable(penetrable), canvas(GetCanvas())
	{
		setDirection(Direction::None);
	}

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

	void update() override;

	bool isOutOfScreen() const;

	void init(const GameObject* from, Direction heading)
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

	void init(const GameObject* from, const GameObject* to)
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
};


