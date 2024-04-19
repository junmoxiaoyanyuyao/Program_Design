#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <locale.h>

#include "definition.h"
#include "Output.h"

char TYPE[5][30] = {"公共必修","公共选修","专业必修","专业选修","挂科再修"};

void Output(ListNode* head,ListNode* tailer){
    FILE* fp;
    char FileName[30];
    ListNode* tt = head->next;
    // setlocale(LC_ALL,"");
    printf("1.txt 2.csv\n选择导出格式:");
    int choice;
    scanf("%d",&choice);
    switch(choice){
        case 1 :
            printf("输入导出文件名(txt):");
            scanf("%s",FileName);
            fp = fopen(FileName,"w");
            if(!fp){
                printf("创建文件失败");
                return;
            }
            fprintf(fp,"学号\t姓名\t学院\t类型\n");
            while(tt != tailer){
                fprintf(fp,"%s\t%s\t%s\n",tt->studentID,tt->studentName,tt->studentFaculty);
                if(tt->CourseNum > 0)
                    fprintf(fp,"\t\t\t课程成绩\t课程名\t课程号\t课程性质\t学分\t成绩\t绩点\n");
                CourseGradeNode* c;
                for(int i = 0;i < tt->CourseNum;i++){
                    c = tt->gradeNode[i];
                    fprintf(fp,"\t\t\t\t\t%s\t%s\t%s\t%s\t%s\t%s\n",c->CourseName,c->CourseNum,TYPE[(int)c->gradeType],c->CourseCredit,c->CourseGrade,c->GPA);
                }
                fprintf(fp,"\t\t\t\t平均加权绩点:%.2lf\n\n",tt->AverageGrade);
                if(tt->QualityGradeNum > 0)
                    fprintf(fp,"\t\t\t素质项目\n");
                thesis* t;
                project* p;
                contest* c1;
                for(int i = 0;i < tt->QualityGradeNum;i++){
                    switch(tt->QGrade[i]->QualityGradeType){
                        case THESIS :
                            t = tt->QGrade[i]->Thesis;
                            fprintf(fp,"\t\t\t\t论文\t论文名\t出版时间\n");
                            fprintf(fp,"\t\t\t\t\t%s\t%d\t",t->thesisName,t->publicationTime);
                            break;
                        case PROJECT :
                            p = tt->QGrade[i]->Project;
                            fprintf(fp,"\t\t\t\t大创\t项目名\t人员名单\t指导老师\t项目编号\t开题时间\t结题时间\n");
                            fprintf(fp,"\t\t\t\t\t%s\t",p->projrectName);
                            for(int i = 0;i < p->memberNum;i++){
                                fprintf(fp,"%s ",p->members[i]);
                            }
                            fprintf(fp,"\t%s\t%d\t%d\t%d\t",p->instructor,p->itemNum,p->approvalTime,p->endTime);
                            break;
                        case CONTEST :
                            c1 = tt->QGrade[i]->Contest;
                            fprintf(fp,"\t\t\t\t竞赛\t竞赛名\t获奖人\t主办单位\t获奖时间\n");
                            fprintf(fp,"\t\t\t\t\t%s\t%s\t%s\t%d\t",c1->contestName,c1->winners[0],c1->organizer,c1->prizeTIme);
                            break;
                        default :
                            break;
                    }
                    fprintf(fp,"\t认定加分:%.2lf\n",tt->QGrade[i]->recognizedCredit);
                }
                fprintf(fp,"\t\t\t\t总素质加分:%.2lf\n\n",tt->AddQualityGrade);
                fprintf(fp,"\t\t\t\t总绩点:%.2lf\n\n",tt->AverageGrade + tt->AddQualityGrade);
                tt = tt->next;
            }
            printf("导出成功\n");
            fclose(fp);
            break;
        case 2 :
            printf("输入导出文件名(csv):");
            scanf("%s",FileName);
            fp = fopen(FileName,"w");
            if(!fp){
                printf("创建文件失败");
                return;
            }
            fprintf(fp,"学号,姓名,学院,成绩类型\n");
            while(tt != tailer){
                fprintf(fp,"%s,%s,%s\n",tt->studentID,tt->studentName,tt->studentFaculty);
                if(tt->CourseNum > 0)
                    fprintf(fp," , , ,课程成绩,课程名,课程号,课程性质,学分,成绩,绩点\n");
                CourseGradeNode* c;
                for(int i = 0;i < tt->CourseNum;i++){
                    c = tt->gradeNode[i];
                    fprintf(fp," , , , ,%s,%s,%s,%s,%s,%s\n",c->CourseName,c->CourseNum,TYPE[(int)c->gradeType],c->CourseCredit,c->CourseGrade,c->GPA);
                }
                fprintf(fp," , , , ,平均加权绩点:%.2lf\n\n",tt->AverageGrade);
                if(tt->QualityGradeNum > 0)
                    fprintf(fp," , , ,素质项目\n");
                thesis* t;
                project* p;
                contest* c1;
                for(int i = 0;i < tt->QualityGradeNum;i++){
                    switch(tt->QGrade[i]->QualityGradeType){
                        case THESIS :
                            t = tt->QGrade[i]->Thesis;
                            fprintf(fp," , , , ,论文,论文名,出版时间\n");
                            fprintf(fp," , , , , ,%s,%d,",t->thesisName,t->publicationTime);
                            break;
                        case PROJECT :
                            p = tt->QGrade[i]->Project;
                            fprintf(fp," , , , ,大创,项目名,人员名单,指导老师,项目编号,开题时间,结题时间\n");
                            fprintf(fp," , , , , ,%s,",p->projrectName);
                            for(int i = 0;i < p->memberNum;i++){
                                fprintf(fp,"%s ",p->members[i]);
                            }
                            fprintf(fp," ,%s,%d,%d,%d,",p->instructor,p->itemNum,p->approvalTime,p->endTime);
                            break;
                        case CONTEST :
                            c1 = tt->QGrade[i]->Contest;
                            fprintf(fp," , , , ,竞赛,竞赛名,获奖人,主办单位,获奖时间\n");
                            fprintf(fp," , , , , ,%s,%s,%s,%d,",c1->contestName,c1->winners[0],c1->organizer,c1->prizeTIme);
                            break;
                        default :
                            break;
                    }
                    fprintf(fp," ,认定加分:%.2lf\n",tt->QGrade[i]->recognizedCredit);
                }
                fprintf(fp," , , , ,总素质加分:%.2lf\n\n",tt->AddQualityGrade);
                fprintf(fp," , , , ,总绩点:%.2lf\n\n",tt->AverageGrade + tt->AddQualityGrade);
                tt = tt->next;
            }
            printf("导出成功\n");
            fclose(fp);
            break;
    }
    system("pause");
    return;
}

