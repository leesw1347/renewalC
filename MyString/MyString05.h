//
// Created by lsw94 on 22-08-14.
//

#ifndef RENEWALC_MYSTRING05_H
#define RENEWALC_MYSTRING05_H

#include <iostream>

// 복사 생산자와 이동 샌산자 그리고 대입 연산자를 호출하는 횟수를 합산하는데 사용
uint16_t count = 0;

class MyString05 {
private:
    char *data;
    int length;
public:
    MyString05(const char *n = nullptr);

    MyString05(const MyString05 &other);

    MyString05(MyString05 &&other) noexcept;

    MyString05 &operator=(const MyString05 &other);

    // 이동 대입 연산자 오버로딩을 만든다
    MyString05 &operator=(MyString05 &&other) noexcept;

    void SetString(const char *n);

    const char *GetString() const;

    int GetLength() const;

    virtual ~MyString05();
};

MyString05 create(const char *ptr = nullptr);

void foo(const char *ptr = nullptr);

#endif //RENEWALC_MYSTRING05_H
