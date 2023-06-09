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

// 풀이1 - product객체배열 사용 (생성자 사용x)
//  -> static currentNum이란 변수로 지금까지 작성된 상품이 몇개인지에 대한 정보를 저장, 이를 이용해 객체배열에 올바른 index에 값을 입력하고 참조할 수 있게 조치
//     -> (구현 시도) 길이가변적 동적배열을 구현하려 했으나.. 
//         1. realloc과 new 연산자의 호환성이 지극히 낮음 + copy를 써서 해결하려고 했으나 string쪽이 제대로 읽지를 못하고, parameter로 들어갈 에러남..
//         2. tmp 배열과 copy를 통해, 어찌어찌 성공했는데 
//            -> if{}안에서 delete를 거니까 오류가 뜨는 이유를 물어보고, 
//               -> 객체배열을 해제하는거니 delete[]로 해야 했음
//            -> 기존에 선언된 포인터에 new 생성자로 동적배열해놓고, new연산자 사용해 더 큰 배열크기로 재선언해도 realloc이나 vector를 쓴 효과가 내는데 별 문제 없는게 맞는지 상관없는지 물어보기
//               -> 상관없지만, 가급적 동적 해제후 다시 할당하는 방법을 쓰는걸 추천. 단, 재할당된 경우 기존 데이터는 지워짐

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
	// 현재 등록된 상품수, 일련번호(현재 등록된 상품수를 받을 예정), 상품명, 제조사, 가격
	static int currentNum;
	int num;
	string name;
	string manufacturer;
	int price;

public:

	~Product() {};

	// 상품 클래스의 멤버변수 초기화를 담당하는 함수 (여기서는 생성자에 관해 부모생성자 상속 및 호출은 생각하지 않는걸로..)
	void init(string _name, string _manufacturer, int _price, int _year, int _month, int _day) {

		num = ++currentNum;
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

	// get함수 : 일련번호(static), 상품명, 제조사, 가격
	static int getCurrentNum() {
		return currentNum;
	}

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
		cout << "일련번호 : " << num << endl;
		cout << "상 품 명 : " << name << endl;
		cout << "제조업체 : " << manufacturer << endl;
		cout << "가    격 : $ " << price << endl;
		cout << "제조일자 : " << getYear() << "년 " << getMonth() << "월 " << getDay() << "일" << endl;
		cout << endl;
	}
};

// 현재 제품번호 부여용 초기화
int Product::currentNum = 0;

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

	// 기본 배열 크기
	int defaultSize = 1;

	// Product 객체배열 메모리에 동적할당 후, 그 시작 주소를 받는 Product 클래스포인터 변수
	//  -> (질문1) calloc, realloc 쓰니까 string이 개판임.. string c언어 문법 호환문제? 
	Product* item = new Product[defaultSize];
	//Product* item = (Product*) calloc(sizeof(Product), defaultSize);


	// Product* tmp;

	while (flag != 1) {

		// 이번 loop에 입력할 상품의 수
		int inputNum = 0;

		cout << "입력할 제품의 갯수는? : " << endl;
		cin >> inputNum;
		while (cin.get() != '\n');

		for (int i = 0; i < inputNum; i++) {

			cout << endl << "일련번호 " << Product::getCurrentNum() + 1 << "번 등록을 시작합니다!" << endl;

			// 만약 처음에 준 배열이 꽉 찼다 치면, 공간 재할당
			//  -> 객체배열 임시복사해서 또 늘리는 식으로 가자.. (잘 안된다)
			if (Product::getCurrentNum() + 1 > defaultSize) {

				//[c언어식 구현 흔적]
				//defaultSize *= 2;
				//item = (Product*) realloc(item, sizeof(Product) * defaultSize);

				int newDefaultSize = defaultSize * 2;

				// 동적배열 구현위해 copy를 위해 미리 할당해 놓은 객체배열
				Product* tmp = new Product[newDefaultSize];
				copy(item, item + defaultSize, tmp);

				// 동적할당한게 객체배열이니, delete를 쓸때도 배열[]을 지우라고 제대로 써줘야 작동함
				delete[] item;

				item = new Product[newDefaultSize];
				copy(tmp, tmp + defaultSize, item);

				// 동적할당한게 객체배열이니, delete를 쓸때도 배열[]을 지우라고 제대로 써줘야 작동함
				delete[] tmp;

				defaultSize = newDefaultSize;
			}

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

			// 입력된 데이터를 바탕으로 해당 객체배열 index에 저장된 객체포인터가 가리키는 Product 객체의 멤버변수들 초기화
			item[Product::getCurrentNum()].init(name, manufacturer, price, year, month, day);

			cout << " ->> (알림) 제품등록이 완료되었습니다. (상품명 : " << item[Product::getCurrentNum() - 1].getName() << ")" << endl;

		}

		cout << endl << " (주의) 등록횟수만큼 등록 완료\n          ->> 계속 등록하시겠습니까? (종료하고 싶으시면 1을 눌러주세요) : " << endl;
		cin >> flag;
	}

	// 종료 후 등록한 상품정보 조회 (staic 변수로 객체배열 index 조회)
	for (int i = 0; i < Product::getCurrentNum(); i++) {
		item[i].showInfo();
	}

	return 0;
}