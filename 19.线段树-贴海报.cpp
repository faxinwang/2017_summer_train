/*
����˼·:
����ǽ�ϵ�ÿһ����Ԫ, ����õ�Ԫ��ĳһ�麣����ס��,���Ǿͽ���ֵ��Ϊ1,����Ϊ0.
�����һ�ź�����ʼ��ǰ��һ��������:
1.���ں���i,����ռ�ݵ�����[ai,bi],�����������������һ����Ԫ��ֵΪ0,��ֻҪ������һ��
  ��Ԫû�б�����, ��ô�ú�������ǿɼ���,++ans(ע������������Ժ��������жϵ�), ����ú���
  ��󽫲��ɼ�.
2.������i��ռ�ݵ�����[ai,bi]�����еĵ�Ԫ��ֵ��Ϊ1.��ʾ�ѱ�����.

�߶�����ʹ��:
��������[ai,bi]�ܳ�(1kw ), ʹ��ѭ����ǳ�ʱû����, ������Ҫʹ���߶�����������������. �߶�����Ҳ��
�Ÿտ�ʼѧϰ, ���Թ����߶������÷���֪ʶ�Ͳ�����.

����ѹ��:
�������������ѹ��, ����ᳬ�ڴ�. ����1kw������, ���߶���������Ҫ2kw������Ԫ��,
ÿ������Ԫ��������4�ֽ�, �����ܹ���2kw*4b/1024 = 78125kb, ��������ڴ�������65535kb,
���Ա����������ѹ��. 
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
int hash[10000005]; //��ʹ��map��

void buildTree(int l,int r,int idx=1){
	st[idx].L = l;
	st[idx].R = r;
	st[idx].SUM = 0;
	if(l==r) return; //�ݹ��:����Ҷ�ӽ��,ֹͣ���� 
	int mid = l + (r - l)/2;
	int lc = idx<<1, rc = lc+1;
	buildTree(l,mid,lc);
	buildTree(mid+1,r,rc);
}

void pushDown(int idx){
	int lc = idx<<1, rc = lc + 1;
	//�������û��pushDown��,�Ž���pushDown 
	if(st[lc].R - st[lc].L + 1 != st[lc].SUM){
		st[lc].SUM = st[lc].R - st[lc].L + 1;
		if(st[lc].L != st[lc].R) pushDown(lc); //һֱpushDown��Ҷ�ӽڵ� 
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
		//��ɢ��.����, ���������֮��ľ������1, ��ô����ɢ��������֮��ľ���ҲҪ����1 
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
