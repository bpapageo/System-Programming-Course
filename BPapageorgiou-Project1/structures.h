#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>

using namespace std;

struct Document{
	int id;
	char* text;
	int sum;
	~Document(){
	delete[] text;
	};
};

struct Score{
	double s;
	int id;
};

struct Postlistnode{
	int id;
	int sum;
	Postlistnode* next;
	Postlistnode(int);
};

class Postlist{
private:
	Postlistnode* head;
	int df;
public:
	Postlist();
	~Postlist();
    	void insert(int);
    	bool empty();
    	void display();
    	int length(int);
	int postlisttermf(int);
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
	Trienode* insertatlevel(char,int);
	Trienode* termfatlevel(char,int);
	void Postlistinsert(int);

};


class Trie{
private:
	Trienode* root;
public:
	Trie();
	~Trie();
	void insert(char*,int);
	bool search(char*);
	void print();
	int termf(char*,int);
	int docf(char*,int);

};

void Qsort( struct Score[], int, int);
int partition( struct Score[], int l, int r);

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

