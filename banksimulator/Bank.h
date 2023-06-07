#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <stdio.h>
#include <ctime>

#define WINDOWS 10
#define MAX_CUSTOMER 500
#define MAX_SERVICETIME 20
#define LATESTARRIVAL 450 

/* 单链表 */
typedef struct cus//客户信息
{
    int number=0;//客户编号
    int arrival;//到达时间
    int service_time;//业务时间
}Customer; 

enum status{idle,busy};

typedef struct bankwindow
{
    status now = idle;//窗口状态
    int start_time=0;//开始忙碌时间
    int cus_num=0;//服务顾客序号
}window;


typedef struct LNode {
  int data; // 数据域
  LNode *next;   // 指针域
} *QueuePtr;

/* 链队列 */

typedef struct Queue{
    QueuePtr front; // 头指针
    QueuePtr rear;  // 尾指针
    int length=0;
} LinkQueue;

void InitQueue_L(LinkQueue &Q);// 构造空队列
bool QueueEmpty_L(LinkQueue Q);// 判断队列是否为空
void EnQueue_L(LinkQueue &Q, int e);// 入队
bool DeQueue_L(LinkQueue &Q, int &e);//出队
void bank_simulator(int nc, Customer cust[], int nw, window *win);//模拟银行

#endif
