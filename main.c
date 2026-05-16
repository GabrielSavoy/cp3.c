/* ===========================
   ARQUIVO: main.c
   SISTEMA ATM EM C
   =========================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numeroConta;
    char nome[100];
    char senha[20];
    float saldo;
} Conta;

Conta contas[MAX_CONTAS];
int totalContas = 0;

/* ===========================
   FUNÇÕES
   =========================== */

void limparTela() {
    system("cls || clear");
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void criarConta() {
    limparTela();

    Conta novaConta;

    printf("=== CRIAR CONTA ===\n");

    novaConta.numeroConta = totalContas + 1;

    printf("Nome: ");
    scanf(" %[^\n]", novaConta.nome);

    printf("Senha: ");
    scanf("%s", novaConta.senha);

    novaConta.saldo = 0;

    contas[totalContas] = novaConta;
    totalContas++;

    printf("\nConta criada com sucesso!\n");
    printf("Numero da conta: %d\n", novaConta.numeroConta);

    pausar();
}

int login() {
    limparTela();

    int numero;
    char senha[20];

    printf("=== LOGIN ===\n");

    printf("Numero da conta: ");
    scanf("%d", &numero);

    printf("Senha: ");
    scanf("%s", senha);

    for(int i = 0; i < totalContas; i++) {
        if(contas[i].numeroConta == numero &&
           strcmp(contas[i].senha, senha) == 0) {

            printf("\nLogin realizado com sucesso!\n");
            pausar();

            return i;
        }
    }

    printf("\nConta ou senha incorreta!\n");
    pausar();

    return -1;
}

void consultarSaldo(Conta *conta) {
    limparTela();

    printf("=== CONSULTAR SALDO ===\n");
    printf("Titular: %s\n", conta->nome);
    printf("Saldo atual: R$ %.2f\n", conta->saldo);

    pausar();
}

void depositar(Conta *conta) {
    limparTela();

    float valor;

    printf("=== DEPOSITO ===\n");

    printf("Valor do deposito: ");
    scanf("%f", &valor);

    if(valor <= 0) {
        printf("Valor invalido!\n");
    } else {
        conta->saldo += valor;
        printf("Deposito realizado com sucesso!\n");
    }

    pausar();
}

void sacar(Conta *conta) {
    limparTela();

    float valor;

    printf("=== SAQUE ===\n");

    printf("Valor do saque: ");
    scanf("%f", &valor);

    if(valor <= 0) {
        printf("Valor invalido!\n");
    }
    else if(valor > conta->saldo) {
        printf("Saldo insuficiente!\n");
    }
    else {
        conta->saldo -= valor;
        printf("Saque realizado com sucesso!\n");
    }

    pausar();
}

void transferir(Conta *contaOrigem) {
    limparTela();

    int contaDestino;
    float valor;

    printf("=== TRANSFERENCIA ===\n");

    printf("Conta destino: ");
    scanf("%d", &contaDestino);

    printf("Valor: ");
    scanf("%f", &valor);

    if(valor <= 0) {
        printf("Valor invalido!\n");
        pausar();
        return;
    }

    if(valor > contaOrigem->saldo) {
        printf("Saldo insuficiente!\n");
        pausar();
        return;
    }

    for(int i = 0; i < totalContas; i++) {

        if(contas[i].numeroConta == contaDestino) {

            contaOrigem->saldo -= valor;
            contas[i].saldo += valor;

            printf("Transferencia realizada com sucesso!\n");

            pausar();
            return;
        }
    }

    printf("Conta destino nao encontrada!\n");

    pausar();
}

void menuConta(Conta *conta) {

    int opcao;

    do {
        limparTela();

        printf("=== ATM BANCARIO ===\n");
        printf("Usuario: %s\n", conta->nome);

        printf("\n1 - Consultar saldo");
        printf("\n2 - Depositar");
        printf("\n3 - Sacar");
        printf("\n4 - Transferir");
        printf("\n0 - Sair");

        printf("\n\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                consultarSaldo(conta);
                break;

            case 2:
                depositar(conta);
                break;

            case 3:
                sacar(conta);
                break;

            case 4:
                transferir(conta);
                break;

            case 0:
                printf("\nSaindo da conta...\n");
                pausar();
                break;

            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }

    } while(opcao != 0);
}

void menuPrincipal() {

    int opcao;
    int indiceConta;

    do {
        limparTela();

        printf("=================================\n");
        printf("      SISTEMA ATM EM C\n");
        printf("=================================\n");

        printf("\n1 - Criar conta");
        printf("\n2 - Login");
        printf("\n0 - Sair");

        printf("\n\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                criarConta();
                break;

            case 2:

                indiceConta = login();

                if(indiceConta != -1) {
                    menuConta(&contas[indiceConta]);
                }

                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }

    } while(opcao != 0);
}

/* ===========================
   MAIN
   =========================== */

int main() {

    menuPrincipal();

    return 0;
}