#include <iostream>
#include <string>

using namespace std;

void runProgram();
void displayMenu();
void info();
void add();
void search();

struct LAKE {
	string name = "-";
	string mountain = "-";
	string beginRiver = "-"; 
	string mainRiver = "-";
	int seaLevelHeight = 0;
	double area = 0;
	double volume = 0;
	double maxDepth = 0;
};

/*void defaultLakes(LAKE* lakes[]) {
	*lakes[0] = { "Urdino", "Rila", "Urdina", "Cherni Iskur", 2278, 2.53, 89.5, 6.6 };
	*lakes[1] = { "Alekovo", "Rila", "Bistrica", "Iskur", 2545, 2.39, 135.5, 14.5 };
	*lakes[2] = { "Marichino", "Rila", "Marica", "Marica", 2378, 2.15, 92.3, 10.8 };
	*lakes[3] = { "Ribno", "Rila", "Gorna Banenska", "Bqla Mesta", 2191, 2.87, 70, 4.5 };
	*lakes[4] = { "Murtvo", "Rila", "Gorna Banenska", "Bqla Mesta", 2292, 4.27, 274, 16.5 };
	*lakes[5] = { "Okoto", "Rila", "Jerman", "Struma", 2440, 6.8, 860, 37.5 };
	*lakes[6] = { "Bubreka", "Rila", "Jerman", "Struma", 2282, 8.5, 1170, 28 };
	*lakes[7] = { "Bliznaka", "Rila", "Jerman", "Struma", 1143, 9.1, 590, 27.5 };
	*lakes[8] = { "Gramatikovo", "Rila", "Jerman", "Struma", 2216, 2.6, 54, 6.5 };
	*lakes[9] = { "Sedmoto", "Rila", "Jerman", "Struma", 2095, 5.9, 240, 11 };
	*lakes[10] = { "Gorno Vasilashko", "Pirin", "Demqnica", "Glazne", 2154, 2.32, 28.7, 3.3 };
	*lakes[11] = { "Ribno Vasilashko", "Pirin", "Demqnica", "Glazne", 2126, 2.59, 41.6, 3.1 };
	*lakes[12] = { "Popovo", "Pirin", "Retije", "Mesta", 2234, 12.36, 270, 29.5 };
	*lakes[13] = { "Vlahinsko", "Pirin", "Vlahinska", "Struma", 2302, 6.34, 421.1, 13.4 };
	*lakes[14] = { "Chairsko", "Pirin", "Chairska", "Bashliica", 2416, 2.26, 47.3, 3.4 };
}*/

void info() {
	LAKE lakes[500];

	int choice;

	lakes[0] = { "Urdino", "Rila", "Urdina", "Cherni Iskur", 2278, 2.53, 89.5, 6.6 };
	lakes[1] = { "Marichino", "Rila", "Marica", "Marica", 2378, 2.15, 92.3, 10.8 };
	lakes[2] = { "Okoto", "Rila", "Jerman", "Struma", 2440, 6.8, 860, 37.5 };
	lakes[3] = { "Bubreka", "Rila", "Jerman", "Struma", 2282, 8.5, 1170, 28 };
	lakes[4] = { "Sedmoto", "Rila", "Jerman", "Struma", 2095, 5.9, 240, 11 };
	lakes[5] = { "Popovo", "Pirin", "Retije", "Mesta", 2234, 12.36, 270, 29.5 };

	for (int i = 0; i < 6; i++) {
		cout << " Lake: " << lakes[i].name << endl;
		cout << " Mountain: " << lakes[i].mountain << endl;
		cout << " Beginning river: " << lakes[i].beginRiver << endl;
		cout << " Valley: " << lakes[i].mainRiver << endl;
		cout << " Sea level hight: " << lakes[i].seaLevelHeight << endl;
		cout << " Area: " << lakes[i].area << endl;
		cout << " Volume: " << lakes[i].volume << endl;
		cout << " Maximal depth: " << lakes[i].maxDepth << endl << endl;
	}

	cout << endl << "Enter \"1\" to get back to the main menu: ";
	cin >> choice;

	if (choice == 1) runProgram();
}

void add() {
	int a;
	cout << "___add\n";
	cout << "type '0' to return bach to the menu\n";
	cin >> a;
	if (a == 0) {
		system("cls");
		runProgram();
	}
}

void search() {
	int a;
	cout << "___search\n";
	cout << "type '0' to return bach to the menu\n";
	cin >> a;
	if (a == 0) {
		system("cls");
		runProgram();
	}
}

void displayMenu() {

	cout << "  _______________________________________________________________________ \n";
	cout << " |                                                                       |\n";
	cout << " |      ///////////     ///////////         ///     ///     ///////////  |\n";
	cout << " |     ///     ///     ///     ///         ///     ///     ///     ///   |\n";
	cout << " |    ///////////     ///     ///         ///     ///     ///////////    |\n";
	cout << " |   ///     ///     ///     ///         ///     ///     ///     ///     |\n";
	cout << " |  ///     ///     ///////////////     ///////////     ///     ///      |\n";
	cout << " |                                                                       |\n";
	cout << " |                                                                       |\n";
	cout << " |                                                                       |\n";
	cout << " |                                1. INFO                                |\n";
	cout << " |                                2. ADD                                 |\n";
	cout << " |                                3. SEARCH                              |\n";
	cout << " |                                4. QUIT                                |\n";
	cout << " |                                                                       |\n";
	cout << " |                                                                       |\n";
	cout << " |_______________________________________________________________________|\n";
}

void runProgram() {
	LAKE lakes[500];
	int choice;
	system("cls");
	displayMenu();
	while (true) {
		cin >> choice;
		switch (choice) {
			case 1: {
				system("cls");
				info();
				break;
			}
			case 2: {
				system("cls");
				add();
				break;
			}
			case 3: {
				system("cls");
				search();
				break;
			}
			case 4: {
				return;
			}
			default: {
				cout << "Try again: ";
			}
		}
	}
}

int main() {
	runProgram();
}