#pragma once
#include <stdio.h> // ǥ�� ����� �Լ� ����, printf()
#include <stdlib.h> // �Ϲ����� ��ƿ��Ƽ �Լ� ����, malloc()
#include <conio.h> // �ܼ� ����� �Լ� ���� , getch()
#include <cstring> // C ��Ÿ���� ���ڿ� ���� �Լ� ����, strcpy()
#include <windows.h> // Windows �ü������ �����ϴ� �پ��� API���� ����ϱ� ���� ��� ����
//API : �� ����Ʈ���� �ý����� ���� ������ �ְ�ްų� ��û�� ó���ϴ� ����� �����ϴ� �������̽�

enum class Direction {
	None,
	Left,
	Right,
};

bool isOverlap(int src_start, int src_end, int target_start, int target_end)
{
	return src_end > target_start && target_end > src_start;
}
