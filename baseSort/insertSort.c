/* 插入排序
 *  
 *  
 *  最优时间复杂度: O(n2)
 *  平均时间复杂度: O(n)
 *  最差时间复杂度: O(n2)
 *     
 *  空间复杂度: O(1)
 *
 *  排序思想：
 *      1. 从第一个元素开始，该元素可以认为已经被排序
 *      2. 取出下一个元素，在已经排序的元素序列中从后向前扫描
 *      3. 如果该元素（已排序）大于新元素，将该元素移到下一位置
 *      4. 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
 *      5. 将新元素插入到该位置后
 *      6. 重复步骤2~5
 */   

#include "comm.h"

void insertionSort(int arr[], int len)
{
    if(!arr || len <= 1)
        return;
    
    int temp, script;
    for(int i = 1; i < len; ++i)
    {
        temp = arr[i];
        script = i - 1;
        for(; script >= 0 && arr[script] > temp; --script)
        {
            arr[script + 1] = arr[script];
        }
        arr[script + 1] = temp;
    }
}

int main(int argc, char **argv)
{
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    insertionSort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}
