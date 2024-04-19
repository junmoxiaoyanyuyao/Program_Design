
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "definition.h"
#include "Modify.h"

char CourseType[5][20] = {
    "��������",
    "����ѡ��",
    "רҵ����",
    "רҵѡ��",
    "�ҿ�����"
};

void CourseGradeModify(ListNode* t){
    CourseGradeNode* c;
    for(int i = 0;i < (t->CourseNum);i++){
        c = t->gradeNode[i];
        printf("%d\t",i + 1);
        printf("�γ���:%s\t�γ̺�:%s\t�γ�����:%s\t",c->CourseName,c->CourseNum,CourseType[c->gradeType]);
        printf("ѧ��:%s\t�ɼ�:%s\t����:%s\n",c->CourseCredit,c->CourseGrade,c->GPA);
    }
    printf("���������޸���Ŀ�ı��:");
    int index;
    scanf("%d",&index);
    while(index < 1 || index > t->CourseNum){
        printf("��Ŵ���,��������:");
        scanf("%d",&index);
    }

    c = t->gradeNode[index - 1];

    printf("1.�γ���\t2.�γ̺�\t3.�γ�����\t4.ѧ��\t5.�ɼ�\t6.����\n");
LOOP:
    printf("��������Ҫ�޸���������:");
    scanf("%d",&index);
    while(index < 1 && index > 6){
        printf("��Ŵ���,��������:");
        scanf("%d",&index);        
    }
    char info[100];
    char* ptr;
    switch(index){
        case 1 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseName);
            printf("�����޸ĺ�Ŀγ���:");
            scanf("%s",c->CourseName);
            printf("�޸ĳɹ�,%s->%s\n",info,c->CourseName);
            break;
        case 2 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseNum);
            printf("�����޸ĺ�Ŀγ̺�:");
            scanf("%s",c->CourseNum);
            printf("�޸ĳɹ�,%s->%s\n",info,c->CourseName);
            break;
        case 3 : 
            printf("1.��������\t2.����ѡ��\t3.רҵ����\t4.רҵѡ��\t5.����\n");
            printf("�����޸ĺ�Ŀγ�����:");
            int d = c->gradeType;
            scanf("%d",&(c->gradeType));
            while(c->gradeType < 0 || c->gradeType > 4){
                printf("����,����������:");
                scanf("%d",&(c->gradeType));
            }
            c->gradeType--;
            printf("�޸ĳɹ�,%s->%s\n",CourseType[d],CourseType[c->gradeType]);
            t->AverageGrade = UpdateGPA(t);
            break;
        case 4 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseCredit);
            printf("�����޸ĺ��ѧ��:");
            scanf("%s",c->CourseCredit);
            while(strtod(c->CourseCredit,&ptr) < 0.0){
                printf("����ѧ��Ϊ����,����������:");
                scanf("%s",c->CourseCredit);
            }
            printf("�޸ĳɹ�,%s->%s\n",info,c->CourseCredit);
            t->AverageGrade = UpdateGPA(t);
            break;
        case 5 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseGrade);
            printf("�����޸ĺ�ĳɼ�:");
            scanf("%s",c->CourseGrade);
            double grade = strtod(c->CourseGrade,&ptr);
            while(grade < 0.0 || grade > 100.0){
                printf("�ɼ�Ӧ��0~100֮��,����������:");
                scanf("%s",c->CourseGrade);
                grade = strtod(c->CourseGrade,&ptr);
            }
            printf("�޸ĳɹ�,%s->%s\n",info,c->CourseGrade);
            GPAMatch(c);
            t->AverageGrade = UpdateGPA(t);
            break;
        case 6 :
            return;
        default : 
            break;
    }
    goto LOOP;
    return;
}

