﻿// 템플릿(Template)
//  : function이나 class의 수많은 overloading 버전들을 개별적으로 작성을 하기 귀찮기에, 포괄적으로 그들의 parameter로 범용적인 자료형이 들어간다고 가정하고 작성한 일종의 funtcion들을 작성하는 공용 양식
//      -> (중요) 컴파일러에 의해 컴파일 과정에서 템플릿을 동반하여 선언된 function or class를 호출하는 코드가 발견되는 경우, 그들이 사용한 자료형에 해당하는 overloading 버전들을 모두 자동으로 쭉 생성해 줌 (= 암시적 구체화)
//          -> 컴파일 단계에서 function이나 class멤버들을 직접 생성하기에, function나 class에 템플릿을 많이 적용하는 만큼 쓰면 컴파일 속도가 느려짐
//              <-> 컴파일 단계에서 코드를 추가하는 것이기에, 그 이후 프로그램 처리 속도랑은 관계 X


//   # 템플릿의 탄생 배경
//      (기) : 객체지향 프로그래밍(OOP) 패러다임이 대세가 되어, class 객체 자료형을 작성하는 방식에 원칙과 표준이 생김 (표준화, 상속, 다형성, 캡슐화)
//      (승) : 그 중 다형성의 원칙에 따라, 동명의 함수지만 parameter의 종류나 개수가 완전히 같지 않으면 다른 함수로 취급함으로서, 같은 함수를 다양한 경우에서 사용가능하게 해주는 overloading이 널리 쓰이기 시작함
//      (전) : overloading 함수들을 작성하다 보니, parameter에 따른 경우의 수가 뒤지게 많다는 점과 그렇게 작성된 함수들이 정작 내용은 자료형만 바꿔 적용하면 전혀 다른게 없는 경우가 많다는 점을 발견
//      (결) : 일반화 프로그래밍(Generic Programming) 패러다임적 관점을 받아들여, 1번 작성하고 나면 비슷한 내용의 overloading 함수들을 포괄할 수 있는 일타쌍피를 노릴 수 있는 양식을 만들고자 하는 움직임 발생
//               -> 결론 : 그렇게 만들어진 function 작성에 편의성을 제공하는 양식이 '템플릿(Template)' 되시겠다!


//   # 표준 템플릿 라이브러리(STL, Standard Template Library)
//      : 일반화 프로그래밍(Generic Programming)을 기조를 달성하고자, C++에서  '템플릿' 들을 사용하여 작성된 class와 function들이 모인 표준 라이브러리
//        (= function 템플릿, class 템플릿을 사용해 overloading이 필요한 function, class들의 집합)


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
//      1. 템플릿 정의
//          : 템플릿 양식을 적용하기 원하는 class나 function 앞에 [template <typename T1 ...>]을 작성시, 'T1 ~ '은 해당 함수나, 클래스의 생성자 및 멤버함수 선언에 사용되는 parameter 타입들의 갯수와 실제 선언부에 들어가는 그들의 자료형이 위치하는 부분에 해당함
//            (= 어디 위에다 template을 작성하냐? 에 따라 템플릿의 종류가 'function template' or 'class template' 나뉨) 

//            - 템플릿의 종류
//               1. 함수 템플릿(function Template)
//                  : 한번 작성하면 다양한 자료 타입을 적용할 수 있는 범용적인 function을 제작하고자, 템플릿 형식에 선언된 typename 변수를  function 선언부, 정의부에 사용해 작성한 경우

//               2. 클래스 템플릿(class Template)
//                  : 한번 작성하면 다양한 자료 타입을 적용할 수 있는 범용적인 class을 제작하고자, 템플릿 형식에 선언된 typename 변수를 class 선언부의 멤버변수나 멤버함수, 생성자함수에 사용하여 작성한 경우
//                      -> (중요) 클래스 템플릿 정의시 둔 선언한 템플릿 parameter의 typename 치환기호 'T' 들을 멤버변수와 멤버함수에 두루두루 적용이 가능함 


//            - (중요) 템플릿 정의 형식 & 구조 설명 (이걸 이해해야 뒤의 특수화 구조를 완벽히 이해 가능)
//               : template  <typename T1, ... >  function명 or class명  <T1, ... > (T1 변수명, ...) { 내용 }
//                                                --------------------   ----------
//                                                어떤 템플릿인지 정함   (생략가능!)   <- (중요!) 템플릿 정의건 생성이건 class명 or function명 옆의 <자료형.. > 부분은 실제로는 존재하나 생략이 가능함
//                                                                                                 <-> 부분 특수화 템플릿은 무조건 써야함 제외
	          
