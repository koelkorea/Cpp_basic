﻿//   # 상속 관계에 놓인 class의 형식
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

//      - class간 상속관계 작성시 접근제어자 (안 적어두면 기본값 private로 적힘)
//         : 쉽게 말해, 부모의 멤버변수를 최소 어느정도 수준으로 접근권한을 규정할거냐? 로 이해하면 ㅇㅋ
//            -> public으로 상속하면 부모멤버의 접근제어자 모두 그대로 가져오고, private은 부모멤버에 대해서는 전부 private로 엄격히 가겠다는 의미
//               (= (중요) 부모멤버가 private인건 원래부터 자식이 어떻게 해볼 수 없다는것 의미 ! )
// 
//               1. 'class 자식클래스 : public 부모클래스' 의 의미
//                   : 부모클래스의 멤버변수에 적힌 접근제어자를 자식도 '그대로' 계승받음
// 		         
//               2. 'class 자식클래스 : protected 부모클래스' 의 의미
//                   : 부모클래스의 멤버변수에 적힌 접근제어자 중 'public에 해당하는 내용들은 자식은 protected'로 계승받음
//                     (= 부모클래스의 멤버변수 중 protected의 접근제어자는 똑같이 이어받음)
// 		         
//               3. 'class 자식클래스 : private 부모클래스' 의 의미
//                   : 부모클래스의 멤버변수에 적힌 접근제어자 중 public, protected에 해당하는 내용들은 자식은 '깡그리 private'로 계승받음
//                     (= 부모클래스의 멤버변수 중 똑같이 이어받는게 1도 없음)

//                   ex) 부모가 다음과 같은 경우, 상속시 접근제어자에 따라 자식이 규정하는 물려받은 멤버변수의 접근제어자 
//                       class parents {            
//                       
//                          private:				      <- 부모 멤버가 private이면 자식이 이를 제어 불가능
//                              int private1;		 
//                              int private2;	
// 		         
//                          protected:				   public:
//                              int protected1;	       int public1;
//                              int protected2;	       int public2;
//                       };

//                       (1) class private_child : private parents 의 경우 규정하는 부모멤버의 제어접근자
//                            -> private:
//                                 int protected1;	       
//                                 int protected2;	       
//                                 int public1;
//                                 int public2;

//                       (2) class protected_child : protected parents 의 경우 규정하는 부모멤버의 제어접근자
//                            -> protected:
//                                 int protected1;	       
//                                 int protected2;	       
//                                 int public1;
//                                 int public2;

//                       (3) class public_child : public parents 의 경우 규정하는 부모멤버의 제어접근자
//                            -> protected:				   public:
//                                 int protected1;	       int public1;	       
//                                 int protected2;	       int public2;	       


//      - 상속된 자식class의 생성자의 초기화리스트(initial list)의 부모class 생성자 대입되는 경우? 의 자식 객체 생성 과정

//         1. 해당 케이스 생성자의 의미 및 자식 객체 생성 과정
//           : 자식class의 생성자 함수 중 :을 써서 일부 parameter들을 생성자 함수에 호출(= 대입)하는 경우, 초기화 리스트(Initialize List)의 원칙으로
//              -> 1단계) 자식 class 생성자의 정의부 실행전에, 자식의 기반인 부모class의 생성자 함수를 먼저 호출하는데 일부 parameter를 사용하여 부모 객체를 생성하고 부모의 멤버변수를 초기화하는데 사용
//              -> 2단계) 그 부모class도 자신의 부모가 존재하는 경우, 부모의 생성자도 마찬가지로 자신의 부모 생성자를 초기화 리스트(Initialize List) 방식으로 호출하면, 마찬가지로 함수 stack 이 쌓이며, 결국 최선조의 객체가 먼저 생성됨
//              -> 3단계) 그렇게 [최후손 class 선언부 -> ... -> 최선조 객체의 선언부, 정의부 실행 -> ... -> 최후손 class 정의부 실행] 패턴대로 생성자 함수가 실행된 결과 자식 class객체가 탄생함

//         2. 해당 케이스의 작성 형식 예시
//           : Class 클래스명 : 접근제어자 부모클래스명1, ... ,  접근제어자 부모클래스명n {
//                클래스명(int param1, .... ,  int paramN) : 부모클래스명1(param1...), .. ,  부모클래스명n(paramN...) 
//             }
// 	    
//             ex) 다중상속 클래스의 생성자에서의 부모생성자를 초기화리스트에 쓴 경우
//                  -> School 클래스 생성자를 작성하면, 그 부모들인 Buliding, ClassRoom, Office 생성자가 먼저 호출되어 그들의 객체가 생성됨
// 	    
//                 class School : public Buliding, public ClassRoom, public Office {           <- School 클래스는 Buliding, ClassRoom, Office 클래스를 모두 부모로 두고 상속 
//                 
//                     School(int _width, int _height, int _students_size, int _class_size, int _teacher_size, string _school_name) : Buliding(_width, _height), ClassRoom(_students_size), Office(_teacher_size) {
//                          school_name = _school_name;
//                     }
//                 };


