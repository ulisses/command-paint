/* ----------------------------------------------------
   Programa DESENHO que utiliza as funcoes de
   leitura e escrita de desenhos

   2006-03-10: created by
       Mario Ulisses Pires Araujo Costa        (43175)
       Nuno Andre Veloso Matias                (44229)
       Vasco Miguel Borges de Almeida Ferreira (43207)
   ---------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mydatatype.h"
#include "bool.h"
#include "myio.h"

/* ------------------------------------------------------------
   Inicio do codigo da aplicacao DESENHO
   ------------------------------------------------------------ */


void criaFile(int l,int c,char fnome[])
{
  FILE *fp=fopen(fnome,"w");
  int i,j;

  fprintf(fp,"P1\n");
  fprintf(fp,"#Imagem PBM gerada pela aplicacao de DESENHO\n");
  fprintf(fp,"%d %d\n",c,l);
  for(i=0;i<l;i++)
  {
	for(j=0;j<c;j++)
	{
		fprintf(fp,"0 ");
	}
	fprintf(fp,"\n");
  }

  fclose(fp);
}

/*
   validacao dos parametros das funcoes
*/

int valida(char *op, int n)
{
  int i,ret=0;

  for(i=0;op-1!=NULL;i++,op = strchr(op,',')+1);
  if (i==n) ret=1;

  return ret;
}


void opcoes (DESENHO d1)
{
  int a,b,c,d;
  char *comando="" , *pontos="";

  while((comando[0]!='s') && (pontos[0]!='s'))
  {
	//system("clear");
	printDesenho(d1);
	puts("\tPrima 's' para voltar\n\n\n");

	char *pontos2=(char *)calloc(100,sizeof(char));
	comando=(char *)calloc(100,sizeof(char));
	pontos=(char *)calloc(100,sizeof(char));

	scanf("%s",comando);
	scanf("%s",pontos);
	
	strcpy(pontos2,pontos);

	if(strcmp(comando,"Point")==0 && valida(pontos,2))
	{
		sscanf (pontos,"%d,%d", &a , &b);
		point(a,b,d1);
	}
	if(strcmp(comando,"PolyLine")==0)
	{
		float mtz[100];

		for(b=0 ; pontos2-1!=NULL ; b++ , pontos2 = strchr(pontos2,',')+1)
		{
			char *acc = (char *)calloc(100,sizeof(char));

			sscanf (pontos2,"%[^,]", acc);
			mtz[b] = atoi(acc);
		}
		polyLine(mtz,b-1,d1);
		comando=""; // comando = 'PolyLine' contem 'Line'
	}
	if(strcmp(comando,"Line")==0 && valida(pontos,4))
	{
		sscanf (pontos,"%d,%d,%d,%d", &a , &b , &c , &d);
		line(a,b,c,d,d1);
	}
	if(strcmp(comando,"Rect")==0 && valida(pontos,4))
	{
		sscanf (pontos,"%d,%d,%d,%d", &a , &b , &c , &d);
		rect(a,b,c,d,d1);
	}
	if(strcmp(comando,"Circ")==0 && valida(pontos,3))
	{
		sscanf (pontos,"%d,%d,%d", &a , &b , &c);
		if(!(circ(a,b,c,d1))) puts("Comando invalido!");
	}
	if(strcmp(comando,"Elip")==0 && valida(pontos,4))
	{
		sscanf (pontos,"%d,%d,%d,%d", &a , &b , &c , &d);
		if(!(elip(a,b,c,d,d1))) puts("Comando invalido!");
	}
  }
}


void menu(DESENHO d1)
{
  char *opcao=(char *)calloc(100,sizeof(char)), *marca=(char *)calloc(2,sizeof(char));

  system("clear");
  puts("\n\n\n");
  puts("\t1 - Cria um desenho novo");
  puts("\t2 - Abrir um desenho guardado");
  puts("\t3 - Guardar um desenho criado");
  puts("\t4 - Set marca\n");
  printf("\t0 - Sair\n\n> ");
  scanf("%s",opcao);

  if(strcmp(opcao,"1")==0)
  {
	char *colunas=(char *)calloc(100,sizeof(char));
	char *linhas=(char *)calloc(100,sizeof(char));
	char *fnome=(char *)calloc(100,sizeof(char));

	printf("\tIntroduza o numero de colunas: ");
	scanf("%s",colunas);
	printf("\tIntroduza o numero de linhas: ");
	scanf("%s",linhas);
	printf("\tIntroduza o nome do ficheiro: ");
	scanf("%s",fnome);

	criaFile(atoi(linhas),atoi(colunas),fnome);
	opcoes(d1);
  }
  if(strcmp(opcao,"2")==0)
  {
	char *nomef=(char *)calloc(100,sizeof(char));

	printf("\tIntroduza o nome do ficheiro existente: ");
	scanf("%s",nomef);

	if(load(nomef,d1))
	{
		puts("FICHEIRO EXISTE!");
		opcoes(d1);
		save("out.pbm",d1);
	}
	else printf("\n\n> ERRO, ficheiro nao existe!\n\n");
  }
  if(strcmp(opcao,"3")==0)
	save("out.pbm",d1);
  if(strcmp(opcao,"4")==0)
  {
	printf("\tIntroduza a marca: ");
	scanf("%s",marca);
	setMarca(atoi(marca));
  }
  if(strcmp(opcao,"0")==0)
	exit(1);
  else menu(d1);
}

/*
  Permite inserir uma lista de comandos separados por '\n'
  ate se carregar em 's'.
      Comandos disponiveis:
        - Point    x,y
        - PolyLine x1,y1,...,xn,yn
        - Line     x1,y1,x2,y2
        - Rect     x1,y1,x2,y2
        - Circ     x,y,r
        - Elip     x1,y1,x2,y2
*/


int main()
{
	DESENHO d1;
	menu(d1);
	
	return 0;
}


/* ------------------------------------------------------------
   Fun
   ------------------------------------------------------------ */

/* desenha uma cara numa imagem 800x600
  circ(250,300,250,d1);
  circ(300,300,50,d1);
  elip(200,200,50,100,d1);
  elip(200,400,50,100,d1);
  elip(400,300,30,100,d1);
  elip(400,300,1,100,d1);
*/
