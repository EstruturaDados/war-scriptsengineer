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
#include <string.h>
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

#define NUM_TERRITORIOS 5

/* Limpa o buffer de entrada (stdin) para evitar problemas entre leituras */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main(void) {
    /* Define locale para mensagens/acentuação em português (opcional) */
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Territorio mapa[NUM_TERRITORIOS];

    printf("Cadastro de %d territórios\n", NUM_TERRITORIOS);
    printf("OBS: use nomes e cores sem espaços (ex: Territorio1, Azul).\n\n");

    /* Entrada dos dados: solicita nome, cor e tropas para cada território */
    for (int i = 0; i < NUM_TERRITORIOS; ++i) {
        printf("Território %d\n", i + 1);

        printf("  Nome: ");
        /* scanf usado conforme instrução; limita tamanho para evitar overflow */
        if (scanf("%29s", mapa[i].nome) != 1) {
            printf("Erro ao ler o nome.\n");
            return 1;
        }

        printf("  Cor do exército: ");
        if (scanf("%9s", mapa[i].cor) != 1) {
            printf("Erro ao ler a cor.\n");
            return 1;
        }

        printf("  Número de tropas: ");
        if (scanf("%d", &mapa[i].tropas) != 1) {
            printf("Erro ao ler o número de tropas.\n");
            return 1;
        }

        /* Limpa qualquer caractere restante na linha antes da próxima iteração */
        limparBufferEntrada();

        printf("\n");
    }

    /* Exibição: mostra todos os territórios cadastrados em formato tabulado */
    printf("=== Territórios cadastrados ===\n");
    printf("%-3s %-29s %-9s %s\n", "ID", "NOME", "COR", "TROPAS");
    for (int i = 0; i < NUM_TERRITORIOS; ++i) {
        printf("%-3d %-29s %-9s %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
