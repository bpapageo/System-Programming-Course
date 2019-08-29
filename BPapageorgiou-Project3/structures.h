#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>	     /* sockets */
#include <sys/types.h>	     /* sockets */
#include <sys/socket.h>	     /* sockets */
#include <netinet/in.h>	     /* internet sockets */
#include <netdb.h>	         /* gethostbyaddr */
#include <unistd.h>	         /* fork */		
#include <signal.h>          /* signal */
#include <ctime>
#include <ctype.h>
#include <pthread.h>   /* For threads  */

extern int errno;

using namespace std;


struct Postlistnode{
	char* path;
	char* content;
	int id;
	int sum;
	Postlistnode* next;
	Postlistnode(int,char*);
	~Postlistnode(){
		delete[] path;
		delete[] content;
	};

};

class Postlist{
private:
	Postlistnode* head;
	int df;
public:
	Postlist();
	~Postlist();
    void insert(int,char*);
    bool empty();
    void display();
    int length(int);
	Postlistnode* postlisttermf(char*);
	int visited;

};

struct Trienode{
	char x;
	Trienode* child;
	Trienode* next;
	Postlist* ppt;
	void print();
	Trienode(char);
	~Trienode();
	Trienode* insertatlevel(char,int,char*);
	Trienode* termfatlevel(char,int);
	void Postlistinsert(int,char*);

};


class Trie{
private:
	Trienode* root;
public:
	Trie();
	~Trie();
	void insert(char*,int,char*);
	void print();
	Postlistnode* termf(char*,char*);
	int docf(char*,int);

};

struct Worker{
	pid_t pid;
	char* dirs;
	Trie *trie;
	char** filenames;
	int numoffiles;
	int numdirs;
	int fd_write ,fd_read;//the descriptors that worker  writes and reads from jobexecutor
	Worker(int,int,int,char*);
	~Worker(){
		delete[] dirs;
		delete trie;
	};
	
};

struct print_struct {

	char* word;
	char c;

	print_struct(char* w, char cc) { word = new char[strlen(w) + 1]; strcpy(word,w); c = cc; }
	~print_struct() { delete[] word; }
};

class print_class {

	print_struct** array;
	int size;
	int index;

	public:

	print_class();
	~print_class();
	void insert(char*, char);
	void highlight(char*, char**, int);


};