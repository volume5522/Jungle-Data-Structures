//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000
//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList

typedef struct _stack
{
	LinkedList ll;
}Stack;  // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createStackFromLinkedList(LinkedList *ll , Stack *stack);
void removeEvenValues(Stack *s);

void push(Stack *s , int item);
int pop(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Stack s;

	c = 1;
	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the stack from the linked list:\n");
	printf("3: Remove even numbers from the stack:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createStackFromLinkedList(&ll, &s); // You need to code this function
			printf("The resulting stack is: ");
			printList(&(s.ll));
			break;
		case 3:
			removeEvenValues(&s); // You need to code this function
			printf("The resulting stack after removing even integers is: ");
			printList(&(s.ll));
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromStack(&s);
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
문제 : 연결 리스트를 스택에 복사하되, 리스트의 "첫 번째 노드부터 차례대로" 스택에 push해야 함.
예시 : (10, 20, 30) → push(10), push(20), push(30) -> Stack (30, 20, 10) <- Top

- Stack의 구조는 LinkedList이며, 삽입은 항상 맨 앞에서 일어남 (push는 index 0 삽입).
- 따라서 리스트의 앞에서부터 순차적으로 push만 하면 자동으로 Stack에는 역순으로 저장됨.

1. 예외 처리 : ll이 NULL이거나 size가 0이면 아무것도 하지 않음.
2. 스택을 먼저 비움 (초기화) → removeAllItemsFromStack()
3. 리스트의 head부터 끝까지 순차적으로 순회하면서 push 수행
-> Stack 내부 구조는 자연스럽게 역순이 되어 문제 조건 만족
----------------------------------------------------------------------------------
*/
void createStackFromLinkedList(LinkedList *ll, Stack *s)
{
	if (ll == NULL || ll->head == NULL)
		return;

	// 스택 초기화
	removeAllItemsFromStack(s);

	// 리스트 앞에서부터 순회하면서 스택에 push
	ListNode *temp = ll->head;
	while (temp != NULL) {
		push(s, temp->item); // Stack은 항상 head에 삽입되므로 자동으로 역순됨
		temp = temp->next;
	}
}


/*
----------------------------------------------------------------------------------
문제 : 스택에서 짝수 값을 제거하라
예시 : Stack (7, 6, 4, 3, 2) -> (7, 3) <- Top

- 스택은 LIFO이므로 Top부터 pop해서 임시 스택에 홀수만 저장
- 이후 임시 스택에서 다시 pop하면서 원래 스택에 push
-> 최종적으로 짝수가 제거된 상태로 순서 유지

1. 예외 처리 : 스택이 비어 있으면 아무것도 하지 않음
2. 임시 스택(temp)을 사용해서 홀수만 보관
3. 다시 temp에서 원래 스택으로 이동
----------------------------------------------------------------------------------
*/
void removeEvenValues(Stack *s)
{
	if (s == NULL || isEmptyStack(s))
		return;

	Stack temp;
	temp.ll.head = NULL;
	temp.ll.size = 0;

	// 스택에서 pop하면서 짝수는 버리고 홀수만 임시 스택에 push
	while (!isEmptyStack(s)) {
		int item = pop(s);
		if (item % 2 != 0)
			push(&temp, item);
	}

	// 다시 temp 스택에서 원래 스택으로 복원
	while (!isEmptyStack(&temp)) {
		int item = pop(&temp);
		push(s, item);
	}
}
//////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////


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
		if (ll->head == NULL)
		{
			exit(0);
		}
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
		if (pre->next == NULL)
		{
			exit(0);
		}
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
