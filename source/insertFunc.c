#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "definition.h"

int maxThesisGradeKind = 6;
int maxContestGradeKind = 5;
int maxProjectGradeKind = 2;
double TheGrade[maxGradeType] = {0.4,0.2,0.1,0.05,0.02,0.01};
double ConGrade[maxGradeType] = {0.4,0.2,0.1,0.05,0.02};
double ProGrade[maxGradeType] = {0.1,0.05};
char TheGName[maxGradeType][maxListNameSize] = {
    "\t业界公认学科综合顶级期刊\n",
    "\tCCF-A期刊\n\tCCF-A会议长文\n\tCCF-B会议的最佳论文/最佳学生论文\n",
    "\tCCF-B期刊论文\n\t中科院期刊分区一区论文\n\tCCFC会议的最佳论文/最佳学生论文\n",
    "\tCCF-C期刊论文\n\tCCF-B 会议长文\n\t中科院期刊分区二区论文\n\t计算机学报、软件学报发表的学术论文\n",
    "\t影响因子非0的SCI检索期刊论文\n\tCCF-C 会议长文\n\t中国科学:信息科学、计算机研究与发展、计算机辅助设计与图形学学报、电子学报中文版、自动化学报发表的学术论文\n",
    "\tEI检索期刊\n"
};
char ConGName[maxGradeType][maxListNameSize] = {
    "\tA类竞赛国家级一等奖(金奖)\n",
    "\tA类竞赛国家级二等奖(银奖)\n\tB类竞赛国家级一等奖(金奖)\n",
    "\tA类竞赛国家级三等奖(铜奖)\n\tB类竞赛国家级二等奖(银奖)\n\tC类竞赛国家级一等奖(金奖)\n",
    "\tB类竞赛国家级三等奖(铜奖)\n\tC类竞赛国家级二等奖(银奖)\n",
    "\tC类竞赛国家级三等奖(铜奖)\n"
};
char ProGName[maxGradeType][maxListNameSize] = {
    "\t国家级优秀结题项目负责人\n",
    "\t国家级优秀结题项目第二名\n"
};

//加分细则重置为计算机学院
void resetGrade(){
    int maxThesisGradeKind = 6;
    int maxContestGradeKind = 5;
    int maxProjectGradeKind = 2;
    double TheGrade[maxGradeType] = {0.4,0.2,0.1,0.05,0.02,0.01};
    double ConGrade[maxGradeType] = {0.4,0.2,0.1,0.05,0.02};
    double ProGrade[maxGradeType] = {0.1,0.05};
    memset(TheGName,0,sizeof(TheGName));
    // strcpy(TheGName,"")
}

