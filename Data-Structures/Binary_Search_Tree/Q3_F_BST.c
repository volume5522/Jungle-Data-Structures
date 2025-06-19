//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void preOrderIterative(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the pre-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting pre-order traversal of the binary search tree is: ");
			preOrderIterative(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
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
문제 : 전위 순회 결과를 출력하는 함수 preOrderIterative(BSTNode *root)를 반복문 방식으로 작성 (단, pop()이랑 push()만 사용)
출력 : 20, 15, 10, 18, 50, 25, 80


생각해야할 것
- root == NULL이면 아무 것도 출력하지 않음
- 스택 초기화는 반드시 해야 함 (기존에 스택에 남은 값이 있으면 안 됨)
- push/pop 외 다른 스택 접근 방식은 사용 금지

접근 방법:
1. 스택 초기화
2. 루트 노드가 NULL이면 종료
3. 루트를 스택에 push
4. 스택이 비어있지 않을 때까지 다음 반복 수행:
	스택에서 pop한 노드를 출력
	오른쪽 자식이 있으면 먼저 push 
	왼쪽 자식이 있으면 나중에 push

왜 오른쪽을 먼저 push?
스택은 LIFO 구조이므로 먼저 push한 오른쪽이 나중에 pop
따라서 전위 순회 순서인 Root → Left → Right를 유지하기 위해서 Right → Left 순으로 push

알고리즘 흐름
1. push(20)
2. pop → 20 출력 → push(50) → push(15)
3. pop → 15 출력 → push(18) → push(10)
4. pop → 10 출력
5. pop → 18 출력
6. pop → 50 출력 → push(80) → push(25)
7. pop → 25 출력
8. pop → 80 출력


*/
void preOrderIterative(BSTNode *root) {
    // 예외 처리: 트리가 비어있으면 아무 작업도 수행하지 않음
    if (root == NULL) return;

    // 스택 초기화 (전위 순회를 위한 스택 사용)
    Stack s;
    s.top = NULL;

    // 루트 노드를 스택에 push (전위 순회 시작점)
    push(&s, root);

    // 스택이 비어있을 때까지 반복
    while (!isEmpty(&s)) {
        // 현재 스택의 top 노드를 pop하여 방문
        BSTNode *node = pop(&s);

        // 노드의 값 출력 (전위 순회: Root → Left → Right)
        printf("%d ", node->item);

        // 스택은 후입선출(LIFO)이므로, 오른쪽 자식을 먼저 push
        // 이렇게 해야 다음 루프에서 왼쪽 자식이 먼저 pop되어 순서 유지됨
        if (node->right) push(&s, node->right);
        if (node->left)  push(&s, node->left);
    }
}

/*
재귀함수로 짠것.											
| 항목        | 재귀 함수 방식                                           | 반복문 + 명시적 스택 방식                          |
| ----------- | ---------------------------------------------           | --------------------------------                  |
| 스택 사용   | 컴파일러의 함수 호출 스택(Call Stack) 자동 사용            | 사용자가 직접 만든 Stack 구조 사용                 |
| 명시성      | 숨겨진 스택 사용 (코드에 없음)                            | 스택 조작이 코드에 명시됨 (`push`, `pop`)          |
| 구현 난이도 | 간결하고 직관적임                                         | 더 복잡하지만 컨트롤 명확*                         |
| 메모리 제어 | 호출 깊이만큼 Call Stack 소비 (Stack Overflow 위험)       | 스택 오버플로우 방지 가능, 직접 크기 조절 가능      |
| 디버깅      | 함수 호출이 깊어질수록 디버깅 어려움                       | 명시적 스택 조작이라 디버깅 용이함                  |
| 반복 제어   | 종료 조건이 함수 리턴 조건에 내포됨                        | `while (!isEmpty())` 등 명시적 제어 필요            |
| 사용 환경   | 순회 깊이가 적은 트리에 적합                               | 깊이가 깊거나 호출 제약 있는 환경에 유리            |



void preOrderRecursive(BSTNode *root) {
    if (root == NULL) return;
    printf("%d ", root->item);
    preOrderRecursive(root->left);
    preOrderRecursive(root->right);
}
*/


///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
