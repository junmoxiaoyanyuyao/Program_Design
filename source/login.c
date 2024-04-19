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
        return false; // ���flagΪ1������false
    }
    else {
        return true; // ���flagΪ0������true
    }
}


void Hello()
{   
    while (true) {
        char choice[100];
        memset(choice, 0, sizeof(choice));
        printf("********************************************\n");
        printf("********ѧ���ɼ���Ϣ����ϵͳ��¼����********\n");
        printf("********************************************\n\n");
        printf("\t\t1.-��¼�˺�-\n");
        printf("\t\t2.-ע���˺�-\n");
        printf("\t\t3.-�˳�����-\n\n");
        printf("******************��ӭʹ��******************\n");
        printf("��ѡ��");
        s_gets(choice, 100);
        int flag1 = str_same_cmp(choice, "1");
        int flag2 = str_same_cmp(choice, "2");
        int flag3 = str_same_cmp(choice, "3");
        while (!flag1 && !flag2 && !flag3) {
            system("cls");
            printf("����Ƿ��������³��ԣ�\n");
            system("pause");
            system("cls");
            printf("********************************************\n");
            printf("********ѧ���ɼ���Ϣ����ϵͳ��¼����********\n");
            printf("********************************************\n\n");
            printf("\t\t1.-��¼�˺�-\n");
            printf("\t\t2.-ע���˺�-\n");
            printf("\t\t3.-�˳�����-\n\n");
            printf("******************��ӭʹ��******************\n");
            printf("��ѡ��");
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
            printf("\n\t\t���ɹ��˳���\n");
            exit(0);
            system("pause");
        }
    }
}

// ע���˺Ź��� 
void registeruser(){
    char account[30];
    char pw[30];
    memset(account, 0, sizeof(account));
    memset(pw, 0, sizeof(pw));
    printf("\t\t��ע���ʺš�\n");
    FILE* fp = fopen("account.txt", "a+");
    if (fp == NULL) {
        printf("���ļ�ʧ�ܣ�\n");
        return;
    }
    memset(account,0, sizeof(account));
    printf("�������û��˺ź�����(�˺�ֻ��Ϊ���ֺ�Ӣ����ĸ���������Ϊ����,Ӣ����ĸ,���š��˺š���������6λ�����12λ)\n\n\n");
    printf("\t�������˺ţ�");
    s_gets(account, 30);
    if (!AccountInput_check(account)) {
        printf("�˺�����Ƿ�\n");
        Sleep(1000);
        system("cls");
        return;
    }
    char existing_account[30];
    int i = 1;
    while (file_s_gets(existing_account,30,fp)!=NULL) {
        xor_encrypt_decrypt(existing_account, 'K');  // �����˺�
        if (i%2==1&&str_same_cmp(existing_account, account) == 1) {
            fclose(fp);
            printf("�˺��ѱ�ע��\n");
            Sleep(1000);
            system("cls");
            return;
        }
        i++;
    }
    printf("\n\t���������룺");
    memset(pw, 0, sizeof(pw));
    s_gets(pw, 30);
    if (!PasswordInput_check(pw)) {
        printf("��������Ƿ�\n");
        Sleep(1000);
        system("cls");
        return;
    }
    printf("\n\n\t�ٴ�ȷ�����룺");
    char pd[30];
    memset(pd, 0, sizeof(pd));
    s_gets(pd, 30);
    for (i = 0; i < sizeof(pw); i++) {
        if (pd[i] != pw[i]) {
            printf("�����������벻һ��\n");
            Sleep(1000);
            system("cls");
            return;
        }
    }
   
    xor_encrypt_decrypt(account, 'K');  // ʹ����Կ'K'�����˺�
    xor_encrypt_decrypt(pw, 'K');       // ʹ����Կ'K'��������
    fprintf(fp, "%s\n", account);       // �洢���ܺ���˺�
    fprintf(fp, "%s\n", pw);            // �洢���ܺ������
	fclose(fp);

	printf("ע��ɹ���\n");
	printf("����������ص�¼����\n");
	system("pause");
	system("cls");
    return;
}


