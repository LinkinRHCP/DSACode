#include <stack>
#include <iostream>
#include "Tree.h"

using namespace std;

/* Binary Tree */

// 构造空二叉树T
void InitBiTree(BiTree &T) {
    T = NULL;
}

// 销毁二叉树T
void DestoryBiTree(BiTree &T) {
    T = NULL;
}

// 从字符串创建二叉树T，输入的字符串应满足A(B,C(D))这样的格式
void CreateBiTree(BiTree &T, string inputString) {
    stack<BiTNode*> btnStack;
    bool leftFlag = true;
    bool rootFlag = true;
    BiTNode *tempNode = NULL;
    for (char s : inputString) {
        /* 如果是字符，则创建相应结点 */
        if (((s >= 'A') && (s <= 'Z')) || ((s >= 'a') && (s <= 'z'))) {
            tempNode = new BiTNode;
            tempNode->data = s; tempNode->lchild = NULL; tempNode->rchild = NULL;
        }
        /* 如果是左括号，则将当前结点进栈 */
        if (s == '(') {
            btnStack.push(tempNode);
            leftFlag = true;
        }
        /* 如果是右括号，则将栈顶元素出栈 */
        else if (s == ')') {
            btnStack.pop();
        }
        /* 如果是逗号，则开始处理右子树 */
        else if (s == ',') {
            leftFlag = false;
        }
        /* 如果是字符 */
        if (((s >= 'A') && (s <= 'Z')) || ((s >= 'a') && (s <= 'z'))) {
            /* 如果是根结点，则将其赋值给二叉树变量 */
            if (rootFlag) {T = tempNode; rootFlag = false;}
            /* 否则，将其作为栈顶结点的子树 */
            else {
                BiTNode *topNode = btnStack.top();
                /* 左子树 */
                if (leftFlag) {
                    topNode->lchild = tempNode;
                }
                /* 右子树 */
                else {
                    topNode->rchild = tempNode;
                }
            }
        }
    }
}

// 二叉树是否为空
bool TreeEmpty(BiTree T) {
    return (T == NULL);
}

// 删去T中的全部结点，使其成为空二叉树
void ClearTree(BiTree &T) {
    /* 如果还有后代，则先释放后代 */
    if (T->lchild) ClearTree(T->lchild);
    if (T->rchild) ClearTree(T->rchild);
    /* 已经没有后代了，直接释放空间 */
    delete T;
    T = NULL;
}

// 返回T的深度
int TreeDepth(BiTree T) {
    /* 结点为空时，深度为0 */
    if (T == NULL) return 0;
    /* 结点非空时，深度为左子树和右子树之间的最大值+1 */
    else {
        int leftDepth = TreeDepth(T->lchild);
        int rightDepth = TreeDepth(T->rchild);
        int maxSubTree = (leftDepth > rightDepth) ? leftDepth : rightDepth;
        return (maxSubTree + 1);
    }
}

// 返回T的根
BiTNode* Root(BiTree T) {
    return T;
}

// 返回x的双亲结点
BiTNode* Parent(BiTree T, BiTNode *x) {
    if (T != NULL) {
        if ((T->lchild == x) || (T->rchild == x)) return T;
        else if (T == x) return NULL;
        else {
            BiTNode *findResult = Parent(T->lchild, x);
            if (findResult) return findResult;
            else return Parent(T->rchild, x);
        }
    }
    else return NULL;
}

// 返回x的左孩子
BiTNode* LeftChild(BiTree T, BiTNode *x) {
    return T->lchild;
}

// 返回x的右孩子
BiTNode* RightChild(BiTree T, BiTNode *x) {
    return T->rchild;
}

// 返回x的左兄弟
BiTNode* LeftSibling(BiTree T, BiTNode *x) {
    BiTNode *parent = Parent(T, x);
    return parent->lchild;
}

// 返回x的右兄弟
BiTNode* RightSibling(BiTree T, BiTNode *x) {
    BiTNode *parent = Parent(T, x);
    return parent->rchild;
}

// 根据LR为0或1，将c插入到T中，使之成为结点x的左子树或右子树。x原有的左子树或右子树则成为c的右子树
void InsertChild(BiTree &T, BiTNode *x, int LR, BiTree c) {
    if (LR == 0) {
        c->rchild = x->lchild;
        x->lchild = c;
    }
    else {
        c->rchild = x->rchild;
        x->rchild = c;
    }
}

// 根据LR为0或1，删除结点x的左子树或右子树
void DeleteChild(BiTree &T, BiTNode *x, int LR) {
    if (LR == 0) ClearTree(x->lchild);
    else ClearTree(x->rchild);
}

// 打印树（https://blog.csdn.net/jklinux/article/details/107866653）
void PrintBiTree1(BiTree T, int type, int level) {
    int i;

    if (T == NULL) return;

    PrintBiTree1(T->rchild, 2, level+1);
    switch (type) {
        case 0:
            printf("%c\n", T->data);
            break;
        case 1:
            for (i = 0; i < level; i++)
                printf("\t");
            printf("\\ %c\n", T->data);
            break;
        case 2:
            for (i = 0; i < level; i++)
                printf("\t");
            printf("/ %c\n", T->data);
            break;
    }
    PrintBiTree1(T->lchild, 1,  level+1);
}

void PrintBiTree(BiTree T) {
    PrintBiTree1(T, 0, 0);
}

/* Tree in Child Sibling Representation Method */

// Init empty CSTree
void InitCSTree(CSTree &T) {
    T = NULL;
}

// Create CSTree from string such as "A(B(E,F),C(G),D(H,I(K),J))"
void CreateCSTree(CSTree &T, string inputString) {
    bool isFirst = true; // Is the first (root) node?
    stack<CSNode*> st;
    CSNode *tempNode = NULL;
    for (char c : inputString) {
        // If meet the left brackt, push current node into the stack
        if (c == '(') {
            st.push(tempNode);
        }
        // If meet the right brackt, pop out the top node in the stack
        else if (c == ')') {
            st.pop();
        }
        // If meet a letter
        else if ((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z'))) {
            // Create a CSNode
            tempNode = new CSNode; tempNode->data = c; tempNode->firstchild = NULL; tempNode->nextsibling = NULL;
            // The first node is the root node
            if (isFirst) {
                T = tempNode;
                isFirst = false;
            }
            // If not the first node, then put it to a appropriate place
            else {
                CSNode *topNode = st.top();
                CSNode *p = topNode->firstchild;
                if (p == NULL) topNode->firstchild = tempNode;
                else {
                    while (p->nextsibling != NULL) {
                        p = p->nextsibling;
                    }
                    p->nextsibling = tempNode;
                }
            }
        }
    }
}

// Print CSTree
void PrintCSTree(CSTree T) {
    cout << "[Method] PrintCSTree: Haven't implement yet..." << endl;
}
