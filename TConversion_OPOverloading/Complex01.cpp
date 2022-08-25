//
// Created by lsw94 on 22-08-23.
//

#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <memory>
#include <cmath>
#include <iomanip>

struct Complex;

struct Complex {
private:
    double real;
    double imginary;
public:
    static bool is_line;

    /*아래는 일반 생성자*/
    constexpr Complex(double real);

    constexpr Complex(double real, double imginary);

    /*1. 단항 연산자 오버로딩*/
    Complex &operator+();

    Complex operator-() const;

    /*전위 연산자 오버로딩이 반환하는 객체는 *this,
     * 후위 단항 연산자는 함수 내부에서 임시 객체를 생성하여 반환한다.*/
    Complex &operator++(); // ++ 전위 연산자 오버로딩
    Complex operator++(int); // ++ 후위 연산자 오버로딩
    Complex &operator--(); // -- 전위 연산자 오버로딩
    Complex operator--(int); // -- 후위 연산자 오버로딩

    /*이항 산술 연산자의 작업결과는 RValue이다.
     * 연산작업 결과는 임시 객체를 만들어 반환한다.
     * 이항 연산자 오버로딩은 아래와 같이 inline(또는 상수 표현식)으로 선언이 가능하며,
     * 전역 연산자 오버로딩으로 만들어도 좋다.*/
//    inline Complex operator+(const Complex &c) const;
    Complex operator+(const Complex &c) const;

    Complex operator-(const Complex &c) const;

    Complex operator*(const Complex &c) const;

    Complex operator/(const Complex &c) const;

    /*대입 연산자의 작업 결과는, 자체 객체의 변화를 발생 시키므로, 다음과 같이 참조를 사용한다*/
    Complex &operator=(const Complex &c);

    Complex &operator+=(const Complex &c);

    Complex &operator-=(const Complex &c);

    /*이항 비교 연산자 오버로딩 (전역 연산자 오버로딩으로 만들어도 좋다)*/
    bool operator==(const Complex &c) const;

    bool operator!=(const Complex &c) const;

    /*타입 변환 연산자 오버로딩(Complex->double 또는 Complex->char)은 자기 자신의
     * 객체를 정수 또는 실수로 만들어준다.
     * ex)
     *      operator 변환-타입(),
         *      또는
         *  explicit operator 변환-타입()
     *  */
    explicit operator double() const {
        return this->real;
    }

    explicit operator char *() const;

    /* std::cout << Complex(x,y) 처럼 복소수를 출력하기 위해 오버로딩 해주어야 한다'*/
    friend std::ostream &operator<<(std::ostream &os, const Complex &c);

    /* 변수의 데이터를 반환*/
    double Real() const;

    /* 변수의 데이터를 반환222*/
    double Imginary() const;

    /* 멤버 선택 연산자 오버로딩 */

    // 배열 인덱스 연산자
    // 간접 참조 연산자
    Complex &operator*();

    /* 주소 연산자*/
    Complex *operator&();

    /*객체 멤버 선택 연산자*/

};

bool Complex::is_line = true;


constexpr Complex::Complex(double real) : real(real), imginary(0.0) {
    std::cout << "Complex(double real) 클래스 생성자 호출!" << std::endl;
}

constexpr Complex::Complex(double real, double imginary) : real(real), imginary(imginary) {
    std::cout << "Complex(double real, double imginary) 클래스 생성자 호출" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Complex &c) {
    os << "(" << c.real << " + " << c.imginary << "i" << ") ";
    return os;
}


Complex Complex::operator+(const Complex &c) const {
    /*
     * 연산 결과는 다음과 같이 임시 저장소를 만들어 반환한다.
     * */
    return {this->real + c.real, this->imginary + c.imginary};
}

/*
 * 위의 + 이항 연산자 오버로딩을 수정하여 아래와 같이 전역 연산자 오버로딩을 만들 수 있다.
 * */
inline Complex operator+(const Complex &a, const Complex &b) {
    return {a.Real() + b.Real(), a.Imginary() + b.Imginary()};
}

