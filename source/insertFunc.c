#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "definition.h"
#include "Insert.h"
#include "login.h"

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

char GPA[11][4] = {"4.0","3.7","3.3","3.0","2.7","2.3","2.0","1.7","1.3","1.0","0.0"}; //默认GPA分值
// char CourseType[5][20] = {
//     "公共必修",
//     "公共选修",
//     "专业必修",
//     "专业选修",
//     "再修"
// };


//等级加分导入
void QualityGradeInput(ListNode* head,ListNode* tailer){
    if(head->next != tailer){
        printf("已保存数据,暂时无法修改");
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
                    fgetc(fp);
                }
                break;
            case 'P' :
                fscanf(fp,"%d",&maxProjectGradeKind);
                if(maxProjectGradeKind > maxGradeType)
                    maxProjectGradeKind = maxGradeType;
                memset(ProGName,0,sizeof(ProGName));
                for(int i = 0;i < maxProjectGradeKind;i++){
                    char ch = fgetc(fp);
                    while(ch == '#'){
                        strcat(ProGName[i],"\t");
                        char temp[500];
                        fscanf(fp,"%s",&temp);
                        strcat(ProGName[i],temp);
                        strcat(ProGName[i],"\n");
                        fgetc(fp);
                        ch = fgetc(fp);
                    }
                    fscanf(fp,"%lf",&ProGName[i]);
                    fgetc(fp);
                }
                break;
            default :

                return;
        }
    }
    return;
}

//素质项目文件输入
void QualityFileInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char filePath[300];
    printf("文件格式:略\n");
    printf("请输入文件路径(输入'#'返回上级菜单):");
    scanf("%s",&filePath);
    if(filePath[0] == '#')
        return;
    FILE *fp = fopen(filePath,"r");
    int failureNum = 0;
    while(fp == NULL){
        failureNum++;
        if(failureNum > 5){
            printf("错误5次,返回\n");
            return;
        }
        printf("文件打开失败，请重新输入(输入‘#’返回上级菜单):");
        scanf("%s",&filePath);
        if(filePath[0] == '#')
            return;
        fp = fopen(filePath,"r");
    }
    QualityFileInput(head,tailer,currentNode,fp);
    fclose(fp);
    return;
}

void QualityFileInput(ListNode* head,ListNode* tailer,ListNode** currentNode,FILE* fp){
    int line = 0; //记录行号
    while(!feof(fp)){
        line++;

        //读取学号
        char info[30];
        memset(info,0,sizeof(info));
        fscanf(fp,"%s",info);
        int len = 0;
        for(len = 0;len < 30 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                printf("Line:%d : 学号错误,返回上级菜单\n",line);
                return;
            }
        }
        if(len != 8){
            printf("Line:%d : 学号位数错误,返回上级菜单\n",line);
            return;
        }

        //搜索学号
        bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

        //读取姓名
        fscanf(fp,"%s",info);
        if(CreateNewNode){
            memset((*currentNode)->studentName,0,sizeof((*currentNode)->studentName));
            strcpy((*currentNode)->studentName,info);
        }
        else if(strcmp((*currentNode)->studentName,info) != 0){
            printf("Line:%d : 姓名信息与历史信息矛盾,退出\n",line);
            return;
        }

        matchFacultyName_list(head, tailer);
        // //读取学院
        // fscanf(fp,"%s",info);
        // if(CreateNewNode){
        //     memset((*currentNode)->studentFaculty,0,sizeof((*currentNode)->studentFaculty));
        //     strcpy((*currentNode)->studentFaculty,info);
        // }
        // else if(strcmp((*currentNode)->studentFaculty,info) != 0){
        //     printf("Line:%d : 学院信息与历史信息矛盾,退出\n",line);
        //     return;
        // }

        //可录入多条素质项目信息
        fgetc(fp);
        int num;
        fscanf(fp,"%d",&num);
        line++;
        fgetc(fp);
        char kind;
        for(int i = 0;i < num;i++){
            QualityGradeNode* tempQualityGrade = malloc(sizeof(QualityGradeNode));
            tempQualityGrade->recognizedCredit = 0.0; //初始化
            line++;
            fscanf(fp,"%c",&kind);
            switch((int)kind){
                case 'P' :
                        if(!projectFileInput(&fp,&(tempQualityGrade->Project))){
                            free(tempQualityGrade);
                            printf("Line:%d : 大创项目信息错误\n",line);
                            return;
                        }
                        tempQualityGrade->QualityGradeType = PROJECT;
                        fgetc(fp);
                        break;
                case 'T' :
                        if(!thesisFileInput(&fp,&(tempQualityGrade->Thesis))){
                            free(tempQualityGrade);
                            printf("Line:%d : 论文项目信息错误\n",line);
                            return;
                        }                
                        tempQualityGrade->QualityGradeType = THESIS;
                        fgetc(fp);
                        break;
                case 'C' :
                        if(!contestFileInput(&fp,&(tempQualityGrade->Contest))){
                            free(tempQualityGrade);
                            printf("Line:%d : 竞赛项目信息错误\n",line);
                            return;
                        }
                        tempQualityGrade->QualityGradeType = CONTEST;
                        fgetc(fp);
                        break;
                default : 
                        printf("Line:%d : 素质项目类型错误\n",line);
                        free(tempQualityGrade);
                        return;
            }

            //时间
            tempQualityGrade->addTime = GetTime();
            
            QualityGradeMatch(tempQualityGrade);
            (*currentNode)->QGrade[(*currentNode)->QualityGradeNum] = tempQualityGrade;
            (*currentNode)->QualityGradeNum++;
            (*currentNode)->AddQualityGrade = UpdataQualityGrade(*currentNode);
        }
        line++;
    }
    printf("素质项目信息文件输入成功\n");
    return;
}

