#include<stdio.h>
#include<unistd.h>
#include<sys/io.h>
int main()
{
ioperm(0x3f8,7,1); //write access permission on COM1(8 addresses)
outb(0x83,0x3fb); //write 0x83 in LCR to make DLAB register accessible
outb(0x00,0x3f9); //Put 0x00 in DLM and 0x0c in DLL for setting
outb(0x0c,0x3f8); //baud rate of 9600bps
outb(0x03,0x3fb); //Put 0x03 in LCR to access THR
char data='P'; //Emulate that the data was received by putting
//same data on THR and RBR register
outb(data,0x3f8); //put the data to be transmitted into THR
printf("Data transmitted = %c\n",data);
while((inb(0x3fd)&0x01)!=0x01); //wait until RBR has some data
char received_data=inb(0x3f8); //read the data from RBR register
printf("Data received = %c\n",received_data);
}
