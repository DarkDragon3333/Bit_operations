#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

// Задание 1.а
void task_1a() {
	cout << "Задание 1.а\n";

	unsigned char mask = 1; //1 — это: 0000 0001 (8-разрядная маска)
	unsigned char a = 255; // 255 = 1111 1111

	cout << "Число: " << int(a) << endl; //Явно приводим переменную a к типу char

	a = a & (~(mask << 4)); // Сдвигаем бит переменной mask влево на 4 позиции. Потом инвертируем mask. Потом применяем операция ‘&’ к переменным mask и a.

	cout << "Результат: " << int(a) << endl << endl; //Явно приводим переменную a к типу char.

}

// Задание 1.б
void task_1b() {
	cout << "Задание 1.б\n";

	unsigned char mask = 1; //1 - это: 0000 0001 (8-разрядная маска)
	unsigned char b = 128; // 128 = 1000 0000

	cout << "Число: " << int(b) << endl; //Явно приводим переменную b к типу char

	b = b | (mask << 6); // Сдвигаем бит переменной mask на 6 позиций влево. Потом применяем операцию ‘|’ к переменным mask и b 

	cout << "Результат: " << int(b) << endl << endl;
}

// Задание 1.в
void task_1B() {
	cout << "Задание 1.в\n";

	unsigned int x = 25; // Беззнаковая переменная x
	const int n = sizeof(int) * 8; // размерность int в битах (4*8=32)
	unsigned maska = (1 << n - 1); // сдвиг единицы на место самого старшего бита (бит под номером 31)

	cout << "Начальный вид маски: " << bitset<n>(maska) << endl; //Выводим маску
	cout << "Результат: ";

	for (int i = 1; i <= n; i++) {
		cout << ((x & maska) >> (n - i)); // Вывод x в битовом представлении
		maska = maska >> 1; //Сдвигаем биты маски вправо
	}
	cout << "\nОбьяснение: выводит число x в битовом представлении, начиная слева и сдвигая полученный бит для его корректного вывода.\n" << endl;

}
// Задание 2.а
void task_2a() {
	cout << "Задание 2.а\n";

	unsigned char mask = 1; //1 = 0000 0001 - 8-разрядная маска
	unsigned char flag = 0; //Битовый массив из нулей, где будут хранится индексы чисел
	int temp = 0;

	cout << "Введите 5 значений от 0 до 7: ";
	for (int i = 0; i < 5; i++) {
		cin >> temp; //Вводим числа массива
		flag = flag | (mask << (temp)); //Сдвигаем бит на значение переменной temp. Применяем операцию ‘|’ к переменной flag и mask и результат присваиваем в переменную flag. Мы сохранили прошлый и новый результат.
	}

	cout << "Результат: ";
	for (int i = 0; i <= 7; i++) {
		if ((mask & flag) != 0) {//Если единицы совпадают
			cout << i << " ";//Выводим число
		}
		mask = mask << 1; //Сдвигаем маску на 1 влево
	}
	cout << "\n\n";
}

// Задание 2.б
void task_2b() {
	cout << "Задание 2.б\n";

	unsigned long long mask = 1;
	unsigned long long m = 0;
	int flag = 0;

	cout << "Введите 5 значений от 0 до 63: ";
	for (int i = 0; i < 5; i++) {
		cin >> flag;
		m = m | (mask << (flag));
	}

	cout << "Результат: ";
	for (int i = 0; i <= 63; i++) {
		if ((mask & m) != 0) {
			cout << i << " ";
		}
		mask = mask << 1;
	}
	cout << "\n\n";
}

// Задание 2.в
void task_2B() {
	cout << "Задание 2.в\n";

	unsigned char mask = 1;
	vector<unsigned char> m; //Создадим вектор m

	for (int i = 0; i <= 63; i++) {
		m.push_back(0); //Добавляем в вектор 64 нуля
	}

	int flag = 0;

	cout << "Введите 5 значений от 0 до 63: ";
	for (int i = 0; i < 5; i++) {
		cin >> flag;
		m[flag / 8] = m[flag / 8] | (mask << (flag % 8));
	}

	cout << "Результат: ";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) { // Рассмотрим элемента вектора
			flag = (m[i] & mask) >> j;
			if (flag == 1) {
				cout << 8 * i + j << " ";
			}
			mask = (mask << 1);
		}
		mask = 1; // Сброс маски
	}
	cout << "\n\n";
}

void createText() {
	ofstream file;
	file.open("text.txt");
	for (int i = 9999999; i >= 1000000; i--) {
		file << i << " ";
	};
	file.close();
}

void task_3a_and_3b() {	// Задания 3.а и 3.б
	cout << "\nЗадание:\n3.1)Реализуйте задачу сортировки числового файла с заданными условиями.\nДобавьте в код возможность определения времени работы программы\n3.2)Определите программно объём оперативной памяти, занимаемый битовым массивом.\n\n";
	unsigned char mask = 1;
	auto begin = chrono::high_resolution_clock::now();
	// Старт таймера
	ofstream output;
	ifstream file;
	file.open("text.txt");
	output.open("output.txt");

	vector<unsigned char> m;
	for (int i = 0; i < 10000000 / 8; i++) {
		m.push_back(0);
	}
	int tmp;
	while (file >> tmp) {
		m[tmp / 8] = m[tmp / 8] | (mask << (tmp % 8));
	}

	for (int i = 0; i < 10000000 / 8; i++) {
		for (int j = 0; j < 8; j++) {
			// Просмотр элемента вектора
			tmp = (m[i] & mask) >> j;
			if (tmp == 1) {
				output << 8 * i + j << " ";
			}
			mask = mask << 1;
		}
		mask = 1; // Сброс маски
	}
	// Остановка таймера
	auto end = chrono::steady_clock::now();
	m.shrink_to_fit();
	cout << m.capacity() << " Байт" << endl;
	cout << m.capacity() / 1024 << " КБ" << endl;
	cout << m.capacity() / 1024 / 1024 << " МБ";
	cout << endl;
	chrono::duration<double, std::milli> elapsed_ms = end - begin;
	cout << "Time: " << elapsed_ms.count() << " ms\n";
}



int main() {
	setlocale(0, "");
	cout << "Практическая работа №2.1\n" << endl;
	while (true)
	{
		cout << "\nВыберите задачи:\n1.a - 1, 1.b - 2, 1.v - 3, 2.a - 4, 2.b - 5, 2.v - 6, 3.a и 3.b - 7,\nсоздания файл для 3 задачи - 8, Выход из программы - n: ";
		char t;
		cin >> t;
		cout << endl;
		switch (t)
		{
		case '1':
			task_1a();
			break;
		case '2':
			task_1b();
			break;
		case '3':
			task_1B();
			break;
		case '4':
			task_2a();
			break;
		case '5':
			task_2b();
			break;
		case '6':
			task_2B();
			break;
		case '7':
			task_3a_and_3b();
			break;
		case '8':
			createText();
			cout << "Создался файл\n";
			break;
		case '9':
			exit(0);
		default:
			cout << "Неверный ввод,повторите попытку\n";

		}
	}


}