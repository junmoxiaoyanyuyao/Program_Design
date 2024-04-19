#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

// #ifndef Definition
// #define Definition
#include "definition.h"
// #endif


extern bool str_same_cmp(char*, char*);
extern char* s_gets(char*, int);
extern bool Input_check(char[100]);
extern char* file_s_gets(char*, int, FILE*);

void guide_information(ListNode*, ListNode*);
void single_Inquire(ListNode*, ListNode*);
void faculty_Inquire(ListNode*, ListNode*);
void file_Inquire(ListNode*, ListNode*);
void Print_stu_credit(ListNode*);
extern void Print_stu_Information(ListNode*, int, FILE*, int);
void Print_stu_Grade(ListNode*);
int compare_grade(const void*, const void*);
void delete_Information(ListNode*, ListNode*);

void sort_cmp_grade(ListNode*, ListNode*,char[30],int,FILE*);

extern void Faculty_Search();
extern void matchFacultyName_one(char [3],ListNode*);