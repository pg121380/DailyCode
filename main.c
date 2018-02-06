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
        printf("***************代码量统计工具***************\n\n");
        printf("1、录入代码行数\n");
        printf("2、打印历史代码量\n");
        printf("3、查询某日代码量\n");
        printf("0、退出系统\n");
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
            printf("输入错误，请重新输入\n");
        }
    }
    return 0;
}

void InputMes()
{
    system("cls");
    //创建链表
    CodeNode* p = CodeNode_head;
    while(CodeNode_head != NULL && p->pNext != NULL)
    {
        p = p->pNext;
        //找到链表的尾节点
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
    printf("请输入代码量：\n");
    scanf("%d",&DailyCode->DailyCode.AmountOfCode);
    DailyCode->DailyCode.Time = CurrentTime();
    printf("录入成功\n");
    return;
}

void SaveMes()
{
    system("cls");
    FILE* pFile = fopen("S:\\CodeInfo.data","w");
    if(pFile == NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    CodeNode* p = CodeNode_head;
    while(p != NULL)
    {
        fprintf(pFile,"%d  %d\n",p->DailyCode.Time,p->DailyCode.AmountOfCode);
        p = p->pNext;
    }
    printf("保存成功\n");
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
        printf("文件打开失败\n");
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
    printf("读取成功\n");
    return;
}


void PrintMes()
{
    system("cls");
    printf("打印代码信息···\n\n");
    CodeNode* p = CodeNode_head;
    while(p != NULL)
    {
        printf("时间：%d\t",p->DailyCode.Time);
        printf("代码行数：%d\t",p->DailyCode.AmountOfCode);
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
    printf("当前总代码量为：%ld行",counter);
}

int CurrentTime()
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p =localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间
    //p = gmtime(&timep); //把日期和时间转换为格林威治(GMT)时间的函数

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
    printf("输入查找的日期：\n");
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
        printf("改日期下并没有录入代码\n");
        return ;
    }
    printf("%d的代码量为:%d行\n",searchDate,sum);
}