//                 @ template 예약어
//                    : 어떤 종류의 템플릿(함수 템플릿, 클래스 템플릿, 특수화 함수 템플릿, 부분 특수화 함수 템플릿)을 시작한다는 의미의 예약어
	          
//                 @ <typename ... T>
//                    : 템플릿 정의시 1번째로 등장하는 <>로 그 안에는 해당 템플릿이 참고하는 function이나 class가 사용하는 parameter중 가변 자료형을 사용하는 녀석이 있는 경우에 그 갯수만큼 'typename의 치환된기호'을 선언함
//                                                                                                                                                                                            ----------------------
//                                                                                                                                                                                           (템플릿 paramter로 명명)
//                       -> 특징
//                          1. 보통 '치환된기호'는 T라고 명명함
//                              -> 그 치환된기호 T... 들은 function이나 class의 선언부의 parameter 작성 부분에 자료형을 놓는 부분에 사용함
//                                 (= T는 typename이 치환된 기호니까, 사실상 typename으로 치환 가능)
	          
//                          2. (중요) 특수화 된 함수 템플릿은 사실상 고정된 자료형이 parameter로 들어가는 상황이기 때문에, 이 1번째 <>부분인 <typename ... T>에 아무것도 적지 않은 'template <>'라고 씀
//                             -> 심지어 template <>의 <>는 생략이 가능함

//                          3. (중요) <typename T1>에서 T와 typename의 관계는 typedef typename T{} 와 같은 의미로 치환되는 관계

//                          4. 과거에는 보통 class가 주된 자료형이라 <typename T1>를 <class Type>으로 적었음


//                 @ 템플릿 parameter = 1번째 <>안의 'typename ... T'
//                    : 템플릿 정의시 1번째 <> 안에 들어가는 'typename T1 ...'를 '템플릿 parameter' 라고 함
//                       -> 특징
//                           1. (중요!) 1번째 <> 안에 적힌 typename타입 변수 T1 ~ TN은 실제 함수나, 클래스의 생성자 및 멤버함수의 선언부의 parameter들중 가변 자료형이 기입하는 부분을 지칭하고, 가변 자료형의 개수를 암시함
//                           2. (중요!) 해당 함수나, 클래스의 생성자 및 멤버함수 선언부의 각 parameter의 자료형이 독립적인 경우, 그만큼 많은 템플릿 parameter의 typename 변수가 필요함
//                           3. rest parameter 형식의 템플릿 파라미터 팩(template parameter pack) 작성 또한 가능
//                               -> (응용!) 재귀함수를 통해 함수에 적용될 parameter를 하나씩 줄여나가기도 가능함 (이 경우 재귀로 돌릴 parameter와 실제 함수 내용에 쓸 parameter의 변수명을 구분해서 작성해야 함
			       
//                       ex1) [가변 자료형이 1가지 뿐일 템플릿 작성 예시]
			       
//                            template <typename T> void swap(T a, T b) { 내용 };             <- template <typename T> void swap<T>(T a, T b); 가 전체코드이며 <T>가 생략됨
//                             -> 만약 a, b의 parameter의 자료형을 독립적으로 지정하고 싶다면?
//                                 -> template <typename T1, typename T2> void swap(T1 a, T2 b); 이렇게 템플릿 parameter 변수를 따로 지정해주고, 함수나 클래스의 선언부에 적히는 parameter의 자료형으로 각각 선언해야 함
			       
//                       ex2) [가변 자료형이 복수 가지인 템플릿 작성 예시]
			       
//                            template <typename T1, typename T2> void swap(T1 a, T2 b) { 내용 };
//                            int a, string b                                                  <- a, b가 같은 타입의 자료형이 아니기에, 각각의 자료형을 따로 지정해줄 T1, T2가 따로 존재하게 됨
//                            swap(a, b);                                                      <- swap<int, string>(a, b); 가 전체코드이며 <int, string>가 생략됨
			       
//                       ex3) [가변 자료형의 갯수가 정해지지 않은 템플릿 파라미터 팩(template parameter pack) 적용 템플릿 작성 예시]
			       
