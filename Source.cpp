#include "Scanner.h"
#include "DrawIntro.h"

int main()
{
	char again = 'Y';
	string path = "", fileContent = "";
	Scanner s;
	DrawIntro drw;

	do
	{
		path = "", fileContent = "";

		cout << "\nPLEASE NOTE THAT ANY SPACES IN FILE PATH WILL TERMINATE PROGRAM\nEnter path of code file with extension: ";
		cin >> path;
		cout << "\n";

		if (s.readFile(path, fileContent))
		{
			s.printFile(fileContent);

			//display
			cout << "\n\n< Token , Type >\n"; s.printLine(); cout << "\n";

			s.splitStr(fileContent);
		}

		else
		{
			cout << "File not found!\n";
			s.printLine();
			cout << "\n";
		}

		cout << "\nDo you want to enter another file (Y/N): ";
		cin >> again;
		cout << "\n";

	} while (again == 'Y' || again == 'y');

	system("pause");
	return 0;
}