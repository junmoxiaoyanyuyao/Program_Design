
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "delete.h"

RecycleBinEntry recycleBin[RECYCLE_BIN_SIZE]; // 回收站数组
int recycleBinIndex=0;

void Delete_guide(ListNode* head, ListNode* tailer) {
    printf("请选择想要执行的操作：1.删除学生信息 2.查看回收站 3.返回上级菜单 输入:");
    char choice[100];
    memset(choice, 0, sizeof(choice));
    s_gets(choice, 100);
    int flag1 = str_same_cmp(choice, "1");
    int flag2 = str_same_cmp(choice, "2");
    int flag3 = str_same_cmp(choice, "3");
    while (!flag1 && !flag2 && !flag3) {
        printf("非法输入，请重新输入！\n");
        Sleep(1000);
        system("cls");
        printf("请选择想要执行的操作：1.删除学生信息 2.查看回收站 3.返回上级菜单 输入:");
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        flag1 = str_same_cmp(choice, "1");
        flag2 = str_same_cmp(choice, "2");
        flag3 = str_same_cmp(choice, "3");
    }
    if (flag1) {
        delete_Information(head, tailer);
        return;
    }
    else if (flag2) {
        printRecycleBin(head, tailer);
        return;
    }
    else if (flag3) {
        return;
    }
}

void delete_Information(ListNode* head, ListNode* tailer) {
    printf("请输入要删除的学生学号(不能有空格):");
    char studentID[100];
    memset(studentID, 0, sizeof(studentID));
    s_gets(studentID, 100);
    if (!Input_check(studentID)) {
        return;
    }
    else {
        ListNode* p = head->next;
        while (p != tailer) {
            if (str_same_cmp(p->studentID, studentID)) {
                Print_stu_Information(p, 0, NULL, 0);
                printf("是否确认删除该学生信息？ 1.是 2.否 输入：");
                char choice[100];
                memset(choice, 0, sizeof(choice));
                s_gets(choice, 100);
                bool flag1 = str_same_cmp(choice, "1");
                bool flag2 = str_same_cmp(choice, "2");
                while (!flag1 && !flag2) {
                    printf("非法输入！\n");
                    printf("是否确认删除该学生信息？ 1.是 2.否 输入：");
                    memset(choice, 0, sizeof(choice));
                    s_gets(choice, 100);
                    flag1 = str_same_cmp(choice, "1");
                    flag2 = str_same_cmp(choice, "2");
                }
                if (flag1) {
                    recycleBin[recycleBinIndex].node = p;
                    recycleBin[recycleBinIndex].deletionTime = time(NULL);  // 记录删除时间
                    recycleBinIndex = (recycleBinIndex + 1) % RECYCLE_BIN_SIZE;

                    p->father->next = p->next;
                    p->next->father = p->father;
                    printf("已删除该学生信息！\n");
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else if (flag2) {
                    return;
                }
            }
            p = p->next;
        }
        printf("未找到该学生信息！\n");
        Sleep(1000);
        system("cls");
        return;
    }
}

void printRecycleBin() {
    printf("回收站内容：\n");
    for (int i = 0; i < RECYCLE_BIN_SIZE; i++) {
        if (recycleBin[i].node != NULL) {
            ListNode* p = recycleBin[i].node;
            printf("学号:%s    姓名:%s    学院:%s    平均绩点（加分前）:%.2f    平均绩点（加分后）:%.2f     删除时间:%s\n", p->studentID,
                p->studentName, p->studentFaculty, p->AverageGrade - p->AddQualityGrade, p->AverageGrade, ctime(&recycleBin[i].deletionTime));
        }
    }
    system("pause");
    system("cls");
}