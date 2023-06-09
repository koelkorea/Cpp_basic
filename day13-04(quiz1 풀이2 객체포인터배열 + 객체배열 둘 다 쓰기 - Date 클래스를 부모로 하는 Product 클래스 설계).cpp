// quiz1 : 상속을 이용한 클래스를 설계하라
//  -> 날짜와 관련된 개념을 설정하는 Date 클래스의 멤버변수와 함수 리스트를 작성하고, 이를 이용해 자식클래스로 Product 클래스를 생성함.. 조건은 다음과 같음

// ★ Date클래스 디자인
//    1. private 멤버변수
//      - 년
//      - 월
//      - 일
//    
//    2. public 멤버 함수
//      - 생성자 - 인수가 없는 기본 생성자를 이용한다.Date()
//      - 년, 월, 일 설정함수 set
//      - 년, 월, 일 리턴함수 get
// 
// ★ Product클래스 디자인 : Date클래스 상속
//    1. private 멤버변수
//      - 상품명
//      - 제조사
//      - 가격
// 
//    2. public 멤버 함수
//      - 생성자 - 인수가 없는 기본 생성자를 이용한다.
//      - SetProduct - 상품명, 제조사, 가격, 년, 월, 일 초기화
//      - 상품명, 제조사, 가격, 제조일자 설정함수 set
//      - 상품명, 제조사, 가격 리턴함수 get
//      - 상품정보 출력 함수


// 풀이2 - 정적 product객체배열 + 정적 product객체포인터배열 사용 (생성자 사용x)
//  -> product객체배열       : 1 while loop당 입력한 product 갯수만큼의 데이터를 저장하는 을 데이터를 저장하는 용도
//  -> product객체포인터배열 : while loop 주차를 index로 한 product 객체배열의 위치정보를 저장하여 product 정보를 출력하기
//  -> 1 while loop당 객체의 개수가 몇개인지는 어떻게 알지?
//      : _msize(포인터) 를 통해 계산하려고 했지만, 에러나서... 그냥 int 배열로 대체함

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Date {

private:
	// 년, 월, 일
	int year, month, day;

public:
	// set함수 : 년, 월, 일 설정함수
	void setYear(int _year) {
		year = _year;
	}

	void setMonth(int _month) {
		month = _month;
	}

	void setDay(int _day) {
		day = _day;
	}

	// get함수 : 년, 월, 일 설정함수
	int getYear() {
		return year;
	}

	int getMonth() {
		return month;
	}

	int getDay() {
		return day;
	}
};

class Product : public Date {

private:
	string name;
	string manufacturer;
	int price;

public:

	~Product() {};

	// 상품 클래스의 멤버변수 초기화를 담당하는 함수 (여기서는 생성자에 관해 부모생성자 상속 및 호출은 생각하지 않는걸로..)
	void init(string _name, string _manufacturer, int _price, int _year, int _month, int _day) {

		name = _name;
		manufacturer = _manufacturer;
		price = _price;

		setDate(_year, _month, _day);
	}

	// set함수 : 상품명, 제조사, 가격, 제조일자
	void setName(string _name) {
		name = _name;
	}

	void setManufacturer(string _manufacturer) {
		manufacturer = _manufacturer;
	}

	void setPrice(int _price) {
		price = _price;
	}

	// 부모클래스 초기화 관련 생성자로 처리 가능하나.. (여기서는 생성자에 관해 부모생성자 상속 및 호출은 생각하지 않는걸로..)
	void setDate(int _year, int _month, int _day) {

		setYear(_year);
		setMonth(_month);
		setDay(_day);
	}

	// get함수 : 상품명, 제조사, 가격
	string getName() {
		return name;
	}

	string getManufacturer() {
		return manufacturer;
	}

	int getPrice() {
		return price;
	}

	// 상품 정보 출력
	void showInfo() {
		cout << endl;
		cout << "상 품 명 : " << name << endl;
		cout << "제조업체 : " << manufacturer << endl;
		cout << "가    격 : $ " << price << endl;
		cout << "제조일자 : " << getYear() << "년 " << getMonth() << "월 " << getDay() << "일" << endl;
		cout << endl;
	}
};

