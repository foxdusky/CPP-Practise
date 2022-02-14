#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    string any;
    cout << "Введите строку ";
    getline(cin,any);
    int i = 0;
    for (i; i < any.size(); i++){
        if (isdigit(any[i]) == false && any[i] != ' ') break;
    }
    if (i == any.size()) cout << "Ваша строка успешно прошла проверку, это число.";
    else cout << "Ваша строка не прошла проверку, это не число.";
    return 0;
}