/* ------
   myio.c
   ------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bool.h"
#include "mydatatype.h"

/*
   --- Funcao de leitura de um desenho previamente gravado em PBM (P1)

	O resultado da funcao e um booleano:
		1 : o desenho foi lido com sucesso
		0 : o desenho nao foi lido, ocorreu um erro
*/

boolean load( char fnome[], DESENHO d )
{

/*
   fnome: nome do ficheiro que se vai carregar
   d    : matriz para onde vai ser carregado o desenho
*/

  FILE *fp;
  char linha[MAXCOLUNAS+1];  // usada para ler as linhas de comentario
  int i, j;                  // variaveis de controlo das linhas e colunas
  boolean erro=FALSE;        // a primeira linha da matriz guardara a dim da imagem

  fp = fopen(fnome,"r");
  if(!fp) return FALSE;
  else
  {
	fgets(linha,MAXCOLUNAS+1,fp); /* le a linha com o identificador */

	/* Enquanto nao conseguir ler as dimensoes... */
	while(fscanf(fp,"%d %d",&(d[0][1]),&(d[0][0]))!=2)
	  fgets(linha,MAXCOLUNAS+1,fp); // descarta as linhas com comentarios

	i=1;
	while((i<d[0][0])&&(!erro)) //Enq nao se tiverem lido as linhas todas
	{
	  j=0;
	  while((j<d[0][1])&&(!erro)) // Enq nao se tiverem lido todas as colunas
		if(!fscanf(fp,"%d",&(d[i][j]))) erro = TRUE;
		else j++;
	  i++;
	}

	fclose(fp);
	return (!erro);
  }
}

/*
    --- Funcao de gravacao do desenho carregado na matriz para o formato PBM (P1)

	   O resultado da funcao e um booleano:
		 1 : o desenho foi gravado com sucesso
		 0 : o desenho nao foi gravado, ocorreu um erro
*/

boolean save( char fnome[], DESENHO d )
{

/*
   fnome: nome do ficheiro onde se vai gravar
   d    : matriz contendo o desenho que se vai gravar
*/

  FILE *fp;
  int linhas = d[0][0] , colunas = d[0][1] , i , j;
   // variaveis de controlo das linhas e colunas
   // a primeira linha da matriz contem a dim da imagem

  fp = fopen(fnome,"w");
  if(!fp) return FALSE;
  else
  {
	fprintf(fp,"P1\n");
	fprintf(fp,"# Imagem PBM gerada pela aplicacao de DESENHO\n");
	fprintf(fp,"%d %d\n",d[0][1],d[0][0]);

	for(i=1;i<=linhas;i++)
	{
		for(j=1;j<=colunas;j++)
		{
			fprintf(fp,"%d ",d[i][j]);
		}
		fprintf(fp,"\n");
	}

	fclose(fp);
	return (TRUE);
  }
}

/* --- Funcao que escreve a matriz no monitor */

int printDesenho(DESENHO d)
{
  int linhas = d[0][0] , colunas = d[0][1] , i , j;

  for(i=1;i<=linhas;i++)
  {
	for(j=1;j<=colunas;j++)
	{
		printf("%d",d[i][j]);
	}
	printf("\n");
  }
  return 0;
}


/* -------------------------------------------------
	OPERAÇOES GRAFICAS
   ------------------------------------------------- */

void setMarca (int n)
{
	marca=n;
}

/*
   x : linha da matriz d onde se quer marcar o ponto
   y : coluna da matriz d onde se quer marcar o ponto
   d : matriz contendo o desenho onde se vai marcar o ponto
*/

void point(int x, int y, DESENHO d)
{
	d[x][y]=marca;
}

/*
   Uma imagem explicativa:

   +-------------------------------------------+
   |                                           |
   | desenho d                     (x2,y2)     |
   |                                 |         |
   |                              +--+         |
   |                           +--+            |
   |                        +--+               |
   |                     +--+                  |
   |                  +--+                     |
   |               +--+                        |
   |            +--+                           |
   |    (x1,y1)-|                              |
   |                                           |
   +-------------------------------------------+
*/


