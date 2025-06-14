//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/*
----------------------------------------------------------------------------------
문제 : 연결리스트를 한 번만 순회하여, 가장 큰 값을 가진 노드를 맨 앞으로 이동시켜라.
예시 : (30, 20, 40, 70, 50) -> (70, 30, 20, 40 50)

- 처음에 이 문제를 보고 생각한 점들
	리스트가 비어 있거나 한 개밖에 없나?	→ 아무 것도 하지 말고 return
	가장 큰 값은 어떻게 찾을 수 있을까?	→ 한 번만 순회하면서 max 추적
	노드를 앞에 "이동"시킬 때 malloc 필요한가?	→ 기존 노드를 옮기므로 malloc X
	head를 바꾸려면 어떻게 해야 할까?	→ 이중 포인터(ListNode **) 사용







1. 예외 상황을 먼저 고려
	리스트가 비어있거나(*ptrHead == NULL) 노드가 하나밖에 없으면((*ptrHead)->next == NULL), 옮길 노드가 없기 때문에 아무것도 하지말고 return.

2. 변수 설계
	한 번의 순회로 가장 큰 노드를 찾아야 하기 때문에 포인터들이 필요함.
	maxNode : 최대값을 가진 노드를 가르킴.
	maxPrev : maxNode의 이전(직전) 노드
	cur : 순회 중인 현재 노드
	prev : cur의 이전(직전) 노드

3. 최대값 노드 찾기
	maxNode가 head보다 더 큰 노드가 있으면 갱신.
	maxPrev는 maxNode의 바로 앞을 기억 (나중에 노드를 리스트에서 끊어내기 위해 필요)

4. maxNode가 이미 맨 앞이면 return
	바꿀 필요 없으니까 그냥 return
ㄴ
5. maxNode를 리스트 앞(Head)으로 옮기기
	maxPrev->next = maxNode->next; → 기존 위치에서 maxNode 끊기
	maxNode->next = *ptrHead; → maxNode가 기존 head를 가리키게
	*ptrHead = maxNode; → maxNode를 head로 만들기

----------------------------------------------------------------------------------
*/

// moveMaxToFront 의 함수는 리스트의 Head 포인터의 주소를 인자로 받음.
// ListNode **ptrhead는 ListNode *ptrhead를 수정할 수 있도록 이중포인터로 전달.
int moveMaxToFront(ListNode **ptrHead)
{
	// 예외처리.
    if (ptrHead == NULL || *ptrHead == NULL || (*ptrHead)->next == NULL)
        return 0;

	// maxNode는 현재까지 찾은 최대값의 노드를 가르킴 -> 초기값은 head
	// maxPrev는 maxNode의 이전 노드를 추적하기 위한 포인터
	// 만약, 최대값이 맨 앞이면, maxPrev는 NULL을 가짐.
    ListNode *maxNode = *ptrHead;
    ListNode *maxPrev = NULL;

	// 연결 리스트를 순회하기 위한 포인터
	// prev : 현재 노드의 이전 노드
	// cur : 현재 검사중인 노트 (head의 다음부터 시작)
    ListNode *prev = *ptrHead;
    ListNode *cur = (*ptrHead)->next;

	// 리스트의 끝까지 반복
    while (cur != NULL) {
		// 현재 노드(cur)의 값이 지금까지의 최대값(maxNode)보다 크면,
		// maxNode를 업데이트하고,
		// maxPrev도 현재 이전 노드인 Prev로 업데이트
        if (cur->item > maxNode->item) {
            maxNode = cur;
            maxPrev = prev;
        }
		// 다음 노드로 이동할려고 하나씩 이동
        prev = cur;
        cur = cur->next;
    }

	// 최댓값 노드가 맨 앞이면, 이동할 필요가 없으니, 그냥 종료
    if (maxPrev == NULL)
        return 0;

	// 최대값 노드를 리스트에서 제거
	// maxPrev가 maxNode를 건너뛰고, maxNode의 다음 노드를 가리키게 함.
    maxPrev->next = maxNode->next;

	// maxNode의 다음 포인터를 기존 head로 연결
	// 즉, maxNode가 새로운 첫 번째 노드가 되기 위한 연결 작업
    maxNode->next = *ptrHead;
	// 리스트의 head 포인터를 maxNode로 갱신
    *ptrHead = maxNode;

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
