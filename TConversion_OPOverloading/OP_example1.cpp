//
// Created by lsw94 on 22-08-23.
//

#include <iostream>

class Class {
public:
    Class(int x) : _x(x) {
        /*생성자를 정의한다.*/
    }

    const Class sum(Class &b) const {
        /*멤버 함수를 정의한다.*/
        return static_cast<const Class>(Class(this->_x + b._x));
    }

    /* 연산자 오버로딩이라고 하는 멤버 함수를 정의한다 */
    const Class operator+(Class &b) {
        return static_cast<const Class>(Class(this->_x + b._x));
    }

private:
public:
    int _x;
};

/*다른 타입의 데이터를 반환하는 연산은 전역 연산자 오버로딩 (Global Operator Overloding) 또는
 * Non-Member Operator Overloading으로 제작해야 한다.*/
std::ostream &operator<<(std::ostream &os, const Class &b) {

}

template<
        class T1,
        class T2>
bool operator==(const T1 &a, const T2 &b) {
    return true;
}

/* Class 타입은 일반 데이터 타입을 총칭한 타입을 의미한다.
 * 전역 함수와 연산자 오버로딩으로 변경한다면 아래와 같이 선언해주어야 한다.*/
Class sum(Class &a, Class &b) {
    return {a._x + b._x};
}

Class operator+(Class &a, int b) {
    return {a._x + b};
}

int main(int argc, char *argv[]) {

    Class a(10), b(100);
    Class c = a + b; // + 연산자 오버로딩 함수 호출
    auto d = a.sum(b); // Class 내 sum 멤버함수 실행
    auto e = a.operator+(b); // .operator+() 연산자를 호출해서 출력

}