#include <iostream>
#include <stdlib.h>
#include "LinkList.h"
#include "common.h"

using namespace std;

/* 单链表 */

// 初始化链表
void InitList_L(LinkList &L) {
    L = NULL;
}

// 求链表长度
int ListLength_L(LinkList L) {
    LNode *p = L; int j = 0;
    while (p) {
    p = p->next; ++j;
    }
    return j;
}

// 链表查找元素
LNode* LocateElem_L(LinkList L, ElemType e) {
    LNode *p = L;
    while (p && p->data != e) p = p->next;
    return p;
}

// 链表插入元素
void ListInsert_L(LinkList &L, int i, ElemType e) {
    LNode *s = new LNode; s->data = e;
    if (i == 1) { s->next = L; L = s; }
    else {
        LNode *q = L; int j = 1;
        while (q && j < i-1) { q = q->next; ++j; }
        if (!q || j > i-1) ErrorMsg("Invalid i value");
        s->next = q->next;
        q->next = s;
    }
}

// 给定指针插入元素（后插）
void ListInsert_L_back(LinkList &L, LNode *p, LNode *s) {
    s->next = p->next;
    p->next = s;
}

// 给定指针插入元素（前插）
void ListInsert_L_front(LinkList &L, LNode *p, LNode *s) {
    if (p == L) {
        s->next = L;
        L = s;
    }
    else {
        LNode *q = L;
        while (q && q->next != p) q = q->next;
        if (!q) ErrorMsg("Invalid p value");
        s->next = p; q->next = s;
    }
}

// 给定指针删除元素
void ListDelete_L(LinkList &L, LNode *p, ElemType &e) {
    if (p == L) L = L->next;
    else {
        LNode *q = L;
        while (q->next && q->next != p) q = q->next;
        if (!(q->next)) ErrorMsg("Invalid p value");
        q->next = p->next;
    }
    e = p->data; delete p;
}

/* 自定义方法 */

// 打印链表
void ShowList_L(LinkList L) {
    LNode *p = L;
    while (p) {
        cout << p->data << "->";
        p = p->next;
    }
    cout << "^" << endl;
}

/* 双向循环链表（带头结点） */

// 初始化链表
void InitList_DL(DLinkList &L) {
    L = new DLNode;
    L->next = L;
    L->prior = L;
}

// 求链表长度
int ListLength_DL(DLinkList L) {
    DLNode *p = L->next;
    int length = 0;
    while (p != L) {
        length++;
        p = p->next;
    }
    return length;
}

// 链表查找元素
DLNode* LocateElem_DL(DLinkList L, ElemType e) {
    DLNode *p = L->next;
    while (p != L && p->data != e) p = p->next;
    return (p != L) ? p : NULL;
}

// 给定指针插入元素（前插）
void ListInsert_DL(DLinkList &L, DLNode *p, DLNode *s) {
    s->prior = p->prior;
    s->next = p;
    p->prior->next = s;
    p->prior = s;
}

// 给定指针删除元素
void ListDelete_DL(DLinkList &L, DLNode *p, ElemType &e) {
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    delete p;
}

/* 自定义方法 */

// 打印链表
void ShowList_DL(DLinkList L) {
    DLNode *p = L->next;
    while (p != L) {
        cout << p->data << "->";
        p = p->next;
    }
    cout << "^" << endl;
}
