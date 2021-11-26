#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };


/*
 * 클래스 이름: Account
 * 클래스 유형: Entity 클래스
 */

class Account
{
private:
	int accID;
	int balance;
	char* cusName;

public:
	Account(int ID, int money, char* name); //기본생성자
	Account(const Account& ref);  //복사생성자

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
	cout << "계좌ID: " << accID << endl;
	cout << "이  름: " << cusName << endl;
	cout << "잔  액: " << balance << endl;
}

Account::~Account()
{
	delete[]cusName;
}


/*
 * 클래스 이름: AccountHandler
 * 클래스 유형: 컨트롤(Control) 클래스
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
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void AccountHandler::MakeAccount(void)  //사용자의 정보를 저장하는 함수이다.
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID: ";	cin >> id;
	cout << "이  름: ";	cin >> name;
	cout << "입금액: ";	cin >> balance;
	cout << endl;

	accArr[accNum++] = new Account(id, balance, name);
	//accArr은 Account의 포인터객체 배열이므로 생성되는 객체들을 동적으로 생성하고
	// 그 객체의 주소값을 저장하는 배열이다.
	//new를 통해 Account클래스의 생성자가 호출된다.
	//생성된 객체의 주소를 accArr[accNum]공간에 저장하고 accNum의 값을 1 증가시킨다.
}

void AccountHandler::DepositMoney(void)  //계좌ID와 입금액을 입력하는 함수이다.
{
	int money;
	int id;
	cout << "[입    금]" << endl;
	cout << "계좌ID: ";	cin >> id;
	cout << "입금액: ";	cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]에 저장된 주소가 가리키는 객체의 getaccid 멤버함수를 실행한다.
			//멤버함수에서 반환되는 값이 id와 같다면
			//아래의 문장을 실행해준다.
		{
			accArr[i]->Deposit(money);
			//accArr[i]에 저장된 주소가 가리키는 객체의 deposit 멤버함수에 
			//money값을 매개변수로 넣어준다.
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
}

void AccountHandler::WithdrawMoney(void)  //계좌id와 출금액을 입력받는 함수
{
	int money;
	int id;
	cout << "[출    금]" << endl;
	cout << "계좌ID: ";	cin >> id;
	cout << "출금액: ";	cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]에 저장된 주소가 가리키는 객체의 getaccid 멤버함수에서
			//반환되는 값과 id가 같다면
			//아래의 문장을 실행해준다.
		{
			if (accArr[i]->Withdraw(money) == 0)
				//withdraw함수에 money매개변수를 넣어서 반환되는 값이 0이라면
			{
				cout << "잔액부족" << endl << endl;
				//잔액 부족을 출력해준다.
				return;
			}

			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
}

AccountHandler::AccountHandler() : accNum(0)
//AccountHandler객체를 생성할때 아무것도 적어주지 않았을때
//이 생성자를 실행하고 accNum을 0으로 초기화 해준다.
{  }

void AccountHandler::ShowAllAccInfo(void) const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		//accArr[i]에 저장된 주소의 showaccinfo멤버함수에 접근하여 실행해준다.
		cout << endl;
	}
}

AccountHandler::~AccountHandler()  //소멸자
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
	//동적으로 생성된 Account의 정보가 저장된 배열의 주소값을 원소로 가지는
	//포인터 배열 accArr[i]를 삭제해줘야한다.
	//class를 벗어나도 포인터로 만든 변수는 메모리상에 남아있기 때문에 없애줘야한다.
}


/*
 * 컨트롤 클래스 AccountHandler 중심으로 변경된 main 함수
 */

int main(void)
{
	AccountHandler manager;
	int choice;

	while (1)
	{
		manager.ShowMenu();
		cout << "선택: ";
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