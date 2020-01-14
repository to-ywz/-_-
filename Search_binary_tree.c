#include <stdio.h>
#include <stdlib.h>
// 建立节点模型
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} SearchTree;

SearchTree *search(SearchTree *T, int data);
SearchTree *insertTree(SearchTree *T, int data);
SearchTree *FindMin(SearchTree *T);
SearchTree *FindMax(SearchTree *T);
SearchTree *deleteTree(SearchTree *T, int data);
void print(SearchTree *root);

/**
 * @brief  二叉查找树
 * @note   
 * @retval 
 */
int main(void)
{
    int data[7] = {45, 24, 53, 45, 12, 24, 90};
    int i;
    SearchTree *root = NULL; //二叉查找树根节点
    for (i = 0; i < 7; i++)  //创建二叉查找树
    {
        root = insertTree(root, data[i]);
    }
    printf("删除前：");
    print(root);
    printf("\n");
    // //root = insertTree(root, 55);
    // print(root);
    // printf("\n");
    printf("删除后：");
    root = deleteTree(root, 24);
    print(root);
    printf("\n");
    return 0;
}

/**
 * @brief  查找函数
 * @note   
 * @param  *T: 查找树
 * @param  data: 带查找数据
 * @retval 查找到的节点
 */
SearchTree *search(SearchTree *T, int data)
{
    // 如果为空；
    if (T == NULL)
    {
        printf("此二叉树为空");
    }
    // 当不为空时分两种情况，第一种比此节点值大，第二种比此节点值小。
    else if (T->data > data)
    {
        return search(T->right, data);
    }
    else if (T->data < data)
    {
        return search(T->left, data);
    }
    else
    {
        return T;
    }
}

/**
 * @brief  插入
 * @note   
 * @param  *T: 查找树
 * @param  data: 待插入的数据
 * @retval 插入完毕的树
 */
SearchTree *insertTree(SearchTree *T, int data)
{
    // 如果为空
    if (T == NULL)
    {
        // 分配一块内存然后再挂在该树上
        T = (SearchTree *)malloc(sizeof(SearchTree));
        T->data = data;
        T->right = NULL;
        T->left = NULL;
        printf("%d插入树中\n", data);
        return T;
    }
    if (T->data > data)
    {
        T->left = insertTree(T->left, data);
    }
    else if (T->data < data)
    {
        T->right = insertTree(T->right, data);
    }
    else
    {
        printf("%d已在树中，不能再次插入!!!\n", data);
    }
    return T;
}

/**
 * @brief  寻找树的最小节点
 * @note   
 * @param  *T: 二叉搜索树
 * @retval 树的最小节点
 */
SearchTree *FindMin(SearchTree *T)
{
    if (T == NULL)
    {
        printf("该树为空");
    }
    if (T->left != NULL)
    {
        return FindMin(T->left);
    }
    return T;
}

/**
 * @brief  寻找树的最大节点
 * @note   
 * @param  *T: 二叉搜索树
 * @retval 树的最大节点
 */
SearchTree *FindMax(SearchTree *T)
{
    if (T == NULL)
    {
        printf("该树为空");
    }
    if (T->right != NULL)
    {
        return FindMax(T->right);
    }
    return T;
}

/**
 * @brief  删除节点算法
 * @note   
 * @param  *T: 二叉搜索树
 * @retval 删除完毕的树
 */
SearchTree *deleteTree(SearchTree *T, int data)
{
    if (T == NULL)
    {
        return T;
    }
    if (T->data > data)
    {
        T->left = deleteTree(T->left, data);
    }
    else if (T->data < data)
    {
        T->right = deleteTree(T->right, data);
    }
    // 找到该节点了
    else if (T->left != NULL && T->right != NULL) // 该节点度为2
    {
        printf("该删除节点为%d\n", T->data);
        T->data = FindMin(T->right)->data;
        T->right = deleteTree(T->right, data);
    }
    else
    {
        printf("该删除节点为%d\n", T->data);
        T = (T->left != NULL) ? T->left : T->right;
    }
    return T;
}

/**
 * @brief  中序输出
 * @note   中序遍历二叉查找树可以得到原关键字有序序列
 * @param  *root: 二叉搜索树
 * @retval None
 */
void print(SearchTree *root)
{
    if (root != NULL)
    {
        print(root->left);
        printf("%d ", root->data);
        print(root->right);
    }
}