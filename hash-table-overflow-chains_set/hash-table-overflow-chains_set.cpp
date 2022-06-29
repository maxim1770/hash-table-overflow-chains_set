#include <iostream>
#include <windows.h>
#include <ctime>
#include <string>
using namespace std;


class Hash_table_Chains
{
	int Size;
	int Capacity;
	struct Node
	{
		int Key;//����
		int Value;//�������� 
		Node* next;//���� ��������� �������� � ������, �� ������ � �������
	};
	Node** Mas; //������ ��������

public:
	// ���-������� ��� ��������� �����
	int Hash(int X)
	{
		return X % Capacity;
	};
	Hash_table_Chains(int new_capacity = 1000)//����������� 
	{
		Capacity = new_capacity;
		Size = 0;
		Mas = new Node * [Capacity];
		for (int i = 0; i < Capacity; i++)Mas[i] = nullptr;
	};
	~Hash_table_Chains()//������������� 
	{
		Clear();
		delete[] Mas;
	};
	Hash_table_Chains(const Hash_table_Chains& table)//����������� ����������� 
	{
		Capacity = table.Capacity;
		Size = table.Size;
		Mas = table.Mas;
		for (int i = 0; i < Capacity; i++)
		{
			Mas[i] = nullptr;
			if (table.Mas[i])
			{
				Node* p = table.Mas[i];
				Node* q = Mas[i];
				Mas[i] = new Node;
				while (p)
				{
					q->Value = p->Value;
					q->Key = p->Key;
					q->next = p->next;
					q = q->next;
					p = p->next;
				}
			}
		}
	};

	void Clear()
	{
		for (int i = 0; i < Capacity; i++)
		{
			Node* cur = Mas[i];
			while (cur) //���� ���� 
			{
				Node* prev = cur;
				cur = cur->next;
				delete prev;
			}
			Mas[i] = nullptr;
		}
		Size = 0;
		Capacity = 0;
	};

	void Print()
	{
		for (int i = 0; i < Capacity; i++)
		{
			Node* cur = Mas[i];
			if (cur) {
				cout << "������ " << i << endl;
				while (cur)
				{
					cout << "�������� " << cur->Value << endl;
					cout << "���� " << cur->Key << endl;
					cur = cur->next;
					if (cur)cout << endl;
				}
				cout << endl;
			}
		}
	};

	void Insert(int new_Key, int new_Value)//������� ���������� � ��� �������
	{
		int index = Hash(new_Key);
		Node* cur = Mas[index];
		while (cur)
		{
			if (cur->Key == new_Key)
			{
				cur->Key = new_Key;
				cur->Value = new_Value;
				return;
			}
			cur = cur->next;
		}
		Node* cur1 = new Node;
		cur1->Key = new_Key;
		cur1->Value = new_Value;
		cur1->next = Mas[index];
		Mas[index] = cur1;
		Size++;
	};

	void mult(Hash_table_Chains* A, Hash_table_Chains* B)
	{
		for (int i = 0; i < A->return_Capacity(); i++)//�������� �� ���� 1 �������
		{
			if (A->Mas[i])//���� �� �����
			{
				Node* cur = A->Mas[i];
				while (cur)//���������� �� ��� ����
				{
					if (B->Find(cur->Value))Insert(cur->Value, cur->Value);//���� ����� �� ������� ���� �� 2 �������, �� ������� ��� � ����� �������
					cur = cur->next;
				}
			}
		}
	}

	bool Delete(int Key)//������� ��������
	{
		if (Find(Key))
		{
			int index = Hash(Key);
			Node* cur = Mas[index];//�������
			Node* pre = nullptr;//���������� 
			while (cur->next)
			{
				if (cur->Key == Key)
				{
					if (pre == nullptr)Mas[index] = cur->next;
					else pre->next = cur->next;
					free(cur);//=0
					return 1;
				}
				pre = cur;
				cur = cur->next;
			}
		}
	};

	bool Find(int Key)
	{
		int index = Hash(Key);
		if (Mas[index])
		{
			Node* cur = Mas[index];
			while (cur)
			{
				if (Key == cur->Key) return 1;
				cur = cur->next;
			}
		}
		return 0;
	};

	bool isEmpty()//�������� �� ������� 
	{
		for (int i = 0; i < Capacity; i++)
			if (Mas[i])return 0;
		return 1;
	};

	int return_Size() { return Size; };
	int return_Capacity() { return Capacity; };
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int new_size;
	cout << "������� ����������� ������� 1: "; cin >> new_size;
	Hash_table_Chains Table1(new_size);
	cout << "��������� ��������� 1:" << endl;
	for (int i = 0; i < new_size; i++)
	{
		int new_var; cin >> new_var;
		Table1.Insert(new_var, new_var);
	}
	cout << "������ ���������:" << endl
		<< "����� �� �����..." << endl;
	Table1.Print();
	cout << endl;
	system("pause");//������� ��� ������ ��� �����������
	system("CLS");//������� �������
	cout << "������� ����������� ������� 2: "; cin >> new_size;
	Hash_table_Chains Table2(new_size);
	cout << "��������� ��������� 2:" << endl;
	for (int i = 0; i < new_size; i++)
	{
		int new_var; cin >> new_var;
		Table2.Insert(new_var, new_var);
	}
	cout << "������ ���������:" << endl
		<< "����� �� �����..." << endl;
	Table2.Print();
	cout << endl;
	system("pause");
	system("CLS");
	Hash_table_Chains Table3(Table1.return_Capacity() + Table2.return_Capacity()); //�������� ����� ���� (���� 1+2 ����)
	Table3.mult(&Table1, &Table2);//���������� ����� �������
	cout << "�������� ����� ���������:" << endl;
	Table3.Print();


	Table1.Clear();
	Table2.Clear();
	Table3.Clear();
	cout << endl << endl;
	system("pause");
	return 1;
}