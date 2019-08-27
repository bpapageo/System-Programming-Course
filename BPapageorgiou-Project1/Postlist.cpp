#include "structures.h"

using namespace std;

Postlistnode::Postlistnode(int x):id(x){
	next=NULL;
	sum=1;
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

void Postlist::insert(int id){
	if(head==NULL){
		head = new Postlistnode(id);
		df++;
	}
	else{
		Postlistnode* temp = head;
		if((temp->id)==id){
			temp->sum++;
			return;
		}
		while(temp->next!=NULL){
			if((temp->next->id)==id){
				temp->next->sum++;
				return;
			}
			temp=temp->next;
		}
		Postlistnode* add = new Postlistnode(id);
		temp->next = add;
		df++;

	}


}

int Postlist::postlisttermf(int id){
	Postlistnode* temp = head;
	while((temp)!=NULL){
		if(temp->id==id){
			return temp->sum;
		}
		temp=temp->next;
	}
	return -1;
}



