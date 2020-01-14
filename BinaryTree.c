#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1024
typedef char ELEM_TYPE;
typedef struct BinaryTreeNode
{
    ELEM_TYPE value;
    struct BinaryTreeNode *LeftChild;
    struct BinaryTreeNode *RightChild;
} BinaryTree;

void InOrderTree(BinaryTree *root);
BinaryTree *RecursiveCreateBinaryTrees();

int main(void)
{
    BinaryTree *BitTree_1;

    BitTree_1 = RecursiveCreateBinaryTrees();
    printf("中序遍历二叉树：");
    InOrderTree(BitTree_1);
    putchar('\n');

    return 0;
}

/**
 * @brief 中序遍历非递归
 * @note   
 * @param  *root: 根节点
 * @retval None
 */
void InOrderTree(BinaryTree *root)
{
    if (NULL == root)
    {
        return;
    }

    int StackTop = 0;
    BinaryTree *TreeStcak[MAXSIZE];

    while (NULL != root || 0 != StackTop)
    {
        while (NULL != root)
        {
            TreeStcak[StackTop++] = root;
            root = root->LeftChild;
        }

        if (0 != StackTop)
        {
            root = TreeStcak[--StackTop];
            printf("%c ", root->value);
            root = root->RightChild;
        }
    }
}

/**
 * @brief  第二类建立二叉树
 * @note   无形参，更像接口函数
 * @retval 返回二叉树
 */
BinaryTree *RecursiveCreateBinaryTrees()
{
    char value;
    scanf("%c", &value);

    BinaryTree *root = (BinaryTree *)malloc(sizeof(BinaryTree));

    if ('0' == value)
    {
        return NULL;
    }

    if (NULL == root)
    {
        printf("ERROR: Could not allocate memory\n");
        return root;
    }

    root->value = value;
    root->LeftChild = RecursiveCreateBinaryTrees();
    root->RightChild = RecursiveCreateBinaryTrees();

    return root;
}