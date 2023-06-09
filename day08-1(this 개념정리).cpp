// this의 의미
//  : 해당 class를 기반으로 하는 객체의 멤버함수를 수행 시, 해당 객체의 멤버변수를 가공하기 위해 호출한 객체의 주소값을 갖게 되는 (숨겨진) '상수 포인터변수'
//     -> 즉, 해당 객체의 멤버변수에 접근 및 가공을 위해서는 해당 객체의 주소값이 필요
//         -> (중요!) 해당 객체를 통해 멤버함수를 호출하는 코드가 발견되면, 컴파일 과정에서 자동으로 그 객체의 주소값인 this가 해당 멤버함수의 parameter로 추가됨 (사용자는 보지 못함)

//   # this가 필요한 이유?
//      : 객체선언 시 멤버변수만 각각 할당하고, 멤버함수는 같은 클래스를 기반으로 한 객체간 공유되기 때문
//        (= 이때 멤버함수 호출하는 객체가 있다면, 해당 클래스를 기반으로 한 어떤 객체가 멤버 함수를 호출했는지를 알아야 해당 객체의 멤버변수들을 가공함)

//   # this의 특성
//     1. 모든 클래스의 멤버함수들은 객체의 주소(this 포인터)를 숨겨진 parameter로 가짐
//         -> 정확히는 컴파일 과정에서 어떤 객체가 멤버함수를 호출하는 코드가 보이면, 그 함수의 parameter에 그 함수를 호출한 객체의 위치가 어딘지를 기록하는 this 포인터가 추가
// 
//     2. 해당 멤버함수가 실행되는 동안에만 스택에 this 포인터가 매개변수로 쌓임 
//         -> 일반 fuction의 동작 원리와 마찬가지임

//   # this포인터를 활용하기 유효한 경우
//      1. 멤버함수의 parameter가 멤버변수와 이름이 같은 경우
//          ex) class B {
//                 int i, j;
//                 void Set(int i, int j) {      <- 각각 멤버변수와 parameter의 이름이 i , j로 같음
//                    this->i = i;               <- this->i 라면 구분이 될 수 있으니 쉽게 해결 가능
//                    this->j = j; 
//                 }

//      2. 멤버함수에서 함수를 호출한 객체를 그 자체를 반환하는 경우
//          -> 하.. 이거 그 객체가 뭔지 내가 어떻게 알아? 라고 안하고
//             -> 해당 클래스 포인터변수 형식으로 객체의 주소값을 받는 this를 역참조한 객체값 *this을 return하면 됨! 


// this가 내부적으로 동작하는 방식이나 과정 주석으로 적어둔 부분
#include <iostream>
using namespace std;

class B {

    private:
        int i, j;

    public:                                         

        // [사용자가 적어둔 멤버함수]                 //         [컴파일러가 변환한 this를 사용한 멤버함수]
        void Set(int _i, int _j) {                  //         void Set(B* const this, int _i, int _j) {        <-  특징1) parameter로 해당 클래스 객체의 주소값 this가 상수 포인터로 들어가있음
            i = _i;                                 //            this->i = _i;                                 <-  특징2) 해당 멤버변수를 접근 및 가공하는 과정에서, 숨겨 가져온 this를 사용해 해당 객체의 멤버변수임을 찾아내서 수정
            j = _j;                                 //            this-> j = _j;
        }                                           //         }

        void Out() {
            cout << i << ", " << j << endl;
        }
};

int main() {
    B ob1, ob2, ob3;

    ob1.Set(1, 10);                                 //         Set(&ob1, 1, 10);       <- 특징3) 맨 앞에 붙여둔 객체명은 사실 특징1)에서 컴파일시 변형된 선언부에 맞춰 this를 위한 parameter값을 위해 객체의 주소값이 들어가도록 변형됨
    ob2.Set(2, 20);                                 //         Set(&ob2, 2, 20);
    ob3.Set(3, 30);                                 //         Set(&ob3, 3, 30);

    ob1.Out();
    ob2.Out();
    ob3.Out();

    return 0;
}
