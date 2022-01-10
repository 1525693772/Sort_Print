#include "Sort.h"
#include "fatal.h"
#include <stdio.h>
#include <time.h>
#include <windows.h>

void Menu()
{
    printf("================Menu================\n");
    printf("-1.Clear data file\n");
    printf("0.Exit\n");
    printf("1.Generate random number\n");
    printf("2.Read data in keyboard\n");
    printf("3.Read data in file\n");
    printf("4.Bubble sort\n");
    printf("5.Selection sort\n");
    printf("6.Insetion sort\n");
    printf("7.Shell sort\n");
    printf("8.Merge sort\n");
    printf("9.Heap sort\n");
    printf("10.Quick sort\n");
    printf("=====================================\n");
}

void RandomNum(int size)
{
    FILE *fp;
    if ((fp = fopen("./Sort 1/Data/UnsortedData.TXT", "a")) == NULL)
        Error("Fail to open file!\n");
    setbuf(fp, NULL);
    fprintf(fp, "%d\n", size);
    fflush(fp);
    srand((unsigned int)time(NULL));
    int num, i;
    for (i = 0; i < size; i++)
    {
        if (i % 100 == 0)
        {
            Sleep(1500);
            srand((unsigned int)time(NULL));
        }
        fprintf(fp, "%d ", rand() % 100000);
        fflush(fp);
    }
    fprintf(fp, "\n");
    fflush(fp);
    fclose(fp);
}

void Swap(ET *a, ET *b)
{
    if (a == b)
        return;
    ET tmp = *a;
    *a = *b;
    *b = tmp;
}

