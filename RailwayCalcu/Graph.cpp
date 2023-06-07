#include <iostream>
#include <iostream>
#include <fstream>
#include "Graph.h"


using namespace std;

/* 邻接矩阵表示法 */

void CreateUDN(MGraph &G) {
    G.kind = UDN; // UDN表示无向网
    G.vexnum=0;G.arcnum=0;

    ifstream cityfile,distfile;
    cityfile.open("RailwayCalcu\\city.txt",ios::in);
    distfile.open("RailwayCalcu\\dist.txt",ios::in);

    if (!cityfile.is_open() || !distfile.is_open())
    {
        cout << "文件打开失败！" <<endl;
        system("pause");
        return;
    }
    
    int i=0,j=0,k=0,rem=INFINITY;
    // 读入顶点数据
    cityfile >> i;
    while (i!=rem)//读到文件尾时i将不变
    {
        rem=i;
        G.vexnum++;
        cityfile >> G.vexs[i];
        cityfile >> i;
    }
    cityfile.close();

    //初始化边数组
    for (i=0; i<G.vexnum; ++i)
        for (j=0; j<G.vexnum; ++j)
            G.arcs[i][j] = INFINITY; // 例如，INFINITY=INT_MAX

    //读入边数据
    int remj=INFINITY,remk=INFINITY;
    distfile >> j; distfile >> k;
    while (j != remj || k != remk)
    {
        G.arcnum++;
        remj=j,remk=k;
        int w=0;
        distfile >> w;
        G.arcs[j][k] = G.arcs[k][j] = w; // 无向网的邻接矩阵是对称的
        distfile >> j; distfile >> k;    
    }
    distfile.close();
}

void CreateDN(MGraph &G) {
    G.kind = DN; // DN表示有向网
    cin >> G.vexnum >> G.arcnum;
    int i,j,k;
    for (i=0; i<G.vexnum; ++i) cin >> G.vexs[i]; // 读入顶点数据
    for (i=0; i<G.vexnum; ++i)
        for (j=0; j<G.vexnum; ++j)
            G.arcs[i][j] = INFINITY; // 例如，INFINITY=INT_MAX
    for (k=0; k<G.arcnum; ++k) {
        VertexType vi, vj; ArcType w;
        cin >> vi >> vj >> w;
        i = LocateVex(G, vi); j = LocateVex(G, vj);
        G.arcs[i][j] = w; // 有向网的邻接矩阵是不对称的
    }
}

// void DestroyGraph(MGraph &G) {
//     /* 销毁顶点数组 */
//     delete G.vexs;
//     /* 销毁边矩阵 */
//     delete G.arcs;
//     /* 重置各个成员 */
//     G.arcnum = 0;
//     G.vexnum = 0;
// }

int LocateVex(MGraph G, VertexType v) {
    for (int i=0; i<G.vexnum; ++i)
        if (G.vexs[i] == v) return i;
    return -1;
}

VertexType GetVex(MGraph G, int v) {
    if ((v >= G.vexnum) || (v < 0)) printf("Index out of range!");
    return G.vexs[v];
}

void PutVex(MGraph &G, int v, VertexType value) {
    if ((v >= G.vexnum) || (v < 0)) printf("Index out of range!");
    G.vexs[v] = value;
}

void showGraph(MGraph G) {
    /* 打印行号 */
    cout << "\t|\t";
    for (int i = 0; i < G.vexnum; i++) cout << G.vexs[i] << "\t";
    cout << endl;
    /* 打印分隔行 */
    cout << "-------\t|------\t";
    for (int i = 0; i < G.vexnum; i++) cout << "-------" << "\t";
    cout << endl;
    /* 分别打印每一行 */
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.vexs[i] << "\t|\t";
        for (int j = 0; j < G.vexnum; j++) {
            if (G.arcs[i][j] >= INFINITY / 2) cout << "INF\t";
            else cout << G.arcs[i][j] << "\t";
        }
        cout << endl;
    }
}

