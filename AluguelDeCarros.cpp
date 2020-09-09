	// LOCADORA DE CARROS
	// NOME DO ALUNO: LUCAS MARCOS GOES MARINHO
	// LOGIN PRINCIPAL: gerente  SENHA: 123
	
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<locale.h>

typedef struct Usuario {
	char login[15],senha[12];	
}Usuario;

typedef struct Funcionario {
	char nome[20],tel[12];
	int matricula;
	Usuario user;
}Funcionario;

typedef struct Carro {
	char modelo[12],placa[8],cor[12],marca[12];
	float valDiaria;
	bool alugado;
}Carro;

typedef struct Endereco {
	char rua[20],bairro[20];
	int casa;
}Endereco;

typedef struct Cliente {
	char nome[20],tel[12],cnh[10];
	Endereco end;
}Cliente;

typedef struct Contrato{
	Carro carro;
	Cliente cli;
	char nomeFunc[20];
	int quantDias,matFunc;
	float valorTotal;
}Contrato;

FILE *PFUN;
FILE *PCAR;
FILE *PCLI;
FILE *PCON;

void login();
void menuGerente();
void menuFuncionario(int matricula);
void menuDeGerencia(int tipo);
void cadastrarFuncionarios();
void cadastrarVeiculos();
void cadastrarClientes();
void pesquisarFuncionarios();
void pesquisarVeiculos();
void pesquisarClientes();
void alterarFuncionario(int matricula);
void alterarVeiculo(char placa[]);
void alterarCliente(char cnh[]);
void excluirFuncionario(int matricula);
void excluirVeiculo(char placa[]);
void excluirCliente(char cnh[]);
int obterQuantidadeDeCadastros(int tipo);
void iniciarAluguel(int matricula);
void finalizarAluguel(int matricula, Cliente cli, Carro carro);
void realizarDevolucao();
void menuRelatorios();
void relatorioCarrosNoPatio();
void relatorioCarrosAlugados();
void relatorioContratos();
main() {
	setlocale(LC_ALL,"Portuguese");
	login();
}

void login() {
	char loginpesq[10],senhapesq[10];
	bool mensagem;
	int op=1;
	
	do {
		system("cls");
		system("title LOCADORA DE CARROS");
		system("color 3f");
		printf("LOGIN:");
		fflush(stdin);
		gets(loginpesq);
		printf("\n\nSENHA:");
		fflush(stdin);
		gets(senhapesq);
		if (strcmp(loginpesq,"gerente")==0 && strcmp(senhapesq,"123")==0) {
			mensagem=true;
			menuGerente();
		} else if (!mensagem == true) {
			Funcionario func;
			PFUN = fopen("ArquivoFuncionario.txt","r");
			rewind(PFUN);	
			while(!feof(PFUN)) {
				fread(&func, sizeof(Funcionario), 1, PFUN);
				if (!feof(PFUN)) {
					if(strcmp(loginpesq,func.user.login)==0 && strcmp(senhapesq,func.user.senha)==0) {
						mensagem=true;
						menuFuncionario(func.matricula);
					}
				}
			}
		} else {
			mensagem=false;
		}
		if (mensagem==false) {
			printf("\n\nDESEJA CONTINUAR NO SISTEMA?");
			printf("\nQUALQUER NÚMERO - SIM");
			printf("\n0 - NÃO");
			printf("\nOpção: ");
			scanf("%i",&op);
		}
	}while(op!=0);
}		

void menuGerente() {
	int op;
	
	do {
		system("title MENU GERENTE");
		system("cls");
		printf("1 - GERENCIAR FUNCIONÁRIOS");
		printf("\n2 - GERENCIAR CARROS");
		printf("\n3 - RELATÓRIOS");
		printf("\n0 - SAIR");
		printf("\nOpção: ");
		scanf("%i",&op);
		switch(op) {
			case 1:
				menuDeGerencia(1);
				break;
			case 2:
				menuDeGerencia(2);
				break;
			case 3:
				menuRelatorios();
				break;
			case 0:
				op=0;
				break;
			default:
				system("cls");
				printf("OPÇÃO INVÁLIDA!");
				Sleep(2000);
		}
	}while(op!=0);
}

void menuFuncionario(int matricula) {
	int op;
	
	do {
		system("title MENU FUNCIONÁRIO");
		system("cls");
		printf("1 - GERENCIAR CLIENTES");
		printf("\n2 - REALIZAR ALUGUEL");
		printf("\n3 - REALIZAR DEVOLUÇÃO");
		printf("\n0 - SAIR");
		printf("\nOpção: ");
		scanf("%i",&op);
		switch(op) {
			case 1:
				menuDeGerencia(3);
				break;
			case 2:
				iniciarAluguel(matricula);
				break;
			case 3:
				realizarDevolucao();
				break;
			case 0:
				op=0;
				break;
			default:
				system("cls");
				printf("OPÇÃO INVÁLIDA!");
				Sleep(2000);
		}
	}while(op!=0);
}

