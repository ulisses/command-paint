#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "id.h"
#include "file.h"

int saveobj (char id[],char ficheiro[], Id_list * list_pointer)
{
	Id_list *aux;
	FILE *f;
	char mfv[100] = "";
	strcat(mfv,ficheiro);
	strcat(mfv,".mfv");
	
	if ((f = fopen(mfv,"a")) == NULL)
		return 1;
	
	aux = list_pointer;
	while (strcmp(aux->id,id)!=0)
		aux=aux->next;
	if (aux->next_group == NULL)
	{
		fprintf(f,"%s\n",aux->comando);
		fclose(f);
		return 0;		
	}
	else
	{
		aux=aux->next_group;
		while (aux != NULL)
		{
			if (strcmp(aux->comando,"")==0)
				aux=aux->next_group;
			else
			{
				fprintf(f,"%s\n",aux->comando);
				aux=aux->next_group;
			}
		}
		fclose(f);
		return 0;
	}
}


ComList * init_hist ()
{
	ComList * ret_pointer;
	ret_pointer = NULL;
	return ret_pointer;
}

ComList * historico (ComList * ret_pointer, char input[])
{
	ComList * aux = (ComList *)malloc(sizeof(ComList));
	
	if (ret_pointer == NULL)
	{
		ret_pointer = aux;
		strcpy(ret_pointer->teclado,input);
		ret_pointer->next = NULL;

		return ret_pointer;		
	}
	else
	{
		ComList * ajudo;
		
		ajudo = ret_pointer;
		while (ajudo->next != NULL)
			ajudo=ajudo->next;
		ajudo->next = aux;
		strcpy(aux->teclado,input);
		aux->next=NULL;
	
				
		return ret_pointer;
	}
}


int savecomlist(char ficheiro[], ComList * ret_pointer)
{
	ComList * aux;
	FILE *f;
	char mfv[100]="";
	strcat(mfv,ficheiro);
	strcat(mfv,".mfv");
	
	if (ret_pointer == NULL)	
		return 0;
	else
	{
		f = fopen (mfv,"a");
		aux = ret_pointer;
		while (aux != NULL)
		{
			fprintf(f,"%s\n",aux->teclado);
			aux=aux->next;			
		}
		
		aux=ret_pointer;
		ret_pointer=aux->next;
		while (ret_pointer != NULL)
		{
			free(aux);
			aux=ret_pointer;
			ret_pointer=aux->next;			
		}
		free(aux);
		
		fclose(f);
		return 0;
	}
}


int main()
{
	ComList * ret_pointer = init_hist();

	

	ret_pointer = historico(ret_pointer,"circulo");
	ret_pointer = historico(ret_pointer,"bola");
	ret_pointer = historico(ret_pointer,"merda");
	
	printf("%s\n",ret_pointer->teclado);
	printf("%s\n",ret_pointer->next->teclado);
	
	savecomlist("ola",ret_pointer);
	
	return 0;
}
