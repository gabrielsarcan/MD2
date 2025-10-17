#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

int mdcComPassos (int a, int b) {
    int resto;
    while (b != 0) { 
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;


    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

long long powMod(long long base, long long exp, long long mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}


int main() {
    #ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    int H, G, Zn, x, n1;
    printf("Gabriel Saraiva Canabrava: 202045768\n");
    printf("Breno Lucena Cordeiro: 202017343\n");

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); 
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    
    int resultado = powMod(a, x, n1);

    printf("Sendo %d o inverso de %d \n", inverso, G);
    printf("Valor final da congruência: %d\n", resultado);
    return 0;
}