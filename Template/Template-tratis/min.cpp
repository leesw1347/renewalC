//
// Created by lsw94 on 22-08-21.
//
#include <iostream>
#include <typeinfo>

/*타입 특성 클래스 템플릿의 필요성에 대해서 알아본다
 * T의 경우 int *처럼 포인터를 사용한다면, 함수 템플릿은 변환 후 실행하는 과정에서
 * 예상치 못한 에러가 발생한다.
 * */

/* T 타입의 함수 템플릿*/
template<class T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

/*T 타입 포인터의 함수
 * long *, double* 타입등도 사용할 수 있어서, 전체 템플릿 특수화보다
 * 좀 더 일반화할 수 있는 장점이 있다.*/
template<class T>
T min(T *a, T *b) {
    return (*a < *b) ? (*a) : (*b);
}

// 전체 템플릿  특수화
template<>
int *min<int *>(int *a, int *b) {
    return (*a < *b) ? a : b;
}

int main(int argc, char *argv[]) {

    int tmp01 = 10;
    int tmp02 = 20;

    int *a = &tmp01, *b = &tmp02;
    std::cout << a << ", " << b << std::endl;
    // 최소값
    std::cout << min<int>(tmp01, tmp02) << std::endl;
    std::cout << min<int>(*a, *b) << std::endl;

    /*아래의 경우 메모리 주소의 min 값을 찾는것이기 떄문에 정상적인 값을 비교하기 힘들다.
     * 템플릿 특수화를 통해서 작업도 가능하다*/
    std::cout << min<int *>(a, b) << std::endl;
}