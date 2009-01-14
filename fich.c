#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fich.h"

int main()
{
	Imagem *pbm=NULL;
//	Pontos *pontos = NULL;
	pbm = load("bandeira.pbm",pbm);

// 	pbm = point(2,2,1,pbm);
// 	pbm = point(0,0,1,pbm);
// 	pbm = line(1, 10, 15, 20, 1, pbm);
// 	pbm = line(1, 20, 15, 10, 1, pbm);
// 	pbm = line(1, 10, 1, 20, 1, pbm);

// 	pbm = line(0,0,8,10,1,pbm);
	pbm = merge("imagemMinus.pbm",pbm);
	printDesenho(pbm);
	save("teste.pbm",pbm);

	int i=2346;
	if(i)
		puts("VERDADE");
	
	return 0;
}

Imagem *load(char *nome, Imagem *ret_pointer)
{
	FILE *fp = fopen(nome,"r");

	Imagem *pbm = (Imagem*) malloc(sizeof(Imagem));
	Linhas *linhasCp;
	Colunas *colunasCp = (Colunas*) malloc(sizeof(Colunas));
	pbm->matriz = (Linhas*) malloc(sizeof(Linhas));

	linhasCp = pbm->matriz;
	colunasCp = linhasCp->proxC;

	ret_pointer=pbm;

	char *tipo = (char *) malloc(sizeof(char));
	char *comment = (char *) malloc(sizeof(char));

	int col=0, lin=0, i, j;

	fscanf(fp, "%[^\n]%*c", tipo);
	fscanf(fp, "%[^\n]%*c", comment);
	fscanf(fp, "%d %d", &col, &lin);

	ret_pointer->lin = lin;
	ret_pointer->col = col;

	for(i=0 ; i < lin ; i++ , linhasCp = linhasCp->proxL)
	{
		pbm = (Imagem*) malloc(sizeof(Imagem));
		linhasCp->proxL = (Linhas*) malloc(sizeof(Linhas));
		linhasCp->proxC = (Colunas*) malloc(sizeof(Colunas));

		colunasCp = linhasCp->proxC;
		for(j=0 ; j < col ; j++ , colunasCp = colunasCp->prox)
		{
			colunasCp->prox = (Colunas*) malloc(sizeof(Colunas));

			fscanf(fp,"%d",&(colunasCp->c));
		}
		colunasCp->prox=NULL;
	}
	linhasCp->proxL=NULL;
	fclose(fp);
	return ret_pointer;
}

void printDesenho(Imagem *pbm)
{
	Linhas *desenho = pbm->matriz;
	Colunas *colunas = desenho->proxC;

	for( ; desenho->proxL!=NULL ; desenho = desenho->proxL)
	{
		colunas = desenho->proxC;
		for( ; colunas->prox!=NULL ; colunas = colunas->prox)
		{
			printf("%d ", colunas->c);
		}
		puts("");
	}
}

void save(char *nf, Imagem *pbm)
{
	FILE *fp;
	Linhas *desenho = pbm->matriz;
	Colunas *colunas = pbm->matriz->proxC;

	fp = fopen(nf,"w");

	fprintf(fp,"P1\n");
	fprintf(fp,"# Imagem PBM gerada pela aplicacao de DESENHO\n");
	fprintf(fp,"%d %d\n",pbm->col,pbm->lin);

	for( ; desenho->proxL!=NULL ; desenho = desenho->proxL)
	{
		colunas = desenho->proxC;
		for( ; colunas->prox!=NULL ; colunas = colunas->prox)
		{
			fprintf(fp,"%d ", colunas->c);
		}
		fprintf(fp,"\n");
	}
}

Imagem *point(int x, int y, int marca, Imagem *pbm)
{
	Linhas *desenho = pbm->matriz;
	Colunas *colunas = pbm->matriz->proxC;
	Imagem *pbmAux = (Imagem*) malloc(sizeof(Imagem));
	int i,j;

	pbmAux=pbm;

	for(i = 0 ; desenho!=NULL ; desenho = desenho->proxL, i++)
	{
		colunas = desenho->proxC;
		for(j = 0 ; colunas!=NULL ; colunas = colunas->prox, j++)
		{
			if(i == x && j == y)
				colunas->c = marca;
		}
	}
	return pbmAux;
}

