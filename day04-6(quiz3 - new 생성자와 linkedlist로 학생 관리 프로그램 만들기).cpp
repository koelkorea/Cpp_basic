// new, delete를 이용한 c++의 동적할당, 해제 기능으로 'linked list'를 통해 다음의 기능을 가진 코드를 작성해라
// 1. 학생 정보 등록
// 2. 학생 정보 삭제
// 3. 학생 정보 전체 리스트 출력
// 4. 전체삭제
// 5. 종료
// -> 메뉴선택하여 실행하기

#include <iomanip>    // setw() 자리수 출력
#include <cstring>    
#include <iostream>

using namespace std;

// 구조체 STU : 학생 개개인의 개인정보... 
//  - 이름 : 문자열(string 아니고, char 배열로 받기에 char 포인터변수)
//  - 전화번호 : 문자열(string 아니고, char 배열로 받기에 char 포인터변수)
typedef struct STU {
	char* name;
	char* phoneNumber;
}STU;

typedef STU NodeElement;

// 구조체 Node : 학생 정보 구조체인 STU를 데이터로 받는 linkedList... 단위 Node
//  - value : STU 구조체 (포인터 아님 = 구조체 자체를 멤버로 둠)
//  - link  : 다음 데이터가 위치한 노드의 주소를 둔 Node구조체 포인터 변수
struct Node {

	// (중요) new Node로 하면 멤버변수인 구조체도 메모리에 자동으로 할당됨
	NodeElement value;
	Node* link;
};

// (중요) 구조체명*& 변수명 = 구조체의 포인터타입의 레퍼런스 변수 (= 과거 c에서 어떤 타입의 포인터를 저장하는 n중 포인터 변수와 용도가 비슷)
//   -> why using this????
//       : 구조체의 주소값을 가지는 특정 포인터변수가 상태를 공유(= 동기화)하는 변수를 paramter로 넣을 수 있음 
//        (= 함수의 파라미터는 call by value로 복사가 원칙이지만.. 이렇게 하면 파라미터로 들어온 변수가 레퍼런스 변수이기에 원본도 같이 변화가 동기화 되는 call by reference 형식이 되는데.. 단지 이걸 포인터변수에도 적용한 것 뿐)
//         -> (중요) 이렇게 하면 , 함수 내에서 변수명 = NULL 이런식으로 대입을 해도, 원본 데이터에 변화가 적용됨 
//            (= return이 필요한 타입명 적용하지 않고, void형식으로 모든것을 함수 안에서 끝낼 수 있음)
//            (= 과거 c에서 2중 포인터 변수의 1중 역참조 값으로 NULL을 직접 대입하거나 해당하는 타입의 다른 변수의 주소값을 놨던 것과 비슷한데, 더 단순한 구조로 사용이 가능해진것)
bool InsertNode(Node*& head, NodeElement data);
bool DeleteNode(Node*& head, int deleteNodenum);
bool DeleteAll(Node*& head);
void PrintMenu(int& menu);
int PrintList(Node*& head);

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

// 학생정보 LinkedList를 시작할 head
//  : 소속 STU없음.. link는 1번째 노드가 있으면 그 노드주소.. 없으면 NULL
Node* LinkedHead = new Node;

int main() {

	// ----------------------------------[Node 구조체 안의 STU구조체는 new Node;를 하면 자동으로 같이 힙 영역에 할당되는가 실험]-----------------------------

	// 각 입력값 크기에 해당하는 동적크기를 갖는 char배열을 만들기 위해, 일단 입력값 자체를 받기 위한 정적 배열을 하나 만들어 준다
	char* inputName = (char*)"헤드";
	char* inputPhoneNumber = (char*)"전화번호";

	// 이름의 문자열 길이만큼 동적할당 (NULL 문자도 포함해야..)
	LinkedHead->value.name = new char[strlen(inputName) + 1];

	// 정적배열에 입력된 이름 문자열을 새로 적은 문자열로 1자씩 복사
	for (int j = 0; j <= strlen(inputName); j++) {
		LinkedHead->value.name[j] = inputName[j];

	}

	// 전화번호의 문자열 길이만큼 동적할당 (NULL 문자도 포함해야..)
	LinkedHead->value.phoneNumber = new char[strlen(inputPhoneNumber) + 1];

	// 정적배열에 입력된 전화번호 문자열을 새로 적은 문자열로 1자씩 복사
	for (int j = 0; j <= strlen(inputPhoneNumber); j++) {
		LinkedHead->value.phoneNumber[j] = inputPhoneNumber[j];
	}

	cout << "-------Node 구조체 안의 STU구조체는 new Node;를 하면 자동으로 같이 힙 영역에 할당되는가?--------- " << endl << endl;
	cout << " ->> new STU없이 선입력된 LinkedList 시작점에 데이터 입력" << endl;
	cout << " ->> (name) : " << LinkedHead->value.name << ", (phoneNumber) : " << LinkedHead->value.phoneNumber << endl << endl;
	cout << "-------[결론] 안에 구조체가 있는 구조체를 new로 생성하면, 내부 구조체도 알아서 잘 생성해줌--------" << endl << endl;

	//--------------------------------------------------------------------------------------------------------------------------------------------------------

	// LinkedList의 head의 link는 일단 NULL 초기화.. (등록된 학생정보가 없음)
	LinkedHead->link = NULL;

	// 메뉴수행 번호 받아줄 변수 (초기값 0)
	int menuNum = 0;

	while (1) {

		cout << "1. 학생 정보 등록" << endl;
		cout << "2. 학생 정보 삭제" << endl;
		cout << "3. 학생 정보 전체 리스트 출력" << endl;
		cout << "4. 학생 정보 전체삭제" << endl;
		cout << "5. 프로그램 종료" << endl << endl;
		cout << "메뉴번호 선택 :";

		cinput(menuNum);
		PrintMenu(menuNum);

	}

	return 0;

}

