#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAXVALUE 10000    //定义最大权值
#define MAXLEAF 30        //定义哈夫曼树中叶子结点个数
#define MAXNODE MAXLEAF*2-1    //定义哈夫曼总结点数
#define MAXSIZE 256

int n;
char str[MAXLEAF];

typedef struct
{
    int weight;
    int parent;
    int r_child;
    int l_child;
}HNodeType;

typedef struct
{
    char data;
    int weight;
}HDatatype;

typedef struct
{
    HDatatype data[MAXSIZE];
    int number;
}HNodeNum;

void Find_Weight(HNodeNum**pHn,char val[])
{
    int i,j;
    HDatatype t;
    *pHn=(HNodeNum*)malloc(sizeof(HNodeNum));
    (*pHn)->number=0;
    for(i=0;i<MAXSIZE;i++)
    {
        ((*pHn)->data[i]).weight=0;
    }

    for(i=0;val[i]!='\0';i++)
    {
        for(j=0;j<(*pHn)->number;j++)
        {
            if(((*pHn)->data[j]).data==val[i])
            {
                ((*pHn)->data[j]).weight++;
                break;
            }
            if(j>=(*pHn)->number)
            {
                ((*pHn)->data[j]).data=val[i];
                ((*pHn)->data[j]).weight=1;
                (*pHn)->number ++;
            }
        }
    }
    for(i=0;i<(*pHn)->number-1;i++)
    {
        for(j=0;j<(*pHn)->number-1-i;j++)
        {
            if(((*pHn)->data[j]).weight>((*pHn)->data[j+1]).weight)
            {
                t=(*pHn)->data[j];
                (*pHn)->data[j]=(*pHn)->data[j+1];
                (*pHn)->data[j+1]=t;
            }
        }
    }
    for(i=0;i<(*pHn)->number;i++)
    {
        printf("%c %d\n",((*pHn)->data[i]).data,((*pHn)->data[i]).weight);
    }
}

HNodeNum *HuffmanTree(HNodeType HuffNode[])
{
    int i,j,m1,m2,x1,x2;
    HNodeNum*pHn=NULL;
    printf("输入字符串: \n");
    gets(str);
    Find_Weight(&pHn,str);
    n=pHn->number;

    for(i=0;i<2*n-1;i++)
    {
        HuffNode[i].weight=0;
        HuffNode[i].parent=-1;
        HuffNode[i].l_child=-1;
        HuffNode[i].r_child=-1;
    }
    for(i=0;i<n;i++)
    {
        HuffNode[i].weight=(pHn->data[i]).weight;
    }

    for(i=0;i<n-1;i++)
    {
        m1=m2=MAXVALUE;
        x1=x2=0;
        for(j=0;j<n+i;j++)
        {
            if(HuffNode[j].weight<m1&&HuffNode[j].parent==-1)
            {
                m2=m1;
                x2=x1;
                m1=HuffNode[j].weight;
                x1=j;

            }
            else if(HuffNode[j].weight<m2&&HuffNode[j].parent==-1)
            {
                m2=HuffNode[j].weight;
                x2=j;
            }
        }
        HuffNode[x1].parent=n+i;
        HuffNode[x2].parent=n+i;
        HuffNode[n+i].weight=HuffNode[x1].weight+HuffNode[x2].weight;
        HuffNode[n+i].l_child=x1;
        HuffNode[n+i].r_child=x2;
    }
    return pHn;
}

#define MAXBIT 100
#define MAXSTR 1000

typedef struct
{
    int bit[MAXBIT];
    int start;
}HCodeType;

void HuffmanCode()
{
    HNodeType HuffNode[MAXNODE];
    HCodeType HuffCode[MAXLEAF],cd;
    int HuffStr[MAXSTR];
    HNodeNum*pHn=NULL;
    int i,j,k,c,p,l=0;
    pHn=HuffmanTree(HuffNode);

    for(i=0;i<n;i++)
    {
        cd.start=n-1;
        c=i;
        p=HuffNode[c].parent;

        while(p!=-1)
        {
            if(HuffNode[p].l_child==c)
            {
                cd.bit[cd.start]=0;
            }
            else
            {
                cd.bit[cd.start]=1;
            }
            cd.start=cd.start-1;
            c=p;
            p=HuffNode[c].parent;
        }
        for(j=cd.start+1;j<n;j++)
        {
            HuffCode[i].bit[j]=cd.bit[j];
        }
        HuffCode[i].start=cd.start;
    }

    for(i=0;i<n;i++)
    {
        printf("%c--",(pHn->data[i]).data);
        for(j=HuffCode[i].start+1;j<n;j++)
        {
            printf("%d",HuffCode[i].bit[j]);
        }
        printf("\n");
    }

    printf("转码为:\n");

    for(i=0;str[i]!='\0';i++)
    {
        for(j=0;j<n;j++)
        {
            if(str[i]==(pHn->data[j]).data)
            {
                for(k=HuffCode[j].start+1;k<n;k++)
                {
                    HuffStr[l]=HuffCode[j].bit[k];
                    printf("%d",HuffStr[l]);
                    l++;
                }
            }
        }
    }
    printf("\n");

    printf("解码为 :\n");
    c=2*n-2;
    for(i=0;i<l;i++)
    {
        if(HuffStr[i]==0)
        {
            c=HuffNode[c].l_child;
        }
        if(HuffStr[i]==1)
        {
            c=HuffNode[c].r_child;
        }
        if(HuffNode[c].l_child==-1&&HuffNode[c].r_child==-1)
        {
            printf("%c",(pHn->data[c]).data);
            c=2*n-2;
        }
    }
    printf("\n");
}

int main()
{
    HuffmanCode();
}
