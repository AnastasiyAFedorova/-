#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
using namespace std;

// РЕАЛИЗАЦИЯ ОЧЕРЕДИ QUEUE 

// СТРУКТУРА УЗЛА ОЧЕРЕДИ
typedef struct Node {
	// значения элемента очереди
	char name[256];			// Фамилия И. О.
	char sex;				// пол
	int age;				// возраст
	char workingPlace[256];	// место работы
	int salary;				// размер дохода
	char goal[100];			// цель обращения

	struct Node* next;		// указатель на следующий элемент
} Node;

Node* head = NULL;			// первый элемент структуры
int countElements = 0;		// колво элементов структуры

// добавление элемента в конец очереди
void enqueue(Node** head, const char name[256], const char sex, int age,
	const char workingPlace[256], int salary, const char goal[100]) {
	// объявление временного объекта структуры
	if ((*head) == NULL) {
		// передача параметров временному объекту
		Node* tmp = new Node();
		strcpy(tmp->name, name);
		tmp->sex = sex;
		tmp->age = age;
		strcpy(tmp->workingPlace, workingPlace);
		tmp->salary = salary;
		strcpy(tmp->goal, goal);
		tmp->next = NULL;
	}
	else {
		Node* current = (*head);
		// поиск последнего элемента очереди
		while (current->next != NULL) current = current->next;

		// выделение памяти для последнего элемента очереди
		current->next = new Node();
		// заполнение текущего узла данными
		strcpy(current->next->name, name);
		current->next->sex = sex;
		current->next->age = age;
		strcpy(current->next->workingPlace, workingPlace);
		current->next->salary = salary;
		strcpy(current->next->goal, goal);

		current = current->next;// переход к следующему узлу
		current->next = NULL;// определение последнего узла как нолевого
	}
	countElements++;// увеличение количества элементов очереди на еденицу 
}

// печать элементов очереди
void print(const Node* head) {
	while (head) {
		printf("%20s |", head->name);
		printf("%5c |", head->sex);
		printf("%10d |", head->age);
		printf("%40s |", head->workingPlace);
		printf("%10d |", head->salary);
		printf("%10s |", head->goal);
		printf("\n");

		head = head->next;// переход к следующему элементу
	}
	printf("\n");
}

// очистка всего очереди (освобождение памяти)
void clear(Node** head)
{
	Node* tmp;
	while (*(head)) {
		tmp = (*head)->next;
		delete(*head);
		*(head) = tmp;
	}
}


// удаление пробелов, табуляций в начале и конце строки
char* trim(char s[256])
{
	
	int i = 0, j;
	while ((s[i] == ' ') || (s[i] == '\t')) i++;

	if (i > 0) {
		for (j = 0; j < strlen(s); j++)
			s[j] = s[j + i];
		s[j] = '\0';
	}

	// удаляем пробелы и табы с конца строки:
	i = strlen(s) - 1;
	while ((s[i] == ' ') || (s[i] == '\t')) i--;

	if (i < (strlen(s) - 1)) s[i + 1] = '\0';

	return s;
}

// разделение строки по заданному символу на столбцы в структуру
void splitStrBySymbol(char* str, Node** obj, const char separetor[])
{
	// убираем из строки символ перехода на новую (\n)
	int inx = strlen(str) - 1;
	if (str[inx] == '\n') str[inx] = '\0';

	// временная строка
	char* strTmp = new char[strlen(str) * sizeof(char)];
	strcpy(strTmp, str);
	// получение подстроки по символу
	char* tmpStr = strtok(strTmp, separetor);
	int column = 1;// столбец поля строки

	char name[256];			// Фамилия И. О.
	char sex = 'м';			// пол
	int age;				// возраст
	char workingPlace[256];	// место работы
	int salary;				// размер дохода
	char goal[100];			// цель обращения

	// выделение последующих частей строки
	do {
		// запись столбца строки
		strcpy(tmpStr, trim(tmpStr));
		if (column == 1) strcpy(name, tmpStr);
		if (column == 2) sex = tmpStr[0];
		if (column == 3) age = atoi(tmpStr);
		if (column == 4) strcpy(workingPlace, tmpStr);
		if (column == 5) salary = atoi(tmpStr);
		if (column == 6) strcpy(goal, tmpStr);

		// переход к следующей подстроке по заданному символу
		tmpStr = strtok(NULL, separetor);
		column++;// следующее поле строки
	} while (tmpStr != NULL);
	enqueue(&(*obj), name, sex, age, workingPlace, salary, goal);
}

// запись данных в файлы
void saveToFile(const char fileName1[50], const char fileName2[50], const Node* head)
{
	// открытие файла для записи
	FILE* file1 = fopen(fileName1, "w");
	FILE* file2 = fopen(fileName2, "w");

	// запись данных в файл
	while (head) {

		// запись в файл с кредитами
		if (_strcmpi(head->goal, "кредит") == 0) {
			fprintf(file1, "%s | %c | %d | %s | %d \n",
				head->name, head->sex, head->age, head->workingPlace,
				head->salary);
		}

		// запись в файл со вкладами
		if (_strcmpi(head->goal, "вклад") == 0) {
			fprintf(file2, "%s | %c | %d | %s | %d \n",
				head->name, head->sex, head->age, head->workingPlace,
				head->salary);
		}

		head = head->next;// переход к следующему элементу
	}
	fclose(file1);// закрытие файла
	fclose(file2);// закрытие файла
}

// чтение данных из файла
bool readFromFile(const char fileName[50], Node** head)
{
	FILE* file;
	// открытие файла для чтения	
	file = fopen(fileName, "r");
	if (file == NULL) return false;

	int i = 0;
	char str[256];

	while (!feof(file)) {
		//считываем текущую строку строку 
		fgets(str, sizeof(str), file);
		splitStrBySymbol(str, &(*head), "|");
		i++;
	}

	fclose(file);
	return true;
}


int main()
{
	
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода


	Node* node = NULL;// очередь
	// чтение данных из файла
	bool bSuccess = readFromFile("input.txt", &node);
	if (!bSuccess) {
		cout << "Ошибка чтения файла...\n";
		system("pause");
		return 0;
	}
	// запись данных в файл
	saveToFile("credit.txt", "deposit.txt", node);

	// вывод очереди на экран
	print(node);
	// освобождение динамической памяти
	clear(&node);

	cout << endl;	// перенос строки
	system("pause");// пауза окна консоли
	return 0;
}