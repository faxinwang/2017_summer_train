/*
��Ŀ����: 
http://acm.hdu.edu.cn/showproblem.php?pid=2444
��Ŀ���ݣ�
��һȺѧ��������֮���е����໥��ʶ������Ҫ���ѧ���ֳ�2�飬����ͬһ��������໥��
��ʶ��������԰����Ƿֳ����飬��ô�Ͱ���˫�˼䣬���ŵĹ���������˷ֱ����ڲ�ͬ���飬������ʶ��

��������
�����ж����������,��ÿ��������� 
����������������n,m����ʾ��n��ѧ���� m����ʶ��
���m�б�ʾ��ʶ��ѧ���ԡ�

�������
������ܷ���ɹ��������No��
��������ж��ٸ����䰲��ѧ����ԡ�

��������
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

�������
No
3
*/ 

/*
����˼·:
�����жϸ�����ͼ�Ƿ���Զ���:
	��DFS��ͼ�����н����������ɫ����Ⱦɫ,���Ⱦɫ��"���н���������Ľ�㲻ͬɫ",
	��˵����ͼ�ǿ��Զ��ֵ�,���򲻿��Զ���.
����ж�������ͼ���Զ���,�����������㷨��ö���ͼ�����ƥ����.
*/ 

#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define maxn 205
using namespace std;

vector<int> g[maxn];
int color[maxn]; //����vis�����colorȾɫ�������,-1��ʾδȾɫ,0,1��ʾ��ȾɫΪ0,1 
int match[maxn]; //������Եĵ�.match[i]Ϊi��ƥ���
int route[maxn]; //9.0��ʾ���ڽ���·����,1��ʾ�ڽ���·���� 

bool dfs(int u){
	for(int i=0,n=g[u].size(); i<n; ++i){
		int v = g[u][i]; //��u�ĵ�i�����ӵ�v 
		if(!route[v]){ //���v���ڽ���·����, �Ͱ����ŵ�����·���� 
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
//�������㷨�����ͼ���ƥ���� 
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
//����Ϊ��ǰ�ڵ�͵�ǰ�ڵ����ɫ 
void dfs(int u,int col){
	color[u] = col; //�Ե�ǰ�ڵ����Ⱦɫ 
	for(int i=0,n=g[u].size(); i < n; ++i){ 
		int v = g[u][i]; //���ʵ�ǰ�������ӵ�v 
		if(color[v] == col){ //���v���Ѿ�Ⱦɫ,����ɫ�뵱ǰ�����ͬ,˵���޷�����
			divFlag = false;
			return;
		}else if(color[v] == -1){ //���v��δȾɫ, ����ʸý�� 
			dfs(v, (col+1) % 2 );
		}
	}
}
//�жϸ���������ͼ�Ƿ�ɷ� 
bool dividable(int n){
	for(int i=1; divFlag && i<=n; ++i){
		if(color[i] == -1) dfs(i,0); //δ��Ⱦɫ,�Ӹõ����dfs
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
