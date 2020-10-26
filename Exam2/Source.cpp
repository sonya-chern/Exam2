#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include<cctype>
#include<cstdlib>
#include<string>
#include <ctime>
#define SHOW
using namespace std;
int sizeArr=1; // размер динамического массива структур
char digit[20]; //массив для преобразования из строки
string FindCase;// та самая строка
int i = 0, j, A, B, C, D, F, IndikVvoda, IndikVvoda2, IndikGo, IndikZapolnenia = 1, IndikZapolnenia2, IndikObezian = 0;
struct Date { int day; int month; int year; int hour; int minute; };
struct Case { string name; int priority; string description; Date y; };
Case x = { "0" , 0 ,"0" , {0,0,0,0,0} };
inline int IsItDigit(int* a, char digit[20]);
inline void EnterDigit(int &a, char digit[], int i);
Case AddCase(Case& x);
Case* CopyFillCase(Case*& ListCases, int IndikZapolnenia, Case& x);
Case* DeleteCase(Case*& ListCases, int& sizeArr, int IndikVvoda, int& IndikZapolnenia);
Case* Modify(Case*& ListCases, int& sizeArr, int IndikVvoda);
void SerchCaseByName(Case*& ListCases, int& sizeArr, string FindCase);
void SerchCaseByPriority(Case*& ListCases, int& sizeArr, int IndikVvoda);
void SerchCaseByDescription(Case*& ListCases, int& sizeArr, string FindCase);
Case* SortByPriority(Case*& ListCases, int& sizeArr);
Case* SortByDate(Case*& ListCases, int& sizeArr);
Case* ChangeCasePlace(Case*& ListCases, int i);
Case* CopyAfterShow(Case*& ListCases, Case*& New_ListCases, int sizeArr, int IndikZapolnenia, int i, int A, int B, int C);
Case* SortAll(Case*& New_ListCases, int IndikZapolnenia, int& IndikGo);
void ShowCase(Case x);
void ShowOnlySort(Case*& New_ListCases, int IndikZapolnenia);

