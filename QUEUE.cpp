#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
using namespace std;

// ���������� ������� QUEUE 

// ��������� ���� �������
typedef struct Node {
	// �������� �������� �������
	char name[256];			// ������� �. �.
	char sex;				// ���
	int age;				// �������
	char workingPlace[256];	// ����� ������
	int salary;				// ������ ������
	char goal[100];			// ���� ���������

	struct Node* next;		// ��������� �� ��������� �������
} Node;

Node* head = NULL;			// ������ ������� ���������
int countElements = 0;		// ����� ��������� ���������

// ���������� �������� � ����� �������
void enqueue(Node** head, const char name[256], const char sex, int age,
	const char workingPlace[256], int salary, const char goal[100]) {
	// ���������� ���������� ������� ���������
	if ((*head) == NULL) {
		// �������� ���������� ���������� �������
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
		// ����� ���������� �������� �������
		while (current->next != NULL) current = current->next;

		// ��������� ������ ��� ���������� �������� �������
		current->next = new Node();
		// ���������� �������� ���� �������
		strcpy(current->next->name, name);
		current->next->sex = sex;
		current->next->age = age;
		strcpy(current->next->workingPlace, workingPlace);
		current->next->salary = salary;
		strcpy(current->next->goal, goal);

		current = current->next;// ������� � ���������� ����
		current->next = NULL;// ����������� ���������� ���� ��� ��������
	}
	countElements++;// ���������� ���������� ��������� ������� �� ������� 
}

// ������ ��������� �������
void print(const Node* head) {
	while (head) {
		printf("%20s |", head->name);
		printf("%5c |", head->sex);
		printf("%10d |", head->age);
		printf("%40s |", head->workingPlace);
		printf("%10d |", head->salary);
		printf("%10s |", head->goal);
		printf("\n");

		head = head->next;// ������� � ���������� ��������
	}
	printf("\n");
}

// ������� ����� ������� (������������ ������)
void clear(Node** head)
{
	Node* tmp;
	while (*(head)) {
		tmp = (*head)->next;
		delete(*head);
		*(head) = tmp;
	}
}


// �������� ��������, ��������� � ������ � ����� ������
char* trim(char s[256])
{
	
	int i = 0, j;
	while ((s[i] == ' ') || (s[i] == '\t')) i++;

	if (i > 0) {
		for (j = 0; j < strlen(s); j++)
			s[j] = s[j + i];
		s[j] = '\0';
	}

	// ������� ������� � ���� � ����� ������:
	i = strlen(s) - 1;
	while ((s[i] == ' ') || (s[i] == '\t')) i--;

	if (i < (strlen(s) - 1)) s[i + 1] = '\0';

	return s;
}

// ���������� ������ �� ��������� ������� �� ������� � ���������
void splitStrBySymbol(char* str, Node** obj, const char separetor[])
{
	// ������� �� ������ ������ �������� �� ����� (\n)
	int inx = strlen(str) - 1;
	if (str[inx] == '\n') str[inx] = '\0';

	// ��������� ������
	char* strTmp = new char[strlen(str) * sizeof(char)];
	strcpy(strTmp, str);
	// ��������� ��������� �� �������
	char* tmpStr = strtok(strTmp, separetor);
	int column = 1;// ������� ���� ������

	char name[256];			// ������� �. �.
	char sex = '�';			// ���
	int age;				// �������
	char workingPlace[256];	// ����� ������
	int salary;				// ������ ������
	char goal[100];			// ���� ���������

	// ��������� ����������� ������ ������
	do {
		// ������ ������� ������
		strcpy(tmpStr, trim(tmpStr));
		if (column == 1) strcpy(name, tmpStr);
		if (column == 2) sex = tmpStr[0];
		if (column == 3) age = atoi(tmpStr);
		if (column == 4) strcpy(workingPlace, tmpStr);
		if (column == 5) salary = atoi(tmpStr);
		if (column == 6) strcpy(goal, tmpStr);

		// ������� � ��������� ��������� �� ��������� �������
		tmpStr = strtok(NULL, separetor);
		column++;// ��������� ���� ������
	} while (tmpStr != NULL);
	enqueue(&(*obj), name, sex, age, workingPlace, salary, goal);
}

// ������ ������ � �����
void saveToFile(const char fileName1[50], const char fileName2[50], const Node* head)
{
	// �������� ����� ��� ������
	FILE* file1 = fopen(fileName1, "w");
	FILE* file2 = fopen(fileName2, "w");

	// ������ ������ � ����
	while (head) {

		// ������ � ���� � ���������
		if (_strcmpi(head->goal, "������") == 0) {
			fprintf(file1, "%s | %c | %d | %s | %d \n",
				head->name, head->sex, head->age, head->workingPlace,
				head->salary);
		}

		// ������ � ���� �� ��������
		if (_strcmpi(head->goal, "�����") == 0) {
			fprintf(file2, "%s | %c | %d | %s | %d \n",
				head->name, head->sex, head->age, head->workingPlace,
				head->salary);
		}

		head = head->next;// ������� � ���������� ��������
	}
	fclose(file1);// �������� �����
	fclose(file2);// �������� �����
}

// ������ ������ �� �����
bool readFromFile(const char fileName[50], Node** head)
{
	FILE* file;
	// �������� ����� ��� ������	
	file = fopen(fileName, "r");
	if (file == NULL) return false;

	int i = 0;
	char str[256];

	while (!feof(file)) {
		//��������� ������� ������ ������ 
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
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������


	Node* node = NULL;// �������
	// ������ ������ �� �����
	bool bSuccess = readFromFile("input.txt", &node);
	if (!bSuccess) {
		cout << "������ ������ �����...\n";
		system("pause");
		return 0;
	}
	// ������ ������ � ����
	saveToFile("credit.txt", "deposit.txt", node);

	// ����� ������� �� �����
	print(node);
	// ������������ ������������ ������
	clear(&node);

	cout << endl;	// ������� ������
	system("pause");// ����� ���� �������
	return 0;
}