void menuDeGerencia(int tipo) {
	int op;
	
	do {
		system("cls");
		if (tipo==1) {
			system("title GERÊNCIA DE FUNCIONÁRIOS");
			printf("1 - CADASTRAR NOVOS FUNCIONÁRIOS");
			printf("\n2 - PESQUISAR FUNCIONÁRIOS");
		} else if (tipo==2) {
			system("title GERÊNCIA DE CARROS");
			printf("1 - CADASTRAR NOVOS VEÍCULOS");
			printf("\n2 - PESQUISAR VEÍCULOS");
		} else {
			system("title GERÊNCIA DE CLIENTES");
			printf("1 - CADASTRAR NOVOS CLIENTES");
			printf("\n2 - PESQUISAR CLIENTES");
		}
		printf("\n0 - VOLTAR");
		printf("\nOpção: ");
		scanf("%i",&op);
		if (tipo==1 && op==1) {
			cadastrarFuncionarios();
		} else if (tipo==1 && op==2) {
			pesquisarFuncionarios();			
		} else if (tipo==2 && op==1) {
			cadastrarVeiculos();
		} else if (tipo==2 && op==2) {
			pesquisarVeiculos();
		} else if (tipo==3 && op==1) {
			cadastrarClientes();
		} else if (tipo==3 && op==2) {
			pesquisarClientes();
		} else if (op==0) {
			op=0;
		} else {
			system("cls");
			printf("OPÇÃO INVÁLIDA!");
			Sleep(2000);
		}
	}while(op!=0);
}

void cadastrarFuncionarios() {
	int op,quant_Total,quant_Preenchida=0;
	Funcionario *pontFunc;
	
	PFUN = fopen("ArquivoFuncionario.txt","ab+");
	
	system("cls");
	printf("DIGITE A QUANTIDADE DE FUNCIONÁRIOS QUE DESEJA CADASTRAR: ");
	scanf("%i",&quant_Total);
	if (quant_Total>0) {
		pontFunc = (Funcionario*)malloc(sizeof(Funcionario)*quant_Total);	
		do {
			system("cls");
			printf("NOME: ");
			fflush(stdin);
			gets(pontFunc[quant_Preenchida].nome);
			printf("\nTELEFONE: ");
			fflush(stdin);
			gets(pontFunc[quant_Preenchida].tel);
			printf("\nMATRICULA: ");
			scanf("%i",&pontFunc[quant_Preenchida].matricula);
			printf("\n\n---- DADOS DE LOGIN ---");
			printf("\nLOGIN: ");
			fflush(stdin);
			gets(pontFunc[quant_Preenchida].user.login);
			printf("\nSENHA: ");
			fflush(stdin);
			gets(pontFunc[quant_Preenchida].user.senha);
			quant_Preenchida++;
			if (quant_Preenchida<quant_Total) {
				printf("\nDESEJA CONTINUAR CADASTRANDO?");
				printf("\n1 - SIM\n0 - NÃO\nOPÇÃO: ");
				scanf("%i",&op);
			} else {
				system("cls");
				printf("QUANTIDADE MÁXIMA SOLICITADA FOI ATINGIDA!!");
				printf("\n\nSALVANDO OS CADASTROS E SAINDO!");
				Sleep(2000);
			}
		}while(quant_Preenchida<quant_Total && op!=0);
		fwrite(pontFunc, sizeof(Funcionario), quant_Preenchida, PFUN);
	} 
	fclose(PFUN);
}

void cadastrarVeiculos() {
	int op,quant_Total,quant_Preenchida=0;
	Carro *pontCar;
	
	PCAR = fopen("ArquivoCarros.txt","ab+");
	
	system("cls");
	printf("DIGITE A QUANTIDADE DE CARROS QUE DESEJA CADASTRAR: ");
	scanf("%i",&quant_Total);
	if (quant_Total>0) {
		pontCar = (Carro*)malloc(sizeof(Carro)*quant_Total);
		do {
			system("cls");
			printf("MODELO: ");
			fflush(stdin);
			gets(pontCar[quant_Preenchida].modelo);
			printf("\nMARCA: ");
			fflush(stdin);
			gets(pontCar[quant_Preenchida].marca);
			printf("\nPLACA: ");
			fflush(stdin);
			gets(pontCar[quant_Preenchida].placa);
			printf("\nCOR: ");
			fflush(stdin);
			gets(pontCar[quant_Preenchida].cor);
			printf("\nVALOR DA DIÁRIA: ");
			scanf("%f",&pontCar[quant_Preenchida].valDiaria);
			pontCar[quant_Preenchida].alugado=false;
			quant_Preenchida++;
			if (quant_Preenchida<quant_Total) {
				printf("\nDESEJA CONTINUAR CADASTRANDO?");
				printf("\n1 - SIM\n0 - NÃO\nOPÇÃO: ");
				scanf("%i",&op);
			} else {
				system("cls");
				printf("QUANTIDADE MÁXIMA SOLICITADA FOI ATINGIDA!!");
				printf("\n\nSALVANDO OS CADASTROS E SAINDO!");
				Sleep(2000);
			}
		}while(quant_Preenchida<quant_Total && op!=0);
		fwrite(pontCar, sizeof(Carro), quant_Preenchida, PCAR);
	}
	fclose(PCAR);
}

