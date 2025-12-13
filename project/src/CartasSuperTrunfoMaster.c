// Desafio Super Trunfo - Países
// Tema 03 - Nível Mestre
// Objetivo: Expandir o sistema do nível Aventureiro para incluir comparações
// entre cartas, cálculo de Super Poder e manipulação de grandes números.
// NOVIDADE: 30 cartas pré-preenchidas + 2 pelo usuário + sistema de comparação
// MODIFICAÇÕES: Estados com nomes de vegetais, sem códigos, nomes padronizados
// NOTA: Aproveitando dos recursos de nossa era, este programa foi escrito com
// assistência de um LLM (Claude Sonnet 4), contudo, não foi apenas um <copy-
// paste>, mas sim uma colaboração entre humano e IA para garantir qualidade.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Constantes ——————————————————————————————————————————————————————————————————
// É assumido que trata-se de apenas um país com 8 estados com 4 cidades cada,
// onde o cadastro de cartas aborda apenas os dados de dito país. Os estados
// agora têm nomes de vegetais para maior clareza e organização visual.
#define NUM_ESTADOS 8               // 8 estados com nomes de vegetais —————————
#define CIDADES_POR_ESTADO 4        // 4 cidades por estado ————————————————————
#define TOTAL_CARTAS (NUM_ESTADOS * CIDADES_POR_ESTADO)  // Total: 32 cartas ———
#define CARTAS_PREENCHIDAS 30       // 30 cartas pré-preenchidas automaticamente 
#define CARTAS_USUARIO 2            // 2 cartas preenchidas pelo usuário ———————
#define TAM_NOME_CIDADE 20          // Tamanho fixo para nomes das cidades —————
#define TAM_NOME_ESTADO 15          // Tamanho fixo para nomes dos estados —————

// Protótipos/declaração das funções ————[corpo de cada função após o main()]———
void           lerNomeCidade(char nomeCidade[]); // Lê nome da cidade ——————————
unsigned long  lerPopulacao(); // Lê população como unsigned long int ——————————
float          lerArea(); // Garante que área seja positiva maior que zero —————
float          lerPIB(); // Garante que PIB seja um número positivo ————————————
int            lerPontosTuristicos(); // Garante pontos turísticos positivos ———
void           limparBuffer(); // Limpa buffer do teclado ——————————————————————
void           padronizarNome(char nome[]); // Padroniza nome de tamanho fixo ——
// FUNÇÕES DO NÍVEL AVENTUREIRO (MANTIDAS) —————————————————————————————————————
double calcularDensidadePopulacional(unsigned long populacao, float area);
double calcularPIBPerCapita(float pib, unsigned long populacao);
// NOVAS FUNÇÕES DO NÍVEL MESTRE ———————————————————————————————————————————————
void   preencherCartasAutomaticamente(  char nomesCidades[][TAM_NOME_CIDADE],
                                        unsigned long populacoes[],
                                        float areas[],
                                        float pibs[],
                                        int pontosTuristicos[]);
void   obterNomesEstados(   char estados[][TAM_NOME_ESTADO]);
float  calcularSuperPoder(  unsigned long populacao,
                            float area,
                            float pib,
                            int pontosTuristicos,
                            double densidade,
                            double pibPerCapita);
void   exibirIndiceCartas(  char nomesCidades[][TAM_NOME_CIDADE]);
int    obterEscolhaUsuario( int maxCartas);
void   compararCartas(      int carta1,
                            int carta2,
                            char nomesCidades[][TAM_NOME_CIDADE],
                            unsigned long populacoes[],
                            float areas[],
                            float pibs[],
                            int pontosTuristicos[],
                            double densidades[], 
                            double pibsPerCapita[],
                            float superPoderes[]);
void   exibirTabelaEstado(  char nomeEstado[],
                            int inicioIndice, 
                            char nomesCidades[][TAM_NOME_CIDADE], 
                            unsigned long populacoes[],
                            float areas[],
                            float pibs[], 
                            int pontosTuristicos[],
                            double densidades[], 
                            double pibsPerCapita[], 
                            float superPoderes[]); // Tabela de exibição ———————

