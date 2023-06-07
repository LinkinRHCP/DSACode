#pragma once

#include <string>

using namespace std;

typedef char TElemType;

/* 链式存储结构的二叉树 */
typedef struct BiTNode {
    TElemType data;                     // 数据域
    struct BiTNode *lchild, *rchild;    // 左指针和右指针
}BiTNode, *BiTree;

void InitBiTree(BiTree &T);                     // 构造空二叉树T
void DestoryBiTree(BiTree &T);                  // 销毁二叉树T
void CreateBiTree(BiTree &T,                    // 从字符串创建二叉树T
                  string inputString);          // 输入的字符串应满足A(B,C(D))这样的格式
bool TreeEmpty(BiTree T);                       // 二叉树是否为空
void ClearTree(BiTree &T);                      // 删去T中的全部结点，使其成为空二叉树
int TreeDepth(BiTree T);                        // 返回T的深度
BiTNode* Root(BiTree T);                        // 返回T的根
BiTNode* Parent(BiTree T, BiTNode *x);          // 返回x的双亲结点
BiTNode* LeftChild(BiTree T, BiTNode *x);       // 返回x的左孩子
BiTNode* RightChild(BiTree T, BiTNode *x);      // 返回x的右孩子
BiTNode* LeftSibling(BiTree T, BiTNode *x);     // 返回x的左兄弟
BiTNode* RightSibling(BiTree T, BiTNode *x);    // 返回x的右兄弟
void InsertChild(BiTree &T, BiTNode *x,         // 根据LR为0或1，将c插入到T中，使之成为结点x的左子树或右子树。x原有的左子树或右子树则成为c的右子树
                 int LR, BiTree c);
void DeleteChild(BiTree &T, BiTNode *x,         // 根据LR为0或1，删除结点x的左子树或右子树
                 int LR);
void PrintBiTree(BiTree T);                     // 打印树

/* Tree in Child Sibling Representation Method */
typedef struct CSNode {
    TElemType data;
    struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

void InitCSTree(CSTree &T);                     // Init empty CSTree
void CreateCSTree(CSTree &T,                    // Create CSTree from string
                  string inputString);          // such as "A(B(E,F),C(G),D(H,I(K),J))"
void PrintCSTree(CSTree T);                     // Print CSTree
