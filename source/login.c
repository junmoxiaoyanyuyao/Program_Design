#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "login.h"
#include "inquire.h"

void xor_encrypt_decrypt(char* str, char key) {
    while (*str != '\0') {
        *str = *str ^ key;
        str++;
    }
}

bool AccountInput_check(char account[30]) {
	int flag = 0;
	if (account[12]!='\0')flag = 1;
	else {
        int i = 0;
		for (i = 0; account[i] != '\0'; i++) {
			if (!((account[i] >= '0' && account[i] <= '9') || (account[i] >= 'a' && account[i] <= 'z') || (account[i] >= 'A' && account[i] <= 'Z'))) {
				flag = 1;
				break;
			}
		}
        if (i <= 5)flag = 1;
	}
	if (flag) {
        return false;
	}
	else return true;
}


bool PasswordInput_check(char pd[30]) {
    int flag = 0; 
    int i = 0;
    if (pd[12] != '\0') {
        flag = 1;
    }
    else {
        for (i = 0; pd[i] != '\0'; i++) {
            if (!((pd[i] >= '0' && pd[i] <= '9') || (pd[i] >= 'a' && pd[i] <= 'z') ||
                (pd[i] >= 'A' && pd[i] <= 'Z') || pd[i] == '!' || pd[i] == '@' || pd[i] == '#' ||
                pd[i] == '$' || pd[i] == '%' || pd[i] == '^' || pd[i] == '&' || pd[i] == '*' ||
                pd[i] == '(' || pd[i] == ')' || pd[i] == '-' || pd[i] == '_' || pd[i] == '+' ||
                pd[i] == '=' || pd[i] == '[' || pd[i] == ']' || pd[i] == '{' || pd[i] == '}' ||
                pd[i] == ';' || pd[i] == ':' || pd[i] == ',' || pd[i] == '.' || pd[i] == '<' ||
                pd[i] == '>' || pd[i] == '/' || pd[i] == '?' || pd[i] == '\\' || pd[i] == '|')) {
                flag = 1; 
                break;
            }
        }
        if (i < 6) {
            flag = 1;
        }
    }
    if (flag) {
        return false; // 如果flag为1，返回false
    }
    else {
        return true; // 如果flag为0，返回true
    }
}


void Hello()
{   
    while (true) {
        char choice[100];
        memset(choice, 0, sizeof(choice));
        printf("********************************************\n");
        printf("********学生成绩信息管理系统登录界面********\n");
        printf("********************************************\n\n");
        printf("\t\t1.-登录账号-\n");
        printf("\t\t2.-注册账号-\n");
        printf("\t\t3.-退出界面-\n\n");
        printf("******************欢迎使用******************\n");
        printf("请选择：");
        s_gets(choice, 100);
        int flag1 = str_same_cmp(choice, "1");
        int flag2 = str_same_cmp(choice, "2");
        int flag3 = str_same_cmp(choice, "3");
        while (!flag1 && !flag2 && !flag3) {
            system("cls");
            printf("输入非法！请重新尝试！\n");
            system("pause");
            system("cls");
            printf("********************************************\n");
            printf("********学生成绩信息管理系统登录界面********\n");
            printf("********************************************\n\n");
            printf("\t\t1.-登录账号-\n");
            printf("\t\t2.-注册账号-\n");
            printf("\t\t3.-退出界面-\n\n");
            printf("******************欢迎使用******************\n");
            printf("请选择：");
            memset(choice, 0, sizeof(choice));
            s_gets(choice, 100);
            flag1 = str_same_cmp(choice, "1");
            flag2 = str_same_cmp(choice, "2");
            flag3 = str_same_cmp(choice, "3");
        }
        if (flag1) {
            login();
        }
        else if (flag2) {
            registeruser();
        }
        else if (flag3) {
            printf("\n\t\t【成功退出】\n");
            exit(0);
            system("pause");
        }
    }
}

