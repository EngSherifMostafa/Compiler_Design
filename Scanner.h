#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
using namespace std;

class Scanner
{
public:
	Scanner();
	~Scanner();

	//methods used in main function
	void printLine() const;
	void printFile(const string fileContent) const;
	void splitStr(string fileContent);
	bool readFile(const string path, string &content);

private:
	//methods used inside class
	void unCompletedComment(const string str);
	bool symDetector(const string type, const string str);
	bool regExps(const string str);
	bool matchRegex(const string type, string str, const regex re);

	//define attributes
	bool matchFlag, complComm;
	char ch;
	string content, type, passStr, symStr;
	smatch match;
	ifstream file;
};
#endif