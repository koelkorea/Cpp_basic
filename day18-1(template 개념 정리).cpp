// 템플릿(Template)
//  : function이나 class의 수많은 overloading 버전들을 개별적으로 작성을 하기 귀찮기에, 포괄적으로 그들의 parameter로 범용적인 자료형이 들어간다고 가정하고 작성한 일종의 공용 양식
//      -> (중요) 템플릿을 작성해두면, 컴파일 시점에서 컴퓨터는 그 템플릿을 참고하여, 적혀있는 function or class멤버들에 대해 모든 자료형에 해당하는 overloading 버전들을 모두 자동으로 쭉 생성해 줌 
//          -> 컴파일 단계에서 function이나 class멤버들을 직접 생성하기에, function나 class에 템플릿을 많이 적용하는 만큼 쓰면 컴파일 속도가 느려짐
//              <-> 컴파일 단계에서 코드를 추가하는 것이기에, 그 이후 프로그램 처리 속도랑은 관계 X


//   # 템플릿의 탄생 배경
//      (기) : 객체지향 프로그래밍(OOP) 패러다임이 대세가 되어, class 객체 자료형을 작성하는 방식에 원칙과 표준이 생김 (표준화, 상속, 다형성, 캡슐화)
//      (승) : 그 중 다형성의 원칙에 따라, 동명의 함수지만 parameter의 종류나 개수가 완전히 같지 않으면 다른 함수로 취급함으로서, 같은 함수를 다양한 경우에서 사용가능하게 해주는 overloading이 널리 쓰이기 시작함
//      (전) : overloading 함수들을 작성하다 보니, parameter에 따른 경우의 수가 뒤지게 많다는 점과 그렇게 작성된 함수들이 정작 내용은 자료형만 바꿔 적용하면 전혀 다른게 없는 경우가 많다는 점을 발견
//      (결) : 일반화 프로그래밍(Generic Programming) 패러다임적 관점을 받아들여, 1번 작성하고 나면 비슷한 내용의 overloading 함수들을 포괄할 수 있는 일타쌍피를 노릴 수 있는 양식을 만들고자 하는 움직임 발생
//               -> 결론 : 그렇게 만들어진 function 작성에 편의성을 제공하는 양식이 '템플릿(Template)' 되시겠다!


//   # (배경지식) 프로그래밍 패러다임
//      : 프로그래밍을 하는데 있어 어떤 가치나 철학에 기준에 둔 방법론을 제시하는 가치관이자 트랜드
// 
//       1. 객체지향 프로그래밍(Objective Oriented Programming)
//           : 데이터로 표현할 어떤 추상적인 대상을 구체적으로 고유 속성과 기능을 가진 객체로 정의하는 식으로 가정한 뒤
//              -> 그렇게 다양한 객체들을 최대한 공통된 속성이나 기능을 가진 카테고리로 묶어서 계보화 시켜 표준화(속성, 기능)한 뒤
//                 -> 검증된 코드의 재사용을 통해 유지보수를 최적화하는데 집중한 [데이터 중점] 방법론
//                     -> (단점) 다양한 자료형 덕분에 overloading 문제 같이 범용코드 짜기가 드럽게 힘듦 + 크고 복잡한 상속 계보가 꼬이면 고치기 어렵다는 단점이 있음
//
//       2. 일반화 프로그래밍(Generic Programming)
//           : 최대한 다양한 자료형을 모두 포괄적으로 처리하는 방향으로 코드를 설계해야 한다는 [알고리즘 중점] 방법론
//              -> 템플릿(Template)은 이러한 일반화 프로그래밍의 사상적 영향을 받아 탄생한 결과물


//   # (중요!) 템플릿 작동하는 과정
//      :  템플릿을 작성해두면, 컴파일 시점에서 컴퓨터는 그 템플릿을 참고하여, 적혀있는 function or class멤버들에 대해 모든 자료형에 해당하는 overloading 버전들을 모두 자동으로 쭉 생성해 줌 
//           -> 미리 class나 function을 작성해둔게 아니고, 컴파일 단계에서 템플릿 리스트에 있는 function나 class들을 overloading 버전들로 모두 다 다시 쭉 적어내는 셈
//              (= 당연히 컴파일 시간이 더 걸릴 수 밖에 없음)


