#include <iostream>
#include <string>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    int max = 0, in = 0, sum = 1, first = 0, change = 0, check = 0;

    const int n = 10;

    int a[n];

    for (int i = 0; i < n; i++) {
        cout << "Введите " << i + 1 << " значение элемента массива.\n";
        cin >> a[i];
    }

    // Обработка массива и его вывод.

    cout << "Массив после обработки ";

    for (int i = 0; i < n; i += 2) {
        change = a[i + 1];
        a[i + 1] = a[i];
        a[i] = change;
        cout << a[i] << "  " << a[i + 1] << "  ";
    }
    cout << '\n';
    // Ищем наибольший элемент массива, попутно умножая значения меж нулевыми значени.ями массива
    
    for (int i = 0; i < n; i++) {
        // Поиск максимального значения.
        if (a[i] > max){
            max = a[i];
            in = i;
        }
        // Вхождение первого нуля, открытие для умножения последующих членов массива.
        if (a[i] == 0 and first == 0)
        {
            first += 1;
            check = i;
        }
        // Непосредственное перемножение.
        if (first == 1 and a[i] != 0) {
            sum *= a[i];
        }
        // Нашёлся второй ноль, закрытие.
        if (a[i] == 0 and first == 1 and check != i) {
            if (check + 1 == i) {
                sum = 0;
            }
            first = 2;
        }
    }

    cout << "Индекс наибольшего числа в массиве - " << in+1 << ", его значение = " << max << "\n";
    
    cout << "Произведение элементов между нулевыми элементами равно: " << sum << "\n";
    


    cout << '\n';
    
    system("pause");
}