#include "structures.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////

Trienode::Trienode(char letter):x(letter){
	child=NULL;
	next=NULL;
	ppt=NULL;
}

Trienode::~Trienode(){
	if(ppt!=NULL){
		delete ppt;
	}
	if(next!=NULL){
		delete next;
	}
	if(child!=NULL){
		delete child;
	}


}

void Trienode::print(){
	cout<<x;
}

void Trienode::Postlistinsert(int id,char* c){
		if(ppt==NULL){
			ppt=new Postlist();
			ppt->insert(id,c);
		}
		else{
			ppt->insert(id,c);
		}

}

Trienode* Trienode::insertatlevel(char letter,int id,char* c){

	if(x==-1){
		//cout<<"Case1"<<endl;
		x=letter;
		child = new Trienode(-1);
		if(id!=-1){
			Postlistinsert(id,c);
		}
		return child;
	}

	if(letter==x){
		//cout<<"Case2"<<endl;
		if(id!=-1){
			Postlistinsert(id,c);
		}
		return child;
	}
	else{
		if(next==NULL){
			//cout<<"case3"<<endl;
			next=new Trienode(letter);
			next->child = new Trienode(-1);
			if(id!=-1){
				next->Postlistinsert(id,c);
			}
			return next->child;
		}
		else{
			Trienode* current = next;
			if((current->x)==letter){
				//cout<<"case4"<<endl;
				if(current->child==NULL){
					current->child = new Trienode(-1);
				}
				if(id!=-1){
					current->Postlistinsert(id,c);
				}
				return current->child;
			}
			while(current->next!=NULL){
				if((current->next->x)==letter){
					//cout<<"casee4"<<endl;
					if(current->next->child==NULL){
						current->next->child = new Trienode(-1);
					}
					if(id!=-1){
						current->next->Postlistinsert(id,c);
					}
					return current->next->child;
				}
				current=current->next;
			}
			//cout<<"case5"<<endl;
			current->next=new Trienode(letter);
			current->next->child = new Trienode(-1);
			if(id!=-1){
				current->next->Postlistinsert(id,c);
			}
			return current->next->child;
		}
	}
}

Trienode* Trienode::termfatlevel(char letter,int flag){
	if(letter==x){
		//cout<<"Case1"<<endl;
		if(flag==1){
			return this;
		}
		else{
			return child;
		}
	}
	else{
		Trienode* current = next;
		if((current->x)==letter){
			//cout<<"case2"<<endl;
			if(flag==1){
				return current;
			}
			else{
				return current->child;
			}
		}
		while(current->next!=NULL){
			if((current->next->x)==letter){
				//cout<<"case3"<<endl;
				if(flag==1){
					return current->next;
				}
				else{
					return current->next->child;
				}
			}
			current=current->next;
		}
		if((current->x)==letter){
			//cout<<"case4"<<endl;
			if(flag==1){
				return current;
			}
			else{
				return current->child;
			}
		}


	}

}
//////////////////////////////////////////////////////////////////////////////////////
Trie::Trie(){
	root=new Trienode(-1);
}

Trie::~Trie(){
	delete root;
}

void Trie::insert(char* w,int id,char* c){
	Trienode* current = root;
	unsigned int i=0;
	while(i<strlen(w)){
		if(i==strlen(w)-1){
			current=current->insertatlevel(w[i],id,c);
			break;	
		}
		current=current->insertatlevel(w[i],-1,c);	
		i++;	
	}

}

Postlistnode* Trie::termf(char* w,char* c){
	Trienode* current = root;
	unsigned int i=0;
	while(i<strlen(w)){
		if(i==strlen(w)-1){
			current=current->termfatlevel(w[i],1);
			break;	
		}
		current=current->termfatlevel(w[i],0);
		i++;
	}
	if(current->ppt==NULL){
		//cout<<"null pointer"<<endl;
		return NULL;
	}

	return current->ppt->postlisttermf(c);


}

int Trie::docf(char* w,int flag){
	Trienode* current = root;
	unsigned int i=0;
	while(i<strlen(w)){
		if(i==strlen(w)-1){
			current=current->termfatlevel(w[i],1);
			break;	
		}
		current=current->termfatlevel(w[i],0);
		i++;
	}
	if(current->ppt==NULL){
		//cout<<"null pointer"<<endl;
		return -1;
	}
	if((current->ppt->visited==1)&&(flag==1)){
		return -2;
	}
	return current->ppt->length(flag);


}

void Trie::print(){

	Trienode* current = root;
	if(current!=NULL)
	cout<<"Printing Trie"<<endl;
	while(current!=NULL){
		current->print();
		if(current->ppt!=NULL){
			current->ppt->display();
		}
		Trienode* cur2 = current;
		while(cur2->next!=NULL){
			cout<<"->";
			cur2->next->print();
			//Trienode* cur3 = cur2;
			/*while(cur3->next->child!=NULL){
				cout<<"|"<<endl;
				cur3->next->child->print();
				cur3=cur3->child;
				cout<<"|"<<endl;
		
			}*/
			cur2=cur2->next;
		}
		current=current->child;
		cout<<endl;
	}


}

////////////////////////////////////////////////////////////////////////////////////////////////


