/*
http://acm.hdu.edu.cn/showproblem.php?pid=2853
Assignment
Problem Description
Last year a terrible earthquake attacked Sichuan province. About 300,000 PLA soldiers 
attended the rescue, also ALPCs. Our mission is to solve difficulty problems to 
optimization the assignment of troops. The assignment is measure by efficiency, 
which is an integer, and the larger the better.
We have N companies of troops and M missions, M>=N. One company can get only 
one mission. One mission can be assigned to only one company. If company i takes 
mission j, we can get efficiency Eij. We have a assignment plan already, and now 
we want to change some companies¡¯ missions to make the total efficiency larger. 
And also we want to change as less companies as possible.
 

Input
For each test case, the first line contains two numbers N and M. N lines follow. 
Each contains M integers, representing Eij. The next line contains N integers. 
The first one represents the mission number that company 1 takes, and so on.
1<=N<=M<=50, 1<Eij<=10000.
Your program should process to the end of file.

Output
For each the case print two integers X and Y. X represents the number of companies 
whose mission had been changed. Y represents the maximum total efficiency can be 
increased after changing.

Sample Input
3 3
2 1 3
3 2 4
1 26 2
2 1 3
2 3
1 2 3
1 2 3
1 2
 

Sample Output
2 26
1 2

*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 55
#define maxm 55
using namespace std;
const int SCALE = 100;
const int INF = 1<<30;

int g[maxn][maxm];
int lx[maxn],ly[maxm];
bool vx[maxn],vy[maxm];
int slack[maxm],match[maxm];
int n,m;

bool dfs(int x){
	vx[x] = 1;
	for(int y=1;y<=m;++y){
		if(vy[y]) continue;
		int gap = lx[x] + ly[y] - g[x][y];
		if(gap == 0){
			vy[y] = 1;
			if(match[y]==-1 || dfs(match[y])){
				match[y] = x;
				return 1;
			}
		}else{
			 if(slack[y] > gap) slack[y] = gap;
		}
	}
	return 0;
}

int KM(){
	memset(match,-1,sizeof(match));
	memset(ly,0,sizeof(ly));
	for(int x=1;x<=n;++x){
		lx[x] = g[x][0];
		for(int y=1;y<=m;++y) if(lx[x]<g[x][y]) lx[x]=g[x][y];
	}
	for(int x=1; x<=n; ++x){
		for(int y=1; y<=m; ++y) slack[y] = INF;
		while(1){
			memset(vx,0,sizeof(vx));
			memset(vy,0,sizeof(vy));
			if(dfs(x)) break;
			int d=INF;
			for(int y=1; y<=m; ++y) if(!vy[y] && slack[y]<d) d = slack[y];
			for(int k=1; k<=n; ++k) if(vx[k]) lx[k] -= d;
			for(int y=1; y<=m; ++y) 
				if(vy[y]) ly[y] += d;
				else slack[y] -= d;
		}
	}
	
	int ans=0;
	for(int y=1; y<=m; ++y) if(match[y] != -1) ans += g[match[y]][y];
	return ans;
}

int main(){
#ifdef WFX
freopen("16 in.txt","r",stdin);
#endif
	while(scanf("%d%d",&n,&m)!=-1){ //m >= n 
		for(int x=1; x<=n; ++x){
			for(int y=1; y<=m; ++y){
				scanf("%d",&g[x][y]);
				g[x][y] *= SCALE;
			}
		}
		int old = 0,y;
		for(int x=1; x<=n; ++x){
			scanf("%d",&y);
			old += g[x][y];
			g[x][y] += 1;
		}
		int ans = KM();
		printf("%d %d\n", n - ans%SCALE, ans/SCALE - old/SCALE);
	}
	
	return 0;
}
