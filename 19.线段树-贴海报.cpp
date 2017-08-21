/*
解题思路:
对于墙上的每一个单元, 如果该单元被某一块海报遮住了,我们就将其值设为1,否则为0.
从最后一张海报开始往前逐一操作海报:
1.对于海报i,它所占据的区间[ai,bi],如果该区间内有至少一个单元的值为0,即只要至少有一个
  单元没有被覆盖, 辣么该海报最后将是可见的,++ans(注意我们是逆序对海报进行判断的), 否则该海报
  最后将不可见.
2.将海报i所占据的区间[ai,bi]内所有的单元的值设为1.表示已被覆盖.

线段树的使用:
由于区间[ai,bi]很长(1kw ), 使用循环标记超时没商量, 所以需要使用线段树来处理区间问题. 线段树我也是
才刚开始学习, 所以关于线段树的用法和知识就不讲了.

区间压缩:
如果不进行区间压缩, 这题会超内存. 对于1kw的区间, 其线段树至少需要2kw个数组元素,
每个数组元素至少是4字节, 所以总共是2kw*4b/1024 = 78125kb, 而本题的内存限制是65535kb,
所以必须进行区间压缩. 
*/
#include<iostream>
#include<cstdio>
#include<set>
#include<map> 
#define MAXL 10005
#define MAXN 10005
using namespace std;
 
struct SegTree{
	int L,R,SUM;
};
SegTree st[MAXL*30]; // *30
int L[MAXN],R[MAXN];  
int hash[10000005]; //比使用map快

void buildTree(int l,int r,int idx=1){
	st[idx].L = l;
	st[idx].R = r;
	st[idx].SUM = 0;
	if(l==r) return; //递归基:到达叶子结点,停止建树 
	int mid = l + (r - l)/2;
	int lc = idx<<1, rc = lc+1;
	buildTree(l,mid,lc);
	buildTree(mid+1,r,rc);
}

void pushDown(int idx){
	int lc = idx<<1, rc = lc + 1;
	//如果子树没有pushDown过,才进行pushDown 
	if(st[lc].R - st[lc].L + 1 != st[lc].SUM){
		st[lc].SUM = st[lc].R - st[lc].L + 1;
		if(st[lc].L != st[lc].R) pushDown(lc); //一直pushDown到叶子节点 
	}
	if(st[rc].R - st[rc].L + 1 != st[rc].SUM){
		st[rc].SUM = st[rc].R - st[rc].L + 1;
		if(st[rc].L != st[rc].R) pushDown(rc);
	}
}

void update(int l,int r,int idx=1){
	if(l==st[idx].L && r==st[idx].R){
		st[idx].SUM = r - l + 1;
		pushDown(idx);
		return;
	}
	int mid = st[idx].L + (st[idx].R - st[idx].L)/2;
	int lc = idx<<1, rc = lc+1;
	if(r<=mid) update(l,r,lc);
	else if(mid < l) update(l,r,rc); 
	else{
		update(l, mid, lc);
		update(mid+1, r, rc);
	}
	st[idx].SUM = st[lc].SUM + st[rc].SUM; //pushUp
}

int getSum(int l,int r,int idx=1){
//	printf("%d %d %d \t %d %d\n",l,r,idx, st[idx].L, st[idx].R);
	if(st[idx].L <= l && r <= st[idx].R && st[idx].R - st[idx].L +1 == st[idx].SUM) return r - l + 1;
	if( l <= st[idx].L && st[idx].R <= r) return st[idx].SUM;
	int mid = st[idx].L + (st[idx].R - st[idx].L)/2;
	int lc = idx<<1, rc = lc+1;
	if(r <= mid) return getSum(l,r,lc);
	if(mid < l) return getSum(l,r,rc);
	return getSum(l,mid,lc) + getSum(mid+1,r,rc);
}

int main(){
#ifdef WFX
freopen("19 in2.txt","r",stdin);
#endif
	int T,n;
	scanf("%d", &T);
	while(T--){
		int ans=0;
		set<int> s;
		scanf("%d", &n);
		for(int i=1; i <= n; ++i){
			scanf("%d%d", &L[i], &R[i]);
			s.insert(L[i]);
			s.insert(R[i]);
		}
//		map<int,int> mp;
		set<int>::iterator pos = s.begin();
//		mp[*pos] = 0; 
		hash[*pos] = 0;
		int prev = *pos;  ++pos;
		//离散化.另外, 如果两个点之间的距离大于1, 那么在离散化后他们之间的距离也要大于1 
		for(int cnt=1; pos != s.end(); ++pos, ++cnt){
			int cur = *pos; 
//			if( cur - prev > 1) mp[cur] = ++cnt;
//			else mp[cur] = cnt;
			if(cur - prev > 1) hash[cur] = ++cnt;
			else hash[cur] = cnt;
			prev = cur;
		}
//		buildTree(mp[*s.begin()], mp[*s.rbegin()]);
		buildTree(hash[*s.begin()], hash[*s.rbegin()]);
		
		for(int i = n; i > 0 ; --i){
//			int l = mp[L[i]], r = mp[R[i]];
			int l = hash[L[i]], r = hash[R[i]]; 
			if( getSum(l,r) < r - l + 1) ++ans;
			update(l,r);
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
