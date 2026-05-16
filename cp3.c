#include <stdio.h>
#include <string.h>

typedef struct {
    int numero;
    char nome[50];
    char senha[20];
    float saldo;
} Conta;

Conta contas[100];
int totalContas = 0;

void criarConta() {

    printf("\n=== CRIAR CONTA ===\n");

    contas[totalContas].numero = totalContas + 1;

    printf("Nome: ");
    scanf(" %[^\n]", contas[totalContas].nome);

    printf("Senha: ");
    scanf("%s", contas[totalContas].senha);

    contas[totalContas].saldo = 0;

    printf("\nConta criada com sucesso!\n");
    printf("Numero da conta: %d\n", contas[totalContas].numero);

    totalContas++;
}

int fazerLogin() {

    int numero;
    char senha[20];

    printf("\n=== LOGIN ===\n");

    printf("Numero da conta: ");
    scanf("%d", &numero);

    printf("Senha: ");
    scanf("%s", senha);

    for(int i = 0; i < totalContas; i++) {

        if(contas[i].numero == numero &&
           strcmp(contas[i].senha, senha) == 0) {

            return i;
        }
    }

    return -1;
}

void consultarSaldo(Conta *conta) {

    printf("\n=== SALDO ===\n");
    printf("Titular: %s\n", conta->nome);
    printf("Saldo atual: R$ %.2f\n", conta->saldo);
}

void depositar(Conta *conta) {

    float valor;

    printf("\nValor do deposito: ");
    scanf("%f", &valor);

    if(valor > 0) {

        conta->saldo += valor;

        printf("Deposito realizado com sucesso!\n");

    } else {

        printf("Valor invalido!\n");
    }
}

void sacar(Conta *conta) {

    float valor;

    printf("\nValor do saque: ");
    scanf("%f", &valor);

    if(valor <= 0) {

        printf("Valor invalido!\n");

    } else if(valor > conta->saldo) {

        printf("Saldo insuficiente!\n");

    } else {

        conta->saldo -= valor;

        printf("Saque realizado com sucesso!\n");
    }
}

void transferir(Conta *contaOrigem) {

    int numeroDestino;
    float valor;

    printf("\nConta destino: ");
    scanf("%d", &numeroDestino);

    printf("Valor da transferencia: ");
    scanf("%f", &valor);

    if(valor <= 0) {

        printf("Valor invalido!\n");
        return;
    }

    if(valor > contaOrigem->saldo) {

        printf("Saldo insuficiente!\n");
        return;
    }

    for(int i = 0; i < totalContas; i++) {

        if(contas[i].numero == numeroDestino) {

            contaOrigem->saldo -= valor;
            contas[i].saldo += valor;

            printf("Transferencia realizada!\n");
            return;
        }
    }

    printf("Conta nao encontrada!\n");
}

void menuConta(Conta *conta) {

    int opcao;

    do {

        printf("\n======= ATM =======\n");
        printf("1 - Consultar saldo\n");
        printf("2 - Depositar\n");
        printf("3 - Sacar\n");
        printf("4 - Transferir\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
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
                printf("Saindo da conta...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);
}

int main() {

    int opcao;
    int usuario;

    do {

        printf("\n======= BANCO =======\n");
        printf("1 - Criar conta\n");
        printf("2 - Login\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                criarConta();
                break;

            case 2:

                usuario = fazerLogin();

                if(usuario >= 0) {

                    printf("\nLogin realizado!\n");

                    menuConta(&contas[usuario]);

                } else {

                    printf("\nConta ou senha incorreta!\n");
                }

                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}