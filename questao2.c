#include <stdio.h>

#define VERBOSE 1 

// Impressão de um vetor (utilitário didático)
void print_vetor(const long long v[], int n) {
    if (!VERBOSE) return;
    printf("Ciclos lidos (C1..CN): [");
    for (int i = 0; i < n; i++) {
        printf("%lld", v[i]);
        if (i+1 < n) printf(", ");
    }
    printf("]\n");
}
    //Algoritmo de Euclides (MDC), com passos
    //Técnica: mdc(a,b) = mdc(b, a mod b) até b==0.

long long mdc(long long a, long long b) {
    long long resto;
    while (b != 0) {
        resto = a % b;
        // A linha abaixo foi corrigida
        printf("Algoritmo de Euclides: %lld mod %lld = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}
   // MMC usando a relação fundamental
   // Técnica: mmc(a,b) = (a / mdc(a,b)) * b

long long mmc(long long a, long long b) {
    if (VERBOSE) {
        printf("\n[MMC] Calculando mmc(%lld, %lld)\n", a, b);
    }
    long long g = mdc(a, b);
    long long res = (a / g) * b;
    if (VERBOSE) {
        printf("[MMC] mmc(%lld, %lld) = ( %lld / %lld ) * %lld = %lld\n",
               a, b, a, g, b, res);
    }
    return res;
}

int main(void) {
    int N;                     
    long long ciclos[10];      
    long long resultado = 1;      

    printf("Gabriel Saraiva Canabrava: 202045768\n");
    printf("Breno Lucena Cordeiro: 202017343\n");
    printf("Digite o numero de chaves (1 a 10): ");
    if (scanf("%d", &N) != 1) {
        printf("Entrada invalida\n");
        return 0;
    }
    if (N < 1 || N > 10) {
        printf("Entrada invalida (N fora do intervalo)\n");
        return 0;
    }
    
    printf("Digite os ciclos de cada chave (2 a 20): ");
    for (int i = 0; i < N; i++) {
        if (scanf("%lld", &ciclos[i]) != 1) {
            printf("Entrada invalida\n");
            return 0;
        }
        if (ciclos[i] < 2 || ciclos[i] > 20) {
            printf("Entrada invalida (Ci fora do intervalo)\n");
            return 0;
        }
    }

    if (VERBOSE) {
        printf("\n=== ETAPA A: Divisibilidade e múltiplos ===\n");
        printf("Cada chave Ki ativa em anos múltiplos de Ci (0, Ci, 2*Ci, ...).\n");
        printf("O primeiro ano >0 em que TODAS ativam juntas é o MMC(C1..CN).\n");
    }
    print_vetor(ciclos, N);
  
    if (VERBOSE) {
        printf("\n=== ETAPA B: Acúmulo do MMC ===\n");
        printf("Começando com resultado=1 (neutro): mmc(1, x) = x.\n");
    }

    for (int i = 0; i < N; i++) {
        long long antes = resultado;
        if (VERBOSE) {
            printf("\n[Iter %d] Incorporando C%d=%lld ao MMC atual=%lld\n",
                   i+1, i+1, ciclos[i], resultado);
        }
        resultado = mmc(resultado, ciclos[i]); 
        if (VERBOSE) {
            printf("[Iter %d] Atualização: mmc(%lld, %lld) = %lld\n",
                   i+1, antes, ciclos[i], resultado);
        }
    }

    if (VERBOSE) {
        printf("\n=== ETAPA C: Limite de Ano (1..50) ===\n");
        printf("Se MMC > 50, não há sincronização no intervalo (1..50).\n");
        printf("MMC final calculado = %lld\n", resultado);
    }

    if (resultado > 50) {
        printf("nao e possivel\n");
        if (VERBOSE) {
            printf("(Motivo: primeiro encontro ocorre no ano %lld, acima de 50.)\n", resultado);
        }
    } else {
        printf("%lld\n", resultado);
        if (VERBOSE) {
            printf("(Interpretacao: todas as chaves ativam juntas pela primeira vez no ano %lld.)\n",
                   resultado);
        }
    }

    if (VERBOSE) {
        printf("\n=== RESUMO DAS TÉCNICAS ===\n");
        printf("1) Algoritmo de Euclides (MDC): repetição de a = b, b = a%%b até b=0.\n");
        printf("2) Relação MMC-MDC: mmc(a,b) = (a / mdc(a,b)) * b.\n");
        printf("3) Associatividade do MMC: acumulamos mmc iterativamente sobre o vetor de ciclos.\n");
        printf("4) Divisibilidade e múltiplos: sincronizar ciclos = buscar o menor múltiplo comum.\n");
        printf("5) Regra do limite: validar se o MMC <= 50 para estar no intervalo permitido.\n");
    }

    return 0;
}
