/*
题目内容：
甲乙两人下一种棋。棋盘是一个n个连续的方格子，棋盘上随机放着m个棋子，一个格子只能放一个棋子。
玩家轮流选择一个棋子移动，移动只能从右向左，至少要移动一个格子，但不能跨越其他的棋子。
甲始终先移动。对任何一种初始局面，你能判断谁能赢？

输入描述
第一行是测试用例的数目c, 下面的行是各测试用例
每个测试用例的第一行是整数m(<=1000),表示有m个棋子,第二行是m个整数，表示每个棋子的方格编号
(左到右从1开始编号) 

输出描述
每个测试用例中赢的一方。
"甲"或者"乙"或者"不确定"

输入样例
2
3
1 2 3
8
1 5 6 7 9 12 14 17

输出样例
乙
甲

*/
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
		if(n^1){ //奇数个棋子, 则先读入第一个棋子的位置 
			scanf("%d",&sum);
			--sum;
			for(int i=1;i<n; i+=2){
				scanf("%d%d",&x,&y); //每次读取两个棋子的位置, 计算中间有多少个空格 
				sum ^= y-x-1;
			}
		}else{
			for(int i=0; i<n;i+=2){
				scanf("%d%d",&x,&y);
				sum ^= y-x-1;
			}
		}
		
		if(sum) printf("甲\n"); //如果最后异或的结果不为0,则先手胜利,否则后手胜利. 
		else printf("乙\n"); 
	}
	
	return 0;
}

