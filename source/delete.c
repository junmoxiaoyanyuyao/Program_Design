
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

char courseType[5][20] = {
    "公共必修",
    "公共选修",
    "专业必修",
    "专业选修",
    "再修"
};

void Delete_guide(ListNode* head, ListNode* tailer) {
    printf("请选择想要执行的操作：1.删除学生整个信息 2.删除学生部分信息 3.查看回收站 4.返回上级菜单 输入:");
    char choice[100];
    memset(choice, 0, sizeof(choice));
    s_gets(choice, 100);
    int flag1 = str_same_cmp(choice, "1");
    int flag2 = str_same_cmp(choice, "2");
    int flag3 = str_same_cmp(choice, "3");
    int flag4 = str_same_cmp(choice, "4");
    while (!flag1 && !flag2 && !flag3&&!flag4) {
        printf("非法输入，请重新输入！\n");
        Sleep(1000);
        system("cls");
        printf("请选择想要执行的操作：1.删除学生整个信息 2.删除学生部分信息 3.查看回收站 4.返回上级菜单 输入:");
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        flag1 = str_same_cmp(choice, "1");
        flag2 = str_same_cmp(choice, "2");
        flag3 = str_same_cmp(choice, "3");
        flag4 = str_same_cmp(choice, "4");
    }
    if (flag1) {
        delete_Information(head, tailer);
        return;
    }
    else if(flag2){
        delete_factor(head,tailer);
        return;
    }
    else if (flag3) {
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
        Sleep(2000);
        system("cls");
        return;
    }
}

void delete_factor(ListNode*head,ListNode*tailer){
    printf("请输入要删除的学生学号(不能有空格):");
    char studentID[100];
    memset(studentID, 0, sizeof(studentID));
    s_gets(studentID, 100);
    if (!Input_check(studentID)) {
        return;
    }
    else{
        ListNode* p = head->next;
        while (p != tailer) {
            if (str_same_cmp(p->studentID, studentID)) {
                printf("请选择想要删除的学生信息内容：1.成绩信息 2.素质加分信息 3.返回上级菜单 输入：");
                char choice[100];
                memset(choice, 0, sizeof(choice));
                s_gets(choice, 100);
                int flag1 = str_same_cmp(choice, "1");
                int flag2 = str_same_cmp(choice, "2");
                int flag3 = str_same_cmp(choice, "3");
                while (!flag1 && !flag2 && !flag3) {
                    printf("非法输入！\n");
                    printf("请选择想要删除的学生信息内容：1.成绩信息 2.素质加分信息 3.返回上级菜单 输入：");
                    memset(choice, 0, sizeof(choice));
                    s_gets(choice, 100);
                    flag1 = str_same_cmp(choice, "1");
                    flag2 = str_same_cmp(choice, "2");
                    flag3 = str_same_cmp(choice, "3");
                }
                if(flag1){  
                        CourseGradeNode* c;
                        if(p->CourseNum == 0){
                            printf("无成绩信息\n");
                            Sleep(2000);
                            return;
                        }
                        for(int i = 0;i < (p->CourseNum);i++){
                            c = p->gradeNode[i];
                            printf("%d\t",i + 1);
                            printf("课程名:%s\t课程号:%s\t课程类型:%s\t",c->CourseName,c->CourseNum,courseType[c->gradeType]);
                            printf("学分:%s\t成绩:%s\t绩点:%s\n",c->CourseCredit,c->CourseGrade,c->GPA);
                        }
                        printf("请输入想删除部分的编号:");
                        int index;
                        // memset(index, 0, sizeof(index));
                        // s_gets(index, 100);
                        scanf("%d",&index);
                        getchar();
                        while(index < 1 || index > p->CourseNum){
                            printf("编号非法,重新输入:");
                            scanf("%d",&index);
                            getchar();
                        // memset(index, 0, sizeof(index));
                        // s_gets(index, 100);
                        }
                        c=p->gradeNode[index - 1];
                        for(int j=index;j < p->CourseNum;j++){
                            p->gradeNode[j-1]=p->gradeNode[j];
                        }
                        p->CourseNum--;
                        p->AverageGrade = UpdateGPA(p);
                        printf("删除成功\n");
                        Sleep(2000);
                        return;
                }
            else if(flag2){
                QualityGradeNode* q;
                thesis* t;
                project* P;
                contest* c;
                if(p->QualityGradeNum == 0){
                    printf("无素质加分信息\n");
                    Sleep(2000);
                    return;
                }
                for(int i = 0;i < (p->QualityGradeNum);i++){
                    q = p->QGrade[i];
                    printf("%d\t",i + 1);
                    switch(q->QualityGradeType){
                        case THESIS :
                            t = q->Thesis;
                            printf("论文\t论文名:%s\t出版时间:%d\n",t->thesisName,t->publicationTime);
                            break;
                        case PROJECT :
                            P = q->Project;
                            printf("大创\t人员名单:");
                            for(int j = 0;j < P->memberNum;j++)
                                printf("%s ",P->members[j]);
                            printf("\t项目名:%s\t项目编号:%d\t开题时间:%d\t结题时间:%d\n",P->projrectName,P->itemNum,P->approvalTime,P->endTime);
                            break;
                        case CONTEST :
                            c = q->Contest;
                            printf("竞赛\t竞赛名:%s\t主办单位:%s\t",c->contestName,c->organizer);
                            printf("获奖名单:");
                            for(int j = 0;c->winners[j][0] != '\0';j++)
                                printf("%s ",c->winners[j]);
                            printf("\t获奖时间:%d\n",c->prizeTIme);
                            break;
                        default :
                            break;
                    }
                    }
                        printf("请输入想删除部分的编号:");
                        int index;
                        scanf("%d",&index);
                        getchar();
                        while(index < 1 || index > p->QualityGradeNum){
                            printf("编号非法,重新输入:");
                            scanf("%d",&index);
                            getchar();
                        // memset(index, 0, sizeof(index));
                        // s_gets(index, 100);
                        }
                        q=p->QGrade[index - 1];
                        for(int j = index;j < p->QualityGradeNum;j++){
                            p->QGrade[j-1]=p->QGrade[j];
                        }
                        p->QualityGradeNum--;
                        p->AddQualityGrade = UpdataQualityGrade(p);
                        printf("删除成功\n");
                        Sleep(2000);
                        return;
                }

                else if(flag3){
                    return;
                }
            }
        }
        printf("未找到该学生信息！\n");
        Sleep(2000);
        system("cls");
    }
    return;
}

void printRecycleBin() {
    printf("回收站内容：\n");
    for (int i = 0; i < RECYCLE_BIN_SIZE; i++) {
        if (recycleBin[i].node != NULL) {
            ListNode* p = recycleBin[i].node;
            printf("学号:%s    姓名:%s    学院:%s    平均绩点（加分前）:%.2f    平均绩点（加分后）:%.2f     删除时间:%s\n", p->studentID,
                p->studentName, p->studentFaculty, p->AverageGrade, p->AverageGrade + p->AddQualityGrade, ctime(&recycleBin[i].deletionTime));
        }
    }
    system("pause");
    system("cls");
}