//   # (복습) 초기화 리스트(Initialize List) 
//      : (중요!) 콜론(:)을 이용하는 초기화법, 정의부보다 우선하여 실행된다는 장점이 있어, const 멤버변수의 초기화에 쓰임                        
//         -> 클래스명(자료형 parameter명...) : 가담O 멤버변수(parameter명) , ...  { 가담X 멤버변수 = parameter 사용하거나 가공한 값 }												
//                                                        
//            ex) class A 멤버는 다음과 같다 가정 ( int a; double b; char c; )
//	        
//                A (int _a, double _d, char _c) : a(_a), c(_c) {
//                    b = _b;
//                }

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


// 상속에서의 접근제어자 설명 + 초기화리스트를 통한 자식클래스 생성자 호출시 부모클래스 생성자 먼저 호출하는 예시
#include <string>
#include <iostream>
using namespace std;

// 사람 class - 생성자, 멤버함수
class human {

	// (중요) 부모클래스의 멤버가 private인건 원래부터 자식이 어떻게 해볼 수 없음!
	//  -> tmp는 후손 클래스라도 사실상 건들수 없는 부모의 절대영역
private:
	int tmp;

	// protected : 해당 클래스와 상속 클래스 내부에서만 참조 및 호출 가능
protected:
	string name;
	string phone;

	// (중요) 생성자는 접근제어자와 상관없이 호출 가능 (얘는 class 객체를 선언 떄 쓰는 거라.. 못 쓰면 클래스가 버려지는거라 가능)
	human(string _name, string _phone) {
		name = _name;
		phone = _phone;
	}
};

// 학생 class - 생성자, 멤버함수
//  -> 'class 자식클래스 : protected 부모클래스' 의 의미
//       : 부모클래스의 멤버변수에 적힌 접근제어자 중 'public에 해당하는 내용들은 자식은 protected'로 계승받음
//         (= 부모클래스의 멤버변수 중 private, protected의 접근제어자는 똑같이 이어받음)
//            -> student는 부모 human의 protected 멤버변수를 protect 영역에 그대로 물려받음
class student : protected human {

protected:

	// [부모의 protect 멤버가 이렇게 같이 있는 효과를 냄]
	//   -> 실제 자식 class 객체는 로는 부모 class 객체가 먼저 만들어지고 그걸 기반으로 보강되는 구조 (당장 student 생성자 참고)
	// string name;
	// string phone;

	unsigned long studentId;
	string major;


	// Class 클래스명 : 접근제어자 부모클래스명 {   클래스명(int param1, .... ,  int paramN) : 부모클래스명1(param1...)   }
	//  -> student 클래스의 parameter 중 _name, _phone은 선언부에서 부모클래스인 human의 생성자 함수를 실행해야 human 클래스 객체를 생성하는데 사용되고, 그 이후 student 클래스 객체의 생성에 나머지 parameter가 들어감 
	//      -> 실제 자식 class 객체는 로는 부모 class 객체가 먼저 만들어지고 그걸 기반으로 보강되는 구조인 이유
	student(string _name, string _phone, unsigned long _studentId, string _major) : human(_name, _phone) {
		studentId = _studentId;
		major = _major;
	}
};

// 졸업생 class - 생성자, 멤버함수
//  -> 'class 자식클래스 : public 부모클래스' 의 의미
//	     : 부모클래스의 멤버변수에 적힌 접근제어자를 자식도 '그대로' 계승받음
class graduate : public student {

protected:

	// [조부모 + 부모의 protect 멤버가 이렇게 같이 있는 효과를 냄]
	// string name;
	// string phone;
	// unsigned long studentId;
	// string major;


public:
	string job;

	// 자식 class 생성자와 초기화리스트 방법으로 함께하는 부모 class 생성자 
	//   : 자식 class 생성자의 정의부 실행전에, 자식의 기반인 부모class의 생성자 함수를 먼저 호출하는데 일부 parameter를 사용하여 부모 객체를 생성하고 부모의 멤버변수를 초기화하는데 사용
	//      -> 그 부모class도 자신의 부모가 존재하는 경우, 부모의 생성자도 마찬가지로 자신의 부모 생성자를 초기화 리스트(Initialize List) 방식으로 호출하면, 마찬가지로 함수 stack 이 쌓이며, 결국 최선조의 객체가 먼저 생성됨
	//         -> 그렇게 [최후손 class 선언부 -> ... -> 최선조 객체의 선언부, 정의부 실행 -> ... -> 최후손 class 정의부 실행] 패턴대로 생성자 함수가 실행된 결과 자식 class객체가 탄생함
	//             ex) graduate 선언부 -> student 선언부 -> human 선언부, 정의부 실행 -> student 정의부 실행 -> graduate 정의부 실행
	graduate(string _name, string _phone, unsigned long _studentId, string _major, string _job) : student(_name, _phone, _studentId, _major) {
		job = _job;
	}

	// 선조 및 부모 클래스들의 모든 멤버가 protected 이기에?
	//  -> 선조 class들의 멤버변수에 제약없이 접근이 가능함
	void showStudentInfo() {
		cout << "[졸업생 정보]" << endl;
		cout << "성    명 : " << name << endl;
		cout << "전화번호 : " << phone << endl;
		cout << "학    번 : " << studentId << endl;
		cout << "전    공 : " << major << endl;
		cout << "직    업 : " << job << endl;
	}
};

int main() {

	// 생성자는 접근제어자의 영향 안 받음
	graduate graduateStudent("michelin", "010-1234-5678", 202312345, "Economics", "worker");

	// showStudentInfo()는 public 영역에 위치한 멤버함수라 main()에서도 호출이 가능함
	graduateStudent.showStudentInfo();

	return 0;
}