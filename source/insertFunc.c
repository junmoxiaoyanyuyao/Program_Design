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
    "\tҵ�繫��ѧ���ۺ϶����ڿ�\n",
    "\tCCF-A�ڿ�\n\tCCF-A���鳤��\n\tCCF-B������������/���ѧ������\n",
    "\tCCF-B�ڿ�����\n\t�п�Ժ�ڿ�����һ������\n\tCCFC������������/���ѧ������\n",
    "\tCCF-C�ڿ�����\n\tCCF-B ���鳤��\n\t�п�Ժ�ڿ�������������\n\t�����ѧ�������ѧ�������ѧ������\n",
    "\tӰ�����ӷ�0��SCI�����ڿ�����\n\tCCF-C ���鳤��\n\t�й���ѧ:��Ϣ��ѧ��������о��뷢չ����������������ͼ��ѧѧ��������ѧ�����İ桢�Զ���ѧ�������ѧ������\n",
    "\tEI�����ڿ�\n"
};
char ConGName[maxGradeType][maxListNameSize] = {
    "\tA�ྺ�����Ҽ�һ�Ƚ�(��)\n",
    "\tA�ྺ�����Ҽ����Ƚ�(����)\n\tB�ྺ�����Ҽ�һ�Ƚ�(��)\n",
    "\tA�ྺ�����Ҽ����Ƚ�(ͭ��)\n\tB�ྺ�����Ҽ����Ƚ�(����)\n\tC�ྺ�����Ҽ�һ�Ƚ�(��)\n",
    "\tB�ྺ�����Ҽ����Ƚ�(ͭ��)\n\tC�ྺ�����Ҽ����Ƚ�(����)\n",
    "\tC�ྺ�����Ҽ����Ƚ�(ͭ��)\n"
};
char ProGName[maxGradeType][maxListNameSize] = {
    "\t���Ҽ����������Ŀ������\n",
    "\t���Ҽ����������Ŀ�ڶ���\n"
};

char GPA[11][4] = {"4.0","3.7","3.3","3.0","2.7","2.3","2.0","1.7","1.3","1.0","0.0"}; //Ĭ��GPA��ֵ
// char CourseType[5][20] = {
//     "��������",
//     "����ѡ��",
//     "רҵ����",
//     "רҵѡ��",
//     "����"
// };


//�ȼ��ӷֵ���
void QualityGradeInput(ListNode* head,ListNode* tailer){
    if(head->next != tailer){
        printf("�ѱ�������,��ʱ�޷��޸�");
        return;
    }
    FILE* fp;
    char FilePath[300];
    printf("���뵼���ļ�·��('#'�˳�):");
    scanf("%s",&FilePath);
    if(FilePath[0] == '#')
        return;
    fp = fopen(FilePath,"r");
    while(!fp){
        printf("·������,��������:");
        scanf("%s",&FilePath);
        if(FilePath[0] == '#')
            return;
        fp = fopen(FilePath,"r");
    }
    int i = 0;
    while(i < 3){
        char GradeKind;
        if(feof(fp))
            return;
        fscanf(fp,"%c",&GradeKind);
         i++;
        switch(GradeKind){
            case 'C' :
                fscanf(fp,"%d",&maxContestGradeKind);
                if(maxContestGradeKind > maxGradeType)
                    maxContestGradeKind = maxGradeType;
                memset(ConGName,0,sizeof(ConGName));
                fgetc(fp);
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
                if(feof(fp))
                    return;
                fgetc(fp);
                break;
            case 'T' :
                fscanf(fp,"%d",&maxThesisGradeKind);
                if(maxThesisGradeKind > maxGradeType)
                    maxThesisGradeKind = maxGradeType;
                memset(TheGName,0,sizeof(TheGName));
                fgetc(fp);
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
                if(feof(fp))
                    return;
                fgetc(fp);
                break;
            case 'P' :
                fscanf(fp,"%d",&maxProjectGradeKind);
                if(maxProjectGradeKind > maxGradeType)
                    maxProjectGradeKind = maxGradeType;
                memset(ProGName,0,sizeof(ProGName));
                fgetc(fp);
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
                if(feof(fp))
                    return;
                fgetc(fp);
                break;
            default :
                return;
        }
    }
    return;
}

