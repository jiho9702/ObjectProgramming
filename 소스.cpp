#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };


/*
 * Ŭ���� �̸�: Account
 * Ŭ���� ����: Entity Ŭ����
 */

class Account
{
private:
	int accID;
	int balance;
	char* cusName;

public:
	Account(int ID, int money, char* name); //�⺻������
	Account(const Account& ref);  //���������

	int GetAccID() const;
	void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
	~Account();
};

Account::Account(int ID, int money, char* name)
	: accID(ID), balance(money)
{
	cusName = new char[strlen(name) + 1];
	strcpy_s(cusName, (strlen(name) + 1), name);
}

Account::Account(const Account& ref)
	: accID(ref.accID), balance(ref.balance)
{
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy_s(cusName, (strlen(ref.cusName) + 1), ref.cusName);
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)
{
	balance += money;
}

int Account::Withdraw(int money)
{
	if (balance < money)
		return 0;

	balance -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "����ID: " << accID << endl;
	cout << "��  ��: " << cusName << endl;
	cout << "��  ��: " << balance << endl;
}

Account::~Account()
{
	delete[]cusName;
}


/*
 * Ŭ���� �̸�: AccountHandler
 * Ŭ���� ����: ��Ʈ��(Control) Ŭ����
 */

class AccountHandler
{
private:
	Account* accArr[100];
	int accNum;

public:
	AccountHandler();
	void ShowMenu(void) const;
	void MakeAccount(void);
	void DepositMoney(void);
	void WithdrawMoney(void);
	void ShowAllAccInfo(void) const;
	~AccountHandler();
};

void AccountHandler::ShowMenu(void) const
{
	cout << "-----Menu------" << endl;
	cout << "1. ���°���" << endl;
	cout << "2. ��    ��" << endl;
	cout << "3. ��    ��" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}

void AccountHandler::MakeAccount(void)  //������� ������ �����ϴ� �Լ��̴�.
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[���°���]" << endl;
	cout << "����ID: ";	cin >> id;
	cout << "��  ��: ";	cin >> name;
	cout << "�Աݾ�: ";	cin >> balance;
	cout << endl;

	accArr[accNum++] = new Account(id, balance, name);
	//accArr�� Account�� �����Ͱ�ü �迭�̹Ƿ� �����Ǵ� ��ü���� �������� �����ϰ�
	// �� ��ü�� �ּҰ��� �����ϴ� �迭�̴�.
	//new�� ���� AccountŬ������ �����ڰ� ȣ��ȴ�.
	//������ ��ü�� �ּҸ� accArr[accNum]������ �����ϰ� accNum�� ���� 1 ������Ų��.
}

void AccountHandler::DepositMoney(void)  //����ID�� �Աݾ��� �Է��ϴ� �Լ��̴�.
{
	int money;
	int id;
	cout << "[��    ��]" << endl;
	cout << "����ID: ";	cin >> id;
	cout << "�Աݾ�: ";	cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]�� ����� �ּҰ� ����Ű�� ��ü�� getaccid ����Լ��� �����Ѵ�.
			//����Լ����� ��ȯ�Ǵ� ���� id�� ���ٸ�
			//�Ʒ��� ������ �������ش�.
		{
			accArr[i]->Deposit(money);
			//accArr[i]�� ����� �ּҰ� ����Ű�� ��ü�� deposit ����Լ��� 
			//money���� �Ű������� �־��ش�.
			cout << "�ԱݿϷ�" << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

void AccountHandler::WithdrawMoney(void)  //����id�� ��ݾ��� �Է¹޴� �Լ�
{
	int money;
	int id;
	cout << "[��    ��]" << endl;
	cout << "����ID: ";	cin >> id;
	cout << "��ݾ�: ";	cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]�� ����� �ּҰ� ����Ű�� ��ü�� getaccid ����Լ�����
			//��ȯ�Ǵ� ���� id�� ���ٸ�
			//�Ʒ��� ������ �������ش�.
		{
			if (accArr[i]->Withdraw(money) == 0)
				//withdraw�Լ��� money�Ű������� �־ ��ȯ�Ǵ� ���� 0�̶��
			{
				cout << "�ܾ׺���" << endl << endl;
				//�ܾ� ������ ������ش�.
				return;
			}

			cout << "��ݿϷ�" << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

AccountHandler::AccountHandler() : accNum(0)
//AccountHandler��ü�� �����Ҷ� �ƹ��͵� �������� �ʾ�����
//�� �����ڸ� �����ϰ� accNum�� 0���� �ʱ�ȭ ���ش�.
{  }

void AccountHandler::ShowAllAccInfo(void) const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		//accArr[i]�� ����� �ּ��� showaccinfo����Լ��� �����Ͽ� �������ش�.
		cout << endl;
	}
}

AccountHandler::~AccountHandler()  //�Ҹ���
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
	//�������� ������ Account�� ������ ����� �迭�� �ּҰ��� ���ҷ� ������
	//������ �迭 accArr[i]�� ����������Ѵ�.
	//class�� ����� �����ͷ� ���� ������ �޸𸮻� �����ֱ� ������ ��������Ѵ�.
}


/*
 * ��Ʈ�� Ŭ���� AccountHandler �߽����� ����� main �Լ�
 */

int main(void)
{
	AccountHandler manager;
	int choice;

	while (1)
	{
		manager.ShowMenu();
		cout << "����: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case MAKE:
			manager.MakeAccount();
			break;
		case DEPOSIT:
			manager.DepositMoney();
			break;
		case WITHDRAW:
			manager.WithdrawMoney();
			break;
		case INQUIRE:
			manager.ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout << "Illegal selection.." << endl;
		}
	}

	return 0;
}