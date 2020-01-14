#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 100 /* 最大顶点数设为100 */
#define INFINITY 65535   /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;      /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;  /* 边的权值设为整型 */
typedef char DataType;   /* 顶点存储的数据类型设为字符型 */

//队列函数
typedef Vertex Ele;
typedef struct QNode
{ //队列结构体
    Ele data[MaxVertexNum];
    int front, rear;
} * Queue;

//图结构体定义
bool Visited[MaxVertexNum];
/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;     /* 有向边<V1, V2> */
    WeightType Weight; /* 权重 */
};
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                   /* 顶点数 */
    int Ne;                                   /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
    DataType Data[MaxVertexNum];              /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

//队列操作函数
Queue createQueue();
bool isempty(Queue q);
bool isfull(Queue q);
void add(Queue q, Ele e);
Ele del(Queue q);
//图操作函数
MGraph BuildGraph();
MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
static void Visit(Vertex V);
void BFS(MGraph Graph, Vertex V, void (*PVisit)(Vertex));

/**
 * @brief  BFS travers
 * @note   邻接矩阵存储
 * @retval None
 */
int main()
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        Visited[i] = false; //初始化为false
    }
    MGraph Graph = BuildGraph();

    BFS(Graph, 0, Visit);

    return 0;
}

/**
 * @brief  初始化一个有VertexNum个顶点但没有边的图
 * @note   0表示通路，没有边！！！！！
 * @param  VertexNum: 顶点个数
 * @retval 无边图(つ﹏⊂)
 */
MGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V = 0; V < Graph->Nv; V++)
    {
        for (W = 0; W < Graph->Nv; W++)
        {
            if (V == W)
            {
                Graph->G[V][W] = 0;
            }
            else
            {
                Graph->G[V][W] = INFINITY;
            }
        }
    }
    return Graph;
}

/**
 * @brief  加入边
 * @note   把光秃秃的图补上边
 * @param  Graph: 没有边被脱光的图
 * @param  E: 待插入边
 * @retval None
 */
void InsertEdge(MGraph Graph, Edge E)
{
    /* 插入边 <V1, V2> */
    Graph->G[E->V1][E->V2] = E->Weight;
    /* 若是无向图，还要插入边<V2, V1> */
    Graph->G[E->V2][E->V1] = E->Weight;
}

/**
 * @brief  构造图
 * @note   
 * @retval 图
 */
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    printf("输入顶点个数：");
    scanf("%d", &Nv);        /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */
    printf("输入边数：");
    scanf("%d", &(Graph->Ne)); /* 读入边数 */
    printf("输入边关系：\n");
    if (Graph->Ne != 0)
    {                                           /* 如果有边 */
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge(Graph, E);
        }
        free(E);
    }

    /* 如果顶点有数据的话，读入数据 */
    for (V = 0; V < Graph->Nv; V++)
    {
        scanf(" %c", &(Graph->Data[V]));
    }

    for (int i = 0; i < Nv; i++)
    {
        for (int j = 0; j < Nv; j++)
        {
            printf("%d ", Graph->G[i][j]);
        }
        printf("\n");
    }

    return Graph;
}

/**
 * @brief  vist函数
 * @note   打印节点
 * @param  V: 须打印的节点
 * @retval None
 */
static void Visit(Vertex V)
{
    printf("正在访问顶点%d\n", V);
}

/**
 * @brief  BSF遍历
 * @note   
 * @param  Graph: 需要遍历的图
 * @param  V: 顶点
 * @param  vist:打印函数 
 * @retval None
 */
void BFS(MGraph Graph, Vertex V, void (*PVisit)(Vertex))
{
    Queue q = createQueue();
    /* 以V为出发点对邻接表存储的图Graph进行BFS搜索 */
    (*PVisit)(V);      /* 访问第V个顶点 */
    Visited[V] = true; /* 标记V已访问 */
    add(q, V);
    while (!isempty(q))
    {
        V = del(q);
        for (Vertex W = 0; W < Graph->Nv; W++)
        {
            if (W != V && Graph->G[V][W] != INFINITY && !Visited[W]) /* 若W是V的邻接点并且未访问过 */
            {
                (*PVisit)(W);      /* 访问第W个顶点 */
                Visited[W] = true; /* 标记W已访问 */
                add(q, W);
            }
        }
    }
}

//队列相关操作
//建队
Queue createQueue()
{
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->front = q->rear = -1;
    return q;
}
//判空
bool isempty(Queue q)
{

    return q->rear == q->front;
}
//判满
bool isfull(Queue q)
{

    return (q->rear + 1) % MaxVertexNum == q->front;
}
//入队
void add(Queue q, Ele e)
{
    if (isfull(q))
    {
        printf("Queue is full\n");
        return;
    }
    q->data[++q->rear] = e;
}
//出队
Ele del(Queue q)
{
    if (isempty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    return q->data[++q->front];
}
