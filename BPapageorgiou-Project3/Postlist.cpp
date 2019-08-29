#include "structures.h"

using namespace std;

Postlistnode::Postlistnode(int x,char* c):id(x){
	FILE *stream;
    char *linee = NULL;
    size_t len = 0;
	next=NULL;
	sum=1;
	path=new char[strlen(c)+1];
	strcpy(path,c);
	stream = fopen(path, "r");
	if (stream == NULL) {
	   	perror("fopen");
	   	exit(EXIT_FAILURE);
	}
	for(int j=0;j<id;j++){
		getline(&linee, &len, stream);
	}
	content=new char[strlen(linee)+1];
	strcpy(content,linee);
	fclose(stream);	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
Postlist::Postlist(){
	head=NULL;
	df=0;
	visited=0;
}

Postlist::~Postlist(){
	while(empty() == false){
		if(head->next==NULL){
			delete head;
			df--;
		}
		else{
			Postlistnode* current=head->next;;
			delete head;
			head=current;
			df--;
		}
	}

}


bool Postlist::empty(){

	return(df==0);
	  
}

int Postlist::length(int flag){
	if(flag==1){
		visited=1;
	}
	return df;
}

void Postlist::display(){
	Postlistnode* temp = head;
	while(temp!=NULL){
		cout<<temp->id<<" "<<temp->sum<<endl;
		temp=temp->next;
	}

}

void Postlist::insert(int id,char* c){
	if(head==NULL){
		head = new Postlistnode(id,c);
		df++;
	}
	else{
		Postlistnode* temp = head;
		if(strcmp(temp->path,c)==0){
			temp->sum++;
			return;
		}
		while(temp->next!=NULL){
			if(strcmp(temp->next->path,c)==0){
				temp->next->sum++;
				return;
			}
			temp=temp->next;
		}
		Postlistnode* add = new Postlistnode(id,c);
		temp->next = add;
		df++;

	}


}


Postlistnode* Postlist::postlisttermf(char* c){
	Postlistnode* temp = head;
	while((temp)!=NULL){
		if(strcmp(temp->path,c)==0){
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}



