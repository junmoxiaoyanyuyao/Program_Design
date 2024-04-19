#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "inquire.h"

void Faculty_Search() {
    printf("******************************************************************************\n");
    printf("01 ��ѧ���\t\t 02 ��ѧ\t\t 03 �����\n");
    printf("04 ����\t\t\t 05 ����\t\t 06 ����\n");
    printf("07 ��\t\t\t 08 ����\t\t 09 ��ѧ�����\n");
    printf("10 ��ѧ\t\t\t 11 ����\t\t 12 ��ѧ\n");
    printf("13 ������ѧ\t\t 14 ��е�뺽�պ���\t 15 ��������\n");
    printf("16 ���Ͽ�ѧ�빤��\t 17 ��ͨ\t\t 18 ������ũҵ����\n");
    printf("19 ���ӿ�ѧ�빤��\t 20 ͨ�Ź���\t\t 21 �������ѧ�뼼��\n");
    printf("22 �����ѧ\t\t 23 ����̽���ѧ�뼼��\t 24 ���蹤��\n");
    printf("25 ��������Դ\t\t 26 ����\t\t 27 ��������\n");
    printf("28 ҩ\t\t\t 29 ����\t\t 30 ������\n");
    printf("33 ��ǻҽ\t\t 37 �����봫��\t\t 38 ����\n");
    printf("39 ���˼����\t\t 40 �˹�����\t\t 55 ���\n");
    printf("65 ������ѧ���������\t 70 �ٴ�ҽ\n");
    printf("81 ����ҽѧ\n");
    printf("******************************************************************************\n");
}

int compare_grade(const void* p1, const void* p2) {
    ListNode** a = (ListNode**)p1;
    ListNode** b = (ListNode**)p2;
    return (*a)->AverageGrade <= (*b)->AverageGrade;
}

void sort_cmp_grade(ListNode* head, ListNode* tailer,char faculty[30], int flag, FILE* fp) {//��flagΪ0ʱ����Ҫ�����ļ� ����Ҫ��ѧԺ���
    ListNode* p = head->next;                                           //��flagΪ1ʱ����Ҫ�����ļ� ��Ҫ��ѧԺ���
    int num = 0;                                                        //��flagΪ2ʱ��Ҫ�����ļ� ����Ҫ��ѧԺ���
    while (p != tailer) {                                               //��flagΪ3ʱ��Ҫ�����ļ� ��Ҫ��ѧԺ���
        num++;
        p = p->next;
    }
    if (num == 0) {
        printf("δ�洢ѧ����Ϣ��\n");
        return;
    }
    int sizeof_p_array = num + 10;
    ListNode** p_array = (ListNode**)malloc(sizeof(ListNode*) * sizeof_p_array);    //ָ������
    p = head->next;
    for (int i = 0; i < num; i++) {
        p_array[i] = p;
        p = p->next;
    }
    qsort(p_array, num, sizeof(ListNode*), compare_grade);
    for (int i = 0; i < num; i++) {
        if (flag == 0 && p_array[i]->CourseNum != 0){
            Print_stu_Information(p_array[i], 0, NULL,2);
        }
        else if (flag == 1) {
            if (str_same_cmp(p_array[i]->studentFaculty, faculty) && p_array[i]->CourseNum != 0){
                Print_stu_Information(p_array[i], 0, NULL,2);
            }
        }
        else if (flag == 2 && p_array[i]->CourseNum != 0){
            Print_stu_Information(p_array[i], 1, fp,2);
        }
        else if (flag == 3) {
            if (str_same_cmp(p_array[i]->studentFaculty, faculty) && p_array[i]->CourseNum != 0){
                Print_stu_Information(p_array[i], 1, fp,2);
            }
        }
    }
    free(p_array);
}

bool str_same_cmp(char* a, char* b) {
    int i = 0;
    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (a[i] != b[i])
            return false;
    }
    if (a[i] == '\0' && b[i] == '\0')
        return true;
    return false;
}


char* s_gets(char* st, int n) {
    char* ret_val;
    char* find;
    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        find = strchr(st, '\n');
        if (find) {
            *find = '\0';
        }
        else {
            while (getchar() != '\n')continue;
        }
    }
    return ret_val;
}
char* file_s_gets(char* st, int n, FILE* fp) {
    char* ret_val;
    char* find;
    ret_val = fgets(st, n, fp);
    if (ret_val) {
        find = strchr(st, '\n');
        if (find) {
            *find = '\0';
        }
        else {
            if (feof(fp)) return NULL;
            while (getchar() != '\n')continue;
        }
    }

    return ret_val;
}