// Função principal ————————————————————————————————————————————————————————————
int main() {
    // Área para definição das variáveis =======================================
    // Variáveis para armazenar os dados das cartas (32 cartas) ————————————————
    char           nomesCidades[TOTAL_CARTAS][TAM_NOME_CIDADE]; // Tamanho único 
    char           nomesEstados[NUM_ESTADOS][TAM_NOME_ESTADO]; // Nro. e nome ——   
    unsigned long  populacoes[TOTAL_CARTAS]; // População (unsigned long) ——————
    float          areas[TOTAL_CARTAS]; // Área em km² de cada cidade ——————————
    float          pibs[TOTAL_CARTAS]; // PIB em bilhões de cada cidade ————————
    int            pontosTuristicos[TOTAL_CARTAS]; // Nro. de pontos turísticos
    
    // VARIÁVEIS CALCULADAS ————————————————————————————————————————————————————
    double densidadesPopulacionais[TOTAL_CARTAS]; // Densidade: hab/km² ————————
    double pibsPerCapita[TOTAL_CARTAS]; // PIB per capita em bilhões/hab ———————
    float  superPoderes[TOTAL_CARTAS]; // NOVA: Super Poder de cada carta ——————

    // Área para entrada de dados ============================================== 
    printf("============ BEM-VINDO AO SUPER TRUNFO - PAÍSES ============\n");
    printf("Sistema avançado com 32 cartas e comparação entre cartas!\n");
    printf("- %d cartas pré-preenchidas automaticamente;\n", CARTAS_PREENCHIDAS);
    printf("- %d cartas para você cadastrar;\n", CARTAS_USUARIO);
    printf("- Cálculo automático de propriedades e Super Poder;\n");
    printf("- Sistema de comparação entre cartas.\n");

    // Inicializa nomes dos estados (vegetais) e pré-preenche cartas ———————————
    obterNomesEstados(nomesEstados);
    preencherCartasAutomaticamente(nomesCidades, populacoes, areas, pibs, pontosTuristicos);

    // Loop para as 2 últimas cartas (índices 30 e 31) —————————————————————————
    for (int i = CARTAS_PREENCHIDAS; i < TOTAL_CARTAS; i++) {
        // Calcula estado para as últimas cartas ———————————————————————————————
        int estado = i / CIDADES_POR_ESTADO;
        
        printf("\n--- Cadastrando sua carta %d (Estado: %s) ---\n", 
               i + 1, nomesEstados[estado]);

        // Lê dados do usuário —————————————————————————————————————————————————
        lerNomeCidade(nomesCidades[i]);
        padronizarNome(nomesCidades[i]); // Padroniza para tamanho fixo ————————
        populacoes[i] = lerPopulacao();
        areas[i] = lerArea();
        pibs[i] = lerPIB();
        pontosTuristicos[i] = lerPontosTuristicos();

        printf("Carta %d cadastrada com sucesso no estado %s!\n", i + 1, nomesEstados[estado]);
    }

    // Calcula propriedades derivadas para TODAS as cartas ————————————————————
    printf("\nCalculando propriedades derivadas e Super Poder...\n");
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        // Densidade Populacional ——————————————————————————————————————————————
        densidadesPopulacionais[i] = calcularDensidadePopulacional(populacoes[i], areas[i]);
        
        // PIB per Capita ——————————————————————————————————————————————————————
        pibsPerCapita[i] = calcularPIBPerCapita(pibs[i], populacoes[i]);
        
        // NOVA: Super Poder ———————————————————————————————————————————————————
        superPoderes[i] = calcularSuperPoder(populacoes[i], areas[i], pibs[i],
                                            pontosTuristicos[i], densidadesPopulacionais[i],
                                            pibsPerCapita[i]);
    }
    printf("Cálculos concluídos!\n");

    // Área para exibição dos dados das cidades ================================
    printf("\n\n===========================================================\n");
    printf("              TODAS AS CARTAS - FORMATO TABULAR\n");
    printf("===========================================================\n");
    
    // Exibe tabela de cada estado —————————————————————————————————————————————
    for (int estado = 0; estado < NUM_ESTADOS; estado++) {
        int inicioIndice = estado * CIDADES_POR_ESTADO;
        
        exibirTabelaEstado(nomesEstados[estado], inicioIndice, nomesCidades,
                          populacoes, areas, pibs, pontosTuristicos,
                          densidadesPopulacionais, pibsPerCapita, superPoderes);
    }

    // NOVA FUNCIONALIDADE: Sistema de comparação de cartas ———————————————————
    printf("\n===========================================================\n");
    printf("                    COMPARAÇÃO DE CARTAS\n");
    printf("===========================================================\n");
    
    // Exibe índice simplificado para escolha ——————————————————————————————————
    printf("Escolha duas cartas para comparar:\n\n");
    exibirIndiceCartas(nomesCidades);
    
    // Obtém escolhas do usuário ———————————————————————————————————————————————
    printf("\nEscolha a primeira carta (1-%d): ", TOTAL_CARTAS);
    int carta1 = obterEscolhaUsuario(TOTAL_CARTAS) - 1; // Converte para índice 0-31
    
    printf("Escolha a segunda carta (1-%d): ", TOTAL_CARTAS);
    int carta2 = obterEscolhaUsuario(TOTAL_CARTAS) - 1; // Converte para índice 0-31
    
    // Realiza e exibe a comparação ————————————————————————————————————————————
    printf("\n===========================================================\n");
    printf("                 RESULTADO DA COMPARAÇÃO\n");
    printf("===========================================================\n");
    
    compararCartas(carta1, carta2, nomesCidades, populacoes, areas, pibs,
                  pontosTuristicos, densidadesPopulacionais, pibsPerCapita, superPoderes);

    // Finalização do programa —————————————————————————————————————————————————
    printf("\n===========================================================\n");
    printf("Total: %d cartas analisadas e comparadas\n", TOTAL_CARTAS);
    printf("Estados organizados por vegetais: ");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("%s", nomesEstados[i]);
        if (i < NUM_ESTADOS - 1) printf(", ");
    }
    printf("\nPropriedades calculadas: Densidade, PIB per Capita e Super Poder\n");
    printf("Obrigado por usar o Super Trunfo!\n");
    return 0;
}

