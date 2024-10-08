// OOP2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <stdlib.h> // itoa
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <iostream>
#include <vector>

#include "Utils.h"
#include "Canvas.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "TextUI.h"

using namespace std;

int main()
{
	//싱글톤으로 작성된 Canvas 클래스
	//캔버스의 인스턴스가 없다면 생성하고, 있다면 해당 객체를 가지고 온다.
	auto canvas = Canvas::GetInstance();
	//GameObject의 PendingObjects에 생성하고 싶은 게임 오브젝트 자식객체 담아두기
	//Palyer는 모양, 위치, hp 정보 기본 생성자 인자로 가지고
	//Enemy는 거기에 추가로 프레임당 데미지 정보를 가진다.
	GameObject::Init(30);

	bool exit_flag{ false };


	while (exit_flag == false) { // if player is alive

		//캔버스 인스턴스에 있는 모든 내용을 ''으로 초기화 시킨다. 
		//마지막 캐릭터 배열의 값에 널 값을 넣어 문자열로 취급할 수 있게 만든다.
		//화면을 지우고 다시 그릴 수 있도록 준비한다.
		canvas->clear();

		//1.모든 Objects객체와 children의 update()함수를 호출한다.
		// 플레이어, 적, 총알은 겹치는 상대 객체가 데미지를 받도록 한다.
		// TextUI는 부모 객체의 남은 hp를 일정 시간동안 표시한다.
		//2.Objects중에 isAlive()가 false인 객체를 모두 해제시키고 지운다.
		//3.남아있는 PendingObjects를 Objects에 담는다.
		GameObject::Update();
		//프레임을 증가시킨다.
		canvas->update();

		//
		GameObject::Draw();

		/* process input event. */
		if (_kbhit()) {
			char ch = _getch();

			switch (ch) {
			case 'q':
				exit_flag = true;
				break;
			case 'n':
				GameObject::Add(new Player{ "(^_^)", rand() % canvas->getScreenSize(), 50.0f });
				break;
			case 'e':
				GameObject::Add(new Enemy{ "(+*_*)", rand() % canvas->getScreenSize(), 50.0f, 10.0f / canvas->getFrameRate() });
				break;
			default:
				GameObject::ProcessInput(ch);
				break;
			}
		}
		//screen에 작성된 내용을 그리고
		//정해진 frame만큼 sleep한다.
		canvas->render();

	} /* end of while(1) */

	GameObject::Destroy();


	return 0;
}