bool projectFileInput(FILE** f,project** p){
    project* temp = malloc(sizeof(project));
    char ch = fgetc(*f);
    if(ch == '\n')
        return false;
    fscanf(*f,"%d",&(temp->memberNum));
    ch = fgetc(*f);
    if(ch == '\n')
        return false;
    for(int i = 0;i < temp->memberNum;i++){
        fscanf(*f,"%s",temp->members[i]);
        ch = fgetc(*f);
        if(ch == '\n')
            return false;
    }
    ch = fgetc(*f);
    if(ch == '\n')
        return false;
    fscanf(*f,"%s",temp->instructor);
    ch = fgetc(*f);
    if(ch == '\n')
        return false;
    fscanf(*f,"%s",temp->projrectName);
    ch = fgetc(*f);
    if(ch == '\n')
        return false;
    fscanf(*f,"%d",&(temp->itemNum));
    ch = fgetc(*f);
    if(ch == '\n')
        return false;
    fscanf(*f,"%d",&(temp->approvalTime));
    ch = fgetc(*f);
    if(ch == '\n')
        return false;
    fscanf(*f,"%d",&(temp->endTime));
    fscanf(*f,"%d",&(temp->proG));
    temp->proG--;
    *p = temp;
    return true;
}

bool thesisFileInput(FILE** f,thesis** t){
    thesis* temp = malloc(sizeof(thesis));
    // char ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    fscanf(*f,"%s",temp->thesisName);
    // ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    fscanf(*f,"%d",&(temp->publicationTime));
    // ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    fscanf(*f,"%d",&(temp->Grade));
    temp->Grade--;
    *t = temp;
    return true;
}

bool contestFileInput(FILE** f,contest** c){
    contest* temp = malloc(sizeof(contest));
    // char ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    fscanf(*f,"%s",temp->contestName);
    // ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    fscanf(*f,"%s",temp->organizer);
    // ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    int memberNum = 0;
    fscanf(*f,"%d",&memberNum);
    // ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;    
    for(int i = 0;i < memberNum;i++){
        fscanf(*f,"%s",temp->winners[i]);
        // ch = fgetc(*f);
        // if(ch == '\n')
        //     return false;
    }
    // ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    fscanf(*f,"%d",&(temp->prizeTIme));
    // ch = fgetc(*f);
    // if(ch == '\n')
    //     return false;
    fscanf(*f,"%d",&(temp->conG));
    temp->conG--;
    *c = temp;
    return true;
}

void QualityGradeMatch(QualityGradeNode* g){
    switch(g->QualityGradeType){
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
        case PROJECT :
                project* temp3 = g->Project;
                grade = temp3->proG;
                g->recognizedCredit = ProGrade[grade];
                break;
        default :
                break;
    }
    return;
}

