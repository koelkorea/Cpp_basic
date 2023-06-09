﻿﻿﻿// 클래스 상속(class inheritance) 
//  : 기존에 존재하는 class의 모든 멤버속성들을 물려받고
//     -> 이를 베이스로 새로운 기능(= 함수)이나 속성(= 데이터)을 추가하여 확장된 새로운 클래스를 구현이 가능한 객체지향언어의 특성
//         -> 참고로 부모의 멤버함수의 경우는 오버라이드하여 새로 작성이 가능함


//   # 상속 관계에 놓인 class의 형식
//      : Class 클래스명 : 접근제어자 부모클래스명1, ... ,  접근제어자 부모클래스명n {  내용  }
//         -> 다중 상속의 경우 ','를 사용, 상속받을 기초 클래스를 여러 개 가능하나..  권장 X

//             ex) 단일상속
//                 class Student : public Person {           <- Student 클래스는 Person 클래스를 부모로 두고 상속 
//                 
//                    private:
//                        int student_id_;
//                 
//                    public:
//                        Student(int sid, char* name, int age) : Person(name, age) {  내용  }
//                 };


//             ex) 다중상속 
//                 class School : public Buliding, public ClassRoom, public Office {           <- School 클래스는 Buliding, ClassRoom, Office 클래스를 모두 부모로 두고 상속 
//                 
//                 };


//   # 접근제어자 (복습)
//      : 클래스의 멤버변수의 변조 방지를 위해 코드 실행 중 접근위치에 따라 멤버변수의 값에 접근여부에 따른 제어권한을 의미 
//         -> 사실상 public과 private만 널리 사용되며, 이들이 getter setter 디자인패턴과 연관 

//        - private     : 해당 클래스 내에서만 해당 클래스의 멤버들에 접근할 수 있음 
//                        (= 오로지 클래스 선언시 미리 작성한 멤버변수 초기화 값과 멤버함수를 통해서만 값의 변조가 가능 == 은닉이 필요한 속성에 적용하게 됨)
//      
//        - protected   : 상속관계에서 해당 클래스의 멤버들에 접근허용 
//                        (= 해당 클래스와 상속관계에 있는 클래스가 선언될 때라면, 해당 멤버변수의 값에 접근 및 변조나 멤버함수의 사용이 가능) 
//      
//        - public      : 어디서든 일단 멤버변수나 멤버메서드가 호출되거나 참조되면, 언제라도 해당 멤버변수의 값에 접근 및 변조나 멤버함수의 사용을 허용함 (사실상 자동문임)


// class 상속 관계 작성 예시 + 접근제어자에 따른 class 멤버변수 및 함수 접근권한 체크 예시코드
#include <iostream>

using namespace std;

// 부모 class
class Base {

    // private : 선언된 클래스 안에서만 접근 가능 (자식 새끼도 접근 불가한, 부모의 영역)
private:
    int a;

    // protected : 선언된 클래스 + 상속된 클래스 안에서 접근 가능 (요즘은 은닉화 개념 복잡해지는거도 싫어서, 그냥 protect 안 씀)
protected:
    int b;

    // public : 어디서나 접근 가능.. 
    //  -> 요즘 보통 private이건, protect건 멤버변수는 public 영역에 get set형식으로 접근가능하게 하는 방식을 씀 
public:
    void Set_a(int _a) { a = _a; }
    void Set_b(int _b) { b = _b; }
    int Get_a() { return a; }
    int Get_b() { return b; }
};

//   # 상속 관계에 놓인 class의 형식
//      : Class 클래스명 : 접근제어자 부모클래스명 {  내용  }

// 자식 class (부모 class Base를 상속함)
//  -> public 상속이므로, 부모의 pretected 이하 변수에 대해서 접근권한 똑같이 설정 
class Derived : public Base {

private:
    int c;

public:

    void Set(int _a, int _b, int _c) {

        // c는 자식 클래스 자신의 변수이므로 접근 가능
        c = _c;

        // (중요) a는 부모 클래스의 private 멤버로 상속받아도 접근 불가능
        //  -> 따라서 a를 초기화 해주는 Set_a함수를 통해 a값 초기화
        // a = _a;
        Set_a(_a);

        // b는 부모 클래스의 protected 멤버변수
        //  -> 자식클래스인 Derived는 상속 받는 입장이라 접근 가능
        b = _b;
    }

    int Mul() {

        // (중요) a는 private 멤버로 상속받아도 접근 불가능
        //  -> Get_a()로 대체
        // return a * b * c;   
        return Get_a() * b * c;
    }
};

int main() {

    // 자식class 기반 객체 생성
    //  -> 그 이전에 부모class에게서 상속된 멤버까지 모두 먼저 메모리가 할당된 후 생성됨
    Derived child;

    // (중요) main()에서 접근 및 호출 가능한 멤버는 해당 class의 멤버중 public만 가능함!

    // 자식클래스의 set()메서드는 public 영역에 존재하기에, main()에서도 언제나 호출가능
    child.Set(5, 4, 5);


    // main() 함수는 부모클래스와 연관X 
    //  -> protect로 상속받은 변수 b, 자신의 private영역에 정의된 멤버변수 c에 대한 접근 X
    // child.b = 1;
    // child.c = 1;

    // 자식클래스의 Mul()메서드는 public 영역에 존재하기에, main()에서도 언제나 호출가능
    cout << child.Mul() << endl;

    return 0;
}