void cadastrarClientes() {
	int op,quant_Total,quant_Preenchida=0;
	Cliente *pontCli;
	
	PCLI = fopen("ArquivoClientes.txt","ab+");
	
	system("cls");
	printf("DIGITE A QUANTIDADE DE CLIENTES QUE DESEJA CADASTRAR: ");
	scanf("%i",&quant_Total);
	if (quant_Total>0) {
		pontCli = (Cliente*)malloc(sizeof(Cliente)*quant_Total);
		do {
			system("cls");
			printf("NOME: ");
			fflush(stdin);
			gets(pontCli[quant_Preenchida].nome);
			printf("\nTELEFONE: ");
			fflush(stdin);
			gets(pontCli[quant_Preenchida].tel);
			printf("\nCNH: ");
			fflush(stdin);
			gets(pontCli[quant_Preenchida].cnh);
			printf("\n\n---DADOS DE ENDEREÇO---");
			printf("\nRUA: ");
			fflush(stdin);
			gets(pontCli[quant_Preenchida].end.rua);
			printf("\nCASA: ");
			scanf("%i",&pontCli[quant_Preenchida].end.casa);
			printf("\nBAIRRO: ");
			fflush(stdin);
			gets(pontCli[quant_Preenchida].end.bairro);
			quant_Preenchida++;
			if (quant_Preenchida<quant_Total) {
				printf("\nDESEJA CONTINUAR CADASTRANDO?");
				printf("\n1 - SIM\n0 - NÃO\nOPÇÃO: ");
				scanf("%i",&op);
			} else {
				system("cls");
				printf("QUANTIDADE MÁXIMA SOLICITADA FOI ATINGIDA!!");
				printf("\n\nSALVANDO OS CADASTROS E SAINDO!");
				Sleep(2000);
			}
		}while(quant_Preenchida<quant_Total && op!=0);
		fwrite(pontCli, sizeof(Cliente), quant_Preenchida, PCLI);
	}
	fclose(PCLI);
}

void pesquisarFuncionarios() {
	Funcionario func;
	int matpesq,op;
	bool achou=false;
	
	PFUN = fopen("ArquivoFuncionario.txt","r");
	system("cls");
	printf("DIGITE A MATRÍCULA DE UM FUNCIONÁRIO CADASTRADO: ");
	scanf("%i",&matpesq);
	rewind(PFUN);
	while(!feof(PFUN)) {
		fread(&func, sizeof(Funcionario), 1, PFUN);
		if (!feof(PFUN)) {
			if(matpesq == func.matricula) {
				system("cls");
				achou=true;
				printf("\t\tFUNCIONÁRIO ENCONTRADO!");
				printf("\n\nNOME: %s  MATRÍCULA: %i\nTELEFONE: %s",func.nome,func.matricula,func.tel);
				printf("\n___DADOS DE USUÁRIO___\nLOGIN: %s  SENHA: %s",func.user.login,func.user.senha);
				printf("\n\n1 - ALTERAR DADOS\n2 - EXCLUIR CADASTRO\n0 - SAIR\nOPÇÃO: ");
				scanf("%i",&op);
				if (op == 1) {
					fclose(PFUN);
					system("cls");
					alterarFuncionario(func.matricula);
					break;
				} else if (op == 2) {
					fclose(PFUN);
					system("cls");
					excluirFuncionario(func.matricula);
					break;
				}
			}
		}
	}
	fclose(PFUN);
	if (achou == false) {
		system("cls");
		printf("NÃO HÁ FUNCIONÁRIOS COM ESSA MATRÍCULA");
		Sleep(2000);
	}
}

void pesquisarVeiculos() {
	Carro carro;
	char placapesq[8];
	bool achou=false;
	int op;
	
	PCAR = fopen("ArquivoCarros.txt","r");
	system("cls");
	printf("DIGITE A PLACA DE UM CARRO CADASTRADO:");
	fflush(stdin);
	gets(placapesq);
	rewind(PCAR);
	while(!feof(PCAR)) {
		fread(&carro, sizeof(Carro), 1, PCAR);
		if (!feof(PCAR)) {
			if(strcmp(placapesq,carro.placa)==0) {
				system("cls");
				achou=true;
				printf("\t\tCARRO ENCONTRADO!");
				printf("\n\nMODELO: %s  MARCA: %s",carro.modelo,carro.marca);
				printf("\nPLACA: %s\nCOR: %s",carro.placa,carro.cor);
				printf("\nVALOR DA DIÁRIA: R$  %.2f ",carro.valDiaria);
				if (carro.alugado == false) {
					printf("\nSTATUS: CARRO NO PÁTIO.");
				} else {
					printf("\nSTATUS: CARRO ALUGADO.");
				}
				printf("\n\n1 - ALTERAR DADOS\n2 - EXCLUIR CADASTRO\n0 - SAIR\nOPÇÃO: ");
				scanf("%i",&op);
				if (op == 1) {
					fclose(PCAR);
					system("cls");
					alterarVeiculo(carro.placa);
					break;
				} else if (op == 2) {
					fclose(PCAR);
					system("cls");
					excluirVeiculo(carro.placa);
					break;
				}
			}
		}	
	
	}
	fclose(PCAR);
	if (achou == false) {
		system("cls");
		printf("NÃO HÁ CARROS COM ESSA PLACA");
		Sleep(2000);
	}
}

void pesquisarClientes() {
	Cliente cliente;
	char cnhpesq[10];
	bool achou=false;
	int op;
	
	PCLI = fopen("ArquivoClientes.txt","r");
	system("cls");
	printf("DIGITE A CNH DE UM CLIENTE CADASTRADO: ");
	fflush(stdin);
	gets(cnhpesq);
	rewind(PCLI);
	while(!feof(PCLI)) {
		fread(&cliente, sizeof(Cliente), 1, PCLI);
		if (!feof(PCLI)) {
			if(strcmp(cnhpesq,cliente.cnh)==0) {
				system("cls");
				achou=true;
				printf("\t\tCLIENTE ENCONTRADO!");
				printf("\n\nNOME: %s  CNH: %s",cliente.nome,cliente.cnh);
				printf("\nTELEFONE: %s",cliente.tel);
				printf("\n___DADOS DE ENDEREÇO___\nRUA: %s  CASA: %i  BAIRRO: %s",cliente.end.rua,cliente.end.casa,cliente.end.bairro);
				printf("\n\n1 - ALTERAR DADOS\n2 - EXCLUIR CADASTRO\n0 - SAIR\nOPÇÃO: ");
				scanf("%i",&op);
				if (op == 1) {
					fclose(PCLI);
					system("cls");
					alterarCliente(cliente.cnh);
					break;
				} else if (op == 2) {
					fclose(PCLI);
					system("cls");
					excluirCliente(cliente.cnh);
					break;
				}
			}
		}	
	}
	fclose(PCLI);
	if (achou == false) {
		system("cls");
		printf("NÃO HÁ CLIENTES COM ESSA CNH");
		Sleep(2000);
	}	
}

