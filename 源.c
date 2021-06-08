#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"locate.h"
#define NUM 5
#define LEN sizeof(list)

char k[5][20] = { "语文","数学","外语","物理","化学" };

typedef struct student
{
    char stu_num[20];    //学号
    char name[10];      //姓名
    float score[5];     //各科目成绩
    float total;        //总成绩
}student;

typedef struct linklist
{
    student stu;
    struct linklist* next;
}list;

list* score_head;       //按成绩由高到低排列的头节点
list* num_head;         //按学号由低到高排列的头节点

int menu_select()       //cmd中输入数字，选择增删查改退出操作
{
   
    printf("\t\t这是学生管理系统");
    printf("\n\t\t建立学生信息表：1");
    printf("\n\t\t插入学生信息：2");
    printf("\n\t\t删除对应学号数据：3");
    printf("\n\t\t按成绩由高到低输出当前表：4");
    printf("\n\t\t按学号由高到低输出当前表：5");
    printf("\n\t\t退出管理系统：0");
    printf("\n\n\t\t请输入数字：");
    int kk;
    do
    {
        scanf_s("%d", &kk);
    } while ((0 > kk) && (kk > 5));
    return kk;
}

void create()                                           //创建学生成绩表-提示信息部分
{
    list* hsort_create();
    gotoxy();
    printf("将创建一个按学生成绩降序的单链表");
    score_head = hsort_create();
}
list* hsort_create()                                    //创建学生成绩表-功能主体部分
{
    gotoxy();
    printf("输入一组学生记录，输入学号为*表示结束");
    list* head, * p, * q, * rear, * findnode(), * input_record();
    head = (list*)malloc(LEN);
    head->next = NULL;
    head->stu.total = 999;
    rear = head;
    p = input_record();
    while (p != NULL)
    {
        if (p->stu.total < rear->stu.total)
        {
            p->next = rear->next;
            rear->next = p;
            rear = p;
        }
        else
        {
            q = findnode(head, p);                 //在链表中寻找p的前驱节点
            p->next = q->next;
            q->next = p;
        }
        p = input_record();
    }
    return head;
}

list* input_record()                             //从命令行输入一个学生的数据
{
    int i;
    list* s = (list*)malloc(LEN);
    s->next = NULL;
    s->stu.total = 0;
    getchar();
    gotoxy();
    printf("输入学号：");
    gets(s->stu.stu_num);
    if (strcmp(s->stu.stu_num, "*") == 0)                   //当输入学号为*时，返回空指针
    {
        return NULL;
    }
    gotoxy();
    printf("输入姓名：");
    gets(s->stu.name);
    gotoxy();
    printf("输入学生成绩，依次为 语文 数学 外语 物理 化学\n");
    for (i = 0;i < NUM;i++)
    {
        gotoxy();
        scanf_s("%f", &s->stu.score[i]);
        s->stu.total += s->stu.score[i];
    }
   
    return s;
}


list* findnode(list* head, list* p)                              //找恰好总成绩比p节点大的前驱节点
{
    list* s;
    s = head;
    while ((s != NULL) && (s->next->stu.total > p->stu.total))
    {
        s = s->next;
    }
    return s;
}
void insert()                                                   //插入新的学生节点-提示信息部分
{
    void data_insert();
    printf("\t\t这是插入模块\n");
    printf("\t\t请输入要插入的学生记录:");
    list* p;
    p = input_record();
    data_insert(p);
}
void data_insert(list*p)                                        //插入新的学生节点-功能主体部分
{
    list* rear;                                                 //rear为score_head的尾节点
    rear = score_head;
    while (rear->next != NULL)
    {
        rear = rear->next;
    }
    if (p->stu.total < rear->stu.total)                      //若新节点总成绩比尾节点的总成绩还小，直接将新节点作为尾节点
    {
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
    else                                                    //若新节点总成绩大于尾节点的总成绩，则寻找新节点应该插入的位置   
    {
        list* q;
        q = findnode(score_head, p);
        p->next = q->next;
        q->next = p;
    }
}
int printlist(list*head)                                                //按总成绩从高到低输出学生信息
{
    int i,n=1;
    gotoxy();
    printf("输出学生成绩表\n");
    printf("\t序号\t\t学号\t姓名");
    for (i = 0;i < NUM;i++)
    {
        printf("\t%s", k[i]);
    }
    printf("\t总成绩\n");
    list* p;
    if (head->next == NULL)
    {
        printf("学生表为空\n");
        return 1;
    }
    p = head->next;
    
    while (p != NULL)
    {
        printf("\t%d", n++);
        printf("\t%s", p->stu.stu_num);
        printf("\t%s", p->stu.name);
        for (i = 0;i < NUM;i++)
        {
            printf("\t%.1f", p->stu.score[i]);
        }
        printf("\t%.1f\n", p->stu.total);
        p = p->next;
    }
    return 0;
}
void delete()                        //删除输入学号对应的学生信息-提示信息部分
{
    list* key_delete();
    char stu_num[20] = { 0 };
    printf("\t\t删除模块\n");
    printf("\t\t输入要删除的学号\n");
    scanf_s("%s", stu_num,20);
    list* q;                            //p存放删除后的返回值，返回失败返回NULL
    q = key_delete(stu_num);
    if (q == NULL)printf("\t\t删除失败");
    else
    {
        free(q);
        printf("\t\t删除成功\n");
        printf("\t\t删除后的新的学生信息表打印如下：\n");
        printlist(score_head);
    }
}
list* key_delete(char *stu_num)                      //删除输入学号对应的学生信息-功能主体部分
{
    list* p,*q;
    p = score_head;
    while ((p->next != NULL) && (strcmp(p->next->stu.stu_num , stu_num)!=0))
    {
        p = p->next;
    }
    q = p->next;
    if (q == NULL)return q;
    else
    {
        p->next = q->next;
        return q;
    }
}
list* selesort()                   //把创建好的按成绩从高到底排列的表转换为以学号从小到大排列的学生表
{
    int i;
    list* head,*s,*p,*q,*hq;
    printf("\t\t输出按学号从小到大排序的成绩表\n");
    head = (list*)malloc(LEN);
    strcpy_s(head->stu.stu_num,20, "\0");
    head->next = NULL;
    p = score_head->next;
    while (p != NULL)
    {
        s = (list*)malloc(LEN);
        s->next = NULL;
        strcpy_s(s->stu.name,10, p->stu.name);
        strcpy_s(s->stu.stu_num,20, p->stu.stu_num);
        for (i = 0;i < NUM;i++)
        {
            s->stu.score[i] = p->stu.score[i];
        }
        s->stu.total = p->stu.total;
        q = head;
        hq = head;
        while ((q != NULL) && (strcmp(q->stu.stu_num, s->stu.stu_num) < 0))
        { 
            hq = q;
            q = q->next;
        }
        s->next = hq->next;
        hq->next = s;
        p = p->next;
    }
    return head;
}


void main()
{
    system("cls");
    int kk;
    do
    {
        kk = menu_select();               //从命令行中给出操作序号
        switch (kk)
        {
        case 1:create();break;      //输入为1，建立按学生成绩由高到低排列的单向链表
        case 2:insert();break;      //输入为2，插入数据，并且按照不改变学生成绩由高到低的顺序
        case 3:delete();break;      //输入为3，删除对应学号的数据
        case 4:printlist(score_head);break;  //输入为4，按成绩由高到低输出当前表
        case 5:num_head = selesort();printlist(num_head);break;    //输入为5，按学号由低到高输出当前表
        case 0:exit(0);             //输入为0，退出程序，返回0
        }
    } while (kk != 0);
}


