#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	char points[2];
	float x[2], y[2], lines[2], pol_per, height, katets[1];
	points[0] = 'A';
	points[1] = 'B';
	points[2] = 'C';
	bool is_real;
	is_real = false;

	// Ввод данных о вершинах треугольника 
	
	for (int i = 0; i < 3; i++) {
		cout << "Введите x точки " << points[i] << ' ';
		cin >> x[i];
		cout << "Введите y точки " << points[i] << ' ';
		cin >> y[i];
	}

	// Вычисление длин сторон
	
	// Вычисление стороны AB
	
	if (y[0] != y[1]) {
		if (x[0] != x[1]) {
			katets[0] = abs(x[0] - x[1]);
			katets[1] = abs(y[0] - y[1]);
			lines[0] = sqrt(pow(katets[0], 2) + pow(katets[1], 2));
		}

		else {
			lines[0] = abs(y[0] - y[1]);
		}
	}
	
	else {
		lines[0] = abs(x[0] - x[1]);
	}
	
	// Вычисление стороны BC
	
	if (y[1] != y[2]) {
		if (x[1] != x[2]) {
			katets[0] = abs(x[1] - x[2]);
			katets[1] = abs(y[1] - y[2]);
			lines[1] = sqrt(pow(katets[0], 2) + pow(katets[1], 2));
		}

		else {
			lines[1] = abs(y[1] - y[2]);
		}
	}
	
	else {
		lines[1] = abs(x[1] - x[2]);
	}

	// Вычисление стороны BA

	if (y[0] != y[2]) {
		if (x[0] != x[2]) {
			katets[0] = abs(x[0] - x[2]);
			katets[1] = abs(y[0] - y[2]);
			lines[2] = sqrt(pow(katets[0], 2) + pow(katets[1], 2));
		}

		else {
			lines[2] = abs(y[0] - y[2]);
		}
	}
	
	else {
		lines[2] = abs(x[0] - x[2]);
	}

	// Проверка треугольника на существование

	if (lines[0] + lines[1] > lines[2]){
		if (lines[0] + lines[2] > lines[1]) {
			if (lines[2] + lines[1] > lines[0]) {
				is_real = true;
			}
		}
	}

	// Расчёт высоты
	
	if (is_real) {
		pol_per = (lines[0] + lines[1] + lines[2]) / 2;
		height = (2 * sqrt(pol_per * (pol_per - lines[0]) * (pol_per - lines[1]) * (pol_per - lines[2]))/lines[1]);
		cout << "Длина высоты вашего треугольника: " << height << endl;
	}
	else {
		cout << "Такого треугольника не существует.";
	}
	system("pause");
	return 0;
}