//   # 템플릿의 특징
//     1. 컴파일 단계에서 function이나 class멤버들을 직접 생성하기에, function나 class에 템플릿을 많이 적용하는 만큼 쓰면 컴파일 속도가 느려짐
//     2. 컴파일 단계에서 코드를 추가하는 것이기에, 그 이후 프로그램 처리 속도랑은 관계 X
//     3. JAVA에서는 이를 제너릭스(generics)라고 부름
//         -> 제너릭스(generics) = 템플릿 + 컴파일 과정에서 객체 자료형 타입 check 추가
//     4. (장점) 수많은 경우의 수에 맞춰 적어야 할 overloading 버전 작성을 일괄적으로 처리하는거라, 제대로만 만들어 두면 편의성이나 코드 완성도나 전부 높아질 수 밖에 없음
//     5. (단점) 포괄적인 함수나 클래스의 정의부만 양식으로 적어주는거라 예측하지 못한 자료형으로 인해 안정성은 떨어질 수 밖에 없음
//     6. 컨테이너 class 객체와


//   # 안정성이 부족함에도 템플릿 사용 이유?
//      : 포괄적인 함수나 클래스의 정의부만 양식으로 적어주는거라 예측하지 못한 자료형으로 인해 안정성은 떨어질 수 밖에 없다? 팩트임
//         -> BUT! 진짜 제대로 만들어만 놓는다면? 코드의 완성도가 높아지고, 코드를 사용하기도 쉬운지라 유지보수 생산성 효율도 증가하기 때문 
//            -> 이러한 장점이 STL(Standard Template Library)처럼 성능과 안정성이 검증된 라이브러리와 함께면 시너지가 대폭 증가함
//               (= 만들기는 어려운데, 일단 제대로만 만들어서 안정성이 검증되면, 그떄부터는 그냥 가져다 쓰면 된다는 의미)


//   # (중요) class나 function 선언시 템플릿 작성법 및 종류
// 
//      - 템플릿 작성법 
//         : 템플릿 양식을 적용하기 원하는 class나 function 위에 템플릿 형식을 <>안에 템플릿 매개변수(parameter)와 함께 작성
//            -> 그러면 컴파일 시 아래의 1개의 class나 function에 대해서 템플릿의 <>안에 작성한 템플릿 매개변수(parameter)의 내용을 반영해서, 관련 overloading function이나 class들을 모두 일괄 생성해 줌
//               (= 어디 위에다 template을 작성하냐? 에 따라 템플릿의 종류가 나뉨)

//      - 템플릿 선언 형식(class, function 전부 공용.. 단지 어디 위에 적냐?가 종류를 가름 문제)
//         : template <typename1 parameter명1, .... typenameN parameter명n>
//           function 선언 or class 선언 
//             -> 특징
//                 a. 선언에 쓰이는 parameter는 템플릿에 적은 parameter명1을 써야 함
//                 b. <>안의 parameter명은 일반적으로 템플릿 기호 T로 표기
//                 c. template는 1개당 1개의 함수나 class를 담당함 (= 하나로 다 해먹을 수 없음) 
//                 d. 템플릿 선언시 <> 안에 작성하는 템플릿 매개변수(parameter)의 수는 복수개도 상관없음
//                     -> (중요) 심지어 rest parameter 개념으로 템플릿 파라미터 팩(template parameter pack)도 사용 가능

//      - typename의 의미
//         : 모든 자료형을 포괄하여 적용한다는 의미
//            -> 과거에는 보통 class가 주된 자료형이라 template <class Type>으로 적었음

