//Modify the above program to use framing concept.

#include<unistd.h>
#include<stdio.h>
#include<sys/io.h>
int main()
{
ioperm(0x3f8,7,1); //COM1 write accessible
outb(0x83,0x3fb); //Access DLAB from LCR
outb(0x0c,0x3f8); //Set baud rate of
outb(0x00,0x3f9); //9600bps from DLM and DLL
outb(0x03,0x3fb); //Access THR from LCR
FILE *f1; //File pointer
char data;
int frame=0,i=0;
f1=fopen("tx.txt","r"); //open file in read mode
do
{
while((inb(0x3fd) & 0x60)!=0x60); //Wait until THR is empty. Checks LSR
i++;
if(i<=8)
{
data=getc(f1); //get the character
outb(data,0x3f8); //transmit
printf("%c",data); //print on terminal
}
else
{
frame++;
i=0;
printf("\nFrame %d transmitted\n",frame);
}
}while(data!=EOF); //iterate until EOF is encountered in file
printf("\n**The file transmitted**\n");
return 0;
}
