#include <stdio.h>

void calcular_imc(float peso, float altura, float *imc, char *classificacao, float *diferenca) {
    *imc = peso / (altura * altura);

    // Classificação segundo OMS
    if (*imc < 18.5f) {
        sprintf(classificacao, "Abaixo do peso");
    } else if (*imc < 25.0f) {
        sprintf(classificacao, "Peso normal");
    } else if (*imc < 30.0f) {
        sprintf(classificacao, "Sobrepeso");
    } else if (*imc < 35.0f) {
        sprintf(classificacao, "Obesidade grau I");
    } else if (*imc < 40.0f) {
        sprintf(classificacao, "Obesidade grau II");
    } else {
        sprintf(classificacao, "Obesidade grau III");
    }

    // Cálculo de diferença de peso para faixa normal (18,5–24,9)
    float imc_min = 18.5f;
    float imc_max = 24.9f;
    float peso_min = imc_min * altura * altura;
    float peso_max = imc_max * altura * altura;

    if (peso < peso_min) {
        *diferenca = peso_min - peso;      // precisa GANHAR peso
    } else if (peso > peso_max) {
        *diferenca = peso_max - peso;      // precisa PERDER peso (valor negativo)
    } else {
        *diferenca = 0.0f;                 // já está na faixa
    }
}

int main() {
    float peso, altura, imc, diferenca;
    char classificacao[30];

    printf("=== Calculadora de IMC ===\n");
    printf("Digite seu peso em kg: ");
    if (scanf("%f", &peso) != 1) {
        printf("Entrada inválida para peso.\n");
        return 1;
    }

    printf("Digite sua altura em metros: ");
    if (scanf("%f", &altura) != 1 || altura <= 0.0f) {
        printf("Entrada inválida para altura.\n");
        return 1;
    }

    calcular_imc(peso, altura, &imc, classificacao, &diferenca);

    printf("\nSeu IMC é: %.1f\n", imc);
    printf("Classificação: %s\n", classificacao);

    if (diferenca > 0.0f) {
        printf("Você precisa ganhar aproximadamente %.1f kg para atingir o peso mínimo saudável.\n", diferenca);
    } else if (diferenca < 0.0f) {
        printf("Você precisa perder aproximadamente %.1f kg para ficar no máximo da faixa saudável.\n", -diferenca);
    } else {
        printf("Parabéns! Você está dentro da faixa de peso normal.\n");
    }

    return 0;
}