//等级加分导入
void GradeInput(ListNode* head,ListNode* preListEnd){
    if(head != preListEnd){
        printf("链表未清空,无法修改");
        return;
    }
    FILE* fp;
    char FilePath[300];
    printf("输入导入文件路径('#'退出):");
    scanf("%s",&FilePath);
    if(FilePath[0] == '#')
        return;
    fp = fopen(FilePath,"r");
    while(!fp){
        printf("路径错误,重新输入:");
        scanf("%s",&FilePath);
        if(FilePath[0] == '#')
            return;
        fp = fopen(FilePath,"r");
    }
    int i = 0;
    while(i < 3){
        char GradeKind;
        fscanf(fp,"%c",&GradeKind);
        i++;
        switch(GradeKind){
            case 'C' :
                fscanf(fp,"%d",&maxContestGradeKind);
                if(maxContestGradeKind > maxGradeType)
                    maxContestGradeKind = maxGradeType;
                memset(ConGName,0,sizeof(ConGName));
                for(int i = 0;i < maxContestGradeKind;i++){
                    char ch = fgetc(fp);
                    while(ch == '#'){
                        strcat(ConGName[i],"\t");
                        char temp[500];
                        fscanf(fp,"%s",&temp);
                        strcat(ConGName[i],temp);
                        strcat(ConGName[i],"\n");
                        fgetc(fp);
                        ch = fgetc(fp);
                    }
                    fscanf(fp,"%lf",&ConGrade[i]);
                    // printf("%s ",ConGName[i]);
                    // printf("%.3lf\n",ConGrade[i]);
                    fgetc(fp);
                }
                break;
            case 'T' :
                fscanf(fp,"%d",&maxThesisGradeKind);
                if(maxThesisGradeKind > maxGradeType)
                    maxThesisGradeKind = maxGradeType;
                memset(TheGName,0,sizeof(TheGName));
                for(int i = 0;i < maxThesisGradeKind;i++){
                    char ch = fgetc(fp);
                    while(ch == '#'){
                        strcat(TheGName[i],"\t");
                        char temp[500];
                        fscanf(fp,"%s",&temp);
                        strcat(TheGName[i],temp);
                        strcat(TheGName[i],"\n");
                        fgetc(fp);
                        ch = fgetc(fp);
                    }
                    fscanf(fp,"%lf",&TheGrade[i]);
                    // printf("%s ",TheGName[i]);
                    // printf("%.3lf\n",TheGrade[i]);
                    fgetc(fp);
                }
                break;
            case 'P' :

                break;
            default :

                break;
        }
    }
    return;
}

//文件输入
void fileInsert(ListNode** preListEnd){
    char filePath[100];
    printf("文件格式：");
    printf("每组数据一行,使用space间隔,缺省信息使用#代替\n");
    printf("开头 : 学号(不可缺省) 姓名\n");
    printf("后续 : 类型:大创、科研、竞赛\n");
    printf("之后按数据定义顺序\n");
    printf("请输入文件路径(输入‘#’退出）：");
    scanf("%s",&filePath);
    if(filePath[0] == '#')
        return;
    FILE *fp = fopen(filePath,"r");
    int failureNum = 0;
    while(!fp && failureNum < 5){
        failureNum++;
        printf("文件打开失败，请重新输入(输入‘#’退出）：");
        scanf("%s",&filePath);
        if(filePath[0] == '#')
            return;
        fp = fopen(filePath,"r");
    }
    duqu(preListEnd,fp);
    fclose(fp);
    return;
}

void duqu(ListNode** preListEnd,FILE* fp){
    while(!feof(fp)){
        gradeNode* tempGrade = malloc(sizeof(gradeNode));
        tempGrade->studentName[0] = '#';
        tempGrade->studentName[1] = '\0';
        tempGrade->recognizedCredit = 0.0; //初始化

        //读取学号
        char info[20];
        fscanf(fp,"%s",&info);
        int len = 0;
        for(len = 0;len < 20 && info[len] != '\0';len++){}
        if(len != 8){
            printf("学号位数错误,退出");
            free(tempGrade);
            return;
        }
        strcpy(tempGrade->studentID,info); 

        //读取姓名
        fscanf(fp,"%s",&info);
        if(info[0] != '#'){
            memset(tempGrade->studentName,0,sizeof(tempGrade->studentName));
            strcpy(tempGrade->studentName,info);
        }

        //读取类型
        char kind;
        fscanf(fp,"%c",&kind);
        switch(kind){
            case 'P' :
                    tempGrade->gradeType = PROJECT;
                    tempGrade->Project = projectFileInput(&fp);
                    //fgetc(fp);
            case 'T' :
                    tempGrade->gradeType = THESIS;

                    //fgetc(fp);
            case 'C' :
                    tempGrade->gradeType = CONTEST;

                    //fgetc(fp);
            default : 
                    printf("素质项目类型错误");
                    free(tempGrade);
                    return;
        }

        ListNode* temp = malloc(sizeof(ListNode));
        temp->next = (*preListEnd)->next;
        (*preListEnd)->next = temp;
        *preListEnd = temp;
        (*preListEnd)->t = tempGrade;
    }
    return;
}


