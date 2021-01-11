#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Spec { ME, MF, FI, INF, KN };

struct Student
{
	string prizv;
	unsigned rikNar;
	int kurs;
	Spec spec;
	int physics;
	int math;

	union
	{
		int prog;
		int cMethod;
		int ped;
	};
};

void Print(Student* p, const int N);
void Create(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec1, const int mid1);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int N;
	cout << "Введіть N: "; cin >> N;

	Student* p = new Student[N];

	int ispec, mid1;
	Spec spec1;
	string prizv;
	int found;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування" << endl;
		cout << " [4] - індексне впорядкування та вивід даних" << endl;
		cout << " [5] - бінарний пошук студента за спеціальністю, прізвищем та середнім балом" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			cout << "введіть [2], щоб побачити результат" << endl;
			break;
		case 4:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "спеціальність(0 - Математика та економіка, 1 - Трудове навчання, 2 - Фізика та інформатика, 3 - Інформатика, 4 - Комп’ютерні науки):  ";
			cin >> ispec;
			spec1 = (Spec)ispec;

			cin.get();
			cin.sync();

			cout << " прізвище: "; getline(cin, prizv);
			cout << " середній бал: "; cin >> mid1;
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec1, mid1)) != -1)
				cout << "Знайдено студента в позиції: " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}


void Create(Student* p, const int N)
{
	int spec1;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; cin >> p[i].prizv;
		cout << " рік нар.: "; cin >> p[i].rikNar;
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність(0 - Математика та економіка, 1 - Трудове навчання, 2 - Фізика та інформатика, 3 - Інформатика, 4 - Комп’ютерні науки): ";
		cin >> spec1;
		p[i].spec = (Spec)spec1;
		cout << " оцінка з фізики: "; cin >> p[i].physics;
		cout << " оцінка з математики: "; cin >> p[i].math;

		switch (p[i].spec)
		{
		case ME:
			cout << " оцінка з педагогіки : "; cin >> p[i].ped;
			break;

		case MF:
			cout << " оцінка з педагогіки : "; cin >> p[i].ped;
			break;

		case FI:
			cout << " оцінка з педагогіки : "; cin >> p[i].ped;
			break;

		case KN:
			cout << " оцінка з програмування : "; cin >> p[i].prog;
			break;

		case INF:
			cout << " оцінка з чисельних методів : "; cin >> p[i].cMethod;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "==================================================================================="
		<< endl;
	cout << "| № | Прізвище | Рік.нар. | Курс | Спеціальність | Фізика | Математика | 3тій предмет |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].rikNar << " "
			<< "| " << setw(11) << left << p[i].kurs
			<< "| " << setw(11) << left << p[i].spec
			<< "| " << setw(11) << left << p[i].physics
			<< "| " << setw(11) << left << p[i].math;
		switch (p[i].spec)
		{
		case ME:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[i].ped << " |" << endl;
			break;
		case MF:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[i].ped << " |" << endl;
			break;
		case FI:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[i].ped << " |" << endl;
			break;
		case INF:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[i].cMethod << " |" << endl;
			break;
		case KN:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[i].prog << " |" << endl;
			break;
		}
	}
	cout << "==================================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	double mid1 = 0, mid2 = 0;
	for (int i0 = 0; i0 < N - 1; i0++) {



		for (int i1 = 0; i1 < N - i0 - 1; i1++)
		{

			if (p[i1].spec == (ME || FI || MF))
				mid1 = (p[i1].physics + p[i1].math + p[i1].ped) / 3;
			else if (p[i1].spec == INF)
				mid1 = (p[i1].physics + p[i1].math + p[i1].cMethod) / 3;
			else
				mid1 = (p[i1].physics + p[i1].math + p[i1].prog) / 3;


			if (p[i1 + 1].spec == (ME || FI || MF))
				mid2 = (p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].ped) / 3;
			else if (p[i1 + 1].spec == INF)
				mid2 = (p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].cMethod) / 3;
			else
				mid2 = (p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].prog) / 3;


			if ((p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].spec == p[i1 + 1].spec &&
					mid1 > mid2)
				||
				((p[i1].spec == p[i1 + 1].spec &&
					mid1 == mid2)) && p[i1].prizv > p[i1 + 1].prizv)
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
		}
	}
}


int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];

	for (int i = 0; i < N; i++)
		I[i] = i;

	int i, j, value, mid1, mid2;

	for (i = 1; i < N; i++)
	{
		value = I[i];

		for (j = i - 1; j >= 0; j--)
		{
			mid1 = (p[I[j]].physics + p[I[j]].math + p[I[j]].ped) / 3;
			mid2 = (p[value].physics + p[value].math + p[value].ped) / 3;

			if (j >= 0 && ((p[I[j]].spec > p[value].spec)
				||
				(p[I[j]].spec == p[value].spec &&
					mid1 > mid2)
				||
				(p[I[j]].spec == p[value].spec &&
					mid1 == mid2 && p[I[j]].prizv > p[value].prizv)))
			{
				I[j + 1] = I[j];
			}
			else
				break;

		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "============================================================================================="
		<< endl;
	cout << "| № | Прізвище | Рік.нар. | Курс | Спеціальність | Фізика | Математика | 3тій предмет |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].rikNar << " "
			<< "| " << setw(11) << left << p[I[i]].kurs
			<< "| " << setw(11) << left << p[I[i]].spec
			<< "| " << setw(11) << left << p[I[i]].physics
			<< "| " << setw(11) << left << p[I[i]].math;

		switch (p[I[i]].spec)
		{
		case ME:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[I[i]].ped << " |" << endl;
			break;
		case MF:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[I[i]].ped << " |" << endl;
			break;
		case FI:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[I[i]].ped << " |" << endl;
			break;
		case INF:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[I[i]].cMethod << " |" << endl;
			break;
		case KN:
			cout << "| " << setw(9) << setprecision(2) << fixed << left
				<< p[I[i]].prog << " |" << endl;
			break;
		}
	}
	cout << "============================================================================================="
		<< endl;
	cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const Spec spec1, const int mid1)
{
	int L = 0, R = N - 1, m;
	int mid;
	do {
		m = (L + R) / 2;
		mid = (p[m].math + p[m].physics + p[m].ped) / 3;
		if (p[m].prizv == prizv && p[m].spec == spec1 && mid == mid1)
			return m;

		if ((p[m].spec < spec1)
			||
			(p[m].spec == spec1 &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}