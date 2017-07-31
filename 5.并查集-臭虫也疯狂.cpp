/*
题目内容：
 霍普教授研究臭虫的性取向。实验前他弄清楚了n个臭虫的性别，并在臭虫的背上标了数
字编号（1~n）。现在给一批臭虫的编号配对，要检查里面有没有同性恋。
输入描述
第一行是整数c,下面接着有c个测试用例。
每个测试用例的第一行是臭虫的数目n（1~2000），以及配对的数目m（1~10^6）。接下来
的行就是m个配对的臭虫编号.

输出描述
一共c行， 每行打印“testcase i:没发现同性恋”,或者“testcase i:发现同性恋”

输入样例
2
3 3
1 2
2 3
1 3
4 2
1 2
3 4

输出样例
testcase 1:发现同性恋
testcase 2:没有发现同性恋

*/

/*
解题思路:
用并查集解决的题目都不太好描述, 因为并查集描述的是一个树型结构,算法思想都是建立在这
个树形结构上的. 在代码中通常用数组来表示这棵树.


*/ 

#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 2005
using namespace std;

int p[maxn]; //p[i]为i的父结点(路径压缩后将指向根节点)
int r[maxn]; //r[i]=0表示i与p[i]是同性，r[i]=1表示i与p[i]是异性 

void init(){
	memset(p,-1,sizeof(p));
	memset(r,0,sizeof(r));
//	for(int i=0,n=sizeof(r)/sizeof(int); i<n;++i) r[i] = 1;
}

//查找并返回a所在树的根结点. 
//同时压缩路径, 让搜索路径上的所有子结点指向根结点. 
//同时更新每个结点与根结点的性别关系. 
int Find(int a){
	if(p[a]==-1) return a;
	int pa = p[a];
	p[a] = Find(pa);
	//整个过程中树的高度不会超过3层,  
	//此处r[a]如果处于第三层,则通过它与直接父节点的性别关系计算出它与根结点的性别关系
	//如果他处于第二层,则其与根结点的性别关系将保持不变. 
	r[a] = (r[a]+r[pa]) % 2; 
	return p[a]; //此时p[a]已经指向了根结点，所以返回的是根结点 
}

//将结点a所在的树 与 结点b所在的树合并. 
//同时算出被做为子结点的根结点与另外一个根结点的性别关系
void Union(int a,int b){
	int pa = Find(a);
	int pb = Find(b);
	p[pa] = pb;
	//此处分四种情况讨论,
	r[pa] = (r[a] + r[b] + 1) % 2;
}


int main(){
#ifdef WFX
freopen("5 in.txt","r",stdin);
#endif

	int T,n,m,a,b;
	scanf("%d",&T);
	
	for(int t=1;t<=T;++t){
		init();
		bool flag=1;
		scanf("%d%d",&n,&m);
		int fa,fb;
		for(int i=0;i<m;++i){
			scanf("%d%d",&a,&b);
			if(flag){ //没有发现同性恋就继续处理, 一旦发现有同性恋就不需要再做任何处理了 
			 	//如果a,b属于同一个集合 
			 	fa = Find(a),fb=Find(b);
				if(fa==fb){
					//并且他们跟根节点有相同的关系(都跟根结点是同性/异性)
					//就说明他们是同性恋 
					if(r[a] == r[b]) flag=0;
				}else Union(a,b); //否则将他们放到同一个集合中 
			}
		}
		if(flag){
			printf("testcase %d:没有发现同性恋\n",t);
		}else{
			printf("testcase %d:发现同性恋\n",t);
		}
	}
	
	return 0;
}
