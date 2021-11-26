#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

void ShowMenu(void);       // �޴����
void MakeAccount(void);    // ���°����� ���� �Լ�
void DepositMoney(void);       // ��    ��
void WithdrawMoney(void);      // ��    ��
void ShowAllAccInfo(void);     // �ܾ���ȸ

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };  //������ ������� ��Ÿ���� ����� ���� ����   #define�� ����ϴ�.

class Account
{
private:            //private���� �����س����� Ŭ���� �ܺο��� ������ �� ����
	int accID;      // ���¹�ȣ
	int balance;    // ��    ��
	char* cusName;   // ���̸�

public:  //�ܺο����� ������ �����ϴ�.
	Account(int ID, int money, char* name)							
		//��������� accID, balance, cunName�� �����ؼ� ���� �Ҵ����ٶ� �ʿ��� �������̴�.
		: accID(ID), balance(money)									
		// accID = ID  accID�� �Ű������� �޾ƿ� ID�� ���� �������ش�
		//balance = money  balance�� �Ű������� �޾ƿ� money���� �������ش�.
	{
		cusName = new char[strlen(name) + 1];						
		//cusName�� ������ ������ �ּҰ��� �����Ҽ� �ִ� character�� �����̴�. 
																	
		//�� ������ new�� ����ؼ� ���ο� character�迭�� ����� �� �ּҸ� �־��ش�.
																	
		//char *name�� �Ʒ��� makeAccount �Լ����� ��ü�� �����Ҷ� 
																	
		// ���ڹ迭�� ���� ������ ���� �־��ִµ� �� �迭�� �ּҸ� *name�� �����Ѵ�.
																	
		// ����� �ּҰ��� Ÿ�� ���� name�� ���̸� strlen�� ���� ��ȯ�޴´�
																	
		//�迭�� ���̴� �Ű������� �޾ƿ� name�迭�� ���̸� ����Ѵ�.
																	
		//�������� null���ڱ��� ����ؼ� +1�� ���ش�.
		
		strcpy_s(cusName, (strlen(name) + 1), name);				
		//strcpy  string copy ���ڿ� �����Լ��� ����ؼ� name�� ���ڸ� cusName�� �����Ѵ�.
	}

	Account(const Account& ref)                                     
		//�Ű������� �����ڸ� �޴� �����ڴ� ����������̴�.
																	
		//��������ڴ� Ŭ������ ���� ��ü�� �����ϰ� �� ��ü�� ���� ������ 
																	
		//������ �ִ� ��ü�� ���� �����ؼ� �־��ְ� ������ ����Ѵ�																	
		
		: accID(ref.accID), balance(ref.balance)					
		//������ �ִ� Ŭ������ ��ü�� ref��� �����ڷ� �޾ƿ����� ���� Ŭ������ ������ ref��� �ϴ°Ͱ� ����.
																	
		//����� ���� �������� ��ü�� accID�� ref�� accID�� �����ؼ� �ְ�
																	
		//����� ���� �������� ��ü�� balance�� ref�� balance�� �����ؼ� �־��ش�.
	{																
		cusName = new char[strlen(ref.cusName) + 1];				
		//cusName�� �����ͺ����� �ּҸ� �����ϴ� �����̴� 
																	
		//�׷��Ƿ� new�� ����ؼ� character�迭�� ������ְ� �� �迭�� �ּҸ� cusName�� �������ش�.
																	
		//�迭�� ũ��� null���� ���� +1�� �ȴ�.
		strcpy_s(cusName, (strlen(ref.cusName) + 1), ref.cusName);
	}

	int GetAccID() const { return accID; }							
	//������ ��ü�� accID�� ���� ��ȯ���ش�. 
	//�̶� const�� �տ� ���̹Ƿν� accID�� ���� �ٲܼ� ������ �˷��ش�.

	void Deposit(int money)
	{
		balance += money;
		//������ ��ü�� balance��������� �Ű������� �޾ƿ� money�� ���� �����ش�.
	}

	int Withdraw(int money)    // ��ݾ� ��ȯ, ���� �� 0 ��ȯ
	{
		if (balance < money)
			// ������ ��ü�� balance�� ����� ���� �Ű������� �޾ƿ� money�� ������ �۴ٸ�
			//0�� ��ȯ���ش�.
			return 0;

		balance -= money;
		//balance�� ���� money�� ���� ���ش�.
		return money;
		//����Ϸ��� �� money���� ��ȯ���ش�.
	}

	void ShowAccInfo() const
		//������ ��ü�� ������ ������ִ� �Լ��̴�.
	{
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
	}

