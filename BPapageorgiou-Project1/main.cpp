#include "structures.h"
#include <cmath>


using namespace std;

int main(int argc,char *argv[]){
	FILE *stream;
        char *linee = NULL;
        size_t len = 0;
	char line[100],name[20];
	int K,numoflines=0,i=0,counter=0,swords=0;
	int flag=0;
	struct Document* map;
	Trie *trie=new Trie();
	if(argc<3){
		cout<<"Incorrect num of arguments.Try again!"<<endl;
		return -1;
	}
	for(int i=1;i<argc;i+=2){
		if(strcmp(argv[i],"-i")==0){
			flag=1;
			strcpy(name,argv[i+1]);
		}
		else if(strcmp(argv[i],"-k")==0){
			K = atoi(argv[i+1]);
		}
	}
	if(flag==1){
		//metrima grammwn gia megethos map
	       	stream = fopen(name, "r");
	        if (stream == NULL) {
	               	perror("fopen");
	              	exit(EXIT_FAILURE);
	        }
	        while ((getline(&linee, &len, stream)) != -1) {
		       	numoflines++;
	        }
		fclose(stream);
		//dhmiourgia map
		cout<<numoflines<<endl;
		map=new struct Document[numoflines];
          	stream = fopen(name, "r");
           	if (stream == NULL) {
               		perror("fopen");
               		exit(EXIT_FAILURE);
           	}
           	while ((getline(&linee, &len, stream)) != -1) {
			//cout<<linee<<endl;
			char* pch;
			pch = strtok(linee,"\t");
			map[i].id = atoi(pch);
			if((map[i].id)!=counter){
				cout<<"Wrong input file"<<endl;
				return -1;
			}
			else{
				counter++;
			}
			pch=strtok(NULL,"\n");
			map[i].text = new char[strlen(pch)+1];
			strcpy(map[i].text,pch);
			i++;
           	}
		free(linee);
		fclose(stream);

	}
	else{
		cout<<"No input file"<<endl;
		return -1;
	}
	//insert mesw toy map
	for(int i=0;i<numoflines;i++){
		char* pch,*copy;
		copy = new char[strlen(map[i].text)+1];
		strcpy(copy,map[i].text);
		pch = strtok(copy," ");
		trie->insert(pch,map[i].id);
		int init=swords;
		swords++;
		while(pch!=NULL){
			pch = strtok(NULL," ");
			if(pch!=NULL){
				trie->insert(pch,map[i].id);
				swords++;	
			}	
		}
		int fin=swords;
		map[i].sum=fin-init;
		delete[] copy;
	}
	while(cin.getline(line,200)){
		char* pch;
		pch = strtok(line," ");
		if(strcmp(pch,"/search")==0){
			double IDF;
			pch = strtok(NULL," ");
			if(pch==NULL){
				cout<<"You must search at least one word"<<endl;
				continue;
			}
			struct Score *score=new struct Score[numoflines];
			//struct Score score[386];
			for(int i=0;i<numoflines;i++){
				score[i].s=0;
				score[i].id=-2;
			}
			int c=1;
			double avgdl=swords/(numoflines-1);
			float kl=1.2;
			float b=0.75;
			char** words = new char*[10];
			while((pch!=NULL)&&(c<=10)){
				char* word = new char[strlen(pch)+1];
				strcpy(word,pch);
				int df=trie->docf(word,0);
				IDF=log((numoflines-df + 0.5)/(df+0.5));
				for(int i=0;i<numoflines;i++){
					int tf=trie->termf(word,i);
					if(tf!=-1){
						score[i].s+=(IDF*(tf*(kl+1)))/(tf+kl*(1-b+b*(map[i].sum)/avgdl));
						score[i].id=map[i].id;
					}					
				}
				words[c-1] = new char[strlen(pch)+1];
				strcpy(words[c-1],word);
				c++;
				delete[] word;
				pch = strtok(NULL," ");

			}
			if(K>numoflines){
				K=numoflines;
			}
			/*	for(int i=0;i<numoflines;i++){
						cout<<score[i].s<<" "<<score[i].id<<endl;
			}*/

			//quicksort gia evresh twn topK

			Qsort(score,0,numoflines-1);

			/*	cout<<"EEEEE"<<endl;
				for(int i=0;i<numoflines;i++){
						cout<<score[i].s<<" "<<score[i].id<<endl;
			}*/
			int j=1;
			for(int i=0;i<K;i++){
				if(score[i].id!=-2){
					printf("%2d.( %4d)[%4.5f] ",j,score[i].id,score[i].s);
					for(int k=0;k<numoflines;k++){
						if(score[i].id==map[k].id){
							//cout<<map[k].text<<endl;
							print_class* obj = new print_class();
							obj->highlight(map[k].text,words,c-1);
							delete obj;
						}
					}
					j++;
				}
				else{
					K++;
					continue;
				}
			}
		for(int i=0;i<c-1;i++)
			delete[] words[i];
		delete[] words;

		delete[] score;

		}
		else if(strcmp(pch,"/df")==0){
			pch = strtok(NULL," ");
			//df xwris orisma
			if(pch==NULL){
				for(int i=0;i<numoflines;i++){
					char *pc,*copy;
					copy = new char[strlen(map[i].text)+1];
					strcpy(copy,map[i].text);
					pc = strtok(copy," ");
					int df=trie->docf(pc,1);
					if(df!=-2){
						cout<<pc<<" "<<df<<endl;
					}
					while(pc!=NULL){
						pc = strtok(NULL," ");
						if(pc!=NULL){
							int df=trie->docf(pc,1);
							if(df!=-2){
								cout<<pc<<" "<<df<<endl;
							}		
						}	
					}
					delete[] copy;

				}

			}
			//df me orisma
			else{
				char* word = new char[strlen(pch)+1];
				strcpy(word,pch);
				int df=trie->docf(word,0);
				if(df!=-2){
					cout<<word<<" "<<df<<endl;
				}
				delete[] word;
			}

		}
		else if(strcmp(pch,"/tf")==0){
			pch = strtok(NULL," ");
			if(pch==NULL){
				cout<<"Wrong input,try again!"<<endl;
				continue;
			}
			int id = atoi(pch);
			pch = strtok(NULL," ");
			if(pch==NULL){
				cout<<"Wrong input,try again!"<<endl;
				continue;
			}
			char* word = new char[strlen(pch)+1];
			strcpy(word,pch);
			int tf=trie->termf(word,id);
			cout<<id<<" "<<word<<" "<<tf<<endl;
			delete[] word;
			

		}
		else if(strcmp(pch,"/exit")==0){
			delete[] map;
			delete trie;
   			return 0;
		}
		else{
			cout<<"Wrong input,try again!"<<endl;
			continue;
		}
		
	}
   	return 0;

}


