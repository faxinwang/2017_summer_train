/*
����˼·:
���������ĿΪż����, ��ѵ�һ,��������һ��, ��,�ĸ�����һ��, ��,��������һ��.... 
û�������м�Ŀո�������n��ȡʯ����Ϸ��ĳһ��ʯ����,Ȼ��ͱ������n��ʯ��,ÿ�ο��Դ�����
һ��������ȡʯ�ӵ���Ϸ.
���������������, ��ѵ�һ������ǰ��Ŀո�������һ��ʯ��,�����ż����ͬ�ϴ���. �Լ���ֽ�ϻ�
һ������, �ü���СֽƬģ������, ����С����߼�����һ��,��Ȼ�����������еĵ���. 

*/
#include<iostream>
#include<cstdio>
using namespace std;

int main(){
#ifdef WFX
freopen("10 in.txt","r",stdin);
#endif 
	int n,T;
	scanf("%d",&T);
	while(T--){
		int sum=0,x,y;
		scanf("%d",&n);
		if(n^1){
			scanf("%d",&sum);
			--sum;
			for(int i=1;i<n; i+=2){
				scanf("%d%d",&x,&y);
				sum ^= y-x-1;
			}
		}else{
			for(int i=0; i<n;i+=2){
				scanf("%d%d",&x,&y);
				sum ^= y-x-1;
			}
		}
		
		if(sum) printf("��\n");
		else printf("��\n"); 
	}
	
	return 0;
}

