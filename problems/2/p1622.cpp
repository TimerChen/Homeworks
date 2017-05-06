#ifdef LOCAL
#endif
#include <cstdio>
#include <iostream>
const int N = 2E5+10;
int n,m,data[N];
/*
int randomSeed;
int randomWordGenerator(){
	randomSeed
	return randomSeed;
}*/
struct Node
{
	Node(short type=-1);
	Node *pre,*next;
	short d;int n;
}null[1];
Node::Node(short type)
{
	pre=next=null;
	d=type;
	if(type<0)n=0;else n=1;
}
struct Queue
{
	short size,rsize;
	Queue(){size=rsize=0;head=end=null;}
	Node *head,*end;
	Node &front()
	{ return *head; }
	Node &back()
	{ return *end; }
	bool empty()
	{ return size==0; }
	void push_back(short t)
	{
		if(empty())
		{
			head=end=new Node(t);
			size++;
		}else{
			if(back().d==t)
			{
				back().n++;
			}else{
				Node *l = new Node(t);
				l->pre = end;
				end->next = l;
				end = l;
				size++;
			}
		}
		rsize++;

	}
	void push_front(short t)
	{
		if(empty())
		{
			head=end=new Node(t);
			size++;
		}else{
			if(front().d==t)
			{
				front().n++;
			}else{
				Node *l = new Node(t);
				l->next = head;
				head->pre = l;
				head = l;
				size++;
			}
		}
		rsize++;
	}
	void pop_back()
	{
		if(empty())throw(1);
		back().n--;	rsize--;
		if(back().n)return;
		if(size==1)
		{
			delete end;
			head = end = null;
		}else{
			end = end->pre;
			delete end->next;
			end->next = null;
		}
		size--;
	}
	void pop_front()
	{
		if(empty())throw(1);
		front().n--;rsize--;
		if(front().n)return;
		if(size==1)
		{
			delete head;
			head=end=null;
		}else{
			head = head->next;
			delete head->pre;
			head->pre = null;
		}
		size--;
	}
}dui;
int main()
{
	//freopen("in.txt","r",stdin);
	int i,j;char str[100];
	scanf("%d",&n);
	short rev=0;
	for(i=1;i<=n;++i)
	{
		scanf(" %s",str);
		if(str[0]=='P' && str[1]=='U'){//Push
			scanf("%d",&j);
			if(!rev)dui.push_back(j);
			else dui.push_front(j);
		}else if(str[0] == 'Q'){//Query
			rev^=1;
			if(dui.rsize==0)
			{ printf("Invalid.\n"); continue; }
			if(dui.rsize==1)
			{ printf("%d\n",dui.front().d); continue;}
			if(dui.size==1)
			{
				if(dui.front().d)
					printf("%d\n",(dui.front().n&1)^1);
				else
					printf("%d\n",1);
				continue;
			}
			//size > 2
			if(!rev)
			{
				if(!dui.back().d)
					printf("%d\n",1);
				else{
					j = dui.back().n;
					if(dui.back().pre->n>1)j++;
					else if(dui.size > 2)j++;
					printf("%d\n",j&1);
				}
			}else{
				if(!dui.front().d)
					printf("%d\n",1);
				else{
					j = dui.front().n;
					if(dui.front().next->n>1)j++;
					else if(dui.size > 2)j++;
					printf("%d\n",j&1);
				}
			}
			rev^=1;
		}else if(str[0] == 'P'){//Pop
			//???
			if(dui.empty())continue;

			if(!rev)dui.pop_back();
			else dui.pop_front();
		}else{//Reverse
			rev^=1;

		}
	}
	return 0;
}
