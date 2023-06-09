// 클래스 상속(class inheritance) 
//  : 기존에 존재하는 class의 모든 멤버속성들을 물려받고
//     -> 이를 베이스로 새로운 기능(= 함수)이나 속성(= 데이터)을 추가하여 확장된 새로운 클래스를 구현이 가능한 객체지향언어의 특성
//         -> 참고로 부모의 멤버함수의 경우는 오버라이드하여 새로 작성이 가능함


//   # 상속의 유형별 분류
//     1. 단일 상속(single inheritance)
//         : 부모 클래스가 1개인 경우의 자식 클래스의 상속 


//   # 클래스간 상속관계를 적용 할 수 있는 조건 
//      : A가 자손, B가 부모로 간주 (= B class를 상속해서, A 클래스 만들기 가능한 논리구조)
//         -> (핵심) 다중 상속 ㅈ같으니까, is만 있는거로 간주하는게 정신건강에 이로움! 
// 
//      1. A is B (= 이다)
//         : 개별 존재 개체들을 요소의 단위 기준으로 놓고, 그들을 구분하는 개념들을 세세하게 나누고, 포괄적인 개념 <-> 개체 중 어디에 더 가까운지를 기준으로 상속관계를 만듦
// 
//           -> 부모 클래스 B로 표기되는 경우가 많은 CLASS
//               : 대분류에 해당하는 개념일수록 상위클래스 (= 모든 실체를 포괄하는 단 하나의 개념이 가장 최고 선조 클래스)
// 
//           -> 자식 클래스 A로 표기되는 경우가 많은 CLASS
//               : 소분류에 해당하는 개념일수록 하위클래스 (= 실체하는 것은 가장 후손에 해당하는 클래스)
// 
//      
//           ex) 학생은 사람이다 (= 사람 class를 상속해서, 학생 클래스 만들기 가능)
//               사과는 과일이다
//               토끼는 동물이다
// 
//           ex) is 상속 관계도 예시 (<-> Has 상속 관계도)
//               -> (중요!) is 기반의 상속관계는 모든 class의 조상 역할을 하는 class가 하나 있고, 확장된 개념들이 자손으로 주렁주렁 달리는 식으로 관계트리가 이뤄짐
//
//                            과일(최선조)
//                        -------------------
//                     복숭아             파충류 
//                  --   --  --        --   --   --
//                천도  백도 천도     캠밸  머루  거봉     


//   # 상속 관계에 놓인 클래스 호출시, 부모와 자식 클래스 호출 순서
//      : (중요!) 자식 class 기반 객체를 생성자를 통해 호출하여 힙영역에 동적할당 생성하면? 
//         -> 그 기반이 되는 부모클래스까지 모두 생성되어 메모리 할당이 이뤄져야 하며, 반드시 자식클래스보다 먼저 구성될 수 밖에 없는 stack 구조로 구성
// 
//             ex) 대충 아이언맨이 기본 장갑에 추가 장갑이나 슈트를 덧대는 식으로 헐크버스터로 합체 구성하는걸 생각하자
// 
//                 1. 자식 class 접근                                           <- 헐크버스터 모드 진입
//                 2. 부모 class 접근                                           <- 기본 베이스 슈트 찾기
//                 3. 부모 class 기반 객체 생성                                 <- 기본 슈트부터 착용 완료
//                     -> (중요!) 다중상속이면 먼저 선언한 부모class부터 호출!  
//                 4. (3을 기반으로) 자식 class 기반 객체로 확장하여 생성       <- 서서히 상위단계 슈트나 장갑을 장착 및 합체하여, 헐크버스터 파츠까지 장착
//                 5. 자식 class 기반 객체 소멸                                 <- 헐크버스터 외장장갑부터 퍼지
//                 6. 부모 class 기반 객체 소멸                                 <- 가장 마지막에 기본슈트 해제
//                 7. 만약 생성자를 통한 동적 할당 시, 소멸자 작동!             <- 헐크버스터 사용자를 데이터베이스에서 권한까지 삭제



// 단일상속 예시 및 자식 class 객체 생성, 소멸 과정 예시1
//  : Person 클래스을 부모 클래스로 삼아 상속관계를 통해 만들어진 student 클래스 
//    -> 학생(= 자식) is 사람(= 부모). 
#include <iostream>
#include <cstring>

using namespace std;

// 부모 클래스 Person
class Person {

    // private이라 Person 자신을 제외한 모든 {}에서 호출 및 참고 불가
    // (중요) 부모클래스의 멤버가 private인건 원래부터 자식이 어떻게 해볼 수 없음!
    //  -> _base는 후손 클래스라도 사실상 건들수 없는 부모의 절대영역
private:
    char* name_;
    int age_;

public:

