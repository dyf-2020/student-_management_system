#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"locate.h"
#define NUM 5
#define LEN sizeof(list)

char k[5][20] = { "����","��ѧ","����","����","��ѧ" };

typedef struct student
{
    char stu_num[20];    //ѧ��
    char name[10];      //����
    float score[5];     //����Ŀ�ɼ�
    float total;        //�ܳɼ�
}student;

typedef struct linklist
{
    student stu;
    struct linklist* next;
}list;

list* score_head;       //���ɼ��ɸߵ������е�ͷ�ڵ�
list* num_head;         //��ѧ���ɵ͵������е�ͷ�ڵ�

int menu_select()       //cmd���������֣�ѡ����ɾ����˳�����
{
   
    printf("\t\t����ѧ������ϵͳ");
    printf("\n\t\t����ѧ����Ϣ��1");
    printf("\n\t\t����ѧ����Ϣ��2");
    printf("\n\t\tɾ����Ӧѧ�����ݣ�3");
    printf("\n\t\t���ɼ��ɸߵ��������ǰ��4");
    printf("\n\t\t��ѧ���ɸߵ��������ǰ��5");
    printf("\n\t\t�˳�����ϵͳ��0");
    printf("\n\n\t\t���������֣�");
    int kk;
    do
    {
        scanf_s("%d", &kk);
    } while ((0 > kk) && (kk > 5));
    return kk;
}

void create()                                           //����ѧ���ɼ���-��ʾ��Ϣ����
{
    list* hsort_create();
    gotoxy();
    printf("������һ����ѧ���ɼ�����ĵ�����");
    score_head = hsort_create();
}
list* hsort_create()                                    //����ѧ���ɼ���-�������岿��
{
    gotoxy();
    printf("����һ��ѧ����¼������ѧ��Ϊ*��ʾ����");
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
            q = findnode(head, p);                 //��������Ѱ��p��ǰ���ڵ�
            p->next = q->next;
            q->next = p;
        }
        p = input_record();
    }
    return head;
}

list* input_record()                             //������������һ��ѧ��������
{
    int i;
    list* s = (list*)malloc(LEN);
    s->next = NULL;
    s->stu.total = 0;
    getchar();
    gotoxy();
    printf("����ѧ�ţ�");
    gets(s->stu.stu_num);
    if (strcmp(s->stu.stu_num, "*") == 0)                   //������ѧ��Ϊ*ʱ�����ؿ�ָ��
    {
        return NULL;
    }
    gotoxy();
    printf("����������");
    gets(s->stu.name);
    gotoxy();
    printf("����ѧ���ɼ�������Ϊ ���� ��ѧ ���� ���� ��ѧ\n");
    for (i = 0;i < NUM;i++)
    {
        gotoxy();
        scanf_s("%f", &s->stu.score[i]);
        s->stu.total += s->stu.score[i];
    }
   
    return s;
}


list* findnode(list* head, list* p)                              //��ǡ���ܳɼ���p�ڵ���ǰ���ڵ�
{
    list* s;
    s = head;
    while ((s != NULL) && (s->next->stu.total > p->stu.total))
    {
        s = s->next;
    }
    return s;
}
void insert()                                                   //�����µ�ѧ���ڵ�-��ʾ��Ϣ����
{
    void data_insert();
    printf("\t\t���ǲ���ģ��\n");
    printf("\t\t������Ҫ�����ѧ����¼:");
    list* p;
    p = input_record();
    data_insert(p);
}
void data_insert(list*p)                                        //�����µ�ѧ���ڵ�-�������岿��
{
    list* rear;                                                 //rearΪscore_head��β�ڵ�
    rear = score_head;
    while (rear->next != NULL)
    {
        rear = rear->next;
    }
    if (p->stu.total < rear->stu.total)                      //���½ڵ��ܳɼ���β�ڵ���ܳɼ���С��ֱ�ӽ��½ڵ���Ϊβ�ڵ�
    {
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
    else                                                    //���½ڵ��ܳɼ�����β�ڵ���ܳɼ�����Ѱ���½ڵ�Ӧ�ò����λ��   
    {
        list* q;
        q = findnode(score_head, p);
        p->next = q->next;
        q->next = p;
    }
}
int printlist(list*head)                                                //���ܳɼ��Ӹߵ������ѧ����Ϣ
{
    int i,n=1;
    gotoxy();
    printf("���ѧ���ɼ���\n");
    printf("\t���\t\tѧ��\t����");
    for (i = 0;i < NUM;i++)
    {
        printf("\t%s", k[i]);
    }
    printf("\t�ܳɼ�\n");
    list* p;
    if (head->next == NULL)
    {
        printf("ѧ����Ϊ��\n");
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
void delete()                        //ɾ������ѧ�Ŷ�Ӧ��ѧ����Ϣ-��ʾ��Ϣ����
{
    list* key_delete();
    char stu_num[20] = { 0 };
    printf("\t\tɾ��ģ��\n");
    printf("\t\t����Ҫɾ����ѧ��\n");
    scanf_s("%s", stu_num,20);
    list* q;                            //p���ɾ����ķ���ֵ������ʧ�ܷ���NULL
    q = key_delete(stu_num);
    if (q == NULL)printf("\t\tɾ��ʧ��");
    else
    {
        free(q);
        printf("\t\tɾ���ɹ�\n");
        printf("\t\tɾ������µ�ѧ����Ϣ���ӡ���£�\n");
        printlist(score_head);
    }
}
list* key_delete(char *stu_num)                      //ɾ������ѧ�Ŷ�Ӧ��ѧ����Ϣ-�������岿��
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
list* selesort()                   //�Ѵ����õİ��ɼ��Ӹߵ������еı�ת��Ϊ��ѧ�Ŵ�С�������е�ѧ����
{
    int i;
    list* head,*s,*p,*q,*hq;
    printf("\t\t�����ѧ�Ŵ�С��������ĳɼ���\n");
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
        kk = menu_select();               //���������и����������
        switch (kk)
        {
        case 1:create();break;      //����Ϊ1��������ѧ���ɼ��ɸߵ������еĵ�������
        case 2:insert();break;      //����Ϊ2���������ݣ����Ұ��ղ��ı�ѧ���ɼ��ɸߵ��͵�˳��
        case 3:delete();break;      //����Ϊ3��ɾ����Ӧѧ�ŵ�����
        case 4:printlist(score_head);break;  //����Ϊ4�����ɼ��ɸߵ��������ǰ��
        case 5:num_head = selesort();printlist(num_head);break;    //����Ϊ5����ѧ���ɵ͵��������ǰ��
        case 0:exit(0);             //����Ϊ0���˳����򣬷���0
        }
    } while (kk != 0);
}


