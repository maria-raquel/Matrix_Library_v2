/*
>>>>>>>>>>> PROJETO FINAL DE PROGRAMACAO ESTRUTURADA <<<<<<<<<<<<<

Professor: 
Igor Malheiros

Alunos:
Joao Antonio Honorato | 20210026680
Maria Raquel Martinez | 20200025900

*/

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

//>================ Implementacoes de Funcoes: =================

//>==================== criacao de matrizes: ===================

/*
    Cria uma matriz a partir de um array, o numero de colunas e o numero de linhas.
    > data: array unidimensional 
    > n_rows: numero de linhas
    > n_cols: numero de colunas
*/
Matrix create_matrix(int *data, int n_rows, int n_cols){
    Matrix m = {data, n_rows, n_cols, n_cols, 1, 0};
    return m;
}

/*
    Cria uma matriz com todos elementos nulos.
    > n_rows: numero de linhas
    > n_cols: numero de colunas
*/
Matrix zeros_matrix(int n_rows, int n_cols){
    return full_matrix(n_rows, n_cols, 0);
}

/*
    Cria uma matriz com todos elementos iguais ao valor passado.
    > n_rows: numero de linhas
    > n_cols: numero de colunas
    > value: valor dos elementos da matriz
*/
Matrix full_matrix(int n_rows, int n_cols, int value){
    int *data = malloc(n_rows*n_cols*sizeof(int));

    for (int i=0; i < n_rows*n_cols;)
        *(data+i++) = value;

    return create_matrix(data, n_rows, n_cols);
}

/*
    Cria uma matriz identidade.
    > n: valor das dimensoes (nxn) da matriz
*/
Matrix i_matrix(int n){
    int *data = malloc(n*n*sizeof(int));

    for (int i=0; i < n*n;)
        *(data+i++) = 0;
    
    for (int j=0; j < n*n; j += n+1)
        *(data+j) = 1;

    return create_matrix(data, n, n);
}

/*
    Cria uma matriz nova, repetindo a matriz passada horizontalmente (reps) vezes.
    Exemplo:
    a matriz a seguir repetida 3 vezes será
    (1 2)...(1 2 1 2 1 2)
    (3 4)-->(3 4 3 4 3 4)
    (5 6)...(5 6 5 6 5 6)
    > matrix: matriz a ser repetida
    > reps: quantidade de repetições
*/
Matrix tile_matrix(Matrix matrix, int reps){
    int *data = malloc(matrix.n_cols*matrix.n_rows*sizeof(int)*reps), new_matrix_index = 0;

    for (int row_index = 0; row_index < matrix.n_rows; row_index++)
        for (int j = 0; j < reps; j++)    
            for (int col_index = 0; col_index < matrix.n_cols; col_index++)
                *(data+new_matrix_index++) = matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols];        

    return create_matrix(data, matrix.n_rows, matrix.n_cols*reps);
}

//>==================== acesso a elementos: ====================

/*
    Retorna o elemento da matriz pela sua posicao.
    > matriz: matriz a ser acessada
    > ri: indice da linha do elemento
    > ci: indice da coluna do elemento
*/
int get_element(Matrix matrix, int ri, int ci){
    if (ri<0 || ci<0 || ri >= matrix.n_rows || ci >= matrix.n_cols){
        puts("in get_element: ");
        printf("Error: index [%d][%d] is out of bounds\n", ri, ci);
        exit(1);
    }

    return matrix.data[matrix.offset + ri*matrix.stride_rows + ci*matrix.stride_cols];
}

/*
    Modifica um elemento da matriz pela sua posicao.
    > matriz: matriz a ser acessada
    > ri: indice da linha do elemento
    > ci: indice da coluna do elemento
    > elem: valor novo do elemento
*/
void put_element(Matrix matrix, int ri, int ci, int elem){
    if (ri<0 || ci<0 || ri >= matrix.n_rows || ci >= matrix.n_cols){
        puts("in get_element: ");
        printf("Error: index [%d][%d] is out of bounds\n", ri, ci);
        exit(1);
    }

    matrix.data[matrix.offset + ri*matrix.stride_rows + ci*matrix.stride_cols] = elem;
}

/*
    Exibe os dados da matriz em seu formato.
*/
void print_matrix(Matrix matrix){
    for (int row_index = 0; row_index < matrix.n_rows; row_index++){
        printf("( ");
        for (int col_index = 0; col_index < matrix.n_cols; col_index++)
            printf("%2d ", matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols]);
    printf(")\n");
    }
}

//>================= manipulacao de dimensoes: =================

/*
    Retorna a matriz transposta da matriz.
*/
Matrix transpose(Matrix matrix){
    Matrix transposed = {matrix.data, matrix.n_cols, matrix.n_rows, matrix.stride_cols, matrix.stride_rows, matrix.offset};
    return transposed;
}

/*
    Altera as dimencoes da matriz.
    > matrix: matriz a ter suas dimensoes alteradas
    > new_n_rows: novo numero de linhas
    > new_n_cols: novo numero de colunas
*/
Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){
   if (matrix.n_cols*matrix.n_rows != new_n_rows*new_n_cols){
        puts("in reshape: ");
        printf("Error: cannot reshape matrix of size %d into shape (%d, %d)\n", matrix.n_cols*matrix.n_rows, new_n_rows, new_n_cols);
        exit(1);
    }
 
    Matrix reshaped = {matrix.data, new_n_rows, new_n_cols, new_n_cols, matrix.stride_cols, matrix.offset};
    return reshaped;
}

