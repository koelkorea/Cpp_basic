// 함수 템플릿 case별 예시코드
#include <iostream>
#include <cstring>
using namespace std;

//-----------------------------------------------------------------------------------------------------------------------
// (예시1) 함수의 parameter에 사용되는 자료형이 1개인 경우의 함수 템플릿 예시

// f_swap : string 이외의 두 변수의 값을 교환
//  -> 2개의 함수의 parameter는 T1으로 치환된 typename이 정해지면, 전부 그것을 따르는 구조
template <typename T1>
void f_swap(T1& val1, T1& val2) {         // void f_swap<T1>(T1& val1, T1& val2); 와 같음

	// 어떤 자료형의 레버런스로 들어오는 paramter val1의 특성
	//  -> (중요) char 배열로 들어오는 문자열 길이까지 미리 템플릿의 자료형으로 처리할 수가 없는 상황에서, 탬플릿 paramter로서 모든 자료형에 대응되더라도 temp에 char 배열 형식의 문자열 val1은 대입되지 않음
	//     -> 하단에 str_swap을 만들고, 문자열 복사 메서드 strcpy_s과 길이를 알아내는 strlen를 사용해서 처리
	T1 temp = val1;

	val1 = val2;
	val2 = temp;

	// typeid(val1).name() == 변수 val1 의 자료형 의미
	cout << typeid(val1).name() << " swap call\n"; 
}

// template <typename T1> == template <class T1>     <- 과거에는 class라고 했지만, 이미 예약어 class가 존재하니 햇살려서 이렇게 함

// str_swap : string인 두 변수의 값을 교환
//  -> 2개의 함수의 parameter는 T1으로 치환된 typename이 정해지면, 전부 그것을 따르는 구조
//     -> (참고!) string 스왑만을 위한 다른 함수를 만드는 건 템플릿의 취지와 어긋나기에, T1이 string으로 들어오는 경우에 한한 f_swap 특수화 함수 템플릿으로 처리하는 것이 정석
template <class T1>
void str_swap(T1& p1, T1& p2) {           // void str_swap<T1>(T1& val1, T1& val2); 와 같음

	T1 temp;

	strcpy_s(temp, strlen(p1) + 1, p1);
	strcpy_s(p1, strlen(p2) + 1, p2);
	strcpy_s(p2, strlen(temp) + 1, temp);

	cout << typeid(p1).name() << " swap call\n";
}

//-----------------------------------------------------------------------------------------------------------------------
// (예시2) 함수의 parameter에 사용되는 자료형의 가지수가 복수개인 경우의 함수 템플릿 예시
//        -> 함수 템플릿을 선언할 때, 필요하다고 여겨지는 경우에 함수의 각 paramter의 자료형이 독립적으로 정해질 수 있도록 템플릿 parameter 또한 여러개 사용이 가능

// showData : parameter로 들어간 변수 a, b, c의 자료형을 console에 출력
//  -> 3개의 함수의 parameter a, b, c는 각각 T1, T2, T3로 치환된 typename이 정해지면, 각자 그것을 따르는 구조
template <typename T1, typename T2, typename T3>
void showData(T1 a, T2 b, T3 c) {         // void showData<T1, T2, T3>(T1 a, T2 b, T3 c); 와 같음

	cout << endl;
	cout << a << "\t" << b << "\t" << c << endl;
	cout << typeid(a).name() << "\t" << typeid(b).name() << "\t" << typeid(c).name() << endl;
}

//-----------------------------------------------------------------------------------------------------------------------
// (예시3) 함수에 rest parameter 개념이 사용되어 자료형 또한 가지수가 정확히 몇개인지 알수 없는 경우의 함수 템플릿 예시
//        -> 함수 템플릿을 선언할 때, 필요하다고 여겨지는 경우에 함수의 각 paramter의 자료형이 독립적으로 정해질 수 있도록 템플릿 parameter 또한 여러개 사용이 가능
//           ->  <typename T1, typename... T2> : 템플릿 파라미터 팩 (템플릿 계의 rest parameter)
//               (T1 arg, T2... args)          : 함수 파리미터 팩 (템플릿 파라미터 팩의 내용을 실제 함수의 rest parameter 적용 함수로 만듦)

// print(T n) : 템플릿 기본형 함수 형식으로 print(T1 arg, T2... args)에서 parameter 수가 점차 줄어드는 재귀함수의 끝을 담당할 목적
//   -> print(T1 arg, T2... args)의 양식을 따르지 않을 것이기에 단독으로 만듦
template <typename T>
void print(T n) {                         // void print<T>(T n); 와 같음

	cout << "마지막 인수 1개 => ";
	cout << n << endl;
}