    // 부모클래스 Person의 생성자
    Person(char* name, int age) {

        // char 문자열 배열의 주소값인 name을 받으면, 그걸 동적할당해서 문자열을 저장할 공간을 힙영역에 동적할당하고, string 라이브러리 함수인 strcpy_s로 문자열 깊게 복사
        int len = strlen(name) + 1;
        name_ = new char[len];
        strcpy_s(name_, strlen(name) + 1, name);

        age_ = age;

        cout << "부모 class 객체 생성 완료\n";
    }

    ~Person() {
        delete[] name_;
        cout << "부모 class 객체 소멸 완료\n";
    }

    void ShowPersonInfo() { cout << "name :" << name_ << "\nage :" << age_ << endl; }
};

// 상속 관계에 놓인 class의 형식
//  -> Class 클래스명 : 접근제어자 부모클래스명1 {  내용   }

// 자식 클래스 Student
class Student : public Person {

    // private이라 Student 자신을 제외한 모든 {}에서 호출 및 참고 불가
private:
    int student_id_;

public:

    // 자식 class 생성자와 초기화리스트 방법으로 함께하는 부모 class 생성자 
    //   : 자식 class 생성자의 정의부 실행전에, 자식의 기반인 부모class의 생성자 함수를 먼저 호출하는데 일부 parameter를 사용하여 부모 객체를 생성하고 부모의 멤버변수를 초기화하는데 사용
    //      -> 그 부모class도 자신의 부모가 존재하는 경우, 부모의 생성자도 마찬가지로 자신의 부모 생성자를 초기화 리스트(Initialize List) 방식으로 호출하면, 마찬가지로 함수 stack 이 쌓이며, 결국 최선조의 객체가 먼저 생성됨
    //         -> 그렇게 [최후손 class 선언부 -> ... -> 최선조 객체의 선언부, 정의부 실행 -> ... -> 최후손 class 정의부 실행] 패턴대로 생성자 함수가 실행된 결과 자식 class객체가 탄생함
    //             ex) graduate 선언부 -> student 선언부 -> human 선언부, 정의부 실행 -> student 정의부 실행 -> graduate 정의부 실행

    // Class 클래스명 : 접근제어자 부모클래스명 {   클래스명(int param1, .... ,  int paramN) : 부모클래스명1(param1...)   }
    //  -> student 클래스의 parameter 중 _name, _phone은 선언부에서 부모클래스인 human의 생성자 함수를 실행해야 Person 클래스 객체를 생성하는데 사용되고, 그 이후 student 클래스 객체의 생성에 나머지 parameter가 들어감 
    //      -> 실제 자식 class 객체는 로는 부모 class 객체가 먼저 만들어지고 그걸 기반으로 보강되는 구조인 이유

    // 자식클래스 생성자 작성시 부모 생성자의 어떤 생성자 함수가 관련되는지 상속관계를 선언해 놔야함
    //  -> 자식 클래스 student는 부모클래스의 생성자가 기반이 되기에, 부모객체부터 생성 후 거기에 자식의 멤버들을 구성하는 구조
    Student(int sid, char* name, int age) : Person(name, age) {
        student_id_ = sid;
        cout << "자식 class 객체 생성 완료\n";
    }

    ~Student() {
        cout << "자식 class 객체 생성 완료\n";
    }

    void ShowStdInfo() {
        cout << "Student number :" << student_id_ << endl;

        // 부모로 부터 ShowPersonInfo()의 멤버함수 또한 이어받기에 사용가능
        //  -> 오버라이드 하면 자식 자신의 방식대로 사용 가능
        this->ShowPersonInfo();
    }
};

int main() {

    // 자식클래스 Student 생성자를 호출하게 되면? 부모가 먼저 호출? 자식이 먼저 호출?
    Student std_1(20230000, (char*)"michelin", 20);

    // ShowStdInfo() public 영역의 멤버함수로 main()에서 호출 가능
    std_1.ShowStdInfo();

    return 0;
}

// ---------------------------------  <- 생성 (부모가 먼저 호출, 생성)
// 부모 class 객체 생성 완료
// 자식 class 객체 생성 완료
// ---------------------------------  <- 실행
// Student number : 20230000
// name : michelin
// age : 20
// ---------------------------------  <- 소멸 (자식이 먼저 소멸)
// 자식 class 객체 소멸 완료
// 부모 class 객체 소멸 완료
// ---------------------------------