//
// Created by lsw94 on 22-08-21.
//

#include <iostream>
#include <string>
#include <type_traits>

/*enable_if 구조체 템플릿은 bool 타입의 true 또는 false냐에 따라
 * 다른 클래스 템플릿 또는 함수 템플릿에 대한 활성화 또는 비활성화시키는 용도로 사용한다.*/

/*템플릿 인수가 lvalue 참조가 아니라면, 아래 함수 템플릿을 활성화 시킨다
 * lvalue가 아니라면, (변수라면) 해당 템플릿 클래스를 호출한다.
 * 아래와 같이 typename 지정자를 활용해서, 반환되는 함수의 데이터 타입이 의존타입이란 사실을 명시해줘야 한다.
 * 컴파일 시점에 활성화 되는 메타 프로그램이기 때문에 2개의 min() 함수는 같은 템플릿 매개변수를 사용하더라도 문제가 발생하지 않는다.
 * */
template<class T>
typename std::enable_if<!std::is_lvalue_reference<T>(), T &>::type min(T &a, T &b) {
    std::cout << "변수" << std::endl;
    return (a < b) ? a : b;
}

/*템플릿 인수가 lvalue 참조이라면 아래 함수 템플릿을 활성화 시킨다
 *만약 아니라면 아래 template은 T 타입에 대해서 참조를 활성화 시키지 않는다.*/
template<class T>
typename std::enable_if<std::is_lvalue_reference<T>::value, T>::type min(T a, T b) {
    std::cout << "참조" << std::endl;
    return (a < b ? a : b);
}

/*템플릿 인수가 포인터라면 아래 함수 템플릿을 활성화 시킨다*/
template<class T>
T min(T *a, T *b) {
    std::cout << "포인터 ";
    return (*a < *b) ? *a : *b;
}

class Shape {
private:
    std::string name;
public:
    Shape(std::string n) : name(n) {
    }

    void GetArea() {
        std::cout << "도형 이름 : " << GetName() << ",\t 도형 크기 : " << Area() << std::endl;
    }

    /*함수를 가상 함수로 선언한다*/
    virtual double Area() { return 0; }

    std::string GetName() {
        return name;
    }

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape) {
        std::cout << shape.name << "(" << &shape << ")";
        return os;
    }
};

/*Shape 클래스를 상속받는 직사각형 클래스를 만든다.*/
class Rectangle : public Shape {
public:
    explicit Rectangle(const std::string &n, double w = 0, double h = 0) : Shape(n), width(w), height(h) {
        std::cout << "Rectangle 클래스 생성자 호출 : " << n << ", " << width << ", " << height << std::endl;
    }

    // 아래 함수는 상위 클래스 내 Area() 함수를 구현하였다.
    double Area() override {
//        return Shape::Area();
        return width * height;
    }

protected:
    double width{};
    double height{};
};

/* Shape 클래스를 상속받는 원 클래스를 만든다.*/
class Circle : public Shape {
protected:
    double radius;
    const double PI = 3.14159;
public:
    explicit Circle(double r = 0) : Shape("원"), radius(r) {
        std::cout << "Circle 클래스 생성자 호출 : " << radius << std::endl;
    }
};

/*
 * 연산자 오버로딩은 다음장에서 배운다.
 * */
bool operator<(Shape &a, Shape b) {
    std::cout << "여기서 Shape를 연산자 오버로딩을 했습니다 " << a << ", " << b << std::endl;
    return a.Area() < b.Area();
}

bool operator>(Shape &a, Shape &b) {
    return a.Area() > b.Area();
}

int main(int argc, char *argv[]) {

    int tmp01 = 10;
    int tmp02 = 20;
    int &tmp03 = tmp01;
    int &tmp04 = tmp02;

    int *a = &tmp01;
    int *b = &tmp02;

    std::cout << a << ", " << b << std::endl;
    std::cout << *a << ", " << *b << std::endl;

//    std::cout << tmp01 << ", " << tmp02 << std::endl;
    std::cout << "1. 최소값 : " << min<int>(*a, *b) << std::endl;
    std::cout << "2. 최소값 : " << min<int &>(tmp03, tmp04) << std::endl;
    std::cout << "3. 최소값 : " << min(a, b) << std::endl;

    Rectangle shape01 = Rectangle("직사각형", 10, 5);
    Circle shape02 = Circle(10);
    std::cout << "4. 최소값 : ";
    Shape &s1 = min<Shape &>(shape01, shape02);

    std::cout << "5. 최소값 : ";
    Shape &s2 = min<Shape>(shape01, shape02);
    s2.GetArea();
}