// 메뉴 입력화면에서 메뉴를 받으면 조건부로 기능진행
void PrintMenu(int& menu) {

	// 1. 학생정보 입력기능
	if (menu == 1) {

		// -----------------------------------------------------[학생 정보 STU 생성 & 작성]--------------------------------------------------------------------------
		// 학생 수 입력 받기
		int studentCnt;

		cout << endl << "[1번. 학생개인정보 입력기능]" << endl << endl << "새로 입력할 학생 수를 입력해주십쇼 : ";
		cinput(studentCnt);

		// 각 입력값 크기에 해당하는 동적크기를 갖는 char배열을 만들기 위해, 일단 입력값 자체를 받기 위한 정적 배열을 하나 만들어 준다
		char inputName[100];
		char inputPhoneNumber[100];

		// 입력할 학생 수만큼 이름, 전화번호 입력받기
		for (int i = 0; i < studentCnt; i++) {

			// STU 구조체 포인터변수에 new 연산자를 통한 메모리에 입력한 학생수에 해당하는 만큼의 크기를 갖는 STU구조체 배열을 할당하고, 그 시작주소를 포인터변수에 대입 
			// (= 힙 영역에 생성된 STU 구조체의 주소값을 call by reference 형식의 레버런스 변수로 넘겨줌)
			//  : 자료형 * 변수명 = new 자료형;   <->   malloc(byte 크기), calloc 등을 쓰던 과거아 다름
			STU* student = new STU;

			cout << " ->> " << setw(3) << i + 1 << "번째로 입력할 학생의 '이름'과 '전화번호'를 입력해주세요 : ";
			cin >> inputName >> inputPhoneNumber;

			//------------------------------[Node에 연결된 STU 구조체에 입력한 이름, 전번 옮기기]---------------------------

			// 이름의 문자열 길이만큼 동적할당 (NULL 문자도 포함해야..)
			student->name = new char[strlen(inputName) + 1];

			// 정적배열에 입력된 이름 문자열을 새로 적은 문자열로 1자씩 복사
			for (int j = 0; j <= strlen(inputName); j++) {
				student->name[j] = inputName[j];

			}

			// 전화번호의 문자열 길이만큼 동적할당 (NULL 문자도 포함해야..)
			student->phoneNumber = new char[strlen(inputPhoneNumber) + 1];

			// 정적배열에 입력된 전화번호 문자열을 새로 적은 문자열로 1자씩 복사
			for (int j = 0; j <= strlen(inputPhoneNumber); j++) {
				student->phoneNumber[j] = inputPhoneNumber[j];
			}

			//--------------------------------------------------------------------------------------------------------------

			// 입력 메서드에 입력한 학생 해당 정보와, Linked의 시작인 head노드의 시작주소값을 가지는 Node포인터변수를 param으로 수행
			//  -> 성공 실패 여부에따라 알림 달라지게 함
			if (InsertNode(LinkedHead, *student) == true) {
				cout << "\t>>>> (알림) 학생 " << i + 1 << "의 정보가 입력 완료.." << endl << endl;
			}
			else {
				cout << "\t>>>> (알림) 학생 " << i + 1 << "의 정보가 입력 실패!" << endl << endl;
			}

			// STU 구조체는 삭제
			delete student;
		}

	}
	// 2. 특정 학생의 정보 삭제기능
	else if (menu == 2) {

		// 리스트의 학생 수 받음
		int deleteFlag = PrintList(LinkedHead);

		// 리스트의 학생이 1명 이상 존재할 시, 개별학생 삭제기능 수행!
		if (deleteFlag != 0) {

			// 삭제할 학생이 몇번째에 있을지 받을 변수
			int deleteNodenum = 0;

			cout << endl << "[2번. 개별 학생정보 입력기능]" << endl;

			// 최소한 1번은 삭제할 학생의 index 입력받는데, 그 값이 0보다 크면서, deleteFlag의 값보다 같거나 커야함 (= 삭제 가능 학생index를 입력받으라는 말)
			do{
				cout << endl << " ->> 몇 번째 학생의 정보를 지우고 싶으신가요? : ";
				cinput(deleteNodenum);

				if (deleteNodenum <= 0 && deleteNodenum > deleteFlag) {
					cout << endl << "\t>>>> (경고) 0보다 크고, 존재하는 학생번호의 값을 입력해주세요!" << endl;
				}

			}while (deleteNodenum <= 0 && deleteNodenum > deleteFlag);

			// 삭제 메서드에  Linked의 시작인 head노드의 지울 학생이 몇번째에 있는지 여부를 param으로 수행
			//  -> 성공 실패 여부에따라 알림 달라지게 함
			if (DeleteNode(LinkedHead, deleteNodenum) == true) {

				cout << "\t>>>> (알림) " << deleteNodenum << "번째 학생 정보 삭제 완료!" << endl << endl;
			}
			else {
				cout << "\t>>>> (알림) " << deleteNodenum << "번째 학생 정보 삭제 실패!" << endl << endl;
			}
		}
		// 리스트의 학생이 0명이면, 삭제 불가 판정
		else {
			cout << "\t>>>> (알림) 현재 삭제할 학생 정보가 존재하지 않음!" << endl << endl;
		}
	}
	// 3. 전체 학생정보 출력기능
	else if (menu == 3) {

		// 리스트의 학생이 1명 이상 존재할 시, 성공문구 출력
		if (PrintList(LinkedHead) != 0) {

			cout << "\t>>>> (알림) 학생 정보 출력완료!" << endl << endl;
		}
		else {
			cout << "\t>>>> (알림) 학생 정보가 없습니다.." << endl << endl;
		}

	}
	// 4. 전체 학생정보 삭제기능
	else if (menu == 4) {

		// 삭제 수행 여부에 따라, 성공문구 출력
		if (DeleteAll(LinkedHead) == true) {

			cout << "\t>>>> (알림) 학생 정보 전체 삭제완료!" << endl << endl;
		}
		else {
			cout << "\t>>>> (알림) 학생 정보가 없거나, 전체 삭제 실패!" << endl << endl;
		}

	}
	else if (menu == 5) {

		// 종료 전에 전역변수인 LinkedList의 head에 할당된 메모리 해제를 잊지마라 
		delete LinkedHead;
		cout << "\t>>>> (알림) 학생관리 프로그램을 종료합니다..." << endl << endl;

		exit(0);
	}

}