//��¼�˺Ź��� 
void login(){
    char account[30];
    char pw[30];
    printf("--------����¼�˺š�--------\n");
    FILE* fp;
    fp = fopen("account.txt", "r");
    if(fp==NULL){
		printf("���ļ�ʧ�ܣ�\n");
        Sleep(1000);
		return;
	}
    printf("�������ʺ�:");
    memset(account, 0, sizeof(account));
    s_gets(account, 30);
    if (!AccountInput_check(account)) {
        printf("�˺�����Ƿ�\n");
        Sleep(1000);
        system("cls");
        return;
    }

    printf("����������:");
    memset(pw, 0, sizeof(pw));
    s_gets(pw, 30);
    if (!PasswordInput_check(pw)) {
        printf("��������Ƿ�\n");
		Sleep(1000);
		system("cls");
		return;
    }
    char existing_account[30];
    char existing_pw[30];
    int i = 1;
    while (file_s_gets(existing_account, 30, fp) != NULL){
        xor_encrypt_decrypt(existing_account, 'K');  // �����˺�
        if (i % 2 == 1 && str_same_cmp(existing_account, account) == 1) {
            i++;
            file_s_gets(existing_pw, 30, fp);
            xor_encrypt_decrypt(existing_pw, 'K');  // ��������
            int wrongtime = 0;
            while(wrongtime<=3){
				if (str_same_cmp(existing_pw, pw) == 1) {
					printf("��¼�ɹ���\n");
					printf("�����������ѧ����Ϣ����ϵͳ!\n");
					system("pause");
					system("cls");
					Menu();
					system("pause");
					system("cls");
                    return;
				}
				else {
					printf("��������㻹��%d�λ��ᣬ����������:", 4 - wrongtime);
					memset(pw, 0, sizeof(pw));
					s_gets(pw, 30);
					wrongtime++;
				}
			}
            if (wrongtime == 4) {
                printf("�������������࣡\n");
                Sleep(1000);
                system("cls");
                return;
            }
        }
        i++;
    }
    printf("�˺�δע�ᣡ\n");
    Sleep(1000);
    system("cls");
    return;
}



void changeFaculty(ListNode* head, ListNode* tailer) {
    printf("������תרҵѧ����ѧ��:");
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
            printf("�������ѧ��ת��ѧԺ���(����-1�������˵�):");
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
                printf("�������Ƿ���\n");
                Sleep(1000);
                Faculty_Search();
                printf("�������ѧ��ת��ѧԺ���(����-1�������˵�):");
                memset(number, 0, sizeof(number));
                s_gets(number, 100);
                flag = 0;
                if (number[2] != '\0')flag = 1;
                else if (number[0] < '0' || number[0]>'9' || number[1] < '0' || number[1]>'9')flag = 1;
            }

            matchFacultyName_one(number, p);
            printf("���޸ĸ�ѧ��ѧԺ��Ϣ��\n");
            break;
        }
        p = p->next;
    }
    if (p == tailer) {
        printf("δ�ҵ���ѧ����Ϣ��\n");
        return;
    }
}
//ѧԺʶ��ѧ��

