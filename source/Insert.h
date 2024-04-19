#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#ifndef Definition
#define Definition
#include "definition.h"
#endif


#ifndef INSERT
#define INSERT

#define maxFailNum 5 //最大错误次数
#define maxSwitchChoiceSIze 11

//素质类默认信息声明
extern double TheGrade[maxGradeType]; //默认论文等级加分数组
extern double ConGrade[maxGradeType]; //默认竞赛等级加分数组
extern double ProGrade[maxGradeType]; //默认大创等级加分数组
extern char TheGName[maxGradeType][maxListNameSize]; //论文作者名单
extern char ConGName[maxGradeType][maxListNameSize]; //竞赛获奖名单
extern char ProGName[maxGradeType][maxListNameSize]; //大创项目名单
extern int maxThesisGradeKind; //论文等级数量
extern int maxContestGradeKind; //竞赛等级数量
extern int maxProjectGradeKind; //大创等级数量

//成绩信息声明
extern char GPA[11][4];
extern char CourseType[4][20];


//Insert函数声明
void Insert(ListNode* head,ListNode* tailer,ListNode** currentNode);

//素质类输入函数声明
void QualityFileInsert(ListNode* head,ListNode* tailer,ListNode** currentNode);
void QualitySingleInsert(ListNode* head,ListNode* tailer,ListNode** currentNode);
void QualityFileInput(ListNode* head,ListNode* tailer,ListNode** currentNode,FILE* fp);
bool projectFileInput(FILE** f,project** p);
bool thesisFileInput(FILE** f,thesis** t);
bool contestFileInput(FILE** f,contest** c);
void projectSingleInput(QualityGradeNode*);
void thesisSingleInput(QualityGradeNode*);
void contestSingleInput(QualityGradeNode*);
void QualityGradeMatch(QualityGradeNode*);
void QualityGradeInput(ListNode* head,ListNode* tailer);

//成绩输入函数声明
void CourseFileInsert(ListNode* head,ListNode* tailer,ListNode** currentNode);
void CourseFileInput(ListNode* head,ListNode* tailer,ListNode** currentNode,FILE* fp);
void CourseSingleInsert(ListNode* head,ListNode* tailer,ListNode** currentNode);

//功能函数声明
bool InsertIDsearch(ListNode* head,ListNode* tailer,ListNode** currentNode,char* info); //搜索结点
unsigned long long GetTime(); //获取时间
void ErrGetLine(); //异常处理吞噬错误输入整行
bool CorrectCourseNum(char* info); //正确的课程编号
bool SwitchCheck(char* choice);


#endif