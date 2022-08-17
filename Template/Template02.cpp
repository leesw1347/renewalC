//
// Created by lsw94 on 22-08-17.
//

#include <iostream>

template<typename T>
void print(const T &t) { /*템플릿 매개변수를 참조로 사용한다*/
    std::cout << t << std::endl;
}

/*
 * 1번째 인수는 일반 타입 매개변수를 만들고 2번째 인수는 가변 매개변수로 만든다.
 * ...는 함수 인수-팩 확장 (function parameter pack extension)
 * */
template<typename First, typename ... Rest>
void print(const First &first, const Rest &... rest) {
    std::cout << first << ", ";
    print(rest...); /*함수의 나머지 인수에 대해 함수를 반복 호출 시킨다*/
}

/*
 * 함수 인수 확장 팩은 다음과 같은 방법으로 사용할 수 있다.
 * */
template<typename ... Ts>
void func(Ts ... args) {
    // sizeof...는 가변 인수의 개수를 반환한다.
    const int size = sizeof...(args) + 2;

    /* 가변 인수를 배열로 만든다 */
    int res[size] = {1, args..., 2};
    std::cout << "size of " << size << std::endl;

    // 범위 기반 for 문 내부에 가변 인수를 사용할 수 있다.
    for (auto i: {args...}) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    /* 람다 내 캡처절 또는 인수로 만들어 사용 할 수 있다. */
    auto lm = [&, args...] {

        return print(args...);

    };
    lm();

    std::cout << std::endl;
}

/* 클래스 템플릿 내부 멤버 함수 템플릿 */
template<typename T>
struct MyClass {
private:
public:
    void f(int); /*일반 멤버 함수이다*/
    template<typename T2>
    void f(T2); /*멤버 함수 템플릿*/
};

template<typename T>
template<typename T2>
void MyClass<T>::f(T2) {

}

template<typename T>
void MyClass<T>::f(int) {

}

int main(int argc, char *argv[]) {

    /*print(1);
    print(10, 20);
    print(100, 200, 300);
    print("first", 2, "third", 3.14159);*/

    func(1, 2, 3);

}