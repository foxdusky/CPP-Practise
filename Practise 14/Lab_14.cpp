#include "wallpaper.h"
wallpaperNode* wallpaperRoot = new wallpaperNode;
int main(string args[])
{
	setlocale(LC_ALL, "Ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int e = 0;
	int check = 0;
	int x;
	while (true) {
		system("cls");
		cout << "1. Запись данных в файл " << endl << "2. Вывод данных из файла" << endl << "3. Найти минимальную стоимость лёгкого рулона с шириной от 50 см" << endl << "4. Вывод в файл таблицы" << endl << "5. Вывод в формате .CSV" << endl << "---------------------------" << endl << "6. Составить список из файла" << endl << "7. Показать список" << endl << "8. Очистить список" << endl << "---------------------------" << endl << "9. Выход" << endl << "---------> ";
		cin >> x;
		switch (x) {
		case 1:
			input_data();
			break;
		case 2:
			output_data();
			system("pause");
			break;
		case 3:
			min_cost();
			system("pause");
			break;
		case 4:
			check = table();
			if (check == 0) {
				cout << "Данные были успешно перенесены в таблицу!\n";
				cout << "Открыть таблицу? (1 - да/ 0 - нет)";
				cin >> e;
				if (e == 1) system("start wallpaper.txt");
			}
			else if (check == 1) {
				cout << "Не удалось открыть файл данных";
			}
			else cout << "Не удалось создать таблицу";
			break;
		case 5:
			check = export_data();
			if (check == 0) {
				cout << "Данные были успешно перенесены в .CSV таблицу!\n";
				cout << "Открыть таблицу? (1 - да/ 0 - нет)";
				cin >> e;
				if (e == 1) system("start excel wallpaper.csv");
			}
			else if (check == 1) {
				cout << "Не удалось открыть файл данных";
			}
			else cout << "Не удалось создать .CSV таблицу";
			break;
		case 6:
			if (wallpaperRoot->next == NULL) {
				create_root(wallpaperRoot);
				cout << "Список составлен!" << endl;
			}
			else
				cout << "Список уже создан" << endl;
			system("pause");
			break;
		case 7:
			if (wallpaperRoot->next != NULL)
				show_root(wallpaperRoot);
			else
				cout << "Список еще не был создан." << endl;
			system("pause");
			break;
		case 8:
			if (wallpaperRoot->next != NULL)
			{
				erase_root(wallpaperRoot);
				cout << "Список успешно очищен." << endl;
			}
			else
				cout << "Список еще не был создан." << endl;
			system("pause");
			break;
		case 9:
			if (wallpaperRoot->next != NULL) {
				cout << "!----------------------!\n" << "На данный момент создан список выберите варианты действий:\n" << "   1. Очистить список и выйти из программы\n" << "   2. Оставить всё как есть и не выходить\n" << "------>";
				cin >> e;
				if (e == 1) {
					erase_root(wallpaperRoot);
					return 0;
				}
				else break;
			}
			return 0;
			break;
		default:
			cout << endl << "Вы ввели неверное значение." << endl;
			system("timeout 5");
		}
	}
}