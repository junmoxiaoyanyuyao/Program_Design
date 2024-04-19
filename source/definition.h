#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


#ifndef Definition
#define Definition

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void showMenu();

// 常量定义
#define maxNameFaculty 30 //学院名长度
#define maxNameSize 20 //最大姓名长度
#define maxThesisNameSize 500 //最大论文名长度
#define maxProjectNameSize 500 //最大项目名长度
#define maxTotalNumPerson 10 //大创项目最大人数
#define maxContestNameSize 500 //最大竞赛名长度
#define maxJournalNameSize 500 // 最大期刊名称长度
#define maxConferenceNameSize 500 // 最大会议名称长度
#define maxIssueInfoSize 20 // 最大卷/期/论文号/页码范围信息长度
#define maxGradeType 8 //素质项目最大等级数量
#define maxListNameSize 500
#define maxQualiityGradeNum 10 //一人最大素质项目数量
#define maxCourseNameSize 200 //课程名最大长度
#define maxCOurseNum 100 //最大课程数量
#define CourseNumSize 11 //默认课程号位数10 + '\0'
#define maxQualityAddGrade 0.4



//结构体声明
typedef struct ListNode ListNode; //链表结点
typedef struct QualityGradeNode QualityGradeNode;//素质项目结点
typedef struct thesis thesis;//科研
typedef struct project project;//项目
typedef struct contest contest;//竞赛
typedef struct CourseGradeNode CourseGradeNode;


//枚举类型定义
enum type { THESIS, PROJECT, CONTEST }; //素质项目类型
enum thesisGrade { G1, G2, G3, G4, G5, G6, G7, G8 }; // 论文等级
enum contestGrade { g1, g2, g3, g4, g5, g6, g7, g8 }; //竞赛等级
enum projectGrade { p1, p2, p3, p4, p5, p6, p7, p8 }; //大创等级
enum GradeType { PubRequired, PubElective, ProRequired, ProElective, Revise }; //课程类型:公共必修,公共选修,专业必修,专业选修,再修
struct thesis {
    char thesisName[maxThesisNameSize]; //论文名称
    int publicationTime; //出版时间
    enum thesisGrade Grade; //论文等级

    //卷/期/论文号/页码范围（部分信息可能没有） 尚未添加
    char journalName[maxJournalNameSize]; // 期刊名称
    char conferenceName[maxConferenceNameSize]; // 会议名称
    char issueInfo[maxIssueInfoSize]; // 卷/期/论文号/页码范围（部分信息可能没有）


    //and so on
}; //论文信息结构体定义

struct project {
    int memberNum;
    char members[maxTotalNumPerson][maxNameSize]; //大创名单，[人员顺序][姓名]
    char instructor[maxNameSize]; //指导老师姓名
    char projrectName[maxProjectNameSize]; //项目名
    enum projectGrade proG; //大创等级
    int itemNum; //项目编号
    int approvalTime; //开题时间
    int endTime; // 结题时间



    //and so on
}; //大创

struct contest {
    char contestName[maxContestNameSize]; //竞赛名
    char organizer[maxNameSize]; //主办单位
    char winners[maxTotalNumPerson][maxNameSize];  //所有获奖人 [顺序][姓名]
    bool winnersOrder; // 获奖人是否有先后顺序
    enum contestGrade conG; //竞赛等级
    bool ifCsContest; // 是否是计算机类竞赛
    int prizeTIme; //获奖时间

    //and so on
};// 竞赛

struct QualityGradeNode {
    enum type QualityGradeType; //素质项目类型
    thesis* Thesis;
    project* Project;
    contest* Contest; //对应具体信息指针
    double recognizedCredit; //认定加分

    unsigned long long addTime; //14位时间戳 type:YYYY MM DD HH MM SS

    //and so on
};

struct CourseGradeNode {
    char CourseName[maxCourseNameSize]; //课程名
    char CourseNum[CourseNumSize]; //课程号

    //开课单位 时间  修读方式  是否主修  ...  尚未添加

    enum GradeType gradeType; //课程性质 类型:公共必修,公共选修,专业必修,专业选修,再修

    char CourseCredit[20]; //学分
    char CourseGrade[20]; //成绩
    char GPA[20]; //绩点
};


struct ListNode {
    char studentID[9]; //8位学号
    char studentName[maxNameSize];//学生姓名
    char studentFaculty[maxNameFaculty]; //学院名

    int QualityGradeNum;
    QualityGradeNode* QGrade[maxQualiityGradeNum]; //素质类项目数组
    double AddQualityGrade;

    int CourseNum;
    CourseGradeNode* gradeNode[maxCOurseNum];
    double AverageGrade;


    ListNode* next;
    ListNode* father;
}; //链表

double UpdateGPA(ListNode* t);
double UpdataQualityGrade(ListNode* t);
void GPAMatch(CourseGradeNode* c);

#endif