void alterarFuncionario(int matricula) {
	Funcionario func;
	int cont=-1,op;
	
	PFUN = fopen("ArquivoFuncionario.txt","rb+");
	rewind(PFUN);
	while(!feof(PFUN)) {
		fread(&func, sizeof(Funcionario), 1, PFUN);
		if (!feof(PFUN)) {
			cont++;
			if(matricula == func.matricula) {
				printf("ESCOLHA O NÚMERO DO DADO A SER ALTERADO OU ( 0 ) PARA SAIR");
				printf("\n\n|| 1 - NOME: %s\n|| 2 - MATRÍCULA: %i\n|| 3 - TELEFONE: %s",func.nome,func.matricula,func.tel);
				printf("\n|| 4 - ALTERAR DADOS DE USUÁRIO (LOGIN: %s  SENHA: %s)",func.user.login,func.user.senha);				
				printf("\n|| 0 - SAIR");
				printf("\n\nOPÇÃO: ");
				scanf("%i",&op);
				if (op>0 && op<5) {
					switch(op) {
						case 1:
							printf("\nNOVO NOME: ");
							fflush(stdin);
							gets(func.nome);
							break;
						case 2:
							printf("\nNOVA MATRÍCULA: ");
							scanf("%i",&func.matricula);
							break;
						case 3:
							printf("\nNOVO TELEFONE: ");
							fflush(stdin);
							gets(func.tel);
							break;
						case 4:
							printf("\nNOVOS DADOS DE USUÁRIO");
							printf("\nLOGIN: ");
							fflush(stdin);
							gets(func.user.login);
							printf("\nSENHA: ");
							fflush(stdin);
							gets(func.user.senha);
							break;					
					}
				fseek(PFUN,cont*sizeof(Funcionario),SEEK_SET);
				fwrite(&func,sizeof(Funcionario),1,PFUN);
				printf("\nDADOS ALTERADOS COM SUCESSO!");
				Sleep(2000);
				break;
				} else if (op == 0){
					system("cls");
					printf("SAINDO");
					Sleep(1000);
				} else {
					system("cls");
					printf("OPÇÃO INVÁLIDA!!");
					Sleep(1000);
				}
			}	
		}
	}
	fclose(PFUN);
}

void alterarVeiculo(char placa[]) {
	Carro carro;
	int cont=-1,op;
	
	PCAR = fopen("ArquivoCarros.txt","rb+");
	rewind(PCAR);
	while(!feof(PCAR)) {
		fread(&carro, sizeof(Carro), 1, PCAR);
		if (!feof(PCAR)) {
			cont++;
			if(strcmp(placa,carro.placa)==0) {
				printf("ESCOLHA O NÚMERO DO DADO A SER ALTERADO OU ( 0 ) PARA SAIR");
				printf("\n\n|| 1 - MODELO: %s\n|| 2 - MARCA: %s\n|| 3 - PLACA: %s",carro.modelo,carro.marca,carro.placa);
				printf("\n|| 4 - COR: %s\n|| 5 - VALOR DA DIÁRIA: R$ %.2f",carro.cor,carro.valDiaria);
				printf("\n|| 0 - SAIR");
				printf("\n\nOPÇÃO: ");
				scanf("%i",&op);
				if (op>0 && op<6) {
					switch(op) {
						case 1:
							printf("\nNOVO MODELO: ");
							fflush(stdin);
							gets(carro.modelo);
							break;
						case 2:
							printf("\nNOVA MARCA: ");
							scanf("%i",&carro.marca);
							break;
						case 3:
							printf("\nNOVO PLACA: ");
							fflush(stdin);
							gets(carro.placa);
							break;
						case 4:
							printf("\nNOVA COR: ");
							fflush(stdin);
							gets(carro.cor);
							break;
						case 5:
							printf("\nNOVO VALOR DE DIÁRIA: ");
							scanf("%f",&carro.valDiaria);
							break;				
					}
					fseek(PCAR,cont*sizeof(Carro),SEEK_SET);
					fwrite(&carro,sizeof(Carro),1,PCAR);
					printf("\nDADOS ALTERADOS COM SUCESSO!");
					Sleep(2000);
					break;					
				} else if (op == 0){
					system("cls");
					printf("SAINDO");
					Sleep(1000);
				} else {
					system("cls");
					printf("OPÇÃO INVÁLIDA!!");
					Sleep(1000);
				}
			}
		}
	}
}

