#include "wallpaper.h"
wallpaper exp1;

// Вывод данных на экран

void print(wallpaper pr) {
	cout << "Длина: " << pr.length << endl;
	cout << "Ширина: " << pr.width << endl;
	cout << "Есть ли рисунок: " << pr.picture << endl;
	cout << "Тип полотна: " << pr.canvas << endl;
	cout << "Дата изготовления: " << pr.date << endl;
	cout << "Срок годности (в годах): " << pr.expiration_date << endl;
	cout << "Плотность: " << pr.density << endl;
	cout << "Цена за рулон: " << pr.cost << endl;
	cout << "___________________________________________________" << endl;
}

// Получение данных из файла

wallpaper line(string sm) {
	wallpaper ret;
	const char p = ' ';
	string put[8];
	int trigger = 0;
	for (int i = 0; i < sm.size(); i++) {
		if (sm[i] != p) {
			put[trigger] += sm[i];
		}
		else {
			trigger++;
		}
	}
	ret.length = stoi(put[0]);
	ret.width = stoi(put[1]);
	ret.picture = put[2];
	ret.canvas = put[3];
	ret.date = put[4];
	ret.expiration_date = stoi(put[5]);
	ret.density = put[6];
	ret.cost = stof(put[7]);
	return ret;
}

// Поиск минимальной стоимости и вывод данных на экран

void min_cost() {
	float min = 32000000;
	ifstream fin;
	cout << endl;
	fin.open(database, ios::in | ios::binary);
	if (!fin) {
		cout << "База данных пуста" << endl;
		system("timeout 5");
		return;
	}
	byte a = 0;
	while (!fin.eof()) {
		string ln = "";
		getline(fin, ln);
		if (ln != "") {
			exp1 = line(ln);
			print(exp1);
			if (((exp1.density == "легкое" || exp1.density == "лёгкое") && (exp1.width >= 50) && min > exp1.cost))
				min = exp1.cost;
		}
	}
	cout << endl;
	if (min != 32000000) {
		cout << "Минимальная стоимость за рулон лёгких обоев с шириной рулона не менее 50 см составляет " << min << " руб.\n";
	}
	else {
		cout << "Рулон лёгких обоев с шириной рулона не менее 50 см не был найден.\n";
	}
	return;
}

// Ввод данных

void input_data() {
	cin.ignore();
	cout << "Введите длину рулона (см): ";
	cin >> exp1.length;
	cout << "Введите ширину рулона (см): ";
	cin >> exp1.width;
	cout << "Есть ли рисунок на обоях (да/нет): ";
	cin >> exp1.picture;
	cout << "Введите тип полотна: ";
	cin >> exp1.canvas;
	cout << "Введите дату изготовления (дд.мм.гггг) : ";
	cin >> exp1.date;
	cout << "Введите срок годности полотна: ";
	cin >> exp1.expiration_date;
	cout << "Введите плотность полотна (лёгкое/тяжёлое): ";
	cin >> exp1.density;
	cout << "Введите стоимость за рулон (руб,коп): ";
	cin >> exp1.cost;
	ofstream fout;
	fout.open(database, ios::app | ios::binary);
	fout.seekp(0, ios::end);
	fout << exp1.length << " " << exp1.width << " " << exp1.picture << " " << exp1.canvas << " " << exp1.date << " " << exp1.expiration_date << " " << exp1.density << " " << exp1.cost << endl;
	fout.close();

}

// Вывод данных на экран

void output_data() {
	ifstream fin;
	cout << endl;
	fin.open(database, ios::in | ios::binary);
	if (!fin) {
		cout << "База данных пуста" << endl;
		return;
	}
	while (!fin.eof()) {
		string ln;
		getline(fin, ln);
		if (ln != "") {
			exp1 = line(ln);
			print(exp1);
		}
	}
	fin.close();
}

// Вывод данных в таблицу txt

