//Write a program to transmit a string using Serial Port.

#include<stdio.h>
#include<unistd.h>
#include<sys/io.h>
#include<string.h>
int main()
{
ioperm(0x3f8,7,1); //write access permission on COM1(8 addresses)
outb(0x83,0x3fb); //write 0x83 in LCR to make DLAB register accessible
outb(0x00,0x3f9); //Put 0x00 in DLM and 0x0c in DLL for setting
outb(0x0c,0x3f8); //baud rate of 9600bps
outb(0x03,0x3fb); //Put 0x03 in LCR to access THR
char data[10]="RIKIN"; //string to be transferred
int i,l;
l=strlen(data);
printf("Length of the data to be transferred = %d\n",l);
for(i=0;i<l;i++)
{
while((inb(0x3f8) & 0x60)!=0x60); //wait until THR is empty
outb(data[i],0x3f8); //put the data to be transmitted into THR
printf("Data Transmitted = %c\n",data[i]);
}
}
