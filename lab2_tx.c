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
char c;
f1=fopen("tx.txt","r"); //open file in read mode
do
{
while((inb(0x3fd) & 0x60)!=0x60); //Wait until THR is empty. Checks LSR
c=getc(f1); //get the character
outb(c,0x3f8); //transmit
printf("%c",c); //print on terminal
}while(c!=EOF); //wait until EOF is encountered in file
fclose(f1); //close the file
printf("\nThe file transmitted\n");
return 0;
}