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
		printf("\nNão há nada para gravar!\n\n");
	}
	else
	{
	 for(id=0; id<i; id+=1)
	  {
	    fwrite(&pecas[id], sizeof(pecas), 1, arq);
		}
	printf("\nInformações gravadas com sucesso!\n\n");
	}
	system("pause");	
}
void lercampos()
{
  if(i<13)
  {
    srand(time(NULL));
	pecas[i].codigo = 1+(rand() % 100);
	printf("Digite o nome da peça: ");
	gets(pecas[i].peca);
	printf("Digite o nome da empresa que solicitou a produção: ");
	gets(pecas[i].empresa);
	printf("Digite o(s) processo(s) de fabricação da peça: ");
	gets(pecas[i].processo);
	printf("Digite a quantidade de peças: ");
	scanf("%i%*c", &pecas[i].qnde);
	printf("Digite o preço unitário da peça: ");
	scanf("%f%*c",&pecas[i].precoUni);
    pecas[i].precoTot=pecas[i].precoUni*pecas[i].qnde;
    printf("\nCódigo da peça é: %i\n", pecas[i].codigo); 
	i=i+1;}
  else
  {
  	printf("Espaço lotado!\n");
  } 
	
}
void exibecampos()
{
    int idx;
    if(i==0)
    {
    	printf("\n Não há peças cadastradas.\n");
    	system("pause");
	}
	else
	{
		insertionSort();
		for(idx=0;idx<i; idx+=1){
	    printf("Código da peça: %i\n", pecas[idx].codigo);
	    printf("Nome da peça: %s\n", pecas[idx].peca);
	    printf("Nome da empresa: %s\n", pecas[idx].empresa);
	    printf("Processo(s) de fabricação: %s\n", pecas[idx].processo);
	    printf("Quantidade: %i\n", pecas[idx].qnde);
	    printf("Preço unitário: %4.2f\n", pecas[idx].precoUni);
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
   printf("\n*********Peças Cadastradas********\n");
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
   printf("\n******Alterar Peças******\n");
   fseek(arq, 0, SEEK_SET); 
   printf("Digite o código da peça:");
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
   	   printf( "\n\n\nAlterando os dados da peça\n\n");
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
	      printf("\nDados não foram alterados\n");      
   }
   else
     printf("\nCódigo não cadastrado\n"); 
   system("pause");  
}
void excluir()
{
   int code, encont=0;
   char resp;
   system("cls");
   printf("\n*********Excluir Peça********\n");
   fseek(arq, 0, SEEK_SET); 
   printf("Digite o código da peça:");
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
   	   printf( "\n\n\nExcluindo os dados da peça\n\n");
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
	      printf("\nDados não foram excluidos!!!\n");    
   }
   else
     printf("\nCódigo não cadastrado\n"); 
   system("pause");
}
void inclusao() 
{
    	lercampos();
        printf("\nPeça cadastrada com sucesso!!\n");   
        system("pause");
}
void pesquisa()
{
   int code, encont=0;
   system("cls"); 
   printf("\n*********Peças Cadastradas********\n");
   fseek(arq, 0, SEEK_SET); 
   printf("Digite o código da peça:");
   scanf("%i", &code);
      
   while(fread(&pecas, sizeof(pecas), 1, arq))
   {
   	for(indice=0;indice<=i;indice+=1){
   	 if(pecas[indice].codigo==code && pecas[indice].codigo!=9999)
   	 {
	   printf( "\n\n\nImprimindo os dados da peça\n\n");
       exibecampos();
       system("pause");
       encont=1;
     }}
   }
   if(encont!=1)
   {
   	  printf( "\n\n\nCódigo não encontrado\n\n");
      system("pause");
   }
   
}

void menu()
{    
  char op;
  do{
	system("cls");
	printf("Cadastro de Peças\n");
	printf("G - Gravar informações em um arquivo\n");
	printf("A - Incluir\n");
	printf("B - Visualizar todos os itens cadastrados\n");
	printf("C - Pesquisar um item individual\n");
	printf("D - Alterar\n");
	printf("E - Excluir\n");
	printf("F - Finalizar o Programa\n");
	printf("\n\nDigite a opção: ");
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
		default: printf("\nOpção Inválida\n"); 
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
 	   printf("O arquivo %s não pode ser aberto... \n ",nome_arquivo);
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
          printf("O arquivo %s não pode ser aberto... \n ",nome_arquivo);
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

