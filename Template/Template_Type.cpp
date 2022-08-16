//
// Created by lsw94 on 22-08-16.
//

#include <iostream>

template<typename T1>
struct string {
private:
public:
    // 아래는 멤버 템플릿 함수
    template<typename T2>
    T1 compare(const T2 &);

// 템플릿 함수처럼 생성자 역시 만들 수 있다
    template<typename T2>
    string(const std::basic_string<T2> &s);
};

// 아래는 string<T1>::compare<T2>의 정의문
template<typename T1>
template<typename T2>
T1 string<T1>::compare(const T2 &t2) {
    std::cout << "string<T1>::compare(const T2&) 함수 호출" << std::endl;
}

template<typename T1>
template<typename T2>
string<T1>::string(const std::basic_string<T2> &s) {

}

// 타입 템플릿 (Alias Template)
template<class T>
using ptr = T *;

// 타입 템플릿을 사용하는 방법은 아래와 같다.
ptr<int> x;

// 변수 템플릿 (Variable Template)
template<typename T>
constexpr T pi = T(3.141592);

// Type 템플릿 매개변수에 대해 디폴트 int 템플릿 인수를 정의하였다면 생략할 수 있다.
template<class T, class Type = int>
T max(Type a, Type b) {
    return a > b ? a : b;
}

int main(int ARGC, char *ARGV[]) {
    x = nullptr;
    std::cout << x << std::endl;
    double item = pi<double>;
    std::cout << item << std::endl;
}