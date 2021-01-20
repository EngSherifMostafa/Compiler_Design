#include "Lexical_Analyzer.h"
#include "Intro_Drawer.h"

int main()
{
	char again = 'Y';
	std::string path = "", fileContent = "";
	Lexical_Analyzer s;
	Intro_Drawer drw;

	do
	{
		path = "", fileContent = "";

		std::cout << "\nPLEASE NOTE THAT ANY SPACES IN FILE PATH WILL TERMINATE PROGRAM\nEnter path of code file with extension: ";
		std::cin >> path;
		std::cout << "\n";

		if (s.readFile(path, fileContent))
		{
			s.printFile(fileContent);

			//display
			std::cout << "\n\n< Token , Type >\n";
			s.printLine();
			std::cout << "\n";

			s.splitStr(fileContent);
		}

		else
		{
			std::cout << "File not found!\n";
			s.printLine();
			std::cout << "\n";
		}

		std::cout << "\nDo you want to enter another file (Y/N): ";
		std::cin >> again;
		std::cout << "\n";

	} while (again == 'Y' || again == 'y');

	system("pause");
	return 0;
}