//
// Created by lsw94 on 22-08-14.
//

#include "MyString05.h"

int main(int argc, char *argv[]) {
/*    MyString05 x = create("Hello World");
    std::cout << "x.GetString() : " << x.GetString() << std::endl;
    MyString05 *p = new MyString05(create("Hello World"));*/

/*try ~catch를 이용해서 예외문을 받아낸다*/
    try {
        foo("throw MyString");
    } catch (MyString05 &myString05) {
        std::cout << "Throw가 호출되었습니다 " << &myString05 << std::endl;
    }
}