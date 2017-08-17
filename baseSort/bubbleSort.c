/*  冒泡排序
 *
 *  最优时间复杂度: O(n)
 *  平均时间复杂度: O(n2)
 *  最差时间复杂度: O(n2)
 *
 *  空间复杂度: O(1)
 *  
 *  冒泡排序规则：
 *  1. 比较相邻的两个元素，如果第一个数比第二个数大，那么交换他们
 *  2. 重复以上步骤，除了最后一个
 *  3. 重复上面步骤直到没有需要比较的数字
 * */  

#include "comm.h"

void bubbleSort(int arr[], int len)
{
    // error deal
    if(!arr || len <= 1)
        return;

    for(int i = 0; i < len - 1; ++i)
    {
        for(int j = 0; j < len - i - 1; ++j)
        {
            if(arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
        }
    }
}

int main(int argc, char **argv)
{
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    bubbleSort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}
