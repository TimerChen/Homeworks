#include <cstdio>
#include "map.hpp"
#include <map>
#include "utility.hpp"
#include <string>
int n,m;
struct Data{
	static int counter;
	int d;
	Data(const Data &a){d=a.d;counter++;}
	Data(int a=0){d=a;counter++;}
	~Data(){counter--;}
};
int Data::counter = 0;
bool operator < (const Data&a, const Data&b)
{
	return a.d < b.d;
}
sjtu::map<int,Data>hash;
std::map<int,int>hash2;
int main()
{
	int i,j;
	//scanf("%d",&n);
	n = 3;
	for(i=0;i<n;i++)
	{
		//hash.insert(sjtu::pair<int,int>(i,i));
		hash[i]=i;
		//printf("%d\n",hash.ROOT->height);
	}
	//hash.erase(hash.find(n/2));
	/*
	for(i=0;i<n;++i)
	{
		if(1896<i && i<=2016)
			continue;
		if(!hash.count(i))
		{
			printf("%d:%d\n",i,hash.count(i));

		}else hash.erase(hash.find(i));
	}*/
	//hash.erase(hash.find(2000));
	sjtu::map<int,Data>::iterator mi;
	int cot=0;
	//hash.erase(hash.find(2));
	/*
	cot = 0;mi = hash.begin();
	while(mi != hash.end())
	{
		printf("%d\n",mi->second);
		mi++;cot++;
	}*/
	//return 0;

	printf("%d\n",Data::counter);
	sjtu::map<int,Data>copy(hash);
	copy.erase(copy.find(2));

	hash=copy;


	copy.clear();

	printf("left:%d\n",Data::counter);
	mi = hash.begin();
	cot = 0;
	printf("size:%d\n",hash.size());
	hash.clear();
	printf("left:%d\n",Data::counter);
	return 0;
}