// 注册账号功能 
void registeruser(){
    char account[30];
    char pw[30];
    memset(account, 0, sizeof(account));
    memset(pw, 0, sizeof(pw));
    printf("\t\t【注册帐号】\n");
    FILE* fp = fopen("account.txt", "a+");
    if (fp == NULL) {
        printf("打开文件失败！\n");
        return;
    }
    memset(account,0, sizeof(account));
    printf("请输入用户账号和密码(账号只能为数字和英文字母，密码可以为数字,英文字母,符号。账号、密码最少6位，最多12位)\n\n\n");
    printf("\t请输入账号：");
    s_gets(account, 30);
    if (!AccountInput_check(account)) {
        printf("账号输入非法\n");
        Sleep(1000);
        system("cls");
        return;
    }
    char existing_account[30];
    int i = 1;
    while (file_s_gets(existing_account,30,fp)!=NULL) {
        xor_encrypt_decrypt(existing_account, 'K');  // 解密账号
        if (i%2==1&&str_same_cmp(existing_account, account) == 1) {
            fclose(fp);
            printf("账号已被注册\n");
            Sleep(1000);
            system("cls");
            return;
        }
        i++;
    }
    printf("\n\t请输入密码：");
    memset(pw, 0, sizeof(pw));
    s_gets(pw, 30);
    if (!PasswordInput_check(pw)) {
        printf("密码输入非法\n");
        Sleep(1000);
        system("cls");
        return;
    }
    printf("\n\n\t再次确认密码：");
    char pd[30];
    memset(pd, 0, sizeof(pd));
    s_gets(pd, 30);
    for (i = 0; i < sizeof(pw); i++) {
        if (pd[i] != pw[i]) {
            printf("两次密码输入不一致\n");
            Sleep(1000);
            system("cls");
            return;
        }
    }
   
    xor_encrypt_decrypt(account, 'K');  // 使用密钥'K'加密账号
    xor_encrypt_decrypt(pw, 'K');       // 使用密钥'K'加密密码
    fprintf(fp, "%s\n", account);       // 存储加密后的账号
    fprintf(fp, "%s\n", pw);            // 存储加密后的密码
	fclose(fp);

	printf("注册成功！\n");
	printf("按任意键返回登录界面\n");
	system("pause");
	system("cls");
    return;
}


//登录账号功能 
void login(){
    char account[30];
    char pw[30];
    printf("--------【登录账号】--------\n");
    FILE* fp;
    fp = fopen("account.txt", "r");
    if(fp==NULL){
		printf("打开文件失败！\n");
        Sleep(1000);
		return;
	}
    printf("请输入帐号:");
    memset(account, 0, sizeof(account));
    s_gets(account, 30);
    if (!AccountInput_check(account)) {
        printf("账号输入非法\n");
        Sleep(1000);
        system("cls");
        return;
    }

    printf("请输入密码:");
    memset(pw, 0, sizeof(pw));
    s_gets(pw, 30);
    if (!PasswordInput_check(pw)) {
        printf("密码输入非法\n");
		Sleep(1000);
		system("cls");
		return;
    }
    char existing_account[30];
    char existing_pw[30];
    int i = 1;
    while (file_s_gets(existing_account, 30, fp) != NULL){
        xor_encrypt_decrypt(existing_account, 'K');  // 解密账号
        if (i % 2 == 1 && str_same_cmp(existing_account, account) == 1) {
            i++;
            file_s_gets(existing_pw, 30, fp);
            xor_encrypt_decrypt(existing_pw, 'K');  // 解密密码
            int wrongtime = 0;
            while(wrongtime<=3){
				if (str_same_cmp(existing_pw, pw) == 1) {
					printf("登录成功！\n");
					printf("按任意键进入学生信息管理系统!\n");
					system("pause");
					system("cls");
					Menu();
					system("pause");
					system("cls");
                    return;
				}
				else {
					printf("密码错误！你还有%d次机会，请重新输入:", 4 - wrongtime);
					memset(pw, 0, sizeof(pw));
					s_gets(pw, 30);
					wrongtime++;
				}
			}
            if (wrongtime == 4) {
                printf("密码错误次数过多！\n");
                Sleep(1000);
                system("cls");
                return;
            }
        }
        i++;
    }
    printf("账号未注册！\n");
    Sleep(1000);
    system("cls");
    return;
}