//������Ŀ�ļ�����
void QualityFileInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char filePath[300];
    printf("�ļ���ʽ:��\n");
    printf("�������ļ�·��(����'#'�����ϼ��˵�):");
    scanf("%s",&filePath);
    if(filePath[0] == '#')
        return;
    FILE *fp = fopen(filePath,"r");
    int failureNum = 0;
    while(fp == NULL){
        failureNum++;
        if(failureNum > 5){
            printf("����5��,����\n");
            return;
        }
        printf("�ļ���ʧ�ܣ�����������(���롮#�������ϼ��˵�):");
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
    int line = 0; //��¼�к�
    while(!feof(fp)){
        line++;

        //��ȡѧ��
        char info[30];
        memset(info,0,sizeof(info));
        fscanf(fp,"%s",info);
        int len = 0;
        for(len = 0;len < 30 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                printf("Line:%d : ѧ�Ŵ���,�����ϼ��˵�\n",line);
                return;
            }
        }
        if(len != 8){
            printf("Line:%d : ѧ��λ������,�����ϼ��˵�\n",line);
            return;
        }

        //����ѧ��
        bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

        //��ȡ����
        fscanf(fp,"%s",info);
        if(CreateNewNode){
            memset((*currentNode)->studentName,0,sizeof((*currentNode)->studentName));
            strcpy((*currentNode)->studentName,info);
        }
        else if(strcmp((*currentNode)->studentName,info) != 0){
            printf("Line:%d : ������Ϣ����ʷ��Ϣì��,�˳�\n",line);
            return;
        }

        matchFacultyName_list(head, tailer);
        // //��ȡѧԺ
        // fscanf(fp,"%s",info);
        // if(CreateNewNode){
        //     memset((*currentNode)->studentFaculty,0,sizeof((*currentNode)->studentFaculty));
        //     strcpy((*currentNode)->studentFaculty,info);
        // }
        // else if(strcmp((*currentNode)->studentFaculty,info) != 0){
        //     printf("Line:%d : ѧԺ��Ϣ����ʷ��Ϣì��,�˳�\n",line);
        //     return;
        // }

        //��¼�����������Ŀ��Ϣ
        fgetc(fp);
        int num;
        fscanf(fp,"%d",&num);
        line++;
        fgetc(fp);
        char kind;
        for(int i = 0;i < num;i++){
            QualityGradeNode* tempQualityGrade = malloc(sizeof(QualityGradeNode));
            tempQualityGrade->recognizedCredit = 0.0; //��ʼ��
            line++;
            fscanf(fp,"%c",&kind);
            switch((int)kind){
                case 'P' :
                        if(!projectFileInput(&fp,&(tempQualityGrade->Project))){
                            free(tempQualityGrade);
                            printf("Line:%d : ����Ŀ��Ϣ����\n",line);
                            return;
                        }
                        tempQualityGrade->QualityGradeType = PROJECT;
                        fgetc(fp);
                        break;
                case 'T' :
                        if(!thesisFileInput(&fp,&(tempQualityGrade->Thesis))){
                            free(tempQualityGrade);
                            printf("Line:%d : ������Ŀ��Ϣ����\n",line);
                            return;
                        }                
                        tempQualityGrade->QualityGradeType = THESIS;
                        fgetc(fp);
                        break;
                case 'C' :
                        if(!contestFileInput(&fp,&(tempQualityGrade->Contest))){
                            free(tempQualityGrade);
                            printf("Line:%d : ������Ŀ��Ϣ����\n",line);
                            return;
                        }
                        tempQualityGrade->QualityGradeType = CONTEST;
                        fgetc(fp);
                        break;
                default : 
                        printf("Line:%d : ������Ŀ���ʹ���\n",line);
                        free(tempQualityGrade);
                        return;
            }

            //ʱ��
            tempQualityGrade->addTime = GetTime();
            
            QualityGradeMatch(tempQualityGrade);
            (*currentNode)->QGrade[(*currentNode)->QualityGradeNum] = tempQualityGrade;
            (*currentNode)->QualityGradeNum++;
            (*currentNode)->AddQualityGrade = UpdataQualityGrade(*currentNode);
        }
        line++;
    }
    printf("������Ŀ��Ϣ�ļ�����ɹ�\n");
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

