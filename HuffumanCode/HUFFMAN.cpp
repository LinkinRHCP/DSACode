#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <math.h>
#include "StackH.cpp"
#include "HUFFMAN.h"

#define EXPAND 0//数组扩展值
 
using namespace std;


void Select(HTNode *HT,int i,int &s1,int &s2)//选取最小权与次小权
{
   int s1w=21474836,s2w=21474836;
   s1=s2=0;
   for (int j = 1; j < i; j++)
   {
      if (HT[j].parent==0)
      {
         if (HT[j].weight < s1w) 
         {
            s2=s1;s1=j;
            s2w=s1w;s1w=HT[j].weight;
         }
         else if (HT[j].weight < s2w) 
         {
            s2=j;
            s2w=HT[j].weight;
         }
      }
   }
}


void Coding(HuffTree HT,int root,char**HC,SqStack &S)//编码获取
{  
   char ch;
   if (root!=0)//树非空
   {
      if (HT[root].lchild==0)//抵达叶子节点
      {
         Push_sq(S,'\0');
         HC[root]=new char[(S.top+1)];
         strcpy(HC[root],S.elem);
         Pop_sq(S,ch);
      }
      
      Push_sq(S,'0');
      Coding(HT,HT[root].lchild,HC,S);
      Pop_sq(S,ch);

      Push_sq(S,'1');
      Coding(HT,HT[root].rchild,HC,S);
      Pop_sq(S,ch);
   }
   
}

void HuffmanCoding (HuffTree HT, char **&HC, int n)//哈夫曼编码
{
   SqStack S;
   InitStack_sq(S,n+2);
   HC = new char*[n+1];
   Coding(HT,2*n-1,HC,S);
}


//构建哈夫曼树
void Create_HuffmanTree(HuffamTree &HT,int ASCII[],int chsum) 
{
   int nodesum=chsum*2-1;
   HT=new HTNode[nodesum+1];

   int k=1;
   for (int i = 0; i < 256+EXPAND; i++)//初始化叶子结点
   {
      if(ASCII[i]!=0)
      {  
         HT[k].parent=HT[k].lchild=HT[k].rchild=0;//关系初始化
         HT[k].ASC=i-EXPAND; //赋予对应ASCII值
         HT[k].weight=ASCII[i];//赋予对应权值

         ASCII[i]=k;//方便文件编码时找到叶子结点位置

         k++;
      }
   }

   for (;k <= nodesum; k++)//初始化未使用空间
   {
      HT[k].parent=HT[k].lchild=HT[k].rchild=0;//关系初始化
      HT[k].weight=0;//未使用赋予0值
   }
   
   for ( k = chsum+1; k <= nodesum; k++)//构建哈夫曼树
   {
      int s1,s2;
      Select(HT,k,s1,s2);//选出最小与次小
      HT[k].lchild=s1, HT[k].rchild=s2;
      HT[k].weight=HT[s1].weight+HT[s2].weight;
      HT[s1].parent=HT[s2].parent=k;
   }   
}

//扫描文件
int Scandata(int ASCII[],int &chsum,float &all)
{
   int single;

   ifstream afile;
   afile.open("HuffumanCode\\stdiofake.h",ios::in);
   if (!afile.is_open())
   {
      cout << "文件打开失败！" <<endl;
      system("pause");
      return 0;
   }
   
   while ((single=afile.get()) != EOF)//记录字符出现次数，并记录字符种类总数
   {
      if (ASCII[single+EXPAND] == 0) chsum++;
      ASCII[single+EXPAND]++;
      all++;//记录字符总数
   } 

   afile.close();
   return 1;  
}

//文件编码
int Codedata(char **HC,int ASCII[])
{
   int single;

   ifstream purefile;
   ofstream codefile;
   purefile.open("HuffumanCode\\stdiofake.h",ios::in);
   codefile.open("HuffumanCode\\stdioCode.h",ios::out | ios::trunc);

   if (!purefile.is_open())
   {
      cout << "文件打开失败！" <<endl;
      system("pause");
      return 0;
   }

   while ((single=purefile.get()) != EOF)//进行文件编码
   {
      codefile << HC[ASCII[single]];
   }

   purefile.close();
   codefile.close();
   return 1;   
}

//文件解码
int DeCode(HuffamTree HT,int root,float &codeall)
{
   ifstream codefile;
   ofstream decodefile;   
   codefile.open("HuffumanCode\\stdioCode.h",ios::in);
   decodefile.open("HuffumanCode\\stdioDeCode.h",ios::out | ios::trunc);

   if (!codefile.is_open())
   {
      cout << "文件打开失败！" <<endl;
      system("pause");
      return 0;
   }

   int single,k=root;

   while ((single=codefile.get()) != EOF)//进行文件编码
   { 
      codeall++;//记录比特数     
      if (single==48) k=HT[k].lchild;
      else k=HT[k].rchild;

      if (HT[k].lchild == 0)//是叶子结点，写入字符并重置k位置
      {
         decodefile << (char)HT[k].ASC;
         k=root;
      }     
   }

   codefile.close();
   decodefile.close();     
   return 1; 
}

void gotoxy(int x,int y)//光标定位函数
{
	COORD p;//定义结构体变量p
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前函数句柄
	p.X=x;p.Y=y;//将光标的目标移动位置传递给结构体
	SetConsoleCursorPosition(handle,p);//移动光标
}

//打印哈夫曼树
void Print_HuffmanTree(HuffamTree HT,int root,int line,int row,int n)
{
   if (HT[root].lchild==0)//为叶子节点则打印ASCII值
   {
      cout << HT[root].ASC;
      return;
   }
   
   if (HT[root].lchild != 0)
   {
      gotoxy(line,row);      
      cout << "@";
      int i;
      for (i = 1; i <= n; i++)
      {
         gotoxy(line,row+i);
         cout << "|";  
      }
      gotoxy(line,row+n+1);
      cout << "----";
      Print_HuffmanTree(HT,HT[root].lchild,line+4,row+n+1,n/2);

      for (i = 1; i <= n; i++)
      {
         gotoxy(line,row-i);
         cout << "|";  
      }
      gotoxy(line,row-n-1);
      cout << "------";      
      Print_HuffmanTree(HT,HT[root].rchild,line+6,row-n-1,n/2);            
   }
}