void alterarCliente(char cnh[]) {
	Cliente cliente;
	int cont=-1,op;
	
	PCLI = fopen("ArquivoClientes.txt","rb+");
	rewind(PCLI);
	while(!feof(PCLI)) {
		fread(&cliente, sizeof(Cliente), 1, PCLI);
		if (!feof(PCLI)) {
			cont++;
			if(strcmp(cnh,cliente.cnh)==0) {
				printf("ESCOLHA O NÚMERO DO DADO A SER ALTERADO OU ( 0 ) PARA SAIR");
				printf("\n\n|| 1 - NOME: %s\n|| 2 - TELEFONE: %s\n|| 3 - CNH: %s",cliente.nome,cliente.tel,cliente.cnh);
				printf("\n|| 4 - ALTERAR DADOS DE ENDEREÇO (RUA: %s CASA: %i BAIRRO: %s)",cliente.end.rua,cliente.end.casa,cliente.end.bairro);				
				printf("\n|| 0 - SAIR");
				printf("\n\nOPÇÃO: ");
				scanf("%i",&op);
				if (op>0 && op<5) {
					switch(op) {
						case 1:
							printf("\nNOVO NOME: ");
							fflush(stdin);
							gets(cliente.nome);
							break;
						case 2:
							printf("\nNOVO TELEFONE: ");
							fflush(stdin);
							gets(cliente.tel);
							break;
						case 3:
							printf("\nNOVA CNH: ");
							fflush(stdin);
							gets(cliente.cnh);
							break;
						case 4:
							printf("\nNOVOS DADOS DE ENDEREÇO");
							printf("\nRUA: ");
							fflush(stdin);
							gets(cliente.end.rua);
							printf("\nCASA: ");
							scanf("%i",&cliente.end.casa);
							printf("\nBAIRRO: ");
							fflush(stdin);
							gets(cliente.end.bairro);
							break;					
					}
					fseek(PCLI,cont*sizeof(Cliente),SEEK_SET);
					fwrite(&cliente,sizeof(Cliente),1,PCLI);
					printf("\nDADOS ALTERADOS COM SUCESSO!");
					Sleep(2000);
					break;					
				} else if (op == 0){
					system("cls");
					printf("SAINDO");
					Sleep(1000);
				} else {
					system("cls");
					printf("OPÇÃO INVÁLIDA!!");
					Sleep(1000);
				}
			}
		}
	}
}

void excluirFuncionario(int matricula) {
	Funcionario func,*pontFunc,*auxFunc;
	int tamanho,i=0,j=0;
	
	tamanho=obterQuantidadeDeCadastros(1);
	
	pontFunc = (Funcionario*)malloc(sizeof(Funcionario)*tamanho);
	auxFunc = (Funcionario*)malloc(sizeof(Funcionario)*tamanho);	
	
	PFUN = fopen("ArquivoFuncionario.txt","rb");
	rewind(PFUN);
	while(!feof(PFUN)){
 		fread(&func,sizeof(Funcionario),1,PFUN);
  		if(!feof(PFUN)){
   			strcpy(pontFunc[i].nome,func.nome);
			pontFunc[i].matricula = func.matricula;
			strcpy(pontFunc[i].tel,func.tel); 
			strcpy(pontFunc[i].user.login,func.user.login);
			strcpy(pontFunc[i].user.senha,func.user.senha);
			i++;
  		}
	}
	fclose(PFUN);
	
	i=-1;
	PFUN = fopen("ArquivoFuncionario.txt","rb");
	rewind(PFUN);	
 	while(!feof(PFUN)){
 		fread(&func,sizeof(Funcionario),1,PFUN);
  		if(!feof(PFUN)){
 			i++;
   			if(pontFunc[i].matricula == matricula){
    			printf("DADOS EXCLUIDOS COM SUCESSO!!");
    			Sleep(2000);    
   			}else{
   				strcpy(auxFunc[j].nome, pontFunc[i].nome);
   				auxFunc[j].matricula = pontFunc[i].matricula;
				strcpy(auxFunc[j].tel, pontFunc[i].tel);
				strcpy(auxFunc[j].user.login, auxFunc[i].user.login);
				strcpy(auxFunc[j].user.senha, auxFunc[i].user.senha);
				j++;
  			}
  		}
 	}
 	fclose(PFUN);
 	PFUN = fopen("ArquivoFuncionario.txt","wb");     
 	fwrite(auxFunc,sizeof(Funcionario),j,PFUN);
 	fclose(PFUN); 	
}

void excluirVeiculo(char placa[]) {
	Carro carro,*pontCar,*auxCar;
	int tamanho,i=0,j=0;
	
	tamanho=obterQuantidadeDeCadastros(2);
	
	pontCar = (Carro*)malloc(sizeof(Carro)*tamanho);
	auxCar = (Carro*)malloc(sizeof(Carro)*tamanho);	
	
	PCAR = fopen("ArquivoCarros.txt","rb");
	rewind(PCAR);
	while(!feof(PCAR)){
 		fread(&carro,sizeof(Carro),1,PCAR);
  		if(!feof(PCAR)){
   			strcpy(pontCar[i].modelo,carro.modelo);
			strcpy(pontCar[i].marca,carro.marca); 
			strcpy(pontCar[i].cor,carro.cor);
			strcpy(pontCar[i].placa,carro.placa);
			pontCar[i].valDiaria = carro.valDiaria;
			pontCar[i].alugado = carro.alugado;
			i++;
  		}
	}
	fclose(PCAR);
	
	i=-1;
	PCAR = fopen("ArquivoCarros.txt","rb");
	rewind(PCAR);	
 	while(!feof(PCAR)){
 		fread(&carro,sizeof(Carro),1,PCAR);
  		if(!feof(PCAR)){
 			i++;
   			if(strcmp(pontCar[i].placa, placa)==0){
    			printf("DADOS EXCLUIDOS COM SUCESSO!!");
    			Sleep(2000);    
   			}else{
   				strcpy(auxCar[j].modelo,pontCar[i].modelo);
				strcpy(auxCar[j].marca,pontCar[i].marca); 
				strcpy(auxCar[j].cor,pontCar[i].cor);
				strcpy(auxCar[j].placa,pontCar[i].placa);
				auxCar[j].valDiaria = pontCar[i].valDiaria;
				auxCar[i].alugado = pontCar[i].alugado;
				j++;
  			}
  		}
 	}
 	fclose(PCAR);
 	PCAR = fopen("ArquivoCarros.txt","wb");     
 	fwrite(auxCar,sizeof(Carro),j,PCAR);
 	fclose(PCAR); 
}

