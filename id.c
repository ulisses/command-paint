#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "id.h"


Id_list * init()
{
	Id_list * list_pointer = NULL;
	return list_pointer;
}

Id_list * init_let (char id[], Id_list * list_pointer)
{
	Id_list * aux = (Id_list *) malloc (sizeof(Id_list));
	aux->next=list_pointer;
	list_pointer=aux;
	strcpy(list_pointer->id,id);
	strcpy(list_pointer->comando,"");
	list_pointer->next_group=NULL;	
	
	return list_pointer;
}

Id_list * let (char id[], char comando[], Id_list * list_pointer,char opcao)
{
	Id_list *aux, *ant;

	if (opcao == 'c')
	{
		if (list_pointer == NULL)
		{
			list_pointer = (Id_list *)malloc(sizeof(Id_list));
			strcpy (list_pointer->id,id);
			strcpy (list_pointer->comando,comando);
			list_pointer->next_group=NULL;
			list_pointer->next = NULL;
			
			return list_pointer;
		}
		else
		{
			aux = (Id_list *) malloc(sizeof(Id_list));
			strcpy(aux->id,id);
			strcpy(aux->comando,comando);
			list_pointer->next_group=NULL;
			aux->next=list_pointer;
			list_pointer=aux;
				
			return list_pointer;
		}
	}
	if (opcao == 'g')
	{
		if (list_pointer == NULL)
			return list_pointer;
		else
		{
			if (list_pointer->next_group == NULL)
			{
				aux = list_pointer;
				while (strcmp(id, aux->id)!=0)
					aux=aux->next;
				list_pointer->next_group=aux;
				
				aux = list_pointer;
				while (strcmp(id,aux->id)!=0)
				{
					ant = aux;
					aux = aux->next;
				}
				ant->next=aux->next;
				
				return list_pointer;
			}
			else
			{
				aux = list_pointer;
				while (aux != NULL) //percorrer ate next_group apontar para NULL
				{
					ant = aux;
					aux=aux->next_group;
				}

				aux = list_pointer;
				while (strcmp(id,aux->id)!=0) // percorrer para achar a estrutura que tem aquele id
					aux=aux->next;
				
				ant->next_group=aux;

				aux = list_pointer;
				while (strcmp(id,aux->id)!=0)
				{
					ant=aux;
					aux = aux->next;
				}
				ant->next=aux->next;
				
				return list_pointer;
			}
		}
		
	}
	return list_pointer;
}

Id_list* del(char id[], Id_list* list_pointer)
{
	Id_list* aux;
	Id_list* ant;	
	if(list_pointer==NULL)
		return list_pointer;
	if(strcmp(list_pointer->id,id)==0)
	{
		aux=list_pointer;
		list_pointer=list_pointer->next;
		free(aux);
		return list_pointer;
	}

	aux=list_pointer;
	
	while(strcmp(aux->id,id)!=0)
	{
		ant=aux;
		aux=aux->next;
		
		if(aux==NULL)
			return list_pointer;
	}
	
	ant->next = aux->next;
	free(aux);
	return list_pointer;
}

Id_list * ungroup(char id[],Id_list * list_pointer)
{
	Id_list * aux;
	Id_list * ant;

	if(list_pointer==NULL)
		return list_pointer;
	
	if (strcmp(list_pointer->id,id)==0)
	{
		aux = list_pointer;
		list_pointer=list_pointer->next;
		aux->next=NULL;

		ant=aux;
		aux=aux->next_group;
		while (aux!=NULL)
		{
			free(ant);
			ant=aux;
			aux=aux->next_group;
		}
		free(ant);
		
		return list_pointer;
	}
	else
	{
		aux = list_pointer;
		while (strcmp(aux->id,id)!=0)
		{	
			ant=aux;
			aux=aux->next;
		}
			
		ant->next=aux->next;
		
		ant=aux;
		aux=aux->next_group;
		while(aux != NULL)
		{
			free(ant);
			ant=aux;
			aux=aux->next_group;
		}
		free(ant);
		return list_pointer;
	}
}

int main()
{
	Id_list* list_pointer=init();

	list_pointer=let("elipse","elip 1,2,3",list_pointer,'c');
	list_pointer=let("circulo","circ 4,5,6",list_pointer,'c');
	list_pointer=let("circulo2","circ 4,5,6",list_pointer,'c');
	list_pointer=let("circulo3","circ 4,5,6",list_pointer,'c');
	list_pointer=let("circulo4","circ 4,5,6",list_pointer,'c');

	//list_pointer=del("rjyjt",list_pointer);
	//list_pointer=init_let("merda",list_pointer);
	//list_pointer=let("jyjt","",list_pointer,'g');
	//list_pointer=let("rgerg","",list_pointer,'g');
	//list_pointer=let("rjyjt","",list_pointer,'g');
	list_pointer=init_let("casa",list_pointer);
	list_pointer=let("circulo","",list_pointer,'g');
	list_pointer=let("circulo4","",list_pointer,'g');

	list_pointer=init_let("pinheiro",list_pointer);
	list_pointer=let("circulo2","",list_pointer,'g');
	list_pointer=let("circulo3","",list_pointer,'g');
	
	list_pointer=init_let("paisagem",list_pointer);
	list_pointer=let("pinheiro","",list_pointer,'g');
	list_pointer=let("casa","",list_pointer,'g');
	
//	list_pointer = ungroup("casa",list_pointer);

	printf("%s\n",list_pointer->next->id);
	printf("%s\n",list_pointer->id);
	printf("%s\n",list_pointer->next_group->id);
	printf("%s\n",list_pointer->next_group->next_group->id);
	//printf("%s\n",list_pointer->next_group->next_group->id);

	return 0;
}