//---------------------------------------------------기존 cin.clear를 발전시킨 메서드 cinput--------------------------------------------
void cinclear() {
	if (cin.fail()) {
		cin.clear();
		while (cin.get() != '\n');
	}
	else while (cin.get() != '\n');
}

void cinput(int& n) {
	while (!(cin >> n)) {
		cinclear();
		cout << "(알림) 입력이 잘못되었습니다. 다시 입력하세요!" << endl << endl;
	}
}

void cinput(char& n) {
	while (!(cin >> n)) {
		cinclear();
		cout << "(알림) 입력이 잘못되었습니다. 다시 입력하세요!" << endl << endl;
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------

int main() {

	cout << "[상품 등록 프로그램]을 작동!" << endl << endl;

	// 종료여부 flag
	int flag = 0;

	// while루프 횟수
	int while_loop = 0;

	// 입력하는 제품 순번
	int product_num = 0;

	// while 1oop을 통해 입력된, product 정보들이 저장된 배열을 배열별로 보관 위해 만든 product 객체 배열
	Product* arr[100];

	// 1 while loop당 입력된 product 객체가 몇개인지 개수 자체를 기록하는 int 배열
	//  -> 원래는 sizeof를 통해 계산하려 했지만 실패하여 이렇게 함..
	int each_loop_input[100] = { 0 };

	while (flag != 1) {

		// while 1 loop당 입력할 product 객체 갯수
		int inputNum = 0;

		cout << "입력할 제품의 갯수는? : " << endl;
		cin >> inputNum;
		while (cin.get() != '\n');

		// while 1 loop당 입력할 product 객체 갯수를 입력받으면, 
		//  -> 그 횟수를 each_loop_input[while 주차]에 입력하여, 제품정보 뽑을때 index로 쓴다
		each_loop_input[while_loop] = inputNum;

		// 이번 while loop에서 입력받을 만큼의 product 객체를 그 숫자만큼의 크기를 가진 객체배열로 생성함
		Product* items = new Product[inputNum];

		// product 정보 입력
		for (int i = 0; i < inputNum; i++) {

			product_num++;

			cout << endl << "제품 " << product_num << "번 등록을 시작합니다!" << endl;

			string name = "";
			string manufacturer = "";
			int price = 0;
			int year = 0;
			int month = 0;
			int day = 0;

			cout << " ->> 상 품 명 : ";
			cin >> name;
			while (cin.get() != '\n');

			cout << " ->> 제조업체 : ";
			cin >> manufacturer;
			while (cin.get() != '\n');

			cout << " ->> 가   격 : ";
			cin >> price;
			while (cin.get() != '\n');

			cout << " ->> 제조일자 (YYYY MM DD 형식으로.. 0은 빼고) : ";
			cin >> year >> month >> day;
			while (cin.get() != '\n');


			items[i].init(name, manufacturer, price, year, month, day);

			cout << " ->> (알림) 제품등록이 완료되었습니다. (상품명 : " << items[i].getName() << ")" << endl;

		}

		// 이번 loop에 입력한 product 정보가 담긴 객체배열의 위치를 기록한 객체포인터를
		//  -> 해당 loop주차의 index에 해당하는 위치의 객체포인터배열 arr에 대입함
		arr[while_loop] = items;

		cout << endl << " (주의) 등록횟수만큼 등록 완료\n          ->> 계속 등록하시겠습니까? (종료하고 싶으시면 1을 눌러주세요) : " << endl;
		cin >> flag;

		// 종료되던 말던 while주차가 끝났음으로 갱신
		while_loop++;
	}

	// while loop 수만큼
	for (int i = 0; i < while_loop; i++) {

		// 해당 while loop에 몇개의 데이터를 입력했는지 기록한 int배열을 참고해서
		for (int j = 0; j < each_loop_input[i]; j++) {

			// 입력한 product들의 정보를 확인
			arr[i][j].showInfo();
		}
	}

	return 0;
}