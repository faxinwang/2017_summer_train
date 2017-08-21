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
#include<algorithm>
#define maxn 50005
using namespace std;
typedef long long LL; 

LL L,N,M;
LL a[maxn];
//判断d是否可以作为上确界 
bool judge(LL d){
	LL sum=0,last=0;
	for(int i=1; i<=N; ++i){
		if(a[i] - last<= d) ++sum; //如果当前石头与上一个石头的距离<=d, 说明该石头可以拿走. 
		else last = a[i]; //否则将当前石头的位置作为下一次计算距离的last值 
	}
	//如果能移走的石头>M个,说明d是一个可行的值,接下来要测试跟小的距离,如果没有更小的可行距离, 那么当前d值就是答案.于是让High=mid 
	//如果能移走的石头<=M个, 说明可能有更大的可行的d值,接下来测试更大的距离,于是让Low = mid+1
	return sum > M;  //注意点1
}

LL bsearch(){
	LL Low =0, High=L,mid;
	while(Low < High){
		mid = Low + (High - Low)/2; 
		if(judge(mid)) High = mid; //注意点2: High变为mid而不是mid-1,因为mid有可能是最大的最短距离.
		else Low = mid +1 ;
	}
	/*注意点3: 返回的是High,因为最后退出的时候是Low==High,且倒数第二次循环的时候一定是 Low+1==High,且mid=Low 
	有两种情况导致Low==High:
		一:judge(mid)返回false,导致Low = mid+1 正好等于High, 退出循环, 此时High是上一次测试得到的可行值,
			而mid虽然可能可行(有可能judge(mid)返回的时候是sum==M), 但此时mid是小于High的. 
		二:judge(mid)返回true, High=mid == Low然后退出.
	*/
	return High; 
}

int main(){
#ifdef WFX
freopen("1 in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	while(cin>>L>>N>>M){
		for(int i=1;i <= N;++i) cin>>a[i];
		a[N+1] = L; //N+1的位置保存最后一个石头到起点的距离,为L 
		N += 1; // 有N+1段距离 
		sort(a+1,a+N+1);
		cout<<bsearch()<<endl;
	}
	
	return 0;
}
