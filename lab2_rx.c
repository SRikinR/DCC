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
FILE *f1,*f2;
char c;
f1=fopen("tx.txt","w"); //received file
f2=fopen("tx.txt","r"); //transmitted file
do
{
c=getc(f2);
putc(c,f1);
printf("%c",c);
}while(c!=EOF);
fclose(f1);
fclose(f2);
printf("\n File Received \n");
return 0;
}