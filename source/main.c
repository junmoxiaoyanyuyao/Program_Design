#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "definition.h"


int main(int argc, char** argv[]){
    ListNode* head = malloc(sizeof(ListNode)); //链表头
    head->next = NULL;
    ListNode* preListEnd = head;
    printf("需要导入加分细则吗?输入Y or N:");
    char c;
    scanf("%c",&c);
    if(c == 'Y')
        GradeInput(head,preListEnd);
    Insert(&preListEnd);

    // for(ListNode* temp = head->next;temp != NULL;temp = temp->next){
    //     printf("学号:%s 姓名:%s 加分:%.2f \n",temp->t->studentID,
    //             temp->t->studentName,temp->t->recognizedCredit);
    //     printf("人数:%d ",temp->t->Project->memberNum);
    //     for(int i = 0;i < temp->t->Project->memberNum;i++){
    //         printf("%s ",temp->t->Project->members[i]);
    //     }
    //     printf("指导老师:%s 项目名:%s \n编号:%d 开始:%d 结束:%d",
    //             temp->t->Project->instructor,temp->t->Project->projrectName,
    //             temp->t->Project->itemNum,temp->t->Project->approvalTime,
    //             temp->t->Project->endTime);
    //     printf("\n");
    // }
    return 0;
}
