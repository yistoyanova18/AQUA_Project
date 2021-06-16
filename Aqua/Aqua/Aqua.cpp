#include <iostream>
#include <string>

using namespace std;

void runProgram();
void displayMenu();
void info();
void add();
void search();

void info() {
	int a;
	cout << "___info\n";
	cout << "type '0' to return bach to the menu\n";
	cin >> a;
	if (a == 0) {
		system("cls");
		runProgram();
	}
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
	cout << " |                                                                       |\n";
	cout << " |                                                                       |\n";
	cout << " |_______________________________________________________________________|\n";
}

void runProgram() {
	int choice;
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
			default: {
				cout << "Try again: ";
			}
		}
	}
}

int main() {
	runProgram();
}