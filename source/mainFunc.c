#pragma execution_character_set("utf-8")  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#include "definition.h"
#include "Insert.h"
#include "Modify.h"
#include "Output.h"
#include "inquire.h"
#include "delete.h"
#include "login.h"


void Menu() {
    ListNode* head = malloc(sizeof(ListNode)); //链表头节点
    ListNode* tailer = malloc(sizeof(ListNode)); //链表尾结点
    head->next = tailer;
    tailer->father = head;
    ListNode* currentNode = head;
    while (true) {
        fflush(stdin);
        // syetem("cls");
            printf("********************************************\n");
            printf("*********** 学生成绩信息管理系统 ***********\n");
            printf("********************************************\n\n");
            printf("\t1. 插入学生信息\n");
            printf("\t2. 导入加分细则\n");
            printf("\t3. 修改学生信息\n");
            printf("\t4. 导出学生信息\n");
            printf("\t5. 查询学生信息\n");
            printf("\t6. 删除学生信息\n");
            printf("\t7. 转专业信息修改\n");
            printf("\t8. 退出登录\n\n");
            printf("********************************************\n");
            printf("请选择操作：");

        char choice[100];
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        int flag1 = str_same_cmp(choice, "1");
        int flag2 = str_same_cmp(choice, "2");
        int flag3 = str_same_cmp(choice, "3");
        int flag4 = str_same_cmp(choice, "4");
        int flag5 = str_same_cmp(choice, "5");
        int flag6 = str_same_cmp(choice, "6");
        int flag7 = str_same_cmp(choice, "7");
        int flag8 = str_same_cmp(choice, "8");
        while (!flag1 && !flag2 && !flag3 && !flag4 && !flag5&&!flag6&&!flag7&&!flag8) {
            printf("非法输入，请重新输入！\n");
            Sleep(1000);
            // syetem("cls");
            printf("********************************************\n");
            printf("*********** 学生成绩信息管理系统 ***********\n");
            printf("********************************************\n\n");
            printf("\t1. 插入学生信息\n");
            printf("\t2. 导入加分细则\n");
            printf("\t3. 修改学生信息\n");
            printf("\t4. 导出学生信息\n");
            printf("\t5. 查询学生信息\n");
            printf("\t6. 删除学生信息\n");
            printf("\t7. 转专业信息修改\n");
            printf("\t8. 退出登录\n\n");
            printf("********************************************\n");
            printf("请选择操作：");
            memset(choice, 0, sizeof(choice));
            s_gets(choice, 100);
            flag1 = str_same_cmp(choice, "1");
            flag2 = str_same_cmp(choice, "2");
            flag3 = str_same_cmp(choice, "3");
            flag4 = str_same_cmp(choice, "4");
            flag5 = str_same_cmp(choice, "5");
            flag6 = str_same_cmp(choice, "6");
            flag7 = str_same_cmp(choice, "7");
            flag8 = str_same_cmp(choice, "8");

        }
        if (flag1) {
            Insert(head,tailer,&currentNode);
            matchFacultyName_list(head, tailer);
             int c;
             while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if(flag2){
             QualityGradeInput(head,tailer);
              int c;
              while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if (flag3) {
            // matchFacultyName_list(head, tailer);
            Modify(head,tailer);
             int c;
             while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if (flag4) {
            // matchFacultyName_list(head, tailer);
            Output(head,tailer);
             int c;
             while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if (flag5) {
            // matchFacultyName_list(head, tailer);
            guide_information(head, tailer);
        }
        else if (flag6) {
            // matchFacultyName_list(head, tailer);
            Delete_guide(head, tailer);
        }
        else if (flag7) {
            // matchFacultyName_list(head, tailer);
            changeFaculty(head, tailer);
        }
        else if (flag8) {
            printf("退出登录成功！\n");
            Sleep(1000);
            return;
        }
    }
}

