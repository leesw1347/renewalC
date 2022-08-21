//
// Created by lsw94 on 22-08-21.
//

#include <iostream>
#include <type_traits>

int main(int argc, char *argv[]) {

    std::cout << std::boolalpha;
    // value 변수는 bool 타입의 정적 변수로 비교 결과를 제공한다.
    std::cout << std::is_same<int, int32_t>::value << std::endl; // true
    std::cout << std::is_same<int, int64_t>::value << std::endl; // false
    std::cout << std::is_same<float, int32_t>::value << std::endl; // false
}