void changeFaculty(ListNode* head, ListNode* tailer) {
    printf("请输入转专业学生的学号:");
    char studentID[100];
    memset(studentID, 0, sizeof(studentID));
    s_gets(studentID, 100);
    if (!Input_check(studentID)) {
        return;
    }
    ListNode* p = head->next;
    while (p != tailer) {
        if (str_same_cmp(p->studentID, studentID)) {
            Faculty_Search();
            printf("请输入该学生转后学院编号(输入-1返回主菜单):");
            char number[100];
            memset(number, 0, sizeof(number));
            s_gets(number, 100);
            int flag = 0;
            if (number[2] != '\0')flag = 1;
            else if (number[0] < '0' || number[0]>'9' || number[1] < '0' || number[1]>'9')flag = 1;
            if (number[0] == '-' && number[1] == '1') {
                system("cls");
                return;
            }
            while (flag) {
                system("cls");
                printf("编号输入非法！\n");
                Sleep(1000);
                Faculty_Search();
                printf("请输入该学生转后学院编号(输入-1返回主菜单):");
                memset(number, 0, sizeof(number));
                s_gets(number, 100);
                flag = 0;
                if (number[2] != '\0')flag = 1;
                else if (number[0] < '0' || number[0]>'9' || number[1] < '0' || number[1]>'9')flag = 1;
            }

            matchFacultyName_one(number, p);
            printf("已修改该学生学院信息！\n");
            break;
        }
        p = p->next;
    }
    if (p == tailer) {
        printf("未找到该学生信息！\n");
        return;
    }
}
//学院识别学号

