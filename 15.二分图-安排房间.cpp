/*
题目链接: 
http://acm.hdu.edu.cn/showproblem.php?pid=2444
题目内容：
有一群学生，他们之间有的人相互认识。现在要求把学生分成2组，其中同一个组的人相互不
认识。如果可以把他们分成两组，那么就安排双人间，安排的规矩是两个人分别属于不同的组，并且认识。

输入描述
可能有多组测试数据,对每组测试数据 
首先输入两个整数n,m，表示有n个学生， m个认识对
随后m行表示认识的学生对。

输出描述
如果不能分组成功则输出“No”
否则输出有多少个房间安排学生配对。

输入样例
4 4
1 2
1 3
1 4
2 3
6 5
1 2
1 3
1 4
2 5
3 6

输出样例
No
3
*/ 

/*
解题思路:
首先判断给定的图是否可以二分:
	用DFS对图中所有结点用两种颜色进行染色,如果染色后"所有结点与相连的结点不同色",
	则说明该图是可以二分的,否则不可以二分.
如果判定给定的图可以二分,则用匈牙利算法求该二分图的最大匹配数.
*/ 

#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define maxn 205
using namespace std;

vector<int> g[maxn];
int color[maxn]; //兼任vis数组和color染色标记数组,-1表示未染色,0,1表示被染色为0,1 
int match[maxn]; //保存配对的点.match[i]为i的匹配点
int route[maxn]; //9.0表示不在交替路径上,1表示在交替路径上 

bool dfs(int u){
	for(int i=0,n=g[u].size(); i<n; ++i){
		int v = g[u][i]; //对u的第i个连接点v 
		if(!route[v]){ //如果v不在交替路径上, 就把它放到交替路径上 
			route[v]=1;
			if(match[v]== 0 ||dfs(match[v])){
				match[u] = v;
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}
//匈牙利算法求二分图最大匹配数 
int hungarian(int n){
	int ans = 0 ;
	vector<int> X,Y;
	X.reserve(n);
	Y.reserve(n);
	for(int i=1;i<=n;++i)
		if(color[i]) X.push_back(i);
		else Y.push_back(i);
	if(X.size() > Y.size()) X.swap(Y);
	
	for(int i=0,n=X.size(); i<n; ++i){
		if(match[X[i]] == 0){
			memset(route,0,sizeof(route));
			if(dfs(X[i])) ++ans;
		}
	}
	return ans;
}

bool divFlag=true; 
//参数为当前节点和当前节点的颜色 
void dfs(int u,int col){
	color[u] = col; //对当前节点进行染色 
	for(int i=0,n=g[u].size(); i < n; ++i){ 
		int v = g[u][i]; //访问当前结点的连接点v 
		if(color[v] == col){ //如果v点已经染色,且颜色与当前结点相同,说明无法分组
			divFlag = false;
			return;
		}else if(color[v] == -1){ //如果v点未染色, 则访问该结点 
			dfs(v, (col+1) % 2 );
		}
	}
}
//判断给定的无向图是否可分 
bool dividable(int n){
	for(int i=1; divFlag && i<=n; ++i){
		if(color[i] == -1) dfs(i,0); //未被染色,从该点进行dfs
	}
	return divFlag;
}

int main(){
#ifdef WFX
freopen("15 in.txt","r",stdin);
#endif
	int a,b;
	int n,m;//n students , m pairs
	while(scanf("%d%d",&n,&m) != EOF){
		memset(color,-1,sizeof(color));
		memset(match,0,sizeof(match));
		for(int i=0; i<m; ++i){
			scanf("%d%d",&a,&b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		
		divFlag = true; 
		if( dividable(n) ){
			printf("%d\n", hungarian(n));
		}else{
			printf("No\n");
		}
		for(int i=1; i<=n; ++i) g[i].clear();
	}
	
	return 0;
}
