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
    printf("01 哲学社会\t\t 02 文学\t\t 03 外国语\n");
    printf("04 艺术\t\t\t 05 体育\t\t 06 经济\n");
    printf("07 法\t\t\t 08 行政\t\t 09 商学与管理\n");
    printf("10 数学\t\t\t 11 物理\t\t 12 化学\n");
    printf("13 生命科学\t\t 14 机械与航空航天\t 15 汽车工程\n");
    printf("16 材料科学与工程\t 17 交通\t\t 18 生物与农业工程\n");
    printf("19 电子科学与工程\t 20 通信工程\t\t 21 计算机科学与技术\n");
    printf("22 地球科学\t\t 23 地球探测科学与技术\t 24 建设工程\n");
    printf("25 环境与资源\t\t 26 金融\t\t 27 公共卫生\n");
    printf("28 药\t\t\t 29 护理\t\t 30 东北亚\n");
    printf("33 口腔医\t\t 37 新闻与传播\t\t 38 考古\n");
    printf("39 马克思主义\t\t 40 人工智能\t\t 55 软件\n");
    printf("65 仪器科学与电气工程\t 70 临床医\n");
    printf("81 动物医学\n");
    printf("******************************************************************************\n");
}

int compare_grade(const void* p1, const void* p2) {
    ListNode** a = (ListNode**)p1;
    ListNode** b = (ListNode**)p2;
    return (*a)->AverageGrade <= (*b)->AverageGrade;
}

void sort_cmp_grade(ListNode* head, ListNode* tailer,char faculty[30], int flag, FILE* fp) {//当flag为0时不需要输入文件 不需要按学院输出
    ListNode* p = head->next;                                           //当flag为1时不需要输入文件 需要按学院输出
    int num = 0;                                                        //当flag为2时需要输入文件 不需要按学院输出
    while (p != tailer) {                                               //当flag为3时需要输入文件 需要按学院输出
        num++;
        p = p->next;
    }
    if (num == 0) {
        printf("未存储学生信息！\n");
        return;
    }
    int sizeof_p_array = num + 10;
    ListNode** p_array = (ListNode**)malloc(sizeof(ListNode*) * sizeof_p_array);    //指针数组
    p = head->next;
    for (int i = 0; i < num; i++) {
        p_array[i] = p;
        p = p->next;
    }
    qsort(p_array, num, sizeof(ListNode*), compare_grade);
    for (int i = 0; i < num; i++) {
        if (flag == 0)Print_stu_Information(p_array[i], 0, NULL,2);
        else if (flag == 1) {
            if (str_same_cmp(p_array[i]->studentFaculty, faculty))Print_stu_Information(p_array[i], 0, NULL,2);
        }
        else if (flag == 2)Print_stu_Information(p_array[i], 1, fp,2);
        else if (flag == 3) {
            if (str_same_cmp(p_array[i]->studentFaculty, faculty))Print_stu_Information(p_array[i], 1, fp,2);
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
            // if (feof(fp))return;
            while (getchar() != '\n')continue;
        }
    }

    return ret_val;
}

void guide_information(ListNode* head, ListNode* tailer) {
    while (true) {
        char choice[100];
        printf("请选择需要执行的功能: 1.手动查询单个学生信息 2.查询学院学生信息 3.文件查询 4.返回主菜单 输入："); //考虑空格
        fflush(stdout);
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        bool flag1 = str_same_cmp(choice, "1");
        bool flag2 = str_same_cmp(choice, "2");
        bool flag3 = str_same_cmp(choice, "3");
        bool flag4 = str_same_cmp(choice, "4");
        while (!flag1 && !flag2 && !flag3 && !flag4) {
            printf("非法输入，请重新输入！\n");
            printf("请选择需要执行的功能: 1.手动查询单个学生信息 2.查询学院学生信息 3.文件查询 4.返回主菜单 输入：");
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
            system("pause");
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
            printf("学号输入非法！\n");
            printf("请选择: 1.重新输入学号 2.返回主菜单 输入：");
            char a[100];
            memset(a, 0, sizeof(a));
            s_gets(a, 100);
            bool flag1 = str_same_cmp(a, "1");
            bool flag2 = str_same_cmp(a, "2");
            while (!flag1 && !flag2) {
                printf("非法输入！\n");
                printf("请选择: 1.重新输入学号 2.返回主菜单 输入：");
                memset(a, 0, sizeof(a));
                s_gets(a, 100);
                flag1 = str_same_cmp(a, "1");
                flag2 = str_same_cmp(a, "2");
            }
            if (flag2)return false;
            else {
                memset(studentID, 0, sizeof(a));
                printf("输入学号(不能有空格):");
                s_gets(studentID, 100);
            }
        }
        else return true;
    }
}

