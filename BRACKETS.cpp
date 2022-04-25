#include <iostream>
#include <stack>
using namespace std;// ������������ ����


struct Bracket
{
public:

	int pos;
	char c;

	Bracket() {}

	Bracket(int p, char sz) { pos = p; c = sz; }
};

// �������� ��������� �� ������������ ������
int isValid(string str)
{
	// ���������� �����
	stack<Bracket> list;
	char firstElement = NULL;// ������ ������� � �����
	int lastIndex = 0;
	// ����� ������� ������� ������
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];

		switch (c)
		{
			// ���� �� �������� ������
		case '{':
		case '(':
		case '[':
		case '<':
			list.push(Bracket(i + 1, c));// ���������� ������ � ����
			lastIndex = i;
			break;


		case '}':
		case ')':
		case ']':
		case '>':

			if (list.size() == 0) return i + 1;
			Bracket br = list.top();// ������ �������� �����
			list.pop();// �������� �������� �� ������� �����

			// ���� ��� ������� ������ "�" ��� �������� ������, �������
			if (c == '}') if (br.c != '{') return i + 1;
			if (c == ')') if (br.c != '(') return i + 1;
			if (c == ']') if (br.c != '[') return i + 1;
			if (c == '>') if (br.c != '<') return i + 1;
		}
	}

	// ������ ������� ��������� ������
	if (list.size() > 0) {
		Bracket br = list.top();// ������ �������� �����
		return br.pos;
	}
	return -1;
}


int main()
{
	setlocale(LC_ALL, "RU");
	string str;
	cout << "������� ���������: ";
	cin >> str;
	int result = isValid(str);
	if (result == -1) cout << "C����� �������� ���������� ���������";
	else  cout << "������ ��������� � ������� " << result;

	cout << endl;
	return 0;
}