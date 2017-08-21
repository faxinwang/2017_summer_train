/*
�����Ͽ����Ľ���˼·, �о���ʹ������ά���ӽ���븸����Ա��ϵ�ķ����򵥵ö�.
�� x+n ������ x ������, �����x��y��ͬ��, �� x �� y+n������, x+n��yҲ������. 
ÿ����һ��x,y, �����ж�x,y(����x+n,y+n)�Ƿ�������,�����,��x,y+n��ͬ��,������
�ŵ�һ��������,ͬ��x+n,yҲ��ͬ��,�ŵ�ͬһ��������ȥ.�������,��ɶ϶�����ͬ����. 
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

//���x��y����,����true, ���򷵻�false
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
			else flag = 1;  //���x��y, x+n��y+n��ͬ��, �����ͬ���� 
		}
		
		printf("Scenario #%d:\n",t);
		if(flag)	printf("Suspicious bugs found!\n");
		else		printf("No suspicious bugs found!\n");
		if(t < T)	printf("\n");
	}
	
	return 0;
}
