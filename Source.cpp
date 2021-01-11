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
	cout << "������ N: "; cin >> N;

	Student* p = new Student[N];

	int ispec, mid1;
	Spec spec1;
	string prizv;
	int found;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� �������������" << endl;
		cout << " [4] - �������� ������������� �� ���� �����" << endl;
		cout << " [5] - ������� ����� �������� �� ������������, �������� �� ������� �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "������ [2], ��� �������� ���������" << endl;
			break;
		case 4:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 5:
			cout << "������ ����� ������:" << endl;
			cout << "������������(0 - ���������� �� ��������, 1 - ������� ��������, 2 - Գ���� �� �����������, 3 - �����������, 4 - ��������� �����):  ";
			cin >> ispec;
			spec1 = (Spec)ispec;

			cin.get();
			cin.sync();

			cout << " �������: "; getline(cin, prizv);
			cout << " ������� ���: "; cin >> mid1;
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec1, mid1)) != -1)
				cout << "�������� �������� � �������: " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}


void Create(Student* p, const int N)
{
	int spec1;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " �������: "; cin >> p[i].prizv;
		cout << " �� ���.: "; cin >> p[i].rikNar;
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ������������(0 - ���������� �� ��������, 1 - ������� ��������, 2 - Գ���� �� �����������, 3 - �����������, 4 - ��������� �����): ";
		cin >> spec1;
		p[i].spec = (Spec)spec1;
		cout << " ������ � ������: "; cin >> p[i].physics;
		cout << " ������ � ����������: "; cin >> p[i].math;

		switch (p[i].spec)
		{
		case ME:
			cout << " ������ � ��������� : "; cin >> p[i].ped;
			break;

		case MF:
			cout << " ������ � ��������� : "; cin >> p[i].ped;
			break;

		case FI:
			cout << " ������ � ��������� : "; cin >> p[i].ped;
			break;

		case KN:
			cout << " ������ � ������������� : "; cin >> p[i].prog;
			break;

		case INF:
			cout << " ������ � ��������� ������ : "; cin >> p[i].cMethod;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "==================================================================================="
		<< endl;
	cout << "| � | ������� | г�.���. | ���� | ������������ | Գ���� | ���������� | 3�� ������� |"
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
	cout << "| � | ������� | г�.���. | ���� | ������������ | Գ���� | ���������� | 3�� ������� |"
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