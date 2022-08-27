//
// Created by lsw94 on 22-08-27.
//

#include <iostream>
#include <deque>
#include <vector>

using std::vector;
using std::deque;

/*
 * 템플릿 템플릿 매개변수
 * */
template<typename T, template<typename ELEM> class CONT =  std::deque>
class Stack {
private:
    CONT<T> elems; /* 템플릿 변환을 사용하여 실제 사용하는 타입을 명시한다. */

public:

};


int main(int argc, char *argv[]) {

}