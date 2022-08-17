//
// Created by lsw94 on 22-08-17.
//
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <deque>
#include <list>

template<typename T>
struct MyClass {
    void f(int); // 일반 멤버 함수이다.

    template<typename T2>
    void f(T2); // 멤버 함수 템플릿이다
};

/* MyClass의 일반 멤버 함수 void f(int)에 대한 정의문
 * 함수 내부의 템플릿 인수를 미리 int로 정의하여 사용할 수 있다*/
template<typename T>
void MyClass<T>::f(int x) {
    std::cout << typeid(T).name() << ", 내부 : int " << std::endl;
}

/* MyClass의 멤버 함수 템플릿의 정의문으로
 * 두개의 서로 다른 타입 템플릿 매개변수를 사용할 수 있다
 * */
template<typename T>
template<typename T2>
void MyClass<T>::f(T2 t2) {
    std::cout << typeid(T).name() << ", 내부 " << typeid(T2).name() << std::endl;
}

/* 템플릿 내 템플릿 매개변수
 * 콘솔에 출력을 위한 << 출력 연산자 오버로딩*/
template<template<class, class...> class C, typename T, class... Args>
std::ostream &operator<<(std::ostream &os, const C<T, Args...> &objs) {
    for (auto const &obj: objs) {
        os << obj << " ";
    }

    return os;
}

/* f(), g() 함수는 같은 타입과 같은 매개변수를 사용하므로, 함수 오버로딩을 적용할 수 없어 분리하였다
 * 만약 아래에서 deque를 사용하고 싶다면,
 * */
template<template<class, class> class V, class T, class A>
void f(V<T, A> &v) {
//    std::cout << typeid(T).name() << std::endl;
//    std::cout << typeid(A).name() << std::endl;
    for (auto const &temp: v) {
        std::cout << temp << " ";
    }
    std::cout << std::endl;
}

template<template<class> class V, class T>
void g(V<T> &v) {
    std::cout << typeid(v).name() << std::endl;
    while (v.empty()) {
        T temp = v.back();
        v.pop_back();
        std::cout << temp << " ";
    }
    std::cout << std::endl;
}

int main(int ARGC, char *ARGV[]) {
    MyClass<std::string> myClass;
    myClass.f('t'); // MyClass의 멤버 함수 템플릿에 대해 암시적인 방법으로 템플릿의 인수를 정한다
    myClass.f(100); // template<typename T> void MyClass<T>::f(int x) 호출한다

    MyClass<int> n;
    n.f('t'); // 함수에 대해 암시적인 방법으로 템플릿 인수를 정한다
    n.f(100); // template<typename T> void MyClass<T>::f(int x)를 호출한다
    n.f<int>(130); // MyClass의 멤버 함수 템플릿의 템플릿 매개변수를 명시적인 방법으로 템플릿 인수를 정한다

    std::vector<double> vf{1.1, 2.2, 3.3, 4.4};
    /*연산자 오버로딩에 대해 명시적 템플릿 변환을 적용하고 자 한다면 에러가 발생한다*/
    std::cout << vf << std::endl;

    std::deque<int> di{1, 2, 3, 4};
    std::deque<float> df{1.0, 2.0, 3.0, 4.0};
    f(di);
    f(df);

    std::list<char> lc{'a', 'b', 'c', 'd'};
    f<std::list, char>(lc);

    // g(di); 암시적 템플릿 변환을 사용하고 자 한다면 에러가 발생한다
    g<std::deque, int>(di);

}