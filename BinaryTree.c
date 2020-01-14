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
    printf("���������������");
    InOrderTree(BitTree_1);
    putchar('\n');

    return 0;
}

/**
 * @brief ��������ǵݹ�
 * @note   
 * @param  *root: ���ڵ�
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
 * @brief  �ڶ��ཨ��������
 * @note   ���βΣ�����ӿں���
 * @retval ���ض�����
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