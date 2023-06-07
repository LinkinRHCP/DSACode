#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "Sort.h"

using namespace std;

void InitList(SqTable &L, int len) {
    // 0号单元不用
    L.r = (ElemType*)malloc((len+1)*sizeof(ElemType));
    L.len = len;
}

void CopyList(SqTable L, SqTable &newL) {
    newL.r = (ElemType*)malloc((L.len+1)*sizeof(ElemType));
    newL.len = L.len;
    memcpy(newL.r, L.r, (L.len+1)*sizeof(ElemType));
}

// 求一个整数的p次方
int intpow(int n, unsigned int p) {
    int res = 1;
    for (unsigned int i=0; i<p; ++i)
        res *= n;
    return res;
}

// 生成一个随机整数，其取值范围是[0, bound]
int randb(int bound) {
    int r = 0;
    unsigned int power = 0;
    do {
        r *= RAND_MAX;
        r += rand(); ++power;
    } while (intpow(RAND_MAX, power) < bound);
    return r % (bound+1);
}

// 随机打乱一个数组
void RandomShuffleList(SqTable L) {
    ElemType* array = L.r + 1; int n = L.len;
    for (int i=n-1; i>0; --i) {
        int j = randb(i); // 0<=j<=i
        ElemType tmp = array[i]; array[i] = array[j]; array[j] = tmp;
    }
}

void Test(SqTable L)
{
    for (int i = 1; i < L.len; i++)
    {
        if (L.r[i] > L.r[i+1]) 
        {
            cout << "仍为乱序" << endl;   
            return;
        }
    }
    cout << "排序成功" <<endl;
}

void SameTest(SqTable L1,SqTable L2)
{
    for (int i = 1; i < L1.len; i++)
    {
        if (L1.r[i] != L2.r[i]) return;
    }
    cout << "相同" << endl;
}

void BubbleSort(SqTable L)
{
    for (int i = 1; i < L.len; i++)
        for (int j = L.len; j > i; j--)
            if (L.r[j] < L.r[j-1])
            {    
                swap(L.r[j],L.r[j-1]);
                //cout << "j=" << j <<endl;
            }            
    return;
}

int Partition(SqTable &L,int low,int high)
{
    L.r[0]=L.r[low];
    int pivot=L.r[low];
    while (low<high)
    {
        while (low<high && L.r[high] >= pivot) high--;
        L.r[low]=L.r[high];
        while (low<high && L.r[low] <= pivot) low++;
        L.r[high]=L.r[low];
    }
    L.r[low]=L.r[0];
    return low;
}

void QSort(SqTable &L,int low,int high)
{
    if (low<high)
    {
        int pivot=Partition(L,low,high);
        QSort(L,low,pivot-1);
        QSort(L,pivot+1,high);
    }
    return;
}

void QuickSort(SqTable &L)
{
    QSort(L,1,L.len);
}

void HeapAdjust(SqTable &L,int s,int t)
{
    int w=L.r[s];
    for (int i = 2*s; i <= t; i*=2)
    {
        if (i<t) i= (L.r[i]>L.r[i+1]) ? i:i+1;
        if (w >= L.r[i]) break;
        L.r[s]=L.r[i];
        s=i;
    }
    L.r[s]=w;
}

void HeapSort(SqTable &L)
{
    for (int i = L.len/2; i >= 1; i--) HeapAdjust(L,i,L.len);
    for (int i = L.len; i > 1; i--)
    {
        swap(L.r[1],L.r[i]);
        HeapAdjust(L,1,i-1);
    }
}

void Merge(ElemType Rs[],ElemType Rt[],int s,int m,int t)
{
    int i,j,k;
    for (i=s,j=m+1,k=i; i <= m && j <= t; k++)
    {
        if (Rs[i] <= Rs[j]) Rt[k]=Rs[i++];
        else Rt[k]=Rs[j++];
    }
    for (;i <= m;) Rt[k++]=Rs[i++];
    for (;j <= t;) Rt[k++]=Rs[j++];
    for (k=s; k <= t; k++) Rs[k]=Rt[k];
}


void MSortPass(ElemType Rs[],ElemType Rt[],int s,int t)
{
    if (s==t) {Rt[s]=Rs[s];return;}
    int m=(s+t)/2;
    MSortPass(Rs,Rt,s,m);
    MSortPass(Rs,Rt,m+1,t);
    Merge(Rs,Rt,s,m,t);
}

void MergeSort(SqTable &L)
{
    SqTable Ltem;
    InitList(Ltem,L.len);
    MSortPass(L.r,Ltem.r,1,L.len);
    L=Ltem;
}


void InSort2(ElemType *r,int n,int incr)
{
    for (int i = incr; i < n; i+=incr)
    {
        if (r[i] < r[i-incr])
        {
            int tmp = r[i];
            int k = i - incr;
            while (k >= 0 && r[k] > tmp)
            {
                r[k + incr] = r[k];
                k -= incr;
            }
            r[k + incr] = tmp;
        } 
        // for (int j = i; (j > incr) && (r[j] < r[j-incr]); j-=incr)
        // {
        //     swap(r[j],r[j-incr]);
        // }                     
    }       
}

void ShlSort(SqTable &L)
{
    int n=L.len;
    for (int i = n/2; i > 2; i/=2)
        for (int j=1;j <= i;j++)
            InSort2(&L.r[j],n+1-j,i);
    InSort2(&L.r[1],n,1);
}

