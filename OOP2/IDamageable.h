#pragma once
class IDamageable {
public:
	// pure virtual functions
	virtual float getHealth() const = 0; // get current health 
	virtual float getDamaged(float damage) = 0; // make this damaged
};

