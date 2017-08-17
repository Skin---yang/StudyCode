/*
 * 选择排序
 *
 * 
 *  最优时间复杂度: O(n2)
 *  平均时间复杂度: O(n2)
 *  最差时间复杂度: O(n2)
 *   
 *  空间复杂度: O(1)
 *
 *
 * */

#include "comm.h"

void selectSort(int arr[], int len)
{
    if(!arr || len <= 1)
        return;
    
    int min; // min number
    for(int i = 0; i < len; ++i)
    {
        min = i;
        for(int j = i+1; j < len; ++j)
        {
            if(arr[min] > arr[j])
            {
                min = j;
            }
        }
        
        swap(&arr[min], &arr[i]);
    }
}

int main(int argc, char **argv)
{
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    selectSort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}
