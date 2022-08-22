//
// Created by lsw94 on 22-08-23.
//

/*
 * reinterpret_cast 연산자는 위험성이 높기 때문에, reinterpret_cast 연산자보다
 * 다른 변환 연산자를 먼저 사용하는것을 추천한다*/

#include <iostream>

int f() {
    return 42;
}

int main(int argc, char *argv[]) {
    int i = 7;

    // f 함수를 새로운 이름의 함수로 만들어 사용한다.
    void (*fp)() = reinterpret_cast<void (*)()>(f);
    int (*fp2)() = reinterpret_cast<int (*)()>(fp);

    fp();
    char *p2 = reinterpret_cast<char *>(&i);


}