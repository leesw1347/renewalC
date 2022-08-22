//
// Created by lsw94 on 22-08-22.
//

#include <iostream>
#include <string>

/*클래스 템플릿을 정의한다*/
template<class T>
struct Base {
    typedef T type;

    virtual void Display() = 0;

};

/* 템플릿 클래스를 상속받는 Optimized 클래스 템플릿을 아래와 같이 선언한다. */
template<class T>
class Optimized : public Base<T> {
private:
    typename Base<T>::type data; // Base 클래스에서 가지고 있는 데이터 타입의 유형을 의미한다 ex) Base<T>::type (std::string)
public:
    typename Base<T>::type GetData() {
        return data;
    }

    explicit Optimized(typename Base<T>::type data) : data(data) {}

    void Display() override final {
        std::cout << "Optimized : " << data << std::endl;
    }

};

/*Derived 클래스는 아래와 같이 위의 클래스 템플릿을 상속받는다.
 * Derived 클래스는 이미 클래스 템플릿이 아닌 일반 클래스이다.*/
class Derived : public Base<int> {
private:
    // 별도 템플릿 인수를 지정할 필요가 없다.
    typename Base::type data; // "typename Base<int>::type data"와 동일하다
public:
    Derived(typename Base::type data) : data(data) {}

    typename Base::type GetData() { return data; }

    void Display() override {
        std::cout << "Derived : " << data << std::endl;
    }
};

/*타입 템플릿 매개변수가 제공하는 클래스를 상속받는 것 만들 수 있다.
 * 대신 타입 템플릿 매개변수에는 반드시 클래스 유형이 들어와야 한다.*/
template<class T>
class Other : public T {
private:
    typename T::type data;
public:
    Other(typename T::type c) : data(c) {}

    typename T::type GetData() { return data; }

    virtual void Display() final {
        std::cout << "Other : " << data << std::endl;
    }
};

/* 템플릿 클래스의 또 다른 예는 아래와 같다.*/
template<class T>
class OBase {
protected:
    T data;
    typedef T type;
public:
    void set(const T &val) {
        data = val;
    }

    T get() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return data;
    }
};

template<class T, class U>
class ODerived : public T {
private:
    U derived;
    typename T::type dtype;
public:
    ODerived(U &val) : derived(val) {
    }

    U get() {
        std::cout << __PRETTY_FUNCTION__;
        return derived;

    }

};

int main(int argc, char *argv[]) {

    Optimized<int> e(100);
    std::cout << "Optimized 객체 : " << e.GetData() << std::endl;
    e.Display();

    Derived d(1200);
    std::cout << "Derived 객체 : " << d.GetData() << std::endl;
    d.Display();

    Other<Base<int>> o(1500);
    std::cout << "Other 객체 : " << o.GetData() << std::endl;
    o.Display();

    std::string str("안녕하세요!");
    ODerived<OBase<int>, std::string> showtime(str);
    std::cout << showtime.get() << " " << showtime.OBase<int>::get() << std::endl;
}