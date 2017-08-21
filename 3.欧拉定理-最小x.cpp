/*
��Ŀ���ݣ� http://acm.hdu.edu.cn/showproblem.php?pid=1395
 ����һ��n, ������ 2^x =1 (mod n)����Сx.
��������
��������n

�������
�����С��x, ��������������ڡ�

��������
5

�������
4

*/
/*
���֪ʶ��: 
1. ��gcd(a,n)==1��һ������һ��������d<nʹ��a^phi(n) == 1 (mod n)(ŷ������,
	phi()��ŷ������,Ҳ����д�� Euler() �� phi_euler() )
2. ���x������a^x==1 (mod n)����С�����⣬�� xһ����phi(n)��Լ��(ע�Ⲣ����
   ���е�Լ��������a^x==1 (mod n) ) 
֤��: 
	���x������ax��1 (mod n)����С����x, ��x<= phi(n)
	����phi(n)=tx+d, ��������dС��x, �� a^phi(n)=a^(tx+d)=a^tx * a^d
	�������a^d=1(mod n) , ����x����С�ģ����ֻ��d=0
	��x����phi(n)

3. ������������С������d��Ϊord_m(a)������aģm�Ľס�
4. ������һ��������a����
	(1)gcd(a,m)==1;
	(2)ord_m(a)==��(m)(��(m)��ʾm��ŷ������);
	��a����m��һ��ԭ����
5. ��gcd(a,m)==1��a^d == 1 mod n�����(m)һ����d�ı�������ˣ���(m)һ����ord_m(a)�ı�����
6. ģm��ԭ���ĳ�Ҫ������m = 1,2,4,p^n, 2p^n������p��������n��������������ֻ����ԭ����
	������˵gcd(a,m)==1��aһ����m��ԭ��)��
7. ��ģm��ԭ��ʱ�����Ц�(��(m))��ԭ����
8. ����ֱ���������⣬����û��һ���취�����ҵ�ģ�ض�mʱ��ԭ������������֪ģm��һ��ԭ����
	����ҳ���������ԭ��. 
	
ŷ������������:
	1)n����������phi(n) =n-1��
	2)m,n���ʣ���phi(mn) = phi(m) * phi(n) 
	3)n��������phi(2n)= phi(n)
	4)p��������a��һ������������ôphi(p^a)=p^a - p^(a-1)
	5)n��һ������������ô Sum{ (d|n)| phi(d) } = n 

����˼·��
1) ��� n=1, �κ���ģ1�����Ϊ0,���Ե�n=1���޽�
2) ��� nΪż��, ��Ϊ2^xһ��Ҳ��ż�� ������2^x % n ������Ϊ1,Ҳ�޽⡣
3) ��� n Ϊ��������2��n���ʣ�Ҳ��gcd(2,n)=1,��֪ʶ��(1)��֪һ������һ��������x<n
   ʹ�õ�2^x==1 (mod n),����xһ����phi(n)��Լ������һ���ɵ����phi(n)����������𰸾���phi(n),
   �����Ҫȥ��������������С��x. 
*/

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

//ֱ����ŷ��������ֵ 
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
//�ж����� 
bool isPrime(int n){
	int i=2,Max=sqrt(n);
	for(; n%i!=0 && i<=Max; ++i);
	return i>Max;
}
//���������� ���� a^x % mod 
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
	while(~scanf("%d",&n)){
		if( n<=1 || n%2==0){
			printf("2^? mod %d = 1\n",n);
		}else{
			int phi_n = euler(n) ;
			//���phi_n����������phi_n��С��Լ������������(���ﲻ����1) 
			if(isPrime(phi_n)) ans = phi_n; 
			else{
				for(int x=2; x<=phi_n;++x) if(phi_n%x==0){
					//�ж�x�Ƿ������ʽ2^x==1 (mod n) 
					if(qpow_mod(2,x,n) == 1){
						ans=x;break;
					}
				}
			}
			printf("2^%d mod %d = 1\n",ans,n);
		}
	}

	return 0;
}
