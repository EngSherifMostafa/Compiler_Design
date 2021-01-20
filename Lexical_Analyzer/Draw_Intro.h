#pragma once
#include <iostream>
#include <string>
#include <windows.h> //screen calculations

class Draw_Intro
{
public:
	Draw_Intro();
	~Draw_Intro();

private:
	void intro();
	void printChar(char);
	void drawSpecialLine(std::string, char);

	int screenWidth, space, counter, index;
	std::string str;
};