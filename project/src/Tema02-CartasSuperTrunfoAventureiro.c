// Desafio Super Trunfo - Países
// Tema 02 - Nível Aventureiro - Cadastro das cartas com propriedades calculadas
// Objetivo: Expandir o sistema do nível Novato para poder incluir propriedades
// calculadas para cada carta cadastrada automaticamente: Densidade Populacional
// e PIB per Capita (com base em dados de entrada).
// NOTA: Aproveitando dos recursos de nossa era, este programa foi escrito com
// assistência de um LLM (Claude Sonnet 4), contudo, não foi apenas um <copy-
// paste>, mas sim uma colaboração entre humano e IA para garantir qualidade. 

#include <stdio.h>
#include <ctype.h>

// Constantes ——————————————————————————————————————————————————————————————————
// É assumido que trata-se de apenas um país com 8 estados (A a H) e 04 cidades,
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
// NOVAS FUNÇÕES DO NÍVEL AVENTUREIRO ——————————————————————————————————————————
double calcularDensidadePopulacional(int populacao, float area); // Densidade ——
double calcularPIBPerCapita(float pib, int populacao); // PIB per capita ———————
void   exibirTabelaEstado(char      letraEstado,
                          int       inicioIndice, 
                          char      codigos[][4],
                          char      nomesCidades[][50], 
                          int       populacoes[],
                          float     areas[],
                          float     pibs[], 
                          int       pontosTuristicos[],
                          double    densidades[], 
                          double    pibsPerCapita[]); // Tormato tabular ———————

// Função principal ————————————————————————————————————————————————————————————
int main() {
    // Área para definição das variáveis =======================================
    // Variáveis para armazenar os dados das cartas (MESMAS DO NÍVEL NOVATO)
    char  codigos[TOTAL_CARTAS][4]; // Códigos automáticos, ex: A01, B01, etc. —
    char  nomesCidades[TOTAL_CARTAS][50]; // Nomes das cidades de cada carta ———
    int   populacoes[TOTAL_CARTAS]; // População de cada cidade ————————————————
    float areas[TOTAL_CARTAS]; // Área em km² de cada cidade ———————————————————
    float pibs[TOTAL_CARTAS]; // PIB em bilhões de cada cidade —————————————————
    int   pontosTuristicos[TOTAL_CARTAS]; // Número de pontos turísticos ———————
    
    // NOVAS VARIÁVEIS DO NÍVEL AVENTUREIRO ————————————————————————————————————
    // Usamos 'double' para maior precisão nos cálculos conforme especificação —
    double densidadesPopulacionais[TOTAL_CARTAS]; // Densidade: hab/km² ————————
    double pibsPerCapita[TOTAL_CARTAS]; // PIB per capita em bilhões/hab ———————

    // Área para entrada de dados ============================================== 
    printf("=== BEM-VINDO AO SUPER TRUNFO - PAÍSES ===\n");
    printf("Vamos cadastrar %d cartas.\n", TOTAL_CARTAS);
    printf("O total de cartas está organizado em %d estados!\n", NUM_ESTADOS);
    printf("Cada estado tem %d cidades com código único.\n", CIDADES_POR_ESTADO);
    printf("NOVIDADE: Densidade Populacional e PIB per Capita serão calculados!\n\n");

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

            // Lê todos os dados desta carta (MESMA LÓGICA DO NÍVEL NOVATO) ————
            lerNomeCidade(nomesCidades[indiceGeral]);
            populacoes[indiceGeral] = lerPopulacao();
            areas[indiceGeral] = lerArea();
            pibs[indiceGeral] = lerPIB();
            pontosTuristicos[indiceGeral] = lerPontosTuristicos();

            // NOVA FUNCIONALIDADE: Calcula propriedades derivadas —————————————
            // Densidade Populacional = População/Área —————————————————————————
            densidadesPopulacionais[indiceGeral] = calcularDensidadePopulacional(
                populacoes[indiceGeral], areas[indiceGeral]
            );
            
            // PIB per Capita = PIB/População ——————————————————————————————————
            pibsPerCapita[indiceGeral] = calcularPIBPerCapita(
                pibs[indiceGeral], populacoes[indiceGeral]
            );

            printf("Carta %s cadastrada com sucesso!\n", codigos[indiceGeral]);
            printf("Densidade calculada: %.2f hab/km²\n", densidadesPopulacionais[indiceGeral]);
            printf("PIB per capita calculado: %.2e reais/hab\n", pibsPerCapita[indiceGeral] * 1e9);
            
            // Incrementa o índice para a próxima posição nos arrays ———————————
            indiceGeral++;
        }
    }

    // Área para exibição dos dados das cidades ================================
    printf("\n\n===========================================================\n");
    printf("              CARTAS CADASTRADAS - FORMATO TABULAR\n");
    printf("===========================================================\n");
    
    // Cada estado terá sua própria tabela organizada com todas as propriedades:
    for (int estado = 0; estado < NUM_ESTADOS; estado++) {
        char letraEstado = 'A' + estado;
        int inicioIndice = estado * CIDADES_POR_ESTADO;
        
        // Chama função que exibe a tabela do estado atual ————————————————————
        exibirTabelaEstado(letraEstado, inicioIndice, codigos, nomesCidades,
                          populacoes, areas, pibs, pontosTuristicos,
                          densidadesPopulacionais, pibsPerCapita);
    }

    printf("\n===========================================================\n");
    printf("Todas as %d cartas foram cadastradas e analisadas!\n", TOTAL_CARTAS);
    printf("Estados: A, B, C, D, E, F, G, H (8 estados)\n");
    printf("Cidades por estado: 01, 02, 03, 04 (4 cidades cada)\n");
    printf("PROPRIEDADES CALCULADAS:\n");
    printf("- Densidade Populacional (hab/km²) - Precisão dupla, 2 casas decimais\n");
    printf("- PIB per Capita (bilhões/hab) - Notação científica, 2 casas decimais\n");
    printf("Obrigado por usar o Super Trunfo - Nível Aventureiro!\n");
    return 0;
}

