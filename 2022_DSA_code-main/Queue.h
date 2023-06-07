#pragma once

#include "LinkList.h"

/* 链队列 */
typedef LinkList QueuePtr;
typedef struct {
    QueuePtr front; // 头指针
    QueuePtr rear;  // 尾指针
} LinkQueue;

void InitQueue_L(LinkQueue &Q); // 构造空队列
bool QueueEmpty_L(LinkQueue Q); // 判断队列是否为空
void EnQueue_L(LinkQueue &Q, ElemType e); // 入队
bool DeQueue_L(LinkQueue &Q, ElemType &e); // 出队
void ShowQueue_L(LinkQueue Q); // 打印队列

/* 循环队列 */
typedef struct {
    ElemType *elem; // 基地址
    int queuesize;  // 当前分配内存大小
    int front;
    int rear;
} SqQueue;

void InitQueue_sq(SqQueue &Q, int msize); // 构造空队列
int QueueLength_sq(SqQueue Q); // 求队列长度
void EnQueue_sq(SqQueue &Q, ElemType e); // 入队
bool DeQueue_sq(SqQueue &Q, ElemType &e); // 出队
void ShowQueue_sq(SqQueue Q); // 打印队列
