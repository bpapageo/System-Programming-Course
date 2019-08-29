#include "structures.h"

using namespace std;

print_class::print_class(){
	size = 100;
	index = 0;
	array = new print_struct*[size];
	for(int i=0; i<size; i++) array[i] = NULL;
}

print_class::~print_class(){

	for(int i=0; i<index; i++)
		delete array[i];

	delete[] array;
}

void::print_class::insert(char* w, char c){

	if (index==size)
	{
	 	size = size*2;
	 	print_struct** temp = new print_struct*[size];
	 	for(int i=0; i<size/2; i++)
			temp[i] = array[i];
		delete[] array;
		array = temp;
	}

	array[index] = new print_struct(w,c);
	index++;
}

void print_class::highlight(char* document, char** words, int words_number){

	// table construction

	char* temp_document = new char[strlen(document) + 1];
	strcpy(temp_document,document);

	char* tok;
	tok = strtok(temp_document," ");

	while(tok!=NULL)
	{


		int flag = 0;
		for(int i=0; i<words_number; i++){
			if(strcmp(words[i],tok)==0)
				flag = 1;
		}

		if(flag==1)	insert(tok,'^');
		else		insert(tok,' ');


		tok = strtok(NULL," ");
	}

	if(temp_document!=NULL) delete []temp_document;

	// table print

	int words_per_line = 10;
	int start = 0;
	int wrds = index;

	while(wrds!=0)
	{

		for(int i=start; i<start + words_per_line; i++)
		{
			if (i>=index) break;
			cout<<array[i]->word<<" ";
			wrds--;
		}
	
		cout<<endl;
	
		int flg = 0;
		for(int i=start; i<start + words_per_line; i++)
		{
			if (i>=index) break;

			for(int j=0; j<strlen(array[i]->word); j++)
				if (array[i]->c == '^') flg = 1;
		}

	
		if (flg == 1)
		{
			for(int i=start; i<start + words_per_line; i++)
			{
				if (i>=index) break;

				for(int j=0; j<strlen(array[i]->word); j++)
					cout<<array[i]->c;
				cout<<" ";	
			}
	
			cout<<endl;

		}

		start = start + words_per_line;
	
	}


}