//      - 템플릿 종류 + 템플릿 적용 대상 호출 및 생성하는 형식
//        1. 함수 템플릿(function Template)
//           : 일반화 프로그래밍(Generic Programming)에 의거, 한번 작성하면 다양한 자료 타입을 적용할 수 있는 범용적인 function을 제작하고자, 템플릿의 내용을 function 선언부, 정의부에 사용해 작성한 경우
//              -> (선언시) function 선언시, 해당 fucntion 위에 작성된 템플릿의 <>안에 지정된 'type명 parameter명'들을 참고해서, function 선언부와 정의부 작성
//              -> (호출시) 이를 바탕으로 컴파일 과정에서 function 호출 코드가 발견되면 호출 당시 <>안에 적힌 'parameter들의 실질적 자료형'에 알맞은 실제 함수를 작성하고 하는 호출해주는 틀(= 양식)
// 	      
//                  ex) list(initializer_list<Type> IList, const Allocator& Al);
// 	      
//        2. 클래스 템플릿(class Template)
//           : 일반화 프로그래밍(Generic Programming)에 의거, 한번 작성하면 다양한 자료 타입을 적용할 수 있는 범용적인 class을 제작하고자, 템플릿의 내용을 class 선언부에 사용하여 작성한 경우
//              -> (선언시) class 선언시, 해당 class 위에 작성된 템플릿을 <>안에 지정된 'type명 parameter명'들을 참고해서, class 생성자 함수의 선언부 및 정의부 작성
//              -> (호출시) 이를 바탕으로 컴파일 과정에서 class 생성자 함수가 발견되면 호출 당시 <>안에 적힌 'parameter들의 실질적 자료형'에 알맞은 실제 class를 생성해주는 틀(= 양식)

//                  ex) 컨테이너클래스명 <value자료형> 객체명 = new 컨테이너클래스명(); 형식도 같은 역할 수행
//                       : <value자료형>의 의미 = 특정 class 형식을 컨테이너 class 객체를 이루는 요소로 사용하기 위해 입력 자료형을 지정하는 역할을 함 
//                          -> 쉽게 말해, C언어에서 컨테이너 class 구현할때, node나 list 내부의 value값의 타입을 'typedef value자료형 컨테이너명_element;' 식으로 구현한걸 정식으로 기능화
//                             (= 이를 통해 동일한 코드를 다양한 데이터 타입에 대해 재사용하기 쉬워진 효과를 같는 것 또한 동일하나, 코드의 수정이 필요한 typedef보다 쓰기도 쉬움)


//   # 템플릿 사용시 주의사항
//      1. 가능한 다양한 자료형에 대해 포괄적으로 적용할 수 있는 범용적인 함수를 제작
//      2. 자료형을 템플릿 기호로 표기시에는 일반적으로 T를 사용
//      3. 컴파일 단계에서 만들어지기 때문에, 컴파일 시간이 늘어나게 되는건 감안해야 함
//      4. 함수의 호출 구문으로 parameter의 자료형을 확인하고 자료형 별로 함수를 제작해야 함 (오버로딩)





// 특수화 (specialization)
//  : 기존에 템플릿이 작성된 함수나 생성자를 호출할때 특정 자료형을 parameter로 가져오는 경우에는 전혀 다른 알고리즘으로 처리하라는 개념
//     -> 쉽게말해 템플릿 예외처리

//   # 특수화의 종류
//      1. 템플릿 특수화 (Template specialization)
//          : 특정 자료형을 parameter로 받을 , 기존 템플릿의 내용을 따르지 않고 function이나 class생성자의 기능을 다르게 하고 싶은 경우 사용

//      2. 부분 특수화 (Partial specialization)
//          : 템플릿의 parameter가 여러 개일 경우, parameter 중 일부만 특수화 시킴



//특수화(Specialization)
//
//함수의 기능을 특정 자료형에서 다른 알고리즘으로 처리 할 경우 특수화
//함수의 이름 아래 모든 경우 오버로딩이 가능하다.템플릿이 아닌 함수템플릿 함수명시적 특수화 템플릿 함수
//명시적 특수화는 반드시 작성template<> 반환형 함수 이름 <typename>(매개변수 리스트) { 함수 정의 }
//우선순위: 일반함수 > 템플릿 특수화 함수 > 템플릿 함수
//
//구체화(Instantiation)
//컴파일 과정에서 특정 자료형에 맞는 함수를 생성.
//
//void swap(T a, T b);
//
//int a, b;
//swap(a, b); // void swap(int a, int b) 함수 생성, 암시적 구체화
//template void swap<int>(int a, int b); // swap(int, int) 함수 생성, 명시적 구체화








// 구체화 (Instaniation)
//  : 컴파일 과정에서 특정 자료형에 맞는 함수를 생성하는 개념
//     -> 만들어진 템플릿에서 해당 자료형에 맞는 구조로 함수를 호출하라