void guide_information(ListNode* head, ListNode* tailer) {
    while (true) {
        char choice[100];
        printf("��ѡ����Ҫִ�еĹ���: 1.�ֶ���ѯ����ѧ����Ϣ 2.��ѯѧԺѧ����Ϣ 3.�ļ���ѯ 4.�������˵� ���룺"); //���ǿո�
        fflush(stdout);
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        bool flag1 = str_same_cmp(choice, "1");
        bool flag2 = str_same_cmp(choice, "2");
        bool flag3 = str_same_cmp(choice, "3");
        bool flag4 = str_same_cmp(choice, "4");
        while (!flag1 && !flag2 && !flag3 && !flag4) {
            printf("�Ƿ����룬���������룡\n");
            printf("��ѡ����Ҫִ�еĹ���: 1.�ֶ���ѯ����ѧ����Ϣ 2.��ѯѧԺѧ����Ϣ 3.�ļ���ѯ 4.�������˵� ���룺");
            fflush(stdout);
            memset(choice, 0, sizeof(choice));
            s_gets(choice, 100);
            flag1 = str_same_cmp(choice, "1");
            flag2 = str_same_cmp(choice, "2");
            flag3 = str_same_cmp(choice, "3");
            flag4 = str_same_cmp(choice, "4");
        }
        if (flag1) {
            single_Inquire(head, tailer);
            system("cls");
        }
        else if (flag2) {
            faculty_Inquire(head, tailer);
            system("cls");
        }
        else if (flag3) {
            file_Inquire(head, tailer);
            system("cls");
        }
        else if (flag4)return;
    }
}

