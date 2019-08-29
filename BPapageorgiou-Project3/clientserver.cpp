#include "structures.h"

#define MAXBUFF 1024

Worker::Worker(int n,int writefd,int readfd,char* drs){
        pid=getpid();
        numdirs=n;
        fd_write=writefd;
        fd_read=readfd;
        trie=new Trie();
        dirs= new char[strlen(drs)+1];
        strcpy(dirs,drs);
}

void client(int readfd, int writefd , char* copy){
   char buff[MAXBUFF];
   int n=MAXBUFF;

//cout<<"Jobexecutor is doing his job"<<endl;
   /* Read the filename from standard input, 
    *  write it to the IPC descriptor.
    */
   //cout<<copy<<endl;
   /*buff=new char[strlen(copy)+1];*/
   strcpy(buff,copy);
   if (write(writefd, buff, n) != n)
      perror("client: write error");
   //cout<<"Jobexecutor writes the word to fifoin"<<buff<<endl;
   /* Read data from the IPC descriptor and write to
    * standard output. 
    */
   //cout<<"eeee"<<buff<<endl;


   while( (n = read(readfd, buff,MAXBUFF)) < 0);
     //cout<<"Jobexecutor reads the word from fifoout and writes it to stdout"<<endl;

      if (write(1, "Communication created\n", strlen("Communication created\n")+1) != strlen("Communication created\n")+1 )   /* fd 1 = stdout */ {
         perror("client: data write error \n");
      }
      cout<<endl;
    


   //delete[] buff;


}

void server(int readfd, int writefd,struct Worker** w,int i,int nd ) {

  //cout<<"Worker is doing his job"<<endl;

   char buff[MAXBUFF];
   int n=MAXBUFF;


   /* Read from the IPC descriptor. */
   cout<<readfd<<endl;
   while((n= read(readfd, buff, MAXBUFF)) < 0){
   if (n <0) { 
      //perror("errorrrr \n");
   }
 }

 //cout<<buff<<endl;
    w[i]=new struct Worker(nd,writefd,readfd,buff);
      /* Write to the IPC descriptor. */

  if (write(writefd, buff, n) != n) {
        perror("server: write error");
   }
   //cout<<"Worker writes to fifoout"<<endl;
   
}

