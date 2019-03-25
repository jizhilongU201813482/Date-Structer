#include  <stdio.h>
#include  <stdlib.h>
typedef struct LNode{
	int num;
	int data;
	struct LNode  *next;
}LNode,*LinkList;

int delateQ_data = 0;

LinkList iniList(){
	LinkList head;
	if(head = (LinkList) malloc (sizeof(LNode)))  head->next = NULL;
	return head;
}

LinkList creatListR(int a[],int n){
	LinkList head = iniList();
	LinkList r = head;
	for(int i=0;i<n;i++){
		LinkList q = (LinkList) malloc (sizeof(LNode));
		q->num = i+1;
		q->data = a[i];
		r->next = q;
		r = q;
		printf("num:%d,p:%d\n",q->num,q->data);
	}
	r->next = head->next;
	return head;
}

LinkList LinkDelete_L(LinkList *m,int i){
	LinkList p,q;
	p = m;
	int j;
	for(j=0;j<i-1;j++)	p = p->next;
	q = p->next;
	p->next = q->next;
	printf("num:%d出局\n",q->num);
	delateQ_data = q->data;
	free(q);
	return p;
}

int startGame(LinkList *L,int n,int first_m){
	LinkList q = L;
	int firstIn = 1;
	while(n-1){
		if(firstIn){
			q = LinkDelete_L(q,first_m);
			firstIn = 0;
		}
		else	q = LinkDelete_L(q,delateQ_data);
		n--;
	}
	return q->num;
}

void main(){
	int p[30],n=0,ch,first_m;
	LinkList head;
	printf("请依次输入初始m值\n");
	scanf("%d",&first_m);
	printf("请依次输入游戏者密码，以非整数字符结束，如：3 1 7...4s \n");
	while(scanf("%d",&p[n++]));
	printf("总参加人数:n:%d\n初始m值为%d\n",n-1,first_m);
	head = creatListR(p,n-1);
	printf("游戏过程\n",n);
	printf("获胜者是%d号\n",startGame(head,n-1,first_m));
}
