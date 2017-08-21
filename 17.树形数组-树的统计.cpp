/*
题目内容：(poj3321)
这是数据结构中的树。 结点编号为1,2,...n. 其中1是根结点。 每个结点可涂一个颜色白或者黑.
操作者可以更改这个颜色。 

输入描述
第一行是结点数目n<=100000.接下来的n-1行是连接这n个结点的边ui, vi
然后的一行是整数m, 表示有m个操作， 接下来的m行就定义了具体操作：
“C x”意思是改变结点x的颜色
“Q x”意思是询问结点x为根的子树上有多少个白色结点。
假设初始时树的所有结点为白色

输出描述
每行是依次回答上面的每个Q x

输入样例
3
1 2
1 3
3
Q 1
C 2
Q 1

输出样例
3
2
*/ 

/*
解题思路:
由于需要求任意一个结点及以该结点为根的子树中白色节点的个数,不妨设白色结点的值为1,黑色
结点的值为0,如果给树上的所有结点按照某种顺序从1到n编号, 那么所有的结点都将处于某一个
区间中. 我们可以为每一个结点附加一个区间[a,b], a表示该结点自身的编号, b表示以当前结点为
根结点的子树中最后被编号的结点的编号,从而使得区间[a,b]中的每一个数字与以a为根结点的子树
中的每一个结点一一对应. 
 
如果要询问以a为根节点的子树上有多少个白色结点,就可以直接用c[b] - c[a-1]计算出来, 
其中c[i]表示结点1,2,..i值的和,也就是其中白色结点的个数.(这样线段树就可以应用上来了) 

如果要修改结点a的值, 相应的也要修改c数组中相应元素的值. 
*/

#include<iostream> 
#include<cstdio>
#include<vector>
#include<cstring>
#define lowbit(x) (x&-x)
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
			flg[i] = 1; //白色记为1, 黑色记为0
			add(i,1); //初始时全为白色
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