void matchFacultyName_list(ListNode* head, ListNode* tailer) {
    ListNode* node = head->next;
    while (node != tailer) {
        // �ж�ѧ��ǰ��λ
        char prefix[3];
        strncpy(prefix, node->studentID, 2);
        prefix[2] = '\0';
        // ƥ��ѧԺ��
        if (str_same_cmp(prefix, "01")) {
            strcpy(node->studentFaculty, "��ѧ���");
        }
        else if (str_same_cmp(prefix, "02")) {
            strcpy(node->studentFaculty, "��ѧ");
        }
        else if (str_same_cmp(prefix, "03")) {
            strcpy(node->studentFaculty, "�����");
        }
        else if (str_same_cmp(prefix, "04")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "05")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "06")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "07")) {
            strcpy(node->studentFaculty, "��");
        }
        else if (str_same_cmp(prefix, "08")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "09")) {
            strcpy(node->studentFaculty, "��ѧ�����");
        }
        else if (str_same_cmp(prefix, "10")) {
            strcpy(node->studentFaculty, "��ѧ");
        }
        else if (str_same_cmp(prefix, "11")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "12")) {
            strcpy(node->studentFaculty, "��ѧ");
        }
        else if (str_same_cmp(prefix, "13")) {
            strcpy(node->studentFaculty, "������ѧ");
        }
        else if (str_same_cmp(prefix, "14")) {
            strcpy(node->studentFaculty, "��е�뺽�պ���");
        }
        else if (str_same_cmp(prefix, "15")) {
            strcpy(node->studentFaculty, "��������");
        }
        else if (str_same_cmp(prefix, "16")) {
            strcpy(node->studentFaculty, "���Ͽ�ѧ�빤��");
        }
        else if (str_same_cmp(prefix, "17")) {
            strcpy(node->studentFaculty, "��ͨ");
        }
        else if (str_same_cmp(prefix, "18")) {
            strcpy(node->studentFaculty, "������ũҵ����");
        }
        else if (str_same_cmp(prefix, "19")) {
            strcpy(node->studentFaculty, "���ӿ�ѧ�빤��");
        }
        else if (str_same_cmp(prefix, "20")) {
            strcpy(node->studentFaculty, "ͨ�Ź���");
        }
        else if (str_same_cmp(prefix, "21")) {
            strcpy(node->studentFaculty, "�������ѧ�뼼��");
        }
        else if (str_same_cmp(prefix, "22")) {
            strcpy(node->studentFaculty, "�����ѧ");
        }
        else if (str_same_cmp(prefix, "23")) {
            strcpy(node->studentFaculty, "����̽���ѧ�뼼��");
        }
        else if (str_same_cmp(prefix, "24")) {
            strcpy(node->studentFaculty, "���蹤��");
        }
        else if (str_same_cmp(prefix, "25")) {
            strcpy(node->studentFaculty, "��������Դ");
        }
        else if (str_same_cmp(prefix, "26")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "27")) {
            strcpy(node->studentFaculty, "��������");
        }
        else if (str_same_cmp(prefix, "28")) {
            strcpy(node->studentFaculty, "ҩ");
        }
        else if (str_same_cmp(prefix, "29")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "30")) {
            strcpy(node->studentFaculty, "������");
        }
        else if (str_same_cmp(prefix, "33")) {
            strcpy(node->studentFaculty, "��ǻҽ");
        }
        else if (str_same_cmp(prefix, "37")) {
            strcpy(node->studentFaculty, "�����봫��");
        }
        else if (str_same_cmp(prefix, "38")) {
            strcpy(node->studentFaculty, "����");
        }
        else if (str_same_cmp(prefix, "39")) {
            strcpy(node->studentFaculty, "���˼����");
        }
        else if (str_same_cmp(prefix, "40")) {
            strcpy(node->studentFaculty, "�˹�����");
        }
        else if (str_same_cmp(prefix, "55")) {
            strcpy(node->studentFaculty, "���");
        }
        else if (str_same_cmp(prefix, "65")) {
            strcpy(node->studentFaculty, "������ѧ���������");
        }
        else if (str_same_cmp(prefix, "70")) {
            strcpy(node->studentFaculty, "�ٴ�ҽ");
        }
        else if (str_same_cmp(prefix, "81")) {
            strcpy(node->studentFaculty, "����ҽѧ");
        }
        else {
            // ���û��ƥ�䵽�����Խ�ѧԺ�����ջ�������������
            strcpy(node->studentFaculty, "����");
        }
        node = node->next;
    }
}

