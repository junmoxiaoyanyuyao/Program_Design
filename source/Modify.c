
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "definition.h"
#include "Modify.h"

char CourseType[5][20] = {
    "公共必修",
    "公共选修",
    "专业必修",
    "专业选修",
    "挂科再修"
};

void CourseGradeModify(ListNode* t){
    CourseGradeNode* c;
    for(int i = 0;i < (t->CourseNum);i++){
        c = t->gradeNode[i];
        printf("%d\t",i + 1);
        printf("课程名:%s\t课程号:%s\t课程类型:%s\t",c->CourseName,c->CourseNum,CourseType[c->gradeType]);
        printf("学分:%s\t成绩:%s\t绩点:%s\n",c->CourseCredit,c->CourseGrade,c->GPA);
    }
    printf("请输入想修改条目的编号:");
    int index;
    scanf("%d",&index);
    while(index < 1 || index > t->CourseNum){
        printf("编号错误,重新输入:");
        scanf("%d",&index);
    }

    c = t->gradeNode[index - 1];

    printf("1.课程名\t2.课程号\t3.课程类型\t4.学分\t5.成绩\t6.返回\n");
LOOP:
    printf("请输入想要修改哪条数据:");
    scanf("%d",&index);
    while(index < 1 && index > 6){
        printf("编号错误,重新输入:");
        scanf("%d",&index);        
    }
    char info[100];
    char* ptr;
    switch(index){
        case 1 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseName);
            printf("输入修改后的课程名:");
            scanf("%s",c->CourseName);
            printf("修改成功,%s->%s\n",info,c->CourseName);
            break;
        case 2 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseNum);
            printf("输入修改后的课程号:");
            scanf("%s",c->CourseNum);
            printf("修改成功,%s->%s\n",info,c->CourseName);
            break;
        case 3 : 
            printf("1.公共必修\t2.公共选修\t3.专业必修\t4.专业选修\t5.再修\n");
            printf("输入修改后的课程类型:");
            int d = c->gradeType;
            scanf("%d",&(c->gradeType));
            while(c->gradeType < 0 || c->gradeType > 4){
                printf("错误,请重新输入:");
                scanf("%d",&(c->gradeType));
            }
            c->gradeType--;
            printf("修改成功,%s->%s\n",CourseType[d],CourseType[c->gradeType]);
            t->AverageGrade = UpdateGPA(t);
            break;
        case 4 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseCredit);
            printf("输入修改后的学分:");
            scanf("%s",c->CourseCredit);
            while(strtod(c->CourseCredit,&ptr) < 0.0){
                printf("输入学分为负数,请重新输入:");
                scanf("%s",c->CourseCredit);
            }
            printf("修改成功,%s->%s\n",info,c->CourseCredit);
            t->AverageGrade = UpdateGPA(t);
            break;
        case 5 : 
            memset(info,'\0',sizeof(info));
            strcpy(info,c->CourseGrade);
            printf("输入修改后的成绩:");
            scanf("%s",c->CourseGrade);
            double grade = strtod(c->CourseGrade,&ptr);
            while(grade < 0.0 || grade > 100.0){
                printf("成绩应在0~100之间,请重新输入:");
                scanf("%s",c->CourseGrade);
                grade = strtod(c->CourseGrade,&ptr);
            }
            printf("修改成功,%s->%s\n",info,c->CourseGrade);
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
                printf("论文\t论文名:%s\t出版时间:%d\n",t->thesisName,t->publicationTime);
                break;
            case PROJECT :
                p = q->Project;
                printf("大创\t人员名单:");
                for(int j = 0;j < p->memberNum;j++)
                    printf("%s ",p->members[j]);
                printf("\t项目名:%s\t项目编号:%d\t开题时间:%d\t结题时间:%d\n",p->projrectName,p->itemNum,p->approvalTime,p->endTime);
                break;
            case CONTEST :
                c = q->Contest;
                printf("竞赛\t竞赛名:%s\t主办单位:%s\t",c->contestName,c->organizer);
                printf("获奖名单:");
                for(int j = 0;c->winners[j][0] != '\0';j++)
                    printf("%s ",c->winners[j]);
                printf("\t获奖时间:%d\n",c->prizeTIme);
                break;
            default :
                break;
        }
        
    }
