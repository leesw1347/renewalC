//
// Created by lsw94 on 22-08-22.
//

#include <iostream>
#include <string>

class Enclose {
private:
    class Nested {
    private:
        std::string name;
    public:
        Nested(std::string &n) : name(n) {}

        void g() {
            std::cout << "Enclose 클래스의 내부 클래스의 " << name.c_str() << std::endl;
        }
    };

public:

    // 정적 함수로 내부 클래스를 객체로 생성하여 반환한다
    static Nested f(std::basic_string<char> n) {
        return Nested{n};
    }

};

int main(int argc, char *argv[]) {
    // Nested 클래스는 Enclode 클래스 내 private 접근 지정자에 선언되어 있으므로, 직접 선언하는 것을 허용하지 않는다.
    /*Enclose::Nested n1 = Enclose::f("객체 생성");*/

    // f() 함수는 public으로 선언되어 있기 때문에 사용이 가능하다.
    Enclose::f(std::forward<std::string>(std::string("객체생성"))).g();

    // Nested 클래스는 private으로 선언되어 있어서 접근이 불가능하다. 따라서 auto를 사용한다면 허용된다.
    auto n2 = Enclose::f("선언방법");
    n2.g();
}
