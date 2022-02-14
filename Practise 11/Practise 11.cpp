#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

string name_of_base;

struct wallpaper {
	char number[20];		//Складской номер
	int length;				//Длина рулона
	int width;				//Ширина рулона
	bool picture;			//Есть ли рисунок на обоях
	char canvas[30];		//Тип полотна
	char date[10];			//Дата изготовления
	int expiration_date;	//Срок годности
	char density[30];		//Плотность
	double cost;			//Цена за рулон
};

int min_cost() {
	int min = 32000000;
	ifstream fin;
	cout << endl;
	if (name_of_base == "") {
		cout << "Я не обнаружил на данный момент открытой базы, введите её имя: ";
		cin >> name_of_base;
		name_of_base += ".dat";
		cout << endl;
	}
	fin.open(name_of_base, ios::in | ios::binary);
	if (!fin) {
		cout << "Нет такой базы" << endl;
		system("timeout 5");
		name_of_base = "";
		return 0;
	}
	byte a=0;
	while (!fin.eof()) {
		const char p = ' ';
		string sm;
		string put[9];
		int trigger = 0;
		getline(fin, sm);
		if (sm != "") {
			for (int i = 0; i < sm.size(); i++) {
				if (sm[i] != p) {
					put[trigger] += sm[i];
				}
				else {
					trigger++;
				}
			}
			cout << "Обои с серийным номером: " << put[0] << endl;
			cout << "Длина: " << put[1] << endl;
			cout << "Ширина: " << put[2] << endl;
			cout << "Есть ли рисунок: ";
			if (put[3] == "1") {
				cout << "да";
			}
			else {
				cout << "нет";
			}
			cout << endl;
			cout << "Тип полотна: " << put[4] << endl;
			cout << "Дата изготовления: " << put[5] << endl;
			cout << "Срок годности (в годах): " << put[6] << endl;
			cout << "Плотность: " << put[7] << endl;
			cout << "Цена за рулон: " << put[8] << endl;
			cout << "___________________________________________________" << endl;
			if (((put[7] == "легкое" || put[7] == "лёгкое") and stoi(put[2]) >= 50) and min > stoi(put[8]))
				min = stoi(put[8]);
		}
	}
	cout << endl;
	if (min != 32000000) {
		cout << "Минимальная стоимость за рулон лёгких обоев с шириной рулона не менее 50 см составляет " << min << " руб.";
	}
	else {
		cout << "Рулон лёгких обоев с шириной рулона не менее 50 см не был найден.";
	}
	return 0;
}

double read_fl(const char mess[30]) {
	while (true) {
		cin.ignore();
		cout << mess;
		string num;
		cin >> num;
		try {
			double res = ::atof(num.c_str());
			cout << endl;
			return res;
		}
		catch (std::invalid_argument e) {
			cout << endl << "Вы ввели невереное значение" << endl;
		}
	}
}