Imagem *line(float x1, float y1, float x2, float y2, int marca, Imagem *pbm)
{
	Linhas *desenho = pbm->matriz;
	Colunas *colunas = pbm->matriz->proxC;
	Imagem *pbmAux = (Imagem*) malloc(sizeof(Imagem));
	int i, y, j;
	float  tx,ty, m, b;

	pbmAux=pbm;

	if(x1==x2)
	{
		if(y1>y2)
		{
			ty = y1; tx = x1; x1 = x2; y1 = y2; x2 = tx; y2 = ty;
		}

		for(i = 0 ; i != (int)x1 ; desenho = desenho->proxL , i++);
		colunas = desenho->proxC;
		for(j = 0 ; j != (int)y1 ; colunas = colunas->prox, j++);
		for(j = (int)y1 ; j <= (int)y2 ; colunas = colunas->prox, j++)
			colunas->c=marca;
	}
	else
	{
		m = (y1-y2)/(x1-x2), b = y1 - m * x1;
	
		if(x1>x2)
		{
			ty=y1; tx=x1; x1 = x2; y1 = y2; x2 = tx; y2 = ty;
		}

		for(i = 0 ; i != (int)x1 ; desenho = desenho->proxL , i++);
		for(i=(int)x1 ; i<=(int)x2 ; desenho = desenho->proxL , i++)
		{
			colunas = desenho->proxC;
			for(j = 0, y = m * i + b; j <= y ; colunas = colunas->prox, j++);
				colunas->c=marca;
		}
	}
	return pbmAux;
}

Imagem *rect(int x1, int y1, int x2, int y2, int marca, Imagem *pbm)
{
	Imagem *pbmAux = (Imagem*) malloc(sizeof(Imagem));

	pbmAux=pbm;

	pbm = line(x1,y1,x2,y1,marca,pbm); // linha vertical esquerda
	pbm = line(x1,y2,x2,y2,marca,pbm); // linha vertical direita
	pbm = line(x2,y1,x2,y2,marca,pbm); // linha horizontal inferior
	pbm = line(x1,y1,x1,y2,marca,pbm); // linha horizontal superior

	return pbmAux;
}

Imagem *polyLine(Pontos *pontos, Imagem *pbm, int marca)
{
	Imagem *pbmAux;
	Pontos *ptsLen;
	int i, k;

	pbmAux = pbm;
	ptsLen = pontos;

	for(i = 0 ; ptsLen->prox!=NULL ; i++, ptsLen=ptsLen->prox);
	for(k = 0 ; k < i-2 ; pontos = pontos->prox->prox, k+=2)
		pbm = line(pontos->p, pontos->prox->p, pontos->prox->prox->p, pontos->prox->prox->prox->p, marca, pbm);

	return pbmAux;
}

Imagem *merge(char *file, Imagem *pbm)
{
	Linhas *linhas = pbm->matriz;
	Colunas *colunas = linhas->proxC;
	int col = pbm->col , lin = pbm->lin;
	Imagem *imagemFile = load(file,imagemFile);

	Imagem *imagemAux = (Imagem*) malloc(sizeof(Imagem));
	Linhas *linhasAux = (Linhas*) malloc(sizeof(Linhas));
	Colunas *colunasAux = (Colunas*) malloc(sizeof(Colunas));
	imagemAux->matriz = linhasAux;
	linhasAux -> proxC = colunasAux;
	imagemAux->col = col;
	imagemAux->lin = lin;

	Imagem *pbmAux;
	pbmAux = imagemAux;


	Linhas *linhasFile = imagemFile->matriz;
	Colunas *colunasFile = linhasFile->proxC;
	int colFile = imagemFile->col, linFile = imagemFile->lin;

	Imagem *timagem = (Imagem*) malloc(sizeof(Imagem));
	Linhas *tlinhas = (Linhas*) malloc(sizeof(Linhas));
	Colunas *tcolunas = (Colunas*) malloc(sizeof(Colunas));
	timagem->matriz = tlinhas;
	tlinhas->proxC = tcolunas;

	if((colFile >= col) || (linFile >= lin))
	{
		tlinhas = linhas;
		linhas = linhasFile;
		linhasFile = tlinhas;
		imagemAux->col = colFile;
		imagemAux->lin = linFile;
		pbmAux = imagemAux;
	}

	for( ; (linhas->proxL!=NULL) || (linhasFile->proxL!=NULL) ; linhas=linhas->proxL  , linhasAux=linhasAux->proxL)
	{
		linhasAux->proxL = (Linhas*) malloc(sizeof(Linhas));
		
		linhasAux->proxC = (Colunas*) malloc(sizeof(Colunas));
		
		colunas = linhas->proxC;
		if(linhasFile->proxL!=NULL)
			colunasFile = linhasFile->proxC;
		
		colunasAux = linhasAux->proxC;
		
		for( ; (colunas->prox!=NULL) || (colunasFile->prox!=NULL) ; colunas=colunas->prox , colunasAux=colunasAux->prox)
		{
			colunasAux->prox = (Colunas*) malloc(sizeof(Colunas));
			
			if(colunasFile->prox!=NULL)
			{
				if(((colunasFile->c != 0) && (colunas->c != 0)) || ((colunasFile->c != 0) && (colunas->c == 0)))
				{
					colunasAux->c = colunasFile->c;
					colunasFile=colunasFile->prox;
				}
				else
				{
					colunasAux->c = colunas->c;
					colunasFile=colunasFile->prox;
				}
			}
			else
			{
				colunasAux->c=colunas->c;
			}
		}
		colunasAux->prox=NULL;
		if(linhasFile->proxL!=NULL)
			linhasFile=linhasFile->proxL;
	}
	linhasAux->proxL=NULL;
	return pbmAux;
}
