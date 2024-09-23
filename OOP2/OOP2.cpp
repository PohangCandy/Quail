#include <stdio.h>
#include <stdlib.h> // itoa
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <iostream>
#include <vector>

#include "Canvas.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "TextUI.h"


using namespace std;


int main()
{
	Canvas	canvas;

	GameObject::Init(&canvas, 30);

	bool exit_flag{ false };

	vector<int> vec;

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(i);
	}

	for (auto it = vec.cbegin(); it != vec.cend(); it++)
	{
		cout << *it << " ";
	}

	while (exit_flag == false) { // if player is alive

		canvas.clear();

		/* process game logic for each game object */
		GameObject::Update(&canvas);
		canvas.update();

		/* draw game objects */
		GameObject::Draw(&canvas);

		/* process input event. */
		if (_kbhit()) {
			char ch = _getch();

			switch (ch) {
			case 'q':
				exit_flag = true;
				break;
			case 'n':
				GameObject::Add(new Player{ "(^_^)", rand() % canvas.getScreenSize(), 50.0f });
				break;
			case 'e':
				GameObject::Add(new Enemy{ "(+*_*)", rand() % canvas.getScreenSize(), 50.0f, 10.0f / canvas.getFrameRate() });
				break;
			default:
				GameObject::ProcessInput(ch, &canvas);
				break;
			}
		}
		canvas.render();

	} /* end of while(1) */

	GameObject::Destroy();

	return 0;
}