//SAMPLE PROGRAM (DOTTED DECIMAL TO BINARY FORM):

#include<stdio.h>
int main()
{
int i=0;
long bin[4];
int dec[4];
long convert(int);
printf("Enter IP address in dotted decimal notation:\n ");
scanf("%d.%d.%d.%d",&dec[0],&dec[1],&dec[2],&dec[3]);
for(i=0;i<4;i++)
bin[i]=convert(dec[i]);
printf("IP address in pure binary notation :\n");
printf("%08ld %08ld %08ld %08ld\n",bin[0],bin[1],bin[2],bin[3]);
}
long convert(int data)
{
long power2(long , long);
long sum = 0,i;
for(i=0;data>0;i++)
{
sum+=(data%2)*(power2(10,i));
data = data/2;
}
return sum;
}
long power2(long m , long n)
{
long ans = 1,i;
for(i=1;i<=n;i++)
ans *= m;
return ans;
}