int main() {
	setlocale(LC_ALL, "Russian");
	Case* ListCases = new Case[sizeArr];
	ListCases[0].y.day = 0; ListCases[0].y.month = 0; ListCases[0].y.year = 0; ListCases[0].y.hour = 0; ListCases[0].y.minute = 0;
	ListCases[0].name = "Дел нет"; ListCases[0].priority = 0; ListCases[0].description = "Дел нет";
	cout << "\t Приветствую! Выберете необходимое действие: " << endl;
	do {
		cout << "1 - заполнить список дел" << endl << "2 - удаление дела" << endl << "3 - редактирование дела" << endl;
		cout << "4 - поиск дела" << endl << "5 - отобразить список дел" << endl << "0 - закрыть приложение" << endl;
		EnterDigit(IndikGo, digit, i);
		switch (IndikGo) {
		case 0: {cout << "Пока!"; return 0; }
		case 1: {
			do {
				system("cls");
				cout << "Желаете добавить дело в список? Нажмите 1." << endl;
				cout << "Для возврата в предыдущее меню нажмите 0" << endl;
				EnterDigit(IndikVvoda, digit, i);
				if (IndikVvoda != 1) break;
				if (sizeArr == 1 && IndikZapolnenia == 1) {
					ListCases[0] = AddCase(x); ++IndikZapolnenia; 
				}
				else {
					Case a;
					ListCases = CopyFillCase(ListCases, IndikZapolnenia, a);
					sizeArr = IndikZapolnenia;
					++IndikZapolnenia;
					cout << "Дело добавлено" << endl;
				}
			} while (IndikVvoda == 1);
			system("cls");
			break; }
		case 2: {
			do {
				system("cls");
				cout << "Какое дело удалить? Выберите номер." << endl;
				cout << "Для возврата в предыдущее меню нажмите 0" << endl;
				for (i = 0; i < sizeArr; i++) {
					cout << i + 1 << " " << "Название: " << ListCases[i].name << endl;
					cout << "  " << "Описание: " << ListCases[i].description << endl << endl;
				}
				EnterDigit(IndikVvoda, digit, i);
				if (IndikVvoda == 0 || IndikVvoda <1 || IndikVvoda>sizeArr) { break; }
				ListCases = DeleteCase(ListCases, sizeArr, IndikVvoda, IndikZapolnenia);
			} while (IndikVvoda != 0);
			system("cls");
			break;
		}
		case 3: {
			do {
				system("cls");
				cout << "Какое дело редактировать? Выберите номер." << endl;
				cout << "Для возврата в предыдущее меню нажмите 0" << endl;
				for (i = 0; i < sizeArr; i++) {
					cout << i + 1 << " " << "Название: " << ListCases[i].name << endl;
					cout << "  " << "Описание: " << ListCases[i].description << endl << endl;
				}
				EnterDigit(IndikVvoda, digit, i);
				if (IndikVvoda == 0 || IndikVvoda <1 || IndikVvoda>sizeArr) { break; }
				ListCases = Modify(ListCases, sizeArr, IndikVvoda);
			} while (IndikVvoda != 0);
			system("cls");
			break;
		}
		case 4: { system("cls");
			do {
				cout << "Поиск дела по названию - нажмите 1, по приоритету - 2, поиск по описанию - 3, по дате и времени - 4" << endl;
				cout << "Для возврата в предыдущее меню нажмите 0" << endl;
				EnterDigit(IndikVvoda, digit, i);
				system("cls");
				if (IndikVvoda == 0 || IndikVvoda < 1 || IndikVvoda>4) { break; }
				switch (IndikVvoda) {
				case 1: {
					cout << "Введите название дела " << endl << "Для возврата в предыдущее меню нажмите 0" << endl;
					getline(cin, FindCase);
					char digit2[30];
					for (i = 0; i < (int)FindCase.length(); i++) { digit2[i] = FindCase[i]; }
					i = IsItDigit(&IndikVvoda, digit2);
					if (i == 1) { break; }
					SerchCaseByName(ListCases, sizeArr, FindCase);
					break;
				}
				case 2: {cout << "Введите номер приоритета ( 1- высокий, 2 - средний, 3 - низкий) " << endl;
					cout << "Для возврата в предыдущее меню нажмите 0" << endl;
					EnterDigit(IndikVvoda, digit, i);
					if (IndikVvoda > 0 && IndikVvoda < 4)
						SerchCaseByPriority(ListCases, sizeArr, IndikVvoda);
					break;
				}
				case 3: {
					cout << "Введите описание дела" << endl << "Для возврата в предыдущее меню нажмите 0" << endl;
					getline(cin, FindCase);
					char digit2[30];
					for (i = 0; i < (int)FindCase.length(); i++) { digit2[i] = FindCase[i]; }
					i = IsItDigit(&IndikVvoda, digit2);
					if (i == 1) { break; }
					SerchCaseByDescription(ListCases, sizeArr, FindCase);
					break; }
				case 4: {
					cout << "Введите число:" << endl; 	EnterDigit(A, digit, i);
					if (A == 0) { cout << "Нет такой даты"; break; }
					cout << "Введите месяц:" << endl;	EnterDigit(B, digit, i);
					if (B == 0) { cout << "Нет такой даты"; break; }
					cout << "Введите год:" << endl;		EnterDigit(F, digit, i);
					if (F == 0) { cout << "Нет такой даты"; break; }
					cout << "Введите час:" << endl;		EnterDigit(C, digit, i);
					cout << "Введите минуты:" << endl;	EnterDigit(D, digit, i);
					int IndikSerch = 0;
					for (i = 0; i < sizeArr; i++) {
						if (ListCases[i].y.day == A &&	ListCases[i].y.month == B &&
							ListCases[i].y.year == F &&	ListCases[i].y.hour == C &&	ListCases[i].y.month == D) {
							cout << ++IndikSerch << " ";
							ShowCase(ListCases[i]);
							cout << endl;
						}
					}
				}
				}
			} while (IndikVvoda > 0);	system("cls");
			break;
		}
		case 5: { 
			/*time_t timer;					//как получить самарское время?
			struct tm* ptm;
			time (&timer);
			ptm = gmtime_s (&timer);
			cout << "Самарское время: " << (ptm->tm_hour + 5) % 24 << ":"<< ptm->tm_min << endl;*/
			system("cls");
			cout << "Введите сегодняшнее число:" << endl;
			EnterDigit(A, digit, i);
			if (A == 0) { cout << "Нет такой даты"; break; }
			cout << "Введите текущий месяц:" << endl;
			EnterDigit(B, digit, i);
			cout << "Введите текущий год:" << endl;
			EnterDigit(C, digit, i);
			system("cls");
			do {
				cout << "Сегодня: " << A << "." << B << "." << C << endl;
				cout << "Отобразить дела на сегодня - нажмите 1, на неделю - 2, отобразить дела на месяц  - 3." << endl;
				cout << "Для возврата в предыдущее меню нажмите 0" << endl;
				EnterDigit(IndikVvoda, digit, i);
				system("cls");
				if (IndikVvoda < 1 || IndikVvoda>3)  break;
				else if (IndikVvoda == 1) {	
					IndikZapolnenia2 = 0;
					for (j = 0; j < sizeArr; j++) {
						if (A == ListCases[j].y.day && B == ListCases[j].y.month && C == ListCases[j].y.year) { ++IndikZapolnenia2; }
					}
					if (IndikZapolnenia2 == 0) { cout << "Дел на сегодня нет" << endl; }
					else {
						Case* New_ListCases = new Case [IndikZapolnenia2];
						i = 1;
						CopyAfterShow(ListCases, New_ListCases, sizeArr, IndikZapolnenia2, i, A, B, C);
						ShowOnlySort(New_ListCases, IndikZapolnenia2);
						SortAll(New_ListCases, IndikZapolnenia2, IndikGo);
						if (IndikGo == 1) continue;
						else {
							system("cls");
							ShowOnlySort(New_ListCases, IndikZapolnenia2);
						}
						delete[] New_ListCases;
					}
				}
				else if (IndikVvoda == 2) {
					IndikZapolnenia2 = 0;
					int n = 0, m = A;
					do {
						for (j = 0; j < sizeArr; j++) {
							if (m == ListCases[j].y.day && B == ListCases[j].y.month && C == ListCases[j].y.year) { ++IndikZapolnenia2; }
						}
						++m; ++n;
					} while (n < 7);
					if (IndikZapolnenia2 == 0) { cout << "Дел нет" << endl; }
					else {
						Case* New_ListCases = new Case[IndikZapolnenia2];
						CopyAfterShow(ListCases, New_ListCases, sizeArr, IndikZapolnenia2, n, A, B, C);
						ShowOnlySort(New_ListCases, IndikZapolnenia2);
						SortAll(New_ListCases, IndikZapolnenia2, IndikGo);
						if (IndikGo == 1) continue;
						delete[] New_ListCases;
					}
				}
				else if (IndikVvoda == 3) {
					IndikZapolnenia2 = 0;
					int n = 0;
						for (j = 0; j < sizeArr; j++) {
							if (A <= ListCases[j].y.day && B == ListCases[j].y.month && C == ListCases[j].y.year) { ++IndikZapolnenia2; }
						}
					if (IndikZapolnenia2 == 0) { cout << "Дел на этот месяц нет" << endl;}
					else {
						Case* New_ListCases = new Case[IndikZapolnenia2];
						i = 0;
						CopyAfterShow(ListCases, New_ListCases, sizeArr, IndikZapolnenia2, i, A, B, C);
						ShowOnlySort(New_ListCases, IndikZapolnenia2);
						SortAll(New_ListCases, IndikZapolnenia2, IndikGo);
						if (IndikGo == 1) continue;
						delete[] New_ListCases;
					}
				}
				//delete[] New_ListCases;
			} while (IndikVvoda != 0);
			system("cls");
			break;
		}
			default: {cout << "Неправильно выбрано действие. Выберете действие: " << endl; IndikObezian++; }
		}
	} while (IndikGo != 0 || IndikObezian > 3); cout << "Пока!";
	delete[] ListCases;
	return 0;
}
/// ///////////////////////////////////////////////////////////
inline int IsItDigit(int* a, char digit[20]) {
	if (isdigit(digit[0])) {
		*a = atoi(digit);
		for (i = 0; i < 20; i++) digit[i] = 0;
		return 1;
	}
	else return 0;
};
inline void EnterDigit(int &a, char digit[], int i) {
	do {
		cin >> digit;
		cin.ignore(32767, '\n');
		i = IsItDigit(&a, digit);
		if (i == 0) cout << "Введите число" << endl;
	} while (i == 0);
};
Case AddCase(Case& x) {
	cout << "Название: "; getline(cin, x.name);
	cout << "Приоритет( 1- высокий, 2 - средний, 3 - низкий): ";	
	EnterDigit(x.priority, digit, i);
	if (x.priority < 1 || x.priority>3) { 
		cout << "Неправильно введен приоритет. Пожалуйста, введите цифру для обозначения приоритета: " << endl; 
		EnterDigit(x.priority, digit, i);
	}
	cout << "Описание: "; getline(cin, x.description);
	cout << "День исполнения: "; 
	EnterDigit(x.y.day, digit, i);
	cout << "Месяц: "; 
	EnterDigit(x.y.month, digit, i);
	cout << "Год: "; 
	EnterDigit(x.y.year, digit, i);
#ifdef SHOW
	cout << "До скольки выполнить, час (формат 24 часа): "; 
	EnterDigit(x.y.hour, digit, i);
	cout << "Минуты: "; 
	EnterDigit(x.y.minute, digit, i);
#endif // SHOW
	return x;
};
void ShowCase(Case x) {
	cout << "Название: " << x.name << endl;
	cout << "Приоритет: " << x.priority << endl;
	cout << "Описание: " << x.description << endl;
	cout << "Дата исполнения: " << x.y.day << "." << x.y.month << "." << x.y.year << "г." << " ";
#ifdef SHOW
	cout << x.y.hour << ":";
	x.y.minute == 0 ? cout << x.y.minute << x.y.minute : cout << x.y.minute;
	cout << endl;
#endif // SHOW
};
void ShowOnlySort(Case*& New_ListCases, int IndikZapolnenia) {
	for (i = 0; i < IndikZapolnenia; i++) {
		cout << i + 1 << " ";
		ShowCase(New_ListCases[i]);
		cout << endl << endl;
	}
};
Case* CopyFillCase(Case*& ListCases, int IndikZapolnenia, Case &x) {
	Case* New_ListCases = new Case[IndikZapolnenia];
	for (i = 0; i < IndikZapolnenia-1; i++) {
		New_ListCases[i].name = ListCases[i].name;
		New_ListCases[i].priority = ListCases[i].priority;
		New_ListCases[i].description = ListCases[i].description;
		New_ListCases[i].y.day = ListCases[i].y.day;
		New_ListCases[i].y.month = ListCases[i].y.month;
		New_ListCases[i].y.year = ListCases[i].y.year;
		New_ListCases[i].y.hour = ListCases[i].y.hour;
		New_ListCases[i].y.minute = ListCases[i].y.minute;
	}
	New_ListCases[IndikZapolnenia - 1] = AddCase(x);
	delete[] ListCases;
	ListCases = New_ListCases;
	return ListCases;
};
Case* DeleteCase(Case*& ListCases, int &sizeArr, int IndikVvoda, int &IndikZapolnenia) {
	if (sizeArr == 1) {
		ListCases[0].y.day = 0; ListCases[0].y.month = 0; ListCases[0].y.year = 0; ListCases[0].y.hour = 0; ListCases[0].y.minute = 0;
		ListCases[0].name = "Дел нет"; ListCases[0].priority = 0; ListCases[0].description = "Дел нет"; IndikZapolnenia = 1;
	}
	else {
		i = 0;
		sizeArr = sizeArr - 1;
		IndikVvoda = IndikVvoda - 1;
		Case* New_ListCases = new Case[sizeArr];
		for (j = 0; j <= sizeArr; j++) {
			if (j == IndikVvoda) { continue; }
			for (;;) {
				New_ListCases[i].name = ListCases[j].name;
				New_ListCases[i].priority = ListCases[j].priority;
				New_ListCases[i].description = ListCases[j].description;
				New_ListCases[i].y.day = ListCases[j].y.day;
				New_ListCases[i].y.month = ListCases[j].y.month;
				New_ListCases[i].y.year = ListCases[j].y.year;
				New_ListCases[i].y.hour = ListCases[j].y.hour;
				New_ListCases[i].y.minute = ListCases[j].y.minute;
				i++;
				break;
			}
		}
		delete[] ListCases; ListCases = New_ListCases;
	}
		return ListCases;	
};
Case* Modify(Case*& ListCases, int& sizeArr, int IndikVvoda) {
	ListCases[IndikVvoda - 1] = AddCase(x); 
	return ListCases;
};
void SerchCaseByName(Case*& ListCases, int& sizeArr, string FindCase) {
	int IndikSerch = 0;
	for (i = 0; i < sizeArr; i++) {
		if ((ListCases[i].name.find(FindCase)) != -1) {
			cout << ++IndikSerch << " ";
			ShowCase(ListCases[i]);
			cout << endl;
		}
	}
	if (!IndikSerch) cout << "Такого дела нет" << endl;
};
void SerchCaseByPriority(Case*& ListCases, int& sizeArr, int IndikVvoda) {
	int IndikSerch = 0;
	for (i = 0; i < sizeArr; i++) {
		if (ListCases[i].priority == IndikVvoda) {
			cout << ++IndikSerch << " ";
			ShowCase(ListCases[i]);
			cout << endl;
		}
	}
	if (!IndikSerch) cout << "Такого дела нет" << endl;
};
void SerchCaseByDescription(Case*& ListCases, int& sizeArr, string FindCase) {
	int IndikSerch = 0;
	for (i = 0; i < sizeArr; i++) {
		if ((ListCases[i].description.find(FindCase)) != -1) {
			cout << ++IndikSerch << " ";
			ShowCase(ListCases[i]);
			cout << endl;
		}
	}
	if (!IndikSerch) cout << "Такого дела нет" << endl;
};
Case* SortByPriority(Case*& New_ListCases, int& IndikZapolnenia) {
	for (i = 0; i < IndikZapolnenia; i++) {
		for (j = IndikZapolnenia - 1; j > i; j--) {
			if (New_ListCases[j - 1].priority > New_ListCases[j].priority) {
				Case temp = New_ListCases[j - 1];
				New_ListCases[j - 1] = New_ListCases[j];
				New_ListCases[j] = temp;
			}
		}
	}
	return New_ListCases;
};
Case* SortByDate(Case*& New_ListCases, int& IndikZapolnenia) {
	for (i = 0; i < IndikZapolnenia; i++) {
		for (j = IndikZapolnenia - 1; j > i; j--) {
			if (New_ListCases[j - 1].y.year > New_ListCases[j].y.year) {
				Case temp = New_ListCases[j - 1];
				New_ListCases[j - 1] = New_ListCases[j];
				New_ListCases[j] = temp;
			}
		}
	}
	for (i = 0; i < IndikZapolnenia; i++) {
		if (New_ListCases[i].y.year == New_ListCases[i + 1].y.year &&
			New_ListCases[i].y.month == New_ListCases[i + 1].y.month) {
			if (New_ListCases[i].y.day > New_ListCases[i + 1].y.day) {
				ChangeCasePlace(New_ListCases, i);
			}
		}
	}
	for (i = 0; i < IndikZapolnenia; i++) {
		if (New_ListCases[i].y.year == New_ListCases[i + 1].y.year &&
			New_ListCases[i].y.month == New_ListCases[i + 1].y.month) {
			if (New_ListCases[i].y.day > New_ListCases[i + 1].y.day) {
				ChangeCasePlace(New_ListCases, i);
			}
		}
	}
	for (i = 0; i < IndikZapolnenia; i++) {
		if (New_ListCases[i].y.year == New_ListCases[i + 1].y.year &&
			New_ListCases[i].y.day == New_ListCases[i + 1].y.day &&
			New_ListCases[i].y.month == New_ListCases[i + 1].y.month) {
			if (New_ListCases[i].y.hour > New_ListCases[i + 1].y.hour) {
				ChangeCasePlace(New_ListCases, i);
			}
		}
	}
	for (i = 0; i < IndikZapolnenia; i++) {
		if (New_ListCases[i].y.year == New_ListCases[i + 1].y.year &&
			New_ListCases[i].y.hour == New_ListCases[i + 1].y.hour &&
			New_ListCases[i].y.day == New_ListCases[i + 1].y.day &&
			New_ListCases[i].y.month == New_ListCases[i + 1].y.month) {
			if (New_ListCases[i].y.minute > New_ListCases[i + 1].y.minute) {
				ChangeCasePlace(New_ListCases, i);

			}
		}
	}
	return New_ListCases;
};
Case* SortAll(Case*& New_ListCases, int IndikZapolnenia, int& IndikGo) {
	do {
		cout << "Отобразить все дела по дате и времени - 1, отобразить дела по приоритету  - 2." << endl;
		cout << "Для возврата в предыдущее меню нажмите 0" << endl;
		EnterDigit(IndikVvoda2, digit, i);
		system("cls");
		IndikGo = 0;
		if (IndikVvoda2 < 1 || IndikVvoda2>2) {IndikGo = 1; break;}
		else if (IndikVvoda2 == 2) {SortByPriority (New_ListCases, IndikZapolnenia); system("cls"); ShowOnlySort(New_ListCases, IndikZapolnenia); }
		else if (IndikVvoda2 == 1){ SortByDate(New_ListCases, IndikZapolnenia); system("cls"); ShowOnlySort(New_ListCases, IndikZapolnenia);
	}
	} while (IndikVvoda2 > 0 && IndikVvoda2 < 3);
	return New_ListCases;
};
Case* ChangeCasePlace(Case*& New_ListCases, int i) {
	Case temp = New_ListCases[i];
	New_ListCases[i] = New_ListCases[i + 1];
	New_ListCases[i + 1] = temp;
	return New_ListCases;
};
Case* CopyAfterShow(Case*& ListCases, Case*& New_ListCases, int sizeArr, int IndikZapolnenia, int i, int A, int B, int C) {
	New_ListCases[IndikZapolnenia];
	int z = 0;
	if (i == 0) {
		for (j = 0; j < sizeArr; j++) {
			if (B == ListCases[j].y.month && C == ListCases[j].y.year) {
				New_ListCases[z].name = ListCases[j].name;
				New_ListCases[z].priority = ListCases[j].priority;
				New_ListCases[z].description = ListCases[j].description;
				New_ListCases[z].y.day = ListCases[j].y.day;
				New_ListCases[z].y.month = ListCases[j].y.month;
				New_ListCases[z].y.year = ListCases[j].y.year;
				New_ListCases[z].y.hour = ListCases[j].y.hour;
				New_ListCases[z].y.minute = ListCases[j].y.minute;
				z++;
			}
		}
	}
	else {
		int m = A;
		do {
			for (j = 0; j < sizeArr; j++) {
				if (m == ListCases[j].y.day && B == ListCases[j].y.month && C == ListCases[j].y.year) {
					New_ListCases[z].name = ListCases[j].name;
					New_ListCases[z].priority = ListCases[j].priority;
					New_ListCases[z].description = ListCases[j].description;
					New_ListCases[z].y.day = ListCases[j].y.day;
					New_ListCases[z].y.month = ListCases[j].y.month;
					New_ListCases[z].y.year = ListCases[j].y.year;
					New_ListCases[z].y.hour = ListCases[j].y.hour;
					New_ListCases[z].y.minute = ListCases[j].y.minute;
					z++;
				}
			}
			++m; --i;
		} while (i > 0);
	}
	return New_ListCases;
};