//                            template <typename ... T1> void print(T1 ... args) { 내용 };     <- rest paramter 형식 적용
//                            print(1, 2, "Hello", 'a');                                       <- print<int, int, string, int>(1, 2, "Hello", 'a'); 가 전체코드이며 <int, int, string, int>가 생략됨
	          
//                 @ function명 or class명
//                    : 앞선 2부분 template 예약어 + <typename ... T>를 어디 앞에 쓰느냐에 따라 '함수 템플릿' 인지? '클래스 템플릿'인지 결정됨
	          
//                 @ <T1, ... >
//                    : 템플릿 정의시 2번째로 등장하는 <>로 function명 or class명 앞에 적는다... 앞선 1번째 <>에서 적은 <typename ... T>중 T에 해당하는 '치환된기호' 부분을 쓰는 위치.. 
//                       -> (중요) 원래는 템플릿 사용시 function명 or class명 선언부와 한 몸으로 붙어다니는 녀석이나, 호출시 ()안에 들어가는 parameter의 자료형을 통해 컴파일러가 대신 작성 가능하므로 [생략가능] 
//                           -> 사실 템플릿 정의시보단 실질적으로 호출시에 실제 들어가는 parameter의 자료형이 정확히 무엇인지 정의하는 부분인지라 템플릿 호출 때 더 중요하게 쓰임
	          
//                               ex) (2번째 <> 생략시) 
//                                    -> 함수 템플릿   : template <typename T1, ... > function명(T1 변수명, ...) { 내용 } 를 의미
//                                    -> 클래스 템플릿 : template <typename T1, ... > class명(T1 변수명, ...) { 내용 } 를 의미
	          
//                 @ (T1 변수명, ... )
//                    : 해당 function이나 class의 선언부에 해당하는 부분으로 해당 부분의 parameter의 자료형 및 변수명을 순차적으로 작성하면 됨
//                       -> 템플릿과 함께 작성되었으니, 이들 중 가변 자료형을 사용하는 parameter에 해당하는 녀석은 1번째 <>안에서 작성된 typename의 치환된기호 'T1' ~ 'Tn'을 parameter 자료형 부분에 기입함
//                           -> (중요!) 설령 어떤 parameter 중 가변 자료형을 사용하지 않는 녀석이 있다치면, 그 녀석의 자료형을 그대로 기입해도 상관없음 (해당 case에 대해 다루는게 '부분 특수화 함수 템플릿' )
	          
//                               ex) (1번째 <> 생략시) 
//                                    -> 함수 템플릿   : template function명(typename 변수명, ...) { 내용 } 를 의미
//                                       클래스 템플릿 : template class명(typename 변수명, ...) { 내용 }을 의미


//            - 템플릿 정의시 특징
//               1. 1번째 <>안의 class나 function의 parameter의 자료형을 지칭하는, 'typename 치환된기호'은 일반적으로 템플릿 기호 T로 표기
//                   -> 그 T를 class나 function 선언부의 parameter 영역에서 가변 자료형을 사용하는 parameter의 자료형 표기 위치에 사용
// 
//               2. 템플릿에 적을 class나 function명 옆의 2번째 <> 안에 위치할 parameter의 자료형 선언부 위치에는 템플릿에 적었던 소위 T로 적은 '템플릿 기호'을 써야 함
// 
//               3. (중요) 템플릿 정의시 function명 <T1...> { 내용 }, class명 <T1...> { 멤버변수; 멤버함수; } 처럼, 2번째 <자료형> 부분은 실제로는 존재하나 생략이 가능함
//                          <-> 부분 특수화 템플릿은 무조건 써야함 제외
// 
//               4. (중요) template 예약어는 그 뒤에 이어지는 class 및 function의 내용들과 세트로 1개당 1개의 함수나 class를 담당함 
//                         (= 템플릿 정의(= 선언)부 하나로 모든 function나 class를 다 통제할 수 없음) 
// 
//               4. 템플릿 선언(= 정의)시 1번째 <> 안에 작성하는 '템플릿 매개변수(parameter)'의 수는 복수 개도 상관없고, 단지 해당 class나 function이 사용하는 parameter중 가변 자료형을 사용하는 만큼 작성하면 됨
//                   -> (중요) 심지어 그 구체적인 수를 모르면 rest parameter 개념으로 템플릿 파라미터 팩(template parameter pack)도 사용 가능
// 
//               6. 템플릿을 통해 class나 function의 자료형 선언을 쉽게 통제할 수 있기 때문에, C++을 포함한 각종 언어의 기본 라이브러리에도 많이 쓰임  (= 당연히 원조격인 STL에서도 적용됨)


