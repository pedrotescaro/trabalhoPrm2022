#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <locale.h> 
#include<time.h>
struct nome{
	int codigo;
	char peca[20];
	char empresa[20];
	char processo[100];
	int qnde;
	float precoUni;
	float precoTot;
	
}pecas[12];
FILE *arq;
int indice;
int i=0;
char nome_arquivo[]="pecas.bin";
void limpaBufferTeclado()
{
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}
void insertionSort() 
{
	int k, j, aux;
	for (k = 1; k < i; k++) { 
		
		int j = k;
	
		while (j > 0 && pecas[j].codigo < pecas[j-1].codigo) {
			int aux = pecas[j].codigo;
			pecas[j].codigo= pecas[j - 1].codigo;
			pecas[j - 1].codigo = aux;
			j -= 1;
		}
	}	
}
void opgravar()
{
	int id;
	fseek(arq,0,SEEK_SET);
	if(i==0)
	{
		printf("\nN�o h� nada para gravar!\n\n");
	}
	else
	{
	 for(id=0; id<i; id+=1)
	  {
	    fwrite(&pecas[id], sizeof(pecas), 1, arq);
		}
	printf("\nInforma��es gravadas com sucesso!\n\n");
	}
	system("pause");	
}
void lercampos()
{
  if(i<13)
  {
    srand(time(NULL));
	pecas[i].codigo = 1+(rand() % 100);
	printf("Digite o nome da pe�a: ");
	gets(pecas[i].peca);
	printf("Digite o nome da empresa que solicitou a produ��o: ");
	gets(pecas[i].empresa);
	printf("Digite o(s) processo(s) de fabrica��o da pe�a: ");
	gets(pecas[i].processo);
	printf("Digite a quantidade de pe�as: ");
	scanf("%i%*c", &pecas[i].qnde);
	printf("Digite o pre�o unit�rio da pe�a: ");
	scanf("%f%*c",&pecas[i].precoUni);
    pecas[i].precoTot=pecas[i].precoUni*pecas[i].qnde;
    printf("\nC�digo da pe�a �: %i\n", pecas[i].codigo); 
	i=i+1;}
  else
  {
  	printf("Espa�o lotado!\n");
  } 
	
}
void exibecampos()
{
    int idx;
    if(i==0)
    {
    	printf("\n N�o h� pe�as cadastradas.\n");
    	system("pause");
	}
	else
	{
		insertionSort();
		for(idx=0;idx<i; idx+=1){
	    printf("C�digo da pe�a: %i\n", pecas[idx].codigo);
	    printf("Nome da pe�a: %s\n", pecas[idx].peca);
	    printf("Nome da empresa: %s\n", pecas[idx].empresa);
	    printf("Processo(s) de fabrica��o: %s\n", pecas[idx].processo);
	    printf("Quantidade: %i\n", pecas[idx].qnde);
	    printf("Pre�o unit�rio: %4.2f\n", pecas[idx].precoUni);
	    printf("Valor total: %4.2f\n", pecas[idx].precoTot);
	    printf("\n\n");}
	    system("pause");
	}
	}
