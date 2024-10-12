#include "TextUI.h"
#include "IDamageable.h"
#include "Canvas.h"

TextUI::TextUI(GameObject* parent)
	: GameObject("", 1), parent(parent), hp(0.0f), 
	n_remaining_frames(60)
{
	damageable = dynamic_cast<IDamageable*>(parent);
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

	//GameObject의 Update()에서 플레이어나 적이 죽을 경우
	//해당 객체를 동적 해제 시켜버린다.
	//damageable 객체를 찾을 수 없으므로 오류가 난다.
	//해당 객체가 삭제되었다면 TextUI도 삭제하면 되지 않을까?

	//GameObject가 사라지면서 Object에 있는 포인터는 제개로 삭제가 된다.
	//하지만 하향 형변환해서 가르키고 있는 Damagable 포인터는 해제되지 않았다.
	float current_hp = damageable->getHealth();
	if (hp == current_hp) return;
	hp = current_hp;
	n_remaining_frames = canvas->getFrameRate();
	sprintf(buf, "%3.1f", hp);
	setShape(buf);
	
}
