#pragma once

#include <iostream>

using namespace std;

/* 顺序栈 */
const int SQSTACK_INC_SIZE = 10;

//typedef int ElemType;
typedef char StackElemType;

typedef struct {
    StackElemType *elem; // 基地址
    int stacksize;  // 当前分配内存大小，单位是sizeof(ElemType)
    int top;        // 栈顶位置，定义为表长-1
} SqStack;

void InitStack_sq(SqStack &S, int msize);
void DestroyStack_sq(SqStack &S);
bool GetTop_sq(SqStack S, StackElemType &e);
void Increment(SqStack &S, int inc_size = SQSTACK_INC_SIZE);
void Push_sq(SqStack &S, StackElemType e);
bool Pop_sq(SqStack &S, StackElemType &e);

/* 自定义方法 */
void ShowStack_sq(SqStack S); // 显示顺序栈信息

/* 顺序栈：泛型 */
template <class T>
struct SqStackT {
    T *elem; // 基地址
    int stacksize;  // 当前分配内存大小，单位是sizeof(ElemType)
    int top;        // 栈顶位置，定义为表长-1
};

template <class T>
void InitStack_sqT(SqStackT<T> &S, int msize) {
    S.elem = new T[msize];
    S.stacksize = msize;
    S.top = -1;
}

template <class T>
void DestroyStack_sqT(SqStackT<T> &S) {
    delete []S.elem;
    S.stacksize = 0;
    S.top = -1;
}

template <class T>
bool GetTop_sqT(SqStackT<T> S, T &e) {
    if (S.top == -1) return false;
    e = S.elem[S.top];
    return true;
}

template <class T>
void IncrementT(SqStackT<T> &S, int inc_size = SQSTACK_INC_SIZE) {
    T *a = new T[S.stacksize + inc_size];
    for (int i=0; i<=S.top; ++i) a[i] = S.elem[i];
    delete []S.elem; S.elem = a;
    S.stacksize += inc_size;
}

template <class T>
void Push_sqT(SqStackT<T> &S, T e) {
    if (S.top == S.stacksize-1) IncrementT(S);
    S.elem[++S.top] = e;
}

template <class T>
bool Pop_sqT(SqStackT<T> &S, T &e) {
    if (S.top == -1) return false;
    e = S.elem[S.top--];
    return true;
}

// 显示顺序栈信息
template <class T>
void ShowStack_sqT(SqStackT<T> S) {
    for (int i = 0; i <= 10; i++) {
        cout << "=";
    }
    cout << "=>" << endl;
    for (int i = 0; i <= S.top; i++) {
        cout << "|" << S.elem[i];
    }
    cout << endl;
}

/* 自定义方法 */
void ShowStack_sq(SqStack S); // 显示顺序栈信息