// print(T1 arg, T2... args) : 템플릿 파라미터 팩을 활용한 overloading 된 함수로 rest parameter 형식임에도 1번째 템플릿 파라미터와, 함수 파라미터 변수를 구분하는 이유는 내용에서 실질적으로 사용하는건 1번째고, 
//   -> 그것을 제외한 나머지 parameter변수들은 재귀함수로 보내는 변수처리를 할 예정이기 때문
template <typename T1, typename... T2>     // 템플릿 파라미터 팩 (템플릿 계의 rest parameter)
void print(T1 arg, T2... args) {           // 함수 파리미터 팩 (템플릿 파라미터 팩의 내용을 실제 함수의 rest parameter 적용 함수로 만듦)

	cout << "가변인수 => ";

	// 1번째 함수 parameter 변수명 arg는 console 출력하고
	cout << arg << endl;

	// 2번째 이외의 나머지 변수들은 rest parameter 형식으로 묶어서, 재귀함수의 parameter로 보냄
	//  -> 이를 통해 parameter가 끝날때까지 해당 함수는 무한 작동
	//  -> 1개가 남을때 상단의 print(n)으로..
	print(args...);
}


int main() {

	//-----------------------------------------------------------------------------------------------------------------------
	// (예시1) 함수의 parameter에 사용되는 자료형이 1개인 함수 템플릿 호출 예시
	int i1 = 123, i2 = 456;
	cout << "변경 전 : " << i1 << ", " << i2 << " / ";
	// f_swap<int>(d1, d2); 와 같음
	f_swap(i1, i2);
	cout << "변경 후 : " << i1 << ", " << i2 << endl << endl;

	double d1 = 12.34, d2 = 56.78;
	cout << "변경 전 : " << d1 << ", " << d2 << " / ";
	// f_swap<double>(d1, d2); 와 같음
	f_swap(d1, d2);
	cout << "변경 후 : " << d1 << ", " << d2 << endl << endl;

	char c1 = 'A', c2 = 'B';
	cout << "변경 전 : " << c1 << ", " << c2 << " / ";
	// f_swap<char>(c1, c2); 와 같음
	f_swap(c1, c2);
	cout << "변경 후 : " << c1 << ", " << c2 << endl << endl;

	// f_swap 함수는 얕은 복사 형식을 쓰기에, 실질적으로 char배열의 시작 주소값을 저장하는 문자열의 값 교환을 수행하는데는 문제가 있음
	//  -> str_swap 함수를 쓰는 이유
	char str1[255] = "C++ language", str2[255] = "Well done!";
	cout << "변경 전 : " << str1 << ", " << str2 << " / ";
	// str_swap<char[]>(str1, str2); 
	str_swap(str1, str2);
	cout << "변경 후 : " << str1 << ", " << str2 << endl << endl;


	//-----------------------------------------------------------------------------------------------------------------------
	// (예시2) 함수의 parameter에 사용되는 자료형의 가지수가 복수개인 함수 템플릿 호출 예시
	//    -> showData의 템플릿 파라미터의 수는 함수 파라미터의 수에 대응하는 3개므로, 각 파라미터의 자료형은 독립적 설정이 가능하며, 
	//       if 함수호출시 템플릿 호출부분 <자료형1 , ... >이 없다면, 컴파일러가 알아서 템플릿 호출시에 코드를 기입

	showData(10, 20, 30);         // showData<int, int, int>(10, 20, 30); 와 같음
	showData('A', 'B', 'C');      // showData<char, char, char>('A', 'B', 'C'); 와 같음
	showData(10, 3.14, "C++");    // showData<int, float, char>(10, 3.14, "C++"); 와 같음

	//-----------------------------------------------------------------------------------------------------------------------
// (예시3) 함수에 rest parameter 개념이 사용되어 자료형 또한 가지수가 정확히 몇개인지 알수 없는 경우의 함수 템플릿 호출 예시
	// -> 함수 템플릿을 선언할 때, 필요하다고 여겨지는 경우에 함수의 각 paramter의 자료형이 독립적으로 정해질 수 있도록 템플릿 parameter 또한 여러개 사용이 가능

	// 보다시피 1개를 사용하건 n개를 사용하건 결국 단일 paramter print 함수와 rest parameter 형식으로 overloading한 함수가 콜라보 된 재귀함수의 결과를 보여줌
	print(1.2345);                                          // print<double>(1.2345); 와 같음
	print(1, 2.5, "C++");                                   // print<int, double, string>(1, 2.5, "C++"); 와 같음
	print(1, 2, "Hello", 'a', 32.14, 78, 56, "apple");

	return 0;
}
