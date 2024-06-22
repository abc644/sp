//使用chatGPT生成

#include <stdio.h>
#include <stdlib.h>

// 矩陣結構體
typedef struct {
    int rows;
    int cols;
    double *data;
} Matrix;

// 創建矩陣
Matrix create_matrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double *)malloc(rows * cols * sizeof(double));
    return mat;
}

// 矩陣轉置
Matrix transpose(Matrix mat) {
    Matrix transposed = create_matrix(mat.cols, mat.rows);
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            transposed.data[j * transposed.cols + i] = mat.data[i * mat.cols + j];
        }
    }
    return transposed;
}

// 矩陣相加
Matrix add(Matrix mat1, Matrix mat2) {
    if (mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
        fprintf(stderr, "Matrix dimensions must agree for addition.\n");
        exit(EXIT_FAILURE);
    }
    Matrix result = create_matrix(mat1.rows, mat1.cols);
    for (int i = 0; i < mat1.rows * mat1.cols; ++i) {
        result.data[i] = mat1.data[i] + mat2.data[i];
    }
    return result;
}

// 矩陣相乘
Matrix multiply(Matrix mat1, Matrix mat2) {
    if (mat1.cols != mat2.rows) {
        fprintf(stderr, "Matrix dimensions must agree for multiplication.\n");
        exit(EXIT_FAILURE);
    }
    Matrix result = create_matrix(mat1.rows, mat2.cols);
    for (int i = 0; i < mat1.rows; ++i) {
        for (int j = 0; j < mat2.cols; ++j) {
            result.data[i * mat2.cols + j] = 0;
            for (int k = 0; k < mat1.cols; ++k) {
                result.data[i * mat2.cols + j] += mat1.data[i * mat1.cols + k] * mat2.data[k * mat2.cols + j];
            }
        }
    }
    return result;
}

// 矩陣打印
void dump(Matrix mat) {
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            printf("%f ", mat.data[i * mat.cols + j]);
        }
        printf("\n");
    }
}

// 矩陣釋放
void free_matrix(Matrix mat) {
    free(mat.data);
}

// 測試函式庫
int main() {
    // 創建矩陣
    Matrix mat1 = create_matrix(2, 2);
    mat1.data[0] = 1; mat1.data[1] = 2;
    mat1.data[2] = 3; mat1.data[3] = 4;

    Matrix mat2 = create_matrix(2, 2);
    mat2.data[0] = 5; mat2.data[1] = 6;
    mat2.data[2] = 7; mat2.data[3] = 8;

    // 轉置
    printf("Matrix 1 Transposed:\n");
    Matrix transposed = transpose(mat1);
    dump(transposed);
    free_matrix(transposed);

    // 相加
    printf("Matrix 1 + Matrix 2:\n");
    Matrix sum = add(mat1, mat2);
    dump(sum);
    free_matrix(sum);

    // 相乘
    printf("Matrix 1 * Matrix 2:\n");
    Matrix product = multiply(mat1, mat2);
    dump(product);
    free_matrix(product);

    // 釋放矩陣
    free_matrix(mat1);
    free_matrix(mat2);

    return 0;
}
