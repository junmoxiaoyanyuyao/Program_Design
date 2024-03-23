#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//结构体声明
typedef struct ListNode ListNode; //链表结点
typedef struct gradeNode gradeNode;//成绩结点
typedef struct thesis thesis;//科研
typedef struct project project;//项目
typedef struct contest contest;//竞赛

// 常量定义
#define maxNameFaculty 30 //学院名长度
#define maxNameSize 20 //最大姓名长度
#define maxThesisNameSize 40 //最大论文名长度
#define maxProjectNameSize 50 //最大项目名长度
#define maxTotalNumPerson 10 //大创项目最大人数
#define maxContestNameSize 30 //最大竞赛名长度
#define maxJournalNameSize 40 // 最大期刊名称长度
#define maxConferenceNameSize 40 // 最大会议名称长度
#define maxIssueInfoSize 20 // 最大卷/期/论文号/页码范围信息长度

//枚举类型定义
enum type{THESIS,PROJECT,CONTEST}; //素质项目类型
enum thesisGrade{G1,G2,G3,G4,G5,G6}; // 论文等级
enum contestGrade{g1,g2,g3,g4,g5}; //竞赛分类

//等级
extern double TheGrade[6];
extern double ConGrade[5];
extern char TheGName[6][500];
extern char ConGName[5][500];


//函数声明
// void showMenu(); //菜单
 

 //功能正在新建文件夹
void Insert(ListNode**);


//Insert函数声明
void fileInsert(ListNode**);
void singleInsert(ListNode**);
void duqu(ListNode**,FILE*);
void fileGetLineOne(gradeNode*,FILE**);
int gradeNodeJudge(char*);
project* projectFileInput(FILE**);
void projectSingleInput(gradeNode*);
void thesisSingleInput(gradeNode*);
void contestSingleInput(gradeNode*);
void pipei(gradeNode*);
void GradeInput(ListNode*,ListNode*);


//结构体定义

struct thesis{
    char thesisName[maxThesisNameSize]; //论文名称
    int publicationTime; //出版时间
    enum thesisGrade Grade; //论文等级

    //卷/期/论文号/页码范围（部分信息可能没有） 尚未添加
    char journalName[maxJournalNameSize]; // 期刊名称
    char conferenceName[maxConferenceNameSize]; // 会议名称
    char issueInfo[maxIssueInfoSize]; // 卷/期/论文号/页码范围（部分信息可能没有）

    
    //and so on
}; //论文信息结构体定义

struct project{
    int memberNum;
    char members[maxTotalNumPerson][maxNameSize]; //大创名单，[人员顺序][姓名]
    char instructor[maxNameSize]; //指导老师姓名
    char projrectName[maxProjectNameSize]; //项目名
    int itemNum; //项目编号
    int approvalTime; //开题时间
    int endTime; // 结题时间
    


    //and so on
}; //大创

struct contest{
    char contestName[maxContestNameSize]; //竞赛名
    char organizer[maxNameSize]; //主办单位
    char winners[maxTotalNumPerson][maxNameSize];  //所有获奖人 [顺序][姓名]
    bool winnersOrder; // 获奖人是否有先后顺序
    enum contestGrade conG; //竞赛等级
    bool ifCsContest; // 是否是计算机类竞赛
    int prizeTIme; //获奖时间

    //and so on
};// 竞赛

struct gradeNode{
    char studentID[9]; //8位学号
    char studentName[maxNameSize];//学生姓名
    enum type gradeType; //素质项目类型
    thesis* Thesis;
    project* Project;
    contest* Contest; //对应具体信息指针
    double recognizedCredit; //认定加分

    char addTime[13]; //12位时间戳 type:YY MM DD HH MM SS

    //and so on
};

struct ListNode{
    gradeNode* t;
    ListNode* next;
}; //链表