// void fileGetLineOne(gradeNode* t,FILE** f){
//     char info[3][20];
//     fscanf(*f,"%s%s%s",info[0],info[1],info[2]);
//     int a[3] = {gradeNodeJudge(info[0]),gradeNodeJudge(info[1]),gradeNodeJudge(info[2])};
//     for(int j = 0;j < 3;j++){
//         switch(a[j]){
//             case 0 : break;
//             case 1 :
//                 int i;
//                 for(i = 0;info[j][i] != '\0';i++)
//                     t->studentID[i] = info[j][i];
//                 t->studentID[i] = info[j][i];
//                 break;
//             case 2 :
//                 int fenmu = 10;
//                 for(int i = 2;info[j][i] != '\0';i++){
//                     t->recognizedCredit += (double)(info[j][i] - '0') / fenmu;
//                     fenmu *= 10;
//                 }
//                 break;
//             case 3 :
//                 for(i = 0;info[j][i] != '\0';i++)
//                     t->studentName[i] = info[j][i];
//                 t->studentName[i] = info[j][i];
//                 break;
//             default :
//                 printf("error");
//                 break;           
//         }
//     }
// }

// int gradeNodeJudge(char* info){
//     if(info[0] == '#')
//         return 0;
//     int len;
//     for(len = 0;info[len] != '\0';len++){}
//     if(len == 8){ //判断学号
//         bool match = true;
//         for(int i = 0;i < len;i++){
//             if(info[i] < '0' || info[i] > '9'){
//                 match = false;
//                 break;
//             }
//         }
//         if(match)
//             return 1;
//     }
//     else if(info[0] == '0' && info[1] == '.'){
//         bool match = true;
//         for(int i = 2;info[i] != '\0';i++){
//             if(info[i] < '0' || info[i] > '9'){
//                 match = false;
//                 break;
//             }
//         }
//         if(match)
//             return 2;
//     }
//     else{ //姓名
//         bool match = true;
//         for(int i = 0;i < len;i++){
//             if(info[i] >= '0' && info[i] <= '9'){
//                 match = false;
//                 break;
//             }
//         }
//         return 3;
//     }
//     return 4;
// }

project* projectFileInput(FILE** f){
    project* p = malloc(sizeof(project));
    fscanf(*f,"%d",&(p->memberNum)); 
    for(int i = 0;i < p->memberNum;i++){
        fscanf(*f,"%s",p->members[i]);
    }
    fscanf(*f,"%s%s%d%d%d",p->instructor,p->projrectName,&(p->itemNum),&(p->approvalTime),&(p->endTime));
    return p;
}



//手动输入
void singleInsert(ListNode** preListEnd){
    gradeNode* g = malloc(sizeof(gradeNode));
    char info[50];
    int failNum = 0;

    //输入学号
    printf("输入学号:");
    scanf("%s",&info);
    int len = 0;
    for(len = 0;len < 20 && info[len] != '\0';len++){}
    while(len != 8){
        failNum++;
        if(failNum >= 5){
            printf("错误5次,退出");
            return;
        }
        printf("学号位数错误,重新输入:");
        scanf("%s",&info);
        len = 0;
        for(len = 0;len < 20 && info[len] != '\0';len++){}
    }
    strcpy(g->studentID,info); 
    
    //输入姓名
    printf("输入姓名:");
    scanf("%s",&(g->studentName));

    printf("输入素质项目类型: 1.科研 2.大创 3.竞赛\n");
    printf("输入选项:");
    int a = 0;
    failNum = 0;
    scanf("%d",&a);
    while(a != 1 && a != 2 && a != 3){
        failNum++;
        if(failNum >= 5){
            printf("错误5次,退出");
            return;
        }
        printf("错误,重新输入:");
        scanf("%d",&a);
    }
    switch(a){
        case 1 :
            g->gradeType = THESIS;
            thesisSingleInput(g);
            break;
        case 2 : 
            g->gradeType = PROJECT;
            projectSingleInput(g);
            break;
        case 3 : 
            g->gradeType = CONTEST;
            contestSingleInput(g);
            break;
        default :
            break;
    }

    printf("输入成功");
    ListNode* temp = malloc(sizeof(ListNode));
    temp->t = g;
    temp->next = (*preListEnd)->next;
    (*preListEnd)->next = temp;
    (*preListEnd) = temp;
    return;
}

