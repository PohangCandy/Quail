#pragma once
#include <stdio.h> // 표준 입출력 함수 제공, printf()
#include <stdlib.h> // 일반적인 유틸리티 함수 제공, malloc()
#include <conio.h> // 콘솔 입출력 함수 제공 , getch()
#include <cstring> // C 스타일의 문자열 관련 함수 제공, strcpy()
#include <windows.h> // Windows 운영체제에서 제공하는 다양한 API들을 사용하기 위한 헤더 파일
//API : 두 소프트웨어 시스템이 서로 정보를 주고받거나 요청을 처리하는 방식을 규정하는 인터페이스

enum class Direction {
	None,
	Left,
	Right,
};

bool isOverlap(int src_start, int src_end, int target_start, int target_end)
{
	return src_end > target_start && target_end > src_start;
}
