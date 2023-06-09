//  - 포인터변수 상수화
//     : 포인터변수가 가지는 특정 자료형의 데이터가 저장된 위치 주소나 이를 역참조 값이 수정될 수 없도록, 대입 연산을 금지하는 성질을 가지게 조치하는 것
//        -> (중요) const를 포인터변수 앞에 붙이냐? 뒤에 붙이냐?에 따라 의미가 달라짐
// 
//        1. const가 자료형 앞에 선언 (const 자료형* 포인터변수명 = 주소값; )
//             : 포인터에 기록된 주소값에 위치한 변수였던 영역을 역참조하여 접근했을 시, 초기화 이후 변경할 수 없는 상수로 선언하겠다는 의미
//               (= 상수화 할 변수를 직접 선언하지 않고, 포인터의 주소값을 통한 간접접근으로 제시하여 일반상수를 선언했다고 이해하면 편함)
//                  -> 단! 역참조를 통한 수정을 배제함 != 해당 변수에 직접 접근하여 수정을 배제함
// 
//               # 포인터변수 역참조한 일반변수 상수화 표기법 (const 자료형 변수명 = 값 유사함)
//                  : const 자료형* 포인터변수명 = 주소값; 
// 	             
//                    ex) int const_int = 91;
//                        const int* const_p1 = &const_int;      <- *const_p1을 상수화 = const_int의 상수화 = 포인터변수를 통해 일반변수 상수화를 한 것과 같음
//                        (x) *const_p1 = 1; 
// 
//               # const 자료형* 포인터변수명 = 주소값;  VS  const 자료형 변수명 = 값
//                  -> (공통점) 둘 다 특정 영역을 초기값 이후 변경 불가능 하도록 만들었다는 점
//                     (차이점) 둘 중 하나만 골라서 특정 영역을 상수화시켰다고, 직접 수정이나 역참조 수정을 한꺼번에 다 막아주진 않음
//                               -> 두 방법을 통한 수정을 전부 막고 싶으면, 일반변수나 포인터나 다 상수화해서 선언해줘야함 
// 
//        2. const가 자료형 뒤에 선언 (자료형* const 포인터변수명 = 주소값; )
//             : 포인터에 기록된 주소값 자체를 초기화 이후 수정할 수 없는 상수로 선언하겠다는 의미
// 
//               # 포인터변수 상수화 표기법
//                  : 자료형* const 포인터변수명 = 주소값; )
// 	             
//                    ex) int const_int = 91;
//                        int* const const_p1 = &const_int;      <- const_p1에 저장된 const_int 주소값 변경 불가능
//                        (x) const_p1 = &another_int; 
//
//        3. const가 자료형 앞, 뒤에 선언 (const 자료형* const 포인터변수명 = 주소값; )
//             : 1, 2의 특성 모두를 적용한다는 의미 (= ??? : 포인터에 저장된 주소값도 수정금지고, 그거 역참조한 값 수정도 금지야!)
// 
//               # 포인터변수 자체와 그 역참조값까지 상수화 표기법
//                  : const 자료형* const 포인터변수명 = 주소값; )
// 	             
//                    ex) int const_int = 91;
//                        const int* const const_p1 = &const_int;      <- const_p1에 저장된 const_int 주소값 변경 불가능 + 역참조한 *const_p1의 값 변경 불가능
//                        (x) const_p1 = &another_int; 
//                        (x) *const_p1 = 1; 

// 포인터변수의 상수화 예시 코드
int main() {

    int a = 5, b = 10, c = 15, dummy = 0;

    // 1. const가 자료형 앞에 선언
    //  : 포인터에 기록된 주소값에 위치한 변수였던 영역을 역참조하여 접근했을 시, 초기화 이후 변경할 수 없는 상수로 선언하겠다는 의미
    //     -> 단! 그렇다고 변수 a의 직접 접근을 통한 수정까지 막아주진 않음
    const int* p1 = &a;

    // [p1이 불가능한 것]
    //  -> 역참조를 통한 값 수정은 불가능!
    *p1 = 60; 

    // [p1이 가능한 것]
    //  -> p1이 저장한 주소값 수정
    p1 = &dummy;

    // 이건 그냥 별개로 가능함 (포인터변수 상수화랑 아무 상관 없음)
    a = 100;

    // 2. const가 자료형 뒤에 선언 
    //  : 포인터에 기록된 주소값 자체를 초기화 이후 수정할 수 없는 상수로 선언하겠다는 의미
    int* const p2 = &b;

    // [p2이 불가능한 것]
    //  -> p2이 저장한 주소값 수정
    p2 = &dummy;

    // [p1이 가능한 것]
     //  -> 역참조를 통한 값 수정은 가능!
    *p2 = 60;

    // 3. const가 자료형 앞, 뒤에 선언
    //  : 포인터에 저장된 주소값인 &c도 수정금지고, 그거 역참조한 변수 c의 값 15의 수정도 금지
    const int* const p3 = &c;

    // [p3이 불가능한 것 = 역참조 수정, 주소값 수정 전부 불가능]
    p3 = &a; //error
    *p3 = 60; //error

    return 0;
}