	~Account()
		//�����ͷε� ��������� �迭�� ����������� ��ü�� Ŭ������ ������������ �Ҹ���� �ʴ´�.
		//���� delete�� ����ؼ� �迭�� ��������Ѵ�.
	{
		delete[]cusName;
	}
};

Account* accArr[100];   // Account ������ ���� �迭
int accNum = 0;        // ����� Account ��

int main(void)
{
	int choice;
	//choice��� ������ ������ �������ش�.

	while (1)
	{
		ShowMenu();
		//ShowMenu �Լ��� ����ؼ� �޴����� ����Ͽ� �����ش�.
		cout << "����: ";
		cin >> choice;
		cout << endl;

		switch (choice)
			//enum���� make = 1, deposit = 2, withdraw = 3, inquire = 4, exit = 5�� ������ �ص״�.
		{
		case MAKE:
			//1�� ������� make�� �Լ��� ����
			MakeAccount();
			break;
		case DEPOSIT:
			//2�� ������� depositmoney�� �Լ��� ����
			DepositMoney();
			break;
		case WITHDRAW:
			//3�� ������� WithdrawMoney�� �Լ��� ����
			WithdrawMoney();
			break;
		case INQUIRE:
			//4�� ������� ShowAllAccInfo�� �Լ��� ����
			ShowAllAccInfo();
			break;
		case EXIT:
			//5�� ������� exit�Լ��� ����
			return 0;
		default:
			//���� ��츦 ��� ���� �Է��ϸ� �߸��� �����̶�� ������ְ� �ٽ� �Է��� �䱸�Ѵ�.
			cout << "Illegal selection.." << endl;
		}
	}

	for (int i = 0; i < accNum; i++)
		delete accArr[i];
		//������ ��ü�� �迭�� main���� �����ϴ��� �����ֱ� ������ ����������Ѵ�.
	return 0;
}

void ShowMenu(void)
//�Ʒ��� ��ºκ��� �����Ѵ�.
{
	cout << "-----Menu------" << endl;
	cout << "1. ���°���" << endl;
	cout << "2. ��    ��" << endl;
	cout << "3. ��    ��" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}

void MakeAccount(void)
//���¸� ������ִ� �Լ��̴�.
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[���°���]" << endl;
	cout << "����ID: ";	cin >> id;
	cout << "��  ��: ";	cin >> name;
	cout << "�Աݾ�: ";	cin >> balance;
	cout << endl;
	//id, name, balance�� �Է¹޴´�.

	accArr[accNum++] = new Account(id, balance, name);
	//�Է¹��� ������� Account������ ���� ���� �����͹迭�� accArr�� �־��ش�.
	//ex) accArr[0] = new Account(1, 10, abc)
	//    accArr[1] = new Account(2, 100, efg)
	//�� ���� ������ �迭�� ���δٸ� ��ü�� �����ϰ� �ȴ�.
}

void DepositMoney(void)
{
	int money;
	int id;
	cout << "[��    ��]" << endl;
	cout << "����ID: ";	cin >> id;
	cout << "�Աݾ�: ";	cin >> money;
	//money�� id�� ���� �Է¹޴´�.

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]�� ��ü�� ����ִ� accID�� ���� �Է��� id�� ���ٸ�
		{
			accArr[i]->Deposit(money);
			//accArr[i]�� ��ü�� ���� Ŭ������ Deposit�Լ��� �����Ѵ�
			//�̶� ���� �Ű������δ� money�� ����.
			cout << "�ԱݿϷ�" << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
	//���� �Է��� id�� accArr[i]�� ����ִ� accID�� �ٸ��� ���� ������ ����Ѵ�.
}

void WithdrawMoney(void)
{
	int money;
	int id;
	cout << "[��    ��]" << endl;
	cout << "����ID: ";
	cin >> id;
	cout << "��ݾ�: ";
	cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]��ü�� ������ class�� GetAccID ����Լ��� �����ؼ�
			//return ���� ���� id�� ������
		{
			if (accArr[i]->Withdraw(money) == 0)
				//accArr[i]��ü�� Ŭ������ withdraw�Լ��� �����ؼ� money��
				//�Ű������� �־����� �� ���� 0���� ��ȯ�޾�����
				//�ԱݵǾ��ִ� �ݾ� ��,accArr[i]�� ����� balance���� money���� ������
			{
				cout << "�ܾ׺���" << endl << endl;
				//�ܾ� ������ ����Ѵ�.
				return;
			}

			cout << "��ݿϷ�" << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

void ShowAllAccInfo(void)
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		//accArr[i]�� Ŭ������ �����ؼ� showaccinfo�Լ��� �������ش�.
		cout << endl;
	}
}