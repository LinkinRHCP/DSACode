#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <math.h>
#include "StackH.h"

#define EXPAND 0//数组扩展值

typedef struct //哈夫曼树结点
{
   int weight,ASC;
   int parent,lchild,rchild;
} HTNode, *HuffamTree;

typedef HTNode *HuffTree;

int Scandata(int ASCII[],int &chsum,float &all);//扫描文件

void Select(HTNode *HT,int i,int &s1,int &s2);//选取最小权与次小权
void Create_HuffmanTree(HuffamTree &HT,int ASCII[],int chsum);//构建哈夫曼树

void Coding(HuffTree HT,int root,char**HC,SqStack &S);//编码获取
void HuffmanCoding (HuffTree HT, char **&HC, int n);//哈夫曼编码

int Codedata(char **HC,int ASCII[]);//文件编码
int DeCode(HuffamTree HT,int root,float &codeall);//文件解码

void gotoxy(int x,int y);//光标定位函数
void Print_HuffmanTree(HuffamTree HT,int root,int line,int row,int n);//打印哈夫曼树

#endif