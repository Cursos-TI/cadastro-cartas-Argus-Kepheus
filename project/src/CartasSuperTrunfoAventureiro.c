// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das cartas
// Objetivo: No nível novato você deve criar as cartas representando as cidades 
// utilizando <scanf> para entrada de dados e <printf> para exibir informações.

#include <stdio.h>
#include <ctype.h>

// Constantes ——————————————————————————————————————————————————————————————————
#define NUM_CARTAS 2  // Número de cartas que serão cadastradas (editável) —————

// Protótipos/declaração das funções ————[corpo de cada função após o main()]———
char  lerEstado(); // Garante que o usuário digite apenas letras de A a H ——————
void  lerCodigo(char codigo[]); // Lê o código da carta (ex: A01) ——————————————
void  lerNomeCidade(char nomeCidade[]); // Lê o nome da cidade —————————————————
int   lerPopulacao(); // Garante que a população seja um número positivo ———————
float lerArea(); // Garante que a área seja um número positivo maior que zero ——
float lerPIB(); // Garante que o PIB seja um número positivo ———————————————————
int   lerPontosTuristicos(); // Garante que o número de pontos seja positivo ———
void  limparBuffer(); // Limpa o buffer do teclado em caso de entrada inválida —

// Função principal ————————————————————————————————————————————————————————————
int main() {
    // ========== Área para definição das variáveis ==========
    // Variáveis para armazenar os dados das cartas
    char estados[NUM_CARTAS];
    char codigos[NUM_CARTAS][4];        // Ex: "A01" (3 chars + '\0')
    char nomesCidades[NUM_CARTAS][50];
    int populacoes[NUM_CARTAS];
    float areas[NUM_CARTAS];
    float pibs[NUM_CARTAS];
    int pontosTuristicos[NUM_CARTAS];

    // ========== Área para entrada de dados ==========
    printf("=== BEM-VINDO AO SUPER TRUNFO - PAÍSES ===\n");
    printf("Vamos cadastrar %d cartas de cidades!\n\n", NUM_CARTAS);

    // Loop para cadastrar cada carta
    for (int i = 0; i < NUM_CARTAS; i++) {
        printf("========================================\n");
        printf("       CADASTRO DA CARTA %d\n", i + 1);
        printf("========================================\n");

        // Lê e valida o estado (A-H)
        estados[i] = lerEstado();

        // Lê o código da carta
        lerCodigo(codigos[i]);

        // Lê o nome da cidade
        lerNomeCidade(nomesCidades[i]);

        // Lê e valida a população
        populacoes[i] = lerPopulacao();

        // Lê e valida a área
        areas[i] = lerArea();

        // Lê e valida o PIB
        pibs[i] = lerPIB();

        // Lê e valida pontos turísticos
        pontosTuristicos[i] = lerPontosTuristicos();

        printf("\nCarta %d cadastrada com sucesso!\n", i + 1);
    }

    // ========== Área para exibição dos dados das cidades ==========
    printf("\n\n==========================================\n");
    printf("         CARTAS CADASTRADAS\n");
    printf("==========================================\n");

    // Loop para exibir cada carta cadastrada
    for (int i = 0; i < NUM_CARTAS; i++) {
        printf("\n===== CARTA %d =====\n", i + 1);
        printf("Estado: %c\n", estados[i]);
        printf("Codigo: %s\n", codigos[i]);
        printf("Nome da Cidade: %s\n", nomesCidades[i]);
        printf("Populacao: %d habitantes\n", populacoes[i]);
        printf("Area: %.2f km²\n", areas[i]);
        printf("PIB: %.2f bilhoes de reais\n", pibs[i]);
        printf("Numero de Pontos Turisticos: %d\n", pontosTuristicos[i]);
    }

    printf("\nObrigado por usar o Super Trunfo!\n");
    return 0;
}

// Função para ler e validar o Estado ——————————————————————————————————————————
char lerEstado() {
    char estado;
    
    do {
        printf("Digite o estado (A-H): ");
        scanf(" %c", &estado);              // Espaço antes de %c limpa o buffer
        estado = toupper(estado);           // Converte para maiúscula
        
        // Verifica se o estado está no intervalo válido
        if (estado < 'A' || estado > 'H') {
            printf("ERRO: Digite apenas letras de A a H!\n");
            limparBuffer();                 // Limpa o buffer em caso de erro
        }
    } while (estado < 'A' || estado > 'H'); // Repete até entrada válida
    
    return estado;
}

// Função para ler o código da carta ———————————————————————————————————————————
void lerCodigo(char codigo[]) {
    // Lê o código da carta sem validação (nível novato)
    printf("Digite o codigo da carta (ex: A01): ");
    scanf("%s", codigo);                    // Lê a string do código
}

// Função para ler o nome da cidade ————————————————————————————————————————————
void lerNomeCidade(char nomeCidade[]) {
    // Lê o nome da cidade incluindo espaços
    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", nomeCidade);           // %[^\n] lê até encontrar Enter
}

// Função para ler e validar a população ———————————————————————————————————————
int lerPopulacao() {
    int populacao;
    
    do {
        printf("Digite a populacao: ");
        
        // scanf retorna 1 se conseguiu ler um inteiro, 0 se não conseguiu
        if (scanf("%d", &populacao) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            populacao = -1;                 // Força o loop a continuar
        }
        else if (populacao < 0) {
            printf("ERRO: A populacao deve ser um numero positivo!\n");
        }
    } while (populacao < 0);
    
    return populacao;
}

// Função para ler e validar a área ————————————————————————————————————————————
float lerArea() {
    float area;
    
    do {
        printf("Digite a area (km²): ");
        
        // Verifica se conseguiu ler um número float válido
        if (scanf("%f", &area) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            area = -1;                      // Força o loop a continuar
        }
        else if (area <= 0) {
            printf("ERRO: A area deve ser maior que zero!\n");
        }
    } while (area <= 0);
    
    return area;
}

// Função para ler e validar o PIB —————————————————————————————————————————————
float lerPIB() {
    float pib;
    
    do {
        printf("Digite o PIB (em bilhoes): ");
        
        // Verifica se conseguiu ler um número float válido
        if (scanf("%f", &pib) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            pib = -1;                       // Força o loop a continuar
        }
        else if (pib < 0) {
            printf("ERRO: O PIB deve ser um numero positivo!\n");
        }
    } while (pib < 0);
    
    return pib;
}

// Função para ler e validar pontos turísticos ——————————————————————————————————
int lerPontosTuristicos() {
    int pontos;
    
    do {
        printf("Digite o numero de pontos turisticos: ");
        
        // Verifica se conseguiu ler um inteiro válido
        if (scanf("%d", &pontos) != 1) {
            printf("ERRO: Digite apenas numeros inteiros!\n");
            limparBuffer();
            pontos = -1;                    // Força o loop a continuar
        }
        else if (pontos < 0) {
            printf("ERRO: O numero de pontos turisticos deve ser positivo!\n");
        }
    } while (pontos < 0);
    
    return pontos;
}

// Função para limpar o buffer do teclado ———————————————————————————————————————
void limparBuffer() {
    int c;
    // Lê e descarta todos os caracteres até encontrar '\n' ou fim do arquivo
    while ((c = getchar()) != '\n' && c != EOF);
}