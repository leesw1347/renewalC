//
// Created by lsw94 on 22-08-21.
//

#include <iostream>
#include <type_traits>
#include <string>

template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
gcd(T lhs, T rhs) {
    std::cout << lhs << ", " << rhs << " = ";
    return lhs + rhs;

}

/* float 타입 또는 double 타입의 함수를 호출할 때 사용한다.
 함수의 3번째 인수는 디폴트 0값을 받는것으로 설정하였다.
 struct is_floating_point : <type_traits>
 템플릿 인수가 실수인지 아닌지 확인할 수 있는 정적 value 변수를 제공한다.
 */
template<typename T>
T gcd(T lhs, T rhs,
      typename std::enable_if<std::is_floating_point<T>::value, T>::type = 0) {
    std::cout << lhs << ", " << rhs << " = ";
    return lhs + rhs;
}

/* template<class T> struct is_fundamental : <type_traits>
 * 템플릿 인수가 기본 타입인지 아닌지 확인할 수 있는 정적 value 변수를 제공한다*/
class A {};

int main(int argc, char *argv[]) {
    std::cout << gcd<int>(100, 100) << std::endl;
    std::cout << gcd<double>(1.0, 2.0) << std::endl;

    // std::is_fundamental 구조체 템플릿을 활용해서, 기본 타입인지 아닌지 체크한다
    std::cout << std::boolalpha; // 출력 형태를 true, false로 변경
    std::cout << std::is_fundamental<A>::value << std::endl;
    std::cout << std::is_fundamental<int>::value << std::endl;
    std::cout << std::is_fundamental<int &>::value << std::endl;
}