// Função para ler nome da cidade (ADAPTADA PARA TAMANHO FIXO) —————————————————
void lerNomeCidade(char nomeCidade[]) {
    printf("Digite o nome da cidade (max %d chars): ", TAM_NOME_CIDADE - 1);
    scanf(" %[^\n]", nomeCidade);
}

// NOVA FUNÇÃO: Padroniza nome para tamanho fixo ———————————————————————————————
void padronizarNome(char nome[]) {
    // Trunca se muito longo ———————————————————————————————————————————————————
    if (strlen(nome) >= TAM_NOME_CIDADE) {
        nome[TAM_NOME_CIDADE - 1] = '\0';
    }
    
    // Preenche com espaços se muito curto ————————————————————————————————————
    int len = strlen(nome);
    for (int i = len; i < TAM_NOME_CIDADE - 1; i++) {
        nome[i] = ' ';
    }
    nome[TAM_NOME_CIDADE - 1] = '\0';
}

// NOVA FUNÇÃO: Obtém nomes dos estados (vegetais) ————————————————————————————
void obterNomesEstados(char estados[][TAM_NOME_ESTADO]) {
    char vegetais[8][TAM_NOME_ESTADO] = {
        "Alface        ",  // Estado 1
        "Brocolis      ",  // Estado 2  
        "Cenoura       ",  // Estado 3
        "Damasco       ",  // Estado 4
        "Espinafre     ",  // Estado 5
        "Feijao        ",  // Estado 6
        "Gengibre      ",  // Estado 7
        "Hortelã       "   // Estado 8
    };
    
    // Copia nomes padronizados ————————————————————————————————————————————————
    for (int i = 0; i < NUM_ESTADOS; i++) {
        strcpy(estados[i], vegetais[i]);
    }
}

// Função para ler população (ADAPTADA PARA UNSIGNED LONG) ————————————————————
unsigned long lerPopulacao() {
    unsigned long populacao;
    
    do {
        printf("Digite a populacao: ");
        
        // scanf com %lu para unsigned long ———————————————————————————————————
        if (scanf("%lu", &populacao) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            populacao = 0; // Força o loop a continuar (0 é inválido) ————————————
        }
        else if (populacao == 0) {
            printf("ERRO: A populacao deve ser maior que zero!\n");
        }
    } while (populacao == 0);
    
    return populacao;
}

// Função para ler área (SEM ALTERAÇÕES DO NÍVEL ANTERIOR) ————————————————————
float lerArea() {
    float area;
    
    do {
        printf("Digite a area (km²): ");
        
        if (scanf("%f", &area) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            area = -1;
        }
        else if (area <= 0) {
            printf("ERRO: A area deve ser maior que zero!\n");
        }
    } while (area <= 0);
    
    return area;
}

