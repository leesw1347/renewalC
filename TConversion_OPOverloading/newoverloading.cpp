//
// Created by lsw94 on 22-08-25.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>

void *operator new(size_t sz) {
    /* operator "new"에 대한 연산자 오버로딩 */
    std::cout << "new called. 크기 : " << sz << std::endl;
    if (sz < 0){
        return nullptr;

    }
    return std::malloc(sz);

}

int main(int argc, char *argv[]) {


}