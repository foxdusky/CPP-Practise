#include <iostream>

using namespace std;

long int f(int n)
{
	if (n == 0) return 0;
	if (n == 1 || n == 2 || n == -1 || n == -2) return 1;
	if (n > 0) {
		return f(n - 1) + f(n - 2);
	}
	else {
		return f(n + 1) + f(n + 2);
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int x = 0;
	cout << "Введите желаемое порядковое число Фибоначчи: ";
	cin >> x;
	int fib, mn = 1;
	fib = f(x);
	if (x < 0 && x % 2 == 0) {
		mn = -1;
	}
	cout << x << "-е Число Фибоначчи: " << mn*fib << "\n";
}	