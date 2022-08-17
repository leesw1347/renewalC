//
// Created by lsw94 on 22-08-17.
//

#include <string>
#include <iostream>
#include <string>

// 타입 템플릿 매개변수를 사용하여 템플릿 클래스를 선언한다
template<typename T>
struct my_map {
private:
    T data;
public:
    explicit my_map(T t) : data(t) {
        std::cout << "my_map struct 생성자 호출 data : " << data << std::endl;
        std::cout << "my_map 내 data 타입의 형태 : " << typeid(data).name() << std::endl;
    }

    T getData() { return data; }
};

/* 타입 템플릿 매개변수와, 템플릿 매개변수릉 다음과 같이 선언한다*/
/**
 *
 * @tparam K : 타입 템플릿 매개변수
 * @tparam V : 타입 템플릿 매개변수
 * @tparam C  : 템플릿 매개변수
 */
template<typename K, typename V, template<typename T> typename C = my_map>
class Map {
private:

    /*앞에서 선언한 C 템플릿 템플릿 매개변수를 사용하여 아래와 같이 선언한다
     * K와 V 매개변수는 타입 템플릿 매개변수이다.*/
    C<K> key;
    C<V> value;

public:
    Map() = default;

    /**
     * 템플릿 인수를 사용하여 멤버 변수를 초기화 한다
     * @param k
     * @param v
     */
    Map(K k, V v) : key(k), value(v) {
        std::cout << "템플릿 인수를 이용하여 멤버 변수 초기화" << std::endl;
    }

    K getKey() {
        return key.getData();
    }

    V getValue() {
        return value.getData();
    }

    void typeCheck() const {
        std::cout << "key typeid " << typeid(key).name() << std::endl;
        std::cout << "value typeid " << typeid(value).name() << std::endl;
    }

};

int main(int argc, char *(argv)[]) {
    std::cout << "hello" << std::endl;

    /**
     * 아래와 같이 사용하면 my_map<int>, my_map<std::string> 객체가 2개를 Map 클래스 내에서 생성할 수 있다.
     * 아래와 같이 getKey(), getValue() 함수를 사용할 경우 my_map 클래스 내 해당 함수가 없는 다른 템플릿은 Map 클래스를 활용할 수 없기 때문에
     * 템플릿 특수화 (template specialization)을 통해서 수정한다
     */
    Map<int, std::string, my_map> map(1000, "템플릿 템플릿 인수");
    std::cout << "Map(" << map.getKey() << "," << map.getValue().data() << ")\n";
}