/*
��Ŀ���ݣ�(poj3321)
�������ݽṹ�е����� �����Ϊ1,2,...n. ����1�Ǹ���㡣 ÿ������Ϳһ����ɫ�׻��ߺ�.
�����߿��Ը��������ɫ�� 

��������
��һ���ǽ����Ŀn<=100000.��������n-1����������n�����ı�ui, vi
Ȼ���һ��������m, ��ʾ��m�������� ��������m�оͶ����˾��������
��C x����˼�Ǹı���x����ɫ
��Q x����˼��ѯ�ʽ��xΪ�����������ж��ٸ���ɫ��㡣
�����ʼʱ�������н��Ϊ��ɫ

�������
ÿ�������λش������ÿ��Q x

��������
3
1 2
1 3
3
Q 1
C 2
Q 1

�������
3
2
*/ 

/*
����˼·:
������Ҫ������һ����㼰�Ըý��Ϊ���������а�ɫ�ڵ�ĸ���,�������ɫ����ֵΪ1,��ɫ
����ֵΪ0,��������ϵ����н�㰴��ĳ��˳���1��n���, ��ô���еĽ�㶼������ĳһ��
������. ���ǿ���Ϊÿһ����㸽��һ������[a,b], a��ʾ�ý������ı��, b��ʾ�Ե�ǰ���Ϊ
��������������󱻱�ŵĽ��ı��,�Ӷ�ʹ������[a,b]�е�ÿһ����������aΪ����������
�е�ÿһ�����һһ��Ӧ. 
 
���Ҫѯ����aΪ���ڵ���������ж��ٸ���ɫ���,�Ϳ���ֱ����c[b] - c[a-1]�������, 
����c[i]��ʾ���1,2,..iֵ�ĺ�,Ҳ�������а�ɫ���ĸ���.(�����߶����Ϳ���Ӧ��������) 

���Ҫ�޸Ľ��a��ֵ, ��Ӧ��ҲҪ�޸�c��������ӦԪ�ص�ֵ. 
*/

#include<iostream> 
#include<cstdio>
#include<vector>
#include<cstring>	
#define lowbit(x) ((x)&(-x))
#define maxn 100005
using namespace std;
int n,m,num;
int lef[maxn],rig[maxn],c[maxn],flg[maxn];
vector<vector<int> >  tree(maxn);

void add(int x,int d){
	while(x<=n){
		c[x] += d;
		x += lowbit(x);
	}
}

int sum(int x){
	int s = 0;
	while(x>0){
		s += c[x];
		x -= lowbit(x);
	}
	return s;
}

void dfs(int u){
	lef[u] = num;
	for(int v=0; v<tree[u].size(); ++v){
		++num;
		dfs(tree[u][v]);
	}
	rig[u] = num;
}

int main(){
#ifdef WFX
freopen("17 in.txt","r",stdin);
#endif
	int a,b,x;
	char op[3];
	while(scanf("%d",&n) != -1){
		memset(lef,0,sizeof(lef));
		memset(rig,0,sizeof(rig));
		memset(c,0,sizeof(c));
		for(int i=1; i<=n; ++i) tree[i].clear();
		
		for(int i=1;i<n;++i){ //n-1 edge 
			scanf("%d%d",&a,&b);
			tree[a].push_back(b);
		}
		num = 1;
		for(int i=1;i<=n;++i){
			flg[i] = 1; //��ɫ��Ϊ1, ��ɫ��Ϊ0
			add(i,1); //��ʼʱȫΪ��ɫ
		}
		dfs(1);
		scanf("%d",&m);
		while(m--){
			scanf("%s%d",op,&x);
			if(op[0]=='Q'){
				printf("%d\n", sum(rig[x]) - sum(lef[x]-1) );
			}else{
				if(flg[x]) 	add(lef[x], -1);
				else 		add(lef[x], 1);
				flg[x] = !flg[x];
			}
		}
	}
	
	
	return 0;
}
