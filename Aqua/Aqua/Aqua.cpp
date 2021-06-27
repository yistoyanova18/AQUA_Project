#include <iostream>
#include <string>
#include <nanodbc.h>
#include <exception>
#include <vector>

using namespace std;

void runProgram(nanodbc::connection conn);
//void displayMenu();
//vector<LAKE> getAllLakes(nanodbc::connection conn);
//void add();
//void search();

struct LAKE {
	int id = 0;
	string name = "-";
	string mountain = "-";
	string beginRiver = "-"; 
	string mainRiver = "-";
	int seaLevelHeight = 0;
	double area = 0;
	double volume = 0;
	double maxDepth = 0;
};

void getBackToMenu(nanodbc::connection conn)
{

	int choice;
	cout << "type '0' to return bach to the menu\n";
	enter:
	cin >> choice;
	if (choice == 0) {
		system("cls");
		runProgram(conn);
	}
	else
	{
		cout << "Invalid entered value! Plase enter again: ";
		goto enter;
	}

}

vector<LAKE> getLakes(nanodbc::connection conn) {

	vector<LAKE> lakes;

	nanodbc::statement statement(conn); //zashto statemnt can't be prepared???
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM AQUA_Lakes.Lakes
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		LAKE lake;
		lake.id = result.get<int>("Id");
		lake.name = result.get<nanodbc::string>("LakeName", "");
		lake.mountain = result.get<nanodbc::string>("Mountain", "");
		lake.beginRiver = result.get<nanodbc::string>("BeginRiver", "");
		lake.mainRiver = result.get<nanodbc::string>("Valley", "");
		lake.seaLevelHeight = result.get<int>("Altitude");
		lake.area = result.get<float>("Area");
		lake.volume = result.get<float>("Volume");
		lake.maxDepth = result.get<float>("MaxDepth");

		lakes.push_back(lake);
	}

	return lakes;
}

void getAllLakes(nanodbc::connection conn)
{
	vector<LAKE> lakes = getLakes(conn);
	for (size_t i = 0; i < lakes.size(); i++)
	{
		cout << lakes[i].id << " ";
		cout << lakes[i].name << " ";
		cout << lakes[i].mountain << " ";
		cout << lakes[i].beginRiver << " ";
		cout << lakes[i].mainRiver << " ";
		cout << lakes[i].seaLevelHeight << " ";
		cout << lakes[i].area << " ";
		cout << lakes[i].volume << " ";
		cout << lakes[i].maxDepth << endl;
	}

	getBackToMenu(conn);
}

string enterText()
{
	string text;
	getline(cin, text);
	return text;
}

int enterInt()
{
	int num;
	cin >> num;
	return num;
}

double enterDouble()
{
	double num;
	cin >> num;
	return num;
}

void insert(nanodbc::connection conn)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            AQUA_Lakes.Lakes
            (LakeName, Mountain, BeginRiver, Valley, Altitude, Area, Volume, MaxDepth)
            VALUES
            (?, ?, ?, ?, ?, ?, ?, ?)
    )"));

	cout << "Enter the lake's name: ";
	const string lakeName = enterText();
	statement.bind(0, &lakeName);

	cout << "Enter the mountain's name: ";
	const string mountainName = enterText();
	statement.bind(1, &mountainName);

	cout << "Enter the lake's starting point: ";
	const string beginRiver = enterText();
	statement.bind(2, &beginRiver);

	cout << "Enter the lake's valley: ";
	const string mainRiver = enterText();
	statement.bind(3, &mainRiver);

	cout << "Enter the lake's altitude: ";
	const int seaLevelHeight = enterInt();
	statement.bind(4, &seaLevelHeight);

	cout << "Enter the lake's area: ";
	double area = enterDouble();
	statement.bind(5, &area);

	cout << "Enter the lake's volume: ";
	double volume = enterDouble();
	statement.bind(6, &volume);

	cout << "Enter the lake's deepest point: ";
	double maxDepth = enterDouble();
	statement.bind(7, &maxDepth);

	execute(statement);
}

void insertLake(nanodbc::connection conn) { //kakvo da pravim za da ne vuvejdame id

	insert(conn);

	getBackToMenu(conn);

}