//素质手输
void QualitySingleInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char info[50];
    int failNum = 0;

    //输入学号
    printf("请输入学号:");
    scanf("%s",info);
    int len = 0;
    for(len = 0;len < 50 && info[len] != '\0';len++){
        if(info[len] < '0' || info[len] > '9'){
            failNum++;
        }
        if(failNum >= maxFailNum){
            printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
            return;
        }
    }
    while(len != 8){
        failNum++;
        if(failNum >= maxFailNum){
            printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
            return;
        }
        printf("学号位数错误,重新输入:");
        scanf("%s",info);
        len = 0;
        for(len = 0;len < 20 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                failNum++;
            }
            if(failNum >= maxFailNum){
                printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
                return;
            }            
        }
    }

    //搜索学号
    bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

    //姓名
    if(CreateNewNode){
        printf("请输入姓名:");
        scanf("%s",&((*currentNode)->studentName));
    }
    else{
        printf("已有姓名:%s ,无需再次输入\n",(*currentNode)->studentFaculty);
    }

    matchFacultyName_list(head, tailer);
    // //学院
    // if(CreateNewNode){
    //     printf("请输入学院:");
    //     scanf("%s",&((*currentNode)->studentFaculty));
    // }
    // else{
    //     printf("已有学院:%s ,无需再次输入\n",(*currentNode)->studentFaculty);
    // }

    //
    bool ContinueInput = true;
    while(ContinueInput){
        printf("素质项目类型: 1.科研 2.大创 3.竞赛 4.返回\n");
        printf("请输入选项:");
        char a[maxSwitchChoiceSIze];
        failNum = 0;
        scanf("%d",&a);
        while(!SwitchCheck(a) || a[0] < 1 || a[0] > 4){
            failNum++;
            if(failNum >= maxFailNum){
                printf("输入错误满%d次,自动上级菜单\n",maxFailNum);
                return;
            }  
            printf("错误,重新输入:");
            scanf("%d",&a);
        }

        QualityGradeNode* tempQualityGrade = malloc(sizeof(QualityGradeNode));
        switch((int)a[0]){
            case '1' :
                tempQualityGrade->QualityGradeType = THESIS;
                thesisSingleInput(tempQualityGrade);
                break;
            case '2' : 
                tempQualityGrade->QualityGradeType = PROJECT;
                projectSingleInput(tempQualityGrade);
                break;
            case '3' : 
                tempQualityGrade->QualityGradeType = CONTEST;
                contestSingleInput(tempQualityGrade);
                break;
            case '4' :
                return;
            default :
                free(tempQualityGrade);
                break;
        }

        //时间
        tempQualityGrade->addTime = GetTime();

        printf("素质项目输入成功\n");
        (*currentNode)->QGrade[(*currentNode)->QualityGradeNum] = tempQualityGrade;
        (*currentNode)->QualityGradeNum++;
        (*currentNode)->AddQualityGrade = UpdataQualityGrade(*currentNode);

        failNum = 0;
        printf("是否需要继续输入其他素质项目? Y or N\n");
        printf("输入:");
        char choose[20];
        scanf("%s",choose);
        while(!SwitchCheck(choose) || failNum < maxFailNum){
            if(strcmp(choose,"N") == 0){
                ContinueInput = false;
                break;
            }
            else if(strcmp(choose,"Y") == 0){
                break;
            }
            else{
                failNum++;
                printf("错误,重新输入:");
                scanf("%s",choose);
            }
        }
        if(failNum >= maxFailNum){
            printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
            return;
        }
    }
    return;
}

void projectSingleInput(QualityGradeNode* g){
    project* p = malloc(sizeof(project));

    printf("请输入成员数量:");
    scanf("%d",&(p->memberNum));

    printf("请输入成员名单");
    for(int i = 0;i < p->memberNum;i++){
        scanf("%s",&p->members[i]);
    }

    printf("请输入指导老师姓名:");
    scanf("%s",&p->instructor);

    printf("请输入项目名称:");
    scanf("%s",&p->projrectName);

    int num;
    for(int i = 0;i < 5;i++){
        printf("G%d:%s",i + 1,ProGName[i]);
    }
    printf("请输入等级:");
    scanf("%d",&num);
    if(num >= 1 && num <= maxProjectGradeKind){
        p->proG = num - 1;
        QualityGradeMatch(g);
    }

    printf("请输入项目编号:");
    scanf("%d",&p->itemNum);

    printf("请输入立项时间:");
    scanf("%d",&p->approvalTime);

    printf("请输入结项时间:");
    scanf("%d",&p->endTime);

    g->Project = p;
    return;
}