void projectSingleInput(gradeNode* g){
    project* p = malloc(sizeof(project));

    printf("输入成员数量:");
    scanf("%d",&(p->memberNum));

    printf("输入成员名单");
    for(int i = 0;i < p->memberNum;i++){
        scanf("%s",&p->members[i]);
    }

    printf("输入指导老师姓名:");
    scanf("%s",&p->instructor);

    printf("项目名称:");
    scanf("%s",&p->projrectName);

    printf("项目编号:");
    scanf("%d",&p->itemNum);

    printf("立项时间:");
    scanf("%d",&p->approvalTime);

    printf("结项时间:");
    scanf("%d",&p->endTime);

    g->Project = p;
    return;
}

void thesisSingleInput(gradeNode* g){
    thesis* t = malloc(sizeof(thesis));
    g->Thesis = t;

    printf("输入论文标题:");
    scanf("%s",t->thesisName);

    printf("输入出版时间:");
    scanf("%d",&t->publicationTime);

    getchar();
    for(int i = 0;i < 6;i++){
        printf("G%d:%s",i + 1,TheGName[i]);
    }
    printf("输入等级数字:");
    int grade;
    scanf("%d",&grade);
    if(grade >= 1 && grade <= 6){
        t->Grade = grade - 1;
        pipei(g);
    }

    //g->Thesis = t;
    return;
}

void contestSingleInput(gradeNode* g){
    contest* c = malloc(sizeof(contest));
    g->Contest = c;

    printf("输入竞赛名:");
    scanf("%s",&c->contestName);

    printf("输入主办单位:");
    scanf("%s",&c->organizer);

    printf("输入获奖人数:");
    int num = 0;
    scanf("%d",&num);
    printf("输入获奖人:");
    for(int i = 0;i < num;i++){
        scanf("%s",&c->winners[i]);
    }
    
    for(int i = 0;i < 5;i++){
        printf("G%d:%s",i + 1,ConGName[i]);
    }
    printf("输入等级数字:");
    scanf("%d",&num);
    if(num >= 1 && num <= 5){
        c->conG = num - 1;
        pipei(g);
    }

    char ch;
    getchar();
    printf("是否是本学院专业相关学科竞赛?输入Y or N:");
    scanf("%c",&ch);
    switch(ch){
        case 'Y' : 
                c->ifCsContest = true;
                break;
        case 'N' :
                c->ifCsContest = false;
                break;
        default : break;
    }

    printf("输入获奖时间:");
    scanf("%d",&c->prizeTIme);

    //g->Contest = c;
    return;
}



void pipei(gradeNode* g){
    switch(g->gradeType){
        case THESIS :
                thesis* temp1 = g->Thesis;
                int grade = temp1->Grade;
                g->recognizedCredit = TheGrade[grade];
                break;
        case CONTEST :
                contest* temp2 = g->Contest;
                grade = temp2->conG;
                g->recognizedCredit = ConGrade[grade];
                break;
        // case PROJECT :
        //         project* temp3 = g->Project;
        //         grade = temp3->;
        //         g->recognizedCredit = ProGrade[grade];
        default :
                break;
    }
    return;
}

bool StrEqu(char *a,char *b){
    int i = 0;
    for(i = 0;a[i] != '\0' && b[i] != '\0';i++){
        if(a[i] != b[i])
            return false;
    }
    if(a[i] == '\0' && b[i] == '\0')
        return true;
    return false;
}