LAKE getLakeById(nanodbc::connection conn)
{
	LAKE lake;

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        SELECT *
            FROM AQUA_Lakes.Lakes
            WHERE Id = ?
    )"));

	int id = enterInt();
	
	statement.bind(0, &id);

	auto result = execute(statement);

	if (result.next())
	{
		LAKE lake;
		lake.id = result.get<int>("Id");
		lake.name = result.get<nanodbc::string>("LakeName", "");
		lake.mountain = result.get<nanodbc::string>("Mountain", "");
		lake.beginRiver = result.get<nanodbc::string>("BeginRiver", "");
		lake.mainRiver = result.get<nanodbc::string>("Valley", "");
		lake.seaLevelHeight = result.get<int>("Altitude");
		lake.area = result.get<float>("Area");
		lake.volume = result.get<float>("Volume");
		lake.maxDepth = result.get<float>("MaxDepth");

	}

	return lake;
}

LAKE getLakeByName(nanodbc::connection conn)
{
	LAKE lake;

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        SELECT *
            FROM AQUA_Lakes.Lakes
            WHERE LakeName = ?
    )"));

	string lakeName = enterText();

	statement.bind(1, &lakeName);

	auto result = execute(statement);

	if (result.next())
	{
		LAKE lake;
		lake.id = result.get<int>("Id");
		lake.name = result.get<nanodbc::string>("LakeName", "");
		lake.mountain = result.get<nanodbc::string>("Mountain", "");
		lake.beginRiver = result.get<nanodbc::string>("BeginRiver", "");
		lake.mainRiver = result.get<nanodbc::string>("Valley", "");
		lake.seaLevelHeight = result.get<int>("Altitude");
		lake.area = result.get<float>("Area");
		lake.volume = result.get<float>("Volume");
		lake.maxDepth = result.get<float>("MaxDepth");

	}

	return lake;
}

void search(nanodbc::connection conn) 
{
	short int choice;

	cout << "SEARCH BY" << endl;
	cout << "1. Id" << endl;
	cout << "2. Name" << endl;
	enter:
	cout << endl << "enter the option's number: ";
	cin >> choice;
	switch (choice)
	{
	case 1: getLakeById(conn);
		break;
	case 2: getLakeByName(conn);
		break;
	default: cout << "Incorrect value entered! Please enter again: "; goto enter;
	}
	getBackToMenu(conn);
}

void deleteLakeByName(nanodbc::connection conn)
{
	cout << "enter the name of the lake you want to delete: ";
	string lakeName = enterText();

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        DELETE 
            FROM AQUA_Lakes.Lakes
            WHERE LakeName = ?
    )"));

	statement.bind(1, &lakeName);

	auto result = execute(statement);

}

void deleteLakeById(nanodbc::connection conn)
{
	cout << "enter the id of the lake you want to delete: ";
	int id  = enterInt();

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        DELETE 
            FROM AQUA_Lakes.Lakes
            WHERE Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);

}

void deleteLake(nanodbc::connection conn)
{

	short int choice;

	cout << "DELETE BY" << endl;
	cout << "1. Id" << endl;
	cout << "2. Name" << endl;
enter:
	cout << endl << "enter the option's number: ";
	cin >> choice;
	switch (choice)
	{
	case 1: deleteLakeById(conn);
		break;
	case 2: deleteLakeByName(conn);
		break;
	default: cout << "Incorrect value entered! Please enter again: "; goto enter;
	}

	getBackToMenu(conn);
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

void runProgram(nanodbc::connection conn) {
	int choice;
	system("cls");
	displayMenu();
	while (true) {
		cin >> choice;
		switch (choice) {
			case 1: {
				system("cls");
				getAllLakes(conn);
				break;
			}
			case 2: {
				system("cls");
				insertLake(conn);
				break;
			}
			case 3: {
				system("cls");
				search(conn);
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

int main() 
{
	
	try
	{
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=DESKTOP-VSMRK4C\\SQLExpress;DATABASE=AQUA_Lakes;Trusted_Connection=yes;"); // an ODBC connection string to your database

		nanodbc::connection conn(connstr);
		
		runProgram(conn);

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