/*
 * 단항 연산자는 변수의 앞 또는 뒤에 붙여서 연산 작업을 수행하는 연산자이다.
 * 객체 내 변수값에 어떠한 변화도 발생하지 않는다. 아래와 같이 생성된 객체를 그대로 반환한다.
 * +단항 연산자는 오버로딩하지 않는다면,
 * 산술 연산을 사용할 때 에러가 발생하기 때문에 전체적인 연관성을 고려하여 만들어 주어야 한다.
 * */

Complex &Complex::operator+() {
    return (*this);
}

/*
 * -1 * c 에 곱한거처럼 실수와 허수 모두 음수(원래 음수였다면 양수)로 만든
 * 객체를 생성하여 반환한다
 * '-' 단항 연산자의 작업 결과는 rvalue(임시 객체)를 만들어 반환한다. 그리고 RVO 복사/이동 생략의 원칙에 따라 객체가 된다
 * */
Complex Complex::operator-() const {
    Complex complex(-this->real, -this->imginary);
    std::cout << "operator-() 호출 : (" << &complex << ") " << std::endl;
    return std::forward<Complex>(complex); /* 지역변수를 반환한다. */
}

Complex &Complex::operator++() {
    ++this->real;
    ++this->imginary;
    return (*this);
}

Complex Complex::operator++(int) {
    // 반환할 임시 객체를 생성한다.
    Complex complex(this->real, this->imginary); // real과 img를 증가 시키기전 객체를 생성해서 리턴해줘야 한다.
    ++this->real;
    ++this->imginary;
    return std::forward<Complex>(complex);
}

/*
 * -- 전위 감소 단항 연산자는 다음과 같이 만든다.
 * */
Complex &Complex::operator--() {
    --this->real;
    --this->imginary;
    return (*this); // this 포인터를 참조로 반환한다.
}

/*
 * -- 후위 감소 단항 연산자를 다음과 같이 정의한다
 * */
Complex Complex::operator--(int) {
    Complex complex(this->real, this->imginary); // 임시 Complex 객체를 생성한다.
    --this->real;
    --this->imginary;
    return complex;
}

Complex Complex::operator-(const Complex &c) const {
    /* - 이항 연잔자 오버로딩은 다음과 같이 연산과 작업이 이루어진다.*/
    return {this->real - c.real, this->imginary - c.imginary};
}

Complex Complex::operator*(const Complex &c) const {
    /*
     * (a + bi)(c + di) = (ac - bd) + (bc - ad)i
     * */
    return {
            (this->real * c.real) - (this->imginary * c.imginary),
            (this->real * c.imginary) + (this->imginary * c.real)
    };
}

Complex Complex::operator/(const Complex &c) const {

}

/*
 * 대입 연산자 오버로딩
 * */
Complex &Complex::operator=(const Complex &c) {
    /*
     * 복사 대입 연산자와 같다.
     * */
    std::cout << this << ", " << &c << std::endl;
    if (this == &c) { // 자기 자신을 대입한다면 그대로 반환된다.
        std::cout << "자기 자신을 대입하는건 불가능하기 때문에 *this를 리턴합니다" << std::endl;
        return (*this);
    }
    this->real = c.real;
    this->imginary = c.imginary;
    return *this;
}

Complex &Complex::operator+=(const Complex &c) {
    // += 연산하려는 객체가 동일한 객체면 더하지 않는다
    if (this == &c) {
        std::cerr << this << "랑 " << &c << "는 서로 동일하기 때문에 += 연산을 수행하지 않겠습니다" << std::endl;
        return (*this);
    }
    this->real += c.real;
    this->imginary += c.imginary;
    return (*this);
}

Complex &Complex::operator-=(const Complex &c) {
    this->real -= c.real;
    this->imginary -= c.imginary;
    return *this;
}

bool Complex::operator==(const Complex &c) const {
    if (this->real == c.real && this->imginary == c.imginary) {
        return true;
    }
    return false;
}