void thesisSingleInput(QualityGradeNode* g){
    thesis* t = malloc(sizeof(thesis));
    g->Thesis = t;

    printf("请输入论文标题:");
    scanf("%s",t->thesisName);

    printf("请输入出版时间:");
    scanf("%d",&t->publicationTime);

    getchar();
    for(int i = 0;i < 6;i++){
        printf("G%d:%s",i + 1,TheGName[i]);
    }
    printf("输入等级论文等级:");
    int grade;
    scanf("%d",&grade);
    if(grade >= 1 && grade <= 6){
        t->Grade = grade - 1;
        QualityGradeMatch(g);
    }
    return;
}

void contestSingleInput(QualityGradeNode* g){
    contest* c = malloc(sizeof(contest));
    g->Contest = c;

    printf("请输入竞赛名:");
    scanf("%s",&c->contestName);

    printf("请输入主办单位:");
    scanf("%s",&c->organizer);

    printf("请输入获奖人数:");
    int num = 0;
    scanf("%d",&num);
    printf("请输入获奖名单:");
    for(int i = 0;i < num;i++){
        scanf("%s",&c->winners[i]);
    }
    
    for(int i = 0;i < 5;i++){
        printf("G%d:%s",i + 1,ConGName[i]);
    }
    printf("请输入竞赛等级:");
    scanf("%d",&num);
    if(num >= 1 && num <= 5){
        c->conG = num - 1;
        QualityGradeMatch(g);
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

    printf("请输入获奖时间:");
    scanf("%d",&c->prizeTIme);
    return;
}


//成绩文件输入
void CourseFileInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char filePath[300];
    printf("文件格式:略\n");
    //

    printf("请输入文件路径(输入'#'返回):");
    scanf("%s",&filePath);
    if(filePath[0] == '#')
        return;
    FILE *fp = fopen(filePath,"r");
    int failureNum = 0;
    while(!fp && failureNum < 5){
        failureNum++;
        printf("文件打开失败，请重新输入(输入‘#’返回):");
        scanf("%s",&filePath);
        if(filePath[0] == '#')
            return;
        fp = fopen(filePath,"r");
    }
    CourseFileInput(head,tailer,currentNode,fp);
    fclose(fp);
    return;
}

void CourseFileInput(ListNode* head,ListNode* tailer,ListNode** currentNode,FILE* fp){
    int line = 0; //记录行号
    while(!feof(fp)){
        line++;

        //读取学号
        char info[30];
        memset(info,'\0',sizeof(info));
        fscanf(fp,"%s",info);
        int len = 0;
        for(len = 0;len < 30 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                printf("Line:%d : 学号错误,退出\n",line);
                return;
            }
        }
        if(len != 8){
            printf("Line:%d : 学号位数错误,退出\n",line);
            return;
        }

        //搜索学号
        bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

        //读取姓名
        fscanf(fp,"%s",info);
        if(CreateNewNode){
            memset((*currentNode)->studentName,0,sizeof((*currentNode)->studentName));
            strcpy((*currentNode)->studentName,info);
        }
        else if(strcmp((*currentNode)->studentName,info) != 0){
            printf("Line:%d : 姓名信息与历史信息矛盾,退出\n",line);
            return;
        }

        matchFacultyName_list(head, tailer);
        // //读取学院
        // fscanf(fp,"%s",info);
        // if(CreateNewNode){
        //     memset((*currentNode)->studentFaculty,0,sizeof((*currentNode)->studentFaculty));
        //     strcpy((*currentNode)->studentFaculty,info);
        // }
        // else if(strcmp((*currentNode)->studentFaculty,info) != 0){
        //     printf("Line:%d : 学院信息与历史信息矛盾,退出\n",line);
        //     return;
        // }

        //可录入多条课程成绩信息
        fgetc(fp);
        int i = 0,index = 0;
        fscanf(fp,"%d",&index);
        while(i < index){
            i++;
            CourseGradeNode* c = malloc(sizeof(CourseGradeNode));
            fscanf(fp,"%s%s%s%s%d",c->CourseNum,c->CourseName,c->CourseCredit,c->CourseGrade,&(c->gradeType));
            char *ptr;
            if(strtod(c->CourseCredit,&ptr) < 0.0){
                printf("Line:%d : 学分为负数,退出\n",line);
                free(c);
                return;
            }
            c->gradeType--;
            double grade = strtod(c->CourseGrade,&ptr);
            if(grade < 0.0 || grade > 100.0){
                printf("Line:%d : 成绩不在0~100之间,退出\n",line);
                free(c);
                return;
            }
            GPAMatch(c);

            (*currentNode)->gradeNode[(*currentNode)->CourseNum] = c;
            (*currentNode)->CourseNum++;
            
        }
        (*currentNode)->AverageGrade = UpdateGPA(*currentNode);
        fgetc(fp);
    }   
    printf("学科成绩文件输入成功\n");
    fclose(fp);
    return;
}