int MaxIndex(ET *a, int i1, int i2)
{
    return a[i1] > a[i2] ? i1 : i2;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int Min(int a, int b)
{
    return a < b ? a : b;
}

void PrintArray(ET *array, const int length)
{
    int i;
    for (i = 0; i < length; i++)
        printf("%d ", array[i]);
    puts("");
}

void PrintArraySection(ET *array, const int start, const int end)
{
    int i;
    for (i = start; i <= end; i++)
        printf("%d ", array[i]);
    puts("");
}

void BubbleSort(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    int i, o, j = 1;
    printf("The origin sequence : ");
    PrintArray(array, length);
    for (i = length - 1; i > 0; i--)
    {
        for (o = 0; o < i; o++)
            if (array[o] > array[o + 1])
                Swap(&array[o], &array[o + 1]);
        printf("Move the %dth largest number to [%d] : ", j, i);
        PrintArray(array, length);
        j++;
    }
    puts("");
}

void SelectionSort(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    int min, i, o, j = 1;
    printf("The origin sequence : ");
    PrintArray(array, length);
    for (i = 0; i < length; i++)
    {
        min = i;
        for (o = i + 1; o < length; o++)
        {
            if (array[o] < array[min])
                min = o;
        }
        Swap(&array[i], &array[min]);
        printf("Move the %dth smallest number to [%d] : ", j, i);
        PrintArray(array, length);
        j++;
    }
    puts("");
}

void InsertionSort(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    int i, o, j = 1, tmp;
    printf("The origin sequence : ");
    PrintArray(array, length);
    for (i = 1; i < length; i++)
    {
        tmp = array[i];
        for (o = i; o > 0 && array[o - 1] > tmp; o--)
            array[o] = array[o - 1];
        array[o] = tmp;
        printf("%dth run,make the leftest %d number be ordered sequence : ", j, j + 1);
        PrintArray(array, length);
        j++;
    }
    puts("");
}

void InsertionSort_NoPrint(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    int i, o, tmp;
    for (i = 1; i < length; i++)
    {
        tmp = array[i];
        for (o = i; o > 0 && array[o - 1] > tmp; o--)
            array[o] = array[o - 1];
        array[o] = tmp;
    }
}

void ShellSort(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    int inc, i, j, o = 1;
    int temp;
    printf("The origin sequence : ");
    PrintArray(array, length);
    for (inc = length / 2; inc > 0; inc /= 2)
    {
        for (i = inc; i < length; i++)
        {
            temp = array[i];
            for (j = i - inc; j >= 0 && array[j] > temp; j -= inc)
                array[j + inc] = array[j];
            array[j + inc] = temp;
        }
        printf("The %dth run,increament = %d : ", o++, inc);
        PrintArray(array, length);
    }
    puts("");
}

void Merge(ET *array, ET *array1, int start, int end, int mainlen)
{
    if (start >= end)
        return;
    int length = end - start, mid = length / 2 + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    Merge(array, array1, start1, end1, mainlen);
    Merge(array, array1, start2, end2, mainlen);
    int k = start;
    while (start1 <= end1 && start2 <= end2)
        array1[k++] = array[start1] < array[start2] ? array[start1++] : array[start2++];
    while (start1 <= end1)
        array1[k++] = array[start1++];
    while (start2 <= end2)
        array1[k++] = array[start2++];
    for (k = start; k <= end; k++)
        array[k] = array1[k];
    printf("Sorted  [%d] - [%d]  :  ", start, end);
    PrintArray(array, mainlen);
    puts("");
}

void MergeSort(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    printf("The origin sequence : ");
    PrintArray(array, length);
    puts("");
    int array1[length];
    Merge(array, array1, 0, length - 1, length);
}

void HeapAdjustment1(ET *array, const int length, int pos)
{
    //left child's index is even number
    //right child's index is odd number
    while (pos > 0)
    {
        if (pos % 2 == 0) //pos is even number,so it is a right child
        {
            //pos-1 means pos's silbiling,that is the left child here
            //it may exceed the length of the array,so need to check
            if (array[MaxIndex(array, pos, pos - 1)] > array[(pos - 1) / 2])
                Swap(&array[MaxIndex(array, pos, pos - 1)], &array[(pos - 1) / 2]);
            pos = (pos - 1) / 2;
        }
        else //pos is odd number
        {
            if (pos + 1 == length)
            {
                if (array[pos] > array[(pos - 1) / 2])
                    Swap(&array[pos], &array[(pos - 1) / 2]);
                pos = (pos - 1) / 2;
            }
            else
            {
                if (array[MaxIndex(array, pos, pos + 1)] > array[(pos - 1) / 2])
                    Swap(&array[MaxIndex(array, pos, pos + 1)], &array[(pos - 1) / 2]);
                pos = (pos - 1) / 2;
            }
        }
    }
}

void HeapAdjustment2(ET *array, int start, int end)
{
    while (start < end)
    {
        if ((start + 1) * 2 - 1 < end)
        {
            int tmp = MaxIndex(array, (start + 1) * 2, (start + 1) * 2 - 1);
            if (array[start] < array[MaxIndex(array, (start + 1) * 2, (start + 1) * 2 - 1)])
                Swap(&array[start], &array[MaxIndex(array, (start + 1) * 2, (start + 1) * 2 - 1)]);
            start = tmp;
        }
        else if ((start + 1) * 2 - 1 == end)
        {
            if (array[start] < array[end])
                Swap(&array[start], &array[end]);
            start = end;
        }
        else
            break;
    }
}

void HeapSort(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    printf("The origin sequence : ");
    PrintArray(array, length);
    int i;
    //Build max head
    for (i = length - 1; i > 0; i -= 2)
    {
        HeapAdjustment1(array, length, i);
    }
    //heap sort
    printf("The sequence after building max heap : ");
    PrintArray(array, length);
    puts("");
    for (i = length - 1; i > 0; i--)
    {
        Swap(&array[0], &array[i]);
        printf("Swap the first one and the last one : ");
        PrintArray(array, length);
        HeapAdjustment2(array, 0, i - 1);
        printf("Rebuild the max heap from 0 to %d    : ", i - 1);
        PrintArray(array, length);
        puts("");
    }
}

int Median3(ET *array, int left, int right)
{
    int mid = (right + left) / 2;
    if (array[left] > array[mid])
        Swap(&array[left], &array[mid]);
    if (array[mid] > array[right])
        Swap(&array[mid], &array[right]);
    if (array[left] > array[mid])
        Swap(&array[left], &array[mid]);
    Swap(&array[mid], &array[right - 1]);
    return array[right - 1];
}

void QSort(ET *array, const int mainlength, int left, int right)
{
    if (left + Cutoff <= right)
    {
        int Pivot = Median3(array, left, right);
        int i = left + 1, j = right - 2;
        while (i < j)
        {
            while (array[i] < Pivot && i < j)
                i++;
            while (array[j] >= Pivot && i < j)
                j--;
            Swap(&array[i], &array[j]);
        }
        if (array[i] >= array[right])
            Swap(&array[i], &array[right]);
        else
            left++;
        printf("[Pivot = %d],[%d] - [%d] : ", Pivot, left, right);
        PrintArray(array, mainlength);
        if (left)
            QSort(array, left, i - 1);
        QSort(array, i + 1, right);
    }
    else
    {
        InsertionSort_NoPrint(array + left, right - left + 1);
    }
}

void QuickSort(ET *array, const int length)
{
    if (!array)
        Error("Invalid array!\n");
    printf("The origin sequence  :   ");
    PrintArray(array, length);
    QSort(array, length, 0, length - 1);
    printf("The result sequence is : ");
    PrintArray(array, length);
    puts("");
}