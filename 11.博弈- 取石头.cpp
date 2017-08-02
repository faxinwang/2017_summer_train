/*
题目内容：
 m堆石子,甲乙两人轮流取，每次需先选择1堆，并取任意数目的石子. 最后取完者的获胜.
规定甲先取。
输入描述
可能有多组测试数据。每组的第一行是m, 第二行是m个整数，表示每堆石子的数目。

输出描述
每个测试用例，甲失败则输出“no”。
否则输出"yes", 并在下面的行输出取法。
    按堆号顺序输出各种甲能取胜的首次取法a,b,表示在第a堆石子中取完石子后剩下b个，甲可以获胜。

输入样例
2
45 45
3
3 6 9
5
5 7 8 9 10

输出样例
No
Yes
9 5
Yes
8 1
9 0
10 3

*/

/*
解题思路:
首先使用特殊K堆石子的xor规则判断当前局面属于P局面(必胜态)还是属于N局面(必败态)
S = n1 xor n2......xor nk
如果当前S>0,则当前处于必胜态, 如果当前S=0,则当前处于必败态.
如果当前S>0, 则一定要在取完石子后让对手处于必败态,也就是在取完石子后要让S=0,
那么怎么让S变为0呢, 先看一下徐老师ppt上的一个证明:

证明XOR规则是合理的：
1) 终结局面,S= 0 xor 0....xor 0 =0, 判定是P局面
2) 如果有一个N局面，则S = k > 0,  假设k的二进制1最高位是第h位,  必然某个ni的第h位为1，
   (否则大家都为0，不可能异或出k). 那么玩家可以让ni变成 ni'=ni xor k,(ni'是变小了)。
   那么一个局面的S'=n1... (ni xor k)... nk = (n1....nk) xor k = k xor k = 0.
   这说明N局面后面一定跟着一个P局面
3) 如果有一个P局面，则 S=n1..xor..nk =0,   操作ni变成ni' 则S' 一定不是0. 因此P局面后面的全是N局面

从上述证明中可以看出, 只要让任意一个第h位为1的ai跟k异或变成ni',就可以使局面变为必败态(S=0), 
那么取走的石子数就是ni - ni' 
*/


#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e6+5;
int a[maxn];

int main(){
#ifdef WFX
freopen("11 in.txt","r",stdin);
#endif
	int m;
	while( scanf("%d",&m)!=-1 ){
		int ans=0;
		for(int i=0;i<m;++i){
			scanf("%d",&a[i]);
			ans ^= a[i];
		}
		if(ans){
			printf("Yes\n");
			int k=1;for(int tmp=ans;tmp;tmp>>=1) k<<=1;
			k>>=1;
			for(int i=0;i<m;++i){
				if(a[i] & k) printf("%d %d\n",a[i],a[i]^ans);
			}
		}else{
			printf("No\n");
		}
	}
	
	return 0;
}