// 1. 개별 학생의 이름, 전화번호를 가진 STU구조체를 데이터로 삼는 Node를 생성하고 그 노드를 linked리스트에 추가 
bool InsertNode(Node*& head, NodeElement data) {

	bool flag = false;

	// 입력할 이름, 전화번호가 NULL이 아니면, 입력과정 진행
	if (data.name != NULL && data.phoneNumber != NULL) {

		// 현재 linkedlist의 마지막으로 붙은 노드를 찾기위한 Node 포인터변수 tmp (head노드의 주소값으로 초기화)
		Node* tmp = head;

		// head에 붙어있는 노드를 의미하는 tmp->link를 시작으로 NULL이 나올때까지, tmp의 Node주소값을 tmp->link로 갱신
		while (tmp->link != NULL) {

			tmp = tmp->link;
		}

		// 추가해줄 STU 구조체(new Node 할 때 같이 생성)를 가지는 linkedlist 생성
		Node* studentLinked = new Node;

		// 새로 만든 Node의 주소값를 기존 마지막의 link에 대입
		tmp->link = studentLinked;

		// 새로 추가할 학생의 이름, 전화번호를 Node와 연결된 STU에 추가 + 추가된 노드의 다음 Node 주소값은 NULL
		studentLinked->value.name = data.name;
		studentLinked->value.phoneNumber = data.phoneNumber;
		studentLinked->link = NULL;

		flag = true;
	}

	return flag;
}

