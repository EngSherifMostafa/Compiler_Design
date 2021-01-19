#include "Scanner.h"

//constructor
Scanner::Scanner()
{
	matchFlag = false, complComm = false;
	
	ch = NULL; //as temp char to transfer from code file to string
	
	content = "", type = "",

	//"symStr" is any "token" act like symbol
	passStr = "", symStr = "";
}

//destructor
Scanner::~Scanner()
{
	Scanner(); //re initialize attributes
}

void Scanner::printLine() const
{
	cout << "------------------------------------------";
}

void Scanner::printFile(const string fileContent) const
{
	cout << "Code file is: \n";
	printLine();
	cout << "\n" << fileContent << "\n";
	printLine();
	cout << "\n";
}

void Scanner::splitStr(string fileContent)
{
	for (int i = 0; i < fileContent.length(); i++)
	{	
		//single line comment detector
		if ((i + 3) < fileContent.length() && fileContent[i] == '<' && fileContent[i + 1] == '!' && fileContent[i + 2] == '-' && fileContent[i + 3] == '-')
		{
			passStr = "";
			passStr += fileContent[i++];
			passStr += fileContent[i++];
			passStr += fileContent[i++];
			passStr += fileContent[i++];

			while (fileContent[i] != '\n' && i < fileContent.length())
			{
				if (fileContent[i] == '-' && fileContent[i + 1] == '-' && fileContent[i + 2] == '>')
				{
					passStr += fileContent[i++];
					passStr += fileContent[i++];
					passStr += fileContent[i];
					complComm = true; //single line comment has been detected
					break;
				}
				passStr += fileContent[i++];
			}
			
			if (complComm)
			{
				complComm = false;
				if (regExps(passStr))
				{
					passStr = "";
					symStr = "";
					matchFlag = false;
					printLine();
					cout << "\n";
				}
			}
			else
			{
				unCompletedComment(passStr);
				i--;
			}

		} //end of single line comment detector

		//multiline comment detector
		else if ((i + 1) < fileContent.length() && fileContent[i] == '#' && fileContent[i + 1] == '#')
		{
			passStr = "";
			passStr += fileContent[i++];
			passStr += fileContent[i++];

			while (i < fileContent.length())
			{
				if (fileContent[i] == '#')
				{
					passStr += fileContent[i];
					complComm = true; //multiline comment has been detected
					break;
				}
				passStr += fileContent[i++];
			}
			
			if (complComm)
			{
				complComm = false;
				if (regExps(passStr))
				{
					passStr = "";
					symStr = "";
					matchFlag = false;
					printLine();
					cout << "\n";
				}
			}
			else
			{
				unCompletedComment(passStr);
				i--;
			}

		} //end of multiline comment detector

		//identifiers detector
		else if (( (i + 1) < fileContent.length() && fileContent[i] == '$') && 
				((fileContent[i + 1] >= 65 && fileContent[i + 1] <= 90) || (fileContent[i + 1] >= 97 && fileContent[i + 1] <= 122)))
		{
			passStr = "";
			passStr += fileContent[i++];
			
			while (i < fileContent.length() &&
				  (fileContent[i] >= 65 && fileContent[i] <= 90) ||
				  (fileContent[i] >= 97 && fileContent[i] <= 122))
				passStr += fileContent[i++];
			
			if (i < fileContent.length()) i--;

			if (regExps(passStr))
			{
				passStr = "";
				symStr = "";
				matchFlag = false;
				printLine();
				cout << "\n";
			}

		} //end of identifiers detector

		//normal tokens
		else
		{
			if (fileContent[i] == ' ' || fileContent[i] == '\n')
			{
				passStr += fileContent[i];
				
				if (regExps(passStr))
				{
					passStr = "";
					symStr = "";
					matchFlag = false;
					printLine();
					cout << "\n";
					continue;
				}
			}
			
			passStr += fileContent[i];
			if (regExps(passStr))
			{
				passStr = "";
				symStr = "";
				matchFlag = false;
				printLine();
				cout << "\n";
			}

		} //end of normal tokens
	} //end of for loop
}

void Scanner::unCompletedComment(const string str)
{
	passStr = "";
	for (int i = 0; i < str.length(); i++)
	{
		//identifiers detector
		if (((i + 1) < str.length() && str[i] == '$') &&
			((str[i + 1] >= 65 && str[i + 1] <= 90) || (str[i + 1] >= 97 && str[i + 1] <= 122)))
			{
				passStr += str[i++];

				while (i < str.length() &&
					(str[i] >= 65 && str[i] <= 90) ||
					(str[i] >= 97 && str[i] <= 122))
					passStr += str[i++];

				if (i < str.length()) i--;

				if (regExps(passStr))
				{
					passStr = "";
					symStr = "";
					matchFlag = false;
					printLine();
					cout << "\n";
				}

			} //end of identifiers detector

		//normal tokens
		else
		{
			if (str[i] == ' ' || str[i] == '\n')
			{
				passStr += str[i];

				if (regExps(passStr))
				{
					passStr = "";
					symStr = "";
					matchFlag = false;
					printLine();
					cout << "\n";
					continue;
				}
			}

			passStr += str[i];
			if (regExps(passStr))
			{
				passStr = "";
				symStr = "";
				matchFlag = false;
				printLine();
				cout << "\n";
			}

		} //end of normal tokens
	} //end of for loop
}

