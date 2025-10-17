#include <stdio.h>
#include <stdlib.h>    
#include <stdbool.h>  
#include <string.h>    


 // Etapa 1: Implementação do Algoritmo de Euclides

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


 //Etapa 1: Função de iteração g(x) para o Pollard's Rho

long long g(long long x, long long n) {
    return ((x * x) % n + 1) % n;
}


// Etapa 1: Implementação do método p de Pollard
 
long long pollardRho(long long N) {
    if (N % 2 == 0) return 2;
    long long x_k = 2, x_2k = 2, d = 1;
    int k = 1;
    printf("\n---[ Iniciando o método p de Pollard para N = %lld ]---\n", N);
    printf("f(x) = (x^2 + 1) mod %lld, x0 = 2\n\n", N);
    while (d == 1) {
        printf("Passo k = %d:\n", k);
        x_k = g(x_k, N);
        x_2k = g(g(x_2k, N), N);
        printf("  x_%d = %lld\n", k, x_k);
        printf("  x_%d = %lld\n", 2 * k, x_2k);
        d = mdc(llabs(x_k - x_2k), N);
        printf("  Cálculo: mdc(|%lld - %lld|, %lld)\n", x_2k, x_k, N);
        printf("  Resultado do mdc: %lld\n\n", d);
        k++;
    }
    if (d == N) {
        printf("O método falhou para N = %lld (fator encontrado é igual a N).\n", N);
        return -1;
    } else {
        printf("Sucesso! Fator não trivial de %lld encontrado: %lld\n", N, d);
        return d;
    }
}


 // Etapa 2: Algoritmo Estendido de Euclides para o Inverso Modular

long long inversoModular(long long a, long long m) {
    long long a0 = a; // Salva o valor original de 'a' para usar na mensagem
    long long m0 = m; // m0 já salva o módulo original
    long long t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1) return 0;

    // Laço do Algoritmo Estendido de Euclides
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Garante que o resultado do inverso seja um número positivo
    if (x1 < 0) {
        x1 += m0;
    }

    // A linha do printf corrigida
    printf("\nSubstituindo, temos que o inverso de %lld em %lld é %lld.\n\n", a0, m0, x1);

    return x1;
}

// ETAPA 3

// verificar se um número é primo (para o Teorema de Fermat)
bool isPrimo(long long num) {
    if (num <= 1) return false;
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}


 // Etapa 3: Função de Exponenciação Modular com seleção de Teoremas
 //Calcula (base^exp) mod n

long long potenciaModular(long long base, long long exp, long long n, long long z) {
    long long res = 1;
    printf("\n   [Cálculo de Potência: (%lld^%lld) mod %lld]\n", base, exp, n);

    // LÓGICA DE SELEÇÃO DE TEOREMA PARA REDUZIR O EXPOENTE
    if (isPrimo(n)) {
        printf("   -> Aplicando Pequeno Teorema de Fermat (n é primo).\n");
        exp = exp % (n - 1);
        printf("   -> Expoente reduzido para: %lld\n", exp);
    } else if (mdc(base, n) == 1) {
        printf("   -> Aplicando Teorema de Euler (mdc(%lld, %lld) = 1).\n", base, n);
        exp = exp % z;
        printf("   -> Expoente reduzido para: %lld\n", exp);
    } else {
        printf("   -> Não foi possível aplicar Fermat ou Euler. Usando expoente original.\n");
    }

    // Exponenciação por Quadratura
    base %= n;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % n;
        exp = exp >> 1;
        base = (base * base) % n;
    }
    
    printf("   -> Resultado final: %lld\n", res);
    return res;
}

// Converte um caractere para seu código numérico
int charParaCodigo(char c) {
    if (c == ' ') return 0;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 11;
    return -1; // Caractere inválido
}

// Converte um código numérico de volta para um caractere
char codigoParaChar(int codigo) {
    if (codigo == 0) return ' ';
    if (codigo >= 11 && codigo <= 36) return (char)(codigo - 11 + 'A');
    return '?'; // Código inválido
}


