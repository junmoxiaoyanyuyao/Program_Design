#pragma execution_character_set("utf-8")  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#include "definition.h"
#include "Insert.h"
#include "Modify.h"
#include "Output.h"
#include "inquire.h"
#include "delete.h"
#include "login.h"


void Menu() {
    ListNode* head = malloc(sizeof(ListNode)); //����ͷ�ڵ�
    ListNode* tailer = malloc(sizeof(ListNode)); //����β���
    head->next = tailer;
    tailer->father = head;
    ListNode* currentNode = head;
    while (true) {
        fflush(stdin);
        // syetem("cls");
            printf("********************************************\n");
            printf("*********** ѧ���ɼ���Ϣ����ϵͳ ***********\n");
            printf("********************************************\n\n");
            printf("\t1. ����ѧ����Ϣ\n");
            printf("\t2. ����ӷ�ϸ��\n");
            printf("\t3. �޸�ѧ����Ϣ\n");
            printf("\t4. ����ѧ����Ϣ\n");
            printf("\t5. ��ѯѧ����Ϣ\n");
            printf("\t6. ɾ��ѧ����Ϣ\n");
            printf("\t7. תרҵ��Ϣ�޸�\n");
            printf("\t8. �˳���¼\n\n");
            printf("********************************************\n");
            printf("��ѡ�������");

        char choice[100];
        memset(choice, 0, sizeof(choice));
        s_gets(choice, 100);
        int flag1 = str_same_cmp(choice, "1");
        int flag2 = str_same_cmp(choice, "2");
        int flag3 = str_same_cmp(choice, "3");
        int flag4 = str_same_cmp(choice, "4");
        int flag5 = str_same_cmp(choice, "5");
        int flag6 = str_same_cmp(choice, "6");
        int flag7 = str_same_cmp(choice, "7");
        int flag8 = str_same_cmp(choice, "8");
        while (!flag1 && !flag2 && !flag3 && !flag4 && !flag5&&!flag6&&!flag7&&!flag8) {
            printf("�Ƿ����룬���������룡\n");
            Sleep(1000);
            // syetem("cls");
            printf("********************************************\n");
            printf("*********** ѧ���ɼ���Ϣ����ϵͳ ***********\n");
            printf("********************************************\n\n");
            printf("\t1. ����ѧ����Ϣ\n");
            printf("\t2. ����ӷ�ϸ��\n");
            printf("\t3. �޸�ѧ����Ϣ\n");
            printf("\t4. ����ѧ����Ϣ\n");
            printf("\t5. ��ѯѧ����Ϣ\n");
            printf("\t6. ɾ��ѧ����Ϣ\n");
            printf("\t7. תרҵ��Ϣ�޸�\n");
            printf("\t8. �˳���¼\n\n");
            printf("********************************************\n");
            printf("��ѡ�������");
            memset(choice, 0, sizeof(choice));
            s_gets(choice, 100);
            flag1 = str_same_cmp(choice, "1");
            flag2 = str_same_cmp(choice, "2");
            flag3 = str_same_cmp(choice, "3");
            flag4 = str_same_cmp(choice, "4");
            flag5 = str_same_cmp(choice, "5");
            flag6 = str_same_cmp(choice, "6");
            flag7 = str_same_cmp(choice, "7");
            flag8 = str_same_cmp(choice, "8");

        }
        if (flag1) {
            Insert(head,tailer,&currentNode);
            matchFacultyName_list(head, tailer);
             int c;
             while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if(flag2){
             QualityGradeInput(head,tailer);
              int c;
              while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if (flag3) {
            // matchFacultyName_list(head, tailer);
            Modify(head,tailer);
             int c;
             while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if (flag4) {
            // matchFacultyName_list(head, tailer);
            Output(head,tailer);
             int c;
             while ((c = getchar()) != '\n' && c != EOF) {}
        }
        else if (flag5) {
            // matchFacultyName_list(head, tailer);
            guide_information(head, tailer);
        }
        else if (flag6) {
            // matchFacultyName_list(head, tailer);
            Delete_guide(head, tailer);
        }
        else if (flag7) {
            // matchFacultyName_list(head, tailer);
            changeFaculty(head, tailer);
        }
        else if (flag8) {
            printf("�˳���¼�ɹ���\n");
            Sleep(1000);
            return;
        }
    }
}

