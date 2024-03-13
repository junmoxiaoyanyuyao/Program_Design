#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct thesis; //thesis information
struct project; //project information
struct contest; //contest information

struct gradeList{
    static const int maxNameSize  = 20;
    int studentID; //8-digit Student ID
    char studentName[maxNameSize]; //Student Name
    enum type{THESIS,PROJECT,CONTEST}; //enum type
    thesis* Thesis = nullptr;
    project* Project = nullptr;
    contest* Contest = nullptr;  //record quality item
    double recognizedCredit; //grade
    int addTime; //12-digit type:YY MM DD HH MM SS

    //and so on
};

struct thesis{
    static const int maxNameSize  = 20;
    static const int maxTotalNumPerson = 10;
    static const int maxThesisNameSize = 40;

    char thesisName[maxThesisNameSize];
    int publicationTime;

    //卷/期/论文号/页码范围（部分信息可能没有） 尚未添加

    enum grade{G1,G2,G3,G4,G5,G6}; //

    //and so on
};

struct project{
    static const int maxNameSize  = 20;
    static const int maxTotalNumPerson = 10;
    static const int maxProjectNameSize = 50;
    char members[maxTotalNumPerson][maxNameSize];
    char instructor[maxNameSize]; // instruct teacher
    char projrectName[maxProjectNameSize]; // name of project
    int itemNum;
    int approvalTime; //time of beign
    int endTime; // time of end

    //and so on
};

struct contest{
    static const int maxNameSize  = 20;
    static const int maxTotalNumPerson = 10; // max total number of person of a single ocntest
    static const int maxContestNameSize = 30;
    
    char contestName[maxContestNameSize];
    char organizer[maxNameSize];
    char winners[maxTotalNumPerson][maxNameSize]; 
    bool winnersOrder = false; // record whether the winners have an order
    enum grade{A1,A2,A3,B1,B2,B3,C1,C2,C3};
    bool ifCsContest; // record whether the contest belong to CS
    int prizeTIme;

    //and so on
};