// Função para ler o nome da cidade (SEM ALTERAÇÕES DO NÍVEL NOVATO) ———————————
void lerNomeCidade(char nomeCidade[]) {
    // Lê o nome da cidade incluindo espaços em branco —————————————————————————
    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", nomeCidade);           // %[^\n] lê até encontrar Enter ———
}

// Função para ler e validar a população (SEM ALTERAÇÕES DO NÍVEL NOVATO) ——————
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

// Função para ler e validar a área (SEM ALTERAÇÕES DO NÍVEL NOVATO) ———————————
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

// Função para ler e validar o PIB (SEM ALTERAÇÕES DO NÍVEL NOVATO) ————————————
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

// Função para ler e validar pontos turísticos (SEM ALTERAÇÕES DO NÍVEL NOVATO)
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

// Função para limpar o buffer do teclado (SEM ALTERAÇÕES DO NÍVEL NOVATO) —————
void limparBuffer() {
    int c;
    // Lê e descarta todos os caracteres até encontrar '\n' ou fim do arquivo ——
    // Isso evita que caracteres inválidos "sobrem" no buffer e causem problemas
    while ((c = getchar()) != '\n' && c != EOF);
}

// NOVA FUNÇÃO: Calcula densidade populacional —————————————————————————————————
double calcularDensidadePopulacional(int populacao, float area) {
    // Densidade = População ÷ Área (habitantes por km²) ———————————————————————
    // Verifica divisão por zero para evitar erro matemático ———————————————————
    if (area <= 0) {
        printf("AVISO: Area invalida para calculo de densidade!\n");
        return 0.0;
    }
    
    // Retorna o cálculo com precisão dupla ————————————————————————————————————
    return (double)populacao / (double)area;
}

// NOVA FUNÇÃO: Calcula PIB per capita —————————————————————————————————————————
double calcularPIBPerCapita(float pib, int populacao) {
    // PIB per capita = PIB ÷ População (bilhões por habitante) ————————————————
    // Verifica divisão por zero para evitar erro matemático ———————————————————
    if (populacao <= 0) {
        printf("AVISO: Populacao invalida para calculo de PIB per capita!\n");
        return 0.0;
    }
    
    // Retorna o cálculo com precisão dupla ————————————————————————————————————
    return (double)pib / (double)populacao;
}

// NOVA FUNÇÃO: Exibe dados em formato tabular por estado ——————————————————————
void exibirTabelaEstado(char letraEstado, int inicioIndice, 
                       char codigos[][4], char nomesCidades[][50], 
                       int populacoes[], float areas[], float pibs[], 
                       int pontosTuristicos[], double densidades[], 
                       double pibsPerCapita[]) {
    
    printf("\n========== ESTADO %c - TABELA RESUMO ==========\n", letraEstado);
    
    // Cabeçalho da tabela —————————————————————————————————————————————————————
    printf("%-4s %-20s %-12s %-10s %-12s %-8s %-15s %-15s\n",
        "Cod", "Cidade", "Pop.(hab)", "Area(km²)", "PIB(bi)", "Pontos",
        "Densidade", "PIB per Cap.(R$)");
    
    printf("%-4s %-20s %-12s %-10s %-12s %-8s %-15s %-15s\n",
           "----", "--------------------", "------------", "----------", 
           "------------", "--------", "---------------", "---------------");

    // Dados das 4 cidades do estado ———————————————————————————————————————————
    for (int i = 0; i < CIDADES_POR_ESTADO; i++) {
        int indice = inicioIndice + i;
        
        printf("%-4s %-20s %-12d %-10.2f %-12.2f %-8d %-15.2f %-15.2e\n",
               codigos[indice],                   // Código da carta ———————————
               nomesCidades[indice],              // Nome da cidade ————————————
               populacoes[indice],                // População —————————————————
               areas[indice],                     // Área ——————————————————————
               pibs[indice],                      // PIB ———————————————————————
               pontosTuristicos[indice],          // Pontos turísticos —————————
               densidades[indice],                // Densidade —————————————————
               pibsPerCapita[indice] * 1e9        // PIB per capita ————————————
        );
    }
    
    printf("\n"); // Linha em branco para separar as tabelas ———————————————————
}