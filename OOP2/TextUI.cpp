#include "TextUI.h"
#include "IDamageable.h"
#include "Canvas.h"

TextUI::TextUI(GameObject* parent)
	: GameObject("", 1), parent(parent), hp(0.0f),canvas(GetCanvas()),
	n_remaining_frames(60), 
	damageable(dynamic_cast<IDamageable*>(parent))
{
	if (parent == nullptr)
		return;
}


void TextUI::draw() const {
	if (n_remaining_frames == 0) return;

	int parent_pos = parent->getPos();
	canvas->draw(getShape(), parent_pos + getPos());
}

void TextUI::update() {
	char buf[10];

	if (n_remaining_frames > 0) --n_remaining_frames;

	float current_hp = damageable->getHealth();
	if (hp == current_hp) return;
	hp = current_hp;
	n_remaining_frames = canvas->getFrameRate();
	sprintf(buf, "%3.1f", hp);
	setShape(buf);
}
