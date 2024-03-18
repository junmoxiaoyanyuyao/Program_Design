#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct ListNode;
struct gradeNode;
struct thesis; //thesis information
struct project; //project information
struct contest; //contest information

#define maxNameSize 20
#define maxThesisNameSize 40
#define maxProjectNameSize 50
#define maxTotalNumPerson 10 // max total number of person of a single ocntest
#define maxContestNameSize 30
enum type{THESIS,PROJECT,CONTEST}; //enum type
enum projectGrade{G1,G2,G3,G4,G5,G6}; //
enum contestGrade{A1,A2,A3,B1,B2,B3,C1,C2,C3};


//function definition
void Insert();
void fileInsert();