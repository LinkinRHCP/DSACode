#pragma once



#define N 100000

using namespace std;

typedef int ElemType;

typedef struct {
    ElemType *r;
    int len;
} SqTable;

void InitList(SqTable &L, int len);
void CopyList(SqTable L, SqTable &newL);
int intpow(int n, unsigned int p);// 求一个整数的p次方
int randb(int bound); // 生成一个随机整数，其取值范围是[0, bound]
void RandomShuffleList(SqTable L);// 随机打乱一个数组 
void Test(SqTable L);//测试排序结果
void SameTest(SqTable L1,SqTable L2);//比较排序结果

void BubbleSort(SqTable L);

int Partition(SqTable &L,int low,int high);
void QSort(SqTable &L,int low,int high);
void QuickSort(SqTable &L);

void HeapAdjust(SqTable &L,int s,int t);
void HeapSort(SqTable &L);

void Merge(ElemType Rs[],ElemType Rt[],int s,int m,int t);
void MSortPass(ElemType Rs[],ElemType Rt[],int s,int t);
void MergeSort(SqTable &L);

void InSort2(ElemType *r,int n,int incr);
void ShlSort(SqTable &L);