void matchFacultyName_list(ListNode* head, ListNode* tailer) {
    ListNode* node = head->next;
    while (node != tailer) {
        // 判断学号前两位
        char prefix[3];
        strncpy(prefix, node->studentID, 2);
        prefix[2] = '\0';
        // 匹配学院名
        if (str_same_cmp(prefix, "01")) {
            strcpy(node->studentFaculty, "哲学社会");
        }
        else if (str_same_cmp(prefix, "02")) {
            strcpy(node->studentFaculty, "文学");
        }
        else if (str_same_cmp(prefix, "03")) {
            strcpy(node->studentFaculty, "外国语");
        }
        else if (str_same_cmp(prefix, "04")) {
            strcpy(node->studentFaculty, "艺术");
        }
        else if (str_same_cmp(prefix, "05")) {
            strcpy(node->studentFaculty, "体育");
        }
        else if (str_same_cmp(prefix, "06")) {
            strcpy(node->studentFaculty, "经济");
        }
        else if (str_same_cmp(prefix, "07")) {
            strcpy(node->studentFaculty, "法");
        }
        else if (str_same_cmp(prefix, "08")) {
            strcpy(node->studentFaculty, "行政");
        }
        else if (str_same_cmp(prefix, "09")) {
            strcpy(node->studentFaculty, "商学与管理");
        }
        else if (str_same_cmp(prefix, "10")) {
            strcpy(node->studentFaculty, "数学");
        }
        else if (str_same_cmp(prefix, "11")) {
            strcpy(node->studentFaculty, "物理");
        }
        else if (str_same_cmp(prefix, "12")) {
            strcpy(node->studentFaculty, "化学");
        }
        else if (str_same_cmp(prefix, "13")) {
            strcpy(node->studentFaculty, "生命科学");
        }
        else if (str_same_cmp(prefix, "14")) {
            strcpy(node->studentFaculty, "机械与航空航天");
        }
        else if (str_same_cmp(prefix, "15")) {
            strcpy(node->studentFaculty, "汽车工程");
        }
        else if (str_same_cmp(prefix, "16")) {
            strcpy(node->studentFaculty, "材料科学与工程");
        }
        else if (str_same_cmp(prefix, "17")) {
            strcpy(node->studentFaculty, "交通");
        }
        else if (str_same_cmp(prefix, "18")) {
            strcpy(node->studentFaculty, "生物与农业工程");
        }
        else if (str_same_cmp(prefix, "19")) {
            strcpy(node->studentFaculty, "电子科学与工程");
        }
        else if (str_same_cmp(prefix, "20")) {
            strcpy(node->studentFaculty, "通信工程");
        }
        else if (str_same_cmp(prefix, "21")) {
            strcpy(node->studentFaculty, "计算机科学与技术");
        }
        else if (str_same_cmp(prefix, "22")) {
            strcpy(node->studentFaculty, "地球科学");
        }
        else if (str_same_cmp(prefix, "23")) {
            strcpy(node->studentFaculty, "地球探测科学与技术");
        }
        else if (str_same_cmp(prefix, "24")) {
            strcpy(node->studentFaculty, "建设工程");
        }
        else if (str_same_cmp(prefix, "25")) {
            strcpy(node->studentFaculty, "环境与资源");
        }
        else if (str_same_cmp(prefix, "26")) {
            strcpy(node->studentFaculty, "金融");
        }
        else if (str_same_cmp(prefix, "27")) {
            strcpy(node->studentFaculty, "公共卫生");
        }
        else if (str_same_cmp(prefix, "28")) {
            strcpy(node->studentFaculty, "药");
        }
        else if (str_same_cmp(prefix, "29")) {
            strcpy(node->studentFaculty, "护理");
        }
        else if (str_same_cmp(prefix, "30")) {
            strcpy(node->studentFaculty, "东北亚");
        }
        else if (str_same_cmp(prefix, "33")) {
            strcpy(node->studentFaculty, "口腔医");
        }
        else if (str_same_cmp(prefix, "37")) {
            strcpy(node->studentFaculty, "新闻与传播");
        }
        else if (str_same_cmp(prefix, "38")) {
            strcpy(node->studentFaculty, "考古");
        }
        else if (str_same_cmp(prefix, "39")) {
            strcpy(node->studentFaculty, "马克思主义");
        }
        else if (str_same_cmp(prefix, "40")) {
            strcpy(node->studentFaculty, "人工智能");
        }
        else if (str_same_cmp(prefix, "55")) {
            strcpy(node->studentFaculty, "软件");
        }
        else if (str_same_cmp(prefix, "65")) {
            strcpy(node->studentFaculty, "仪器科学与电气工程");
        }
        else if (str_same_cmp(prefix, "70")) {
            strcpy(node->studentFaculty, "临床医");
        }
        else if (str_same_cmp(prefix, "81")) {
            strcpy(node->studentFaculty, "动物医学");
        }
        else {
            // 如果没有匹配到，可以将学院名留空或者做其他处理
            strcpy(node->studentFaculty, "其它");
        }
        node = node->next;
    }
}

