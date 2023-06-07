#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Poly.h"

using namespace std;


LNode *InputList(int a)//多项式输入
{
   LNode *head = new LNode;
   LNode *p = head;
   int item = 0;
   float input=0;
   cout << "分别输入系数和次数，一次仅输入一项(系数输入0结束输入):" << endl;
   do
   {
      cin >> input;
      if (input == 0) //结束输入的判定
      {  
         break;
      }

      LNode *newnode = new LNode;
      newnode -> coeffience = input;
      item++;
      cin >> newnode ->frequency;
      p -> next = newnode;
      p = p -> next;
   } while (1);

   if(item == 0) 
   {
      head -> next = new LNode;
      head -> next -> coeffience = 0;
      head -> next -> frequency = 0;
   }
   head -> coeffience = item;//记录项数
   cout << "输入成功" << endl;
   return head;
}

void Deletezero(LinkList head)//删除系数为0的项
{
   if(head -> coeffience == 0) return;
   LNode *p = head;
   int times = 0;
   while (p != NULL && p -> next != NULL)
   {
      while (p -> next != NULL && fabs(p -> next -> coeffience) == 0)
      {
         LNode *q = p -> next;
         p -> next = p -> next -> next;
         delete q;
         times++;
      }
      p = p -> next;
   }
   head -> coeffience -= times;
}

void DeletePoly(LinkList &head)//销毁多项式
{
   if(head == NULL) 
   {
      cout << "已为空无法删除" << endl;
      return;
   }
   LNode *p = head, *q;
   while (p != NULL)
   {
      q = p;
      p = p -> next;
      delete q;     
   }
   head = NULL;
   cout << "删除完成" <<endl;
}


void ShowList_L(LinkList head) //多项式输出
{
   if (head -> coeffience == 0)//为空则输出0
   {
      cout << "0" << endl;
      return;
   }

   LNode *p = head -> next;
   while (p) 
   {
      cout  << "[" << p->coeffience << "X^(" << p->frequency << ")]+";
      p = p -> next;
   }
   cout << "\b" << " " << endl;
}

void ShowAll(LinkList *head)
{
   int i = 0;
   while(head[i] != NULL)//打印非空多项式
   {
      cout << "第" << i+1 << "个多项式: ";
      ShowList_L(head[i]); 
      i++;           
   }   
}

int Sort_Combine(LinkList head)//次数从大到小排序，并合并同类项
{
   LNode *p;
   int length = head -> coeffience, change;

   for (int j = 0; j < length-1; j++)//冒泡排序
   {
      int times=0;
      p = head -> next;

      for ( int i = 1 ; i < length-j; i++)
      {   
         while ((p -> next != NULL) && (p -> frequency == p -> next -> frequency))//合并同类项
         {
            p -> coeffience += p -> next -> coeffience;
            LNode *q = p -> next;
            p -> next = p -> next -> next;
            delete q;
            length--;
         }       

         if ((p -> next != NULL) && (p -> frequency < p -> next -> frequency))
         {
            change = p -> frequency;
            p -> frequency = p -> next -> frequency;
            p -> next -> frequency = change;

            change = p -> coeffience;
            p -> coeffience = p -> next -> coeffience;
            p -> next -> coeffience = change;     

            times ++;
         }

         p = p -> next;
      }

      if (times == 0)
      {
         head -> coeffience = length;         
         Deletezero(head);//删除0
         return 1;
      }
   }
   Deletezero(head);//删除0
   head -> coeffience = length;
   return 1;
}

LNode *Add_Sub(LinkList a, LinkList b, char type)//多项式加减
{
   LNode *newhead = new LNode, *q = a -> next;
   LNode *p = newhead;

   while(q != NULL)//复制第一个多项式
   {
      LNode *newnode = new LNode;
      newnode -> coeffience = q -> coeffience;
      newnode -> frequency = q -> frequency;
      p -> next = newnode;
      p = p -> next;
      q = q -> next;
   }

   LNode *remember = p;
   q = b -> next;
   while(q != NULL)//复制第二个多项式
   {
      LNode *newnode = new LNode;
      newnode -> coeffience = q -> coeffience;
      newnode -> frequency = q -> frequency;
      p -> next = newnode;
      p = p -> next;
      q = q -> next;
   }

   if(type == '-')//加减判定
   {
      remember = remember -> next;
      while(remember != NULL)
      { 
         remember -> coeffience = -(remember -> coeffience);
         remember = remember -> next;
      }
   }
   newhead -> coeffience = a -> coeffience + b -> coeffience;
   Sort_Combine(newhead);//进行加减
   return newhead;
}

LNode *Multiply(LinkList a, LinkList b)//多项式乘法
{
   LNode *newhead = new LNode;
   newhead -> coeffience = (a->coeffience)*(b->coeffience);//项数为两多项式项数之积
   LNode *p1 = a -> next, *p2 = b -> next, *q = newhead;
   //计算各项
   while (p1 != NULL)
   {
      p2 = b -> next;
      while (p2 != NULL)
      {
         LNode *newnode = new LNode;
         newnode -> coeffience = (p1->coeffience)*(p2->coeffience);
         newnode -> frequency = (p1->frequency)+(p2->frequency);
         q -> next = newnode;
         q = q -> next;
         p2 = p2 -> next;
      }
      p1 = p1 -> next;
   }
   Sort_Combine(newhead);//合并同类项
   return newhead;
}

LNode *Divison(LinkList a, LinkList b)//多项式除法
{
   LNode *p = a;
   LNode *newhead = new LNode;
   LNode *q = newhead;
   newhead -> coeffience = 0;
   while (p -> next != NULL && p -> coeffience != 0 && b -> next -> frequency <= p -> next -> frequency)
   {

      LNode *newnode = new LNode;
      newnode -> frequency = (p->next->frequency) - (b->next->frequency);
      newnode -> coeffience = (p->next->coeffience)/(b->next->coeffience);
      q -> next = newnode;
      q = q -> next;
      newhead -> coeffience++;
      p = Add_Sub(a, Multiply(newhead,b), '-');
   }
   return newhead;
}