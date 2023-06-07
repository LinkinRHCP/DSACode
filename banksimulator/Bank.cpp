#include <iostream>
#include <stdio.h>
#include <ctime>
#include "Bank.h"

using namespace std;

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
void EnQueue_L(LinkQueue &Q, int e) {
    QueuePtr p = new LNode;
    p->data = e; p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    Q.length++;
}

// 出队
bool DeQueue_L(LinkQueue &Q, int &e) {
    if (QueueEmpty_L(Q)) return false;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    Q.length--;
    if (Q.rear == p) Q.rear = Q.front; // 注意：队列变空特殊处理
    delete p; return true;
}

void bank_simulator(int nc, Customer cust[], int nw, window *win)
{
    const int TIME = 480;//总时间取9:00至17:00
    int t=0;//初始时间
    int c,w;//中间变量
    int idw = nw;//空闲窗口数

    float sum_wait = 0;//等待时间总长
    float sum_busywin = 0;//每分钟忙碌窗口总数

    LinkQueue line;InitQueue_L(line);
    cout << "开业啦！" << endl;

    while (t < TIME || line.length > 0 || idw < nw)
    {
        if(t < TIME) for(c=0; c<nc; c++)//来的人先入队 
            if(cust[c].arrival == t) EnQueue_L(line,c);//入队元素为其在名单中的位置

        for(w=0; w<nw; ++w) 
        if (win[w].now == busy)//若该窗口忙碌,则进行时间比较，判断服务是否结束
        {
            c=win[w].cus_num;
            if (t-win[w].start_time == cust[c].service_time)
            {
                win[w].now = idle;
                idw++;
            }
            sum_busywin++;//记录总每分钟忙碌窗口数     
        }
        
        for (w=0;w<nw; w++)//空闲窗口开始服务
        {
            if (win[w].now == idle && line.length > 0)
            {
                DeQueue_L(line,c); sum_wait += (t-cust[c].arrival);//出队并记录等待时间
                win[w].cus_num = c;
                win[w].start_time = t;
                win[w].now = busy;
                idw--;
            }    
        }
       t++;//时间推进
    //    cout << t << endl;
    //    cout << idw << endl; 
    }
    cout << "营业结束,共营业" << t << "分钟" << endl;
    cout << "平均等待时间为:" << sum_wait/TIME << "分钟" << endl;
    cout << "窗口平均占用率为:" << sum_busywin/(nw*t) << endl;
}

