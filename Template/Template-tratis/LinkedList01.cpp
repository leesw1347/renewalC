//
// Created by lsw94 on 22-08-22.
//

#include <iostream>
#include <exception>

template<typename T>
class LinkedList {
private:
    struct Node {
    private:
    public:
        T data;
        Node *prev;
        Node *next;

        // 아래는 Node 내부 클래스의 인스턴스를 생성하는 생성자입니다.
        Node(T t, Node *p, Node *n) : data(t), prev(p), next(n) {}

    };

    /*LinkedList의 멤버 변수는 아래와 같습니다.*/
    Node *head; /*리스트 내 시작 노드의 위치를 가리킨다.*/
    Node *tail; /*리스트 내 마지막 노드의 위치를 가리킨다.*/

public:
    /*링크드 리스트의 디폴트 생성자는 멤버 변수를 모두 NULL로 만든다.*/
    LinkedList() : head(nullptr), tail(nullptr) {


    }

    /*아래 생성자는 배열 내 데이터를 링크드 리스트의 초기화 값으로 사용한다.*/
    template<int N>
    LinkedList(T (&arr)[N]) : LinkedList() {
        for (int i(0); i < N; i++) {
            push_back(arr[i]); /*리스트의 끝에 하나씩 배열의 데이터를 입력한다.*/
        }
    }

    /*새로운 Node 객체를 만들 때 호출되는 push_back() 함수와 push_front() 함수는 new 연산자를 사용한다.
     * LinkedList 객체 삭제 시 delete를 사용하여 생성한 모든 Node 객체를 삭제시켜 주어야 한다.*/
    virtual ~LinkedList() {
        // head pointer가 nullptr이라면 더이상 데이터가 존재하지 않음을 나타낸다.
        while (head) {
            Node *temp = head; /* head부터 시작해서 하나씩 Node 객체를 읽고 삭제시킨다.*/
            head = temp->next; /*다음 위치의 Node 객체를 head에 넣는다.*/
            delete temp;
        }
    }

    /*empty() 함수는 리스트가 비어있는지 확인하는것
     * nullptr 역시 nullptr이므로 0으로 표기된다. 따라서 !nullptr은 참이된다.*/
    template<typename EMPTY = bool>
    EMPTY empty() const {
        return (!head || !tail);
    }

    /*push_back() 함수는 인수로 받은 데이터를 새롭게 생성한 노드에 넣고
     * 그 위치를 tail에 넣는 기능을 제공한다.*/
    void push_back(T);

    /*push_front() 함수는 선언문으로 데이터를
     * 생성한 노드에 넣고 그 위치를 head에 넣는다.*/
    void push_front(T);

    /*
     * pop_back() 함수는 tail이 가리키는 노드로부터 하나의 데이터를 꺼낸다.
     * 그리고 꺼내어 사용한 노드를 삭제 시킨다.
     * */
    T pop_back();

    T pop_front(); /* head부터 정방향으로 하나 꺼낸다.*/

    /*후입 선출 방법으로 마지막 입력된 데이터를부터 순차적으로 출력한다.*/
    void display_back();

    /*선입선출 방법으로 처음 입력된 데이터를 앞에서부터 순차적으로 출력한다.*/
    void display_front();
};

/*push_back() 함수는 데이터를 리스트의 뒤에 넣는다*/
template<typename T>
void LinkedList<T>::push_back(T data) {
    tail = new Node(data, tail, nullptr);

    /*이전 Node 객체의 next 변수는 현재 nullptr이므로 새롭게 생성한 tail 객체를
     * 가리키도록 next 변수를 다음과 같이 수정한다.*/
    if (tail->prev) {
        tail->prev->next = tail;
    }

    /*data가 처음 입력되는 데이터라면 head는 nullptr이다.*/
    if (head == nullptr) {
        head = tail;
    }

}

/*push_front() 함수는 데이터를 리스트의 앞에 넣는다*/
template<typename T>
void LinkedList<T>::push_front(T data) {
    /*next 변수는 head 변수가 가리키는 노드의 주소를 물려받는다.*/
    head = new Node(data, nullptr, head);

    /*push_back 함수의 리스트의 앞에서 작업을 수행한다*/
    if (head->next) {
        head->next->prev = head;
    }

    /* 처음 입력되는 데이터라면, tail 역시 같은 Node 객체를 가리키도록 만든다.*/
    if (tail == nullptr) {
        tail = head;
    }
}

template<typename T>
T LinkedList<T>::pop_back() {
//    return nullptr;
    T temp = tail->data;

    return static_cast<T>(temp);
}

int main(int argc, char *argv[]) {

    int arr[] = {4, 6, 8, 32, 19};

    /*배열의 데이터를 사용하여 list라는 LinkedList 객체를 생성한다.*/
    LinkedList<int> list(arr);

    list.push_back(11);
    list.push_front(100);
    list.display_front();

    /* 후입선출 방법으로 데이터를 읽고 리스트에서 객체를 삭제시킨다.*/
    while (!list.empty()) {
        std::cout << list.pop_back() << " ";
    }
    std::cout << std::endl;

}