//��������
void QualitySingleInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char info[50];
    int failNum = 0;

    //����ѧ��
    printf("������ѧ��:");
    scanf("%s",info);
    int len = 0;
    for(len = 0;len < 50 && info[len] != '\0';len++){
        if(info[len] < '0' || info[len] > '9'){
            failNum++;
        }
        if(failNum >= maxFailNum){
            printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
            return;
        }
    }
    while(len != 8){
        failNum++;
        if(failNum >= maxFailNum){
            printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
            return;
        }
        printf("ѧ��λ������,��������:");
        scanf("%s",info);
        len = 0;
        for(len = 0;len < 20 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                failNum++;
            }
            if(failNum >= maxFailNum){
                printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
                return;
            }            
        }
    }

    //����ѧ��
    bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

    //����
    if(CreateNewNode){
        printf("����������:");
        scanf("%s",&((*currentNode)->studentName));
    }
    else{
        printf("��������:%s ,�����ٴ�����\n",(*currentNode)->studentName);
    }

    matchFacultyName_list(head, tailer);
    // //ѧԺ
    // if(CreateNewNode){
    //     printf("������ѧԺ:");
    //     scanf("%s",&((*currentNode)->studentFaculty));
    // }
    // else{
    //     printf("����ѧԺ:%s ,�����ٴ�����\n",(*currentNode)->studentFaculty);
    // }

    //
    bool ContinueInput = true;
    while(ContinueInput){
        printf("������Ŀ����: 1.���� 2.�� 3.���� 4.����\n");
        printf("������ѡ��:");
        char a[maxSwitchChoiceSIze];
        failNum = 0;
        scanf("%s",a);
        while(!SwitchCheck(a) || a[0] < '1' || a[0] > '4'){
            failNum++;
            if(failNum >= maxFailNum){
                printf("���������%d��,�Զ��ϼ��˵�\n",maxFailNum);
                return;
            }  
            printf("����,��������:");
            scanf("%s",a);
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

        //ʱ��
        tempQualityGrade->addTime = GetTime();

        printf("������Ŀ����ɹ�\n");
        (*currentNode)->QGrade[(*currentNode)->QualityGradeNum] = tempQualityGrade;
        (*currentNode)->QualityGradeNum++;
        (*currentNode)->AddQualityGrade = UpdataQualityGrade(*currentNode);

        failNum = 0;
        printf("�Ƿ���Ҫ������������������Ŀ? Y or N\n");
        printf("����:");
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
                printf("����,��������:");
                scanf("%s",choose);
            }
        }
        if(failNum >= maxFailNum){
            printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
            return;
        }
    }
    return;
}

void projectSingleInput(QualityGradeNode* g){
    project* p = malloc(sizeof(project));

    printf("�������Ա����:");
    scanf("%d",&(p->memberNum));

    printf("�������Ա����:");
    for(int i = 0;i < p->memberNum;i++){
        scanf("%s",&p->members[i]);
    }

    printf("������ָ����ʦ����:");
    scanf("%s",&p->instructor);

    printf("��������Ŀ����:");
    scanf("%s",&p->projrectName);

    int num;
    for(int i = 0;i < maxProjectGradeKind;i++){
        printf("G%d:%s",i + 1,ProGName[i]);
    }
    printf("������ȼ�:");
    scanf("%d",&num);
    while(num < 1 || num > maxContestGradeKind){
        printf("����,����������:");
        scanf("%d",&num);
    }
    p->proG = num - 1;
    QualityGradeMatch(g);

    printf("��������Ŀ���:");
    scanf("%d",&p->itemNum);

    printf("����������ʱ��:");
    scanf("%d",&p->approvalTime);

    printf("���������ʱ��:");
    scanf("%d",&p->endTime);

    g->Project = p;
    return;
}

void thesisSingleInput(QualityGradeNode* g){
    thesis* t = malloc(sizeof(thesis));
    g->Thesis = t;

    printf("���������ı���:");
    scanf("%s",t->thesisName);

    printf("���������ʱ��:");
    scanf("%d",&t->publicationTime);

    getchar();
    for(int i = 0;i < maxThesisGradeKind;i++){
        printf("G%d:%s",i + 1,TheGName[i]);
    }
    printf("����ȼ����ĵȼ�:");
    int grade;
    scanf("%d",&grade);
    while(grade < 1 || grade > maxThesisGradeKind){
        printf("����,����������:");
        scanf("%d",&grade);
    }
    t->Grade = grade - 1;
    QualityGradeMatch(g);
    return;
}

void contestSingleInput(QualityGradeNode* g){
    contest* c = malloc(sizeof(contest));
    g->Contest = c;

    printf("�����뾺����:");
    scanf("%s",&c->contestName);

    printf("���������쵥λ:");
    scanf("%s",&c->organizer);

    printf("�����������:");
    int num = 0;
    scanf("%d",&num);
    printf("�����������:");
    for(int i = 0;i < num;i++){
        scanf("%s",&c->winners[i]);
    }
    
    for(int i = 0;i < maxContestGradeKind;i++){
        printf("G%d:%s",i + 1,ConGName[i]);
    }
    printf("�����뾺���ȼ�:");
    scanf("%d",&num);
    while(num < 1 || num > maxContestGradeKind){
        printf("����,����������:");
        scanf("%d",&num);
    }
    c->conG = num - 1;
    QualityGradeMatch(g);

    char ch;
    getchar();
    printf("�Ƿ��Ǳ�ѧԺרҵ���ѧ�ƾ���?����Y or N:");
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

    printf("�������ʱ��:");
    scanf("%d",&c->prizeTIme);
    return;
}


