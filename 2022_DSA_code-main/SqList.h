#pragma once

typedef int ElemType; // 元素类型重命名
typedef struct {
    ElemType *elem; // 基地址
    int listsize; // 当前分配内存大小
    int length; // 当前顺序表长度
} SqList;

void InitList_sq(SqList &L, int msize); // 初始化顺序表
void DestoryList_sq(SqList &L); // 销毁顺序表
void ClearList(SqList &L); // 置空顺序表
bool ListEmpty_sq(SqList L); // 判断顺序表是否为空
int ListLength_sq(SqList L); // 返回顺序表的长度
void GetElem_sq(SqList L, int i, ElemType &e); // 获取线性表L中位序为i的元素
int LocateElem_sq(SqList L, ElemType e); // 返回顺序表L中首个e元素的位序
void ListInsert_sq(SqList &L, int i, ElemType e); // 在顺序表L中位序为i的元素前面插入元素e
void Increment(SqList &L, int inc_size); // 增加顺序表的容量
void ListDelete_sq(SqList &L, int i, ElemType &e); // 删除顺序表中位序为i的元素，并把值赋予e

/* 自定义方法 */
void ShowList_sq(SqList L); // 打印顺序表
