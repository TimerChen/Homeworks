#include <cstdio>
const int N = 1E5+61;
using namespace std;
template<class T>
class Queue
{
private:
	T *dui;int dl,dr,SIZE;
	void del(){if(dui)delete []dui;dui=NULL;}
public:
	Queue(int n=0)
	:SIZE(n)
	{ dui = new T[n]; }
	~Queue(){del();}
	void clear(){dl=0;dr=-1;}
	bool empty(){return dl>dr;}
	T &top(){return dui[dl];}
	T &back(){return dui[dr];}
	int size()const{return dr-dl+1;}
	void pop_front(){if(empty())throw(0);dl++;}
	void pop_back(){if(empty())throw(0);dr--;}
	void push(const T&a){if(dr+1==SIZE)throw(1);dui[++dr]=a;}
	void resize(int n){SIZE = n;del();dui = new T[n];}
};
struct Data
{
	int i,val;
	Data(int a=0,int b=0):i(a),val(b){}
};
int n,m,data[N];
int scan(){int i=0;scanf("%d",&i);return i;}
Queue<Data>minq,maxq;
void push(int i,int val)
{
	while(!minq.empty() && minq.back().val >= val)minq.pop_back();
	minq.push(Data(i,val));
	while(!maxq.empty() && maxq.back().val <= val)maxq.pop_back();
	maxq.push(Data(i,val));
}
void pop(int i)
{
	while(!minq.empty() && minq.top().i <= i-m)minq.pop_front();
	while(!maxq.empty() && maxq.top().i <= i-m)maxq.pop_front();
}
int main()
{
	int i,j,a,b;
	n = scan();m = scan();
	minq.resize(n);
	maxq.resize(n);
	for(i=1;i<=n;++i)
	{
		a=scan();
		push(i,a);
		pop(i);
		if(i >= m)
		{
			//printf("%d",minq.top().i);
			printf("%d ",minq.top().val);
			data[i]=maxq.top().val;
		}
	}
	printf("\n");
	for(i=m;i<=n;i++)
		printf("%d ",data[i]);
	return 0;
}
