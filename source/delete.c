
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

RecycleBinEntry recycleBin[RECYCLE_BIN_SIZE]; // ����վ����
int recycleBinIndex=0;

char courseType[5][20] = {
    "��������",
    "����ѡ��",
    "רҵ����",
    "רҵѡ��",
    "����"
};

void Delete_guide(ListNode* head, ListNode* tailer) {
    printf("��ѡ����Ҫִ�еĲ�����1.ɾ��ѧ��������Ϣ 2.ɾ��ѧ��������Ϣ 3.�鿴����վ 4.�����ϼ��˵� ����:");
    char choice[100];
    memset(choice, 0, sizeof(choice));
    s_gets(choice, 100);
    int flag1 = str_same_cmp(choice, "1");
    int flag2 = str_same_cmp(choice, "2");
    int flag3 = str_same_cmp(choice, "3");
    int flag4 = str_same_cmp(choice, "4");
    while (!flag1 && !flag2 && !flag3&&!flag4) {
        printf("�Ƿ����룬���������룡\n");
        Sleep(1000);
        system("cls");
        printf("��ѡ����Ҫִ�еĲ�����1.ɾ��ѧ��������Ϣ 2.ɾ��ѧ��������Ϣ 3.�鿴����վ 4.�����ϼ��˵� ����:");
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
    printf("������Ҫɾ����ѧ��ѧ��(�����пո�):");
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
                printf("�Ƿ�ȷ��ɾ����ѧ����Ϣ�� 1.�� 2.�� ���룺");
                char choice[100];
                memset(choice, 0, sizeof(choice));
                s_gets(choice, 100);
                bool flag1 = str_same_cmp(choice, "1");
                bool flag2 = str_same_cmp(choice, "2");
                while (!flag1 && !flag2) {
                    printf("�Ƿ����룡\n");
                    printf("�Ƿ�ȷ��ɾ����ѧ����Ϣ�� 1.�� 2.�� ���룺");
                    memset(choice, 0, sizeof(choice));
                    s_gets(choice, 100);
                    flag1 = str_same_cmp(choice, "1");
                    flag2 = str_same_cmp(choice, "2");
                }
                if (flag1) {
                    recycleBin[recycleBinIndex].node = p;
                    recycleBin[recycleBinIndex].deletionTime = time(NULL);  // ��¼ɾ��ʱ��
                    recycleBinIndex = (recycleBinIndex + 1) % RECYCLE_BIN_SIZE;

                    p->father->next = p->next;
                    p->next->father = p->father;
                    printf("��ɾ����ѧ����Ϣ��\n");
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
        printf("δ�ҵ���ѧ����Ϣ��\n");
        Sleep(2000);
        system("cls");
        return;
    }
}

void delete_factor(ListNode*head,ListNode*tailer){
    printf("������Ҫɾ����ѧ��ѧ��(�����пո�):");
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
                printf("��ѡ����Ҫɾ����ѧ����Ϣ���ݣ�1.�ɼ���Ϣ 2.���ʼӷ���Ϣ 3.�����ϼ��˵� ���룺");
                char choice[100];
                memset(choice, 0, sizeof(choice));
                s_gets(choice, 100);
                int flag1 = str_same_cmp(choice, "1");
                int flag2 = str_same_cmp(choice, "2");
                int flag3 = str_same_cmp(choice, "3");
                while (!flag1 && !flag2 && !flag3) {
                    printf("�Ƿ����룡\n");
                    printf("��ѡ����Ҫɾ����ѧ����Ϣ���ݣ�1.�ɼ���Ϣ 2.���ʼӷ���Ϣ 3.�����ϼ��˵� ���룺");
                    memset(choice, 0, sizeof(choice));
                    s_gets(choice, 100);
                    flag1 = str_same_cmp(choice, "1");
                    flag2 = str_same_cmp(choice, "2");
                    flag3 = str_same_cmp(choice, "3");
                }
                if(flag1){  
                        CourseGradeNode* c;
                        if(p->CourseNum == 0){
                            printf("�޳ɼ���Ϣ\n");
                            Sleep(2000);
                            return;
                        }
                        for(int i = 0;i < (p->CourseNum);i++){
                            c = p->gradeNode[i];
                            printf("%d\t",i + 1);
                            printf("�γ���:%s\t�γ̺�:%s\t�γ�����:%s\t",c->CourseName,c->CourseNum,courseType[c->gradeType]);
                            printf("ѧ��:%s\t�ɼ�:%s\t����:%s\n",c->CourseCredit,c->CourseGrade,c->GPA);
                        }
                        printf("��������ɾ�����ֵı��:");
                        int index;
                        // memset(index, 0, sizeof(index));
                        // s_gets(index, 100);
                        scanf("%d",&index);
                        getchar();
                        while(index < 1 || index > p->CourseNum){
                            printf("��ŷǷ�,��������:");
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
                        printf("ɾ���ɹ�\n");
                        Sleep(2000);
                        return;
                }
            else if(flag2){
                QualityGradeNode* q;
                thesis* t;
                project* P;
                contest* c;
                if(p->QualityGradeNum == 0){
                    printf("�����ʼӷ���Ϣ\n");
                    Sleep(2000);
                    return;
                }
                for(int i = 0;i < (p->QualityGradeNum);i++){
                    q = p->QGrade[i];
                    printf("%d\t",i + 1);
                    switch(q->QualityGradeType){
                        case THESIS :
                            t = q->Thesis;
                            printf("����\t������:%s\t����ʱ��:%d\n",t->thesisName,t->publicationTime);
                            break;
                        case PROJECT :
                            P = q->Project;
                            printf("��\t��Ա����:");
                            for(int j = 0;j < P->memberNum;j++)
                                printf("%s ",P->members[j]);
                            printf("\t��Ŀ��:%s\t��Ŀ���:%d\t����ʱ��:%d\t����ʱ��:%d\n",P->projrectName,P->itemNum,P->approvalTime,P->endTime);
                            break;
                        case CONTEST :
                            c = q->Contest;
                            printf("����\t������:%s\t���쵥λ:%s\t",c->contestName,c->organizer);
                            printf("������:");
                            for(int j = 0;c->winners[j][0] != '\0';j++)
                                printf("%s ",c->winners[j]);
                            printf("\t��ʱ��:%d\n",c->prizeTIme);
                            break;
                        default :
                            break;
                    }
                    }
                        printf("��������ɾ�����ֵı��:");
                        int index;
                        scanf("%d",&index);
                        getchar();
                        while(index < 1 || index > p->QualityGradeNum){
                            printf("��ŷǷ�,��������:");
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
                        printf("ɾ���ɹ�\n");
                        Sleep(2000);
                        return;
                }

                else if(flag3){
                    return;
                }
            }
        }
        printf("δ�ҵ���ѧ����Ϣ��\n");
        Sleep(2000);
        system("cls");
    }
    return;
}

void printRecycleBin() {
    printf("����վ���ݣ�\n");
    for (int i = 0; i < RECYCLE_BIN_SIZE; i++) {
        if (recycleBin[i].node != NULL) {
            ListNode* p = recycleBin[i].node;
            printf("ѧ��:%s    ����:%s    ѧԺ:%s    ƽ�����㣨�ӷ�ǰ��:%.2f    ƽ�����㣨�ӷֺ�:%.2f     ɾ��ʱ��:%s\n", p->studentID,
                p->studentName, p->studentFaculty, p->AverageGrade, p->AverageGrade + p->AddQualityGrade, ctime(&recycleBin[i].deletionTime));
        }
    }
    system("pause");
    system("cls");
}