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
并查集有两个常用的接口:
Find(x): 查询x结点所在树的根结点
Union(a,b): 合并a,b两个结点所在的树(也有人写作merge(a,b))
本题的主要难点在于理解r[]数组如何表示和维护子结点与父结点或根节点之间的性别关系. 
由于此处实现的Find()函数进行了路径压缩, 导致所有的树不会超过2层, 两颗树合并后不会超过3层.
当两颗树合并后, 有颗树中原本处于第二层的子结点会变到第三层,当再次进行路径压缩让这些结点重新
回到第二层时,就需要利用它与其父节点的性别关系计算出它与根结点的性别关系.这也是整个程序的难点所在. 
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
	//初始情况下所有的结点都是一颗独立的树,根节点就是它自己,r[i]均为0 
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
	/*
	此处分五种情况讨论:
	1.如果a,b都是根结点,则pa=a,pb=b,r[a]和 r[b]都是0,
		则r[pa] = (r[a]+r[b]+1) % 2 =1,满足pa与pb必须异性是的关系 
		
	如果a,b都不是根结点,则分以下四种情况讨论 
	2.如果a与pa性别相同, b与pb性别相同,则r[a]为0,r[b]为0, r[pa] = (r[a]+r[b]+1)%2 = 1 % 2 = 1
		满足pa与pb必须性别不同的关系(如果pa与pb性别相同,则a,b性别也相同)
		
	3.如果a与pa性别不同, b与pb性别相同,则r[a]为1,r[b]为0, r[pa] = (r[a]+r[b]+1)%2 = 2 % 2 = 0 
		满足pa与pb必须性别相同的关系 
	
	4.如果a与pa性别相同, b与pb性别不同,则r[a]为0,r[b]为1, r[pa] = (r[a]+r[b]+1)%2 = 2 % 2 = 0
		满足pa与pb必须性别相同的关系 
	
	5.如果a与pa性别不同, b与pb性别不同,则r[a]为1,r[b]为1, r[pa] = (r[a]+r[b]+1)%2 = 3 % 2 = 1
		满足pa与pb必须性别不同的关系 
		 
	如果a,b一个是根结点,一个是叶结点:
	1.如果a是根结点,b是叶结点, 则pa=a, r[a] = 0,
		如果b与根结点同性, 则r[b] = 0, r[pa] = ( r[a] + r[b] + 1 )%2 = 1, 满足pa必须与pb性别不同的关系.
		如果b与根节点异性, 则r[b] = 1, r[pa] = ( r[a] + r[b] + 1 )%2 = 0,  满足pa必须与pb性别相同的关系.
	2.同理, a是叶结点,b是根节点时也能得到正确的结果. 
	
	所以下式总是可以正确计算出两颗树合并后两个根节点之间的性别关系
	在更新r[pa]的值后, pa的子结点与pa的性别关系可能会出错(当pa不等于a的时候),但这个会在下一次查询其子结
	点时在Find()函数中被更新为正确值.
	*/
	r[pa] = (r[a] + r[b] + 1) % 2;
}


int main(){
#ifdef WFX
freopen("5 in.txt","r",stdin);
#endif

	int T,n,m,a,b,fa,fb;
	scanf("%d",&T);
	
	for(int t=1; t<=T; ++t){
		init();
		bool flag  = 0;
		scanf("%d%d",&n,&m);
		for(int i=0;i<m;++i){
			scanf("%d%d",&a,&b);
			if(flag) continue; //一旦发现有同性恋就不需要再做任何处理了 
			//如果a,b属于同一个集合 
			fa = Find(a),fb=Find(b);
			if(fa==fb){
				//并且他们跟根节点有相同的关系(都跟根结点是同性/异性)
				//就说明他们是同性恋 
				if(r[a] == r[b]) flag=1;
			}else Union(a,b); //否则将他们放到同一个集合中
		}
		if(flag)	printf("Scenario #%d:\nSuspicious bugs found!\n",t);
		else		printf("Scenario #%d:\nNo suspicious bugs found!\n",t);
//		for(int i=1; i<=n; ++i) printf("%d ",r[i]);
		if(t<T) 	printf("\n");
	}
	
	return 0;
}