void matchFacultyName_one(char number[3], ListNode* p) {
    memset(p->studentFaculty,0,sizeof(p->studentFaculty));
    if (str_same_cmp(number, "01")) {
        strcpy(p->studentFaculty, "哲学社会");
    }
    else if (str_same_cmp(number, "02")) {
        strcpy(p->studentFaculty, "文学");
    }
    else if (str_same_cmp(number, "03")) {
        strcpy(p->studentFaculty, "外国语");
    }
    else if (str_same_cmp(number, "04")) {
        strcpy(p->studentFaculty, "艺术");
    }
    else if (str_same_cmp(number, "05")) {
        strcpy(p->studentFaculty, "体育");
    }
    else if (str_same_cmp(number, "06")) {
        strcpy(p->studentFaculty, "经济");
    }
    else if (str_same_cmp(number, "07")) {
        strcpy(p->studentFaculty, "法");
    }
    else if (str_same_cmp(number, "08")) {
        strcpy(p->studentFaculty, "行政");
    }
    else if (str_same_cmp(number, "09")) {
        strcpy(p->studentFaculty, "商学与管理");
    }
    else if (str_same_cmp(number, "10")) {
        strcpy(p->studentFaculty, "数学");
    }
    else if (str_same_cmp(number, "11")) {
        strcpy(p->studentFaculty, "物理");
    }
    else if (str_same_cmp(number, "12")) {
        strcpy(p->studentFaculty, "化学");
    }
    else if (str_same_cmp(number, "13")) {
        strcpy(p->studentFaculty, "生命科学");
    }
    else if (str_same_cmp(number, "14")) {
        strcpy(p->studentFaculty, "机械与航空航天");
    }
    else if (str_same_cmp(number, "15")) {
        strcpy(p->studentFaculty, "汽车工程");
    }
    else if (str_same_cmp(number, "16")) {
        strcpy(p->studentFaculty, "材料科学与工程");
    }
    else if (str_same_cmp(number, "17")) {
        strcpy(p->studentFaculty, "交通");
    }
    else if (str_same_cmp(number, "18")) {
        strcpy(p->studentFaculty, "生物与农业工程");
    }
    else if (str_same_cmp(number, "19")) {
        strcpy(p->studentFaculty, "电子科学与工程");
    }
    else if (str_same_cmp(number, "20")) {
        strcpy(p->studentFaculty, "通信工程");
    }
    else if (str_same_cmp(number, "21")) {
        strcpy(p->studentFaculty, "计算机科学与技术");
    }
    else if (str_same_cmp(number, "22")) {
        strcpy(p->studentFaculty, "地球科学");
    }
    else if (str_same_cmp(number, "23")) {
        strcpy(p->studentFaculty, "地球探测科学与技术");
    }
    else if (str_same_cmp(number, "24")) {
        strcpy(p->studentFaculty, "建设工程");
    }
    else if (str_same_cmp(number, "25")) {
        strcpy(p->studentFaculty, "环境与资源");
    }
    else if (str_same_cmp(number, "26")) {
        strcpy(p->studentFaculty, "金融");
    }
    else if (str_same_cmp(number, "27")) {
        strcpy(p->studentFaculty, "公共卫生");
    }
    else if (str_same_cmp(number, "28")) {
        strcpy(p->studentFaculty, "药");
    }
    else if (str_same_cmp(number, "29")) {
        strcpy(p->studentFaculty, "护理");
    }
    else if (str_same_cmp(number, "30")) {
        strcpy(p->studentFaculty, "东北亚");
    }
    else if (str_same_cmp(number, "33")) {
        strcpy(p->studentFaculty, "口腔医");
    }
    else if (str_same_cmp(number, "37")) {
        strcpy(p->studentFaculty, "新闻与传播");
    }
    else if (str_same_cmp(number, "38")) {
        strcpy(p->studentFaculty, "考古");
    }
    else if (str_same_cmp(number, "39")) {
        strcpy(p->studentFaculty, "马克思主义");
    }
    else if (str_same_cmp(number, "40")) {
        strcpy(p->studentFaculty, "人工智能");
    }
    else if (str_same_cmp(number, "55")) {
        strcpy(p->studentFaculty, "软件");
    }
    else if (str_same_cmp(number, "65")) {
        strcpy(p->studentFaculty, "仪器科学与电气工程");
    }
    else if (str_same_cmp(number, "70")) {
        strcpy(p->studentFaculty, "临床医");
    }
    else if (str_same_cmp(number, "81")) {
        strcpy(p->studentFaculty, "动物医学");
    }
    else {
        // 如果没有匹配到，可以将学院名留空或者做其他处理
        strcpy(p->studentFaculty, "未知学院");
    }

}