//�ɼ��ļ�����
void CourseFileInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char filePath[300];
    printf("�ļ���ʽ:��\n");
    //

    printf("�������ļ�·��(����'#'����):");
    scanf("%s",&filePath);
    if(filePath[0] == '#')
        return;
    FILE *fp = fopen(filePath,"r");
    int failureNum = 0;
    while(!fp && failureNum < 5){
        failureNum++;
        printf("�ļ���ʧ�ܣ�����������(���롮#������):");
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
    int line = 0; //��¼�к�
    while(!feof(fp)){
        line++;

        //��ȡѧ��
        char info[30];
        memset(info,'\0',sizeof(info));
        fscanf(fp,"%s",info);
        int len = 0;
        for(len = 0;len < 30 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                printf("Line:%d : ѧ�Ŵ���,�˳�\n",line);
                return;
            }
        }
        if(len != 8){
            printf("Line:%d : ѧ��λ������,�˳�\n",line);
            return;
        }

        //����ѧ��
        bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

        //��ȡ����
        fscanf(fp,"%s",info);
        if(CreateNewNode){
            memset((*currentNode)->studentName,0,sizeof((*currentNode)->studentName));
            strcpy((*currentNode)->studentName,info);
        }
        else if(strcmp((*currentNode)->studentName,info) != 0){
            printf("Line:%d : ������Ϣ����ʷ��Ϣì��,�˳�\n",line);
            return;
        }

        matchFacultyName_list(head, tailer);
        // //��ȡѧԺ
        // fscanf(fp,"%s",info);
        // if(CreateNewNode){
        //     memset((*currentNode)->studentFaculty,0,sizeof((*currentNode)->studentFaculty));
        //     strcpy((*currentNode)->studentFaculty,info);
        // }
        // else if(strcmp((*currentNode)->studentFaculty,info) != 0){
        //     printf("Line:%d : ѧԺ��Ϣ����ʷ��Ϣì��,�˳�\n",line);
        //     return;
        // }

        //��¼������γ̳ɼ���Ϣ
        fgetc(fp);
        int i = 0,index = 0;
        fscanf(fp,"%d",&index);
        while(i < index){
            i++;
            CourseGradeNode* c = malloc(sizeof(CourseGradeNode));
            fscanf(fp,"%s%s%s%s%d",c->CourseNum,c->CourseName,c->CourseCredit,c->CourseGrade,&(c->gradeType));
            char *ptr;
            if(strtod(c->CourseCredit,&ptr) < 0.0){
                printf("Line:%d : ѧ��Ϊ����,�˳�\n",line);
                free(c);
                return;
            }
            c->gradeType--;
            double grade = strtod(c->CourseGrade,&ptr);
            if(grade < 0.0 || grade > 100.0){
                printf("Line:%d : �ɼ�����0~100֮��,�˳�\n",line);
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
    printf("ѧ�Ƴɼ��ļ�����ɹ�\n");
    fclose(fp);
    return;
}

//�γ�����
void CourseSingleInsert(ListNode* head,ListNode* tailer,ListNode** currentNode){
    char info[50];
    int failNum = 0;

    //����ѧ��
    printf("����ѧ��:");
    scanf("%s",info);
    int len = 0;
    for(len = 0;len < 50 && info[len] != '\0';len++){
        if(info[len] < '0' || info[len] > '9'){
            failNum++;
        }
        if(failNum >= maxFailNum){
            printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
            return;
        }
    }
    while(len != 8){
        failNum++;
        if(failNum >= maxFailNum){
            printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
            return;
        }
        printf("ѧ��λ������,��������:");
        scanf("%s",info);
        len = 0;
        for(len = 0;len < 20 && info[len] != '\0';len++){
            if(info[len] < '0' || info[len] > '9'){
                failNum++;
            }
            if(failNum >= maxFailNum){
                printf("���������%d��,�Զ��ϼ��˵�\n",maxFailNum);
                return;
            }            
        }
    }

    //����ѧ��
    bool CreateNewNode = InsertIDsearch(head,tailer,currentNode,info);

    //����
    if(CreateNewNode){
        printf("��������:");
        scanf("%s",&((*currentNode)->studentName));
    }
    else{
        printf("����������Ϣ:%s ,�����ٴ�����\n",(*currentNode)->studentName);
    }

    matchFacultyName_list(head, tailer);
    // //ѧԺ
    // if(CreateNewNode){
    //     printf("����ѧԺ:");
    //     scanf("%s",&((*currentNode)->studentFaculty));
    // }
    // else{
    //     printf("����ѧԺ��Ϣ:%s ,�����ٴ�����\n",(*currentNode)->studentFaculty);
    // }

    //
    
    bool ContinueInput = true;
    while(ContinueInput){
        CourseGradeNode* c = malloc(sizeof(CourseGradeNode));
        failNum = 0;
        printf("����γ̱��:");
        memset(info,'\0',sizeof(info));
        scanf("%s",info);
        while(!CorrectCourseNum(info)){
            if(failNum >= maxFailNum){
                printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
                return;
            }
            printf("����,��������:");
            scanf("%s",info);
        }
        memset(c->CourseNum,'\0',sizeof(c->CourseNum));
        strcpy(c->CourseNum,info);
        printf("������γ���:");
        scanf("%s",c->CourseName);
        printf("1.�������� 2.����ѡ�� 3.רҵ���� 4.רҵѡ�� 5.����\n");
        printf("������γ�����:");
        int a;
        scanf("%d",&a);
        if(a >= 1 && a <= 5){
            c->gradeType = a - 1;
        }
        else{
            printf("����,����");
            return;
        }
        printf("������ѧ��:");
        scanf("%s",c->CourseCredit);
        char* ptr;
        while(strtod(c->CourseCredit,&ptr) < 0.0){
            printf("����ѧ��Ϊ����,����������:");
            scanf("%s",c->CourseCredit);
        }
        printf("������ɼ�:");
        scanf("%s",c->CourseGrade);
        double grade = strtod(c->CourseGrade,&ptr);
        while(grade < 0.0 || grade > 100.0){
            printf("�ɼ�Ӧ��0~100֮��,����������:");
            scanf("%s",c->CourseGrade);
            grade = strtod(c->CourseGrade,&ptr);
        }
        GPAMatch(c);
        printf("���Զ�ƥ�伨��:%s\n",c->GPA);

        printf("����ɹ�\n");
        (*currentNode)->gradeNode[(*currentNode)->CourseNum] = c;
        (*currentNode)->CourseNum++;

        failNum = 0;
        printf("�Ƿ���Ҫ���������������ѧ�Ƴɼ�? Y or N\n");
        printf("����:");
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
                printf("����,��������:");
                scanf("%s",choose);
            }
        }
        if(failNum >= maxFailNum){
            printf("���������%d��,�Զ������ϼ��˵�\n",maxFailNum);
            return;
        }

        (*currentNode)->AverageGrade = UpdateGPA(*currentNode);
    }
    return;
}


