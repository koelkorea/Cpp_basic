// class 객체 포인터 배열
//  : 말그대로 class객체포인터변수로만 이뤄진 배열
//     -> 객체포인터가 여러개 필요한 경우 사용하며, 이는 동적할당되어 생성되는 class객체가 많다는 의미로 받아들일수 있음

//   # (부록) 후기 언어들의 고민 및 아이디어
//      : class 객체배열을 동적으로 길이를 조절 가능하게 하면, 충분히 가변적으로 갯수가 증감하는 객체들을 쉽게 저장이 가능함
//        But! 개념도 복잡해지고, 그를 통해 동적할당된 메모리 영역을 하나하나 다 신경써서 뭘 하기도 ㅈㄴ 귀찮고 짜증남
//         -> (타협점) 포인터 배제하고, list만 동적신축되는 자료구조 class로 신설하자! 
//             : 그냥 동적으로 길이를 신축가능한 어떤 자료형이라도 받는 list 개념을 만들어서, 신축성 갯수가 예상디는 class객체는 여기다 저장하는 걸로 가자..
//               전역으로 쓰고 싶은 class객체 데이터들이 있다면, 걔를 전역변수로 선언하면, 굳이 포인터 쓸 필요 없잖아?
               
#include <iostream>
using namespace std;

class A {

    private:
        int a, b;

    public:

        A(int _a, int _b) {
            a = _a;
            b = _b;
            cout << "생성자 호출\n";
        }
        void Show(int i) {
            cout << "a[" << i << "] : " << "a =  " << a << ", b = " << b << endl;
        }
};

// class객체포인터 배열을 활용하여, class 객체 생성 및 관리, 소멸을 손쉽게 하게 함
int main() {

    A* p[5]; //객체 포인터 배열(포인터 5개 = 4byte * 5개)

    //객체 생성 시 인수 전달
    for (int i = 0; i < 5; i++) p[i] = {
        new A(i, i * 10);
    }

    //객체포인터->멤버함수
    for (int i = 0; i < 5; i++) {
        p[i]->Show(i);
    }
    
    //delete 포인터;
    for (int i = 0; i < 5; i++) {
        delete p[i]; 
        cout << "동적메모리 해제(객체)\n";
    }
    return 0;
}
