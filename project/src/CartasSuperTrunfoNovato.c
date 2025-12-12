// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das cartas
// Objetivo: No nível novato você deve criar as cartas representando as cidades 
// utilizando <scanf> para entrada de dados e <printf> para exibir informações.

#include <stdio.h>
#include <ctype.h>

// Constantes ——————————————————————————————————————————————————————————————————
// É assumido que trata-se de apenas um pais com 8 estados (A a H) e 04 cidades,
// onde o cadastro de cartas aborda apenas os dados de dito país sem especificar
// qual é o nome do país. Possíveis melhorias incluem permitir múltiplos países.
#define NUM_ESTADOS 8           // 8 estados de A a H conforme especificação ———
#define CIDADES_POR_ESTADO 4    // 4 cidades por estado (01, 02, 03, 04) ———————
#define TOTAL_CARTAS (NUM_ESTADOS * CIDADES_POR_ESTADO)  // Total: 32 cartas ———

// Protótipos/declaração das funções ————[corpo de cada função após o main()]———
void  lerNomeCidade(char nomeCidade[]); // Lê o nome da cidade —————————————————
int   lerPopulacao(); // Garante que a população seja um número positivo ———————
float lerArea(); // Garante que a área seja um número positivo maior que zero ——
float lerPIB(); // Garante que o PIB seja um número positivo ———————————————————
int   lerPontosTuristicos(); // Garante que o número de pontos seja positivo ———
void  limparBuffer(); // Limpa o buffer do teclado em caso de entrada inválida —

// Função principal ————————————————————————————————————————————————————————————
int main() {
    // Área para definição das variáveis =======================================
    // Variáveis para armazenar os dados das cartas
    char  codigos[TOTAL_CARTAS][4]; // Códigos automáticos, ex: A01, B01, etc. —
    char  nomesCidades[TOTAL_CARTAS][50]; // Nomes das cidades de cada carta ———
    int   populacoes[TOTAL_CARTAS]; // População de cada cidade ————————————————
    float areas[TOTAL_CARTAS]; // Área em km² de cada cidade ———————————————————
    float pibs[TOTAL_CARTAS]; // PIB em bilhões de cada cidade —————————————————
    int   pontosTuristicos[TOTAL_CARTAS]; // Número de pontos turísticos ———————

    // Área para entrada de dados ============================================== 
    printf("=== BEM-VINDO AO SUPER TRUNFO - PAÍSES ===\n");
    printf("Vamos cadastrar %d cartas.\n", TOTAL_CARTAS);
    printf("O total de cartas está organizado em %d estados!\n", NUM_ESTADOS);
    printf("Cada estado tem %d cidades com código único.\n\n", CIDADES_POR_ESTADO);

    // Variável para controlar o índice geral dos arrays ———————————————————————
    int indiceGeral = 0;

    // Loop externo: percorre todos os estados de A a H ————————————————————————
    for (int estado = 0; estado < NUM_ESTADOS; estado++) {
        // Calcula a letra do estado atual (A=0, B=1, C=2, ..., H=7) ———————————
        char letraEstado = 'A' + estado;
        
        printf("===========================================================\n");
        printf("                 CADASTRO DO ESTADO %c\n", letraEstado);
        printf("===========================================================\n");

        // Loop interno: percorre as 4 cidades de cada estado ——————————————————
        for (int cidade = 1; cidade <= CIDADES_POR_ESTADO; cidade++) {
            printf("\n--- Cadastrando carta %c%02d ---\n", letraEstado, cidade);
            
            // Gera automaticamente o código da carta no formato correto ———————
            // <sprintf> escreve na string, <printf> escreve na tela ———————————
            sprintf(codigos[indiceGeral], "%c%02d", letraEstado, cidade);
            
            printf("Codigo da carta: %s\n", codigos[indiceGeral]);

            // Lê todos os dados desta carta ———————————————————————————————————
            lerNomeCidade(nomesCidades[indiceGeral]);
            populacoes[indiceGeral] = lerPopulacao();
            areas[indiceGeral] = lerArea();
            pibs[indiceGeral] = lerPIB();
            pontosTuristicos[indiceGeral] = lerPontosTuristicos();

            printf("Carta %s cadastrada com sucesso!\n", codigos[indiceGeral]);
            
            // Incrementa o índice para a próxima posição nos arrays ———————————
            indiceGeral++;
        }
    }

    // Área para exibição dos dados das cidades ================================
    printf("\n\n===========================================================\n");
    printf("                      CARTAS CADASTRADAS\n");
    printf("===========================================================\n");

    // Reinicia o índice para percorrer os arrays na exibição ——————————————————
    indiceGeral = 0;
    
    // Loop para exibir todas as cartas organizadas por estado —————————————————
    for (int estado = 0; estado < NUM_ESTADOS; estado++) {
        char letraEstado = 'A' + estado;
        
        printf("\n========== ESTADO %c ==========\n", letraEstado);
        
        // Exibe as 4 cidades do estado atual ——————————————————————————————————
        for (int cidade = 0; cidade < CIDADES_POR_ESTADO; cidade++) {
            printf("\n===== CARTA %s =====\n", codigos[indiceGeral]);
            printf("Estado: %c\n", letraEstado);
            printf("Codigo: %s\n", codigos[indiceGeral]);
            printf("Nome da Cidade: %s\n", nomesCidades[indiceGeral]);
            printf("Populacao: %d habitantes\n", populacoes[indiceGeral]);
            printf("Area: %.2f km²\n", areas[indiceGeral]);
            printf("PIB: %.2f bilhoes de reais\n", pibs[indiceGeral]);
            printf("Pontos Turisticos: %d\n", pontosTuristicos[indiceGeral]);
            
            // Avança para a próxima carta —————————————————————————————————————
            indiceGeral++;
        }
    }

    printf("\n\nTodas as %d cartas foram cadastradas!\n", TOTAL_CARTAS);
    printf("Estados: A, B, C, D, E, F, G, H (8 estados)\n");
    printf("Cidades por estado: 01, 02, 03, 04 (4 cidades cada)\n");
    printf("Obrigado por usar o Super Trunfo!\n");
    return 0;
}