// Função para ler PIB (SEM ALTERAÇÕES DO NÍVEL ANTERIOR) —————————————————————
float lerPIB() {
    float pib;
    
    do {
        printf("Digite o PIB (em bilhoes): ");
        
        if (scanf("%f", &pib) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            pib = -1;
        }
        else if (pib < 0) {
            printf("ERRO: O PIB deve ser um numero positivo!\n");
        }
    } while (pib < 0);
    
    return pib;
}

// Função para ler pontos turísticos (SEM ALTERAÇÕES DO NÍVEL ANTERIOR) ———————
int lerPontosTuristicos() {
    int pontos;
    
    do {
        printf("Digite o numero de pontos turisticos: ");
        
        if (scanf("%d", &pontos) != 1) {
            printf("ERRO: Digite apenas numeros inteiros!\n");
            limparBuffer();
            pontos = -1;
        }
        else if (pontos < 0) {
            printf("ERRO: O numero de pontos turisticos deve ser positivo!\n");
        }
    } while (pontos < 0);
    
    return pontos;
}

// Função para limpar buffer (SEM ALTERAÇÕES) —————————————————————————————————
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para calcular densidade (ADAPTADA PARA UNSIGNED LONG) ———————————————
double calcularDensidadePopulacional(unsigned long populacao, float area) {
    if (area <= 0) {
        printf("AVISO: Area invalida para calculo de densidade!\n");
        return 0.0;
    }
    
    // Conversão cuidadosa de tipos ————————————————————————————————————————————
    return (double)populacao / (double)area;
}

// Função para calcular PIB per capita (ADAPTADA PARA UNSIGNED LONG) ——————————
double calcularPIBPerCapita(float pib, unsigned long populacao) {
    if (populacao == 0) {
        printf("AVISO: Populacao invalida para calculo de PIB per capita!\n");
        return 0.0;
    }
    
    // Conversão cuidadosa de tipos ————————————————————————————————————————————
    return (double)pib / (double)populacao;
}

// NOVA FUNÇÃO: Preenche 30 cartas automaticamente (SEM CÓDIGOS) ——————————————
void preencherCartasAutomaticamente(char nomesCidades[][TAM_NOME_CIDADE], 
                                   unsigned long populacoes[], float areas[],
                                   float pibs[], int pontosTuristicos[]) {
    
    // Dados realistas de cidades brasileiras (PADRONIZADOS) ——————————————————
    char nomes[30][TAM_NOME_CIDADE] = {
        "São Paulo          ", "Rio de Janeiro     ", "Salvador           ", "Fortaleza          ",
        "Belo Horizonte     ", "Manaus             ", "Curitiba           ", "Recife             ",
        "Brasília           ", "Goiânia            ", "Belém              ", "Porto Alegre       ",
        "Guarulhos          ", "Campinas           ", "São Luís           ", "São Gonçalo        ",
        "Maceió             ", "Duque de Caxias    ", "Campo Grande       ", "Natal              ",
        "Teresina           ", "São Bernardo       ", "Nova Iguaçu        ", "João Pessoa        ",
        "Santo André        ", "Osasco             ", "Jaboatão           ", "Contagem           ",
        "Ribeirão Preto     ", "Uberlândia         "
    };
    
    // Dados de população (em habitantes) ——————————————————————————————————————
    unsigned long pops[30] = {
        12325232, 6748000, 2886698, 2669342,
        2521564, 2219580, 1948626, 1653461,
        3055149, 1536097, 1499641, 1488252,
        1392121, 1213792, 1108975, 1084839,
        1025360, 924624, 906092, 890480,
        868075, 844483, 817208, 817511,
        721368, 697886, 695956, 668949,
        695737, 699097
    };
    
    // Dados de área (em km²) ——————————————————————————————————————————————————
    float ars[30] = {
        1521.11, 1200.27, 692.82, 314.93,
        331.40, 11401.09, 434.89, 218.44,
        5760.78, 739.49, 1059.46, 496.68,
        318.68, 794.57, 834.78, 249.14,
        510.65, 467.62, 8096.05, 167.26,
        1391.98, 408.45, 521.24, 211.47,
        175.78, 64.95, 258.69, 195.27,
        650.95, 4115.82
    };
    
    // Dados de PIB (em bilhões) ———————————————————————————————————————————————
    float pibs_dados[30] = {
        714.68, 254.51, 60.73, 58.26,
        93.68, 75.88, 102.65, 66.27,
        259.49, 49.15, 36.25, 93.77,
        55.45, 59.02, 19.31, 14.98,
        16.46, 15.21, 28.48, 18.28,
        13.73, 46.27, 13.04, 16.78,
        56.90, 55.46, 12.34, 11.87,
        18.45, 26.51
    };
    
    // Dados de pontos turísticos ——————————————————————————————————————————————
    int pontos[30] = {
        156, 189, 128, 89, 76, 94, 67, 82,
        145, 54, 78, 98, 23, 45, 67, 34,
        89, 28, 112, 76, 58, 67, 31, 87,
        45, 32, 54, 43, 78, 89
    };
    
    // Preenche os arrays com os dados (SEM CÓDIGOS) ——————————————————————————
    for (int i = 0; i < CARTAS_PREENCHIDAS; i++) {
        strcpy(nomesCidades[i], nomes[i]);
        populacoes[i] = pops[i];
        areas[i] = ars[i];
        pibs[i] = pibs_dados[i];
        pontosTuristicos[i] = pontos[i];
    }
}