void matchFacultyName_one(char number[3], ListNode* p) {
    memset(p->studentFaculty,0,sizeof(p->studentFaculty));
    if (str_same_cmp(number, "01")) {
        strcpy(p->studentFaculty, "��ѧ���");
    }
    else if (str_same_cmp(number, "02")) {
        strcpy(p->studentFaculty, "��ѧ");
    }
    else if (str_same_cmp(number, "03")) {
        strcpy(p->studentFaculty, "�����");
    }
    else if (str_same_cmp(number, "04")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "05")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "06")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "07")) {
        strcpy(p->studentFaculty, "��");
    }
    else if (str_same_cmp(number, "08")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "09")) {
        strcpy(p->studentFaculty, "��ѧ�����");
    }
    else if (str_same_cmp(number, "10")) {
        strcpy(p->studentFaculty, "��ѧ");
    }
    else if (str_same_cmp(number, "11")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "12")) {
        strcpy(p->studentFaculty, "��ѧ");
    }
    else if (str_same_cmp(number, "13")) {
        strcpy(p->studentFaculty, "������ѧ");
    }
    else if (str_same_cmp(number, "14")) {
        strcpy(p->studentFaculty, "��е�뺽�պ���");
    }
    else if (str_same_cmp(number, "15")) {
        strcpy(p->studentFaculty, "��������");
    }
    else if (str_same_cmp(number, "16")) {
        strcpy(p->studentFaculty, "���Ͽ�ѧ�빤��");
    }
    else if (str_same_cmp(number, "17")) {
        strcpy(p->studentFaculty, "��ͨ");
    }
    else if (str_same_cmp(number, "18")) {
        strcpy(p->studentFaculty, "������ũҵ����");
    }
    else if (str_same_cmp(number, "19")) {
        strcpy(p->studentFaculty, "���ӿ�ѧ�빤��");
    }
    else if (str_same_cmp(number, "20")) {
        strcpy(p->studentFaculty, "ͨ�Ź���");
    }
    else if (str_same_cmp(number, "21")) {
        strcpy(p->studentFaculty, "�������ѧ�뼼��");
    }
    else if (str_same_cmp(number, "22")) {
        strcpy(p->studentFaculty, "�����ѧ");
    }
    else if (str_same_cmp(number, "23")) {
        strcpy(p->studentFaculty, "����̽���ѧ�뼼��");
    }
    else if (str_same_cmp(number, "24")) {
        strcpy(p->studentFaculty, "���蹤��");
    }
    else if (str_same_cmp(number, "25")) {
        strcpy(p->studentFaculty, "��������Դ");
    }
    else if (str_same_cmp(number, "26")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "27")) {
        strcpy(p->studentFaculty, "��������");
    }
    else if (str_same_cmp(number, "28")) {
        strcpy(p->studentFaculty, "ҩ");
    }
    else if (str_same_cmp(number, "29")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "30")) {
        strcpy(p->studentFaculty, "������");
    }
    else if (str_same_cmp(number, "33")) {
        strcpy(p->studentFaculty, "��ǻҽ");
    }
    else if (str_same_cmp(number, "37")) {
        strcpy(p->studentFaculty, "�����봫��");
    }
    else if (str_same_cmp(number, "38")) {
        strcpy(p->studentFaculty, "����");
    }
    else if (str_same_cmp(number, "39")) {
        strcpy(p->studentFaculty, "���˼����");
    }
    else if (str_same_cmp(number, "40")) {
        strcpy(p->studentFaculty, "�˹�����");
    }
    else if (str_same_cmp(number, "55")) {
        strcpy(p->studentFaculty, "���");
    }
    else if (str_same_cmp(number, "65")) {
        strcpy(p->studentFaculty, "������ѧ���������");
    }
    else if (str_same_cmp(number, "70")) {
        strcpy(p->studentFaculty, "�ٴ�ҽ");
    }
    else if (str_same_cmp(number, "81")) {
        strcpy(p->studentFaculty, "����ҽѧ");
    }
    else {
        // ���û��ƥ�䵽�����Խ�ѧԺ�����ջ�������������
        strcpy(p->studentFaculty, "δ֪ѧԺ");
    }

}