// Função para ler o nome da cidade ————————————————————————————————————————————
void lerNomeCidade(char nomeCidade[]) {
    // Lê o nome da cidade incluindo espaços em branco —————————————————————————
    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", nomeCidade);           // %[^\n] lê até encontrar Enter ———
}

// Função para ler e validar a população ———————————————————————————————————————
int lerPopulacao() {
    int populacao;
    
    do {
        printf("Digite a populacao: ");
        
        // scanf retorna 1 se conseguiu ler um inteiro, 0 se não conseguiu —————
        if (scanf("%d", &populacao) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            populacao = -1;                 // Força o loop a continuar ————————
        }
        else if (populacao < 0) {
            printf("ERRO: A populacao deve ser um numero positivo!\n");
        }
    } while (populacao < 0);               // Repete até entrada válida ————————
    
    return populacao;
}

// Função para ler e validar a área ————————————————————————————————————————————
float lerArea() {
    float area;
    
    do {
        printf("Digite a area (km²): ");
        
        // Verifica se conseguiu ler um número float válido ————————————————————
        if (scanf("%f", &area) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            area = -1;                      // Força o loop a continuar ————————
        }
        else if (area <= 0) {
            printf("ERRO: A area deve ser maior que zero!\n");
        }
    } while (area <= 0);                   // Repete até entrada válida ————————
    
    return area;
}

// Função para ler e validar o PIB —————————————————————————————————————————————
float lerPIB() {
    float pib;
    
    do {
        printf("Digite o PIB (em bilhoes): ");
        
        // Verifica se conseguiu ler um número float válido ————————————————————
        if (scanf("%f", &pib) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            pib = -1;                       // Força o loop a continuar ————————
        }
        else if (pib < 0) {
            printf("ERRO: O PIB deve ser um numero positivo!\n");
        }
    } while (pib < 0);                     // Repete até entrada válida ————————
    
    return pib;
}

// Função para ler e validar pontos turísticos ————————————————————————————————
int lerPontosTuristicos() {
    int pontos;
    
    do {
        printf("Digite o numero de pontos turisticos: ");
        
        // Verifica se conseguiu ler um inteiro válido —————————————————————————
        if (scanf("%d", &pontos) != 1) {
            printf("ERRO: Digite apenas numeros inteiros!\n");
            limparBuffer();
            pontos = -1;                    // Força o loop a continuar ————————
        }
        else if (pontos < 0) {
            printf("ERRO: O numero de pontos turisticos deve ser positivo!\n");
        }
    } while (pontos < 0);                  // Repete até entrada válida ————————
    
    return pontos;
}

// Função para limpar o buffer do teclado ——————————————————————————————————————
void limparBuffer() {
    int c;
    // Lê e descarta todos os caracteres até encontrar '\n' ou fim do arquivo ——
    // Isso evita que caracteres inválidos "sobrem" no buffer e causem problemas
    while ((c = getchar()) != '\n' && c != EOF);
}