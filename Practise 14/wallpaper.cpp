#include "wallpaper.h"
wallpaper exp1;

// ����� ������ �� �����

void print(wallpaper pr) {
	cout << "�����: " << pr.length << endl;
	cout << "������: " << pr.width << endl;
	cout << "���� �� �������: " << pr.picture << endl;
	cout << "��� �������: " << pr.canvas << endl;
	cout << "���� ������������: " << pr.date << endl;
	cout << "���� �������� (� �����): " << pr.expiration_date << endl;
	cout << "���������: " << pr.density << endl;
	cout << "���� �� �����: " << pr.cost << endl;
	cout << "___________________________________________________" << endl;
}

// ��������� ������ �� �����

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

// ����� ����������� ��������� � ����� ������ �� �����

void min_cost() {
	float min = 32000000;
	ifstream fin;
	cout << endl;
	fin.open(database, ios::in | ios::binary);
	if (!fin) {
		cout << "���� ������ �����" << endl;
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
			if (((exp1.density == "������" || exp1.density == "�����") && (exp1.width >= 50) && min > exp1.cost))
				min = exp1.cost;
		}
	}
	cout << endl;
	if (min != 32000000) {
		cout << "����������� ��������� �� ����� ����� ����� � ������� ������ �� ����� 50 �� ���������� " << min << " ���.\n";
	}
	else {
		cout << "����� ����� ����� � ������� ������ �� ����� 50 �� �� ��� ������.\n";
	}
	return;
}

// ���� ������

void input_data() {
	cin.ignore();
	cout << "������� ����� ������ (��): ";
	cin >> exp1.length;
	cout << "������� ������ ������ (��): ";
	cin >> exp1.width;
	cout << "���� �� ������� �� ����� (��/���): ";
	cin >> exp1.picture;
	cout << "������� ��� �������: ";
	cin >> exp1.canvas;
	cout << "������� ���� ������������ (��.��.����) : ";
	cin >> exp1.date;
	cout << "������� ���� �������� �������: ";
	cin >> exp1.expiration_date;
	cout << "������� ��������� ������� (�����/������): ";
	cin >> exp1.density;
	cout << "������� ��������� �� ����� (���,���): ";
	cin >> exp1.cost;
	ofstream fout;
	fout.open(database, ios::app | ios::binary);
	fout.seekp(0, ios::end);
	fout << exp1.length << " " << exp1.width << " " << exp1.picture << " " << exp1.canvas << " " << exp1.date << " " << exp1.expiration_date << " " << exp1.density << " " << exp1.cost << endl;
	fout.close();

}

// ����� ������ �� �����

void output_data() {
	ifstream fin;
	cout << endl;
	fin.open(database, ios::in | ios::binary);
	if (!fin) {
		cout << "���� ������ �����" << endl;
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

// ����� ������ � ������� txt

int table() {
	ifstream fin;
	ofstream fout;
	fout.open(txt_table, ios::out);
	fin.open(database, ios::binary);
	if (!fout) {
		return 2;
	}
	if (fin) {
		string title = "|   �����     |     ������   | ������� |     ��� �������       | ���� ������������ | ���� �������� |    ���������    |   ���� �� �����  |";
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
				fout << "|"; fout.width(13); fout << put[0]; // �����
				fout << "|"; fout.width(14); fout << put[1]; // ������

				// �������
				if (put[2] == "1") { 
					fout << "|"; fout.width(9); fout << "��"; 
				}	
				else {
					fout << "|"; fout.width(9); fout << "���";
				}
				fout << "|"; fout.width(23); fout << put[3]; // ��� �������
				fout << "|"; fout.width(19); fout << put[4]; // ���� ������������
				fout << "|"; fout.width(15); fout << put[5]; // ���� ��������
				fout << "|"; fout.width(17); fout << put[6]; // ���������
				fout << "|"; fout.width(18); fout << put[7]; // ���������
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

// ������� � CSV

int export_data() {
	ifstream fin;
	ofstream fout;
	fout.open(csv_table, ios::out);
	fin.open(database, ios::binary);
	string title = "�����;������;�������;��� �������;���� ������������;���� ��������;���������;���� �� �����";
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
				fout << put[0] << ";"; //�����
				fout << put[1] << ";"; // ������
				//�������
				if (put[2] == "1") {
					fout << "��" << ";";
				}
				else {
					fout << "���" << ";";
				}
				fout << put[3] << ";"; // ��� �������
				fout << put[4] << ";"; // ���� ������������
				fout << put[5] << ";"; // ���� ��������
				fout << put[6] << ";"; // ���������
				string price = "";
				for (int i = 0; i < put[7].size(); i++) {
					if (put[7][i] != '.') {
						price += put[7][i];
					}
					else {
						price += ',';
					}
				}
				fout << price << endl; // ���� �� �����
			}
		}
		fout.close();
		fin.close();
		return 0;
	}
	else return 1;
}

// �������� ������������� ������

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

// ����� ������

void show_root(wallpaperNode* node) {
	wallpaperNode* currNode = node;
	while (true) {
		cout << "����� ����� ���� : " << currNode << endl;
		cout << "����� ����������� ���� : " << currNode->prev << endl;
		cout << "����� ���������� ���� : " << currNode->next << endl << endl;
		print(currNode->Data);
		if (currNode->next == NULL) break;
		currNode = currNode->next;
	}
}

// ������� ������

void erase_root(wallpaperNode* node) {
	if (node->next != NULL)
		erase_root(node->next);
	if (node->prev != NULL)
	{
		node->prev->next = NULL;
		delete node;
	}
}