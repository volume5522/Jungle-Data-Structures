#include <stdio.h>
#include <stdlib.h> //동적 메모리, 숫자 변환, 난수, 프로그램 종료 등에 관련된 다양한 표준 함수들을 사용하기 위한 선언

typedef struct node {
    int data;
    struct node* next;
} Node;

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {    
    // 지역 변수이기 때문에 main() 함수가 호출될 때 스택 프레임에 올라감. 포인터 변수 first, second, third, fourth 를 stack에 저장.
    // malloc을 통해 동적할당을 시행. 동적할당의 크기는 sizeof(Node)로 인해 node의 크기만큼 할당됨. 
    // malloc()은 원하는 바이트 수만큼의 메모리를 힙에 할당. sizeof(Node)는 Node 구조체가 차지하는 바이트 크기를 계산
    // 동적할당이란? -> 프로그램 실행 중(runtime)에, 필요한 만큼 메모리를 직접 요청해서(heap 영역에) 사용하는 것. (언제, 어디서 하는지가 중요. 크기는 중요하지 않음.)
    // 정적할당이란? -> 컴파일 타임에 크기가 정해지고, 스택에 저장

    Node *first = malloc(sizeof(Node)); 
    Node *second = malloc(sizeof(Node));
    Node *third = malloc(sizeof(Node));
    Node *fourth = malloc(sizeof(Node));

    if (!first || !second || !third || !fourth) { // 메모리 할당 실패 시 예외 처리
        printf("Memory allocation failed\n");
        return 1;
    }

    first->data = 1;  // 첫 번째 노드의 data 필드에 값 1 저장
    first->next = second; // 첫 번째 노드가 두 번째 노드를 가리키도록 연결

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = fourth;

    fourth->data = 4;
    fourth->next = NULL;

    printList(second); // 아까는 &를 썼는데 이번에는 왜 그냥 쓰냐? -> 
    //first같은 경우 위에서 포인터변수로 설정을 했기 때문에 그냥 쓰는게 옳다.(first -> Node *) 만약  &first가 되버리면, Node **가 되어버림.


    //malloc으로 할당한 메모리는 자동으로 해제되지 않음. 
    //free()로 직접 해제하지 않으면 -> 메모리 누수(leak) 발생. 메모리 누수가 많아지면 시스템 리소스 고갈 -> 프로그램 속도 저하/강제 종료
    free(first);
    free(second);
    free(third);
    free(fourth);

    return 0;   
}
