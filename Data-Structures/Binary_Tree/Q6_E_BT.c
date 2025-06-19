//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;


///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void printSmallerValues(BTNode *node, int m);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stack, BTNode *node);
BTNode* pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;
    int c, value;
    BTNode *root;

    c = 1;
    root = NULL;


    printf("1: Create a binary tree.\n");
    printf("2: Print smaller values.\n");
    printf("0: Quit;\n");

    while(c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if( scanf("%d",&c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                printf("Enter an integer value to print smaller values: ");
                scanf("%d",&value);
                printf("The values smaller than %d are: ", value);
                printSmallerValues(root,value);
                printf("\n");
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {printf("\n");
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/*
----------------------------------------------------------------------------------
문제 : 이진 트리에서 주어진 값 m보다 작은 모든 값을 출력하라.
출력 순서는 중위 순회(in-order traversal)를 사용해야 한다.

예시 : 트리가 다음과 같고 m = 55일 때
            50
          
         30    60
              
      25  40      80

출력 결과는 : 25 30 40 50

- 처음에 이 문제를 보고 생각한 점들
    노드가 NULL이면?                  -> 아무 것도 하지 말고 return
    출력 순서를 어떻게 유지할까?       -> in-order traversal 사용
    출력 조건은 어떻게 확인할까?       -> node->item < m 이면 출력

1. 예외 상황을 먼저 고려
    노드가 NULL이면 출력할 것이 없으므로 바로 return;

2. 중위 순회(in-order traversal)
    - 왼쪽 서브트리 -> 현재 노드 -> 오른쪽 서브트리 순서로 순회한다.
    - 현재 노드의 값이 m보다 작을 때만 출력한다.

3. 출력 방식
    printf("%d ", node->item); 를 이용해 조건에 맞는 노드만 출력

4. 함수는 void형이며 반환값 없음
----------------------------------------------------------------------------------
*/
void printSmallerValues(BTNode *node, int m) //Testcase에 똑같이 하고싶으면 전위순회로 탐색하기.
{
    // 예외처리 : 노드가 NULL이면 아무 것도 하지 않고 종료
    if (node == NULL)
        return;

    // 왼쪽 서브트리 탐색
    printSmallerValues(node->left, m);

    // 현재 노드의 값이 m보다 작으면 출력
    if (node->item < m)
        printf("%d ", node->item);

    // 오른쪽 서브트리 탐색
    printSmallerValues(node->right, m);
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stack,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stack,temp->right);
        if(temp->left != NULL)
            push(&stack,temp->left);
    }
    return root;
}

void push( Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stack->top == NULL)
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

BTNode* pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if(top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if(*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}