void excluirCliente(char cnh[]) {
	Cliente cliente,*pontCli,*auxCli;
	int tamanho,i=0,j=0;
	
	tamanho=obterQuantidadeDeCadastros(3);
	
	pontCli = (Cliente*)malloc(sizeof(Cliente)*tamanho);
	auxCli = (Cliente*)malloc(sizeof(Cliente)*tamanho);	
	
	PCLI = fopen("ArquivoClientes.txt","rb");
	rewind(PCLI);
	while(!feof(PCLI)){
 		fread(&cliente,sizeof(Cliente),1,PCLI);
  		if(!feof(PCLI)){
   			strcpy(pontCli[i].nome,cliente.nome);
			strcpy(pontCli[i].tel,cliente.tel); 
			strcpy(pontCli[i].cnh,cliente.cnh);
			strcpy(pontCli[i].end.rua,cliente.end.rua);
			strcpy(pontCli[i].end.bairro,cliente.end.bairro);
			pontCli[i].end.casa = cliente.end.casa;
			i++;
  		}
	}
	fclose(PCLI);
	
		i=-1;
	PCLI = fopen("ArquivoClientes.txt","rb");
	rewind(PCLI);	
 	while(!feof(PCLI)){
 		fread(&cliente,sizeof(Cliente),1,PCLI);
  		if(!feof(PCLI)){
 			i++;
   			if(strcmp(pontCli[i].cnh ,cnh)==0){
    			printf("DADOS EXCLUIDOS COM SUCESSO!!");
    			Sleep(2000);    
   			}else{
   				strcpy(auxCli[j].nome,pontCli[i].nome);
				strcpy(auxCli[j].tel,pontCli[i].tel); 
				strcpy(auxCli[j].cnh,pontCli[i].cnh);
				strcpy(auxCli[j].end.rua,pontCli[i].end.rua);
				strcpy(auxCli[j].end.bairro,pontCli[i].end.bairro);
				auxCli[j].end.casa = pontCli[i].end.casa;
				j++;
  			}
  		}
 	}
	fclose(PCLI);
 	PCLI = fopen("ArquivoClientes.txt","wb");     
 	fwrite(auxCli,sizeof(Cliente),j,PCLI);
 	fclose(PCLI);  	
}

int obterQuantidadeDeCadastros(int tipo) {
	Funcionario func;
	Carro carro;
	Cliente cli;
	int cont=0;     

	if (tipo == 1) {
		PFUN = fopen("ArquivoFuncionario.txt","rb");
		rewind(PFUN);     
		while(!feof(PFUN)){
 			fread(&func,sizeof(Funcionario),1,PFUN);
  			if(!feof(PFUN)){
   				cont++; 
  			}
		} 
	fclose(PFUN); 	  
	} else if (tipo == 2) {
		PCAR = fopen("ArquivoCarros.txt","rb");
		rewind(PCAR);
		while(!feof(PCAR)) {
			fread(&carro,sizeof(Carro),1,PCAR);
			if(!feof(PCAR)) {
				cont++;
			}
		}
	fclose(PCAR);
	} else {
		PCLI = fopen("ArquivoClientes.txt","rb");
		rewind(PCLI);
		while(!feof(PCLI)) {
			fread(&cli,sizeof(Cliente),1,PCLI);
			if(!feof(PCLI)) {
				cont++;
			}
		}
	fclose(PCLI);
	}
	return cont;
}

void iniciarAluguel(int matricula) {
	Cliente cliente;
	Carro carro;
	char cnhpesq[10],placaescolhida[8];
	bool achoucnh=false,achouplaca=false;
	int op;
	
	PCLI = fopen("ArquivoClientes.txt","r");
	system("cls");
	printf("O CLIENTE DEVE ESTAR CADASTRADO PARA REALIZAR O ALUGUEL!\nDIGITE A CNH: ");
	fflush(stdin);
	gets(cnhpesq);
	rewind(PCLI);
	while(!feof(PCLI)) {
		fread(&cliente, sizeof(Cliente), 1, PCLI);
		if (!feof(PCLI)) {
			if(strcmp(cnhpesq,cliente.cnh)==0) {
				achoucnh=true;
				system("cls");
				printf("CLIENTE ENCONTRADO!!");
				printf("\n\nPROSSEGUINDO COM A OPERAÇÃO...");
				Sleep(2000);
				
				PCAR = fopen("ArquivoCarros.txt","r");
				system("cls");
				printf("\t\tCARROS DISPONÍVEIS\n\n");
				rewind(PCAR);
				while(!feof(PCAR)) {
					fread(&carro,sizeof(Carro),1,PCAR);
					if (!feof(PCAR)) {
						if (carro.alugado == false) {
							printf("\nMODELO: %s  MARCA: %s",carro.modelo,carro.marca);
							printf("\nPLACA: %s\nCOR: %s",carro.placa,carro.cor);
							printf("\nVALOR DA DIÁRIA: R$ %.2f",carro.valDiaria);
							printf("\n_____________________________________\n");
						}
					}
				}
				printf("DIGITE A PLACA DO CARRO QUE SERÁ ALUGADO: ");
				fflush(stdin);
				gets(placaescolhida);
				rewind(PCAR);
				while(!feof(PCAR)) {
					fread(&carro,sizeof(Carro),1,PCAR);
					if (!feof(PCAR)) {
						if (strcmp(placaescolhida, carro.placa)==0 && carro.alugado == false) {
							achouplaca=true;
							system("cls");
							printf("\t\tCARRO A SER ALUGADO\n");						
							printf("\n\nMODELO: %s  MARCA: %s",carro.modelo,carro.marca);
							printf("\nPLACA: %s\nCOR: %s",carro.placa,carro.cor);
							printf("\nVALOR DA DIÁRIA: R$ %.2f",carro.valDiaria);
							printf("\n\n1 - CONFIRMAR\n0 - CANCELAR\nOPÇÃO: ");
							scanf("%i",&op);
							if (op == 1) {
								system("cls");
								fclose(PCAR);
								finalizarAluguel(matricula,cliente,carro);
								break;
							} else if (op == 0) {
								system("cls");
								printf("CANCELANDO OPERAÇÃO!");
								Sleep(2000);
							} else {
								printf("cls");
								printf("OPÇÃO INVÁLIDA!!");
								Sleep(2000);
							}
						}
					}
				}
				if( op == 1) {
					break;
				} else {
					fclose(PCAR);
				}
				if (achouplaca == false) {
					system("cls");
					printf("PLACA ESCOLHIDA NÃO IDENTIFICADA!");
					Sleep(2000);
				}				
			}	
		}
	}
	fclose(PCLI);
	if (achoucnh == false) {
		system("cls");
		printf("CLIENTE NÃO ENCONTRADO!");	
		Sleep(2000);
	}
}

