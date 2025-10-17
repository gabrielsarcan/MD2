# Atividade - Matemática Discreta II
## Autores

* **Gabriel Saraiva Canabrava** - Matrícula: 202045769
* **Breno Lucena Cordeiro** - Matrícula: 202017343

## Como Compilar e Executar

O código foi desenvolvido em C e pode ser compilado utilizando o GCC.

```bash
# Para compilar o programa da Questão 1
gcc -o programa questao01.c -lm

# Para executar
./programa
```
*Substitua `questao01.c` pelo nome do seu arquivo correspondente a cada questão.*

---

## Respostas - Questão 04 (Bônus)

```c
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

int mdcComPassos (int a, int b) {
    int resto;
    while (b != 0) { // [Linha 10]
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; // [Linha 14]
    }
    return a;
}

int inversoModular(int a, int m) {
    // [Linha 23] O esqueleto original não tem código nesta linha.
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
        x1 += m0; // [Linha 36]

    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

long long powMod(long long base, long long exp, long long mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // [Linha 45]
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
    printf("Insira H: "); scanf("%d", &H);
    printf("Insira G: "); scanf("%d", &G);
    printf("Insira Zn: "); scanf("%d", &Zn);
    printf("Insira x: "); scanf("%d", &x);
    printf("Insira n1: "); scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); // [Linha 72]
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    
    int resultado = powMod(a, x, n1); // [Linha 78]

    printf("Sendo %d o inverso de %d \n", inverso, G);
    printf("Valor final da congruência: %d\n", resultado);
    return 0;
}
```

### 2. Previsão da Saída com os Valores Fornecidos

Com as entradas **H=7, G=3, Zn=11, x=10, n1=13**, a saída do programa será:

```
Insira H: 7
Insira G: 3
Insira Zn: 11
Insira x: 10
Insira n1: 13


Substituindo, temos que o inverso de 3 em 11 é 4.

Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
Sendo 4 o inverso de 3
Valor final da congruência: 4
```

### 3. Respostas para Verdadeiro ou Falso

* **(V)** O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
* **(F)** Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn. *(Justificativa: O inverso modular de um número 'a' módulo 'n' só existe se mdc(a, n) = 1)*
* **(V)** A operação `(H * inverso) % Zn` representa a divisão modular de H por G.
* **(V)** Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1. *(Justificativa: O enunciado da Questão 1 exige esta lógica, e o Teorema de Fermat é a ferramenta padrão para isso, conforme visto na Aula 11)*
* **(F)** A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização. *(Justificativa: A função no esqueleto utiliza o método de exponenciação por quadratura (ou binária), que é altamente otimizado)*
* **(V)** Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0. *(Justificativa: Esta é a forma padrão de garantir que o inverso esteja no conjunto {0, 1, ..., n-1}, e a linha `if (x1 < 0) x1 += m0;` está no esqueleto do código)*
* **(V)** O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo. *(Justificativa: Para n1 primo, o Pequeno Teorema de Fermat é um caso especial mais simples, onde $\phi(n1) = n1 - 1$)*