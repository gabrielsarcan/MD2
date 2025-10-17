#include <stdio.h>
#include <string.h>

#define VERBOSE 1  // 1 = imprime passo a passo; 0 = silencioso 

// Exponenciação rápida (a^b), com logs quando VERBOSE=1
long long pow_ll(long long a, long long b) {
    long long r = 1;
    if (VERBOSE) {
        printf("[pow_ll] calculando %lld^%lld\n", a, b);
    }
    while (b > 0) {
        if (VERBOSE) {
            printf("  b=%lld, r=%lld, a=%lld  %s\n",
                   b, r, a, (b & 1) ? "(b impar → r*=a)" : "");
        }
        if (b & 1) r *= a;
        a *= a;
        b >>= 1;
    }
    if (VERBOSE) {
        printf("[pow_ll] resultado = %lld\n", r);
    }
    return r;
}

// Lê N como inteiro simples OU como a^b (com logs)
int read_N(long long *N_out) {
    char buf[128];
    printf("Digite um numero (ou uma potencia no formato a^b): ");
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    long long N = 0, a = 0, b = 0;
    if (strchr(buf, '^')) {
        if (sscanf(buf, " %lld ^ %lld ", &a, &b) == 2 ||
            sscanf(buf, " %lld^%lld ", &a, &b) == 2) {
            if (VERBOSE) printf("[read_N] detectado formato a^b: a=%lld, b=%lld\n", a, b);
            if (b < 0) return 0;
            N = pow_ll(a, b);  // aqui já imprime o passo a passo da potência
        } else {
            return 0;
        }
    } else {
        if (sscanf(buf, " %lld ", &N) != 1) return 0;
        if (VERBOSE) printf("[read_N] inteiro simples lido: N=%lld\n", N);
    }
    *N_out = N;
    return 1;
}

int main(void) {
    long long N_input;
    
    printf("Gabriel Saraiva Canabrava: 202045768\n");
    printf("Breno Lucena Cordeiro: 202017343\n");
    if (!read_N(&N_input)) {
        printf("Entrada invalida\n");
        return 0;
    }
    if (N_input <= 0) {
        printf("Entrada invalida\n");
        return 0;
    }

    if (N_input == 1) {
        if (VERBOSE) {
            printf("[caso especial] N=1 → fatoracao vazia\n");
            printf("  tau(1)=1 (produto vazio)\n");
            printf("  sigma(1)=1 (soma dos divisores de 1)\n");
        }
        printf("Fatores: (nenhum)\n");
        printf("tau(N)=1\n");
        printf("sigma(N)=1\n");
        printf("Razao de Eficiencia: %.2f\n", 1.00);
        return 0;
    }

    long long n = N_input;
    double tau = 1.0;
    double sigma = 1.0;

    printf("Fatoracao de %lld por Divisao trivial:\n", N_input);

    // Divisao trivial: testa fator 2 separadamente
    if (VERBOSE) printf("[trial] testando fator 2\n");
    if (n % 2 == 0) {
        int e = 0;
        while (n % 2 == 0) {
            n /= 2; e++;
            if (VERBOSE) printf("  2 divide, n -> %lld (e=%d)\n", n, e);
        }
        printf("  fator %d com expoente %d\n", 2, e);

        double old_tau = tau;
        tau = tau * (e + 1);
        printf("    tau parcial: %.0f -> %.0f (x %d)\n", old_tau, tau, e + 1);

        // sigma para 2^e: ((2^(e+1)-1)/(2-1))
        double pe1 = 1.0;               
        for (int i = 0; i < e + 1; ++i) pe1 *= 2.0;
        double termo = (pe1 - 1.0) / (2.0 - 1.0);
        if (VERBOSE) printf("    [sigma] termo para 2^%d = (2^(%d)-1)/(1) = %.0f\n", e, e+1, termo);

        double old_sigma = sigma;
        sigma = sigma * termo;
        printf("    sigma parcial: %.0f -> %.0f (x %.0f)\n", old_sigma, sigma, termo);
    }

       // Divisão Trivial: fatores ímpares até sqrt(n)
    for (long long p = 3; p * p <= n; p += 2) {
        if (VERBOSE) printf("[trial] testando p=%lld (p*p=%lld, n=%lld)\n", p, p*p, n);
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) {
                n /= p; e++;
                if (VERBOSE) printf("  %lld divide, n -> %lld (e=%d)\n", p, n, e);
            }
            printf("  fator %lld com expoente %d\n", p, e);

            double old_tau = tau;
            tau = tau * (e + 1);
            printf("    tau parcial: %.0f -> %.0f (x %d)\n", old_tau, tau, e + 1);

            // sigma para p^e: ((p^(e+1)-1)/(p-1))
            double pe1 = 1.0;     
            for (int i = 0; i < e + 1; ++i) pe1 *= (double)p;
            double termo = (pe1 - 1.0) / ((double)p - 1.0);
            if (VERBOSE) printf("    [sigma] termo para %lld^%d = ((%lld^(%d))-1)/(%lld-1) = %.0f\n",
                                 p, e, p, e+1, p, termo);

            double old_sigma = sigma;
            sigma = sigma * termo;
            printf("    sigma parcial: %.0f -> %.0f (x %.0f)\n", old_sigma, sigma, termo);
        }
    }

    // Sobrou primo > 1? então é o último fator 
    if (n > 1) {
        int e = 1;
        printf("  fator %lld com expoente %d\n", n, e);

        double old_tau = tau;
        tau = tau * (e + 1);
        printf("    tau parcial: %.0f -> %.0f (x %d)\n", old_tau, tau, e + 1);

        double pe1 = (double)n * (double)n; // n^(e+1) = n^2
        double termo = (pe1 - 1.0) / ((double)n - 1.0);
        if (VERBOSE) printf("    [sigma] termo para %lld^%d = ((%lld^(%d))-1)/(%lld-1) = %.0f\n",
                             n, e, n, e+1, n, termo);

        double old_sigma = sigma;
        sigma = sigma * termo;
        printf("    sigma parcial: %.0f -> %.0f (x %.0f)\n", old_sigma, sigma, termo);
    }

    double R = sigma / tau;
    if (VERBOSE) {
        printf("[final] tau=%.0f, sigma=%.0f, R=sigma/tau=%.2f\n", tau, sigma, R);
    }
    printf("tau(N)=%.0f\n", tau);
    printf("sigma(N)=%.0f\n", sigma);
    printf("Razao de Eficiencia: %.2f\n", R);
    return 0;
}