bool Complex::operator!=(const Complex &c) const {
    /*아래 코드로도 대체가 가능하다.*/
    /*if (this->real == c.real && this->imginary == c.imginary) {
        return false;
    }
    return true;*/
    return !operator!=(c);

}

double Complex::Imginary() const {
    return imginary;
}

double Complex::Real() const {
    return real;
}

Complex::operator char *() const {
    /*
     * 복소수를 문자열로 변환한다.
     * */
    char *buffer = new char[20];
    snprintf(buffer, 20, "(%.2f + %.2fl)", real, imginary);
    return buffer;
}

Complex &Complex::operator*() {
    return *this;
}

Complex *Complex::operator&() {
    return this;
}

/*
 * ( == ) 등가 비교 연산자 오버로딩은 다음과 같다.
 * */

int main(int argc, char *argv[]) {

    /*std::cout << std::setprecision(2) << std::fixed;
    Complex d1 = 10; // 암시적 변환으로 Complex 객체를 생성한다
    std::cout << "d1은 " << d1 << std::endl;

    *//* Complex 구조체 간의 덧셈 작업을 위해 이항 덧셈 연산자 오버로딩을 호출한다. *//*
    Complex d2 = d1 + static_cast<Complex>(10.1);
    std::cout << d2 << " = " << d1 << " + " << 10.1 << std::endl;
    Complex d3 = 20.1 + d1;

//    std::cout << (-d2) << std::endl;
//    std::cout << &ptr << std::endl;

    d3++;
    std::cout << d3 << std::endl;*/
    Complex num1(2, 3); // Complex 객체를 생성한다.
    auto *num2 = new Complex(3, 4);

    /*소수점 두자리까지 화면에 출력한다.*/

    /*
    std::cout << "첫 번째 복소수" << std::endl;
    std::cout << ", 두 번째 복소수" << std::endl;

    // 단항 연산 작업을 수행한다.
    std::cout << "\n단항 연산자 오버로딩----" << std::endl;
    std::cout << "-" << num1 << "는 ";
    std::cout << -num1 << "이다." << std::endl;

    Complex num3(30, 20);
    std::cout << "3번째 복소수 " << num3 << std::endl;
    std::cout << "3번째 ++복소수 " << ++num3 << std::endl;
    std::cout << "3번째 복소수++ " << num3++ << std::endl;
    std::cout << "3번째 --복소수 " << --num3 << std::endl;
    std::cout << "3번째 복소수-- " << num3-- << std::endl;

    delete num2;*/

    /* 대입 연산자는 산술 연산과 다르게, 오른쪽에서 왼쪽으로 연산이 진행된다. */
    /*Complex a(0.12, 1.03);
    Complex b(1.972, 0.23);
    a = b;
    a = b;
    a += b;*/

    std::cout << "\n이항 연산자 오버로딩----" << std::endl;
    Complex sum = num1 + *num2;
    std::cout << sum << " = " << num1 << +" + " << *num2 << std::endl;
    sum = num1 - *num2;
    std::cout << sum << " = " << num1 << +" - " << *num2 << std::endl;
//    std::cout << std::boolalpha;
//    std::cout << "is_line " << Complex::is_line << std::endl;

    Complex num3(30, 20);
    sum = num3 * num1; // operator* 연산자 오버로딩 호출;
//    std::cout << (typeid(sum).name()) << std::endl;
    std::cout << sum << " = " << num3 << " * " << num1 << std::endl;

    /*sum = num3 / num1;
    std::cout << sum << " / " << num3 << " / " << num1 << std::endl;*/

    sum += num3; // operator+= 연산자 오버로딩 활용
    std::cout << sum << "(" << sum.Real() << "," << sum.Imginary() << ")" << " += " << num3 << std::endl;
    auto ptr = static_cast<char *>(sum);
    std::cout << "ptr... " << ptr << std::endl;
    std::cout << "*sum " << *sum << std::endl;

    return 0;
}