// 2. 특정 학생의 정보들 모두를 삭제하는 기능(그 학생정보가 있는 Node를 메모리 해제)
bool DeleteNode(Node*& head, int deleteNodenum) {

	bool flag = true;

	// 사용자가 0을 입력했을때, 에러를 피하도록 조치 (물론 애초에 0 < deleteNodenum < print에 찍힌 return값 이도록 조치)
	if (deleteNodenum == 0) {

		// 경고문과 함께 false입력
		cout << "\t>>>> (경고!) 0번째 데이터는 존재하지 않는 데이터이므로 삭제할 수 없습니다." << endl;
		return flag = false;
	}

	// 노드의 주소값을 찍을 커서로서 linkedList용 노드포인터
	Node* tmpForCursor = head;

	// 삭제 노드의 주소값을 저장할 linkedList용 노드포인터 (NULL로 초기화 시켜놓음.. tmpForCursor를 직접 삭제 안하는 이유는.. 그 초기값이 head라 예측못한 경우의 수에 head가 지워질수 있음)
	Node* tmpForDelete = NULL;

	// linkedList 헤드 = 0, deleteNodenum에 해당하는 횟수만큼 link를 타서, tmpForDelete값을 찍을 예정
	for (int i = 0; i < deleteNodenum; i++) {

		// 삭제할 노드의 위치 전에 위치한 노드에 도달할 경우?
		if (i == deleteNodenum - 1) {

			// 삭제할 노드의 주소를 받을 tmpForDelete에 삭제노드의 주소를 대입(삭제 전 노드의 link에 입력된 주소값)
			tmpForDelete = tmpForCursor->link;

			// 삭제할 노드의 다음 노드가 마지막 노드가 아니라면? (= 삭제할 노드가 리스트의 중간에 위치)
			if (tmpForCursor->link->link != NULL) {

				// 삭제 전 노드의 link값을 삭제노드 다음 노드의 주소로 대입
				tmpForCursor->link = tmpForCursor->link->link;
			}
			// 삭제할 노드의 다음 노드가 마지막 노드라면? (= 삭제할 노드가 리스트의 끝에 위치)
			else {

				// 삭제할 노드 이전노드의 link를 NULL로 저장
				tmpForCursor->link = NULL;
			}

		}

		// 헤드 = 0이고, 루프가 끝날때, 다음 노드로 갱신
		tmpForCursor = tmpForCursor->link;
	}

	// 삭제노드의 주속값이 들어간 tmpForDelete의 주소를 이용해 메모리 해제
	delete tmpForDelete;


	return flag;
}

// 3. 전체 학생정보 출력 (몇 명의 학생이 존재하는지를 반환)
int PrintList(Node*& head) {

	// 현재 리스트의 학생수를 받을 변수
	int studentNum = 0;

	// head를 시작으로 linked 리스트를 순회하며 노드의 주소값을 갱신받을 Node포인터 변수
	Node* tmp = head;

	// 노드에 연결된 다른 노드의 주소값인 link가 NULL이 나오는 녀석까지 노드의 주소값을 받을 변수
	while (tmp->link != NULL) {

		tmp = tmp->link;

		// 학생값의 갱신은 ++연산자로..
		cout << endl << "학생 " << setw(3) << ++studentNum << "번 정보" << endl;
		cout << " ->> 이름 : " << tmp->value.name << endl;
		cout << " ->> 전화번호 : " << setw(3) << tmp->value.phoneNumber << endl;
	}

	cout << endl;

	// 몇명의 학생정보가 있는지 갱신
	return studentNum;
}

// 4. 전체 학생정보 삭제
bool DeleteAll(Node*& head) {

	bool flag = false;

	// head가 가리키는 link의 주소값의 다른 노드의 주소값이 시작
	Node* tmpForNext = head->link;
	Node* tmpForDelete = NULL;

	// 애초에 1번째 노드가 존재하지 않는다면, 메서드를 시작하지도 않고, link가 NULL인 끝노드에 도착하면 중단
	//  -> 1개 이상의 학생정보 노드가 존재한다면? 순회하면서 삭제
	while (tmpForNext != NULL) {

		// 삭제 가능함으로 true로
		flag = true;

		// 현재 노드를 삭제할 노드의 주소를 받을 포인터변수에 대입
		tmpForDelete = tmpForNext;
		
		// 커서노드는 link에 연결된 다음 노드의 주소값을 대입
		tmpForNext = tmpForNext->link;

		// 삭제노드를 메모리에 할당된 영역까지 해제헤서 삭제
		delete tmpForDelete;
	}

	// 다 삭제했으면, head의 link 멤버를 null로..
	head->link = NULL;

	return flag;

}