int table() {
	ifstream fin;
	ofstream fout;
	fout.open(txt_table, ios::out);
	fin.open(database, ios::binary);
	if (!fout) {
		return 2;
	}
	if (fin) {
		string title = "|   Длина     |     Ширина   | Рисунок |     Тип полотна       | Дата изготовления | Срок годности |    Плотность    |   Цена за рулон  |";
		string delim = "+------------ + ------------ + ------- + --------------------- + ----------------- + ------------- + --------------- + -----------------+";
		fout.setf(ios::fixed);
		fout.precision(2);
		fout << delim << endl;
		fout << title << endl;
		fout << delim << endl;
		while (!fin.eof()) {
			const char p = ' ';
			string sm;
			string put[8];
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
				fout.setf(ios::right);
				fout << "|"; fout.width(13); fout << put[0]; // Длина
				fout << "|"; fout.width(14); fout << put[1]; // Ширина

				// Рисунок
				if (put[2] == "1") { 
					fout << "|"; fout.width(9); fout << "Да"; 
				}	
				else {
					fout << "|"; fout.width(9); fout << "Нет";
				}
				fout << "|"; fout.width(23); fout << put[3]; // Тип полотна
				fout << "|"; fout.width(19); fout << put[4]; // Дата изготовления
				fout << "|"; fout.width(15); fout << put[5]; // Срок годности
				fout << "|"; fout.width(17); fout << put[6]; // Плотность
				fout << "|"; fout.width(18); fout << put[7]; // Стоимость
				fout << "|" << endl;
			}
		}
		fout << delim << endl;
		fout.close();
		fin.close();
		return 0;
	}
	else return 1;
}

// Экспорт в CSV

int export_data() {
	ifstream fin;
	ofstream fout;
	fout.open(csv_table, ios::out);
	fin.open(database, ios::binary);
	string title = "Длина;Ширина;Рисунок;Тип полотна;Дата изготовления;Срок годности;Плотность;Цена за рулон";
	fout << title << endl;
	if (!fout) {
		return 2;
	}
	if (fin) {
		while (!fin.eof()) {
			const char p = ' ';
			string sm;
			string put[8];
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
				fout << put[0] << ";"; //Длина
				fout << put[1] << ";"; // Ширина
				//Рисунок
				if (put[2] == "1") {
					fout << "Да" << ";";
				}
				else {
					fout << "Нет" << ";";
				}
				fout << put[3] << ";"; // Тип полотна
				fout << put[4] << ";"; // Дата изготовления
				fout << put[5] << ";"; // Срок годности
				fout << put[6] << ";"; // Плотность
				string price = "";
				for (int i = 0; i < put[7].size(); i++) {
					if (put[7][i] != '.') {
						price += put[7][i];
					}
					else {
						price += ',';
					}
				}
				fout << price << endl; // Цена за рулон
			}
		}
		fout.close();
		fin.close();
		return 0;
	}
	else return 1;
}

// Создание динамического списка

void create_root(wallpaperNode* node) {
	ifstream fin;
	fin.open(database, ios::binary);
	if (fin) {
		wallpaperNode* currNode = new wallpaperNode;
		currNode = node;
		while (!fin.eof()) {
			string ln;
			getline(fin, ln);
			if (ln != "") {
				exp1 = line(ln);
				currNode->Data = exp1;
				currNode->next = new wallpaperNode;
				currNode->next->prev = currNode;
				currNode = currNode->next;
			}
		}
		currNode->prev->next = NULL;
		delete currNode;
		fin.close();
	}
}

// Вывод списка

void show_root(wallpaperNode* node) {
	wallpaperNode* currNode = node;
	while (true) {
		cout << "Адрес этого узла : " << currNode << endl;
		cout << "Адрес предыдущего узла : " << currNode->prev << endl;
		cout << "Адрес следующего узла : " << currNode->next << endl << endl;
		print(currNode->Data);
		if (currNode->next == NULL) break;
		currNode = currNode->next;
	}
}

// Очистка списка

void erase_root(wallpaperNode* node) {
	if (node->next != NULL)
		erase_root(node->next);
	if (node->prev != NULL)
	{
		node->prev->next = NULL;
		delete node;
	}
}