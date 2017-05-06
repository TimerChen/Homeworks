#include <cstdio>
const int N = 1E5+10;
const int TN = 4*N;
const long long MAX = 1E16;
template<class T>
T max(const T&a, const T&b){return a<b?b:a;}
typedef long long ll;
struct Point
{
	int d;Point *next;
	Point (){next=NULL;}
	void push(int a)
	{
		Point *l = new Point;
		l->d = a;l->next=next;
		next=l;
	}
}point[N];
int scan(){int i=0;scanf("%d",&i);return i;}
int n,m,data[N],dfn[N][2],DFN,list[2*N];
int Tn,ROOT;
short v[N];
void dfs(int x=1)
{
	v[x] = 1;
	dfn[x][0] = ++DFN;
	list[DFN] = x;
	for(Point *i = point[x].next;i;i=i->next)
	if(!v[i->d]){
		dfs(i->d);
	}
	v[x] = 0;
	dfn[x][1] = ++DFN;
	list[DFN] = -x;

}
struct Node
{
	Node(){l=-1;}
	ll tree,lmax,tmax;
	int lson,rson,l,r;
	void set(int x)
	{
		if(list[x] < 0)
		{
			tree = -data[-list[x]];
			tmax = -MAX;
		}else
		{
			tree = data[list[x]];
			tmax = tree;
		}
		lmax = tree;
		l=r=x;
	}
	Node &operator = (const Node &a)
	{
		l=a.l;r=a.r;
		tree=a.tree;tmax=a.tmax;lmax=a.lmax;
		return *this;
	}
}tree[TN];

Node operator + (const Node &a, const Node &b)
{
	Node c;
	if(a.l==-1)return b;if(b.l==-1)return a;
	if(a.r+1!=b.l)throw(1);
	c.l=a.l;c.r=b.r;
	c.tree = a.tree + b.tree;
	c.lmax = max(c.tree, a.tree+b.lmax);
	c.lmax = max(c.lmax, a.lmax);
	c.tmax = max(a.tmax, a.tree+b.tmax);
	if(list[c.r] > 0)
		c.tmax = max(c.tmax, c.lmax);
	return c;
}
int Build(int l=1,int r=DFN)
{
	int ro = ++Tn;
	if(l < r)
	{
		int mid = (l+r)/2;
		tree[ro].lson = Build(l,mid);
		tree[ro].rson = Build(mid+1,r);
		tree[ro] = tree[tree[ro].lson] + tree[tree[ro].rson];
	}else{
		tree[ro].set(l);
	}
	return ro;
}
void change(int x,int ro=ROOT,int l=1,int r=DFN)
{
	if(l==r){tree[ro].set(x);return;}
	int mid = (l+r)/2;
	if(x<=mid)change(x,tree[ro].lson,l,mid);
	else change(x,tree[ro].rson,mid+1,r);
	tree[ro] = tree[tree[ro].lson] + tree[tree[ro].rson];
}
ll ask_sum(int la,int ra,int ro=ROOT,int l=1,int r=DFN)
{
	if(la > ra)return 0;
	if(la<=l&&r<=ra)return tree[ro].tree;
	ll re=0;int mid = (l+r)/2;
	if(la<=mid)re+=ask_sum(la,ra,tree[ro].lson,l,mid);
	if(mid+1<=ra)re+=ask_sum(la,ra,tree[ro].rson,mid+1,r);
	return re;
}
Node ask_max(int la,int ra,int ro=ROOT,int l=1,int r=DFN)
{
	if(la<=l&&r<=ra)return tree[ro];
	Node re;int mid = (l+r)/2;
	if(la<=mid)re=ask_max(la,ra,tree[ro].lson,l,mid);
	if(mid+1<=ra)re=re+ask_max(la,ra,tree[ro].rson,mid+1,r);
	return re;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int i,j,a,b;
	n = scan();m = scan();
	for( i = 1;i < n; ++i )
	{
		a=scan();b=scan();
		point[a].push(b);
		point[b].push(a);
	}
	for(i=1;i<=n;++i)
		data[i]=scan();
	dfs();
	ROOT = Build();
	for(i=1;i<=m;++i)
	{
		if(scan())
		{
			a=scan();
			ll ans = ask_sum(1,dfn[a][0]-1);
			ans += ask_max(dfn[a][0],dfn[a][1]).tmax;
			printf("%lld\n",ans);
		}else{
			a=scan();b=scan();
			data[a]=b;
			change(dfn[a][0]);
			change(dfn[a][1]);
		}
	}
	return 0;
}
