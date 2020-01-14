#include <stdio.h>
#include <stdlib.h>

typedef int ELEMENTTYPE;
typedef struct ListNode
{
    ELEMENTTYPE Element;
    struct ListNode *next;
} ListNode, *List;

List Create(List L);
int Destroy(List L);
void PrinList(List L);

/**
 * @brief  前序建表
 * @note   动态开辟，记得释放，遇到#停止
 * @retval None
 */
int main(void)
{
    List list = NULL;

    list = Create(list);
    PrinList(list);
    Destroy(list);
    
    return 0;
}

/**
 * @brief  创建链表
 * @note   输入指定字符停止
 * @param  L: 待创建的链表的头指针
 * @retval 表
 */
List Create(List L)
{
    List head, p;
    head = p = (List)malloc(sizeof(ListNode));
    p->next = NULL;

    while (scanf("%d", &p->Element) && 0 != p->Element - '#')
    {
        if (NULL == L)
        {
            L = head;
        }
        else
        {
            head->next = p;
        }
        head = p;
        p = (List)malloc(sizeof(ListNode));
        p->next = NULL;
    }
    return L;
}

/**
 * @brief  销毁链表
 * @note   
 * @param  L: 待销毁链表
 * @retval  0 / 1, 成功/失败
 */
int Destroy(List L)
{
    if (NULL == L)
    {
        return 1;
    }
    free(L);
    return 0;
}

/**
 * @brief  输出链表
 * @note   
 * @param  L: 待输出链表
 * @retval None
 */
void PrinList(List L)
{
    if (NULL == L)
    {
        printf("List is empty\n");
        return;
    }
    List tmp = L;
    while (NULL != tmp)
    {
        printf("%d ", tmp->Element);
        tmp = tmp->next;
    }
}