void Print_stu_Information(ListNode* p, int flag, FILE* fp, int isheader) {
    // 表头格式
    char* headerFormat = "%-10s\t%-15s\t%-20s\t%-20s\t%-20s\n";
    // 数据行格式
    char* dataFormat = "%-10s\t%-15s\t%-20s\t%-20.2f\t%-20.2f\n";

    if (isheader == 1) {
        if (flag == 0) printf(headerFormat, "学号", "姓名", "学院", "平均绩点（加分前）", "平均绩点（加分后）");
        if (flag == 1) fprintf(fp, headerFormat, "学号", "姓名", "学院", "平均绩点（加分前）", "平均绩点（加分后）");
    }

    if (isheader == 2) {
        if (flag == 0) printf(dataFormat, p->studentID, p->studentName, p->studentFaculty, p->AverageGrade, p->AverageGrade + p->AddQualityGrade);
        if (flag == 1) fprintf(fp, dataFormat, p->studentID, p->studentName, p->studentFaculty, p->AverageGrade, p->AverageGrade  + p->AddQualityGrade);
    }
    if (isheader == 0) {
        if (flag == 0)printf("学号:%s    姓名:%s    学院:%s    平均绩点（加分前）:%.2f    平均绩点（加分后）:%.2f\n", p->studentID,
            p->studentName, p->studentFaculty, p->AverageGrade, p->AverageGrade + p->AddQualityGrade);   //strtod字符串转double要求字符串已合法
        if (flag == 1)fprintf(fp, "学号:%s    姓名:%s    学院:%s    平均绩点（加分前）:%.2f    平均绩点（加分后）:%.2f\n", p->studentID,
            p->studentName, p->studentFaculty, p->AverageGrade, p->AverageGrade  + p->AddQualityGrade);
    }
}

void Print_stu_Grade(ListNode* p) {
    char coursetype[maxCourseNameSize];
    memset(coursetype, 0, sizeof(coursetype));
    for (int i = 0; i < p->CourseNum; i++) {
        if(p->gradeNode[i]->gradeType==0){//公共必修,公共选修,专业必修,专业选修,再修
            strcpy(coursetype,"公共必修");
        }
        else if(p->gradeNode[i]->gradeType==1){
            strcpy(coursetype,"公共选修");
        }
        else if(p->gradeNode[i]->gradeType==2){
            strcpy(coursetype,"专业必修");
        }
        else if(p->gradeNode[i]->gradeType==3){
            strcpy(coursetype,"专业选修");
        }
        else if(p->gradeNode[i]->gradeType==4){
            strcpy(coursetype,"再修");
        }
        printf("课程名：%s\t课程号：%s\t课程性质：%s\t学分：%s\t成绩：%s\t绩点：%s\n", p->gradeNode[i]->CourseName, p->gradeNode[i]->CourseNum, coursetype, p->gradeNode[i]->CourseCredit, p->gradeNode[i]->CourseGrade,p->gradeNode[i]->GPA);
    }
}

void Print_stu_credit(ListNode* p) {
    for (int i = 0; i < p->QualityGradeNum; i++) {
        if (p->QGrade[i]->QualityGradeType == THESIS) {
            printf("论文名称:%s 出版时间:%d 论文等级:%d 期刊名称:%s\n", p->QGrade[i]->Thesis->thesisName, p->QGrade[i]->Thesis->publicationTime, p->QGrade[i]->Thesis->Grade, p->QGrade[i]->Thesis->journalName);
        }
        else if (p->QGrade[i]->QualityGradeType == PROJECT) {
            printf("项目名:%s 项目编号:%d 开题时间:%d 结题时间:%d\n", p->QGrade[i]->Project->projrectName, p->QGrade[i]->Project->itemNum, p->QGrade[i]->Project->approvalTime, p->QGrade[i]->Project->endTime);
        }
        else if (p->QGrade[i]->QualityGradeType == CONTEST) {
            printf("竞赛名:%s 主办单位:%s 竞赛等级:%d 获奖时间:%d\n", p->QGrade[i]->Contest->contestName, p->QGrade[i]->Contest->organizer, p->QGrade[i]->Contest->conG, p->QGrade[i]->Contest->prizeTIme);
        }
    }
}

