﻿﻿﻿// 클래스 상속(class inheritance) 
//  : 기존에 존재하는 class의 모든 멤버속성들을 물려받고
//     -> 이를 베이스로 새로운 기능(= 함수)이나 속성(= 데이터)을 추가하여 확장된 새로운 클래스를 구현이 가능한 객체지향언어의 특성
//         -> 참고로 부모의 멤버함수의 경우는 오버라이드하여 새로 작성이 가능함


//   # 상속 이해 필수 용어
//      1. 부모 클래스 (base, super, parent class)
//          : 어떤 클래스가 상속관계를 통해 특정 클래스의 멤버속성의 기반이 되는 경우에 상위 클래스로 분류될때 붙여지는 이름
//            (= 베이스, 상위, 슈퍼, 기초 class 라고도 불림)

//      2. 자식 클래스(derived, sub, child class)
//         : 어떤 클래스가 상속관계를 통해 특정 클래스의 멤버속성의 기반으로 새롭게 작성되는 경우에 하위 클래스로 분류될때 붙여지는 이름
//            (= 파생, 하위 클래스 라고도 불림)


//   # 자식 클래스의 구성
//      = 부모 클래스의 모든 멤버 + 자식클래스 추가 멤버 ( 속성 : data + 기능 : function )


//   # 상속 관계에 놓인 클래스 호출시, 부모와 자식 클래스 호출 순서
//      : (중요!) 자식 class 기반 객체를 생성자를 통해 호출하여 힙영역에 동적할당 생성하면? 
//         -> 그 기반이 되는 부모클래스까지 모두 생성되어 메모리 할당이 이뤄져야 하며, 반드시 자식클래스보다 먼저 구성될 수 밖에 없는 stack 구조로 구성
// 
//             ex) 대충 아이언맨이 기본 장갑에 추가 장갑이나 슈트를 덧대는 식으로 헐크버스터로 합체 구성하는걸 생각하자
// 
//                 1. 자식 class 접근                                        <- 헐크버스터 모드 진입
//                 2. 부모 class 접근                                        <- 기본 베이스 슈트 찾기
//                 3. 부모 class 기반 객체 생성                               <- 기본 슈트부터 착용 완료
//                     -> (중요!) 다중상속이면 먼저 선언한 부모class부터 호출!  
//                 4. (3을 기반으로) 자식 class 기반 객체로 확장하여 생성       <- 서서히 상위단계 슈트나 장갑을 장착 및 합체하여, 헐크버스터 파츠까지 장착
//                 5. 자식 class 기반 객체 소멸                               <- 헐크버스터 외장장갑부터 퍼지
//                 6. 부모 class 기반 객체 소멸                               <- 가장 마지막에 기본슈트 해제
//                 7. 만약 생성자를 통한 동적 할당 시, 소멸자 작동!             <- 헐크버스터 사용자를 데이터베이스에서 권한까지 삭제

// 단일상속 예시 및 자식 class 객체 생성, 소멸 과정 예시2
//  : Base 클래스을 부모 클래스로 삼아 상속관계를 통해 만들어진 Derived 클래스 
//    -> 생성자 오버로딩 된 녀석, 그 생성과정을 보자 .. (중요) 사실 결론은 부모 FILO
#include <iostream>
using namespace std;

// 부모 클래스 Base
class Base {

    // private이라 Base 자신을 제외한 모든 {}에서 호출 및 참고 불가
    // (중요) 부모클래스의 멤버가 private인건 원래부터 자식이 어떻게 해볼 수 없음!
    //  -> _base는 후손 클래스라도 사실상 건들수 없는 부모의 절대영역
private:
    int _base;

public:
    Base() : _base(20) {
        cout << "default 부모 class 객체 생성" << endl;
    }

    ~Base() {
        cout << "부모 class 객체 소멸" << endl << endl;
    }

    // Base 생성자 함수 오버로딩1
    Base(int n) : _base(n) {
        cout << "parameter 1개 부모 class 객체 생성" << endl;
    }

    void ShowBaseData() {
        cout << _base << endl;
    }
};


// 상속 관계에 놓인 class의 형식
//  -> Class 클래스명 : 접근제어자 부모클래스명1 {  내용   }

// 자식 클래스 Derived
class Derived : public Base {

    // private이라 Derived 자신을 제외한 모든 {}에서 호출 및 참고 불가
private:
    int _derived;

public:
    Derived() : _derived(30) {
        cout << "default 자식 class 객체 생성" << endl;
    }

    ~Derived() {
        cout << "자식 class 객체 파생 소멸" << endl;
    }

    // Derived 생성자 함수 오버로딩1 (parameter 1개)
    Derived(int n) : _derived(n) {
        cout << "parameter 1개 자식 class 객체 생성" << endl;
    }

    // Derived 생성자 함수 오버로딩2 (parameter 2개)
    //  -> 초기화리스트를 통해 부모 Base 생성자 함수로 부모 객체부터 생성
    Derived(int n1, int n2) : Base(n1), _derived(n2) {
        cout << "parameter 2개(부모클래스가 1번째 가져가서 생성자에 사용) 자식 class 객체 생성" << endl;
    }

    void ShowDerviedData() {
        ShowBaseData(); cout << _derived << endl;
    }
};

int main() {
    // case1 : 자식 class default생성자 사용해 객체 만듦
    Derived dr1;
    dr1.ShowDerviedData();
    cout << endl << endl;

    // case2 : 자식 class 생성자 parameter 1개 사용 객체 만듦
    Derived dr2(12);
    dr2.ShowDerviedData();
    cout << endl << endl;

    // case3 : 자식 class 생성자 parameter 2개 사용해 객체 만듦
    Derived dr3(23, 24);
    dr3.ShowDerviedData();
    cout << endl << endl;

    return 0;
}


// [1. 자식 class default생성자 사용해 객체 만듦]

// default 부모 class 객체 생성
// default 자식 class 객체 생성
// 20
// 30

// [2. 자식 class 생성자 parameter 1개 사용 객체 만듦]

// default 부모 class 객체 생성
// parameter 1개 자식 class 객체 생성
// 20
// 12

// [3. 자식 class 생성자 parameter 2개 사용 객체 만듦]

// parameter 1개 부모 class 객체 생성
// parameter 2개(부모클래스가 1번째 가져가서 생성자에 사용) 자식 class 객체 생성
// 23
// 24

// 자식 class 객체 파생 소멸
// 부모 class 객체 소멸

// 자식 class 객체 파생 소멸
// 부모 class 객체 소멸

// 자식 class 객체 파생 소멸
// 부모 class 객체 소멸