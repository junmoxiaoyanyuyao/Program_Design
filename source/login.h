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

bool AccountInput_check(char account[30]);
bool PasswordInput_check(char pd[30]);
void registeruser();
void Hello();
void login();
void xor_encrypt_decrypt(char* str, char key);
void Menu();
//תרҵ
void changeFaculty(ListNode*, ListNode*);
void matchFacultyName_list(ListNode*, ListNode*);
extern void matchFacultyName_one(char [3],ListNode*);
extern void Faculty_Search();
extern char* file_s_gets(char*, int, FILE*);
extern char* s_gets(char*, int);
extern bool Input_check(char[100]);