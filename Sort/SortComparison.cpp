#include "Sort.cpp"



int main() 
{
    SqTable L;
    InitList(L, N);
    for (int i=1; i<=N; ++i) L.r[i] = i;
    RandomShuffleList(L);
    clock_t begin, end;

    //冒泡排序
    SqTable L1;
    CopyList(L, L1);
    begin = clock(); // 计时器开始
    BubbleSort(L1);
    end = clock(); // 计时器结束
    Test(L1);   
    printf("BubbleSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    //快速排序
    SqTable L2;
    CopyList(L, L2);
    begin = clock(); // 计时器开始
    QuickSort(L2);
    end = clock(); // 计时器结束
    Test(L2);
    SameTest(L1,L2);    
    printf("QuickSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    //堆排序
    SqTable L3;
    CopyList(L, L3);
    begin = clock(); // 计时器开始
    HeapSort(L3);
    end = clock(); // 计时器结束
    Test(L3); 
    SameTest(L2,L3);    
    printf("HeapSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    //归并排序
    SqTable L4;
    CopyList(L, L4);
    begin = clock(); // 计时器开始
    MergeSort(L4);
    end = clock(); // 计时器结束
    Test(L4);
    SameTest(L3,L4);    
    printf("MergeSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    //希尔排序
    SqTable L5;
    CopyList(L, L5);
    begin = clock(); // 计时器开始
    ShlSort(L5);
    end = clock(); // 计时器结束
    Test(L5);    
    SameTest(L4,L5);
    printf("ShellSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    system("pause");
    return 0;
}