void line(float x1, float y1, float x2, float y2, DESENHO d)
{
  float m = (y1-y2)/(x1-x2), b = y1 - m * x1, t, tx,ty;
  int i, y, x;

  if(x1!=x2)
  {
	if(x1>x2)
	{
		ty=y1; tx=x1; x1 = x2; y1 = y2; x2 = tx; y2 = ty;
	}

	for(i=x1;i<x2;i++)
	{
		y = m * i + b;
		d[i][y]=marca;
	}
  }
  else if(y1 != y2)
  {
	if (y1 > y2)
	{
		t = y2; y2 = y1; y1 = t; t = x2; x2 = x1; x1 = t;
	}
	m = (x1 - x2) / (y1 - y2);
	b = x1 - m * y1;

	for(i=y1;i<=y2;i++)
	{
		x = (m * i + b);
		d[x][i]=marca;
	}
  }
}

/*
   Desenha um rectangulo cuja sua diagonal seja
   uma linha do ponto (x1,y1) ate (x2,y2)

   Uma imagem explicativa:

   +-------------------------------------------+
   | desenho d                                 |
   |                               (x2,y2)     |
   |           +---------------------+         |
   |           |                  l  |         |
   |           |               a  +--+         |
   |           |           o n +--+  |         |
   |           |         g  +--+     |         |
   |           |      a  +--+        |         |
   |           |   i  +--+           |         |
   |           |d  +--+              |         |
   |           |+--+                 |         |
   |           +---------------------+         |
   |      (x1,y1)                              |
   +-------------------------------------------+

*/

void rect(int x1, int y1, int x2, int y2, DESENHO d)
{
	line(x1,y1,x2,y1,d); // linha vertical esquerda
	line(x1,y2,x2,y2,d); // linha vertical direita
	line(x2,y1,x2,y2,d); // linha horizontal inferior
	line(x1,y1,x1,y2,d); // linha horizontal superior
}

/*
   a : array contendo todos os pontos na forma:
         x1,y1,x2,y2,...,xn,yn
   b : tamanho-1 do array a
   d : matriz contendo o desenho onde se vai marcar as varias linhas
*/

void polyLine(float a[], int b, DESENHO d)
{
  int i;

  for(i=0;i<b-2;i+=2)
	line(a[i],a[i+1],a[i+2],a[i+3],d);
}

/*
  Propriedades para desenhar um circulo:
    a)  'l' e 'c'  SEMPRE >= que 'r'
    b1) 'l'+'r'    SEMPRE <= MAXLINHAS
    b2) 'c'+'r'+1  SEMPRE <= MAXCOLUNAS
*/

int circ(int l , int c , int r , DESENHO d)
{
  int a,ret=0,linhas=d[0][0],colunas=d[0][1];

  if((l>=r && c>=r) || (l+r<=linhas && c+r+1<=colunas))
  {
  	for(a=0;a<360*r;a++)
	{
		int px = r * cos(a) , py = r * sin(a) , yy = py+c , xx = px+l;

		d[xx][yy]=marca;
	}
	ret=1;
  }
  return ret;
}

/*
  Propriedades para desenhar uma elipse:
    a1)  'x1' e 'y1' SEMPRE >= x2
    b1) 'x1'+'x2'    SEMPRE <= MAXLINHAS
    b2) 'y1'+'y2'+1  SEMPRE <= MAXCOLUNAS
*/

int elip(int x1, int y1, int x2, int y2, DESENHO d)
{
  int a,ret=0,linhas=d[0][0],colunas=d[0][1];

	for(a=0;a<360*(x2+y2);a++)
	{
		int px = x2 * cos(a) , py = y2 * sin(a) , yy = py+y1 , xx = px+x1;

		d[xx][yy]=marca;
	}
	return ret;
}

int text (int x,int y,char texto[],char ori, DESENHO d)
{
	int i;
	if (ori == 'h')
	{
		for (i=0;texto[i] != '\0';i++)
		{
			d[x][y]=texto[i];
			y++;
		}
		return 0; 	
	}
	if (ori == 'v')
	{
		for (i=0;texto[i] != '\0';i++)
		{
			d[x][y]=texto[i];
			x++;
		}		
		return 0;
	}
	else
		return -1; //para casos de dar erro!!!
}

int erase (int x1,int y1,int x2,int y2, DESENHO d)
{
	int i,j;
	if (y1 > y2)
		erase (x2,y2,x1,y1,d);
	if (x2 > x1)
	{
		for (i=x1; i <= x2; i++)
		{
			for (j=y1; j <= y2; j++)
				d[i][j]='\0';			
		}
		return 0;
	}
	else
	{
		for (i=x2; i<= x1; i++)
		{
			for (j=y1; j <= y2; j++)
				d[i][j]='\0';
		}
		return 0;	
	}
}
