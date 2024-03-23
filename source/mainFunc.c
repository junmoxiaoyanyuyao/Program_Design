#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>s

#include "definition.h"



void Insert(ListNode** preListEnd){
    printf("选择选项: 1.文件输入 2.手动单个输入 3.返回主菜单\n");
    printf("输入:");
    int a;
    while(scanf("%d",&a) && (a > 3 || a < 1)){
        printf("错误，请再次输入\n");
        printf("选择选项: 1.文件输入 2.手动单个输入 3.返回主菜单\n");
        printf("输入:");
    }
    
    switch(a){
        case 1 : fileInsert(preListEnd);
                    break;
        case 2 : singleInsert(preListEnd);
                    break;
        case 3 : return;
        default : printf("错误，自动返回主菜单\n");
                    return;
    }
}

