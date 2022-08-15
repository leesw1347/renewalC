//
// Created by lsw94 on 22-08-14.
//

#ifndef RENEWALC_MYSTRING05_H
#define RENEWALC_MYSTRING05_H

#include <iostream>

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


#endif //RENEWALC_MYSTRING05_H
