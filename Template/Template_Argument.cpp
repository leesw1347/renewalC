//
// Created by lsw94 on 22-08-17.
//

#include <iostream>
#include <deque>
#include <vector>

template<typename T, template<typename ELEM> class CONT = std::deque>
class Stack : public CONT<T> {
private:
    CONT<T> elems; // 템플릿 변환을 사용하여 실제 사용하는 타입을 명시한다
public:
    Stack() : CONT<T>() {
        std::cout << "Stack 클래스 기본 생성자 호출" << std::endl;
    }

    void push(T const &x) {
        elems.push_back(x);
    }

    void pop() {
        elems.pop_back();
    }

    [[nodiscard]] const T &top() const {
        elems.back();
    }

    [[nodiscard]] bool empty() const {
        return elems.empty();
    }
};

// 타입이 아닌 템플릿 매개변수 (None Type Template Arugment)
template<class T, int size>
class MyFile {
private:
    T *filepos;
    static int array[size]; // 타입이 아닌 매개변수를 사용하여 배열의 크기를 지정한다.

public:
    MyFile();

    ~MyFile();

    void advance();
};

template<class T, int size>
MyFile<T, size>::MyFile() {
    std::cout << "MyFile 클래스 기본 디폴트 생성자 호출" << std::endl;
}

template<class T, int size>
MyFile<T, size>::~MyFile() {
    std::cout << "MyFile 클래스 소멸자 호출" << std::endl;
}

template<class T, int size>
void MyFile<T, size>::advance() {

}

/* 타입 템플릿 매개변수 ( type template parameter )
 * int 타입이나, char와 같은 타입
 * 클래스, 구조체 공유체와 같은 묶음 타입
 * T::value_type 과 같은 내부에서 사용하는 선언된 데이터 타입
 *  ex) std::map<int, const char *>::value_type, (typedef std::pair<int, const char *> value_type)
 * */
template<typename T, int T2, char T3>
class Item {
private:
public:

};

/*
 * "=" 디폴트 데이터 타입
 * */

// allocator 클래스 템플릿을 선언한다.
template<typename Type>
class allocator {
};

// Allocator 매개변수의 디폴트 타입으로 만든다.
template<typename Type, typename Allocator = allocator<Type>>
class stack {
private:
public:
};

template<class T1, class T2=T1>
class X {
};

int main(int argc, char *argv[]) {
    // 템플릿 템플릿 매개변수를 인수로 사용한다면 std::vector 클래스 템플릿을 명시해주어야 한다.
    Stack<int, std::vector> vStack2;
    vStack2.push(200);
    vStack2.push(130);
    while (!(vStack2.empty())) {
        std::cout << vStack2.top() << std::endl;
        vStack2.pop();
    }

    /*Allocator 매개변수에 대응되는 데이터 타입을 명시하지 않는다면, 자동적으로 Allocator<int>로 할당된다*/
    stack<int> MyStack;
    stack<int, float> MyStack2;
    X<int> x2; // X<int, int>

    std::cout << "Hello" << std::endl;
}