void QualityGradeModify(ListNode* node){
    QualityGradeNode* q;
    thesis* t;
    project* p;
    contest* c;
    for(int i = 0;i < (node->QualityGradeNum);i++){
        q = node->QGrade[i];
        printf("%d\t",i + 1);
        switch(q->QualityGradeType){
            case THESIS :
                t = q->Thesis;
                printf("����\t������:%s\t����ʱ��:%d\n",t->thesisName,t->publicationTime);
                break;
            case PROJECT :
                p = q->Project;
                printf("��\t��Ա����:");
                for(int j = 0;j < p->memberNum;j++)
                    printf("%s ",p->members[j]);
                printf("\t��Ŀ��:%s\t��Ŀ���:%d\t����ʱ��:%d\t����ʱ��:%d\n",p->projrectName,p->itemNum,p->approvalTime,p->endTime);
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
LOOP:
    int index;
    printf("�������޸���Ϣ�ı��(����'0'����):");
    scanf("%d",&index);
    if(index == 0)
        return;
    while(index < 1 || index > node->QualityGradeNum){
        printf("��Ŵ���,��������:");
        scanf("%d",&index);
    }
    q = node->QGrade[index - 1];
    switch(q->QualityGradeType){
        case THESIS :
            printf("1.��������\t2.����ʱ��\t3.����\n");
            printf("��ѡ�����޸ĵ���Ϣ:");
            scanf("%d",&index);
            switch(index){
                case 1 : 
                    printf("�������޸ĺ����������:");
                    scanf("%s",q->Thesis->thesisName);
                    printf("�޸ĳɹ�\n");
                    break;
                case 2 :
                    printf("�������޸ĺ�ĳ���ʱ��:");
                    scanf("%s",q->Thesis->thesisName);
                    printf("�޸ĳɹ�\n");
                    goto LOOP;
                    break;
                case 3 :
                    break;
                default :
                    break;
            }
            break;
        case PROJECT :
            printf("1.��Ŀ��\t2.��Ա����\t3.ָ����ʦ\t4.��Ŀ���\t5.����ʱ��\t6.����ʱ��\t7.����\n");
            printf("���������޸ĵ���Ϣ");
            scanf("%d",&index);
            switch(index){
                case 1 : 
                    printf("�������޸ĺ����Ŀ����:");
                    scanf("%s",q->Project->projrectName);
                    printf("�޸ĳɹ�\n");
                    break;
                case 2 :
                    printf("�������޸ĺ����Ա��������:");
                    scanf("%d",&(q->Project->memberNum));
                    printf("�������޸ĺ����Ա����:");
                    for(int i = 0;i < q->Project->memberNum;i++)
                        scanf("%s",q->Project->members[i]);
                    printf("�޸ĳɹ�\n");
                    break;
                case 3 :
                    printf("�������޸ĺ��ָ����ʦ:");
                    scanf("%s",q->Project->instructor);
                    printf("�޸ĳɹ�\n");
                    break;
                case 4 :
                    printf("�������޸ĺ����Ŀ���:");
                    scanf("%s",q->Project->itemNum);
                    printf("�޸ĳɹ�\n");
                    break;
                case 5 :
                    printf("�������޸ĺ�Ŀ���ʱ��:");
                    scanf("%d",&(q->Project->approvalTime));
                    printf("�޸ĳɹ�\n");
                    break;
                case 6 :
                    printf("�������޸ĺ�Ľ���ʱ��:");
                    scanf("%d",&(q->Project->endTime));
                    printf("�޸ĳɹ�\n");
                case 7 :
                    break;
                default :
                    break;
            }
            break;
        case CONTEST :
            printf("1.������\t2.���쵥λ\t3.������\t4.��ʱ��\t5.����\n");
            printf("���������޸ĵ�ѡ��:");
            scanf("%d",&index);
            switch(index){
                case 1 : 
                    printf("�������޸ĺ�ľ�����:");
                    scanf("%s",q->Contest->contestName);
                    printf("�޸ĳɹ�\n");
                    break;
                case 2 :
                    printf("�������޸ĺ�����쵥λ����:");
                    scanf("%s",q->Contest->organizer);
                    printf("�޸ĳɹ�\n");
                    break;
                case 3 :
                    printf("�������޸ĺ�Ļ���������:");
                    scanf("%d",&index);
                    for(int i = 0;i < index;i++)
                        scanf("%s",q->Contest->winners);
                    printf("�޸ĳɹ�\n");
                    break;
                case 4 :
                    printf("�������޸ĺ�Ļ�ʱ��:");
                    scanf("%d",&(q->Contest->prizeTIme));
                    printf("�޸ĳɹ�\n");
                    break;
                case 5 :
                    break;
                default :
                    break;
            }
            break;
        default :
            break;
    }
    // printf("�޸ĳɹ�\n");
    return;
}

void Modify(ListNode* head,ListNode* tailer){
    printf("���������޸���Ϣ��ѧ��('#'����):");
    char studentID[9];
    scanf("%s",studentID);
    ListNode* t = head->next;
    if(studentID[0] == '#')
        return;
    while(t != tailer){
        if(strcmp(t->studentID,studentID) == 0)
            break;
        t = t->next;
    }
    if(t == tailer){
        printf("ѧ�Ų�����,����\n");
        return;
    }
    printf("���ҳɹ�\nѧ��:%s\t����:%s\n",t->studentID,t->studentName);
LOOP:
    int choose;
    printf("1.�ɼ� 2.���� 3.����\n�����������޸ĵ�����:");
    scanf("%d",&choose);
    switch(choose){
        case 1 :
            if(t->CourseNum == 0)
                printf("�޿��޸�����,����\n");
            else{
                CourseGradeModify(t);
                goto LOOP;
            }
            break;
        case 2 :
            if(t->QualityGradeNum == 0)
                printf("�޿��޸�����,����\n");
            else{
                QualityGradeModify(t);
                goto LOOP;
            }
            break;
        case 3 :
            break;
        default :
            printf("����,����\n");
            break;
    }
    return;
}

