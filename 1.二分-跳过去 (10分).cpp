/*
题目内容：
  “跳过去”比赛将在一条河中进行，河中分布着一些大石头。组委会选择了两块石头作为比赛起点和终点。
在起点和终点之间，有 N 块石头（不含起点和终 点的岩石）。比赛时选手们将从起点出发，每一步跳向
下一块石头，直到终点。
为了提高比赛难度，组委会计划移走一些石头，使得选手们在比赛过程中的最短跳跃距离尽可能长。由于
预算限制，组委会至多从起点和终点之间移走 M 块石头（不能移走起点和终点的石头）。

输入描述：
输入第一行包含3个整数 L,N，M，表示起点和终点的距离，之间的岩石数，以及组委会至多移走的岩石数。
接下来 N 行，每行一个整数，第 i 行的整数0<d?[i]<L, 表示中间依次的每块石头与起点的距离，保证
d[i]<d[i+1]

其中L<=10^9, M<N-2<=10^5

输出描述：
最短跳跃距离的最大值

输入样例：
25 5 2
2
11
14
17
21

输出样例
4
*/ 

/*
解题思路:(二分搜索) 
 首先确定上下界: Low=0, High=L;
 对于每一个mid = Low + (High-Low)/2; 尝试将其当做上确界,统计能移走的石头数量Sum. 
 	如果Sum>M,  说明mid值过大,不可以作为上确界,需要测试更小的mid值
 	如果sum<=M, 说明肯定有更大的mid值可以作为上确界,需要测试更大的mid值

时间复杂度: NLog(L)
*/

#include<iostream>
#include<cstdio>
#define maxn 100005
using namespace std;

int L,N,M;
int a[maxn];
//假设d是否可以作为上确界 
int judge(int d){
	int sum=0,last=0;
	for(int i=1; i<=N; ++i){
		if(a[i] - last<= d) ++sum; //如果当前石头与上一个石头的距离<=d, 说明该石头可以拿走. 
		else last = a[i]; //否则将当前石头的位置作为下一次计算距离的last值 
	}
//	printf("sum=%d ",sum);
	//如果能移走的石头多余M个,说明d值过大,不可以作为上确界,需要测试更小的d值: High = mid;
	//如果能移走的石头<=M 个, 说明肯定有更大的d值可以作为上确界,需要测试更大的d值:Low = mid+1; 
	return sum > M; 
}

int bsearch(){
	int Low =0, High=L,mid;
	while(Low < High){
		mid = Low + (High - Low)/2; 
		if(judge(mid)) High = mid;
		else Low = mid +1 ;
	}
	return mid;
}

int main(){
#ifdef WFX
freopen("1 in.txt", "r", stdin);
#endif
	scanf("%d%d%d",&L,&N,&M);
	for(int i=1;i <= N;++i) scanf("%d",a+i);
	a[N+1] = L; //N+1的位置保存最后一个石头到起点的距离,为L 
	N += 1; // 有N+1段距离 
	
	printf("%d",bsearch());
	
	return 0;
}
