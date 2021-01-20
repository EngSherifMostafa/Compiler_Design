#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

class Lexical_Analyzer
{
public:
	Lexical_Analyzer();
	~Lexical_Analyzer();

	//methods used in main function
	void printLine() const;
	void printFile(const std::string) const;
	void splitStr(std::string);
	bool readFile(const std::string, std::string&);

private:
	//methods used inside class
	void unCompletedComment(const std::string);
	bool symDetector(const std::string, const std::string);
	bool regExps(const std::string);
	bool matchRegex(const std::string, std::string, const std::regex);

	//define attributes
	bool matchFlag, complComm;
	char ch;
	std::string content, type, passStr, symStr;
	std::smatch match;
	std::ifstream file;
};