void finalizarAluguel(int matricula, Cliente cli, Carro carro) {
	Contrato contrato;
	Funcionario func;
	Carro carroAlt;
	int op,cont=-1;
	
	PCON = fopen("ArquivoContratos.txt","ab+");
	PFUN = fopen("ArquivoFuncionario.txt","rb");
	
	rewind(PFUN);
	while(!feof(PFUN)) {
		fread(&func, sizeof(Funcionario), 1, PFUN);
		if (!feof(PFUN)) {
			if(matricula == func.matricula) {
				contrato.matFunc = func.matricula;
				strcpy(contrato.nomeFunc, func.nome);
			}
		}
	}
	fclose(PFUN);
	strcpy(contrato.cli.nome, cli.nome);
	strcpy(contrato.cli.tel, cli.tel);
	strcpy(contrato.cli.cnh, cli.cnh);
	strcpy(contrato.cli.end.rua, cli.end.rua);
	strcpy(contrato.cli.end.bairro, cli.end.bairro);
	contrato.cli.end.casa = cli.end.casa;
	strcpy(contrato.carro.modelo, carro.modelo);
	strcpy(contrato.carro.marca, carro.marca);
	strcpy(contrato.carro.placa, carro.placa);
	strcpy(contrato.carro.cor, carro.cor);
	contrato.carro.valDiaria = carro.valDiaria;
	printf("DIGITE A QUANTIDADE DE DIAS DO ALUGUEL: ");
	scanf("%i",&contrato.quantDias);
	contrato.valorTotal = contrato.quantDias*contrato.carro.valDiaria;
	system("cls");
	printf("\t\tCONTRATO GERADO\n\n");
	printf("______________DADOS DO CARRO____________________\n\nMODELO: %s  MARCA: %s  PLACA: %s",contrato.carro.modelo,contrato.carro.marca,contrato.carro.placa);
	printf("\nCOR: %s  VALOR DÁ DIÁRIA: R$ %.2f",contrato.carro.cor,contrato.carro.valDiaria);
	printf("\n______________DADOS DO CLIENTE________________\n\nNOME: %s  TELEFONE: %s\nNÚMERO DA CNH: %s",contrato.cli.nome,contrato.cli.tel,contrato.cli.cnh);
	printf("\nENDEREÇO || RUA: %s CASA: %i  BAIRRO: %s",contrato.cli.end.rua,contrato.cli.end.casa,contrato.cli.end.bairro);
	printf("\n______________DADOS DO FUNCIONÁRIO__________________\n\nMATRÍCULA: %i  NOME: %s",contrato.matFunc,contrato.nomeFunc);
	printf("\n_______________DADOS DO ALUGUEL_________________\n\nQUANTIDADE DE DIAS: %i  VALOR TOTAL: R$ %.2f",contrato.quantDias,contrato.valorTotal);
	printf("\n\n1 - CONFIRMAR ALUGUEL\n0 - CANCELAR\nOPÇÃO: ");
	scanf("%i",&op);
	if (op == 1) {
		fwrite(&contrato,sizeof(Contrato),1,PCON);
		
		PCAR = fopen("ArquivoCarros.txt","rb+");
		rewind(PCAR);
		while(!feof(PCAR)) {
			fread(&carroAlt, sizeof(Carro), 1, PCAR);
			if (!feof(PCAR)) {
				cont++;
				if(strcmp(contrato.carro.placa,carroAlt.placa)==0) {
					carroAlt.alugado=true;
					fseek(PCAR,cont*sizeof(Carro),SEEK_SET);
					fwrite(&carroAlt,sizeof(Carro),1,PCAR);
					break;
				}
			}
		}
		fclose(PCAR);
		system("cls");
		printf("\nALUGUEL REALIZADO!!");
		Sleep(1000);
	} else if (op == 0){
		system("cls");
		printf("CANCELANDO OPERAÇÃO!");
		Sleep(2000);
	} else {
		printf("cls");
		printf("OPÇÃO INVÁLIDA!!");
		Sleep(2000);
	}
	fclose(PCON);
}