//      2.1 (핵심!) 템플릿 인스턴스화 = 암시적 구체화 (implicit Instantiation)
//          : 작성된 템플릿을 참고, 컴파일 시점에서 컴파일러는 그 곳의 function or class를 호출 및 생성하는 코드들을 색출한 뒤, 그들이 사용한 자료형에 해당하는 overloading 버전들을 모두 자동으로 쭉 생성해 줌 
//             -> 컴파일 시점에서 만들어진 템플릿을 참고하여, 호출 및 생성하는 코드의 자료형에 맞는 구조로 function이나 class를 구체화시켜 작성하여 대응한다고 생각하면 편함
//                 -> 미리 class나 function을 작성해둔게 아니고, 컴파일 단계에서 템플릿 리스트에 있는 function나 class들을 사용하는 자료형에 한해서만 overloading 버전들로 모두 다 다시 쭉 적어내는 셈
//                    (= 당연히 컴파일 시간이 더 걸릴 수 밖에 없음)

//            - (중요) 템플릿 호출 형식 (선언부는 상단 참고)
//               1. 함수 템플릿(function Template)
//                   : function명 <실제typename1, ...> (parameter1, ....);
//                                --------------------
//                                     (생략가능!)        <- (중요!) 템플릿 정의건 호출이건 class명 or function명 옆의 <자료형.. > 부분은 실제로는 존재하나 생략이 가능함  <-> 부분 특수화 템플릿은 무조건 써야함 제외
//                                                                    -> 단! 템플릿 호출 시에는 가급적이면 자료형 정보를 명시하는 것이 프로그래머 입장에서 결과 예측에 편함     
//                                                                        -> 아니면, 최소한 parameter로 들어간 값의 자료형을 명시라도 명확히 하면 컴파일러가 그걸로 템플릿 호출코드의 2번째 <자료형>을 작성해 줌

//                     ex) template <typename T> void swap(T a, T b);                         <- (함수 템플릿 정의) template <typename T> void swap<T>(T a, T b); 가 전체코드이며 <T>가 생략됨
//                         int a, b;									                      
//                         swap(a, b);                                                        <- (함수 템플릿 호출) swap<int>(a, b); 가 전체코드이며 <int>가 생략됨
//                         void swap(int a, int b)                                            <- int를 paramter로 둔 swap 호출이 발견되면, void swap(T a, T b)의 paramter 자료형을 int로 구체화시켜 override한 함수 코드를 생성해 주는게 암시적 구체화

//               2. 클래스 템플릿(class Template)
//                   : class명 <실제typename1, ...> 객체명 = new class명(parameter1, ....);
//                             --------------------
//                                  (생략가능!)        <- (중요!) 템플릿 정의건 호출이건 class명 or function명 옆의 <자료형.. > 부분은 실제로는 존재하나 생략이 가능함  <-> 부분 특수화 템플릿은 무조건 써야함 제외
//                                                                 -> 단! 템플릿 호출 시에는 가급적이면 자료형 정보를 명시하는 것이 프로그래머 입장에서 결과 예측에 편함     
//                                                                     -> 아니면, 최소한 parameter로 들어간 값의 자료형을 명시라도 명확히 하면 컴파일러가 그걸로 템플릿 호출코드의 2번째 <자료형>을 작성해 줌

//                     ex) template <typename T> class Dummy(T a);                            <- (클래스 템플릿 정의) template <typename T> class Dummy<T>(T a); 가 전체코드이며 <T>가 생략됨
//                         template <typename T> Dummy<T>::SetA(T a1) { a = a1 };             <- (함수 템플릿 정의) 멤버함수 SetA()는 파라미터의 변수명이 클래스의 멤버변수와 달라야 하므로 따로 함수 템플릿으로 정의함

//                         Dummy d1(10);                                                      <- (생성자 함수를 통한 클래스 템플릿 호출) Dummy d1 <int>(10); 가 전체코드이며 템플릿 parameter를 투입하는 <int>가 코드에서 생략됨
//                                                                                                 -> int를 paramter로 둔 Dummy 생성자함수 호출이 발견되었기에 Dummy생성자함수의 paramter 자료형을 int로 구체화시켜 override한 함수 코드를 생성해 주는게 암시적 구체화
//                         d1.SetA(1);                                                        <- (템플릿이 존재하는 클래스의 멤버함수 호출) 