// NOVA FUNÇÃO: Calcula Super Poder com conversões cuidadosas —————————————————
float calcularSuperPoder(unsigned long populacao, float area, float pib,
                        int pontosTuristicos, double densidade, double pibPerCapita) {
    
    // Soma com conversões explícitas para evitar erros de tipo ———————————————
    float superPoder = (float)populacao + area + pib + (float)pontosTuristicos + 
                      (float)densidade + (float)pibPerCapita;
    
    return superPoder;
}

// NOVA FUNÇÃO: Exibe índice simplificado para escolha (SEM CÓDIGOS) ——————————
void exibirIndiceCartas(char nomesCidades[][TAM_NOME_CIDADE]) {
    printf("%-4s %-20s  %-4s %-20s  %-4s %-20s\n", 
           "Nº", "Cidade", "Nº", "Cidade", "Nº", "Cidade");
    printf("%-4s %-20s  %-4s %-20s  %-4s %-20s\n",
           "---", "--------------------", "---", "--------------------", 
           "---", "--------------------");
    
    // Exibe em 3 colunas para economizar espaço ——————————————————————————————
    for (int i = 0; i < TOTAL_CARTAS; i += 3) {
        printf("%-4d %-20s", i + 1, nomesCidades[i]);
        
        if (i + 1 < TOTAL_CARTAS) {
            printf("  %-4d %-20s", i + 2, nomesCidades[i + 1]);
        } else {
            printf("  %-4s %-20s", "", "");
        }
        
        if (i + 2 < TOTAL_CARTAS) {
            printf("  %-4d %-20s", i + 3, nomesCidades[i + 2]);
        }
        
        printf("\n");
    }
}

// NOVA FUNÇÃO: Obtém escolha válida do usuário ———————————————————————————————
int obterEscolhaUsuario(int maxCartas) {
    int escolha;
    
    do {
        if (scanf("%d", &escolha) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            limparBuffer();
            escolha = 0; // Valor inválido para continuar loop ——————————————————
        }
        else if (escolha < 1 || escolha > maxCartas) {
            printf("ERRO: Digite um numero entre 1 e %d!\n", maxCartas);
        }
    } while (escolha < 1 || escolha > maxCartas);
    
    return escolha;
}

