

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Pessoa
{
	char nome[50];
	int cpf;
	int numFicha;
	int prioritario;

} Pessoa;


typedef struct Nodo
{
	Pessoa* pessoa;
	Nodo* proximo;
	Nodo* anterior;

} Nodo;

typedef struct Fila
{
	Nodo* inicio;
	Nodo* fim;

} Fila;

Pessoa* CriaPessoa(char nome[], int cpf, int numFicha, int prioritario)
{
	Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));
	strcpy_s(pessoa->nome, nome);
	pessoa->cpf = cpf;
	pessoa->numFicha = numFicha;
	pessoa->prioritario = prioritario;

	return pessoa;
}



Fila* Inicializa()
{
	Fila* f = (Fila*)malloc(sizeof(Fila));
	f->inicio = NULL;
	f->fim = NULL;

	return f;
}

void Enfilera(Fila* f, Pessoa* p)
{
	Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
	
	if (f == NULL) {
		printf("Fila estava vazia!");
		f = Inicializa();
	}
	nodo->pessoa = p;

	nodo->proximo = f->fim;
	nodo->anterior = NULL;

	if (nodo->proximo != NULL) {
		nodo->proximo->anterior = nodo;
	}


	f->fim = nodo;

	if (f->inicio == NULL) {
		f->inicio = nodo;
	}

}

Pessoa*  Desenfilera(Fila* f)
{
	Pessoa* p;
	Nodo* nodo = f->inicio;
	f->inicio = nodo->anterior;
	p = nodo->pessoa;
	free(nodo);

	return p;
}

void ImprimePessoa(Pessoa* p)
{
	printf("Nome: %s\n ", p->nome);
	printf("Numero CPF: %d \n", p->cpf);
	printf("Numero da Ficha: %d \n", p->numFicha);
	printf("Prioritario? [S/N]:  %d \n\n", p->prioritario);


}

void ImprimeFila(Fila* f)
{
	Nodo* current = f->inicio;
	if (current == NULL)
	{
		printf("Fila vazia!\n");
		system("pause");

	}

	for (current = f->inicio; current != NULL; current = current->anterior)
	{
		ImprimePessoa(current->pessoa);
	}

}

int Menu()
{
	int resposta;

	system("cls");
	printf("Menu Atendimento: \n");
	printf("1 - Incluir pessoas:\n");
	printf("2 - Atendimento:\n");
	printf("3 - Encerrar o dia:\n");
	printf("4 - Mostrar filas: \n");
	printf("5 - Encerrar: \n");

	scanf("%d", &resposta);

	if (resposta < 1 || resposta >5)
	{
		printf("Opção invalida.");
		system("pause");
		resposta = Menu();

	}
	return resposta;
}

Pessoa* LePessoa()
{
	Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));
	printf("Digite o numero da ficha:\n");
	scanf("%d", &pessoa->numFicha);
	printf("Digite o nome:\n");
	scanf("%s", &pessoa->nome);
	printf("Digite CPF:\n");
	scanf("%d", &pessoa->cpf);
	printf("Prioritario?(1 para Sim, 0 para Não)");
	do
	{
		scanf("%d", &pessoa->prioritario);
	} while (pessoa->prioritario < 0 || pessoa->prioritario >1);




	return pessoa;
}
int ContaNodo(Fila* fila)
{
	Nodo* atual = NULL;
	int contador = 0;

	for (atual = fila->inicio; atual != NULL; atual = atual->anterior)
	{
		contador++;
	}
	return contador;
}

bool EhFilaVazia(Fila* fila)
{
	if (fila == NULL)
	{
		printf("Deu um erro aqui!");
		return false;
	}
	if (ContaNodo(fila) > 0)
	{
		return false;
	}
	return true;
}

void ClearFila(Fila* fila)
{
	if (EhFilaVazia(fila))
	{
		free(fila);
	}
	else
	{
		Nodo* atual = NULL;
		Nodo* proximo = NULL;
		atual = fila->inicio;
		while (atual != NULL)
		{
			proximo = atual->anterior;
			free(atual);
			atual = proximo;
		}
		free(fila);
	}
}



Pessoa* Atendimento(Fila* prioritaria, Fila* normal)
{
	Pessoa* pessoa = NULL;

	if (!EhFilaVazia(prioritaria))
	{
		pessoa = Desenfilera(prioritaria);
		printf("Atendendo Fila Prioritaria: ");
	}
	else if (!EhFilaVazia(normal))
	{
		pessoa = Desenfilera(normal);
		printf("Atendendo Fila Normal!");
	}
	else
	{
		printf("Filas Vazias!");
	}

	return pessoa;
}


void Run() {

	Fila* filaNormal = Inicializa();
	Fila* filaPrioritaria = Inicializa();
	Pessoa* pessoa;
	bool run = true;

	do
	{
		switch (Menu())
		{
		case 1:
			pessoa = LePessoa();
			if (pessoa->prioritario)
			{
				Enfilera(filaPrioritaria, pessoa);
			}
			else
			{
				Enfilera(filaNormal, pessoa);
			}
			system("pause");
			break;
		case 2:
			pessoa = Atendimento(filaPrioritaria, filaNormal);
			if (pessoa != NULL) {
				printf("\nNome do paciente atendido: %s\n  ", pessoa->nome);
			}
			system("pause");
			break;
		case 3:
			ClearFila(filaNormal);
			ClearFila(filaPrioritaria);
			system("pause");
			break;
		case 4:
			printf("\nFila Prioritaria: \n");
			ImprimeFila(filaPrioritaria);
			printf("\nFila Normal: \n");
			ImprimeFila(filaNormal);
			system("pause");
			break;
		case 5:
			printf("Encerrando Dia\n\n\n");
			run = false;
			system("pause");
			break;
		default:
			break;
		}
	} while (run);

}


int main()
{

	Run();

	
	return 1;
}
