#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "definition.h"

double TheGrade[6] = {0.4,0.2,0.1,0.05,0.02,0.01};
double ConGrade[5] = {0.4,0.2,0.1,0.05,0.02};
char TheGName[6][500] = {
    "\t业界公认学科综合顶级期刊",
    "\tCCF-A期刊\n\tCCF-A会议长文\n\tCCF-B会议的最佳论文/最佳学生论文\n",
    "\tCCF-B期刊论文\n\t中科院期刊分区一区论文\n\tCCFC会议的最佳论文/最佳学生论文\n",
    "\tCCF-C期刊论文\n\tCCF-B 会议长文\n\t中科院期刊分区二区论文\n\t计算机学报、软件学报发表的学术论文\n",
    "\t影响因子非0的SCI检索期刊论文\n\tCCF-C 会议长文\n\t中国科学:信息科学、计算机研究与发展、计算机辅助设计与图形学学报、电子学报中文版、自动化学报发表的学术论文\n",
    "\tEI检索期刊"
};
char ConGName[5][500] = {
    "\tA类竞赛国家级一等奖(金奖)\n",
    "\tA类竞赛国家级二等奖(银奖)\n\tB类竞赛国家级一等奖(金奖)\n",
    "\tA类竞赛国家级三等奖(铜奖)\n\tB类竞赛国家级二等奖(银奖)\n\tC类竞赛国家级一等奖(金奖)\n",
    "\tB类竞赛国家级三等奖(铜奖)\n\tC类竞赛国家级二等奖(银奖)\n",
    "\tC类竞赛国家级三等奖(铜奖)\n"
};



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

    memset(TheGName,0,sizeof(TheGName));
    for(int i = 0;i < 6;i++){
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
    fgetc(fp);
    memset(ConGName,0,sizeof(ConGName));
    for(int i = 0;i < 5;i++){
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
    return;
}

//文件输入
void fileInsert(ListNode** preListEnd){
    char filePath[100];
    printf("文件格式：");
    printf("每组数据两行,使用space间隔,缺省信息使用#代替\n");
    printf("第一行 : 学号 姓名\n");
    printf("第二行:类型:大创、科研、竞赛");
    printf("之后按数据定义顺序\n");
    printf("请输入文件路径(输入‘#’退出）：");
    scanf("%s",&filePath);
    if(filePath[0] == '#')
        return;
    FILE *fp = fopen(filePath,"r");
    while(!fp){
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
        tempGrade->studentID[0] = '#';
        tempGrade->studentID[1] = '\0';
        tempGrade->studentName[0] = '#';
        tempGrade->studentName[1] = '\0';
        tempGrade->recognizedCredit = 0.0; //初始化

        //读取第一行
        fileGetLineOne(tempGrade,&fp);
        if(tempGrade->studentID[0] == '#' && tempGrade->studentName[0] == '#'){
            printf("error");
            free(tempGrade);
            return;
        }
        //读取第二行
        fgetc(fp);
        char info;
        fscanf(fp,"%c",&info);
        //读取第三行
        if(info == '1'){
            tempGrade->gradeType = PROJECT;
            tempGrade->Project = projectFileInput(&fp);
            fgetc(fp);
        }
        else if(info == 2){
            tempGrade->gradeType = THESIS;
            fgetc(fp);
        }
        else if(info == 3){
            tempGrade->gradeType = CONTEST;
            fgetc(fp);
        }
        else{
            printf("error");
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


void fileGetLineOne(gradeNode* t,FILE** f){
    char info[3][20];
    fscanf(*f,"%s%s%s",info[0],info[1],info[2]);
    int a[3] = {gradeNodeJudge(info[0]),gradeNodeJudge(info[1]),gradeNodeJudge(info[2])};
    for(int j = 0;j < 3;j++){
        switch(a[j]){
            case 0 : break;
            case 1 :
                int i;
                for(i = 0;info[j][i] != '\0';i++)
                    t->studentID[i] = info[j][i];
                t->studentID[i] = info[j][i];
                break;
            case 2 :
                int fenmu = 10;
                for(int i = 2;info[j][i] != '\0';i++){
                    t->recognizedCredit += (double)(info[j][i] - '0') / fenmu;
                    fenmu *= 10;
                }
                break;
            case 3 :
                for(i = 0;info[j][i] != '\0';i++)
                    t->studentName[i] = info[j][i];
                t->studentName[i] = info[j][i];
                break;
            default :
                printf("error");
                break;           
        }
    }
}

int gradeNodeJudge(char* info){
    if(info[0] == '#')
        return 0;
    int len;
    for(len = 0;info[len] != '\0';len++){}
    if(len == 8){ //判断学号
        bool match = true;
        for(int i = 0;i < len;i++){
            if(info[i] < '0' || info[i] > '9'){
                match = false;
                break;
            }
        }
        if(match)
            return 1;
    }
    else if(info[0] == '0' && info[1] == '.'){
        bool match = true;
        for(int i = 2;info[i] != '\0';i++){
            if(info[i] < '0' || info[i] > '9'){
                match = false;
                break;
            }
        }
        if(match)
            return 2;
    }
    else{ //姓名
        bool match = true;
        for(int i = 0;i < len;i++){
            if(info[i] >= '0' && info[i] <= '9'){
                match = false;
                break;
            }
        }
        return 3;
    }
    return 4;
}

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
    printf("输入学号:");
    scanf("%s",&(g->studentID));
    

    printf("输入姓名:");
    scanf("%s",&(g->studentName));

    printf("输入素质项目类型: 1.科研 2.大创 3.竞赛\n");
    printf("输入选项:");
    int a = 0;
    scanf("%d",&a);
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
                switch(temp1->Grade){
                    case G1 : 
                            g->recognizedCredit = TheGrade[0];
                            return;
                    case G2 : 
                            g->recognizedCredit = TheGrade[1];
                            return;
                    case G3 : 
                            g->recognizedCredit = TheGrade[2];
                            return;
                    case G4 : 
                            g->recognizedCredit = TheGrade[3];
                            return;
                    case G5 : 
                            g->recognizedCredit = TheGrade[4];
                            return;
                    case G6 : 
                            g->recognizedCredit = TheGrade[5];
                            return;
                    default : break;
                }
                break;
        case CONTEST :
                contest* temp2 = g->Contest;
                switch(temp2->conG){
                    case g1 : 
                            g->recognizedCredit = ConGrade[0];
                            return;
                    case g2 : 
                            g->recognizedCredit = ConGrade[1];
                            return;
                    case g3 : 
                            g->recognizedCredit = ConGrade[2];
                            return;
                    case g4 : 
                            g->recognizedCredit = ConGrade[3];
                            return;
                    case g5 : 
                            g->recognizedCredit = ConGrade[4];
                            return;
                    default : break;
                }
                break;
    }
    return;
}

