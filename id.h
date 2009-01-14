/* ----
   id.h
   ----*/

/*---------
  Estrutura
  ---------*/

typedef struct id_list
{
	char id[100];
	char comando[100];
	struct id_list * next_group;
	struct id_list * next;
	}Id_list;
	
/* ---------------------
   Cabeçalho das funções
   ---------------------*/

Id_list * init();
Id_list * init_let (char id[],Id_list * list_pointer);
Id_list * let (char id[], char comando[], Id_list * list_pointer, char opcao);
Id_list * del (char id[], Id_list* list_pointer);
int saveobj(char id[],char ficheiro[], Id_list * list_pointer);
