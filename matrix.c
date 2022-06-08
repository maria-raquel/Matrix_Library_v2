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
    int *data;
    data = malloc(n_rows*n_cols*sizeof(int));

    for (int i=0; i < n_rows*n_cols;)
        *(data+i++) = value;

    Matrix m = create_matrix(data, n_rows, n_cols);
    return m;
}

/*
    Cria uma matriz identidade.
    > n: valor das dimensoes (nxn) da matriz
*/
Matrix i_matrix(int n){
    int *data;
    data = malloc(n*n*sizeof(int));

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
    int *data, k = 0;
    data = malloc(matrix.n_cols*matrix.n_rows*sizeof(int)*reps);

    for (int l = 1; l < matrix.n_rows+1; l++){
        for (int j = 0; j < reps; j++){
            for (int i = 0 + (l-1)*matrix.stride_rows; i < matrix.stride_rows + (l-1)*matrix.stride_rows; i++){
                *(data + k) = matrix.data[i];
                k++;
            }
        }
    }
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

    if (ri >= matrix.n_rows || ci >= matrix.n_cols){
        puts("in get_element: ");
        printf("Error: index [%d][%d] is out of bounds\n", ri, ci);
        exit(1);
    }

    int i = matrix.offset;

    for (int row=0; row<ri; i += matrix.stride_rows, row++){}
    for (int col=0; col<ci; i += matrix.stride_cols, col++){}

    return matrix.data[i];
}

/*
    Modifica um elemento da matriz pela sua posicao.
    > matriz: matriz a ser acessada
    > ri: indice da linha do elemento
    > ci: indice da coluna do elemento
    > elem: valor novo do elemento
*/
void put_element(Matrix matrix, int ri, int ci, int elem){

    if (ri >= matrix.n_rows || ci >= matrix.n_cols){
        puts("in put_element: ");
        printf("Error: index [%d][%d] is out of bounds\n", ri, ci);
        exit(1);
    }

    int i = matrix.offset;

    for (int row=0; row<ri; i += matrix.stride_rows, row++){}
    for (int col=0; col<ci; i += matrix.stride_cols, col++){}

    matrix.data[i] = elem;
}

/*
    Exibe os dados da matriz em seu formato.
*/
void print_matrix(Matrix matrix){
    int i = matrix.offset;
    for (int row = 0; row < matrix.n_rows; row++){
        printf("( ");
        for (int col = 0; col < matrix.n_cols; col++)
            printf("%2d ", matrix.data[i++]);
        printf(")\n");
    }
}

//>================= manipulacao de dimensoes: =================

/*
    Retorna a matrix transposta da matriz.
*/
Matrix transpose(Matrix matrix){
    int *data = malloc((matrix.n_cols)*(matrix.n_rows)*sizeof(int)); 

    int cols_counter = 1, cols_resetter = 0;

    for (int i = 0, j = 0; i < matrix.n_cols*matrix.n_rows; i++){
        data[i] = matrix.data[j];
        j += matrix.stride_rows;
        cols_counter++;
        if (cols_counter > matrix.n_rows){
            cols_counter = 1;
            cols_resetter++;
            j = cols_resetter;
        }
    }

    return create_matrix(data, matrix.n_cols, matrix.n_rows);
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
        printf("Error: cannot reshape matrix of %d elements into shape (%d, %d)\n", matrix.n_cols*matrix.n_rows, new_n_rows, new_n_cols);
        exit(1);
    }

    return create_matrix(matrix.data, new_n_rows, new_n_cols);
}

/*
    Retorna um recorte da matriz.
    > rs: indice da linha inicial do recorte
    > re: indice da linha final do recorte
    > cs: indice da coluna inicial do recorte
    > ce: indice da coluna final do recorte
*/
Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce){
    Matrix m;
    int *data, new_n_cols = re-rs, new_n_rows = ce-cs;

    data = malloc((new_n_cols)*(new_n_rows)*sizeof(int)); 

    int i = 0;
    for (int x = 0; x < new_n_cols; x++)
        for (int y = 0; y < new_n_rows; y++)
            data[i++] = a_matrix.data[((rs+(x))*a_matrix.stride_rows) + ((cs+(y)) * a_matrix.stride_cols)];
    
    return create_matrix(data, new_n_cols, new_n_rows);
}

//>======================== agregacao: =========================

/*
    Retorna o menor elemento da matriz.
*/
int min(Matrix matrix){
    int min = matrix.data[matrix.offset];

    for (int i = matrix.offset+1; i < matrix.n_cols*matrix.n_rows; i++)
        if (matrix.data[i] < min)
            min = matrix.data[i];

    return min;
}

/*
    Retorna o maior elemento da matriz.
*/
int max(Matrix matrix){
    int max = matrix.data[matrix.offset];

    for (int i = matrix.offset+1; i < matrix.n_cols*matrix.n_rows; i++)
        if (matrix.data[i] > max)
            max = matrix.data[i];

    return max;
}

/*
    Retorna o indice do menor elemento da matriz.
    (O indice do elemento no array unidimencional que armazena os dados da matriz).
*/
int argmin(Matrix matrix){
    int index_min = matrix.offset, min = matrix.data[index_min];

    for (int i=matrix.offset+1; i < matrix.n_cols*matrix.n_rows; i++){
        if (matrix.data[i] < min){
            min = matrix.data[i];
            index_min = i;
        }
    }

    return index_min;
}

/*
    Retorna o indice do maior elemento da matriz.
    (O indice do elemento no array unidimencional que armazena os dados da matriz).
*/
int argmax(Matrix matrix){
    int index_max = matrix.offset, max = matrix.data[index_max];

    for (int i = matrix.offset+1; i < matrix.n_cols*matrix.n_rows; i++){
        if (matrix.data[i] > max){
            max = matrix.data[i];
            index_max = i;
        }
    }

    return index_max;
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