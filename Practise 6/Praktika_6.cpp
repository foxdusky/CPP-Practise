#include <iostream>

using namespace std;

int main()
{

    setlocale(LC_ALL, "Ru");
    
    const int n = 5, c = 4;
    int mas[n][c];
    int i = 0, j = 0, del, krat[n*c], in = 0;
    
    cout << "Введите делитель ";
    cin >> del;

    for (i; i < n; i++) {
        cout << "Введите заглавие " << i+1 << " столбца ";
        cin >> mas[i][j];
        if (mas[i][j] % del == 0) {
            krat[in] = mas[i][j];
            in += 1;
        }
        for (j = 0; j < c; j++) {
            cout << "Введите значение " << j + 1 << " элемента столбца ";
            cin >> mas[i][j];
            if (mas[i][j] % del == 0) {
                krat[in] = mas[i][j];
                in += 1;
            }
        }
    }
    
    for (int i = 0; i<n*c;i++){
        if (i == 0 and krat[i] == 0) {
            cout << "В матрице нет элементов кратных " << del;
            break;
        }
        else if (i==0) cout << "Массив кратных делителю\n";
        if (krat[i] > 0 ){
            cout << krat[i] << " ";
        }
        else break;
    }
    cout << '\n';
    system("pause");
}