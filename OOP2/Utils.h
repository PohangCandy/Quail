#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <Windows.h>


struct Position { //Screen Position
	int x;
	int y;

	Position(int x, int y) : x(x), y(y) {}

	// copy constructor
	Position(const Position& other): Position(other.x,other.y){}




};

typedef Position Dimension;

class Borland {

public:
	static void Initialize()
	{
		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 25;
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
		//SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	}

	static int WhereX()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int WhereY()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void GotoXY(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void GotoXY(const Position* pos)
	{
		if (!pos) return;
		GotoXY( (*pos).x, (*pos).y);
	}
	static void GotoXY(const Position& pos)
	{
		GotoXY( pos.x, pos.y);
	}
};

class Debug {
	static int nDebugLine;
	static char whiteSpaces[80];

public:
	static void Log(const char* fmt, ...)
	{
		char dest[1024];
		static clock_t startTime = clock();

		if (whiteSpaces[0] == '\0') { // if not initialized yet.
			memset(whiteSpaces, ' ', 80);
			whiteSpaces[79] = '\0';
		}

		va_list argPtr;

		va_start(argPtr, fmt);

		Borland::GotoXY(0, nDebugLine++ % 20 + 20);
		vsprintf(dest, fmt, argPtr);
		va_end(argPtr);
		printf("[%5d: %.3f] %s", nDebugLine, (clock() - startTime)/1000.0f, dest);
		printf("\n%s", whiteSpaces);
	}
};

enum class Direction {
	None,
	Left,
	Right,
};

bool isOverlap(int src_start, int src_end, int target_start, int target_end);



#endif 
