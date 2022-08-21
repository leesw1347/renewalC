//
// Created by lsw94 on 22-08-21.
//

/*타입 속성 구조체 템플릿을 사용해서, 다른 예를 만들어본다*/

/*pod 클래스를 만든다*/
struct POD {
private:
public:
    int m;
};

/*일반 클래스를 만든다*/
class MyClass {
public:
    MyClass(int i, int j){
        x = i;
        y = j;

    }
private:
    int x;
    int y;

};

int main(int argc, char *argv[]) {


}