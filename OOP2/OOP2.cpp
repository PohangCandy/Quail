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
#include "InputManager.h"

using namespace std;

int main()
{
	Borland::Initialize();
	InputManager inputManager;

	auto canvas = Canvas::GetInstance();
	GameObject::Init(30);

	Borland::GotoXY(1, 1);

	cout << "hello world";

	int x = Borland::WhereX();
	int y = Borland::WhereY();

	bool exit_flag{ false };


	while (exit_flag == false) { // if player is alive

		canvas->clear();

		/* process game logic for each game object */
		GameObject::Update();
		canvas->update();

		/* draw game objects */
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
		canvas->render();

	} /* end of while(1) */

	GameObject::Destroy();


	return 0;
}
