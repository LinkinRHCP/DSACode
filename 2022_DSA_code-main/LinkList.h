#pragma once

/* 单链表 */
typedef int ElemType; // 元素类型
typedef struct LNode {
  ElemType data; // 数据域
  LNode *next;   // 指针域
} *LinkList;

void InitList_L(LinkList &L); // 初始化链表
int ListLength_L(LinkList L); // 求链表长度
LNode* LocateElem_L(LinkList L, ElemType e); // 链表查找元素
void ListInsert_L(LinkList &L, int i, ElemType e); // 给定位序插入元素
void ListInsert_L_back(LinkList &L, LNode *p, LNode *s); // 给定指针插入元素（后插）
void ListInsert_L_front(LinkList &L, LNode *p, LNode *s); // 给定指针插入元素（前插）
void ListDelete_L(LinkList &L, LNode *p, ElemType &e); // 给定指针删除元素

/* 自定义方法 */
void ShowList_L(LinkList L); // 打印链表

/* 双向循环链表（带头结点） */
typedef struct DLNode {
    ElemType data;
    DLNode *prior;
    DLNode *next;
} *DLinkList;

void InitList_DL(DLinkList &L); // 初始化链表
int ListLength_DL(DLinkList L); // 求链表长度
DLNode* LocateElem_DL(DLinkList L, ElemType e); // 链表查找元素
void ListInsert_DL(DLinkList &L, DLNode *p, DLNode *s); // 给定指针插入元素（前插）
void ListDelete_DL(DLinkList &L, DLNode *p, ElemType &e); // 给定指针删除元素

/* 自定义方法 */
void ShowList_DL(DLinkList L); // 打印链表
