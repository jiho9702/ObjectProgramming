#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

void ShowMenu(void);       // 메뉴출력
void MakeAccount(void);    // 계좌개설을 위한 함수
void DepositMoney(void);       // 입    금
void WithdrawMoney(void);      // 출    금
void ShowAllAccInfo(void);     // 잔액조회

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };  //열거형 순서대로 나타나는 상수를 보기 쉽게   #define과 비슷하다.

class Account
{
private:            //private으로 지정해놓으면 클래스 외부에서 접근할 수 없다
	int accID;      // 계좌번호
	int balance;    // 잔    액
	char* cusName;   // 고객이름

public:  //외부에서도 접근이 가능하다.
	Account(int ID, int money, char* name)							
		//멤버변수인 accID, balance, cunName에 접근해서 값을 할당해줄때 필요한 생성자이다.
		: accID(ID), balance(money)									
		// accID = ID  accID에 매개변수로 받아온 ID의 값을 대입해준다
		//balance = money  balance에 매개변수로 받아온 money값을 대입해준다.
	{
		cusName = new char[strlen(name) + 1];						
		//cusName은 포인터 변수로 주소값을 저장할수 있는 character형 변수이다. 
																	
		//이 변수에 new를 사용해서 새로운 character배열을 만들고 그 주소를 넣어준다.
																	
		//char *name은 아래의 makeAccount 함수에서 객체를 생성할때 
																	
		// 문자배열에 의해 생성된 것을 넣어주는데 그 배열의 주소를 *name에 저장한다.
																	
		// 저장된 주소값을 타고 들어가서 name의 길이를 strlen을 통해 반환받는다
																	
		//배열의 길이는 매개변수로 받아온 name배열의 길이를 사용한다.
																	
		//마지막의 null문자까지 계산해서 +1을 해준다.
		
		strcpy_s(cusName, (strlen(name) + 1), name);				
		//strcpy  string copy 문자열 복사함수를 사용해서 name의 문자를 cusName에 복사한다.
	}

	Account(const Account& ref)                                     
		//매개변수로 참조자를 받는 생성자는 복사생성자이다.
																	
		//복사생성자는 클래스를 통해 객체를 생성하고 그 객체에 값을 넣을때 
																	
		//기존에 있던 객체의 값을 복사해서 넣어주고 싶을때 사용한다																	
		
		: accID(ref.accID), balance(ref.balance)					
		//기존에 있던 클래스의 객체를 ref라는 참조자로 받아왔을때 기존 클래스의 별명을 ref라고 하는것과 같다.
																	
		//복사된 값을 넣으려는 객체의 accID에 ref의 accID를 복사해서 넣고
																	
		//복사된 값을 넣으려는 객체의 balance에 ref의 balance를 복사해서 넣어준다.
	{																
		cusName = new char[strlen(ref.cusName) + 1];				
		//cusName은 포인터변수로 주소를 저장하는 변수이다 
																	
		//그러므로 new를 사용해서 character배열을 만들어주고 그 배열의 주소를 cusName에 저장해준다.
																	
		//배열의 크기는 null문자 포함 +1이 된다.
		strcpy_s(cusName, (strlen(ref.cusName) + 1), ref.cusName);
	}

	int GetAccID() const { return accID; }							
	//생성된 객체의 accID의 값을 반환해준다. 
	//이때 const를 앞에 붙이므로써 accID의 값은 바꿀수 없음을 알려준다.

	void Deposit(int money)
	{
		balance += money;
		//생성된 객체의 balance멤버변수에 매개변수로 받아온 money의 값을 더해준다.
	}

	int Withdraw(int money)    // 출금액 반환, 부족 시 0 반환
	{
		if (balance < money)
			// 생성된 객체의 balance에 저장된 값이 매개변수로 받아온 money의 값보다 작다면
			//0을 반환해준다.
			return 0;

		balance -= money;
		//balance의 값에 money의 값을 빼준다.
		return money;
		//출금하려고 한 money값을 반환해준다.
	}

	void ShowAccInfo() const
		//생성된 객체의 정보를 출력해주는 함수이다.
	{
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
	}

