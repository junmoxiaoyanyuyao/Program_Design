#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <locale.h>

#include "definition.h"
#include "Output.h"

char TYPE[5][30] = {"��������","����ѡ��","רҵ����","רҵѡ��","�ҿ�����"};

void Output(ListNode* head,ListNode* tailer){
    FILE* fp;
    char FileName[30];
    ListNode* tt = head->next;
    // setlocale(LC_ALL,"");
    printf("1.txt 2.csv\nѡ�񵼳���ʽ:");
    int choice;
    scanf("%d",&choice);
    switch(choice){
        case 1 :
            printf("���뵼���ļ���(txt):");
            scanf("%s",FileName);
            fp = fopen(FileName,"w");
            if(!fp){
                printf("�����ļ�ʧ��");
                return;
            }
            fprintf(fp,"ѧ��\t����\tѧԺ\t����\n");
            while(tt != tailer){
                fprintf(fp,"%s\t%s\t%s\n",tt->studentID,tt->studentName,tt->studentFaculty);
                if(tt->CourseNum > 0)
                    fprintf(fp,"\t\t\t�γ̳ɼ�\t�γ���\t�γ̺�\t�γ�����\tѧ��\t�ɼ�\t����\n");
                CourseGradeNode* c;
                for(int i = 0;i < tt->CourseNum;i++){
                    c = tt->gradeNode[i];
                    fprintf(fp,"\t\t\t\t\t%s\t%s\t%s\t%s\t%s\t%s\n",c->CourseName,c->CourseNum,TYPE[(int)c->gradeType],c->CourseCredit,c->CourseGrade,c->GPA);
                }
                fprintf(fp,"\t\t\t\tƽ����Ȩ����:%.2lf\n\n",tt->AverageGrade);
                if(tt->QualityGradeNum > 0)
                    fprintf(fp,"\t\t\t������Ŀ\n");
                thesis* t;
                project* p;
                contest* c1;
                for(int i = 0;i < tt->QualityGradeNum;i++){
                    switch(tt->QGrade[i]->QualityGradeType){
                        case THESIS :
                            t = tt->QGrade[i]->Thesis;
                            fprintf(fp,"\t\t\t\t����\t������\t����ʱ��\n");
                            fprintf(fp,"\t\t\t\t\t%s\t%d\t",t->thesisName,t->publicationTime);
                            break;
                        case PROJECT :
                            p = tt->QGrade[i]->Project;
                            fprintf(fp,"\t\t\t\t��\t��Ŀ��\t��Ա����\tָ����ʦ\t��Ŀ���\t����ʱ��\t����ʱ��\n");
                            fprintf(fp,"\t\t\t\t\t%s\t",p->projrectName);
                            for(int i = 0;i < p->memberNum;i++){
                                fprintf(fp,"%s ",p->members[i]);
                            }
                            fprintf(fp,"\t%s\t%d\t%d\t%d\t",p->instructor,p->itemNum,p->approvalTime,p->endTime);
                            break;
                        case CONTEST :
                            c1 = tt->QGrade[i]->Contest;
                            fprintf(fp,"\t\t\t\t����\t������\t����\t���쵥λ\t��ʱ��\n");
                            fprintf(fp,"\t\t\t\t\t%s\t%s\t%s\t%d\t",c1->contestName,c1->winners[0],c1->organizer,c1->prizeTIme);
                            break;
                        default :
                            break;
                    }
                    fprintf(fp,"\t�϶��ӷ�:%.2lf\n",tt->QGrade[i]->recognizedCredit);
                }
                fprintf(fp,"\t\t\t\t�����ʼӷ�:%.2lf\n\n",tt->AddQualityGrade);
                fprintf(fp,"\t\t\t\t�ܼ���:%.2lf\n\n",tt->AverageGrade + tt->AddQualityGrade);
                tt = tt->next;
            }
            printf("�����ɹ�\n");
            fclose(fp);
            break;
        case 2 :
            printf("���뵼���ļ���(csv):");
            scanf("%s",FileName);
            fp = fopen(FileName,"w");
            if(!fp){
                printf("�����ļ�ʧ��");
                return;
            }
            fprintf(fp,"ѧ��,����,ѧԺ,�ɼ�����\n");
            while(tt != tailer){
                fprintf(fp,"%s,%s,%s\n",tt->studentID,tt->studentName,tt->studentFaculty);
                if(tt->CourseNum > 0)
                    fprintf(fp," , , ,�γ̳ɼ�,�γ���,�γ̺�,�γ�����,ѧ��,�ɼ�,����\n");
                CourseGradeNode* c;
                for(int i = 0;i < tt->CourseNum;i++){
                    c = tt->gradeNode[i];
                    fprintf(fp," , , , ,%s,%s,%s,%s,%s,%s\n",c->CourseName,c->CourseNum,TYPE[(int)c->gradeType],c->CourseCredit,c->CourseGrade,c->GPA);
                }
                fprintf(fp," , , , ,ƽ����Ȩ����:%.2lf\n\n",tt->AverageGrade);
                if(tt->QualityGradeNum > 0)
                    fprintf(fp," , , ,������Ŀ\n");
                thesis* t;
                project* p;
                contest* c1;
                for(int i = 0;i < tt->QualityGradeNum;i++){
                    switch(tt->QGrade[i]->QualityGradeType){
                        case THESIS :
                            t = tt->QGrade[i]->Thesis;
                            fprintf(fp," , , , ,����,������,����ʱ��\n");
                            fprintf(fp," , , , , ,%s,%d,",t->thesisName,t->publicationTime);
                            break;
                        case PROJECT :
                            p = tt->QGrade[i]->Project;
                            fprintf(fp," , , , ,��,��Ŀ��,��Ա����,ָ����ʦ,��Ŀ���,����ʱ��,����ʱ��\n");
                            fprintf(fp," , , , , ,%s,",p->projrectName);
                            for(int i = 0;i < p->memberNum;i++){
                                fprintf(fp,"%s ",p->members[i]);
                            }
                            fprintf(fp," ,%s,%d,%d,%d,",p->instructor,p->itemNum,p->approvalTime,p->endTime);
                            break;
                        case CONTEST :
                            c1 = tt->QGrade[i]->Contest;
                            fprintf(fp," , , , ,����,������,����,���쵥λ,��ʱ��\n");
                            fprintf(fp," , , , , ,%s,%s,%s,%d,",c1->contestName,c1->winners[0],c1->organizer,c1->prizeTIme);
                            break;
                        default :
                            break;
                    }
                    fprintf(fp," ,�϶��ӷ�:%.2lf\n",tt->QGrade[i]->recognizedCredit);
                }
                fprintf(fp," , , , ,�����ʼӷ�:%.2lf\n\n",tt->AddQualityGrade);
                fprintf(fp," , , , ,�ܼ���:%.2lf\n\n",tt->AverageGrade + tt->AddQualityGrade);
                tt = tt->next;
            }
            printf("�����ɹ�\n");
            fclose(fp);
            break;
    }
    system("pause");
    return;
}