int main() {
    long long N1, N2;
    printf("Gabriel Saraiva Canabrava: 202045768\n");
    printf("Breno Lucena Cordeiro: 202017343\n");
    printf("        SISTEMA DE CRIPTOGRAFIA RSA COMPLETO\n");
    printf("====================================================\n");

    printf("\n[ ETAPA 1: FATORAÇÃO COM P DE POLLARD ]\n");
    printf("Digite o primeiro número composto (N1, 3 ou 4 dígitos): ");
    scanf("%lld", &N1);
    printf("Digite o segundo número composto (N2, 3 ou 4 dígitos): ");
    scanf("%lld", &N2);

    long long p = pollardRho(N1);
    long long q = pollardRho(N2);

    if (p == -1 || q == -1) {
        printf("\nFalha na fatoração. O programa será encerrado.\n");
        return 1;
    }
    printf("\n[ FIM DA ETAPA 1 ] Primos encontrados: p = %lld, q = %lld\n", p, q);


    printf("\n====================================================\n");
    printf("[ ETAPA 2: GERAÇÃO DAS CHAVES RSA ]\n");
    long long n = p * q;
    printf("1. Cálculo do módulo: n = p * q = %lld * %lld = %lld\n", p, q, n);
    long long z = (p - 1) * (q - 1);
    printf("2. Cálculo do Totiente de Euler: z = (p-1)*(q-1) = %lld * %lld = %lld\n", p-1, q-1, z);
    long long E = 2;
    printf("3. Procurando o menor expoente público E > 1 tal que mdc(E, %lld) = 1...\n", z);
    while (E < z) {
        if (mdc(E, z) == 1) break;
        E++;
    }
    printf("   Expoente público E escolhido: %lld\n", E);
    printf("4. Calculando expoente privado D...\n");
    long long D = inversoModular(E, z);
    printf("   Expoente privado D calculado: %lld\n", D);
    printf("\nChave Pública: (n=%lld, E=%lld)\n", n, E);
    printf("Chave Privada: (n=%lld, D=%lld)\n", n, D);

    printf("\n====================================================\n");
    printf("[ ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA ]\n");

    char mensagem[100];
    printf("\nDigite a mensagem para criptografar (letras maiúsculas e espaços): ");
    getchar();
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = 0; 

    int len = strlen(mensagem);
    long long codificada[len];
    long long decodificada[len];
    char mensagem_final[len + 1];

    printf("\n--- CRIPTOGRAFANDO A MENSAGEM ---\n");
    for (int i = 0; i < len; i++) {
        char c = mensagem[i];
        int m_bloco = charParaCodigo(c);
        printf("\nCaractere '%c' -> Bloco M = %d", c, m_bloco);
        codificada[i] = potenciaModular(m_bloco, E, n, z);
        printf(" -> Bloco Cifrado C = %lld", codificada[i]);
    }

    printf("\n\nMensagem Cifrada (sequência de blocos):\n");
    for (int i = 0; i < len; i++) {
        printf("%lld ", codificada[i]);
    }
    printf("\n");

    printf("\n--- DESCRIPTOGRAFANDO A MENSAGEM ---\n");
    for (int i = 0; i < len; i++) {
        long long c_bloco = codificada[i];
        printf("\nBloco Cifrado C = %lld", c_bloco);
        decodificada[i] = potenciaModular(c_bloco, D, n, z);
        printf(" -> Bloco Decifrado M = %lld", decodificada[i]);
        mensagem_final[i] = codigoParaChar(decodificada[i]);
    }
    mensagem_final[len] = '\0';

    printf("\n\n====================================================\n");
    printf("VERIFICAÇÃO FINAL:\n");
    printf("Mensagem Original:   %s\n", mensagem);
    printf("Mensagem Decifrada:  %s\n", mensagem_final);
    if (strcmp(mensagem, mensagem_final) == 0) {
        printf("\nSucesso! A mensagem foi recuperada corretamente.\n");
    } else {
        printf("\nFalha! A mensagem não foi recuperada.\n");
    }

    return 0;
}