//            - 템플릿 호출시 특징
//               1. 실질적으로 사용하는 빈도가 높은 라이브러리를 다루는 프로그래머가 가장 많이 쓸 템플릿 기능
//                   -> 주로 특정한 자료형 형식만을 input받기 위한 객체 배열이나 컨테이너 클래스에서 사용

//                      ex) 컨테이너클래스명 <value자료형> 객체명 = new 컨테이너클래스명(); 형식
//                           : <value자료형>의 의미 = 특정 class 형식을 컨테이너 class 객체를 이루는 요소로 사용하기 위해 입력 자료형을 지정하는 역할을 함 
//                              -> 쉽게 말해, C언어에서 컨테이너 class 구현할때, node나 list 내부의 value값의 타입을 'typedef value자료형 컨테이너명_element;' 식으로 구현한걸 정식으로 기능화
//                                 (= 이를 통해 동일한 코드를 다양한 데이터 타입에 대해 재사용하기 쉬워진 효과를 같는 것 또한 동일하나, 코드의 수정이 필요한 typedef보다 쓰기도 쉬움)

//               2. (중요!) 템플릿이 호출될 시 function이나 class나 어떤 종류라도 전부 호출 될때, 'function class명<실제typename1, ...>(parameter1,... )' 에서 <실제typename1, ...>을 수행함 
//                   -> 템플릿 호출시 <실제typename1, ...> 부분은 생략해도 상관없음 (= 어차피 컴파일러가 호출된 코드를 읽어서 알아서 처리하기 때문)
//                       <-> 부분 특수화 템플릿은 무조건 써야함 제외

//               3. (중요!) 템플릿 호출시 function or class명<실제typename1, ...>(parameter1,... )' 에서 <실제typename1, ...>이 생략이 가능하지만, 가급적이면 자료형 정보를 명시하는 것이 프로그래머 입장에서 편함
//                    -> 특수화 된 템플릿이 존재할 시에 override 된 함수의 내용이 각각 다른 경우에, 해당 parameter의 자료형을 명시해 놓으면, 컴파일러가 어떤 함수를 호출해야 하는지 구분하는데 유용


//      2.2 명시적 구체화(explicit instantiation)
//          : 사용자가 직접 원하는 function이나 class에다 template 키워드와 함께 템플릿 parameter를 명시하는 [(템플릿) 특수화(specialization)]를 통해
//             -> 원하는 특정 parameter 자료형이 들어오면, 어떤식으로 function의 내용을 수행하라고 수동 지시하는 행위 
//                 <-> 호출, 생성이 확정된 function 템플릿, class 템플릿들에 한해서만, 사용하는 자료형에 해당하는 overloading 버전들만 모두 자동으로 쭉 생성해주는 암시적 구체화 (implicit Instantiation)와 다름

//                ex) template <typename T> void swap(T a, T b);
//                    template void swap<int>(int a, int b);       <- 프로그래머가 직접 (템플릿) 특수화(specialization) 코드를 입력하여, swap함수를 int 자료형을 받는 형태로 내용을 구체화를 시키라고 수동 지시 
//                                                                      -> 반드시 특수화(specialization)에 대해서 공부할 것 (애초에 function만 적용 가능함)

//            - (중요!) 특수화(specialization)는 애초에 function(class멤버함수, 전역함수)만 적용 가능함
//                      (= 명시적 구체화(explicit instantiation)도 function(class멤버함수, 전역함수)만 가능)


//      3. (템플릿) 구체화된 코드 생성
//          : 컴파일러가 2번의 과정을 통해 생성된 인스턴스의 구체화된 코드를 통해, 실제 데이터 타입에 대한 작업을 수행하는 함수, 클래스 또는 객체를 생성함 

//      4. 컴파일 및 링크
//          :  컴파일러는 템플릿을 사용하여 생성된 구체화된 코드를 컴파일하고, 필요한 경우 링크 단계에서 이 코드를 최종 실행 파일에 연결


