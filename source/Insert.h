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

#define maxFailNum 5 //���������
#define maxSwitchChoiceSIze 11

//������Ĭ����Ϣ����
extern double TheGrade[maxGradeType]; //Ĭ�����ĵȼ��ӷ�����
extern double ConGrade[maxGradeType]; //Ĭ�Ͼ����ȼ��ӷ�����
extern double ProGrade[maxGradeType]; //Ĭ�ϴ󴴵ȼ��ӷ�����
extern char TheGName[maxGradeType][maxListNameSize]; //������������
extern char ConGName[maxGradeType][maxListNameSize]; //����������
extern char ProGName[maxGradeType][maxListNameSize]; //����Ŀ����
extern int maxThesisGradeKind; //���ĵȼ�����
extern int maxContestGradeKind; //�����ȼ�����
extern int maxProjectGradeKind; //�󴴵ȼ�����

//�ɼ���Ϣ����
extern char GPA[11][4];
extern char CourseType[4][20];


//Insert��������
void Insert(ListNode* head,ListNode* tailer,ListNode** currentNode);

//���������뺯������
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

//�ɼ����뺯������
void CourseFileInsert(ListNode* head,ListNode* tailer,ListNode** currentNode);
void CourseFileInput(ListNode* head,ListNode* tailer,ListNode** currentNode,FILE* fp);
void CourseSingleInsert(ListNode* head,ListNode* tailer,ListNode** currentNode);

//���ܺ�������
bool InsertIDsearch(ListNode* head,ListNode* tailer,ListNode** currentNode,char* info); //�������
unsigned long long GetTime(); //��ȡʱ��
void ErrGetLine(); //�쳣�������ɴ�����������
bool CorrectCourseNum(char* info); //��ȷ�Ŀγ̱��
bool SwitchCheck(char* choice);


#endif