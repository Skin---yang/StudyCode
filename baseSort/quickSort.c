/*  快速排序
 * 
 * 最优时间复杂度: O(n log n)
 * 平均时间复杂度: O(n log n)
 * 最差时间复杂度: O(n2)
 * 
 * 空间复杂度: 根据实现会有变化
 *   
 *   排序思想：
 *      选定一个基准数，然后将剩余的所有数和基准数比较，比基准数小的放在左边，比基准数大的放在右边。相等的就随意了。
 *      通过这样分区之后基准数的位置肯定是对了的。
 *      然后通过递归将基准数前后两个分区的元素进行分区，最后达成排序。
 *
 */ 


#include "comm.h"

void quick_sort(int arr[], int start, int end)
{
    if(start >= end)
        return;
    
    //select the last number as the number of base number.
    int left = start;
    int right = end - 1;
    int baseNumber = arr[end];

    while(left < right)
    {
        while(arr[left] < baseNumber && left < right)
            ++left;
        while(arr[right] >= baseNumber && left < right)
            --right;

        swap(&arr[left], &arr[right]);
    }

    if(arr[left] >= baseNumber)
    {
        swap(&arr[left], &arr[end]);
    }
    else
    {
        ++left;
    }
    
    if(left > 0)
    {
        quick_sort(arr, start, left - 1);
    }
    quick_sort(arr, left + 1, end);
}

//recursion achieve
void quickSort_Recursion(int arr[], int len)
{
    quick_sort(arr, 0, len-1);
}

int main(int argc, char **argv)
{
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    quickSort_Recursion(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}
