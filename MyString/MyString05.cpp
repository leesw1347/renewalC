//
// Created by lsw94 on 22-08-14.
//

#include "MyString05.h"

#include <vector>
#include <string>
#include <iostream>

MyString05::MyString05(const char *n) {
    std::cout << "MyString05 클래스 생성자 호출(" << this << ") " << n << std::endl;
}

MyString05::MyString05(const MyString05 &other) : data(other.data) {
    std::cout << "MyString05 클래스 복사 생성자 호출(" << this << ") " << std::endl;
    count++;
}

/**
 * 이동 대입연산자
 * @param other 이동 생성자 Rvalue
 */
MyString05::MyString05(MyString05 &&other) noexcept
//        : data(other.data), length(other.length) {
{
    std::cout << "MyString 클래스 이동 생성자 호출" << std::endl;
    // rvalue 참조는 함수가 반환된 다음 삭제된다.
    printf("MyString::MyString(MyString && '%s')\n", data);
    /*other.data = nullptr; // 인수로 사용한 객체 소멸 시, 리소스 (char *)를 삭제하지 못하도록 nullptr를 만든다.
    // 깊은 복사를 수행하지 않으므로 처리 속도가 빠르다.
    other.length = 0;*/
    std::swap(this->data, other.data);
    ++count;
}

MyString05::~MyString05() {
    std::cout << "MyString05 클래스 소멸자 호츨(" << this << ")" << std::endl;
}

MyString05 &MyString05::operator=(const MyString05 &other) {
    std::cout << "MyString05 클래스 복사 대입 연산자 호출" << std::endl;
    if (this != &other) {
        data = other.data;
    }
    printf("MyString &MyString::operator = (MyString & '%s')\n", this->data);
    ++count;
    return (*this);
}

/**
 * 이동 대입 연산자의 rvalue 참조 역시 무명 변수이므로 함수 반환 후 자동 삭제된다.
 * @param other 이동대입을 하기 위한 rvalue MyString05 참조 객체
 * @return *this
 */
MyString05 &MyString05::operator=(MyString05 &&other) noexcept {
    std::cout << "이동 대입연산자 오버로딩 호출" << std::endl;
    if (this != &other) {

        /*char *mData = this->data;
        int mLength = this->length;

        // 인수의 데이터를 서로 교환한다
        data = other.data;
        length = other.length;
        other.data = mData;
        other.length = mLength;*/

        // 이동 대입 연산자 오버로딩은 보통 swap() 함수를 사용하여 멤버 변수의 데이터를 서로 교환한다
        std::swap(this->data, other.data);
        std::swap(this->length, other.length);
    }

    printf("MyString& MyString::operator=(MyString && '%s')\n", this->data);
    return *this;
}

void MyString05::SetString(const char *n) {
    std::cout << "MyString05::SetString " << n << std::endl;
}

const char *MyString05::GetString() const {
    return data;
}

/**
 * NRVO (Named Return Value Optimization)
 * @param ptr: 생성하려는 문자열
 * @return MyString 객체
 */
MyString05 create(const char *ptr) {
    // const 지정자나 volatile 지정자가 없는 순수한 변수여야 한다.
    MyString05 myString05(ptr); // 지역변수 생성
//    std::cout << "일로는 들어온거??" << std::endl;
    /*return myString05; // 복사생성자 호출하지 않는다.*/

    /*아래와 같이 객체를 생성하여 반환하는 경우에는 이동 생성자의 호출이 생략된다*/
    return MyString05{myString05}; /*무명변수를 생성한다*/
}

/**
 * 함수 내부에서 객체를 생성하여 throw를 사용하여 예외를 던졌을 때,
 * 복사 생성자의 호출이 생략된다
 * @param ptr :
 */
void foo(const char *ptr) {
    throw MyString05(ptr);
}
