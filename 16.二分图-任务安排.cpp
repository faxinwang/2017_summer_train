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
int d;

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
			 if(d > slack[y]) d = slack[y];
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
			d = INF;
			if(dfs(x)) break;
//			int d=INF;
//			for(int y=1; y<=m; ++y) if(!vy[y] && slack[y]<d) d = slack[y];
			for(int k=1; k<=n; ++k) if(vx[k]) lx[k] -= d;
			for(int y=1; y<=m; ++y) 
				if(vy[y]) vy[y] += d;
				else slack[y] -= d;
		}
	}
	
	int ans=0;
	for(int y=1;y<=m;++y) if(match[y] != -1) ans += g[match[y]][y];
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
