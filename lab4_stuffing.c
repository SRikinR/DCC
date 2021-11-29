#include<stdio.h>
#include<sys/io.h>
#include<unistd.h>
void init()
{
ioperm(0x3f8,7,1);
outb(0x83,0x3fb);
outb(0x0c,0x3f8);
outb(0x00,0x3f9);
outb(0x03,0x3fb);
}
char packet[8],frame[20];
int k,j,flag;
int packet_counter=0,frame_counter=0,stuff_counter=0;
char DLE='$',STX='@',ETX='*';
FILE *f1,*f2;
void from_network_layer() //create the frames
{
for(k=0;k<8;k++)
{
packet[k]=getc(f1);
if(packet[k]==EOF)
{
flag=1;
break;
}
}
printf("\npacket no. of %d is generated",++packet_counter);
}
void data_link_layer() //frame with packet
{
stuff_counter=0;
frame[0]=DLE;
frame[1]=STX;
for(k=0;k<8;k++)
{
frame[k+2+stuff_counter]=packet[k];

if(packet[k]==DLE)
{
stuff_counter++;
frame[k+2+stuff_counter]=DLE;
}
}
frame[k+2+stuff_counter]=DLE;
k++;
frame[k+2+stuff_counter]=ETX;
printf("\nFrame no.%d is generated ",++frame_counter);
}
void to_physical_layer()
{
for(j=0;j<=k+2+stuff_counter;j++)
{
putc(frame[j],f2);
printf("%c",frame[j]);
}
}
int main()
{
f1=fopen("text.txt","r");
f2=fopen("Tx.txt","w");
init();
do{
from_network_layer();
data_link_layer();
to_physical_layer();
}while(flag!=1);
fclose(f1);
fclose(f2);
printf("\n The file transmitted\n");
}