	~Account()
		//포인터로된 멤버변수에 배열을 생성했을경우 객체가 클래스를 빠져나가더라도 소멸되지 않는다.
		//따라서 delete를 사용해서 배열을 지워줘야한다.
	{
		delete[]cusName;
	}
};

Account* accArr[100];   // Account 저장을 위한 배열
int accNum = 0;        // 저장된 Account 수

int main(void)
{
	int choice;
	//choice라는 정수형 변수를 생성해준다.

	while (1)
	{
		ShowMenu();
		//ShowMenu 함수를 사용해서 메뉴들을 출력하여 보여준다.
		cout << "선택: ";
		cin >> choice;
		cout << endl;

		switch (choice)
			//enum으로 make = 1, deposit = 2, withdraw = 3, inquire = 4, exit = 5로 지정을 해뒀다.
		{
		case MAKE:
			//1을 누른경우 make의 함수를 실행
			MakeAccount();
			break;
		case DEPOSIT:
			//2를 누른경우 depositmoney의 함수를 실행
			DepositMoney();
			break;
		case WITHDRAW:
			//3을 누른경우 WithdrawMoney의 함수를 실행
			WithdrawMoney();
			break;
		case INQUIRE:
			//4를 누른경우 ShowAllAccInfo의 함수를 실행
			ShowAllAccInfo();
			break;
		case EXIT:
			//5를 누른경우 exit함수를 실행
			return 0;
		default:
			//위의 경우를 벗어난 수를 입력하면 잘못된 선택이라고 출력해주고 다시 입력을 요구한다.
			cout << "Illegal selection.." << endl;
		}
	}

	for (int i = 0; i < accNum; i++)
		delete accArr[i];
		//생성된 객체의 배열은 main문을 종료하더라도 남아있기 때문에 삭제해줘야한다.
	return 0;
}

void ShowMenu(void)
//아래의 출력부분을 실행한다.
{
	cout << "-----Menu------" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void MakeAccount(void)
//계좌를 만들어주는 함수이다.
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID: ";	cin >> id;
	cout << "이  름: ";	cin >> name;
	cout << "입금액: ";	cin >> balance;
	cout << endl;
	//id, name, balance를 입력받는다.

	accArr[accNum++] = new Account(id, balance, name);
	//입력받은 내용들을 Account저장을 위해 만든 포인터배열인 accArr에 넣어준다.
	//ex) accArr[0] = new Account(1, 10, abc)
	//    accArr[1] = new Account(2, 100, efg)
	//와 같이 각각의 배열이 서로다른 객체를 생성하게 된다.
}

void DepositMoney(void)
{
	int money;
	int id;
	cout << "[입    금]" << endl;
	cout << "계좌ID: ";	cin >> id;
	cout << "입금액: ";	cin >> money;
	//money와 id의 값을 입력받는다.

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]의 객체에 들어있는 accID가 내가 입력한 id와 같다면
		{
			accArr[i]->Deposit(money);
			//accArr[i]의 객체가 속한 클래스의 Deposit함수를 수행한다
			//이때 들어가는 매개변수로는 money가 들어간다.
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
	//내가 입력한 id와 accArr[i]에 들어있는 accID가 다르면 위의 문장을 출력한다.
}

void WithdrawMoney(void)
{
	int money;
	int id;
	cout << "[출    금]" << endl;
	cout << "계좌ID: ";
	cin >> id;
	cout << "출금액: ";
	cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
			//accArr[i]객체가 포함한 class의 GetAccID 멤버함수에 접근해서
			//return 받은 값이 id와 같을때
		{
			if (accArr[i]->Withdraw(money) == 0)
				//accArr[i]객체의 클래스에 withdraw함수에 접근해서 money를
				//매개변수로 넣었을때 그 값이 0으로 반환받았으면
				//입금되어있는 금액 즉,accArr[i]에 저장된 balance값이 money보다 작을때
			{
				cout << "잔액부족" << endl << endl;
				//잔액 부족을 출력한다.
				return;
			}

			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
}

void ShowAllAccInfo(void)
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		//accArr[i]의 클래스에 접근해서 showaccinfo함수를 실행해준다.
		cout << endl;
	}
}