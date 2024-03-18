#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "definition.h"


typedef struct thesis{
    

    char thesisName[maxThesisNameSize];
    int publicationTime;

    //卷/期/论文号/页码范围（部分信息可能没有） 尚未添加

    

    //and so on
}thesis;

typedef struct project{
    
    char members[maxTotalNumPerson][maxNameSize];
    char instructor[maxNameSize]; // instruct teacher
    char projrectName[maxProjectNameSize]; // name of project
    int itemNum;
    int approvalTime; //time of beign
    int endTime; // time of end
    enum projectGrade proG;


    //and so on
}project;

typedef struct contest{
    char contestName[maxContestNameSize];
    char organizer[maxNameSize];
    char winners[maxTotalNumPerson][maxNameSize]; 
    bool winnersOrder; // record whether the winners have an order
    enum contestGrade conG;
    bool ifCsContest; // record whether the contest belong to CS
    int prizeTIme;

    //and so on
}contest;

typedef struct gradeNode{
    int studentID; //8-digit Student ID
    char studentName[maxNameSize];//Student Name
    enum type gradeType;
    thesis* Thesis;
    project* Project;
    contest* Contest;  //record quality item
    double recognizedCredit; //grade
    int addTime; //12-digit type:YY MM DD HH MM SS

    //and so on
}gradeNode;



typedef struct ListNode{
    struct gradeNode* t;
}ListNode;


void Insert(){
    printf("Choose option : 1.file input 2.single input 3.quit\n");
    printf("input:");
    int a;
    while(scanf("%d",&a) && (a > 3 || a < 1)){
        printf("again\nChoose option : 1.file input 2.single input 3.quit\n");
        printf("input:");
    }
    switch(a){
        case 1 : fileInsert();
                    break;
        case 2 : break;
        case 3 : return;
        default : printf("fault\n");
                    break;
    }
}

void fileInsert(){
    char filePath[50];
    printf("input filePath : ");
    scanf("%s",&filePath);
    FILE *fp = fopen(filePath,"r");
    if(!fp){
        printf("fault");
    }
    else{
        printf("corr");
    }
    return;
}