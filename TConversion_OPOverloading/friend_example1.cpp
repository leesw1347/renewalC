//
// Created by lsw94 on 22-08-23.
//


/*
 * friend 키워드를 이용해서 클래스 내부의 모든 멤버의 접근이 허용된다
 * */

class Ours; /* 전방선언(Forward Declartions) */

class Friends {
    int Func2(Ours &b);

public:

    int Func1(Ours &b);
};

class Ours {
private:
    int _b;

    friend int Friends::Func1(Ours &b);

public:
};

/* Func1() 함수의 정의문 */
int Friends::Func1(Ours &b) {
    return b._b;
}

/* Func2() 함수는 Ours 클래스의 친구가 아니기 때문에 _b 멤버를 호출 시 에러가 발생한다*/
int Friends::Func2(Ours &b) {
    return b._b; // Func2 함수는 Ours 클래스 내에서 친구로 설정되어 있지 않기 때문에 _b 멤버 변수에 접근할 수 없다.
}

int main(int argc, char *argv[]) {


}