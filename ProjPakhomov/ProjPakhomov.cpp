#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <stdlib.h>

using namespace std;

template <typename T>
void read(T& value, string comment = "Введите значение", float min = 0, float max = -1)
{
	cout << comment << ": ";
	cin >> value;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float))
	{
		while (!cin || value < min || (value > max && max >= min))
		{
			cout << comment << ": ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> value;
		}
	}

	if (typeid(T) == typeid(bool))
	{
		while (!cin)
		{
			cout << comment << ": ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> value;
		} 
	}
}

void read(string& value, string comment = "Введите значение")
{
	cout << comment << ": ";
	cin >> ws;
	getline(cin, value);
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
	cout << "8. Очистить\n";
	cout << "0. Выход\n";
}

struct tube
{
	int length, diameter;
	bool isWorking;
};

struct station
{
	string name;
	int workshops, workshopsUsed;
	float efficiency;
};

void printStats(tube object)
{
	cout << "Добавлена труба.\n";
	cout << "Длина: " << object.length << "\n";
	cout << "Диаметр: " << object.diameter << "\n";
	cout << "Статус: " << (object.isWorking ? "В ремонте\n" : "В работе\n");
}

void printStats(station object)
{
	cout << "Добавлена станция \"" << object.name << "\"\n";
	cout << "Цехов: " << object.workshops << "\n";
	cout << "Из них в работе: " << object.workshopsUsed << "\n";
	cout << "Эффективность: " << object.efficiency << "\n";
}

void save(bool tubeAdded, bool stationAdded, tube sTube, station sStation)
{
	ofstream file;
	file.open("save.txt");
	if (file)
	{
		file << tubeAdded << endl;
		file << stationAdded << endl;

		if (tubeAdded)
		{
			file << sTube.length << endl;
			file << sTube.diameter << endl;
			file << sTube.isWorking << endl;
		}

		if (stationAdded)
		{
			file << sStation.name << endl;
			file << sStation.workshops << endl;
			file << sStation.workshopsUsed << endl;
			file << sStation.efficiency << endl;
		}
	}

	file.close();
}

void load(bool& tubeAdded, bool& stationAdded, tube& sTube, station& sStation)
{
	ifstream file;
	file.open("save.txt");
	if (file)
	{
		file >> tubeAdded;
		file >> stationAdded;

		if (tubeAdded)
		{
			file >> sTube.length;
			file >> sTube.diameter;
			file >> sTube.isWorking;
		}

		if (stationAdded)
		{
			file >> ws;
			getline(file, sStation.name);
			file >> sStation.workshops;
			file >> sStation.workshopsUsed;
			file >> sStation.efficiency;
		}
	}

	file.close();
}

int main()
{
	setlocale(LC_ALL, "Ru");
	
	bool isRunning = true; // States if program is supposed to run

	bool tubeAdded = false, stationAdded = false;
	int command;

	tube mainTube{ 0, 0, 0 };
	station mainStation{ "Untitled", 0, 0, 0 };

	while (isRunning)
	{

		printMenuOptions();

		read<int>(command, "Введите команду", 0, 8);

		system("CLS"); //  Clear screen

		switch (command)					//  Run the command got from user
		{
		case 0:								//  End programm
			isRunning = false;
			break;
		case 1:								//  Create tube
			if (!tubeAdded)
			{
				tubeAdded = true;
				read<int>(mainTube.length, "Введите длину трубы", 1);
				read<int>(mainTube.diameter, "Введите диаметр трубы", 1);
				read<bool>(mainTube.isWorking, "Введите статус трубы (1 - Работает, 0 - не работает)");
			}
			break;
		case 4:								//  Edit tube
			if (tubeAdded)
				read<bool>(mainTube.isWorking, "Введите статус трубы (1 - Работает, 0 - не работает)");
			break;
		case 2:								//  Create station
			if (!stationAdded)
			{
				stationAdded = true;
				read(mainStation.name, "Введите название станции");
				read<int>(mainStation.workshops, "Введите число цехов", 1);
				read<int>(mainStation.workshopsUsed, "Введите число активных цехов (Не более " + to_string(mainStation.workshops) + ")", 1, mainStation.workshops);
				read<float>(mainStation.efficiency, "Введите эффективность станции (От 0 до 1)", 0, 1);
			}
			break;
		case 5:								//  Edit station
			if (stationAdded)
				read<int>(mainStation.workshopsUsed, "Введите число активных цехов (Не более " + to_string(mainStation.workshops) + ")", 1, mainStation.workshops);
			break;
		case 3:								//  Check if there is tube/station to print info about
			if (tubeAdded)
				printStats(mainTube);
			if (stationAdded)
				printStats(mainStation);
			if (!(tubeAdded || stationAdded))
				cout << "Ни станции, ни трубы не добавлено.\n";
			break;
		case 6:								//  Save
			save(tubeAdded, stationAdded, mainTube, mainStation);
			break;
		case 7:								//  Load
			load(tubeAdded, stationAdded, mainTube, mainStation);
			break;
		case 8:								//  Clear
			tubeAdded = false;
			stationAdded = false;
			break;

		}
		cout << endl;
	}

}