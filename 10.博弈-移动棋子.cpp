/*
解题思路:
如果棋子数目为偶数个, 则把第一,二个看成一组, 三,四个看成一组, 五,六个看成一组.... 
没组棋子中间的空格数看成n堆取石子游戏中某一堆石子数,然后就变成了有n堆石子,每次可以从任意
一堆中任意取石子的游戏.
如果有奇数个棋子, 则把第一个棋子前面的空格数看成一堆石子,后面的偶数个同上处理. 自己在纸上画
一条格子, 用几张小纸片模拟棋子, 拉个小伙伴走几局玩一玩,自然就能明白其中的道理. 

*/
#include<iostream>
#include<cstdio>
using namespace std;

int main(){
#ifdef WFX
freopen("10 in.txt","r",stdin);
#endif 
	int n,T;
	scanf("%d",&T);
	while(T--){
		int sum=0,x,y;
		scanf("%d",&n);
		if(n^1){
			scanf("%d",&sum);
			--sum;
			for(int i=1;i<n; i+=2){
				scanf("%d%d",&x,&y);
				sum ^= y-x-1;
			}
		}else{
			for(int i=0; i<n;i+=2){
				scanf("%d%d",&x,&y);
				sum ^= y-x-1;
			}
		}
		
		if(sum) printf("甲\n");
		else printf("乙\n"); 
	}
	
	return 0;
}

