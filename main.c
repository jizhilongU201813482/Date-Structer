#include<stdio.h>
#include<stdlib.h>
#define STACK_INI_SIZE 1000
#define STACKINEMENT 10
#define NULL 0
typedef struct
{
	int *base;
	int *top;
	int stacksize;
	int length;
}stack;
main()
{
	void initlist(stack *s);
	void operation(stack *s);
	stack s;
	initlist(&s);
	operation(&s);
}
void initlist(stack *s)
{
	s->base=s->top=(int *)malloc(STACK_INI_SIZE*sizeof(int));
	if(!s->base)
	{
		printf("ø™±Ÿ ß∞‹");
		exit(1);
	}
	s->length=0;
	s->stacksize=STACK_INI_SIZE;
}
void push(stack *s,int i)
{
	if(s->length==s->stacksize)
	{
		s->base=(int *)realloc(s->base,(STACK_INI_SIZE+STACKINEMENT)*sizeof(int));
		s->length=STACK_INI_SIZE;
		s->stacksize+=STACKINEMENT;
	}
	*(s->top)=i;
	s->length++;
	s->top++;
}
void pop(stack *s)
{
	if(s->top==s->base)
	{
		printf("’ªø’Œﬁ∑®…æ≥˝¥ÌŒÛ");
		exit(1);
	}
	s->top--;
	printf("%d ",*(s->top));
	*(s->top)=NULL;
	s->length--;
}
void operation(stack *s)
{
	int a[1000],i,j,k,m,n,l,z,y,flag1=1,flag2=1;
	char ch;
	printf("«Î ‰»Î≥µœ· ˝\n");
	scanf("%d",&i);
	flag1=1;
	for(j=0;j<i*2;j++)
	{
		a[j++]=1;
		a[j]=0;
	}
	while(flag1)
	{
		l=1,k=0;
		for(j=0;j<i*2;j++)
		{
			if(a[j]==1)
				push(s,l++);
			else if(a[j]==0)
				pop(s);
		}
		printf("\n");
		for(j=0;j<i;j++)
			if(a[j]==1)
				k++;
			if(k==i)
				flag1=0;
			a[i*2-1]++;
			while(flag2&&flag1)
			{

				z=1,m=0,n=0,y=1;
				for(j=i*2-1;j>=0&&z;j--)
					if(a[j]!=2)
						z=0;
					else
					{
						a[j]=0;
						a[j-1]++;
					}
					for(j=0;j<i*2&&y;j++)
					{
						if(a[j]==1)
							m++;
						else if(a[j]==0)
							n++;
						else
							printf("¥ÌŒÛ\n");
						if(n>m)
							y=0;

					}
					if(m==i&&n==i&&a[0]==1&&a[i*2-1]==0&&y==1)
						flag2=0;
					else
						a[i*2-1]++;

			}
			flag2=1;
	}
}