//课程手输
void CourseSingleInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char info[50];
    int failNum = 0;

    //输入学号
    printf("输入学号:");
    scanf("%s",info);
    int len = 0;
    for(len = 0;len < 50 && info[len] != '\0';len++){
        if(info[len] < '0' || info[len] > '9'){
            failNum++;
        }
        if(failNum >= maxFailNum){
            printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
            return;
        }
    }
    while(len != 8){
        failNum++;
        if(failNum >= maxFailNum){
            printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
            return;
        }
        printf("学号位数错误,重新输入:");
        scanf("%s",info);
        len = 0;
        for(len = 0;len < 20 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                failNum++;
            }
            if(failNum >= maxFailNum){
                printf("输入错误满%d次,自动上级菜单\n",maxFailNum);
                return;
            }            
        }
    }

    //搜索学号
    bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

    //姓名
    if(CreateNewNode){
        printf("输入姓名:");
        scanf("%s",&((*currentNode)->studentName));
    }
    else{
        printf("已有姓名信息:%s ,无需再次输入\n",(*currentNode)->studentFaculty);
    }

    matchFacultyName_list(head, tailer);
    // //学院
    // if(CreateNewNode){
    //     printf("输入学院:");
    //     scanf("%s",&((*currentNode)->studentFaculty));
    // }
    // else{
    //     printf("已有学院信息:%s ,无需再次输入\n",(*currentNode)->studentFaculty);
    // }

    //
    
    bool ContinueInput = true;
    while(ContinueInput){
        CourseGradeNode* c = malloc(sizeof(CourseGradeNode));
        failNum = 0;
        printf("输入课程编号:");
        memset(info,'\0',sizeof(info));
        scanf("%s",info);
        while(!CorrectCourseNum(info)){
            if(failNum >= maxFailNum){
                printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
                return;
            }
            printf("错误,重新输入:");
            scanf("%s",info);
        }
        memset(c->CourseNum,'\0',sizeof(c->CourseNum));
        strcpy(c->CourseNum,info);
        printf("请输入课程名:");
        scanf("%s",c->CourseName);
        printf("1.公共必修 2.公共选修 3.专业必修 4.专业选修 5.再修\n");
        printf("请输入课程性质:");
        int a;
        scanf("%d",&a);
        if(a >= 1 && a <= 5){
            c->gradeType = a - 1;
        }
        else{
            printf("错误,返回");
            return;
        }
        printf("请输入学分:");
        scanf("%s",c->CourseCredit);
        char* ptr;
        while(strtod(c->CourseCredit,&ptr) < 0.0){
            printf("输入学分为负数,请重新输入:");
            scanf("%s",c->CourseCredit);
        }
        printf("请输入成绩:");
        scanf("%s",c->CourseGrade);
        double grade = strtod(c->CourseGrade,&ptr);
        while(grade < 0.0 || grade > 100.0){
            printf("成绩应在0~100之间,请重新输入:");
            scanf("%s",c->CourseGrade);
            grade = strtod(c->CourseGrade,&ptr);
        }
        GPAMatch(c);
        printf("已自动匹配绩点:%.1lf\n",grade);

        printf("输入成功\n");
        (*currentNode)->gradeNode[(*currentNode)->CourseNum] = c;
        (*currentNode)->CourseNum++;

        failNum = 0;
        printf("是否需要继续输入此人其他学科成绩? Y or N\n");
        printf("输入:");
        char choose[20];
        scanf("%s",choose);
        while(failNum < maxFailNum){
            if(strcmp(choose,"N") == 0){
                ContinueInput = false;
                break;
            }
            else if(strcmp(choose,"Y") == 0){
                break;
            }
            else{
                failNum++;
                printf("错误,重新输入:");
                scanf("%s",choose);
            }
        }
        if(failNum >= maxFailNum){
            printf("输入错误满%d次,自动返回上级菜单\n",maxFailNum);
            return;
        }

        (*currentNode)->AverageGrade = UpdateGPA(*currentNode);
    }
    return;
}