//   # 템플릿의 특징
// 
//     1. 컴파일 단계에서 function이나 class멤버들을 직접 생성하기에, function나 class에 템플릿을 많이 적용하는 만큼 쓰면 컴파일 속도가 느려짐
//     2. 컴파일 단계에서 코드를 추가하는 것이기에, 그 이후 프로그램 처리 속도랑은 관계 X
// 
//     3. (장점) 수많은 경우의 수에 맞춰 적어야 할 overloading 버전 작성을 일괄적으로 처리하는거라, 제대로만 만들어 두면 편의성이나 코드 완성도나 전부 높아질 수 밖에 없음
//     4. (단점) 포괄적인 함수나 클래스의 정의부만 양식으로 적어주는거라 예측하지 못한 자료형으로 인해 안정성은 떨어질 수 밖에 없음
// 
//     5. JAVA에서는 이를 제너릭스(generics)라고 부름
//         -> 제너릭스(generics) = 템플릿 + 컴파일 과정에서 객체 자료형 타입 check 추가
// 
//     6. (중요!) 템플릿이 호출될 시 function이나 class나 어떤 종류라도 전부 호출 될때, '함수명<호출에 쓰인 parameter 자료형>(parameter1,... )' 에서 <호출에 쓰인 parameter 자료형>을 수행함 
//          -> 템플릿 호출시 <실제typename1, ...> 부분은 생략해도 상관없음 (= 어차피 컴파일러가 호출된 코드를 읽어서 알아서 처리하기 때문)
//              <-> 부분 특수화 템플릿은 무조건 써야함 제외


//   # 안정성이 부족함에도 템플릿 사용 이유?
//      : 포괄적인 함수나 클래스의 정의부만 양식으로 적어주는거라 예측하지 못한 자료형으로 인해 안정성은 떨어질 수 밖에 없다? 팩트임
//         -> BUT! 진짜 제대로 만들어만 놓는다면? 코드의 완성도가 높아지고, 코드를 사용하기도 쉬운지라 유지보수 생산성 효율도 증가하기 때문 
//            -> 이러한 장점이 STL(Standard Template Library)처럼 성능과 안정성이 검증된 라이브러리와 함께면 시너지가 대폭 증가함
//               (= 만들기는 어려운데, 일단 제대로만 만들어서 안정성이 검증되면, 그떄부터는 그냥 가져다 쓰면 된다는 의미)


//   # 템플릿 사용시 주의사항
//      1. 가능한 다양한 자료형에 대해 포괄적으로 적용할 수 있도록 함수 내용이 범용적인 자료형을 포괄할 수 있도록 설계해야 함
//      2. 템플릿 정의시 1번째 <>안에 범용 자료형을 의미하는 typename을 치환하는 템플릿 기호로 표기시에는 일반적으로 T를 사용
//      3. 컴파일 단계에서 만들어지기 때문에, 컴파일 시간이 늘어나게 되는건 감안해야 함
//      4. 함수의 호출 구문으로 parameter의 자료형을 확인하고 자료형 별로 함수를 제작해야 함 (오버로딩)
//      5. (중요!) 함수 템플릿이나 class 템플릿이나 호출 및 생성시, function or class명 옆의 <>안에 자료형 정보를 생략하건 생략하지 않건 그 의미하는 바에 차이는 없음(컴파일 과정에서 처리)
//          -> 그렇지만! 가급적이면 자료형 정보를 명시하는 것이 프로그래머 입장에서 편함
//              -> 특수화 된 템플릿이 존재할 시에 override 된 함수의 내용이 각각 다른 경우에, 해당 parameter의 자료형을 명시해 놓으면, 컴파일러가 어떤 함수를 호출해야 하는지 구분하는데 유용



// (템플릭) 특수화 (specialization)
//  : 기존에 템플릿이 작성된 [function(class 멤버함수, 전역함수)]를 호출할 시, 고정된 특정 자료형을 parameter로 가져오는 경우에는 '전혀 다른 알고리즘으로 처리(= override)'하라는 개념의 템플릿 양식
//     -> 쉽게 말해, 작성된 함수 템플릿의 특정 자료형에 대해서만 예외 처리 override를 하는 것을 의미
//         -> 템플릿의 명시적 구체화(explicit instantiation)를 작성할 때 템플릿 특수화 문법을 사용함


