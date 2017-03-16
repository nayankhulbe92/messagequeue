#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;
    int p,s=0,sum,len,q=0,diff,mul,div;
    FILE *fp;


    if ((key = ftok("kirk.c", 'B')) == -1) {  /* same key as kirk.c */
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, 0644)) == -1) { /* connect to the queue */
        perror("msgget");
        exit(1);
    }
    
    printf("spock: ready to receive messages, captain.\n");

 /* Spock never quits! */
    
        if (msgrcv(msqid, &buf, sizeof buf.mtext, 0, 0) == -1) 
        {
            perror("msgrcv");
            exit(1);
        }
// my code ;

len = strlen(buf.mtext);// length of received array.

// converting all charecters in mtext to integers;

for(int i=0; i<len; i++) // loop will run until '+' or '-' or '*' or '/' in input string.
{

    if(buf.mtext[i]==43)   
    {
    p=i;
    break; // break when '+';
    }
    if(buf.mtext[i]==45)
    {
     p=i;
     break; //break when '-';
    }
    if(buf.mtext[i]==42)
    {
      p=i;
      break;// break when '*';
    }

    if(buf.mtext[i]==47)
    {
      p=i; 
      break;// break when '/';
    }

  q = q * 10 + ( buf.mtext[i] - '0' );
}


for(int j=p+1;j<len;j++) // contiue after '+' or '-' or '*' or '/' symbol in input string.
{

  s = s * 10 + ( buf.mtext[j] - '0' );

}


if(buf.mtext[p]==43) // for '+' operation
{
  sum=s+q;
  fp=fopen("out.txt","w+");     // opening output file in write mode.
  fprintf(fp,"Client :");   
  fprintf(fp,"%ld\n",buf.mtype);// printing client number in output file.
  fprintf(fp," %s ",buf.mtext);// print input string
  fprintf(fp,"%d",sum);        // print output
}

if(buf.mtext[p]==45) // for '-' operation
{
  diff=q-s;
  fp=fopen("out.txt","w+"); 
  fprintf(fp,"Client :");
  fprintf(fp,"%ld\n",buf.mtype);
  fprintf(fp," %s ",buf.mtext);
  fprintf(fp,"%d",diff);
 

}

if(buf.mtext[p]==42)// for '*' operation
{
  mul=s*q;
  fp=fopen("out.txt","w+");
  fprintf(fp,"Client :");
  fprintf(fp,"%ld\n",buf.mtype);
  fprintf(fp," %s ",buf.mtext);
  fprintf(fp,"%d",mul);
  }

if(buf.mtext[p]==47) //for '/' operation
{
  div=s/q;
  fp=fopen("out.txt","w+");
  fprintf(fp,"Client :");
  fprintf(fp,"%ld\n",buf.mtype);
  fprintf(fp," %s ",buf.mtext);
  fprintf(fp,"%d",div);
  
}
        

    return 0;
}
