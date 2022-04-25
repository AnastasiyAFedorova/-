#include <iostream>
#include <stack>
using namespace std;// пространство имен


struct Bracket
{
public:

	int pos;
	char c;

	Bracket() {}

	Bracket(int p, char sz) { pos = p; c = sz; }
};

// проверка выражени€ на корректность скобок
int isValid(string str)
{
	// объ€вление стека
	stack<Bracket> list;
	char firstElement = NULL;// первый элемент в стеке
	int lastIndex = 0;
	// обход каждого символа строки
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];

		switch (c)
		{
			// одна из открытых скобок
		case '{':
		case '(':
		case '[':
		case '<':
			list.push(Bracket(i + 1, c));// добавление скобки в стек
			lastIndex = i;
			break;


		case '}':
		case ')':
		case ']':
		case '>':

			if (list.size() == 0) return i + 1;
			Bracket br = list.top();// первый элемента стека
			list.pop();// удаление элемента из вершины стека

			// если дл€ текущей скобки "с" нет открытой скобки, выходим
			if (c == '}') if (br.c != '{') return i + 1;
			if (c == ')') if (br.c != '(') return i + 1;
			if (c == ']') if (br.c != '[') return i + 1;
			if (c == '>') if (br.c != '<') return i + 1;
		}
	}

	// вернет позицию ошибочной скобки
	if (list.size() > 0) {
		Bracket br = list.top();// первый элемента стека
		return br.pos;
	}
	return -1;
}


int main()
{
	setlocale(LC_ALL, "RU");
	string str;
	cout << "¬ведите выражение: ";
	cin >> str;
	int result = isValid(str);
	if (result == -1) cout << "Cтрока содержит корректное выражение";
	else  cout << "ќшибка выражени€ в позиции " << result;

	cout << endl;
	return 0;
}