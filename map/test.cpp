#include <cstdio>
#include "map.hpp"
#include <map>
#include "utility.hpp"
#include <algorithm>
#include <string>
#include <ctime>
#include <iostream>
const int N = 1E5+10;
int n,m,list[N];
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
short v[N];
sjtu::map<int,Data>hash;
std::map<int,int>hash2;
int main()
{
	int seed = time(0);
	seed = 1493961569;
	srand(seed);
	printf("%d\n",seed);
	//1493961516 10
	int i,j;
	//scanf("%d",&n);
	n = 5;

	for(i=1;i<=n;++i)
	{
		list[i]= i;
		list[n+i] = i;
	}
	sjtu::map<int,Data>::iterator mi;
	std::random_shuffle(list+1,list+1+n*2);
	for(i=1;i<=n;++i)
	{
		DEBUG = i;
		//printf("[%d] :%d\n",i,list[i]);
		std::cout << "Time:" << i << std::endl;
			hash.debug_p();

		if(v[list[i]]){
			v[list[i]]=0;
			mi = hash.find(list[i]);
			if(mi == hash.end())
				throw(0);
			//hash.debug(mi);
			//return 0;
			mi.debug() ;
			hash.erase(mi);
		}else{
			hash[list[i]] = list[i];
			v[list[i]] = 1;
		}
		//if(i==4)return 0;
	}
	printf("Stage 1 finished.\n");
	return 0;
	for(mi=hash.begin();mi!=hash.end();++mi)
	{
		printf("%d %d\n",mi->first,mi->second.d);
	}
	printf("Stage 2 finished.\n");
	//printf("left:%d\n",Data::counter);
	return 0;
}
