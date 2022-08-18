//
// Created by lsw94 on 22-08-18.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

/*클래스 템플릿을 선언하거나 정의한다*/
template<typename T>
inline std::string stringify(const T &x) {
    std::ostringstream out;
    out << x;
    return out.str();
}

/*전체 템플릿 특수화, 별도 템플릿 매개변수를 지정하지 않는다.
 * 템플릿 인수를 지정하여, 템플릿 매개변수와 또 다른 형식의 함수 오버로딩처럼 사용한다.*/
template<>
inline std::string stringify<bool>(const bool &x) {
    std::ostringstream out;
    out << std::boolalpha << x;
    return out.str(); // out 변수에 입력된 문자열을 반환한다
}

template<>
inline std::string stringify<double>(const double &x) {
    std::ostringstream out;
    const int sigdigits = std::numeric_limits<double>::digits10;
    out << std::setprecision(sigdigits) << x;
//    out << x;
    return out.str();
}

int main(int argc, char *argv[]) {
    std::cout << stringify<int>(100) << ", " << stringify<bool>(true) << ",  " <<
              stringify<double>(23.65) << std::endl;
}
