/*
>>>>>>>>>>> PROJETO FINAL DE PROGRAMACAO ESTRUTURADA <<<<<<<<<<<<<

Professor: 
Igor Malheiros

Alunos:
Joao Antonio Honorato | 20210026680
Maria Raquel Martinez | 20200025900

*/

#include "matrix.h"
#include <stdio.h>

int main(){
    int array[] = {2, 13, 6, 1, 17, 4, 8, 14, 6, 11, 14, 4};
    Matrix teste, op_1, op_2;
    teste = create_matrix(array, 3, 4);
    op_1 = create_matrix(array, 2, 2);
    op_2 = full_matrix(2, 2, 2);

    puts("//>==================== criacao de matrizes: ===================");
    puts("Create matrix:");
    print_matrix(teste);
    putchar('\n');

    puts("Zeros matrix:");
    print_matrix(zeros_matrix(2, 4));
    putchar('\n');

    puts("Full matrix:");
    print_matrix(full_matrix(5, 2, 13));
    putchar('\n');

    puts("I matrix:");
    print_matrix(i_matrix(4));
    putchar('\n');

    puts("Tile matrix:");
    print_matrix(tile_matrix(i_matrix(3), 3));
    putchar('\n');

    puts("//>==================== acesso a elementos: ====================");
    puts("Matrix a ser usada nos testes: ");
    print_matrix(teste);
    putchar('\n');
    printf("Get element (1, 2): %d\n\n", get_element(teste, 1, 2));
    
    put_element(teste, 0, 1, 0);
    puts("Put element 0 em (0, 1): ");
    print_matrix(teste);
    putchar('\n');

    puts("//>================= manipulacao de dimensoes: =================");
    puts("Transpose: ");
    print_matrix(transpose(teste));
    putchar('\n');

    puts("Reshape: ");
    print_matrix(reshape(teste, 2, 6));
    putchar('\n');

    puts("Slice das linhas 1 a 2 e colunas 1 a 2:");
    print_matrix(slice(teste, 1, 3, 1, 3));
    putchar('\n');

    puts("//>======================== agregacao: =========================");
    printf("Min: %d\n\n", min(teste));
    printf("Max: %d\n\n", max(teste));
    printf("Argmin: %d\n\n", argmin(teste));
    printf("Argmax: %d\n\n", argmax(teste));

    puts("//>================== operacoes aritmeticas: ===================");
    puts("Operando 1:");
    print_matrix(op_1);
    putchar('\n');
    puts("Operando 2:");
    print_matrix(op_2);
    putchar('\n');

    puts("Add: ");
    print_matrix(add(op_1, op_2));
    putchar('\n');

    puts("Sub: ");
    print_matrix(sub(op_1, op_2));
    putchar('\n');

    puts("Division: ");
    print_matrix(division(op_1, op_2));
    putchar('\n');

    puts("Mul: ");
    print_matrix(mul(op_1, op_2));
    putchar('\n');

    return 0;
}