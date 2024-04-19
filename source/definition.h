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

void Menu();

// ��������
#define maxNameFaculty 30 //ѧԺ������
#define maxNameSize 20 //�����������
#define maxThesisNameSize 500 //�������������
#define maxProjectNameSize 500 //�����Ŀ������
#define maxTotalNumPerson 10 //����Ŀ�������
#define maxContestNameSize 500 //�����������
#define maxJournalNameSize 500 // ����ڿ����Ƴ���
#define maxConferenceNameSize 500 // ���������Ƴ���
#define maxIssueInfoSize 20 // ����/��/���ĺ�/ҳ�뷶Χ��Ϣ����
#define maxGradeType 8 //������Ŀ���ȼ�����
#define maxListNameSize 500
#define maxQualiityGradeNum 10 //һ�����������Ŀ����
#define maxCourseNameSize 200 //�γ�����󳤶�
#define maxCOurseNum 100 //���γ�����
#define CourseNumSize 11 //Ĭ�Ͽγ̺�λ��10 + '\0'
#define maxQualityAddGrade 0.4



//�ṹ������
typedef struct ListNode ListNode; //������
typedef struct QualityGradeNode QualityGradeNode;//������Ŀ���
typedef struct thesis thesis;//����
typedef struct project project;//��Ŀ
typedef struct contest contest;//����
typedef struct CourseGradeNode CourseGradeNode;


//ö�����Ͷ���
enum type { THESIS, PROJECT, CONTEST }; //������Ŀ����
enum thesisGrade { G1, G2, G3, G4, G5, G6, G7, G8 }; // ���ĵȼ�
enum contestGrade { g1, g2, g3, g4, g5, g6, g7, g8 }; //�����ȼ�
enum projectGrade { p1, p2, p3, p4, p5, p6, p7, p8 }; //�󴴵ȼ�
enum GradeType { PubRequired, PubElective, ProRequired, ProElective, Revise }; //�γ�����:��������,����ѡ��,רҵ����,רҵѡ��,�ҿ�����
struct thesis {
    char thesisName[maxThesisNameSize]; //��������
    int publicationTime; //����ʱ��
    enum thesisGrade Grade; //���ĵȼ�

    //��/��/���ĺ�/ҳ�뷶Χ��������Ϣ����û�У� ��δ���
    char journalName[maxJournalNameSize]; // �ڿ�����
    char conferenceName[maxConferenceNameSize]; // ��������
    char issueInfo[maxIssueInfoSize]; // ��/��/���ĺ�/ҳ�뷶Χ��������Ϣ����û�У�


    //and so on
}; //������Ϣ�ṹ�嶨��

struct project {
    int memberNum;
    char members[maxTotalNumPerson][maxNameSize]; //��������[��Ա˳��][����]
    char instructor[maxNameSize]; //ָ����ʦ����
    char projrectName[maxProjectNameSize]; //��Ŀ��
    enum projectGrade proG; //�󴴵ȼ�
    int itemNum; //��Ŀ���
    int approvalTime; //����ʱ��
    int endTime; // ����ʱ��



    //and so on
}; //��

struct contest {
    char contestName[maxContestNameSize]; //������
    char organizer[maxNameSize]; //���쵥λ
    char winners[maxTotalNumPerson][maxNameSize];  //���л��� [˳��][����]
    bool winnersOrder; // �����Ƿ����Ⱥ�˳��
    enum contestGrade conG; //�����ȼ�
    bool ifCsContest; // �Ƿ��Ǽ�����ྺ��
    int prizeTIme; //��ʱ��

    //and so on
};// ����

struct QualityGradeNode {
    enum type QualityGradeType; //������Ŀ����
    thesis* Thesis;
    project* Project;
    contest* Contest; //��Ӧ������Ϣָ��
    double recognizedCredit; //�϶��ӷ�

    unsigned long long addTime; //14λʱ��� type:YYYY MM DD HH MM SS

    //and so on
};

struct CourseGradeNode {
    char CourseName[maxCourseNameSize]; //�γ���
    char CourseNum[CourseNumSize]; //�γ̺�

    //���ε�λ ʱ��  �޶���ʽ  �Ƿ�����  ...  ��δ���

    enum GradeType gradeType; //�γ����� ����:��������,����ѡ��,רҵ����,רҵѡ��,����

    char CourseCredit[20]; //ѧ��
    char CourseGrade[20]; //�ɼ�
    char GPA[20]; //����
};


struct ListNode {
    char studentID[9]; //8λѧ��
    char studentName[maxNameSize];//ѧ������
    char studentFaculty[maxNameFaculty]; //ѧԺ��

    int QualityGradeNum;
    QualityGradeNode* QGrade[maxQualiityGradeNum]; //��������Ŀ����
    double AddQualityGrade;

    int CourseNum;
    CourseGradeNode* gradeNode[maxCOurseNum];
    double AverageGrade;


    ListNode* next;
    ListNode* father;
}; //����

double UpdateGPA(ListNode* t);
double UpdataQualityGrade(ListNode* t);
void GPAMatch(CourseGradeNode* c);

#endif