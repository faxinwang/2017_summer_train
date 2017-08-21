/*
在网上看到的解题思路, 感觉比使用数组维护子结点与父结点性别关系的方法简单得多.
把 x+n 看成是 x 的异性, 则如果x与y是同性, 则 x 与 y+n是异性, x+n与y也是异性. 
每输入一对x,y, 首先判断x,y(或者x+n,y+n)是否是异性,如果是,则x,y+n是同性,把他们
放到一个集合中,同理x+n,y也是同性,放到同一个集合中去.如果不是,则可断定存在同性恋. 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 2005
using namespace std;

int p[maxn*2];

int Find(int x){
	if(p[x] == -1) return x;
	return p[x] = Find(p[x]);
}

void Union(int x,int y){ 
	int px = Find(x);
	int py = Find(y);
	if(px != py) p[px] = py;
}

//如果x和y异性,返回true, 否则返回false
inline bool judge(int x,int y){
	return Find(x)!=Find(y);
}

int main(){
#ifdef WFX
freopen("5 in.txt","r",stdin);
#endif
	int T,n,m,x,y;
	scanf("%d",&T);
	for(int t=1; t<=T; ++t){
		memset(p,-1,sizeof(p));
		scanf("%d%d",&n,&m);
		bool flag = 0;
		for(int i=0; i<m; ++i){
			scanf( "%d%d",&x, &y );
			if( flag ) continue;
			if( judge(x,y) || judge(x+n,y+n) ) Union(x,y+n), Union(x+n,y); 
			else flag = 1;  //如果x和y, x+n和y+n都同性, 则存在同性恋 
		}
		
		printf("Scenario #%d:\n",t);
		if(flag)	printf("Suspicious bugs found!\n");
		else		printf("No suspicious bugs found!\n");
		if(t < T)	printf("\n");
	}
	
	return 0;
}