/*
    Retorna um recorte da matriz.
    > rs: indice da linha inicial do recorte
    > re: indice da linha final do recorte
    > cs: indice da coluna inicial do recorte
    > ce: indice da coluna final do recorte
*/
Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce){
    if (rs<0 || cs<0 || re > a_matrix.n_rows || ce > a_matrix.n_cols){
        puts("in slice: ");
        puts("Error: index is out of bounds");
        exit(1);
    };

    Matrix sliced = {a_matrix.data, re-rs, ce-cs, a_matrix.stride_rows, a_matrix.stride_cols, a_matrix.offset + rs*a_matrix.stride_rows + cs*a_matrix.stride_cols};
    return sliced;
}

//>======================== agregacao: =========================

/*
    Retorna o menor elemento da matriz.
*/
int min(Matrix matrix){
    int min = matrix.data[matrix.offset];

    for (int row_index = 0; row_index < matrix.n_rows; row_index++)
        for (int col_index = 0; col_index < matrix.n_cols; col_index++)
            if (matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols] < min)
                min = matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols];

    return min;
}

/*
    Retorna o maior elemento da matriz.
*/
int max(Matrix matrix){
    int max = matrix.data[matrix.offset];

    for (int row_index = 0; row_index < matrix.n_rows; row_index++)
        for (int col_index = 0; col_index < matrix.n_cols; col_index++)
            if (matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols] > max)
                max = matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols];

    return max;
}

/*
    Retorna o indice do menor elemento da matriz.
    (O indice do elemento no array unidimencional que armazena os dados da matriz).
*/
int argmin(Matrix matrix){
    int min_index = matrix.offset, min = matrix.data[min_index];

    for (int row_index = 0; row_index < matrix.n_rows; row_index++)
        for (int col_index = 0; col_index < matrix.n_cols; col_index++)
            if (matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols] < min){
                min = matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols];
                min_index = matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols;
            }

    return min_index;
}

/*
    Retorna o indice do maior elemento da matriz.
    (O indice do elemento no array unidimencional que armazena os dados da matriz).
*/
int argmax(Matrix matrix){
    int max_index = matrix.offset, max = matrix.data[max_index];

    for (int row_index = 0; row_index < matrix.n_rows; row_index++)
        for (int col_index = 0; col_index < matrix.n_cols; col_index++)
            if (matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols] > max){
                max = matrix.data[matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols];
                max_index = matrix.offset + row_index*matrix.stride_rows + col_index*matrix.stride_cols;
            }

    return max_index;
}

//>================== operacoes aritmeticas: ===================

/*
    Adiciona duas matrizes elemento a elemento.
*/
Matrix add(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_cols != matrix_2.n_cols || matrix_1.n_rows != matrix_2.n_rows){
        puts("in add: ");
        printf("Error: operands of incompatible shape\n");
        exit(1);
    }

    int *data;
    data = malloc(matrix_1.n_cols*matrix_1.n_rows*sizeof(int));

    for (int i = matrix_1.offset; i < matrix_1.n_cols*matrix_1.n_rows; i++)
        *(data+i) = matrix_1.data[i] + matrix_2.data[i];

    return create_matrix(data, matrix_1.n_rows, matrix_1.n_cols);;
}

/*
    Subtrai duas matrizes elemento a elemento.
    > matrix_1: matriz minuendo
    > matrix_2: matriz subtraendo
*/
Matrix sub(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_cols != matrix_2.n_cols || matrix_1.n_rows != matrix_2.n_rows){
        puts("in sub: ");
        printf("Error: operands of incompatible shape\n");
        exit(1);
    }

    int *data;
    data = malloc(matrix_1.n_cols*matrix_1.n_rows*sizeof(int));

    for (int i=matrix_1.offset; i < matrix_1.n_cols*matrix_1.n_rows; i++)
        *(data+i) = matrix_1.data[i] - matrix_2.data[i];

    return create_matrix(data, matrix_1.n_rows, matrix_1.n_cols);
}

/*
    Divide duas matrizes elemento a elemento.
    Como a matriz é feita de um array de inteiros, a divisão sempre será intera.
    > matrix_1: matriz dividendo
    > matrix_2: matriz divisor
*/
Matrix division(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_cols != matrix_2.n_cols || matrix_1.n_rows != matrix_2.n_rows){
        puts("in division: ");
        printf("Error: operands of incompatible shape\n");
        exit(1);
    }

    int size = matrix_1.n_cols*matrix_1.n_rows;

    for (int i = 0; i<size; i++){
        if (matrix_2.data[i] == 0){
            puts("in division: ");
            printf("Error: cannot divide by 0\n");
            exit(1);
        }
    }

    int *data;
    data = malloc(size*sizeof(int));

    for (int i = matrix_1.offset; i < matrix_1.n_cols*matrix_1.n_rows; i++)
        *(data+i) = matrix_1.data[i] / matrix_2.data[i];

    return create_matrix(data, matrix_1.n_rows, matrix_1.n_cols);
}

/*
    Multiplica duas matrizes elemento a elemento.
*/
Matrix mul(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_cols != matrix_2.n_cols || matrix_1.n_rows != matrix_2.n_rows){
        puts("in mul: ");
        printf("Error: operands of incompatible shape\n");
        exit(1);
    }

    int *data;
    data = malloc(matrix_1.n_cols*matrix_1.n_rows*sizeof(int));

    for (int i=matrix_1.offset; i < matrix_1.n_cols*matrix_1.n_rows; i++)
        *(data+i) = matrix_1.data[i] * matrix_2.data[i];

    return create_matrix(data, matrix_1.n_rows, matrix_1.n_cols);
}