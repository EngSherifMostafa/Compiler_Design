#pragma once
#include <iostream>
#include <string>
#include <windows.h> //screen calculations

class Intro_Drawer
{
public:
	Intro_Drawer();
	~Intro_Drawer();

private:
	void intro();
	void printChar(char);
	void drawSpecialLine(std::string, char);

	int screenWidth, space, counter, index;
	std::string str;
};