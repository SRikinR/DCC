//MODIFICATION: Demonstrate the retransmission of data at sender side using wrong Acknowledgement

#include<stdio.h>
#include<stdlib.h>
char seq='0',ack='0';
int flag=1;
int count=0;
FILE *fp1,*fp2;
void inc()
{
int n;
n=atoi(&seq); //ascii to integer conversion of the sequence number
if(n%2==0)
seq='1'; //for even frame, send seq=1
else
seq='0'; //for odd frame, send seq=0
}
void receiver(char *fr)
{
int j;
long int n;
if(fr[0]==seq) //for correct reception
{
printf("\nFrame Received\n");
printf("%c",fr[0]);
for(j=1;j<6;j++) //recreating the whole frame and storing into a file
{
if(fr[j]!=EOF)
{
fputc(fr[j],fp2);
printf("%c",fr[j]);
}
else
{
fputc(fr[j],fp2);
printf("%c",fr[j]);
break;
}
}
count++;
ack=seq;
printf("\nAck Sent=%c\n",ack);
}
}
void physical_layer(char *frm)
{
receiver(frm);
if(count==3) //create a intentional problem of sending wrong acknowledgement
ack='2';
}
void sender()
{
int i;
char data[6];
while(flag)
{
printf("\nFrame Generated\n");
data[0]=seq;
printf("%c",data[0]);
for (i=1;i<6;i++) //Generate Frame of length 5
{
data[i]=fgetc(fp1);
printf("%c",data[i]);
if (data[i]==EOF)
{flag=0;
break;}}
physical_layer(data);
printf("Ack received=%c\n",ack);
if(ack!=seq)
{
physical_layer(data);
printf("Ack received=%c\n",ack);
printf("**Received retransmitted Frame**\n");
inc();
}
else
inc();}}
int main(){
fp1=fopen("tx.txt","r");
fp2=fopen("rx.txt","w");
sender();
fclose(fp1);
fclose(fp2);
return 0;}