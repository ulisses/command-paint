typedef struct colunas
{
	int c;
	struct colunas *prox;
}Colunas;

typedef struct linhas
{
	Colunas *proxC;
	struct linhas *proxL;
}Linhas;

typedef struct imagem
{
	int col;
	int lin;
	Linhas *matriz;
}Imagem;

typedef struct pontos
{
	int p;
	struct pontos *prox;
}Pontos;

Imagem *load(char *nome, Imagem *ret_pointer);
void printDesenho(Imagem *pbm);
void save(char *nf, Imagem *pbm);

Imagem *point(int x, int y, int marca, Imagem *pbm);
Imagem * line(float x1, float y1, float x2, float y2, int marca, Imagem *pbm);
Imagem *rect(int x1, int y1, int x2, int y2, int marca, Imagem *pbm);
Imagem *polyLine(Pontos *pontos, Imagem *pbm, int marca);

Imagem *merge(char *file, Imagem *pbm);
