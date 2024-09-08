#pragma once

#include "Utils.h"

class GameObject;

class Canvas {
	int		size;
	char* screen;
	int		frame_rate;
	int		n_frames;

public:
	Canvas(int size = 80, int frame_rate = 30)
		: size(size), screen(new char[(size_t)size + 1]), frame_rate(frame_rate), n_frames(0)
	{}

	~Canvas()
	{
		delete[] screen;
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	void draw(const GameObject* obj);

	void draw(const char* shape, int pos)
	{
		if (!shape) return;

		int len = (int)strlen(shape);
		if (pos < 0) {
			if (pos + len <= 0) return;
			shape = shape - pos;
			len = (int)strlen(shape);
			pos = 0;
		}
		if (pos + strlen(shape) >= size) {
			if (pos >= size) return;
			len = size - pos;
		}
		memcpy(screen + pos, shape, len);
	}

	void render() const
	{
		printf("%s\r", screen);

		Sleep(1000 / frame_rate);
	}

	bool isOutOfScreen(int pos, int size) const
	{
		return pos + size < 0 || pos >= this->size;
	}

	void update()
	{
		n_frames++;
	}

	// getter
	int getCurrentFrameNumber() const { return n_frames; }

	int getScreenSize() const { return size; }

	int getFrameRate() const { return frame_rate; }
};