//����
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
        res += t->QGrade[i]->recognizedCredit;
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
    printf("���뷽ʽ: 1.�ļ�����\t2.�ֶ�����\t3.�����ϼ��˵�\n");
    printf("��ѡ�����뷽ʽ:");
    char choose1[maxSwitchChoiceSIze];
    int status = scanf("%s",choose1);
    int failNum = 0;
    while(!SwitchCheck(choose1) || status == 0 || choose1[0] < '1' || choose1[0] > '4'){
        failNum++;
        if(failNum >= maxFailNum){
            printf("�������%d��,�Զ��������˵�\n",maxFailNum);
            return;
        }
        printf("�������,����������:");
        ErrGetLine();
        status = scanf("%d",&choose1);
    }

    if(choose1[0] == '3'){ //
        return;
    }
InsertMenu2: 
    printf("�ɼ�����:1.ѧ�Ƴɼ�\t2.������Ŀ\t3.����\n");
    printf("��ѡ��ɼ�����:");
    failNum = 0;
    char choose2[maxSwitchChoiceSIze];
    status = scanf("%s",choose2);
    while(!SwitchCheck(choose2) || status == 0 || choose2[0] < '1' || choose2[0] > '3'){
        failNum++;
        if(failNum >= maxFailNum){
            printf("�������%d��,�Զ��������˵�\n",maxFailNum);
            return;
        }
        printf("�������,��������:");
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
                            printf("����\n");
                            return;
                }
                break;
        case '3' :
            break;
        default : break;
    }
    return;
}