void visualizar()
{
   int	tamanho;
   tamanho=ftell(arq);
   system("cls");
   fseek(arq, 0, SEEK_SET); 
   printf("%i", tamanho);
   printf("\n*********Pe�as Cadastradas********\n");
   if(tamanho==0)
   {
   	exibecampos();
   }
   else
	{
	   while (fread(&pecas, sizeof(pecas), 1, arq))
       {
       if(pecas[i].codigo!=9999)
       {
       	insertionSortInverso();
       	exibecampos ();
       	
       	printf("\n");
	   }
       }	
	}
}
void alterar()
{
   int code, encont=0;
   char resp;
   system("cls"); 
   printf("\n******Alterar Pe�as******\n");
   fseek(arq, 0, SEEK_SET); 
   printf("Digite o c�digo da pe�a:");
   scanf("%i%*c", &code);
   while(fread(&pecas, sizeof(pecas), 1, arq))
   {
   	 if(pecas[0].codigo==code)
   	 {
	   encont=1;
	   break;}
    }   
   if(encont==1)
   {
   	   printf( "\n\n\nAlterando os dados da pe�a\n\n");
       exibecampos();
       printf("\nDeseja realmente alterar? (S/N)");
       scanf("%c%*c",&resp);
	   if((resp=='s') || (resp == 'S'))
	   {
	       lercampos();
		   fseek(arq, sizeof(pecas), SEEK_CUR);
	       fwrite(&pecas, sizeof(pecas), 1, arq); 
	       printf("\nDados foram alterados\n");    
       }
	   else
	      printf("\nDados n�o foram alterados\n");      
   }
   else
     printf("\nC�digo n�o cadastrado\n"); 
   system("pause");  
}
void excluir()
{
   int code, encont=0;
   char resp;
   system("cls");
   printf("\n*********Excluir Pe�a********\n");
   fseek(arq, 0, SEEK_SET); 
   printf("Digite o c�digo da pe�a:");
   scanf("%i%*c", &code);
   while(fread(&pecas, sizeof(pecas), 1, arq))
   {
   	 if(pecas[indice].codigo==code)
   	 {
	   encont=1;
	   break;}
   }
   if(encont==1)
   {
   	   printf( "\n\n\nExcluindo os dados da pe�a\n\n");
       exibecampos();
       printf("\nDeseja realmente excluir ? (S/N)");
       scanf("%c%*c",&resp);
	   if((resp=='s') || (resp == 'S'))
	   {
	       pecas[indice].codigo=9999;
		   fseek(arq, sizeof(pecas), SEEK_CUR);
	       fwrite(&pecas, sizeof(pecas), 1, arq); 
	       printf("\nDados foram excluidos com sucesso\n");
       }
	   else
	      printf("\nDados n�o foram excluidos!!!\n");    
   }
   else
     printf("\nC�digo n�o cadastrado\n"); 
   system("pause");
}
void inclusao() 
{
    	lercampos();
        printf("\nPe�a cadastrada com sucesso!!\n");   
        system("pause");
}
void pesquisa()
{
   int code, encont=0;
   system("cls"); 
   printf("\n*********Pe�as Cadastradas********\n");
   fseek(arq, 0, SEEK_SET); 
   printf("Digite o c�digo da pe�a:");
   scanf("%i", &code);
      
   while(fread(&pecas, sizeof(pecas), 1, arq))
   {
   	for(indice=0;indice<=i;indice+=1){
   	 if(pecas[indice].codigo==code && pecas[indice].codigo!=9999)
   	 {
	   printf( "\n\n\nImprimindo os dados da pe�a\n\n");
       exibecampos();
       system("pause");
       encont=1;
     }}
   }
   if(encont!=1)
   {
   	  printf( "\n\n\nC�digo n�o encontrado\n\n");
      system("pause");
   }
   
}

void menu()
{    
  char op;
  do{
	system("cls");
	printf("Cadastro de Pe�as\n");
	printf("G - Gravar informa��es em um arquivo\n");
	printf("A - Incluir\n");
	printf("B - Visualizar todos os itens cadastrados\n");
	printf("C - Pesquisar um item individual\n");
	printf("D - Alterar\n");
	printf("E - Excluir\n");
	printf("F - Finalizar o Programa\n");
	printf("\n\nDigite a op��o: ");
	scanf("%c%*c",&op);
	switch(op)
	{
		case 'G' : 
		case 'g' :opgravar(); break;
		case 'A' : 
		case 'a' :inclusao(); break;
		case 'B' : 
		case 'b' :visualizar(); break;
		case 'C' : 
		case 'c' :pesquisa(); break;
		case 'D' : 
		case 'd' :alterar(); break;
		case 'E' : 
		case 'e' :excluir(); break;
		case 'F' :
		case 'f' :printf("\nFim do programa\n"); break;			
		default: printf("\nOp��o Inv�lida\n"); 
		         system ("pause");
		limpaBufferTeclado();
	}
  }while(op!='f'&&op!='F');
}
void exclusaoDefinitiva()
{
    FILE *arqAux;
	char nome_arquivo[]="pecas.bin";	
    if (( arq = fopen(nome_arquivo , "rb"))==NULL)
	{												
 	   printf("O arquivo %s n�o pode ser aberto... \n ",nome_arquivo);
       printf("O programa termina aqui... \n\n");
       system("pause");
       exit(0);
    }
    
    arqAux = fopen("ArquivoAuxiliar.bin", "wb");
    while (fread(&pecas, sizeof(pecas), 1, arq))
    {
   	for(indice=0;indice<=i;indice+=1){
       if(pecas[indice].codigo!=9999)
          fwrite(&pecas, sizeof(pecas), 1, arqAux); 
    }}
    fclose(arq);
    fclose(arqAux);
    system("del pecas.bin");
    system("ren ArquivoAuxiliar.bin pecas.bin");
}
int main ()
{
	setlocale(LC_ALL, "Portuguese"); 
    char nome_arquivo[]="pecas.bin";			
    if (( arq = fopen( nome_arquivo, "r+b"))==NULL)														
 	   if (( arq = fopen( nome_arquivo, "w+b")) == NULL)
       {
          printf("O arquivo %s n�o pode ser aberto... \n ",nome_arquivo);
          printf("O programa termina aqui... \n\n");
          system("pause");
          exit(0);
        }
    
    menu();
        
	printf("\nFechando o arquivo e saindo do programa ... ");
    fclose(arq); 
    exclusaoDefinitiva();
    printf ("\n");
	system ("pause");
	return 0;
}

