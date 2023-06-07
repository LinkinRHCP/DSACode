#ifndef POLY_H
#define POLY_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

typedef float ElemType; // 元素类型
typedef struct LNode 
{
  float coeffience=-1;int frequency; // 数据域
  LNode *next = NULL;   // 指针域
} *LinkList;

LNode *InputList(int a);//多项式输入
void Deletezero(LinkList head);//删除系数为0的项
void DeletePoly(LinkList &head);//销毁多项式
void ShowList_L(LinkList head);//多项式输出
void ShowAll(LinkList *head);//打印所有多项式
int Sort_Combine(LinkList head);//次数从大到小排序，并合并同类项
LNode *Add_Sub(LinkList a, LinkList b, char type);//多项式加减
LNode *Multiply(LinkList a, LinkList b);//多项式乘法
LNode *Divison(LinkList a, LinkList b);//多项式除法

#endif