// NOVA FUNÇÃO: Compara duas cartas e exibe resultados ————————————————————————
void compararCartas(int carta1, int carta2, char nomesCidades[][TAM_NOME_CIDADE],
                   unsigned long populacoes[], float areas[], float pibs[],
                   int pontosTuristicos[], double densidades[], 
                   double pibsPerCapita[], float superPoderes[]) {
    
    printf("Comparando: %s vs %s\n\n", nomesCidades[carta1], nomesCidades[carta2]);
    
    // População: maior vence ——————————————————————————————————————————————————
    int popVence = (populacoes[carta1] > populacoes[carta2]) ? 1 : 0;
    printf("População: Carta %d venceu (%d)\n", popVence ? 1 : 2, popVence);
    
    // Área: maior vence ———————————————————————————————————————————————————————
    int areaVence = (areas[carta1] > areas[carta2]) ? 1 : 0;
    printf("Área: Carta %d venceu (%d)\n", areaVence ? 1 : 2, areaVence);
    
    // PIB: maior vence ————————————————————————————————————————————————————————
    int pibVence = (pibs[carta1] > pibs[carta2]) ? 1 : 0;
    printf("PIB: Carta %d venceu (%d)\n", pibVence ? 1 : 2, pibVence);
    
    // Pontos Turísticos: maior vence ——————————————————————————————————————————
    int pontosVence = (pontosTuristicos[carta1] > pontosTuristicos[carta2]) ? 1 : 0;
    printf("Pontos Turísticos: Carta %d venceu (%d)\n", pontosVence ? 1 : 2, pontosVence);
    
    // Densidade: MENOR vence (regra especial) —————————————————————————————————
    int densVence = (densidades[carta1] < densidades[carta2]) ? 1 : 0;
    printf("Densidade Populacional: Carta %d venceu (%d)\n", densVence ? 1 : 2, densVence);
    
    // PIB per Capita: maior vence —————————————————————————————————————————————
    int pibPcVence = (pibsPerCapita[carta1] > pibsPerCapita[carta2]) ? 1 : 0;
    printf("PIB per Capita: Carta %d venceu (%d)\n", pibPcVence ? 1 : 2, pibPcVence);
    
    // Super Poder: maior vence —————————————————————————————————————————————————
    int superVence = (superPoderes[carta1] > superPoderes[carta2]) ? 1 : 0;
    printf("Super Poder: Carta %d venceu (%d)\n", superVence ? 1 : 2, superVence);
    
    // Resumo final —————————————————————————————————————————————————————————————
    int totalVitoriasCarta1 = popVence + areaVence + pibVence + pontosVence + densVence + pibPcVence + superVence;
    printf("\nResumo: Carta 1 venceu %d/7 comparações\n", totalVitoriasCarta1);
    printf("Carta vencedora geral: Carta %d (%s)\n", 
           (totalVitoriasCarta1 > 3) ? 1 : 2,
           (totalVitoriasCarta1 > 3) ? nomesCidades[carta1] : nomesCidades[carta2]);
}

// Função para exibir tabela (ADAPTADA SEM CÓDIGOS E COM NOMES DE VEGETAIS) ———
void exibirTabelaEstado(char nomeEstado[], int inicioIndice, 
                       char nomesCidades[][TAM_NOME_CIDADE], 
                       unsigned long populacoes[], float areas[], float pibs[], 
                       int pontosTuristicos[], double densidades[], 
                       double pibsPerCapita[], float superPoderes[]) {
    
    printf("\n========== ESTADO %s - TABELA RESUMO ==========\n", nomeEstado);
    
    // Cabeçalho da tabela (SEM CÓDIGOS) ———————————————————————————————————————
    printf("%-20s %-12s %-10s %-12s %-8s %-12s %-12s %-12s\n",
           "Cidade", "Pop.(hab)", "Area(km²)", "PIB(bi)", "Pontos",
           "Densidade", "PIB pc(R$)", "SuperPoder");
    
    printf("%-20s %-12s %-10s %-12s %-8s %-12s %-12s %-12s\n",
           "--------------------", "------------", "----------", 
           "------------", "--------", "------------", "------------", "------------");

    // Dados das 4 cidades do estado (SEM CÓDIGOS) ————————————————————————————
    for (int i = 0; i < CIDADES_POR_ESTADO; i++) {
        int indice = inicioIndice + i;
        
        printf("%-20s %-12lu %-10.2f %-12.2f %-8d %-12.2f %-12.2e %-12.2f\n",
               nomesCidades[indice],               // Nome da cidade (padronizado)
               populacoes[indice],                 // População (unsigned long) —
               areas[indice],                      // Área —————————————————————
               pibs[indice],                       // PIB ——————————————————————
               pontosTuristicos[indice],           // Pontos turísticos ————————
               densidades[indice],                 // Densidade —————————————————
               pibsPerCapita[indice] * 1e9,        // PIB per capita ———————————
               superPoderes[indice]                // Super Poder ——————————————
        );
    }
    
    printf("\n"); // Linha em branco para separar as tabelas ———————————————————
}