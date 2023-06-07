#include <iostream>
#include "SqList.h"
#include "common.h"

using namespace std;

// 初始化顺序表
void InitList_sq(SqList &L, int msize) {
    L.elem = new ElemType[msize];
    L.listsize = msize;
    L.length = 0;
}

// 销毁顺序表
void DestoryList_sq(SqList &L) {
    delete []L.elem;
    L.length = 0;
    L.listsize = 0;
}

// 判断顺序表是否为空
bool ListEmpty_sq(SqList L) {
    return (L.length == 0);
}

// 返回顺序表的长度
int ListLength_sq(SqList L) {
    return L.length;
}

// 获取线性表L中位序为i的元素
void GetElem_sq(SqList L, int i, ElemType &e) {
    if (i < 1 || i > L.length) ErrorMsg("Invalid i value");
    e = L.elem[i-1];
}

// 返回顺序表L中首个e元素的位序
int LocateElem_sq(SqList L, ElemType e) {
    for (int i = 1; i <= L.length; ++i)
        if (L.elem[i-1] == e) return i;
    return 0;
}

// 在顺序表L中位序为i的元素前面插入元素e
void ListInsert_sq(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) ErrorMsg("Invalid i value");
    if (L.length == L.listsize) Increment(L, 10);
    for (int j = L.length - 1; j >= i - 1; --j) L.elem[j+1] = L.elem[j];
    L.elem[i-1] = e;
    ++L.length;
}

// 增加顺序表的容量
void Increment(SqList &L, int inc_size) {
    ElemType *a = new ElemType[L.listsize + inc_size];
    for (int i = 0; i < L.length; ++i) a[i] = L.elem[i];
    delete []L.elem; L.elem = a;
    L.listsize += inc_size;
}

// 删除顺序表中位序为i的元素，并把值赋予e
void ListDelete_sq(SqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length) ErrorMsg("Invalid i value");
    e = L.elem[i-1];
    for (int j = i; j <= L.length - 1; ++j) L.elem[j-1] = L.elem[j];
    --L.length;
}

/* 自定义方法 */

// 打印顺序表
void ShowList_sq(SqList L) {
    int x;
    for (int i = 0; i < L.length; i++) {
        GetElem_sq(L, i+1, x);
        cout << x << "\t";
    }
    cout << endl;
}
