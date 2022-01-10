#define Cutoff 2

typedef int ET;

void Menu();

void RandomNum(int size);

void Swap(ET *a, ET *b);

int MaxIndex(ET *a, int i1, int i2);

int Max(int a, int b);

int Min(int a, int b);

void PrintArray(ET *array, const int length);

void PrintArraySection(ET *array, const int start, const int end);

void BubbleSort(ET *array, const int length);

void SelectionSort(ET *array, const int length);

void InsertionSort(ET *array, const int length);
void InsertionSort_NoPrint(ET *array, const int length);

void ShellSort(ET *array, const int length);

void Merge(ET *array, ET *array1, int start, int end, int mainlen);
void MergeSort(ET *array, const int length);

void HeapAdjustment1(ET *array, const int length, int pos);
void HeapAdjustment2(ET *array, int start, int end);
void HeapSort(ET *array, const int length);

int Median3(ET *array, int left, int right);
void QSort(ET *array, const int mainlength, int left, int right);
void QuickSort(ET *array, const int length);