#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
typedef struct code
{
    int Time;
    int AmountOfCode;
} Code;

typedef struct node
{
    Code DailyCode;
    struct node* pNext;
} CodeNode;

CodeNode* CodeNode_head = NULL;

void InputMes();
void SaveMes();
void LoadMes();
void PrintMes();
void CountAmountOfCode();
int CurrentTime();
void AmountOfCodeSearch();
int main()
{
    int choice;
    while(1)
    {
        printf("***************������ͳ�ƹ���***************\n\n");
        printf("1��¼���������\n");
        printf("2����ӡ��ʷ������\n");
        printf("3����ѯĳ�մ�����\n");
        printf("0���˳�ϵͳ\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            LoadMes();
            InputMes();
            SaveMes();
            break;
        case 2:
            LoadMes();
            PrintMes();
            break;
        case 3:
            AmountOfCodeSearch();
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("�����������������\n");
        }
    }
    return 0;
}

void InputMes()
{
    system("cls");
    //��������
    CodeNode* p = CodeNode_head;
    while(CodeNode_head != NULL && p->pNext != NULL)
    {
        p = p->pNext;
        //�ҵ������β�ڵ�
    }
    CodeNode* DailyCode = (CodeNode*)malloc(sizeof(CodeNode));
    DailyCode->pNext = NULL;
    if(CodeNode_head == NULL)
    {
        CodeNode_head = DailyCode;
        p = CodeNode_head;
    }
    else
    {
        p->pNext = DailyCode;
    }
    printf("�������������\n");
    scanf("%d",&DailyCode->DailyCode.AmountOfCode);
    DailyCode->DailyCode.Time = CurrentTime();
    printf("¼��ɹ�\n");
    return;
}

void SaveMes()
{
    system("cls");
    FILE* pFile = fopen("S:\\CodeInfo.data","w");
    if(pFile == NULL)
    {
        printf("�ļ���ʧ��\n");
        return;
    }
    CodeNode* p = CodeNode_head;
    while(p != NULL)
    {
        fprintf(pFile,"%d  %d\n",p->DailyCode.Time,p->DailyCode.AmountOfCode);
        p = p->pNext;
    }
    printf("����ɹ�\n");
    fclose(pFile);
}

void LoadMes()
{
    system("cls");
    CodeNode *p,*temp;
    p = temp = CodeNode_head;
    while(temp != NULL)
    {
        p = p->pNext;
        free(temp);
        temp = p;
    }
    CodeNode_head = NULL;

    FILE* pFile = fopen("S:\\CodeInfo.data","r");
    if(pFile == NULL)
    {
        printf("�ļ���ʧ��\n");
        return;
    }
    while(!feof(pFile))
    {
        CodeNode* DailyCode = (CodeNode*)malloc(sizeof(CodeNode));
        fscanf(pFile,"%d  %d\n",&DailyCode->DailyCode.Time,&DailyCode->DailyCode.AmountOfCode);

        if(CodeNode_head == NULL)
        {
            CodeNode_head = DailyCode;
            p = CodeNode_head;
        }
        else
        {
            p->pNext = DailyCode;
            p = p->pNext;
            p->pNext = NULL;
        }
    }
    fclose(pFile);
    printf("��ȡ�ɹ�\n");
    return;
}


void PrintMes()
{
    system("cls");
    printf("��ӡ������Ϣ������\n\n");
    CodeNode* p = CodeNode_head;
    while(p != NULL)
    {
        printf("ʱ�䣺%d\t",p->DailyCode.Time);
        printf("����������%d\t",p->DailyCode.AmountOfCode);
        printf("\n");
        p = p->pNext;
    }
    CountAmountOfCode();
    printf("\n\n");
}

void CountAmountOfCode()
{
    CodeNode* p = CodeNode_head;
    long counter = 0;
    while(p != NULL)
    {
        counter += p->DailyCode.AmountOfCode;
        p = p->pNext;
    }
    printf("��ǰ�ܴ�����Ϊ��%ld��",counter);
}

int CurrentTime()
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p =localtime(&timep); //�˺�����õ�tm�ṹ���ʱ�䣬���Ѿ����й�ʱ��ת��Ϊ����ʱ��
    //p = gmtime(&timep); //�����ں�ʱ��ת��Ϊ��������(GMT)ʱ��ĺ���

    long Time;
    Time = (1900 + p->tm_year) * 10000 +(1 + p->tm_mon) * 100 +(p->tm_mday);
    return Time;
}

void AmountOfCodeSearch()
{
    LoadMes();
    int sum = 0;
    int searchDate;
    int searchTag = 0;
    printf("������ҵ����ڣ�\n");
    scanf("%d",&searchDate);
    CodeNode* p =CodeNode_head;
    while(p != NULL)
    {
        if(p->DailyCode.Time == searchDate)
        {
            sum += p->DailyCode.AmountOfCode;
            searchTag = 1;
        }
        p = p->pNext;
    }
    if(!searchTag)
    {
        printf("�������²�û��¼�����\n");
        return ;
    }
    printf("%d�Ĵ�����Ϊ:%d��\n",searchDate,sum);
}