bool Scanner::regExps(const string str)
{
	//Single Line Comments
	type = "Single Line Comments";
	regex slc("(<!--.*?-->)");
	if (matchRegex(type, str, slc))
		return true;

	//Multi-Line comment
	type = "Multi-Line comment";
	regex mlc("#{2}(.|\n)*?#");
	if (matchRegex(type, str, mlc))
		return true;

	//Identifiers
	type = "Identifiers";
	regex id("\\$[a-zA-Z]+");
	if (matchRegex(type, str, id))
		return true;

	//Keywords
	type = "Keywords";
	regex kw("(if|else|int|return|void|while)"); //note that \^ mean start with
	if(matchRegex(type, str, kw))
		matchFlag = true;

	//Numbers
	type = "Numbers";
	regex num("\\d");
	if(matchRegex(type, str, num))
		matchFlag = true;
	
	//White space
	type = "White space";
	regex ws("\\s");
	if(matchRegex(type, str, ws))
		matchFlag = true;

	//Symbols
	type = "Symbols";
	if (symDetector(type, str))
		matchFlag = true;

	return matchFlag;
}

bool Scanner::symDetector(const string type, const string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		//initial symStr after every loop
		symStr = "";
	
		//multi symbol
		if ((i + 2) < str.length() && str[i] == '=' && str[i + 1] == '=' && str[i + 2] == '=' && i < str.size())
		{
			symStr += str[i++];
			symStr += str[i++];
			symStr += str[i];
			regex sCom("={3}");
			if (matchRegex(type, symStr, sCom))
				matchFlag = true;
		}

		else if ((i + 1) < str.length() && str[i] == '=' && str[i + 1] == '=')
		{
			symStr += str[i++];
			symStr += str[i];
			regex com("={2}");
			if(matchRegex(type, symStr, com))
				matchFlag = true;
		}

		else if ((i + 1) < str.length() && str[i] == '!' && str[i + 1] == '=')
		{
			symStr += str[i++];
			symStr += str[i];
			regex nEq("(!=)");
			if(matchRegex(type, symStr, nEq))
				matchFlag = true;
		}

		else if ((i + 1) < str.length() && str[i] == '<' && str[i + 1] == '=')
		{
			symStr += str[i++];
			symStr += str[i];
			regex lte("<=");
			if(matchRegex(type, symStr, lte))
				matchFlag = true;
		} //end of multi symbol

		  //single symbol
		else
		{
			symStr += str[i];

			regex ass("\\=");
			if (matchRegex(type, symStr, ass))
			{
				matchFlag = true;
				continue;
			}

			regex not("\\!");
			if (matchRegex(type, symStr, not))
			{
				matchFlag = true;
				continue;
			}

			regex lt("\\<");
			if (matchRegex(type, symStr, lt))
			{
				matchFlag = true;
				continue;
			}

			regex lp("\\(");
			if (matchRegex(type, symStr, lp))
			{
				matchFlag = true;
				continue;
			}

			regex rp("\\)");
			if (matchRegex(type, symStr, rp))
			{
				matchFlag = true;
				continue;
			}

			regex lc("\\{");
			if (matchRegex(type, symStr, lc))
			{
				matchFlag = true;
				continue;
			}

			regex rc("\\}");
			if (matchRegex(type, symStr, rc))
			{
				matchFlag = true;
				continue;
			}

			regex lb("\\[");
			if (matchRegex(type, symStr, lb))
			{
				matchFlag = true;
				continue;
			}

			regex rb("\\]");
			if (matchRegex(type, symStr, rb))
			{
				matchFlag = true;
				continue;
			}

			regex and ("\\&");
			if (matchRegex(type, symStr, and))
			{
				matchFlag = true;
				continue;
			}

			regex or ("\\|");
			if (matchRegex(type, symStr, or))
			{
				matchFlag = true;
				continue;
			}

			regex comma("\\,");
			if (matchRegex(type, symStr, comma))
			{
				matchFlag = true;
				continue;
			}

			regex semi("\\;");
			if (matchRegex(type, symStr, semi))
			{
				matchFlag = true;
				continue;
			}

			regex plus("\\+");
			if (matchRegex(type, symStr, plus))
			{
				matchFlag = true;
				continue;
			}

			regex minus("\\-");
			if (matchRegex(type, symStr, minus))
			{
				matchFlag = true;
				continue;
			}

			regex times("\\*");
			if (matchRegex(type, symStr, times))
			{
				matchFlag = true;
				continue;
			}

			regex over("\\/");
			if (matchRegex(type, symStr, over))
			{
				matchFlag = true;
				continue;
			}
		} //end of single symbol
	} //end of for loop
	
	return matchFlag;
}

bool Scanner::matchRegex(const string type, string str, const regex re)
{
	if (regex_search(str, match, re))
	{
		cout << "< " << match[0] << " , " << type << " >\n";
		str = match.suffix();
		return true;
	}
	return false;
}

bool Scanner::readFile(const string path, string &content)
{
	content = "";
	file.open(path);

	if (file.is_open())
	{
		while (file.get(ch))
			content += ch;
		file.close();
		return true;
	}

	return false;
}