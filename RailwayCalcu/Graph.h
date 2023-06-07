#pragma once

#include <string>


using namespace std;

typedef string VertexType;
typedef int ArcType;

/* 邻接矩阵表示法 */

const int MAX_VERTEX_NUM = 30;
const int INFINITY = 0x7fffff;

// 图的类型：有向图、有向网、无向图、无向网
typedef enum {DG, DN, UDG, UDN} GraphKind;

typedef struct {
    // VertexType表示顶点的类型，例如char、int……
    VertexType vexs[MAX_VERTEX_NUM];
    // ArcType表示边和权值的类型
    // 若为无权图，可取bool型
    // 若为网，可取int型、float型……
    ArcType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
} MGraph;

void CreateUDN(MGraph &G); // 构造无向网
void CreateDN(MGraph &G); // 构造有向网
void DestroyGraph(MGraph &G); // 销毁图
int LocateVex(MGraph G, VertexType v); // 查找顶点
VertexType GetVex(MGraph G, int v); // 返回存储在位置v中的顶点的值
void PutVex(MGraph &G, int v, VertexType value); // 将值value赋值给存储在位置v中的顶点
void showGraph(MGraph G); // 显示图

int Dijkstra(MGraph &G,int v1,int v2,int D[],int P[][MAX_VERTEX_NUM]);
void Deletecity(MGraph &G);//删除城市
void Printcity(MGraph G);//打印城市及编号
void GetminRoad(MGraph G);//获得最短路径

/* 邻接表表示法 */

struct ArcNode {
    int adjvex;
    ArcType weight;
    ArcNode *nextarc;
};
typedef struct {
    VertexType data;
    ArcNode *firstarc;
} VertexNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
    GraphKind kind;
} ALGraph;

void CreateUDN(ALGraph &G); // 构造无向网
void CreateDN(ALGraph &G); // 构造有向网
int LocateVex(ALGraph G, VertexType v); // 查找顶点
void showGraph(ALGraph G); // 显示图
