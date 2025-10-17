// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

/*
 * Estrutura Territorio:
 * Agrupa informações de um território: nome, cor do exército e número de tropas.
 * nome tem espaço para 29 caracteres mais o terminador '\0' (total 30).
 * cor tem espaço para 9 caracteres mais '\0' (total 10).
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Limpa o buffer de entrada (stdin) para evitar problemas entre leituras */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Aloca dinamicamente um vetor de Territorio com 'n' elementos */
Territorio* alocarMapa(int n) {
    Territorio* mapa = (Territorio*) calloc((size_t)n, sizeof(Territorio));
    if (!mapa) {
        fprintf(stderr, "Erro: falha na alocação de memória.\n");
    }
    return mapa;
}

/* Libera a memória alocada para o mapa */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

/* Exibe o mapa atual (apenas leitura - usa const) */
void exibirMapa(const Territorio* mapa, int n) {
    printf("\n=== Territórios cadastrados ===\n");
    printf("%-3s %-29s %-9s %s\n", "ID", "NOME", "COR", "TROPAS");
    for (int i = 0; i < n; ++i) {
        printf("%-3d %-29s %-9s %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
    printf("\n");
}

/* Cadastro dos territórios (modifica o mapa via ponteiro) */
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("Cadastro de %d territórios\n", n);
    printf("OBS: use nomes e cores sem espaços (ex: Territorio1, Azul).\n\n");

    for (int i = 0; i < n; ++i) {
        printf("Território %d\n", i + 1);

        printf("  Nome: ");
        if (scanf("%29s", mapa[i].nome) != 1) {
            printf("Erro ao ler o nome.\n");
            limparBufferEntrada();
            --i; // repetir este índice
            continue;
        }

        printf("  Cor do exército: ");
        if (scanf("%9s", mapa[i].cor) != 1) {
            printf("Erro ao ler a cor.\n");
            limparBufferEntrada();
            --i;
            continue;
        }

        printf("  Número de tropas: ");
        if (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 0) {
            printf("Erro ao ler o número de tropas (insira um inteiro >= 0).\n");
            limparBufferEntrada();
            --i;
            continue;
        }

        limparBufferEntrada();
        printf("\n");
    }
}

/* Simula um ataque entre dois territórios usando rand() (valores 1..6) */
/* Regras:
   - atacante deve ter pelo menos 2 tropas para iniciar ataque.
   - se atacante vencer (roll maior), o defensor troca de cor para a do atacante
     e recebe metade (inteiro) das tropas do atacante (transferidas).
   - as tropas transferidas são subtraídas do atacante.
   - se atacante perder, perde 1 tropa (sem ficar abaixo de 0).
*/
void atacar(Territorio* atacante, Territorio* defensor) {
    if (!atacante || !defensor) return;

    if (atacante == defensor) {
        printf("Erro: não é possível atacar o mesmo território.\n");
        return;
    }

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é permitido atacar um território da mesma cor '%s'.\n", atacante->cor);
        return;
    }

    if (atacante->tropas < 2) {
        printf("Erro: o território atacante precisa ter pelo menos 2 tropas (tem %d).\n", atacante->tropas);
        return;
    }

    int atk_roll = rand() % 6 + 1;
    int def_roll = rand() % 6 + 1;

    printf("Rolagem: %s (atacante) -> %d | %s (defensor) -> %d\n",
           atacante->nome, atk_roll, defensor->nome, def_roll);

    if (atk_roll > def_roll) {
        /* atacante vence: reduz 1 tropa do defensor apenas */
        defensor->tropas -= 1;
        if (defensor->tropas < 0) defensor->tropas = 0;

        printf("Resultado: %s venceu. %s perdeu 1 tropa (agora tem %d tropas).\n",
               atacante->nome, defensor->nome, defensor->tropas);
    } else {
        /* atacante perde: perde uma tropa */
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("Resultado: %s não teve sucesso e perdeu 1 tropa (agora tem %d tropas).\n",
               atacante->nome, atacante->tropas);
    }
}

/* Mostra menu principal e retorna escolha do usuário */
int exibirMenuPrincipal(void) {
    printf("Ações disponíveis:\n");
    printf("  1) Exibir territórios\n");
    printf("  2) Atacar\n");
    printf("  3) Sair\n");
    printf("Escolha: ");
    int opc;
    if (scanf("%d", &opc) != 1) {
        limparBufferEntrada();
        return -1;
    }
    limparBufferEntrada();
    return opc;
}

/* --- Função principal (orquestra o fluxo) --- */
int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand((unsigned int) time(NULL));

    int num;
    printf("Informe o número total de territórios: ");
    if (scanf("%d", &num) != 1 || num <= 0) {
        printf("Número inválido. Encerrando.\n");
        return 1;
    }
    limparBufferEntrada();

    Territorio* mapa = alocarMapa(num);
    if (!mapa) return 1;

    cadastrarTerritorios(mapa, num);
    exibirMapa(mapa, num);

    /* Loop principal de interação para executar ataques até o usuário sair */
    while (1) {
        int opc = exibirMenuPrincipal();
        if (opc == 1) {
            exibirMapa(mapa, num);
        } else if (opc == 2) {
            int ida, idd;
            exibirMapa(mapa, num);
            printf("Selecione o ID do território atacante: ");
            if (scanf("%d", &ida) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); continue; }
            printf("Selecione o ID do território defensor: ");
            if (scanf("%d", &idd) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); continue; }
            limparBufferEntrada();

            if (ida < 1 || ida > num || idd < 1 || idd > num) {
                printf("IDs inválidos. Use valores entre 1 e %d.\n", num);
                continue;
            }

            Territorio* atacante = &mapa[ida - 1];
            Territorio* defensor  = &mapa[idd - 1];

            atacar(atacante, defensor);

            exibirMapa(mapa, num);
        } else if (opc == 3) {
            printf("Saindo. Liberando memória e encerrando.\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    liberarMemoria(mapa);
    return 0;
}
