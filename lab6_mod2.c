//(2) Modify the above programs to find class as well as subnet mask of entered IPaddress.


#include<stdio.h>
#include<string.h>
char findClass(int ip)
{
//check the first octet
// Class A
if (ip >=1 && ip <= 126)
return 'A';
// Class B
else if (ip >= 128 && ip <= 191)
return 'B';
// Class C
else if (ip >= 192 && ip <= 223)
return 'C';
// Class D
else if (ip >= 224 && ip <= 239)
return 'D';
// Class E
else
return 'E';
}
void subnet(char ipClass) //function to print subnet mask as per ipclass
{
if (ipClass == 'A')
{
printf("Subnet mask = 255.0.0.0\n");
}
else if (ipClass == 'B')
{
printf("Subnet mask = 255.255.0.0\n");
}
else if (ipClass == 'C')
{
printf("Subnet mask = 255.255.255.0\n");
}
else
printf("In this Class, IP address is not divided into Network and Host ID\n");
}
int main()
{
int i=0;
int dec[4];
char ipclass;
printf("Enter IP address in dotted decimal notation (separate each byte by .):\n ");
scanf("%d.%d.%d.%d",&dec[0],&dec[1],&dec[2],&dec[3]);
ipclass=findClass(dec[0]);
printf("IP belongs to class %c\n",ipclass);
subnet(ipclass);
}
