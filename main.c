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
    op_2 = full_matrix(2, 2, 3);

    puts("//>==================== criacao de matrizes: ===================");
    puts("Zeros matrix, matriz (2,4):");
    print_matrix(zeros_matrix(2, 4));

    puts("Full matrix, matriz (5,2) de 7s:");
    print_matrix(full_matrix(5, 2, 7));

    puts("I matrix (4):");
    print_matrix(i_matrix(4));

    puts("Tile matrix, I matrix (3) com 3 repetições:");
    print_matrix(tile_matrix(i_matrix(2), 3));

    puts("//>==================== acesso a elementos: ====================");
    puts("Matrix a ser usada nos testes: ");
    print_matrix(teste);

    printf("Get element (1,2): %d\n\n", get_element(teste, 1, 2));
    
    put_element(teste, 0, 1, 0);
    puts("Put element 0 em (0,1): ");
    print_matrix(teste);

    puts("//>================= manipulacao de dimensoes: =================");
    puts("Transpose da matriz teste: ");
    print_matrix(transpose(teste));

    puts("Reshape da matriz teste para (2,6): ");
    print_matrix(reshape(teste, 2, 6));

    puts("Slice (1,3,1,3) da matriz teste:");
    print_matrix(slice(teste, 1, 3, 1, 3));

    puts("Transpose do slice (1,3,1,3) da matriz teste:");
    print_matrix(transpose(slice(teste, 1, 3, 1, 3)));

    puts("Reshape para (4,1) da transpose do slice (1,3,1,3) da matriz teste:");
    print_matrix(reshape(transpose(slice(teste, 1, 3, 1, 3)), 4, 1));

    puts("Tile com 6 repeticoes da reshape para (4,1) da transpose do slice (1,3,1,3) da matriz teste:");
    print_matrix(tile_matrix(reshape(transpose(slice(teste, 1, 3, 1, 3)), 4, 1), 6));

    puts("Slice (2,4,0,2) da tile com 6 repeticoes da reshape para (4,1) da transpose do slice (1,3,1,3) da matriz teste:");
    print_matrix(slice(tile_matrix(reshape(transpose(slice(teste, 1, 3, 1, 3)), 4, 1), 6), 2, 4, 0, 2));

    puts("//>======================== agregacao: =========================");
    puts("Valores minimos e maximos da matriz teste e seus indices:");
    printf("Min: %d\n", min(teste));
    printf("Max: %d\n", max(teste));
    printf("Argmin: %d\n", argmin(teste));
    printf("Argmax: %d\n\n", argmax(teste));

    puts("//>================== operacoes aritmeticas: ===================");
    puts("Operando 1:");
    print_matrix(op_1);
    puts("Operando 2:");
    print_matrix(op_2);

    puts("Add: ");
    print_matrix(add(op_1, op_2));

    puts("Sub: ");
    print_matrix(sub(op_1, op_2));

    puts("Division: ");
    print_matrix(division(op_1, op_2));

    puts("Mul: ");
    print_matrix(mul(op_1, op_2));

    puts("Somando o operando 1 ao operando 2 ao quadrado: ");
    print_matrix(add (op_1, mul(op_2, op_2)));

    puts("Subtraindo o operando 2 de 3 vezes o operando 1: ");
    print_matrix(sub(add(op_1, (add(op_1, op_1))), op_2));
    
    puts("Transposta do slice (0,3,1,4) da matriz teste:");
    print_matrix(transpose(slice(teste, 1, 3, 2, 4)));

    puts("Dividindo o slice (0,3,1,4) da matriz teste pelo operando 2: ");
    print_matrix(division(slice(teste, 1, 3, 2, 4), op_2));

    puts("Reshape para (2,2) da primeira linha da matriz teste: ");
    print_matrix(reshape(slice(teste, 0, 1, 0, 4), 2, 2));

    puts("Transposta do slice (0,3,1,4) da matriz teste somado ao reshape para (2,2) da primeira linha da matriz teste:");
    print_matrix(add(reshape(slice(teste, 0, 1, 0, 4), 2, 2), transpose(slice(teste, 1, 3, 2, 4))));

    return 0;
}