//   # 특수화 된 '함수 템플릿' 정의 형식
//      : template <> 자료형 function명 <구체적인자료형>(구체적인자료형 parameters...) { 함수 정의 }
//                 --                   ----------------
//            (생략가능!)              (조건부 생략가능!)              <- (중요!) 특수화 된 함수 템플릿도 정의건 생성이건 function명 옆의 <자료형.. > 부분은 '유추할 수 있는 경우에 한해서' 생략이 가능함 
//       -> 가변 자료형 사용 X           -> BUT 사용 추천                          -> 단! 특수화 된 템플릿이면 가급적이면 <자료형> 정보를 작성하거나, 최소한 parameter로 들어간 값의 자료형을 명시라도 명확히 하는 것이 에러 방지나 예측에 유용함 

//         ex) template <typename T> void swap(T a, T b);              <- 기존 입력된 함수 템플릿 
//             template void swap<int>(int a, int b);                  <- 프로그래머가 직접 (템플릿) 특수화(specialization) 코드를 입력하여, swap함수를 int 자료형을 받는 형태로 내용을 구체화를 시키라고 수동 지시 


//   # (중요) 특수화 템플릿 종류별 호출 및 생성하는 형식
//      : 기존의 템플릿 작성과 유사하지만, 단지 특수화 템플릿에 선언된 function여서 특정한 자료형만 parameter로 들어가는 경우 override된 내용을 출력함 (= class 생성자 함수는 고려하지 않음)
//          -> (중요) 특수화 템플릿은 기존 템플릿 호출 및 생성과 비슷하게, function or class명 옆의 <자료형>을 생략은 가능하나, '유추할 수 있는 경우에 한해서'만 가능함...
//             -> BUT! 가급적이면 해당 parameter의 자료형을 명시해 놓는 쪽이 컴파일러로 하여금 일반이나 특수화 된 함수 템플릿 중 무엇을 호출해야 하는지 명확하게 하므로 오작동 가능성을 낮출수 있음


//   # (중요) 함수의 특징
//      : 템플릿이 아닌 function, 함수 템플릿, 명시적 특수화 함수 템플릿, 3가지 전부 같은 function명이란 가정하여 override가 가능함


//   # 특수화(specialization) 사용시 주의사항
//      1. (중요) class 생성자 함수는 사용이 불가능 함 (= 생성자 함수는 typename 자료형을 쓰는 템플릿에서 내용을 바꾸는 override가 불가능 함)
//          -> class 멤버함수는 특수화가 가능함 (애초에 함수 템플릿 만이 대상)
//              -> 단! 부분 특수화는 불가능

//      2. 해당 템플릿은 parameter가 가변 자료형 (= typename)을 사용하지 않는 경우를 상정함
//         (= 따라서 1번째 <>에 typename과 T같은 치환문자가 들어가지 않은 빈 <>가 들어가는게 정석임)
//             -> <>는 있으나 마나라서 생략가능!

//      3. 특수화 함수 템플릿 정의 시 <> 생략 가능 여부
//          - template<>의 <>는 생략 가능
//          - 2번째 <자료형>인, function명 <자료형>의 생략은 '유추가능 여부'라는 조건부로 가능하나, 가급적 써주는 게 에러 방지나 결과예측에 유용함

//      4. 특수화 함수 템플릿 호출 시 <> 생략 가능 여부
//          - function명 <자료형>의 생략은 '유추가능 여부'라는 조건부로 가능하나, 가급적 써주는 게 에러 방지나 결과예측에 유용함

//      5. 만약 호출 함수 분석결과 중복된 overloading 함수들이 발견될 시 실행의 우선순위는 다음과 같음 
//          : 일반함수 > 템플릿 특수화 함수 > 템플릿 함수


// (템플릭) 부분 특수화(Partial specialization)
//  : '일반 function'을 대상으로 하는 함수 템플릿에 사용되는 function의 parameter가 가변 자료형도 있지만, 고정된 특정 자료형도 같이 존재하는 경우 사용하는 템플릿 양식
//     -> 쉽게 말해, 일부는 시즈모드 일부는 퉁퉁이 처럼, 2개 이상의 parameter 자료형이 선언되었는데, 가변 자료형과 고정 자료형이 혼재되어 있어서, 일부 parameter에 대해서만 특수화 처리를 해야하는 함수 템플릿를 의미함 
//         -> 부분 특수화를 많이 할 경우 절대적 소스코드가 늘어날 수는 있지만, 결국 목적코드로 생성되는 기계어 코드의 양은 같음

//             ex) template <typename T, int count> void display <T, count> (T value) {  내용  }
//                  -> [일반 function]을 대상으로, 특수화 함수 템플릿의 <>안의 템플릿 parameter가 '가변 자료형 + 일반 자료형'으로 구성되어 있는 경우


