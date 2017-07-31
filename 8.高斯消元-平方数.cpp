/*
题目内容：
 有n个整数a1,a2,...an，每个数ai的质因子不超过2000. 现从中选取一些数，它们的乘积刚好是平方数。
问有多少种挑选方案。 假定n<=300, ai<=2000

输入描述
第一行是n
第二行是n个整数

输出描述
方案数。为防止数目过大，结果需模1000000007.

输入样例
3
3 3 4

输出样例
3
*/

/*
解题思路:
	对于任意自然数n,都可以将它分解为n=P1^R1 * P2^R2 * P3^R3....,(其中Pi为其质因数,Ri为Pi的指数), 
	该式子就叫n的 "唯一分解式". 
	对于平方数N,它的唯一分解式 N = P1^R1 * P2^R1 * P3^R3 *.....中的Ri必须全都为偶数,这样开方出
	来的才是整数,基于这一性质, 我们对给定的每个整数a1,a2,...,an进行质因数分解,并记录所有整数ai
	的所有质因数Pi的个数Ri,并保存在一个二维矩阵中,如下:
P1	R11*x1	R12*x2	R13*x3 ...	R1n*xn
P2	R21*x1	R22*x2	R23*x3 ...	R2n*xn
...	...
Pj	Ri1*x1	...		Rij*xi ...	Rin*xn
...	... 
Pm	Rm1*x1	Rm1*x2	Rm3*x3 ...	Rmn*xn
	其中: 
	1) P1,P2,...,Pm为a1,a2,...,an分解出来的所有的质数.
	2) R12为a2分解出来的质数P1的个数,Rij为aj分解出来的质数pi的个数 
	3) xi取值0或1,取1表示选择ai,取0表示不选择ai
要使得最后选出的数的乘积N是一个完全平方数,则式N = P1^R1 * P2^R2 * P3^R3*...*PmRm中的每个质因数Pi
对应的指数Ri必须为偶数,所以可以得到如下方程:
	R11*x1 + R12*x2 + R13*x3 + ... + R1n*xn = R1
	R21*x1 + R22*x2	+ R23*x3 + ... + R2n*xn = R2
	...
	Rm1*x1 + Rm2*x2 + Rm3*x3 + ... + Rmn*xn = Rn
	其中:
	1) 因为xi的取值为0或1,所以Ri的值即为选出的所有整数{xi}分解出的质数Pi的总个数.
	2) 上面已经说了, 要使得最后乘积N为完全平方数,必须满足Ri均为偶数
由于我们只需要记录Rij和Ri是奇数还是偶数,所以我们可以将上述方程进一步简化, 
	R11*x1 + R12*x2 + R13*x3 + ... + R1n*xn = 0 (mod 2) 
	R21*x1 + R22*x2	+ R23*x3 + ... + R2n*xn = 0 (mod 2) 
	...
	Rm1*x1 + Rm2*x2 + Rm3*x3 + ... + Rmn*xn = 0 (mod 2)
这样,xi的系数Rij就都是0或1的值, 并且方程的右边全都变成了0(之前Ri必须都为偶数才能使选出的数的成绩为
完全平方数)这进一步简化了后面高斯消元的过程. 
对于这个方程,我们把系数用二维数组保存起来,然后用高斯消元法求出该矩阵的秩r,进而可得该方程组的自由变
元的个数n-r. 由于xi的取值只有0或1两种选择, 所以总的满足条件的选择方案数就是2^(n-r) - 1,(减一是因为
要减去一个都不选的情况,因为题目要求至少选择一个正整数)
*/

#include <iostream>
#include<cstdio>
using namespace std;
const int Max = 2005;
const int Mod = 1000000007;
bool vis[Max];
char mtx[500][305];
int  p[500]; //初步估计小于2000的质数不超过1000个

int init(){
	int cnt=0;
	for(int i=2; i<Max; ++i){
		if(!vis[i]){
			p[cnt++] = i;
			for(int j=i*i; j<=Max; j+=i) vis[j] = 1;
		}
	}
	return cnt;
}

//计算a^n % Mod 
int quick_mod(int a,int n){
	int ans = 1, x = a % Mod;
	while(n){
		if(n&1) ans = ans * x % Mod;
		x = x * x % Mod;
		n >>= 1;
	}
	return ans;
}

//高斯消元 
int rank(char a[][305], int m , int n )  
{  
    int i = 0 , j = 0 , k , r , u;  
    while( i < m && j < n )  
    {  
        r = i;  
        for( k = i; k < m; k++ )  
            if ( a[k][j] ) {r = k;break;}  
        if ( a[r][j] )  
        {  
            if ( r != i )  
                for( k = 0; k <= n; k++ ) swap( a[r][k] , a[i][k] );  
            for( u = i + 1; u < m; u++ )  
                if ( a[u][j] )  
                for( k = i; k <= n; k++ )   a[u][k] ^= a[i][k];  
            i++;  
        }  
        j++;  
    } 
    return i;  
}  

int main(){
#ifdef WFX
freopen("8 in.txt","r",stdin);
#endif
	int n,a,maxp=0;
	int prime_n = init(); //找出所有不大于2000的质数并返回个数 
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&a);
		//对a进行质因数分解,结果保存在mtx矩阵中 
		for(int j=0;j<prime_n && a;++j){
			while(a % p[j] == 0){
				a /= p[j];
				mtx[j][i] ^= 1; //与1异或,效果等于(mtx[j][i]+1)%2
				//记录分解出的最大的质因数在p数组中的下标 
				if(maxp < j) maxp = j;
			}
		}
	}
	int r = rank(mtx,maxp+1,n); //返回矩阵的秩 
	printf("%d",quick_mod(2,n - r) -1);
	return 0; 
} 