//经典算法
int Dijkstra(MGraph &G,int v1,int v2,int D[],int P[][MAX_VERTEX_NUM])
{
   int S[G.vexnum]={0};
   for (int i = 0; i < G.vexnum; i++)//初始化数组
   {
      D[i]=G.arcs[v1][i];
      if(D[i] != INFINITY)
      {
         P[i][0]=v1;
         P[i][1]=i;
         P[i][2]=-1;//-1说明路径结束
      }
   }

   S[v1]=1;
   D[v1]=0;
   int k=0;
   for (int i = 0; i < G.vexnum; i++)//主循环
   {
      int min=INFINITY;
      for (int j=0; j < G.vexnum; j++)//寻找最短路径
      {
         if (!S[j] && D[j]<min){min=D[j];k=j;}
      }
      if (k==v2) return 1;//找到v1至v2的最短路径
      S[k]=1;//v1至k号点最短路径确定

      for (int j = 0; j < G.vexnum; j++)
      {
         if (! S[j] && D[k] + G.arcs[k][j] < D[j])//是否修正的判断
         {
            //更新长度
            D[j]=D[k] + G.arcs[k][j];
            //更新路径
            int w=0;
            for (w=0;P[k][w] != -1;w++) P[j][w]=P[k][w];
            P[j][w]=j;P[j][w+1]=-1;
         }
      }   
   }
   cout << "此路不通！";
   return 0;
}

//删除城市
void Deletecity(MGraph &G)
{
   cout << "输入删除的城市的编号(一次只能删除一个):"; 
   int v;
   cin >> v;
   for (int i = 0; i < G.vexnum; i++)
   {
      G.arcs[v][i]=G.arcs[i][v]=INFINITY;

   }
   G.vexs[v]="NULL";
   return;
}

//打印城市及编号
void Printcity(MGraph G)
{
   for (int i = 0; i < G.vexnum; i++)
   {
      cout << i << " " << G.vexs[i] << endl;
   }
   return;
}

//获得最短路径
void GetminRoad(MGraph G)
{
   cout << "输入求最短路径的两个城市的编号:";
   int city1,city2;
   cin >> city1 >> city2;

   int D[G.vexnum],P[G.vexnum][MAX_VERTEX_NUM];
   if(Dijkstra(G,city1,city2,D,P))
   {
      cout << "最短路径长度为:" << D[city2] << endl;
      cout << "路径为:" << G.vexs[P[city2][0]];
      int k=1;
      while (P[city2][k]!=-1)
      {
         cout << "-->" <<  G.vexs[P[city2][k]];
         k++; 
      }         
   }
}


/* 邻接表表示法 */

void CreateUDN(ALGraph &G) {
    G.kind = UDN;
    cin >> G.vexnum >> G.arcnum;
    int i,j,k;
    for (i=0; i<G.vexnum; ++i) {
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }
    for (k=0; k<G.arcnum; ++k) {
        VertexType vi, vj; ArcType w;
        cin >> vi >> vj >> w;
        i = LocateVex(G, vi); j = LocateVex(G, vj);
        ArcNode *p = new ArcNode; p->adjvex = j; p->weight = w;
        p->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = p;
        p = new ArcNode; p->adjvex = i; p->weight = w;
        p->nextarc = G.vertices[j].firstarc; G.vertices[j].firstarc = p;
    }
}

void CreateDN(ALGraph &G) {
    G.kind = UDN;
    cin >> G.vexnum >> G.arcnum;
    int i,j,k;
    for (i=0; i<G.vexnum; ++i) {
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }
    for (k=0; k<G.arcnum; ++k) {
        VertexType vi, vj; ArcType w;
        cin >> vi >> vj >> w;
        i = LocateVex(G, vi); j = LocateVex(G, vj);
        ArcNode *p = new ArcNode; p->adjvex = j; p->weight = w;
        p->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = p;
    }
}

int LocateVex(ALGraph G, VertexType v) {
    for (int i=0; i<G.vexnum; ++i)
        if (G.vertices[i].data == v) return i;
    return -1;
}

void showGraph(ALGraph G) {
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.vertices[i].data << " ";
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            cout << "--(" << p->weight << ")--> ";
            cout << G.vertices[p->adjvex].data << " ";
            p = p->nextarc;
        }
        cout << "--> ^"<< endl;
    }
}
