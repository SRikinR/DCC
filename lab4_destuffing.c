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
int i,j,y,flag=0;
int packet_counter=0,frame_counter=0,stuff_counter=0;
char DLE='$',STX='@',ETX='*';
FILE *f3,*f4;
void from_physical_layer() //create the frames
{
i=0;
do{
frame[i]=getc(f3);//read the received file
i++;
}
while(frame[i
-1]!=ETX);
}
void data_link_layer() //frame with packet {
i=2,y=0;
while((frame[i]!=ETX)&&(y<8))
{
if(frame[i]==EOF) {
packet[y]=frame[i];
y++;
}
else if((frame[i]!=DLE)&&(frame[i]!=EOF)) {
packet[y]=frame[i];
y++;
}
else if((frame[i]==DLE)&&(frame[i+1]==DLE)) {
packet[y]=frame[i];
y++;
i++;
}
else if((frame[i]==DLE)&&(frame[i+1]==ETX))
break;
i++;
}}
void to_network_layer() {
for(i=0;i<8;i++) {
if(packet[i]==EOF) {
flag=1;
break;
}
else {
putc(packet[i],f4);
printf("%c",packet[i]);
}
}
}
int main()
{
f3=fopen("tx.txt","r");
f4=fopen("rx.txt","w");
init();
do{
from_physical_layer();
data_link_layer();
to_network_layer();
}while(flag!=1);
fclose(f3);
fclose(f4);
printf("\nThe file received\n");
}
