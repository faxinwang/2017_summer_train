/*
题目内容：
 给定一个n, 求满足 2^x =1 (mod n)的最小x.
输入描述
输入整数n

输出描述
输出最小的x, 或者输出“不存在”

输入样例
5

输出样例
4

*/
/*
相关知识点: 
1. 若gcd(a,n)==1，一定存在一个正整数d<n使得a^phi(n) == 1 (mod n)(欧拉定理,
	phi()是欧拉函数,也经常写作 Euler() 或 phi_euler() )
2. 如果x是满足a^x==1 (mod n)的最小正数解，则 x一定是phi(n)的约数(注意并不是
   所有的约数都满足a^x==1 (mod n) ) 
证明: 
	如果x是满足ax≡1 (mod n)的最小的正x, 则x<= ? (n)
	则令? (n)=tx+d, 其中余数d小于x, 则 a?(n)=a tx+d,=atx.ad
	因此满足ad=1(mod n) , 由于x是最小的，因此只好d=0
	故x整除? (n)

3. 满足条件的最小正整数d记为ord_m(a)，叫做a模m的阶。
4. 若对于一个正整数a满足
	(1)gcd(a,m)==1;
	(2)ord_m(a)==φ(m)(φ(m)表示m的欧拉函数);
	则a叫做m的一个原根。
5. 若gcd(a,m)==1且a^d == 1 mod n，则φ(m)一定是d的倍数。因此，φ(m)一定是ord_m(a)的倍数。
6. 模m有原根的充要条件是m = 1,2,4,p^n, 2p^n，其中p是素数，n是任意正整数（只是有原根，
	并不是说gcd(a,m)==1则a一定是m的原根)。
7. 当模m有原根时，它有φ(φ(m))个原根。
8. 除了直接运算以外，至今还没有一个办法可以找到模特定m时的原根，但假如已知模m有一个原根，
	则可找出它其他的原根. 
	
欧拉函数的性质:
	1)n是质数，则phi(n) =n-1；
	2)m,n互质，则phi(mn) = phi(m) * phi(n) 
	3)n是奇数，phi(2n)= phi(n)
	4)p是素数，a是一个正整数，那么phi(p^a)=p^a - p^(a-1)
	5)n是一个正整数，那么 Sum{ (d|n)| phi(d) } = n 

解题思路：
1) 如果 n=1, 任何数模1结果都为0,所以当n=1是无解
2) 如果 n为偶数, 因为2^x一定也是偶数 ，所以2^x % n 不可能为1,也无解。
3) 如果 n 为奇数，则2与n互质，也即gcd(2,n)=1,由知识点(1)可知一定存在一个正整数x<n
   使得的2^x==1 (mod n),并且x一定是phi(n)的约数，进一步可得如果phi(n)是素数，则答案就是phi(n),
   否则就要去找满足条件的最小的x. 
*/

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

//直接求欧拉函数的值 
int euler(int n){
	int res=n;
	for(int i=2; i*i <=n; ++i){
		if( n % i == 0){
			res = res/i*(i-1);
			while(n % i == 0) n/=i;
		}
	}
	if(n>1) res = res / n * (n-1);
	return res;
}
//判断素数 
bool isPrime(int n){
	int i=2,Max=sqrt(n);
	for(; n%i!=0 && i<=Max; ++i);
	return i>Max;
}
//快速幂运算 返回 a^x % mod 
int qpow_mod(int a,int x,int mod){
	int rtn = 1,buff=a;
	while(x){
		if(x&1) rtn = rtn * buff % mod;
		buff = buff * buff % mod;
		x >>= 1;
	}
	return rtn;
}

int main(){
	int n,ans=0;
	scanf("%d",&n);
	if( n<=1 || n%2==0){
		printf("不存在");
	}else{
		int phi_n = euler(n) ;
		//如果phi_n是素数，则phi_n最小的约数就是他本身(这里不考虑1) 
		if(isPrime(phi_n)) ans = phi_n; 
		else{
			for(int x=2; x<=phi_n;++x) if(phi_n%x==0){
				//判断x是否满足等式2^x==1 (mod n) 
				if(qpow_mod(2,x,n) == 1){
					ans=x;break;
				}
			}
		}
		printf("%d",ans);
	}
	
	return 0;
}