LOOP:
    int index;
    printf("输入想修改信息的编号(输入'0'返回):");
    scanf("%d",&index);
    if(index == 0)
        return;
    while(index < 1 || index > node->QualityGradeNum){
        printf("编号错误,重新输入:");
        scanf("%d",&index);
    }
    q = node->QGrade[index - 1];
    switch(q->QualityGradeType){
        case THESIS :
            printf("1.论文名称\t2.出版时间\t3.返回\n");
            printf("请选择想修改的信息:");
            scanf("%d",&index);
            switch(index){
                case 1 : 
                    printf("请输入修改后的论文名称:");
                    scanf("%s",q->Thesis->thesisName);
                    printf("修改成功\n");
                    break;
                case 2 :
                    printf("请输入修改后的出版时间:");
                    scanf("%s",q->Thesis->thesisName);
                    printf("修改成功\n");
                    goto LOOP;
                    break;
                case 3 :
                    break;
                default :
                    break;
            }
            break;
        case PROJECT :
            printf("1.项目名\t2.人员名单\t3.指导老师\t4.项目编号\t5.开题时间\t6.结题时间\t7.返回\n");
            printf("请输入想修改的信息");
            scanf("%d",&index);
            switch(index){
                case 1 : 
                    printf("请输入修改后的项目名称:");
                    scanf("%s",q->Project->projrectName);
                    printf("修改成功\n");
                    break;
                case 2 :
                    printf("请输入修改后的人员名单人数:");
                    scanf("%d",&(q->Project->memberNum));
                    printf("请输入修改后的人员名单:");
                    for(int i = 0;i < q->Project->memberNum;i++)
                        scanf("%s",q->Project->members[i]);
                    printf("修改成功\n");
                    break;
                case 3 :
                    printf("请输入修改后的指导老师:");
                    scanf("%s",q->Project->instructor);
                    printf("修改成功\n");
                    break;
                case 4 :
                    printf("请输入修改后的项目编号:");
                    scanf("%s",q->Project->itemNum);
                    printf("修改成功\n");
                    break;
                case 5 :
                    printf("请输入修改后的开题时间:");
                    scanf("%d",&(q->Project->approvalTime));
                    printf("修改成功\n");
                    break;
                case 6 :
                    printf("请输入修改后的结题时间:");
                    scanf("%d",&(q->Project->endTime));
                    printf("修改成功\n");
                case 7 :
                    break;
                default :
                    break;
            }
            break;
        case CONTEST :
            printf("1.竞赛名\t2.主办单位\t3.获奖名单\t4.获奖时间\t5.返回\n");
            printf("请输入想修改的选项:");
            scanf("%d",&index);
            switch(index){
                case 1 : 
                    printf("请输入修改后的竞赛名:");
                    scanf("%s",q->Contest->contestName);
                    printf("修改成功\n");
                    break;
                case 2 :
                    printf("请输入修改后的主办单位名称:");
                    scanf("%s",q->Contest->organizer);
                    printf("修改成功\n");
                    break;
                case 3 :
                    printf("请输入修改后的获奖名单人数:");
                    scanf("%d",&index);
                    for(int i = 0;i < index;i++)
                        scanf("%s",q->Contest->winners);
                    printf("修改成功\n");
                    break;
                case 4 :
                    printf("请输入修改后的获奖时间:");
                    scanf("%d",&(q->Contest->prizeTIme));
                    printf("修改成功\n");
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
    // printf("修改成功\n");
    return;
}

void Modify(ListNode* head,ListNode* tailer){
    printf("请输入想修改信息的学号('#'返回):");
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
        printf("学号不存在,返回\n");
        return;
    }
    printf("查找成功\n学号:%s\t姓名:%s\n",t->studentID,t->studentName);
LOOP:
    int choose;
    printf("1.成绩 2.素质 3.返回\n请输入你想修改的类型:");
    scanf("%d",&choose);
    switch(choose){
        case 1 :
            if(t->CourseNum == 0)
                printf("无可修改数据,返回\n");
            else{
                CourseGradeModify(t);
                goto LOOP;
            }
            break;
        case 2 :
            if(t->QualityGradeNum == 0)
                printf("无可修改数据,返回\n");
            else{
                QualityGradeModify(t);
                goto LOOP;
            }
            break;
        case 3 :
            break;
        default :
            printf("错误,返回\n");
            break;
    }
    return;
}