void realizarDevolucao() {
	Carro carro;
	char placapesq[8];
	bool achou=false;
	int op,cont=-1;
	
	PCAR = fopen("ArquivoCarros.txt","rb+");
	
	system("cls");
	printf("DIGITE A PLACA DO CARRO A SER DEVOLVIDO: ");
	fflush(stdin);
	gets(placapesq);
	rewind(PCAR);
	while(!feof(PCAR)) {
		fread(&carro,sizeof(Carro),1,PCAR);
		if (!feof(PCAR)) {
			cont++;
			if (strcmp(placapesq, carro.placa)==0 && carro.alugado == true) {
				achou=true;
				system("cls");
				printf("\t\tCARRO A SER DEVOLVIDO\n");						
				printf("\n\nMODELO: %s  MARCA: %s",carro.modelo,carro.marca);
				printf("\nPLACA: %s\nCOR: %s",carro.placa,carro.cor);
				printf("\nVALOR DA DIÁRIA: R$ %.2f",carro.valDiaria);
				printf("\n\n1 - CONFIRMAR\n0 - CANCELAR\nOPÇÃO: ");
				scanf("%i",&op);
				if (op == 1) {
					carro.alugado=false;
					fseek(PCAR,cont*sizeof(Carro),SEEK_SET);
					fwrite(&carro,sizeof(Carro),1,PCAR);
					system("cls");
					printf("\nDEVOLUÇÃO REALIZADA!!");
					Sleep(1000);
					break;
				} else if (op == 0) {
					system("cls");
					printf("CANCELANDO OPERAÇÃO!");
					Sleep(2000);
				} else {
					printf("cls");
					printf("OPÇÃO INVÁLIDA!!");
					Sleep(2000);
				}
			}
		}
	}
	fclose(PCAR);
	if (achou == false) {
		system("cls");
		printf("NÃO HÁ CARROS ALUGADOS COM ESSA PLACA");
		Sleep(2000);
	}			
}

void menuRelatorios() {
	int op;
	
	do {
		system("cls");
		system("title RELATÓRIOS DISPONÍVEIS");
		printf("1 - CARROS NO PATIO");
		printf("\n2 - CARROS ALUGADOS");
		printf("\n3 - CONTRATOS GERADOS");
		printf("\n0 - SAIR");
		printf("\nOPÇÃO: ");
		scanf("%i",&op);
		switch(op) {
			case 1:
				relatorioCarrosNoPatio();
				break;
			case 2:
				relatorioCarrosAlugados();
				break;
			case 3:
				relatorioContratos();
				break;
			case 0:
				op=0;
				break;
			default:
				system("cls");
				printf("OPÇÃO INVÁLIDA!!");
				Sleep(2000);
		}
	}while(op!=0);
}

void relatorioCarrosNoPatio() {
	Carro carro;
	
	PCAR = fopen("ArquivoCarros.txt","rb");
	rewind(PCAR);
	system("cls");
	while(!feof(PCAR)) {
		fread(&carro,sizeof(Carro),1,PCAR);
		if (!feof(PCAR)) {						
			if (carro.alugado == false) {
				printf("\n\nMODELO: %s  MARCA: %s",carro.modelo,carro.marca);
				printf("\nPLACA: %s\nCOR: %s",carro.placa,carro.cor);
				printf("\nVALOR DA DIÁRIA: R$ %.2f",carro.valDiaria);	
				printf("\n______________________________________\n");
			}
		}
	}
	system("pause");
	fclose(PCAR);
}

void relatorioCarrosAlugados() {
	Carro carro;
	
	PCAR = fopen("ArquivoCarros.txt","rb");
	rewind(PCAR);
	system("cls");
	while(!feof(PCAR)) {
		fread(&carro,sizeof(Carro),1,PCAR);
		if (!feof(PCAR)) {						
			if (carro.alugado == true) {
				printf("\n\nMODELO: %s  MARCA: %s",carro.modelo,carro.marca);
				printf("\nPLACA: %s\nCOR: %s",carro.placa,carro.cor);
				printf("\nVALOR DA DIÁRIA: R$ %.2f",carro.valDiaria);	
				printf("\n______________________________________\n");
			}
		}
	}
	system("pause");
	fclose(PCAR);
}

void relatorioContratos() {
	Contrato contrato;
	
	PCON = fopen("ArquivoContratos.txt","rb");
	rewind(PCON);
	system("cls");
	while(!feof(PCON)) {
		fread(&contrato,sizeof(Contrato),1,PCON);
		if (!feof(PCON)) {
			printf("______________DADOS DO CARRO____________________\n\nMODELO: %s  MARCA: %s  PLACA: %s",contrato.carro.modelo,contrato.carro.marca,contrato.carro.placa);
			printf("\nCOR: %s  VALOR DÁ DIÁRIA: R$ %.2f",contrato.carro.cor,contrato.carro.valDiaria);
			printf("\n______________DADOS DO CLIENTE________________\n\nNOME: %s  TELEFONE: %s\nNÚMERO DA CNH: %s",contrato.cli.nome,contrato.cli.tel,contrato.cli.cnh);
			printf("\nENDEREÇO || RUA: %s CASA: %i  BAIRRO: %s",contrato.cli.end.rua,contrato.cli.end.casa,contrato.cli.end.bairro);
			printf("\n______________DADOS DO FUNCIONÁRIO__________________\n\nMATRÍCULA: %i  NOME: %s",contrato.matFunc,contrato.nomeFunc);
			printf("\n_______________DADOS DO ALUGUEL_________________\n\nQUANTIDADE DE DIAS: %i  VALOR TOTAL: R$ %.2f",contrato.quantDias,contrato.valorTotal);
			printf("\n\n____________________________________________________________\n\n");
		}
	}
	system("pause");
	fclose(PCON);
}