bool read_b(const char mess[50]) {
	while (true) {
		cin.ignore();
		cout << mess;
		string in;
		cin >> in;
		if (in == "да" || in == "нет") {
			if (in == "да") {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			cout << endl << "Вы ввели неверное значение" << endl;
		}
	}
}

int read_i(const char mess[30]) {
	while (true) {
		cin.ignore();
		cout << mess;
		string in;
		cin >> in;
		try {
			int res = stoi(in);
			return res;
		}
		catch (std::invalid_argument e) {
			cout << endl << "Вы ввели неверное значение" << endl;
		}
	}
}

void write_fl() {
	bool c;
	c = true;
	wallpaper wr;
	cin.ignore();
	if (name_of_base == "") {
		cout << "На данный момент не открыта ни одна база, введите имя сущестующей или создайте новую: ";
		cin >> name_of_base;
		name_of_base += ".dat";
		cout << endl;
	}
	cout << "Введите складской номер: ";
	cin >> wr.number;
	wr.length = read_i("Введите длину рулона (см): ");
	wr.width = read_i("Введите ширину рулона (см): ");
	wr.picture = read_b("Есть ли рисунок на обоях (да/нет): ");
	cin.ignore();
	cout << "Введите тип полотна: ";
	cin >> wr.canvas;
	while (c) {
		cin.ignore();
		cout << "Введите дату изготовления (дд.мм.гггг) : ";
		string d;
		cin >> d;
		for (int i = 0; i < 10; i++) {
			if ((i != 2) && (i != 5)) {
				if (!(d[i] >= 0)) {
					cout << "Вы ввели неверное значение!";
					break;
				}
			}
		}
		string h;
		int dy, m;
		h = d[0];
		dy = atoi(h.c_str()) * 10;
		h = d[1];
		dy += atoi(h.c_str());
		h = d[3];
		m = atoi(h.c_str()) * 10;
		h = d[4];
		m += atoi(h.c_str());
		if ((dy <= 31) && (m <= 12)) {
			for (int i = 0; i < 10; i++) {
				wr.date[i] = d[i];
			}
			c = false;
		}
		else {
			cout << "Вы ввели неверное значение";
		}

		wr.expiration_date = read_i("Введите срок годности полотна (в годах): ");
		cout << "Введите плотность полотна (лёгкое/тяжёлое): ";
		cin >> wr.density;
		wr.cost = read_fl("Введите стоимость за рулон (руб): ");

		ofstream fout;
		fout.open(name_of_base, ios::app | ios::binary);
		fout.seekp(0, ios::end);
		fout << wr.number << " " << wr.length << " " << wr.width << " " << wr.picture << " " << wr.canvas << " ";
		for (int i = 0; i < 10; i++) {
			fout << wr.date[i];
		}
		fout << " " << wr.expiration_date << " " << wr.density << " " << wr.cost << endl;
		fout.close();
	}
}

void read_list() {
	ifstream fin;
	cout << endl;
	if (name_of_base == "") {
		cout << "Я не обнаружил на данный момент открытой базы, введите её имя: ";
		cin >> name_of_base;
		name_of_base += ".dat";
		cout << endl;
	}
	fin.open(name_of_base, ios::in | ios::binary);
	if (!fin) {
		cout << "Нет такой базы" << endl;
		name_of_base = "";
		return;
	}
	cout << "___________________________________________________" << endl;
	while (!fin.eof()) {
		const char p = ' ';
		string sm;
		string put[9];
		int trigger = 0;
		getline(fin, sm);
		if (sm != "") {
			for (int i = 0; i < sm.size(); i++) {
				if (sm[i] != p) {
					put[trigger] += sm[i];
				}
				else {
					trigger++;
				}
			}
			cout << "Обои с серийным номером: " << put[0] << endl;
			cout << "Длина: " << put[1] << endl;
			cout << "Ширина: " << put[2] << endl;
			cout << "Есть ли рисунок: ";
			if (put[3] == "1") {
				cout << "да";
			}
			else {
				cout << "нет";
			}
			cout << endl;
			cout << "Тип полотна: " << put[4] << endl;
			cout << "Дата изготовления: " << put[5] << endl;
			cout << "Срок годности (в годах): " << put[6] << endl;
			cout << "Плотность: " << put[7] << endl;
			cout << "Цена за рулон: " << put[8] << endl;
			cout << "___________________________________________________" << endl;
		}
	}
	fin.close();
}

int main()
{
	setlocale(LC_ALL, "Ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true) {
		int x;
		system("cls");
		cout << "1. Запись данных в файл " << endl << "2. Вывод данных из файла" << endl << "3. Найти минимальную стоимость лёгкого рулона с шириной от 50 см" << endl << "4. Выйти из программы" << endl << "------------------> ";
		cin >> x;
		switch (x) {
		case 1:
			write_fl();
			break;
		case 2:
			read_list();
			system("pause");
			break;
		case 3:
			min_cost();
			system("pause");
			break;
		case 4:
			return 0;
			break;
		default:
			cout << endl << "Вы ввели неверное значение." << endl;
			system("timeout 5");
		}
	}
}