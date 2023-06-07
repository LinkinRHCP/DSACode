#include <iostream>
#include "StackH.h"

using namespace std;

/* 顺序栈 */

void InitStack_sq(SqStack &S, int msize) {
    S.elem = new StackElemType[msize];
    S.stacksize = msize;
    S.top = -1;
}

void DestroyStack_sq(SqStack &S) {
    delete []S.elem;
    S.stacksize = 0;
    S.top = -1;
}

bool GetTop_sq(SqStack S, StackElemType &e) {
    if (S.top == -1) return false;
    e = S.elem[S.top];
    return true;
}

void Increment(SqStack &S, int inc_size) {
    StackElemType *a = new StackElemType[S.stacksize + inc_size];
    for (int i=0; i<=S.top; ++i) a[i] = S.elem[i];
    delete []S.elem; S.elem = a;
    S.stacksize += inc_size;
}

void Push_sq(SqStack &S, StackElemType e) {
    if (S.top == S.stacksize-1) Increment(S);
    S.elem[++S.top] = e;
}

bool Pop_sq(SqStack &S, StackElemType &e) {
    if (S.top == -1) return false;
    e = S.elem[S.top--];
    return true;
}

/* 自定义方法 */

// 显示顺序栈信息
void ShowStack_sq(SqStack S) {
    for (int i = 0; i <= 10; i++) {
        cout << "=";
    }
    cout << "=>" << endl;
    for (int i = 0; i <= S.top; i++) {
        cout << "|" << S.elem[i];
    }
    cout << endl;
}

