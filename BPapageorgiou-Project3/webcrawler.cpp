#include "structures.h"


using namespace std;

void perror_exit(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void *thread_f(void *argp){ /* Thread function */
	printf("I am the newly created thread %ld\n",
	pthread_self());
	pthread_exit((void *) 47);
}

int main(int argc,char *argv[]){

	clock_t begin = clock();

	char line[100],str[40];
	int numthreads,servport,commport;
	int flag=0;
	int i,status;
	char* url,*hostname,*savedir;

	if(argc<12){
		cout<<"Incorrect num of arguments.Try again!"<<endl;
		return -1;
	}
	for(i=1;i<argc;i+=2){
		if(strcmp(argv[i],"-d")==0){
			flag=1;
			savedir=new char[strlen(argv[i+1]+1)];
			strcpy(savedir,argv[i+1]);
			url=new char[strlen(argv[i+2]+1)];
			strcpy(url,argv[i+2]);
		}
		else if(strcmp(argv[i],"-t")==0){
			numthreads = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i],"-p")==0){
			servport = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i],"-c")==0){
			commport = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i],"-h")==0){
			hostname=new char[strlen(argv[i+1]+1)];
			strcpy(hostname,argv[i+1]);
		}
	}
	if(flag==1){
		int sock,sock2,newsock2;
		char buf[256];
		unsigned int serverlen;
		struct sockaddr_in server;
		struct sockaddr *serverptr;
		struct hostent *rem;
		if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { /* Create socket */
		    perror("socket"); exit(1); }
		if ((rem = gethostbyname(hostname)) == NULL) { /* Find server address */
		    perror("gethostbyname"); exit(1); }
		server.sin_family = PF_INET;                      /* Internet domain */
		bcopy((char *) rem -> h_addr, (char *) &server.sin_addr,rem -> h_length);
		server.sin_port = htons(servport); /* Server's Internet address and port */
		serverptr = (struct sockaddr *) &server;
		serverlen = sizeof server;
		if (connect(sock, serverptr, serverlen) < 0) { /* Request connection */
		    perror("connect"); exit(1); }
		printf("Requested connection to host %s port %d\n", hostname, servport);

	    int i,err;
	    pthread_t *tids;
	    if ((tids = (pthread_t*)malloc(numthreads * sizeof(pthread_t))) == NULL) {
		      perror("malloc");  exit(1); }
	    for (i=0 ; i<numthreads ; i++) {
	         if (err = pthread_create(tids+i, NULL, thread_f, NULL)) {
	              /* Create a thread */
	             perror("pthread_create");   exit(1);} 
	        }
	    for (i=0 ; i<numthreads ; i++){
		   if (err = pthread_join(*(tids+i), NULL)) {
		      /* Wait for thread termination */
		      perror("pthread_join"); 
		      exit(1); 
		      }
	    }         
		close(sock);

	    struct sockaddr_in server2,client2;
	    socklen_t clientlen2;
	    struct sockaddr *serverptr2=(struct sockaddr *)&server2;
	    struct sockaddr *clientptr2=(struct sockaddr *)&client2;
	    if ((sock2 = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	        perror_exit("socket");
	    server2.sin_family = AF_INET;       /* Internet domain */
	    server2.sin_addr.s_addr = htonl(INADDR_ANY);
	    server2.sin_port = htons(commport);      /* The given port */
	    /* Bind socket to address */
	    if (bind(sock2, serverptr2, sizeof(server2)) < 0)
	        perror_exit("bind");
	    /* Listen for connections */
	    if (listen(sock2, 5) < 0) perror_exit("listen");
    	printf("Listening for connections to port %d\n", commport);

		while (1) { 
		   	clientlen2 = sizeof(client2);

	    	if ((newsock2 = accept(sock2, clientptr2, &clientlen2)) < 0) perror_exit("accept");
	    	/* Find client's address */
	    	printf("Accepted connection 2\n");
            do {
		    	bzero(line, sizeof line);             /* Initialize buffer */
	            if (read(newsock2, line, sizeof line) < 0) { /* Get message */
	                  perror("read"); exit(1); }
	            printf("Read string: %s\n", line);
	            char* pch;
				pch = strtok(line,"\r");
				if(strcmp(pch,"STATS")==0){

					int minutes=0,hours=0;
					clock_t end = clock();
  					double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  					cout<<elapsed_secs<<" "<<CLOCKS_PER_SEC<<endl;
  					if(elapsed_secs>60){
	  					minutes = elapsed_secs / 60;
	  					elapsed_secs -= minutes * 60;
  					}
  					if(minutes>60){
  						hours = minutes / 60;
 	  					minutes -= hours * 60;

  					}
					sprintf(str,"Served up for %d:%d:%f",hours,minutes,elapsed_secs);
					//cout<<str<<endl;
					if (write(newsock2, str, sizeof str) < 0){/* Send message */
	                  perror("write"); exit(1); }

				}
				else if(strcmp(pch,"SEARCH")==0){		

				}
				else if(strcmp(pch,"SHUTDOWN")==0){		

					break;
				}
				else{
					cout<<"Wrong input,try again!"<<endl;
					continue;
				}

            } while (strcmp(line, "SHUTDOWN") != 0);       /* Finish on "end" */
            close(newsock2);
            break;   
	    }



	}
	else{
		cout<<"No input file"<<endl;
		return -1;
	}


   	return 0;

}