void single_Inquire(ListNode* head, ListNode* tailar) {
    char studentID[100];
    printf("请输入你要查询的学生学号(不能有空格):");
    s_gets(studentID, 100);
    if (!Input_check(studentID)) {
        return;
    }
    else {
        ListNode* p = head->next;
        while (p != tailar) {
            if (str_same_cmp(p->studentID, studentID)) {
                while (true) {
                    printf("请输入想要查询的内容:1.学生基本学生信息 2.学生详细成绩信息 3.学生详细素质加分信息 4.返回主菜单 输入：");
                    char choice[100];
                    memset(choice, 0, sizeof(choice));
                    s_gets(choice, 100);
                    bool flag1 = str_same_cmp(choice, "1");
                    bool flag2 = str_same_cmp(choice, "2");
                    bool flag3 = str_same_cmp(choice, "3");
                    bool flag4 = str_same_cmp(choice, "4");
                    while (!flag1 && !flag2 && !flag3 && !flag4) {
                        printf("非法输入！\n");
                        printf("请输入想要查询的内容:1.学生基本学生信息 2.学生详细成绩信息 3.学生详细素质加分信息 4.返回主菜单 输入：");
                        memset(choice, 0, sizeof(choice));
                        s_gets(choice, 100);
                        flag1 = str_same_cmp(choice, "1");
                        flag2 = str_same_cmp(choice, "2");
                        flag3 = str_same_cmp(choice, "3");
                        flag4 = str_same_cmp(choice, "4");
                    }
                    if (flag1) {
                        Print_stu_Information(p, 0, NULL,0);
                        
                    }
                    else if (flag2) {
                        printf("学号:%s 姓名:%s 学院：%s 平均绩点:%.2lf\n", p->studentID, p->studentName, p->studentFaculty, p->AverageGrade);
                        printf("学生成绩具体信息：\n");
                        Print_stu_Grade(p);
                    }
                    else if (flag3) {
                        if (p->QualityGradeNum == 0) {
                            printf("该学生没有素质加分信息！\n");
                        }
                        else {
                            printf("学号:%s 姓名:%s 学院：%s 素质加分:%.2f\n", p->studentID, p->studentName, p->studentFaculty, p->AddQualityGrade);
                            printf("学生素质加分具体信息：\n");
                            Print_stu_credit(p);
                        }
                    }
                    else if (flag4) {
                        return;
                    }
                }
            }
            p = p->next;
        }
        printf("未找到该学生信息！\n");
        return;
    }
}

void faculty_Inquire(ListNode* head, ListNode* tailer) {
    Faculty_Search();
    printf("请输入你要查询的学院编号(不能有空格):");       //需要考虑是否合法
    char number[100];
    memset(number, 0, sizeof(number));
    s_gets(number, 100);
    int flag = 0;
    if (number[2] != '\0')flag = 1;
    else if (number[0] < '0' || number[0]>'9' || number[1] < '0' || number[1]>'9')flag = 1;
    while (flag) {
        printf("编号输入非法！\n");
        printf("请输入你要查询的学院编号(不能有空格):");
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
        printf("未找到该学院学生信息！\n");
        return;
    }
    else {
        printf("选择排序方式 1.学号默认顺序 2.加分后绩点高低顺序 3.返回主菜单 输入：");
        char choice[100];
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        bool flag1 = str_same_cmp(choice, "1");
        bool flag2 = str_same_cmp(choice, "2");
        bool flag3 = str_same_cmp(choice, "3");
        while (!flag1 && !flag2 && !flag3) {
            printf("非法输入！\n");
            printf("选择排序方式 1.学号默认顺序 2.加分后绩点高低顺序 3.返回主菜单 输入：");
            memset(choice, 0, sizeof(choice));
            s_gets(choice, 100);
            flag1 = str_same_cmp(choice, "1");
            flag2 = str_same_cmp(choice, "2");
            flag3 = str_same_cmp(choice, "3");
        }
        if (flag3)return;
        printf("是否需要将输出结果写入文件？ 1.是 2.否 输入：");
        memset(choice, 0, 100);
        s_gets(choice, 100);
        bool flag4 = str_same_cmp(choice, "1");
        bool flag5 = str_same_cmp(choice, "2");
        while (!flag4 && !flag5) {
            printf("非法输入！\n");
            printf("是否需要将输出结果写入文件？ 1.是 2.否 输入：");
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
                printf("打开文件失败！\n");
                return;
            }
            ListNode* p = head->next;
            if (flag1) {
                fprintf(fp,"%s学院学生基本信息:\n", faculty);
                Print_stu_Information(p, 1, fp, 1);
                while (p != tailer) {
                    if (str_same_cmp(p->studentFaculty, faculty)) {
                        Print_stu_Information(p, 1, fp,2);
                    }
                    p = p->next;
                }
            }
            else if (flag2) {
                fprintf(fp,"%s学院学生基本信息:\n", faculty);
                Print_stu_Information(p, 1, fp, 1);
                sort_cmp_grade(head, tailer, faculty, 3, fp);
            }
            printf("学生信息已写入到'faculty_search.txt'文件(源文件目录下)\n");
            fclose(fp);
        }
        else {
            printf("%s学院学生基本信息:\n", faculty);
            Print_stu_Information(p, 0, NULL, 1);
            if (flag1) {
                ListNode* p = head->next;
                while (p != tailer) {
                    if (str_same_cmp(p->studentFaculty, faculty))Print_stu_Information(p, 0, NULL,2);
                    p = p->next;
                }
            }
            else if (flag2) {
                sort_cmp_grade(head, tailer, faculty, 1, NULL);
            }
        }
    }
}