//功能
bool InsertIDsearch(ListNode* head,ListNode* tailer,ListNode** currentNode,char* info){
    int isForward = 0;
    while((*currentNode) != head && (*currentNode) != tailer){
            int res = strcmp(info,(*currentNode)->studentID);
             if(res == 0){
                return false;
             }
             else if(res < 0 && isForward >= 0){
                *currentNode = (*currentNode)->father;
                isForward = 1;
             }
             else if(res > 0 && isForward <= 0){
                *currentNode = (*currentNode)->next;
                isForward = -1;
             }
             else if(res < 0 && isForward == -1){
                ListNode* tempNode = malloc(sizeof(ListNode));
                tempNode->AddQualityGrade = 0.0;
                tempNode->AverageGrade = 0.0;
                tempNode->father = (*currentNode)->father;
                tempNode->next = *currentNode;
                (*currentNode)->father->next = tempNode;
                (*currentNode)->father = tempNode;
                *currentNode = tempNode;
                memset((*currentNode)->studentID,'\0',sizeof((*currentNode)->studentID));
                strcpy((*currentNode)->studentID,info);
                (*currentNode)->QualityGradeNum = 0;
                (*currentNode)->CourseNum = 0;
                return true;
             }
             else if(res > 0 && isForward == 1){
                ListNode* tempNode = malloc(sizeof(ListNode));
                tempNode->AddQualityGrade = 0.0;
                tempNode->AverageGrade = 0.0;
                tempNode->father = (*currentNode);
                tempNode->next = (*currentNode)->next;
                (*currentNode)->next->father = tempNode;
                (*currentNode)->next = tempNode;
                *currentNode = tempNode;
                memset((*currentNode)->studentID,'\0',sizeof((*currentNode)->studentID));
                strcpy((*currentNode)->studentID,info);
                (*currentNode)->QualityGradeNum = 0;
                (*currentNode)->CourseNum = 0;
                return true;
             }
    }
    if((*currentNode) == tailer){
        ListNode* tempNode = malloc(sizeof(ListNode));
        tempNode->AddQualityGrade = 0.0;
        tempNode->AverageGrade = 0.0;
        tempNode->father = (*currentNode)->father;
        tempNode->next = *currentNode;
        (*currentNode)->father->next = tempNode;
        (*currentNode)->father = tempNode;
        *currentNode = tempNode;
    }
    else{
        ListNode* tempNode = malloc(sizeof(ListNode));
        tempNode->AddQualityGrade = 0.0;
        tempNode->AverageGrade = 0.0;
        tempNode->father = (*currentNode);
        tempNode->next = (*currentNode)->next;
        (*currentNode)->next->father = tempNode;
        (*currentNode)->next = tempNode;
        *currentNode = tempNode;
    }
    memset((*currentNode)->studentID,'\0',sizeof((*currentNode)->studentID));
    strcpy((*currentNode)->studentID,info);
    //printf("%s",(*currentNode)->studentID);
    (*currentNode)->QualityGradeNum = 0;
    (*currentNode)->CourseNum = 0;
    return true;
}

unsigned long long GetTime(){
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);
    unsigned long long res = 0;
    res += (p->tm_year + 1900) * 10000000000;
    res += (p->tm_mon + 1) * 100000000;
    res += (p->tm_mday) * 1000000;
    res += (p->tm_hour) * 10000;
    res += (p->tm_min) * 100;
    res += p->tm_sec;
    return res;
}

void ErrGetLine(){
    char c = getchar();
    while(c != '\n'){
        c = getchar();
    }
	return;
}

bool CorrectCourseNum(char* info){
    int i;
    for(i = 0;i < 2;i++){
        if(info[i] < 'a' || info[i] > 'z' || info[i] == '\0')
            return false;
    }
    for(i = 2;i < 10;i++){
        if(info[i] < '0' || info[i] > '9' || info[i] == '\0')
            return false;
    }
    if(info[10] != '\0')
        return false;
    return true;
}

bool SwitchCheck(char* choice){
    return choice[1] == '\0';
}

