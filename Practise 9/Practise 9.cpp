#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void wrf(const char mess[50], float x, float y, float r) {
	ofstream outf;
	outf.open("out.txt", ios::app);
	outf << "Для точки (" << x << "; " << y << ") и радиуса окружности " << r << ": " << mess << endl;
	cout << "Для точки (" << x << "; " << y << ") и радиуса окружности " << r << ": " << mess << endl;
	outf.close();
}

int main() {

	setlocale(LC_ALL, "RU");

	// TODO: Ввод из файла

	ifstream inf;
	inf.open("in.txt", ios::binary);
	if (!inf) {
		cout << "Файл не найден!" << endl;
	}
	else {
		char buf[50];
		float x, y, r;
		inf.seekg(0, ios_base::beg);
		while (!inf.eof()) {
			inf >> x >> y >> r;
			if (r <= 0) {
				wrf("Радиус не может быть отрицательным или быть равным нулю.", x, y, r);
			}
			else {
				// Проверка на попадание в первый отрезок

				if ((x <= 0 && x >= -2 * r) and (y <= 2 * r && y >= 0) and (x != 0 && y != 0)) {
					if (round(pow(r, 2) * 100) / 100 >= ((round(pow((x + r), 2) * 100) / 100) + (round(pow((y - r), 2) * 100) / 100))) {
						wrf("Точка принадлежит первому графику", x, y, r);
					}
					else {
						wrf("Точка не принадлежит первому графику", x, y, r);
					}
				}

				// Проверка на попадание во второй отрезок

				else if ((x >= 0 && x <= 2 * r) && (y <= 0 && y >= -r)) {
					wrf("Точка принадлежит второму графику", x, y, r);
				}

				// Исключение для обоих случаев, не принадлежит

				else {
					wrf("Точка не принадлежит ни одному графику.", x, y, r);
				}
			}
		}
		inf.close();
	}
	system("pause");
	return 0;
}