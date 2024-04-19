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

#define RECYCLE_BIN_SIZE 5  // ����վ�Ĵ�С
typedef struct RecycleBinEntry {
    ListNode* node;
    time_t deletionTime;  // ʱ�������¼ɾ��ʱ��ʱ��
} RecycleBinEntry;
// extern RecycleBinEntry recycleBin[RECYCLE_BIN_SIZE]; // ����վ����
extern int recycleBinIndex; // ��ǰ����վ������

extern bool str_same_cmp(char*, char*);
extern char* s_gets(char*, int);
extern bool Input_check(char[100]);
extern void Print_stu_Information(ListNode*, int, FILE*, int);

void delete_factor(ListNode*head,ListNode*tailer);
void delete_Information(ListNode*, ListNode*);
void printRecycleBin();
void Delete_guide(ListNode*,ListNode*);