double UpdateGPA(ListNode* t){
    double res;
    double totalGrade = 0.0,totalCredit = 0.0;
    if(t->CourseNum == 0)
        return 0.0;
    char* ptr;
    for(int i = 0;i < t->CourseNum;i++){
        if(t->gradeNode[i]->gradeType == Revise)
            continue;
        totalCredit += strtod(t->gradeNode[i]->CourseCredit,&ptr);
        totalGrade += strtod(t->gradeNode[i]->CourseCredit,&ptr) * strtod(t->gradeNode[i]->GPA,&ptr);
    }
    res = totalGrade / totalCredit;
    return res;
}

double UpdataQualityGrade(ListNode* t){
    if(t->QualityGradeNum == 0)
        return 0.0;
    double res = 0.0;
    char* ptr;
    for(int i = 0;i < t->QualityGradeNum;i++)
        res += t->QGrade[i]->recognizedCredit,&ptr;
    res = fmin(res,maxQualityAddGrade);
    return res;
}

void GPAMatch(CourseGradeNode* c){
    char* ptr;
    double grade = strtod(c->CourseGrade,&ptr);

    if(c->gradeType == Revise){
        if(grade > 60.0)
            strcpy(c->GPA,"1.0");
        else
            strcpy(c->GPA,"0.0");
        return;
    }

    if(grade >= 90.0)
        strcpy(c->GPA,GPA[0]);
    else if(grade >= 87.0)
        strcpy(c->GPA,GPA[1]);
    else if(grade >= 84.0)
        strcpy(c->GPA,GPA[2]);
    else if(grade >= 80.0)
        strcpy(c->GPA,GPA[3]);
    else if(grade >= 77.0)
        strcpy(c->GPA,GPA[4]);
    else if(grade >= 74.0)
        strcpy(c->GPA,GPA[5]);
    else if(grade >= 70.0)
        strcpy(c->GPA,GPA[6]);
    else if(grade >= 67.0)
        strcpy(c->GPA,GPA[7]);
    else if(grade >= 64.0)
        strcpy(c->GPA,GPA[8]);
    else if(grade >= 60.0)
        strcpy(c->GPA,GPA[9]);
    else
        strcpy(c->GPA,GPA[10]);
    return;
}

void Insert(ListNode* head,ListNode* tailer,ListNode** currentNode){
InsertMenu1:
    printf("输入方式: 1.文件输入\t2.手动输入\t3.返回上级菜单\n");
    printf("请选择输入方式:");
    char choose1[maxSwitchChoiceSIze];
    int status = scanf("%s",choose1);
    int failNum = 0;
    while(!SwitchCheck(choose1) || status == 0 || choose1[0] < '1' || choose1[0] > '4'){
        failNum++;
        if(failNum >= maxFailNum){
            printf("输入错误%d次,自动返回主菜单\n",maxFailNum);
            return;
        }
        printf("输入错误,请重新输入:");
        ErrGetLine();
        status = scanf("%d",&choose1);
    }

    if(choose1[0] == '3'){ //
        return;
    }
InsertMenu2: 
    printf("成绩类型:1.学科成绩\t2.素质项目\t3.返回\n");
    printf("请选择成绩类型:");
    failNum = 0;
    char choose2[maxSwitchChoiceSIze];
    status = scanf("%s",choose2);
    while(!SwitchCheck(choose2) || status == 0 || choose2[0] < '1' || choose2[0] > '3'){
        failNum++;
        if(failNum >= maxFailNum){
            printf("输入错误%d次,自动返回主菜单\n",maxFailNum);
            return;
        }
        printf("输入错误,重新输入:");
        ErrGetLine();
        status = scanf("%d",&choose2);
    }

    switch((int)choose1[0]){
        case '1' :
                switch((int)choose2[0]){
                    case '1' :
                        CourseFileInsert(head,tailer,currentNode);
                        goto InsertMenu2;
                        break;
                    case '2' :
                        QualityFileInsert(head,tailer,currentNode);
                        goto InsertMenu2;
                        break;
                    case '3' :
                        goto InsertMenu1;
                        break;
                    default : break;
                }

        case '2' : 
                switch((int)choose2[0]){
                    case '1' : 
                            CourseSingleInsert(head,tailer,currentNode);
                            goto InsertMenu2;
                            break;
                    case '2' : 
                            QualitySingleInsert(head,tailer,currentNode);
                            goto InsertMenu2;
                            break;
                    case '3' :
                        goto InsertMenu1;
                        break;
                    default : 
                            printf("返回\n");
                            return;
                }
                break;
        case '3' :
            break;
        default : break;
    }
    return;
}