bool Input_check(char studentID[100]) {
    while (true) {
        int flag = 0;
        if (studentID[8] != '\0')flag = 1;
        else {
            for (int i = 0; i < 8; i++) {
                if (studentID[i] < '0' || studentID[i]>'9') {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            printf("ѧ������Ƿ���\n");
            printf("��ѡ��: 1.��������ѧ�� 2.�������˵� ���룺");
            char a[100];
            memset(a, 0, sizeof(a));
            s_gets(a, 100);
            bool flag1 = str_same_cmp(a, "1");
            bool flag2 = str_same_cmp(a, "2");
            while (!flag1 && !flag2) {
                printf("�Ƿ����룡\n");
                printf("��ѡ��: 1.��������ѧ�� 2.�������˵� ���룺");
                memset(a, 0, sizeof(a));
                s_gets(a, 100);
                flag1 = str_same_cmp(a, "1");
                flag2 = str_same_cmp(a, "2");
            }
            if (flag2)return false;
            else {
                memset(studentID, 0, sizeof(a));
                printf("����ѧ��(�����пո�):");
                s_gets(studentID, 100);
            }
        }
        else return true;
    }
}

void Print_stu_Information(ListNode* p, int flag, FILE* fp, int isheader) {
    // ��ͷ��ʽ
    char* headerFormat = "%-10s\t%-15s\t%-20s\t%-20s\t%-20s\n";
    // �����и�ʽ
    char* dataFormat = "%-10s\t%-15s\t%-20s\t%-20.2f\t%-20.2f\n";

    if (isheader == 1) {
        if (flag == 0) printf(headerFormat, "ѧ��", "����", "ѧԺ", "ƽ�����㣨�ӷ�ǰ��", "ƽ�����㣨�ӷֺ�");
        if (flag == 1) fprintf(fp, headerFormat, "ѧ��", "����", "ѧԺ", "ƽ�����㣨�ӷ�ǰ��", "ƽ�����㣨�ӷֺ�");
    }

    if (isheader == 2) {
        if (flag == 0) printf(dataFormat, p->studentID, p->studentName, p->studentFaculty, p->AverageGrade - p->AddQualityGrade, p->AverageGrade);
        if (flag == 1) fprintf(fp, dataFormat, p->studentID, p->studentName, p->studentFaculty, p->AverageGrade - p->AddQualityGrade, p->AverageGrade);
    }
    if (isheader == 0) {
        if (flag == 0)printf("ѧ��:%s    ����:%s    ѧԺ:%s    ƽ�����㣨�ӷ�ǰ��:%.2f    ƽ�����㣨�ӷֺ�:%.2f\n", p->studentID,
            p->studentName, p->studentFaculty, p->AverageGrade,p->AverageGrade + p->AddQualityGrade);   //strtod�ַ���תdoubleҪ���ַ����ѺϷ�
        if (flag == 1)fprintf(fp, "ѧ��:%s    ����:%s    ѧԺ:%s    ƽ�����㣨�ӷ�ǰ��:%.2f    ƽ�����㣨�ӷֺ�:%.2f\n", p->studentID,
            p->studentName, p->studentFaculty, p->AverageGrade,p->AverageGrade + p->AddQualityGrade);
    }
}

void Print_stu_Grade(ListNode* p) {
    char coursetype[maxCourseNameSize];
    memset(coursetype, 0, sizeof(coursetype));
    for (int i = 0; i < p->CourseNum; i++) {
        if(p->gradeNode[i]->gradeType==0){//��������,����ѡ��,רҵ����,רҵѡ��,����
            strcpy(coursetype,"��������");
        }
        else if(p->gradeNode[i]->gradeType==1){
            strcpy(coursetype,"����ѡ��");
        }
        else if(p->gradeNode[i]->gradeType==2){
            strcpy(coursetype,"רҵ����");
        }
        else if(p->gradeNode[i]->gradeType==3){
            strcpy(coursetype,"רҵѡ��");
        }
        else if(p->gradeNode[i]->gradeType==4){
            strcpy(coursetype,"�ҿ�����");
        }
        printf("�γ�����%s\t\t�γ̺ţ�%s\t�γ����ʣ�%s\tѧ�֣�%s\t�ɼ���%s\t���㣺%s\n", p->gradeNode[i]->CourseName, p->gradeNode[i]->CourseNum, coursetype, p->gradeNode[i]->CourseCredit, p->gradeNode[i]->CourseGrade,p->gradeNode[i]->GPA);
    }
}

void Print_stu_credit(ListNode* p) {
    for (int i = 0; i < p->QualityGradeNum; i++) {
        if (p->QGrade[i]->QualityGradeType == THESIS) {
            printf("��������:%s ����ʱ��:%d ���ĵȼ�:%d �ڿ�����:%s ", p->QGrade[i]->Thesis->thesisName, p->QGrade[i]->Thesis->publicationTime, p->QGrade[i]->Thesis->Grade, p->QGrade[i]->Thesis->journalName);
        }
        else if (p->QGrade[i]->QualityGradeType == PROJECT) {
            printf("��Ŀ��:%s ��Ŀ���:%d ����ʱ��:%d ����ʱ��:%d ", p->QGrade[i]->Project->projrectName, p->QGrade[i]->Project->itemNum, p->QGrade[i]->Project->approvalTime, p->QGrade[i]->Project->endTime);
        }
        else if (p->QGrade[i]->QualityGradeType == CONTEST) {
            printf("������:%s ���쵥λ:%s �����ȼ�:%d ��ʱ��:%d ", p->QGrade[i]->Contest->contestName, p->QGrade[i]->Contest->organizer, p->QGrade[i]->Contest->conG, p->QGrade[i]->Contest->prizeTIme);
        }
        printf("�϶��ӷ�:%.2lf\n",p->QGrade[i]->recognizedCredit);
    }
}

void single_Inquire(ListNode* head, ListNode* tailar) {
    char studentID[100];
    printf("��������Ҫ��ѯ��ѧ��ѧ��(�����пո�):");
    s_gets(studentID, 100);
    if (!Input_check(studentID)) {
        return;
    }
    else {
        ListNode* p = head->next;
        while (p != tailar) {
            if (str_same_cmp(p->studentID, studentID)) {
                // if(p->CourseNum==0||p->AverageGrade==0.0){
                //     printf("��ѧ����Ϣ��ȫ�������������Ϣ���ڲ�ѯ��\n");
                //     Sleep(1000);
                //     return;
                // }
                while (true) {
                    printf("��������Ҫ��ѯ������:1.ѧ������ѧ����Ϣ 2.ѧ����ϸ�ɼ���Ϣ 3.ѧ����ϸ���ʼӷ���Ϣ 4.�������˵� ���룺");
                    char choice[100];
                    memset(choice, 0, sizeof(choice));
                    s_gets(choice, 100);
                    bool flag1 = str_same_cmp(choice, "1");
                    bool flag2 = str_same_cmp(choice, "2");
                    bool flag3 = str_same_cmp(choice, "3");
                    bool flag4 = str_same_cmp(choice, "4");
                    while (!flag1 && !flag2 && !flag3 && !flag4) {
                        printf("�Ƿ����룡\n");
                        printf("��������Ҫ��ѯ������:1.ѧ������ѧ����Ϣ 2.ѧ����ϸ�ɼ���Ϣ 3.ѧ����ϸ���ʼӷ���Ϣ 4.�������˵� ���룺");
                        memset(choice, 0, sizeof(choice));
                        s_gets(choice, 100);
                        flag1 = str_same_cmp(choice, "1");
                        flag2 = str_same_cmp(choice, "2");
                        flag3 = str_same_cmp(choice, "3");
                        flag4 = str_same_cmp(choice, "4");
                    }
                    if (flag1) {
                        if(p->CourseNum == 0){
                            printf("��ѧ����Ϣ��ȫ�������������Ϣ���ڲ�ѯ��\n");
                            system("pause");
                        }
                        else{
                            Print_stu_Information(p, 0, NULL,0);
                            system("pause");
                        }
                    }
                    else if (flag2) {
                        if(p->CourseNum==0){
                            printf("��ѧ��û�пγ���Ϣ��\n");
                            system("pause");
                        }
                        else{
                        printf("ѧ��:%s ����:%s ѧԺ��%s ƽ������:%.2lf\n", p->studentID, p->studentName, p->studentFaculty, p->AverageGrade);
                        printf("ѧ���ɼ�������Ϣ��\n");
                        Print_stu_Grade(p);
                        system("pause");
                        }
                    }
                    else if (flag3) {
                        if (p->QualityGradeNum == 0) {
                            printf("��ѧ��û�����ʼӷ���Ϣ��\n");
                            system("pause");
                        }
                        else {
                            printf("ѧ��:%s ����:%s ѧԺ��%s ���ʼӷ�:%.2f\n", p->studentID, p->studentName, p->studentFaculty, p->AddQualityGrade);
                            printf("ѧ�����ʼӷ־�����Ϣ��\n");
                            Print_stu_credit(p);
                            system("pause");
                        }
                    }
                    else if (flag4) {
                        return;
                    }
                }
            }
            p = p->next;
        }
        printf("δ�ҵ���ѧ����Ϣ��\n");
        system("pause");
        return;
    }
}

void faculty_Inquire(ListNode* head, ListNode* tailer) {
    Faculty_Search();
    printf("��������Ҫ��ѯ��ѧԺ���(�����пո�):");       //��Ҫ�����Ƿ�Ϸ�
    char number[100];
    memset(number, 0, sizeof(number));
    s_gets(number, 100);
    int flag = 0;
    if (number[2] != '\0')flag = 1;
    else if (number[0] < '0' || number[0]>'9' || number[1] < '0' || number[1]>'9')flag = 1;
    while (flag) {
        printf("�������Ƿ���\n");
        printf("��������Ҫ��ѯ��ѧԺ���(�����пո�):");
        memset(number, 0, sizeof(number));
        s_gets(number, 100);
        flag = 0;
        if (number[2] != '\0')flag = 1;
        else if (number[0] < '0' || number[0]>'9' || number[1] < '0' || number[1]>'9')flag = 1;
    }
    ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
    matchFacultyName_one(number, temp);
    char faculty[maxNameFaculty];
    strcpy(faculty, temp->studentFaculty);
    int num = 0;
    ListNode* p = head->next;
    while (p != tailer) {
        if (str_same_cmp(p->studentFaculty, faculty)) {
            num++;
        }
        p = p->next;
    }
    if (num == 0) {
        printf("δ�ҵ���ѧԺѧ����Ϣ��\n");
        system("pause");
        return;
    }
    else {
        printf("ѡ������ʽ 1.ѧ��Ĭ��˳�� 2.�ӷֺ󼨵�ߵ�˳�� 3.�������˵� ���룺");
        char choice[100];
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        bool flag1 = str_same_cmp(choice, "1");
        bool flag2 = str_same_cmp(choice, "2");
        bool flag3 = str_same_cmp(choice, "3");
        while (!flag1 && !flag2 && !flag3) {
            printf("�Ƿ����룡\n");
            printf("ѡ������ʽ 1.ѧ��Ĭ��˳�� 2.�ӷֺ󼨵�ߵ�˳�� 3.�������˵� ���룺");
            memset(choice, 0, sizeof(choice));
            s_gets(choice, 100);
            flag1 = str_same_cmp(choice, "1");
            flag2 = str_same_cmp(choice, "2");
            flag3 = str_same_cmp(choice, "3");
        }
        if (flag3)return;
        printf("�Ƿ���Ҫ��������д���ļ��� 1.�� 2.�� ���룺");
        memset(choice, 0, 100);
        s_gets(choice, 100);
        bool flag4 = str_same_cmp(choice, "1");
        bool flag5 = str_same_cmp(choice, "2");
        while (!flag4 && !flag5) {
            printf("�Ƿ����룡\n");
            printf("�Ƿ���Ҫ��������д���ļ��� 1.�� 2.�� ���룺");
            memset(choice, 0, sizeof(choice));
            s_gets(choice, 100);
            flag4 = str_same_cmp(choice, "1");
            flag5 = str_same_cmp(choice, "2");
        }
        if (flag4) {
            FILE* fp;
            char filename[1000];
            memset(filename,0,sizeof(filename));
            strcpy(filename, faculty);
            strcat(filename, ".txt");
            char name[100] = "D:\\data\\vscode\\Program_Design\\build\\faculty_search.txt";
            fp = fopen(name, "w");
            if (fp == NULL) {
                printf("���ļ�ʧ�ܣ�\n");
                system("pause");
                return;
            }
            ListNode* p = head->next;
            if (flag1) {
                fprintf(fp,"%sѧԺѧ��������Ϣ:\n", faculty);
                Print_stu_Information(p, 1, fp, 1);
                while (p != tailer) {
                    if (str_same_cmp(p->studentFaculty, faculty) && p->CourseNum != 0) {
                        Print_stu_Information(p, 1, fp,2);
                    }
                    p = p->next;
                }
            }
            else if (flag2) {
                fprintf(fp,"%sѧԺѧ��������Ϣ:\n", faculty);
                Print_stu_Information(p, 1, fp, 1);
                sort_cmp_grade(head, tailer, faculty, 3, fp);
            }
            printf("ѧ����Ϣ��д�뵽'faculty_search.txt'�ļ�(Դ�ļ�Ŀ¼��)\n");
            fclose(fp);
            system("pause");
        }
        else {
            printf("%sѧԺѧ��������Ϣ:\n", faculty);
            Print_stu_Information(p, 0, NULL, 1);
            if (flag1) {
                ListNode* p = head->next;
                while (p != tailer) {
                    if (str_same_cmp(p->studentFaculty, faculty) && p->CourseNum != 0){
                        Print_stu_Information(p, 0, NULL,2);
                    }
                    p = p->next;
                }
            }
            else if (flag2) {
                sort_cmp_grade(head, tailer, faculty, 1, NULL);
            }
            system("pause");
        }
    }
}

void file_Inquire(ListNode* head, ListNode* tailer) {
    printf("�뽫��Ҫ��ѯ��ѧ��ѧ��д���ļ���\n");
    printf("Ҫ��ÿ��һ��ѧ�ţ�ÿ����ѧ�ż���һ���س��ָ��������пո�\n");
    printf("����ѯ����Ϊ1000�������������޷���ѯ��\n");
    printf("���һ��ѧ���������������س�����\n");
    printf("\n");
    printf("�������ļ�·��(·�����Բ�Ҫ��˫���ţ�):");
    char filepath[1000];
    memset(filepath, 0, sizeof(filepath));
    s_gets(filepath, 1000);
    FILE* fp;
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("���ļ�ʧ�ܣ�\n");
        system("pause");
        return;
    }
    printf("ѡ������ʽ 1.��ѯĬ��˳�� 2.�ӷֺ󼨵�ߵ�˳�� 3.�������˵�\n");
    printf("���ѣ���ѡ��ڶ��ַ�ʽ������ļ��в����в�ѯ��������Ϣ��\n");
    printf("����ѡ��");
    char choice[100];
    memset(choice, 0, sizeof(choice));
    s_gets(choice, 100);
    bool flag1 = str_same_cmp(choice, "1");
    bool flag2 = str_same_cmp(choice, "2");
    bool flag3 = str_same_cmp(choice, "3");
    while (!flag1 && !flag2 && !flag3) {
        printf("�Ƿ����룡\n");
        printf("ѡ������ʽ 1.��ѯĬ��˳�� 2.�ӷֺ󼨵�ߵ�˳�� 3.�������˵�\n");
        printf("���ѣ���ѡ��ڶ��ַ�ʽ������ļ��в����в�ѯ��������Ϣ��\n");
        printf("����ѡ��");
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        flag1 = str_same_cmp(choice, "1");
        flag2 = str_same_cmp(choice, "2");
        flag3 = str_same_cmp(choice, "3");
    }
    if (flag3)return;
    char studentID[1010][100];
    memset(studentID, 0, sizeof(studentID));
    int i = 0;
    while (file_s_gets(studentID[i], 100, fp) != NULL) {
        if (studentID[i][8] != '\0') {
            printf("�ļ���ѧ��������ļ���ʽ�Ƿ���\n");
            printf("������ļ����ݻ��ʽ���ٳ���\n");
            fclose(fp);
            system("pause");
            return;
        }
        for (int j = 0; j < 8; j++) {
            if (studentID[i][j] < '0' || studentID[i][j]>'9') {
                printf("�ļ���ѧ��������ļ���ʽ�Ƿ���\n");
                printf("������ļ����ݻ��ʽ���ٳ���\n");
                fclose(fp);
                system("pause");
                return;
            }
        }
        i++;
    }
    int num = i;
    if (i == 0) {
        printf("�ļ��в����в�ѯ��Ϣ��\n");
        fclose(fp);
        system("pause");
        return;
    }
    i = 0;
    FILE* fp1;
    fp1 = fopen("result.txt", "w");
    if (fp1 == NULL) {
        printf("����ļ���ʧ�ܣ�\n");
        fclose(fp);
        system("pause");
        return;
    }
    int flag = 0;
    int k = 1;
    if(flag1){
        while (!str_same_cmp(studentID[i], "")) {
            ListNode* p = head->next;
            while (p != tailer) {
                if (str_same_cmp(p->studentID, studentID[i])) {
                    fprintf(fp1,"��%d����ѯ�����", k);
                    if(p->CourseNum == 0){
                        fprintf(fp1,"��ѧ����Ϣ��ȫ\n");
                        k++;
                        flag = 1;
                        p = p->next;
                        break;
                    }
                    k++;
                    Print_stu_Information(p, 1, fp1,0);
                    flag = 1;
                    break;
                }
                p = p->next;
            }
            if (!flag) {
                fprintf(fp1,"��%d����ѯ�����", k);
                k++;
                fprintf(fp1, "δ�ҵ���ѧ����Ϣ��\n");
            }
            flag = 0;
            i++;
        }
    }
    else if (flag2) {
        num += 10;
        ListNode** p_array = (ListNode**)malloc(sizeof(ListNode*) * num);
        num -= 10;
        ListNode* p = head->next;
        int k = 0;
        int if_save = 0;
        for (int i = 0; i < num; i++) {
            p = head->next;
            while (p != tailer) {
                if (str_same_cmp(studentID[i], p->studentID)) {
                    if_save = 0;
                    for (int j = 0; j < k; j++) {
                        if (str_same_cmp(p_array[j]->studentID, studentID[i])) {
                            if_save = 1;
                            break;
                        }
                    }
                    if (!if_save){
                        p_array[k++] = p;
                        break;
                    }
                }
                p = p->next;
            }
        }
        if (k == 0) {
            printf("δ��ѯ���κ���Ϣ��\n");
            free(p_array);
            fclose(fp1);
            fclose(fp);
            system("pause");
            return;
        }
        qsort(p_array, k, sizeof(ListNode*), compare_grade);
        Print_stu_Information(p, 1, fp1, 1);
        for (int i = 0; i < k; i++) {
            if(p->CourseNum == 0)
                continue;
            Print_stu_Information(p_array[i], 1, fp1,2);
        }
        free(p_array);
    }
    printf("��ѯ��ϣ�����������'result.txt'�ļ�(Դ�ļ�Ŀ¼��)\n");
    fclose(fp1);
    fclose(fp);
    system("pause");
    return;
}



// int main() {
//     ListNode* head = malloc(sizeof(ListNode)); //����ͷ�ڵ�
//     ListNode* tailer = malloc(sizeof(ListNode)); //����β���
//     head->next = tailer;
//     tailer->father = head;
//     ListNode* currentNode = head;
//     for (int i = 0; i < 3; ++i) {
//         // �����½��
//         ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
//         newNode->next = NULL;
//         newNode->father = NULL;
//         scanf("%s", newNode->studentID);
//         getchar();
//         scanf("%s", newNode->studentName);
//         getchar();
//         scanf("%lf", &newNode->AverageGrade);
//         getchar();
//         scanf("%lf", &newNode->AddQualityGrade);
//         getchar();
//         ListNode* temp = head;
//         while (temp->next != tailer) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//         newNode->next = tailer;
//         tailer->father = newNode;
//     }
//     Hello(head, tailer);
//     return 0;
// }