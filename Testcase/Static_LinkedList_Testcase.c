#include <stdio.h> //화면 출력, 키보드 입력, 파일 입출력 등 모든 I/O 작업에 필수

struct node // 구조체의 이름은 'struct node' 이녀석은 두개의 맴버를 가짐 int data, struct node *next
{
    int data; // 노드가 실제로 저장하는 값 (정수)
    struct node *next; // 다음 노드를 나타낼 수 있게하는 포인터
};
typedef struct node Node; // 'struct node'라는 이름이 너무 길어서 이름을 Node로 바꿈 'struct node' -> 'Node'

void printList(Node *head) // 출력 함수 : 인자를 왜 포인터로 받아? -> 원본 리스트(노드들)에 접근하기 위해 포인터로 받음.
// 값 복사가 아니라 주소 전달이라 효율적
//만약 void printList(Node head); 로 선언하면? head만 복사됨 → head.next는 못 따라감

{
    Node *current = head; // current는 현재 노드를 가리키는 포인터. 
    //처음에는 리스트의 첫 노드를 가리키게 됨. 이렇게 하면 원래의 head는 변경되지 않고, 순회는 current를 통해 안전하게 수행.

    while (current != NULL) // 반복 : current의 값이 NULL이 아닐 때까지.
    {
        printf("%d -> ", current->data); // 출력을 함 현재의 current의 data값을 출력.
        current = current->next; //current를 다음 노드로 이동. 즉, 연결 리스트를 한 칸씩 순회.
    }
    printf("NULL\n"); // 끝나면 NULL 선언
}

int main()
{
    Node a, b, c, d; // Node형 변수 a, b, c, d를 선언함. 이들은 지역변수이므로 일반적으로 스택(stack)에 저장됨.
                     // main() 함수 내부에서 선언된 변수는 자동 변수(auto variable)이며, 이는 스택 메모리 영역에 저장
    a.data = 1; // a의 맴버 data를 1로 설정
    a.next = &b; // a의 맴버 next 포인터를 b의 주소로 설정 

    b.data = 2;
    b.next = &c;

    c.data = 3;
    c.next = &d;

    d.data = 4;
    d.next = NULL;

    printList(&a); // 왜 &a 인가? a는 구조체 자체이고, &a가 a의 주소이기 때문. 

    return 0;
}
