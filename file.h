/*------
  file.h
  ------*/
  
typedef struct comlist
{
	char teclado[100];
	struct comlist * next;
	}ComList;
	
/* ---------------------
   Cabeçalho das funções
   ---------------------*/	

int saveobj (char id[],char ficheiro[], Id_list * list_pointer);
