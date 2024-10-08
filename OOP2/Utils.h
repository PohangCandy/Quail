#pragma once

#include <stdio.h>
#include <stdlib.h> // itoa
#include <conio.h>
#include <cstring>
#include <windows.h>


enum class Direction {
	None,
	Left,
	Right,
};

bool isOverlap(int src_start, int src_end, int target_start, int target_end);