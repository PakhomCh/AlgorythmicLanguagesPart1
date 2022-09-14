#include <iostream>
#include <string>
#include <locale>

using namespace std;

void clc()
{
	for (int i = 0; i < 100; i++)
		cout << "\n";
}

struct tube
{

	int length, diameter;
	bool onRepair;

};

struct station
{

	string name;
	int workshops, workshopsUsed;
	float efficiency;

};

tube newTube(int length = 1, int diameter = 1)
{

	tube t;
	t.length = length;
	t.diameter = diameter;
	t.onRepair = false;

	return t;

}

station newStation(string name, int workshops = 1, int workshopsused = 0, float efficiency = 1.0)
{

	station s;
	s.name = name;
	s.workshops = workshops;
	s.workshopsUsed = workshopsused;
	s.efficiency = efficiency;

	return s;

}

void printMenuOptions()
{

	cout << "1. Добавить трубу\n";
	cout << "2. Добавить КС\n";
	cout << "3. Просмотр всех объектов\n";
	cout << "4. Редактировать трубу\n";
	cout << "5. Редактировать КС\n";
	cout << "6. Сохранить\n";
	cout << "7. Загрузить\n";
	cout << "8. Отчистить\n";
	cout << "0. Выход\n";

}

void printStats(tube object)
{

	cout << "Добавлена труба.\n";
	cout << "Длина: " << object.length << "\n";
	cout << "Диаметр: " << object.diameter << "\n";
	cout << "Статус: " << (object.onRepair ? "В ремонте\n\n" : "В работе\n\n");

}

void printStats(station object)
{

	cout << "Добавлена станция \"" << object.name << "\"\n";
	cout << "Цехов: " << object.workshops << "\n";
	cout << "Из них в работе: " << object.workshopsUsed << "\n";
	cout << "КПД: " << object.efficiency << "\n\n";

}

tube editTube(tube object)
{

	tube replacement;
	int length, diameter, status;

	cout << "Введите новый диаметр или 0, чтобы сохранить текущий: ";
	
	cin >> diameter;
	while (!cin || diameter < 0)
	{
		cout << " ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> diameter;
	}

	if (diameter > 0)
		replacement.diameter = diameter;
	else
		replacement.diameter = object.diameter;

	cout << "Введите новую длину или 0, чтобы сохранить текущую: ";

	cin >> length;
	while (!cin || length < 0)
	{
		cout << " ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> length;
	}

	if (length > 0)
		replacement.length = length;
	else
		replacement.length = object.length;

	cout << "Введите статус трубы (1 - Работает, 0 - В ремонте): ";

	cin >> status;
	while (!cin || (status != 0 && status != 1))
	{
		cout << " ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> status;
	}

	if (status == 0)
		replacement.onRepair = true;
	else
		replacement.onRepair = false;

	cout << "\n\n";

	return replacement;

}

station editStation(station object)
{

	station replacement;
	string name;
	int workshops, wsused;
	float efficiency;

	cout << "Введите новое название или 0, чтобы сохранить текущее: ";

	cin >> name;
	while (!cin)
	{
		cout << " ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> name;
	}

	if (name != "0")
		replacement.name = name;
	else
		replacement.name = object.name;

	cout << "Введите новое число цехов или 0, чтобы сохранить текущее: ";

	cin >> workshops;
	while (!cin || workshops < 0)
	{
		cout << " ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> workshops;
	}

	if (workshops > 0)
		replacement.workshops = workshops;
	else
		replacement.workshops = object.workshops;

	cout << "Введите число используемых цехов (не более " << replacement.workshops << "): ";

	cin >> wsused;
	while (!cin || wsused < 0)
	{
		cout << " ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> wsused;
	}

	replacement.workshopsUsed = wsused;
	
	cout << "Введите эффективность КС (От 0 до 1): ";

	cin >> efficiency;
	while (!cin || efficiency < 0 || efficiency > 1)
	{
		cout << " ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> efficiency;
	}

	replacement.efficiency = efficiency;

	cout << "\n\n";

	return replacement;

}

int main()
{

	setlocale(LC_ALL, "Ru");

	bool isRunning = true; // States if program is supposed to run

	bool tubeAdded = false, stationAdded = false;
	int command;

	tube mainTube;
	station mainStation;

	while (isRunning)
	{
		printMenuOptions();

		cout << "\nВведите команду: ";
		cin >> command;
		while (!cin)
		{
			cout << "\nВведите команду: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> command;
		}

		clc(); //  Clear screen;

		switch (command)					//  Run the command got from user
		{
		case 0:								//  End programm
			isRunning = false;
			break;
		case 1:								//  Create tube
			tubeAdded = true;
			mainTube = newTube();
		case 4:								//  Edit tube
			mainTube = editTube(mainTube);
			break;
		case 2:								//  Create station
			stationAdded = true;
			mainStation = newStation("Untitled");
		case 5:								//  Edit station
			mainStation = editStation(mainStation);
			break;
		case 3:								//  Check if there is tube/station to print info about
			if (tubeAdded)
				printStats(mainTube);
			if (stationAdded)
				printStats(mainStation);
			if (!(tubeAdded || stationAdded))
				cout << "Ни станции, ни трубы не добавлено.\n\n";
			break;
		case 6:								//  TODO: Save
			break;
		case 7:								//  TODO: Load
			break;
		case 8:								//  TODO: Clear
			tubeAdded = false;
			stationAdded = false;
			break;

		}

	}

}