void file_Inquire(ListNode* head, ListNode* tailer) {
    printf("请将需要查询的学生学号写入文件中\n");
    printf("要求：每行一个学号，每两个学号间用一个回车分隔，不能有空格\n");
    printf("最大查询上限为1000个，超出内容无法查询！\n");
    printf("最后一个学号输入后不能再输入回车键！\n");
    printf("\n");
    printf("请输入文件路径(路径两旁不要带双引号！):");
    char filepath[1000];
    memset(filepath, 0, sizeof(filepath));
    s_gets(filepath, 1000);
    FILE* fp;
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("打开文件失败！\n");
        return;
    }
    printf("选择排序方式 1.查询默认顺序 2.加分后绩点高低顺序 3.返回主菜单\n");
    printf("提醒：若选择第二种方式，输出文件中不含有查询不到的信息！\n");
    printf("输入选择：");
    char choice[100];
    memset(choice, 0, sizeof(choice));
    s_gets(choice, 100);
    bool flag1 = str_same_cmp(choice, "1");
    bool flag2 = str_same_cmp(choice, "2");
    bool flag3 = str_same_cmp(choice, "3");
    while (!flag1 && !flag2 && !flag3) {
        printf("非法输入！\n");
        printf("选择排序方式 1.查询默认顺序 2.加分后绩点高低顺序 3.返回主菜单\n");
        printf("提醒：若选择第二种方式，输出文件中不含有查询不到的信息！\n");
        printf("输入选择：");
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
            printf("文件中学号输入或文件格式非法！\n");
            printf("请调整文件内容或格式后再尝试\n");
            fclose(fp);
            return;
        }
        for (int j = 0; j < 8; j++) {
            if (studentID[i][j] < '0' || studentID[i][j]>'9') {
                printf("文件中学号输入或文件格式非法！\n");
                printf("请调整文件内容或格式后再尝试\n");
                fclose(fp);
                return;
            }
        }
        i++;
    }
    int num = i;
    if (i == 0) {
        printf("文件中不含有查询信息！\n");
        fclose(fp);
        return;
    }
    i = 0;
    FILE* fp1;
    fp1 = fopen("result.txt", "w");
    if (fp1 == NULL) {
        printf("输出文件打开失败！\n");
        fclose(fp);
        return;
    }
    int flag = 0;
    int k = 1;
    if(flag1){
        while (!str_same_cmp(studentID[i], "")) {
            ListNode* p = head->next;
            while (p != tailer) {
                if (str_same_cmp(p->studentID, studentID[i])) {
                    fprintf(fp1,"第%d个查询结果：", k);
                    k++;
                    Print_stu_Information(p, 1, fp1,0);
                    flag = 1;
                    break;
                }
                p = p->next;
            }
            if (!flag) {
                fprintf(fp1,"第%d个查询结果：", k);
                k++;
                fprintf(fp1, "未找到该学生信息！\n");
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
            printf("未查询到任何信息！\n");
            free(p_array);
            fclose(fp1);
            fclose(fp);
            return;
        }
        qsort(p_array, k, sizeof(ListNode*), compare_grade);
        Print_stu_Information(p, 1, fp1, 1);
        for (int i = 0; i < k; i++) {
            Print_stu_Information(p_array[i], 1, fp1,2);
        }
        free(p_array);
    }
    printf("查询完毕！结果已输出到'查询结果.txt'文件(源文件目录下)\n");
    fclose(fp1);
    fclose(fp);
    return;
}



// int main() {
//     ListNode* head = malloc(sizeof(ListNode)); //链表头节点
//     ListNode* tailer = malloc(sizeof(ListNode)); //链表尾结点
//     head->next = tailer;
//     tailer->father = head;
//     ListNode* currentNode = head;
//     for (int i = 0; i < 3; ++i) {
//         // 创建新结点
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