//메인 템플릿의 템플릿 변수가 2개의 경우
//사용자는 반드시 템플릿 매개변수를 2개 전달(기본값이 없다면)


//   # 특수화(specialization) 사용시 주의사항
//      1. 부분 특수화에서 T의 타입이 결정되는 방식을 주의 (= 다른 함수 템플릿에 중복되는 경우 발생)
//      2. 부분 특수화에서 default parameter는 표시하지 않음 (= 메인 템플릿에 정의 값을 그대로 받음)
//      3. 템플릿 특수화는 class에서 특정 멤버함수를 특수화 할 수 있으나, 부분 특수화는 아예 불가능


//부분 특수화(Partial specialization)
//템플릿에서 매개변수의 수는 메인 템플릿 매개변수 수와 다를 수 있다.
//함수(템플릿 매개변수 + 일반 매개변수)
//
//특수화를 많이 할 경우 소스코드가 늘어날 수는 있지만
//결국 목적코드로 생성되는 기계어 코드의 양은 같음









//표준 템플릿 라이브러리(STL, Standard Template Library)
//템플릿들의 집합
//컨테이너(Container) : 자료구조
//이터레이터(Iterator) : 데이터 접근 객체
//함수 객체(Function Object) : 함수 역할의 객체
//알고리즘(Algorithm) : 알고리즘 함수(정렬, 검색, 비교, … 등)
//
//이터레이터(Iterator : 반복자, 포인터)
//일반화 프로그램에서 데이터를 접근하는 객체
//배열, 연결리스트, 큐 등 다양함(컨테이너 or 알고리즘)에 얽매이지 않고 저장된 data를 접근할 수 있는 일반화된 표현
//
//Container<data>::iterator itr = Container.begin(), itr1, itr2;
//데이터 값을 접근 할 수 있다.[내용 참조 기능 : (*itr)]
//다른 이터레이터에 대입 할 수 있다.[대입 가능 : itr1 = itr]
//다른 이터레이터와 비교 할 수 있다.[비교 가능 : itr == itr1, itr != itr2]
//컨테이너의 모든 원소를 접근 할 수 있다.[증감 연산 : ++itr, itr++]
//
//_Fn for_each(_InIt _First, _InIt _Last, _Fn _Func)
//함수포인터 for_each(시작 ITR, 종단 ITR, 함수 포인터)



// 함수 템플릿 예시1
#include <iostream>
#include <cstring>
using namespace std;

// == template <class T1>     <- 과거에는 class라고 했지만, 이미 예약어 class가 존재하니 햇살려서 이렇게 함
template <typename T1>

void f_swap(T1& val1, T1& val2) {
	T1 temp = val1;
	val1 = val2;
	val2 = temp;
	cout << typeid(val1).name() << " swap call\n"; // typeid(val1).name() == val1의 자료형
}

template <class T1>

void str_swap(T1& p1, T1& p2) {
	T1 temp;
	strcpy_s(temp, strlen(p1) + 1, p1);
	strcpy_s(p1, strlen(p2) + 1, p2);
	strcpy_s(p2, strlen(temp) + 1, temp);
	cout << typeid(p1).name() << " swap call\n";
}

int main() {
	int i1 = 123, i2 = 456;
	cout << "변경 전 : " << i1 << ", " << i2 << " / ";
	f_swap(i1, i2);
	cout << "변경 후 : " << i1 << ", " << i2 << endl << endl;

	double d1 = 12.34, d2 = 56.78;
	cout << "변경 전 : " << d1 << ", " << d2 << " / ";
	f_swap(d1, d2);
	cout << "변경 후 : " << d1 << ", " << d2 << endl << endl;

	char c1 = 'A', c2 = 'B';
	cout << "변경 전 : " << c1 << ", " << c2 << " / ";
	f_swap(c1, c2);
	cout << "변경 후 : " << c1 << ", " << c2 << endl << endl;

	char str1[255] = "C++ language", str2[255] = "Well done!";
	cout << "변경 전 : " << str1 << ", " << str2 << " / ";
	str_swap(str1, str2);
	cout << "변경 후 : " << str1 << ", " << str2 << endl << endl;

	return 0;
}