/*
��Ŀ���ݣ�
 ��n������a1,a2,...an��ÿ����ai�������Ӳ�����2000. �ִ���ѡȡһЩ�������ǵĳ˻��պ���ƽ������
���ж�������ѡ������ �ٶ�n<=300, ai<=2000

��������
��һ����n
�ڶ�����n������

�������
��������Ϊ��ֹ��Ŀ���󣬽����ģ1000000007.

��������
3
3 3 4

�������
3
*/

/*
����˼·:
	����������Ȼ��n,�����Խ����ֽ�Ϊn=P1^R1 * P2^R2 * P3^R3....,(����PiΪ��������,RiΪPi��ָ��), 
	��ʽ�Ӿͽ�n�� "Ψһ�ֽ�ʽ". 
	����ƽ����N,����Ψһ�ֽ�ʽ N = P1^R1 * P2^R1 * P3^R3 *.....�е�Ri����ȫ��Ϊż��,����������
	���Ĳ�������,������һ����, ���ǶԸ�����ÿ������a1,a2,...,an�����������ֽ�,����¼��������ai
	������������Pi�ĸ���Ri,��������һ����ά������,����:
P1	R11*x1	R12*x2	R13*x3 ...	R1n*xn
P2	R21*x1	R22*x2	R23*x3 ...	R2n*xn
...	...
Pj	Ri1*x1	...		Rij*xi ...	Rin*xn
...	... 
Pm	Rm1*x1	Rm1*x2	Rm3*x3 ...	Rmn*xn
	����: 
	1) P1,P2,...,PmΪa1,a2,...,an�ֽ���������е�����.
	2) R12Ϊa2�ֽ����������P1�ĸ���,RijΪaj�ֽ����������pi�ĸ��� 
	3) xiȡֵ0��1,ȡ1��ʾѡ��ai,ȡ0��ʾ��ѡ��ai
Ҫʹ�����ѡ�������ĳ˻�N��һ����ȫƽ����,��ʽN = P1^R1 * P2^R2 * P3^R3*...*PmRm�е�ÿ��������Pi
��Ӧ��ָ��Ri����Ϊż��,���Կ��Եõ����·���:
	R11*x1 + R12*x2 + R13*x3 + ... + R1n*xn = R1
	R21*x1 + R22*x2	+ R23*x3 + ... + R2n*xn = R2
	...
	Rm1*x1 + Rm2*x2 + Rm3*x3 + ... + Rmn*xn = Rn
	����:
	1) ��Ϊxi��ȡֵΪ0��1,����Ri��ֵ��Ϊѡ������������{xi}�ֽ��������Pi���ܸ���.
	2) �����Ѿ�˵��, Ҫʹ�����˻�NΪ��ȫƽ����,��������Ri��Ϊż��
��������ֻ��Ҫ��¼Rij��Ri����������ż��,�������ǿ��Խ��������̽�һ����, 
	R11*x1 + R12*x2 + R13*x3 + ... + R1n*xn = 0 (mod 2) 
	R21*x1 + R22*x2	+ R23*x3 + ... + R2n*xn = 0 (mod 2) 
	...
	Rm1*x1 + Rm2*x2 + Rm3*x3 + ... + Rmn*xn = 0 (mod 2)
����,xi��ϵ��Rij�Ͷ���0��1��ֵ, ���ҷ��̵��ұ�ȫ�������0(֮ǰRi���붼Ϊż������ʹѡ�������ĳɼ�Ϊ
��ȫƽ����)���һ�����˺����˹��Ԫ�Ĺ���. 
�����������,���ǰ�ϵ���ö�ά���鱣������,Ȼ���ø�˹��Ԫ������þ������r,�����ɵø÷���������ɱ�
Ԫ�ĸ���n-r. ����xi��ȡֵֻ��0��1����ѡ��, �����ܵ�����������ѡ�񷽰�������2^(n-r) - 1,(��һ����Ϊ
Ҫ��ȥһ������ѡ�����,��Ϊ��ĿҪ������ѡ��һ��������)
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 2005
using namespace std;
const int MOD = 1e9+7;
int vis[maxn], p[maxn];
int mtx[maxn][500];

//�ҳ�2000���ڵ�����,������������ 
int init(){
	int cnt=0;
	for(int i=2; i<maxn; ++i)
		if(!vis[i]){
			p[cnt++] = i;
			for(int j=i*i; j<maxn; j+=i) vis[j] = 1;
		}
	return cnt;
}

long long quick_mod(long long a, long long b){
	long long res = 1;
	while(b){
		if(b&1) res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1; 
	}
	return res;
}

//��˹��Ԫ 
int Rank(int m, int n){
	int i=0,j=0,r,u;
	while(i<m && j<n){
		for(r=i; mtx[r][j]==0 && r<m; ++r);
		if(mtx[r][j]){
			if( r != i) swap(mtx[i], mtx[r]);
//			if( r != i) for(int k=0; k<n; ++k) swap(mtx[r][k],mtx[i][k]);
			for(u=i+1; u<m; ++u) if(mtx[u][j]) {
				for(int k=i; k<n; ++k) mtx[u][k] ^= mtx[i][k];
			}
			++i;
		}
		++j;
	}
	return i;
}

int main(){
#ifdef WFX
freopen("8 in.txt","r",stdin);
#endif
	int T,n;
	int cnt = init();
	scanf("%d",&T);
	for(int t=1; t<=T; ++t){
		memset(mtx,0,sizeof(mtx));
		int maxi = 0 , i;
		unsigned long long x;
		scanf("%d",&n);
		for(int j=0; j<n; ++j){
			scanf("%lld",&x);
			//��x�����������ֽ�,���������mtx������
			for(i=0; i<cnt && x!=1 ; ++i) while(x % p[i] == 0){
				x/=p[i]; mtx[i][j] ^= 1;//��1���,Ч������(mtx[j][i]+1)%2
				maxi = max(maxi,i);
			}
		}
		int free = n  - Rank( maxi+1, n );
		long long ans = quick_mod(2, free) - 1;
		printf("Case #%d:\n%lld\n", t, ans);
	}
	
	return 0;
}
