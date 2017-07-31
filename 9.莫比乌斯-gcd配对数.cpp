/*
题目内容：
给你5个整数a,b,c,d,k, 求满足a <= x <= b && c <= y <= d && gcd(x,y)=k 的数对(x,y)的对数。
规定（x,y）和（y,x）不重复计数。
输入描述
第一行输入测试用例的个数n, 接下来是n行测试用例
每行测试用例包括a b c d k共5个数，其中 0 < a <= b <= 100,000,
 0 < c <= d <= 100,000, 0 <= k <= 100,000, 

（为了简单起见，可以假设a=c=1）

输出描述
输出n行， 每行是一个测试用例中的对数。

输入样例
2
1 3 1 5 1
1 11014 1 14409 9

输出样例
9
736427
*/

/*
参考 http://blog.csdn.net/lixuepeng_001/article/details/50577932 

解题思路:
看了很多博客才慢慢搞懂了. 下面说一下自己的理解. 
首先看一下莫比乌斯函数mu(x)的定义: 
1) 若 x = 1, 则 mu(x) = 1
2) 若 x = P1*P2* ... * Pk,(Pi均为质数) 则 mu(x)=pow(-1,k)
3) 其他情况下, mu(x) = 0 

对莫比乌斯函数,有两个反演公式:
F(n) = Sum{ (d|n)| f(d) }  ---->  f(n) = Sum{ (d|n)| F(n/d)*mu(d) }
F(n) = Sum{ (n|d)| f(d) }  ---->  f(n) = Sum{ (n|d)| F(d)*mu(d/n) }
第一种:就是说如果函数F(n)等于所有f(d)的和(其中d为n所有的约数),
则f(n)等于所有F(n/d)*mu(d)的和. 
第二种: 就是说如果函数F(n)等于所有f(d)的和(其中d是n的倍数),
则f(n)等于所有F(d)*mu(d/n)的和(本题使用的正式这个公式). 

既然这题可以用莫比乌斯反演, 那我们就需要构造出符合这种条件的F()函数和f()函数:
定义: 
对a <= x <= b, c <= y <= d:
f(n) 为 gcd(x,y)=n 的数对(x,y)的数目 
F(n) 为 gcd(x,y)=k*n 的数对(x,y)的数目(k=1,2,3,...)
则 F(n) = Sum{ (n|d)| f(d) }, 从而得到 f(n) = Sum{ (n|d) | F(d)*mu(d/n) }
那么F(n)怎么算呢?
既然x,y都是n的倍数,那么在区间[a,b]内, x可取的值的个数有(b-a+1)/n个, y可取的值的个数有(d-c+1)/n个 
所以F(n) = (b-a+1)/n * (d-c+1)/n;
本题中a,c为1,所以F(x) = (m/x)*(n/x),  (m=b/k,n=d/k)
所以f(1) = mu(1)*F(1) + mu(2)*F(2) + ... + mu(min(m,n))*F(min(m,n))

然后分析一下题目:
求1 <= x <= b, 1 <= y <= d中满足gcd(x,y)==k的数对(x,y)的数目,问题可以转化为
求1 <= x <= b/k, 1 <= y <= d/k中满足gcd(x/k, y/k)=1 的数对 (x,y)的数目,这不正好就是f(1)的值吗.

接下来只需要去重就可以了,因为题目说(x,y)和(y,x)不重复计算.
G(b,d)- G(b,b) / 2 

*/

#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1e5+5;
int mu[maxn],p[maxn];
bool vis[maxn];

/* 
莫比乌斯函数筛:
若i为奇数个不同素数之积mu[i] = -1
若i为偶数个不同素数之积mu[i] = 1
若i有质数平方因子则mu[i] = 0。
这个做起来比欧拉函数容易，在素数筛上，若i为素数则mu[i] = -1，若i % p[j] == 0，
 则mu[i * p[j]] = 0，显然p[j]就是它的质数平方因子，否则mu[i * p[j]] = -mu[i]
*/  
void init_mu(){
	int cnt=0;
	mu[1]=1;
	for(int i=2;i<maxn; ++i){
		if(!vis[i]){
			p[cnt++] = i;
			mu[i] = -1;
		}
		for(int j=0; j<cnt && i*p[j]<maxn; ++j){
			vis[i*p[j]] = 1;
			if(i%p[j] == 0){
				mu[i*p[j]] = 0;
				break;
			}
			mu[i*p[j]] = -mu[i];
		}
	}
}


int main(){
#ifdef WFX
freopen("9 in.txt","r",stdin);
#endif
	int T,a,b,c,d,k;
	init_mu();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		if(k==0){
			printf("0"); continue;
		}
		b/=k, d/=k;
		LL cnt1=0,cnt2=0;
		LL lim = b < d ? b : d;
		for(int i=1; i<=lim; ++i){
			cnt1 += mu[i]*(b/i)*(d/i);
			cnt2 += mu[i]*(lim/i)*(lim/i);
		}
		printf("%d\n",cnt1-cnt2/2);
	}
	
	return 0;
}
