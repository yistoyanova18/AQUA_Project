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

	void display()
	{
		cout << this->id << " ";
		cout << this->name << " ";
		cout << this->mountain << " ";
		cout << this->beginRiver << " ";
		cout << this->mainRiver << " ";
		cout << this->seaLevelHeight << " ";
		cout << this->area << " ";
		cout << this->volume << " ";
		cout << this->maxDepth << endl;
	}
};

void getBackToMenu(nanodbc::connection conn)
{

	int choice;
	cout << "type '0' to return bach to the menu\n";
enter:
	cin >> choice;
	if (choice == 0) {
		//system("cls");
		//runProgram(conn);
	}
	else
	{
		cout << "Invalid entered value! Plase enter again: ";
		goto enter;
	}

}

vector<LAKE> getLakes(nanodbc::connection conn) {

	vector<LAKE> lakes;

	nanodbc::statement statement(conn); 
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM AQUA_Lakes.dbo.Lakes
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
		lakes[i].display();
	}

	getBackToMenu(conn);
}

string enterText()
{
	cin.ignore(1, '\n');
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
            AQUA_Lakes.dbo.Lakes
            (LakeName, Mountain, BeginRiver, Valley, Altitude, Area, Volume, MaxDepth)
            VALUES
            (?, ?, ?, ?, ?, ?, ?, ?)
    )"));

	cout << "Enter the lake's name: ";
	const string lakeName = enterText();
	statement.bind(0, lakeName.c_str());

	cout << "Enter the mountain's name: ";
	const string mountainName = enterText();
	statement.bind(1, mountainName.c_str());

	cout << "Enter the lake's starting point: ";
	const string beginRiver = enterText();
	statement.bind(2, beginRiver.c_str());

	cout << "Enter the lake's valley: ";
	const string mainRiver = enterText();
	statement.bind(3, mainRiver.c_str());



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

void insertLake(nanodbc::connection conn) { 

	insert(conn);

	getBackToMenu(conn);
}

LAKE getLakeById(nanodbc::connection conn, const int& lakeId)
{
	LAKE lake;

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        SELECT *
            FROM AQUA_Lakes.dbo.Lakes
            WHERE Id = ?
    )"));

	statement.bind(0, &lakeId);

	auto result = execute(statement);

	if (result.next())
	{
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

LAKE getLakeByName(nanodbc::connection conn, const string& lakeName)
{
	LAKE lake;

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        SELECT *
            FROM AQUA_Lakes.dbo.Lakes
            WHERE LakeName = ?
    )"));

	statement.bind(0, lakeName.c_str());

	auto result = execute(statement);

	if (result.next())
	{
		lake.id = result.get<int>("Id");
		lake.name = result.get<nanodbc::string>("LakeName", "");
		lake.mountain = result.get<nanodbc::string>("Mountain", "");
		lake.beginRiver = result.get<nanodbc::string>("BeginRiver", "");
		lake.mainRiver = result.get<nanodbc::string>("Valley", "");
		lake.seaLevelHeight = result.get<int>("Altitude");
		lake.area = result.get<double>("Area");
		lake.volume = result.get<double>("Volume");
		lake.maxDepth = result.get<double>("MaxDepth");

	}

	return lake;
}

void search(nanodbc::connection conn)
{
	short int choice;
	LAKE lake;
	int lakeId;
	string lakeName;

	do {
		cout << "SEARCH BY" << endl;
		cout << "1. Id" << endl;
		cout << "2. Name" << endl;
		cout << "3. Exit" << endl;
		cout << endl << "enter the option's number: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter lake id: ";
			lakeId = enterInt();
			lake = getLakeById(conn, lakeId);
			if (lake.id != 0) {
				lake.display();
			}
			else {
				cout << "The lake with id " << lakeId << " was not found!" << endl;
			}
			break;
		case 2:
			cout << "Enter lake's name: ";
			lakeName = enterText();
			lake = getLakeByName(conn, lakeName);
			if (lake.id != 0) {
				lake.display();
			}
			else {
				cout << "The lake with name " << lakeName << " was not found!" << endl;
			}
			break;
		case 3: break;
		default: cout << "Incorrect value entered! Please enter again: " << endl;
		}
	} while (choice != 3);

	system("cls");
	runProgram(conn);
}

bool deleteLakeByName(nanodbc::connection conn, const string& lakeName)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        DELETE 
            FROM AQUA_Lakes.dbo.Lakes
            WHERE LakeName = ?
    )"));

	statement.bind(1, lakeName.c_str());

	auto result = execute(statement);

	return result.affected_rows() != 0;
}

bool deleteLakeById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        DELETE 
            FROM AQUA_Lakes.dbo.Lakes
            WHERE Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);

	return result.affected_rows() != 0;

}

void deleteLake(nanodbc::connection conn)
{
	short int choice;
	bool queryResult = false;
	int id;
	string lakeName;


	do {
		cout << "DELETE BY" << endl;
		cout << "1. Id" << endl;
		cout << "2. Name" << endl;
		cout << "3. Exit" << endl;
		cout << endl << "enter the option's number: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter the id of the lake you want to delete: ";
			id = enterInt();
			queryResult = deleteLakeById(conn, id);

			if (queryResult)
			{
				cout << "The lake with id " << id << " was deleted successfully!" << endl;
			}
			else {
				cout << "The lake with id " << id << " was not found!" << endl;
			}
			break;
		case 2: 
			cout << "Enter the name of the lake you want to delete: ";
			lakeName = enterText();
			deleteLakeByName(conn, lakeName);
			if (queryResult)
			{
				cout << "The lake with name " << lakeName << " was deleted successfully!" << endl;
			}
			else {
				cout << "The lake with name " << lakeName << " was not found!" << endl;
			}

			break;
		case 3: break;
		default: cout << "Incorrect value entered! Please enter again: ";
		}

	} while (choice != 3);
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

	while (true) {
		system("cls");
		displayMenu();
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

		//cout << deleteLakeById(conn, 6);

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