//   # 부분 특수화 템플릿 정의 형식
//      : template <typename T, ... , 구체적인자료형1 변수명1, ... > 자료형 함수명 <T, ... , 변수명1, .... > (T value...) { 함수 정의 }
//                                    -----------------------------                -------------------------
//                                    (어떤 자료형이 고정 자료형인지                     (생략 가능!)                <- (중요!) 이 부분을 적어줘야 이것이 부분 특수화 템플릿임을 컴파일러가 인지함
//                                     꼭! 적어줘야 컴파일러가 인지) 

//        ex) template <typename T> void display(T value);                            <- 기존 입력된 함수 템플릿 
//            template <typename T, int count> void display(T value) {  내용  }       <- 부분 특수화 함수 템플릭 선언


//   # (중요) 부분 특수화 (함수) 템플릿 종류별 호출 및 생성하는 형식
//      : function명 <실제typename1, ... , 고정변수값1(or 고정타입변수명1), ...> (parameter1, ....);
//                   -----------------------------------------------------------
//                                         (생략 불가능!)                       <- (중요!) 반드시 이 부분을 적어줘야 고정된 템플릿 파라미터인 고정변수값1 or 고정타입변수명1...의 값을 받아서, 부분 특수화 함수 템플릿의 내용을 실행이 가능함
//                                                                                           -> (중요!) 반드시 호출시 선언된[템플릿 parameter]의 갯수와 자료형에 맞는 타입명과 값을 가진 고정된 타입의 데이터들을 <>안에 입력해야 함
//        ex) int a = 10;
//            display <char, 10>('A');                                          <- 호출시 <char, 10>와 같은 부분을 선언부의 <typename T, int count>와 맞게 적어줘야 함 
//            display <double, a)('A')


//   # 부분 특수화(Partial specialization) 사용시 주의사항
//      1. (중요!) 오로지 [일반 function]에 한해서만, 부분 특수화 템플릿은 사용 가능함 
//                (= class와 연관된 멤버함수나 생성자 함수나 부분 특수화 사용 X)

//      2. (중요!) 부분 특수화 된 함수 템플릿을 정의시, 반드시 함수 호출시 선언되는 parameter들의 갯수만큼 'typename T'와 '고정자료형 변수명'둘을 1번째 <> 안에 입력해야 함
// 
//           ex) display() 라는 함수에 고정자료형 parameter 1개와 가변자료형 parameter가 있으면, 2개에 해당하는 만큼을 자료형 정보를 1번째 <>안에 넣음)
// 
//      3. (중요!) 부분 특수화 된 함수 템플릿을 호출시, typename 부분의 구체적 자료형과 고정 자료형에 맞는 데이터들을 정의되었던 '템플릿 parameter의 갯수'만큼을 <>안에 입력해야 함
//                 (= 메인 템플릿의 1번째 <>안의 템플릿 paramter의 갯수가 2개의 경우, 사용자는 반드시 <>안에 자료형 및 변수값 or 변수명에 해당하는 템플릿 매개변수를 2개 전달)

//          ex) template <typename T, int count> void display(T value) {  내용  }       <- 부분 특수화 함수 템플릿 선언
//              display <char, 10>('A');                                                <- 호출시 <char, 10>와 같은 부분을 선언부의 <typename T, int count>와 맞게 적어줘야 함

//      4. 2번의 이유로 부분 특수화(Partial specialization)에서 default parameter는 표시하지 않음  
//          -> 어차피 정의건 선언이건 부분 특수화 템플릿에서는 모든 종류의 <자료형>의 템플릿 parameter를 생략하지 말고 입력해야 하므로..
//              -> 메인 템플릿에 정의된대로 선언시 <>에 반드시 입력된 템플릿 parameter들을 그대로 받음

//      5. 부분 특수화(Partial specialization)에서 Typename 자료형인 parameter 객체 T의 타입이 결정되는 방식을 주의 
//          -> 다른 특수화 된 함수 템플릿과 overload 된 선언부의 내용이 중복되는 경우 예측하지 못해 의도하지 못한 상황이 발생함을 주의하라는 의미

//      6. 부분 특수화를 많이 할 경우 절대적 소스코드가 늘어날 수는 있지만, 결국 목적코드로 생성되는 기계어 코드의 양은 같음