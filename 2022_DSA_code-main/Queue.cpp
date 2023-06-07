#include <iostream>
#include "Queue.h"
#include "SqList.h"
#include "common.h"

using namespace std;

/* 链队列 */

// 构造空队列
void InitQueue_L(LinkQueue &Q) {
    Q.front = Q.rear = new LNode;
    Q.front->next = NULL;
}

// 判断队列是否为空
bool QueueEmpty_L(LinkQueue Q) {
    return Q.front == Q.rear;
}

// 入队
void EnQueue_L(LinkQueue &Q, ElemType e) {
    QueuePtr p = new LNode;
    p->data = e; p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

// 出队
bool DeQueue_L(LinkQueue &Q, ElemType &e) {
    if (QueueEmpty_L(Q)) return false;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front; // 注意：队列变空特殊处理
    delete p; return true;
}

// 打印队列
void ShowQueue_L(LinkQueue Q) {
    QueuePtr p = Q.front->next;
    while (p) {
        cout << p->data << "\t";
        p = p->next;
    }
    cout << endl;
}

/* 循环队列 */

// 构造空队列
void InitQueue_sq(SqQueue &Q, int msize) {
    Q.elem = new ElemType[msize];
    Q.queuesize = msize;
    Q.front = Q.rear = 0;
}

// 求队列长度
int QueueLength_sq(SqQueue Q) {
    return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}

// 入队
void EnQueue_sq(SqQueue &Q, ElemType e) {
    if ((Q.rear+1) % Q.queuesize == Q.front) ErrorMsg("Full Queue!");
    Q.elem[Q.rear] = e; Q.rear = (Q.rear+1) % Q.queuesize;
}

// 出队
bool DeQueue_sq(SqQueue &Q, ElemType &e) {
    if (Q.front == Q.rear) return false;
    e = Q.elem[Q.front]; Q.front = (Q.front+1) % Q.queuesize;
    return true;
}

// 打印队列
void ShowQueue_sq(SqQueue Q) {
    int length = QueueLength_sq(Q);
    for (int i = Q.front; i < Q.front + length; i++)
        cout << Q.elem[i % Q.queuesize] << "\t";
    cout << endl;
}
