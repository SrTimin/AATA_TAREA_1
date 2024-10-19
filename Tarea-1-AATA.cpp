#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

// Clase para manejar las matrices
class Matrix {
private:
    int* data;
    int n;

public:
    Matrix(int size) : n(size) {
        data = (int*)malloc(size * size * sizeof(int));
        if (!data) {
            throw std::bad_alloc();
        }
    }

    ~Matrix() {
        free(data);
    }

    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;

    Matrix(Matrix&& other) noexcept : data(other.data), n(other.n) {
        other.data = nullptr;
    }

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            free(data);
            data = other.data;
            n = other.n;
            other.data = nullptr;
        }
        return *this;
    }

    int& at(int i, int j) {
        return data[i * n + j];
    }

    const int& at(int i, int j) const {
        return data[i * n + j];
    }

    int getSize() const { return n; }

    void copySubMatrix(const Matrix& src, int srcRow, int srcCol, int destRow, int destCol, int size) {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                at(destRow + i, destCol + j) = src.at(srcRow + i, srcCol + j);
            }
        }
    }
};

// Función para generar matrices aleatorias
Matrix generateRandomMatrix(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    Matrix matrix(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matrix.at(i, j) = dis(gen);
        }
    }
    return matrix;
}

// Método tradicional O(n^3)
Matrix traditionalMultiplication(const Matrix& A, const Matrix& B) {
    int n = A.getSize();
    Matrix C(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int sum = 0;
            for(int k = 0; k < n; k++) {
                sum += A.at(i, k) * B.at(k, j);
            }
            C.at(i, j) = sum;
        }
    }
    return C;
}

// Función auxiliar para sumar matrices
Matrix addMatrix(const Matrix& A, const Matrix& B, int size) {
    Matrix C(size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            C.at(i, j) = A.at(i, j) + B.at(i, j);
        }
    }
    return C;
}

// Función auxiliar para restar matrices
Matrix subtractMatrix(const Matrix& A, const Matrix& B, int size) {
    Matrix C(size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            C.at(i, j) = A.at(i, j) - B.at(i, j);
        }
    }
    return C;
}

// Método DR1
Matrix DR1(const Matrix& A, const Matrix& B) {
    int n = A.getSize();
    Matrix C(n);

    if(n == 1) {
        C.at(0, 0) = A.at(0, 0) * B.at(0, 0);
        return C;
    }

    int half = n/2;

    // Crear submatrices temporales
    Matrix A11(half), A12(half), A21(half), A22(half);
    Matrix B11(half), B12(half), B21(half), B22(half);
    Matrix C11(half), C12(half), C21(half), C22(half);

    // Copiar datos a submatrices
    for(int i = 0; i < half; i++) {
        for(int j = 0; j < half; j++) {
            A11.at(i, j) = A.at(i, j);
            A12.at(i, j) = A.at(i, j + half);
            A21.at(i, j) = A.at(i + half, j);
            A22.at(i, j) = A.at(i + half, j + half);

            B11.at(i, j) = B.at(i, j);
            B12.at(i, j) = B.at(i, j + half);
            B21.at(i, j) = B.at(i + half, j);
            B22.at(i, j) = B.at(i + half, j + half);
        }
    }

    // Calcular C11, C12, C21, C22
    Matrix temp1 = DR1(A11, B11);
    Matrix temp2 = DR1(A12, B21);
    C11 = addMatrix(temp1, temp2, half);

    temp1 = DR1(A11, B12);
    temp2 = DR1(A12, B22);
    C12 = addMatrix(temp1, temp2, half);

    temp1 = DR1(A21, B11);
    temp2 = DR1(A22, B21);
    C21 = addMatrix(temp1, temp2, half);

    temp1 = DR1(A21, B12);
    temp2 = DR1(A22, B22);
    C22 = addMatrix(temp1, temp2, half);

    // Combinar resultados
    for(int i = 0; i < half; i++) {
        for(int j = 0; j < half; j++) {
            C.at(i, j) = C11.at(i, j);
            C.at(i, j + half) = C12.at(i, j);
            C.at(i + half, j) = C21.at(i, j);
            C.at(i + half, j + half) = C22.at(i, j);
        }
    }

    return C;
}

// Método DR2 (Strassen)
Matrix DR2(const Matrix& A, const Matrix& B) {
    int n = A.getSize();
    Matrix C(n);

    if(n == 1) {
        C.at(0, 0) = A.at(0, 0) * B.at(0, 0);
        return C;
    }

    int half = n/2;

    // Crear submatrices
    Matrix A11(half), A12(half), A21(half), A22(half);
    Matrix B11(half), B12(half), B21(half), B22(half);

    // Copiar datos a submatrices
    for(int i = 0; i < half; i++) {
        for(int j = 0; j < half; j++) {
            A11.at(i, j) = A.at(i, j);
            A12.at(i, j) = A.at(i, j + half);
            A21.at(i, j) = A.at(i + half, j);
            A22.at(i, j) = A.at(i + half, j + half);

            B11.at(i, j) = B.at(i, j);
            B12.at(i, j) = B.at(i, j + half);
            B21.at(i, j) = B.at(i + half, j);
            B22.at(i, j) = B.at(i + half, j + half);
        }
    }

    // Cálculos de Strassen
    Matrix M1 = DR2(addMatrix(A11, A22, half), addMatrix(B11, B22, half));
    Matrix M2 = DR2(addMatrix(A21, A22, half), B11);
    Matrix M3 = DR2(A11, subtractMatrix(B12, B22, half));
    Matrix M4 = DR2(A22, subtractMatrix(B21, B11, half));
    Matrix M5 = DR2(addMatrix(A11, A12, half), B22);
    Matrix M6 = DR2(subtractMatrix(A21, A11, half), addMatrix(B11, B12, half));
    Matrix M7 = DR2(subtractMatrix(A12, A22, half), addMatrix(B21, B22, half));

    // Combinación final
    Matrix C11 = addMatrix(subtractMatrix(addMatrix(M1, M4, half), M5, half), M7, half);
    Matrix C12 = addMatrix(M3, M5, half);
    Matrix C21 = addMatrix(M2, M4, half);
    Matrix C22 = addMatrix(subtractMatrix(addMatrix(M1, M3, half), M2, half), M6, half);

    // Combinar resultados
    for(int i = 0; i < half; i++) {
        for(int j = 0; j < half; j++) {
            C.at(i, j) = C11.at(i, j);
            C.at(i, j + half) = C12.at(i, j);
            C.at(i + half, j) = C21.at(i, j);
            C.at(i + half, j + half) = C22.at(i, j);
        }
    }

    return C;
}

// Función para medir tiempos
void measureTime(int n) {
    Matrix A = generateRandomMatrix(n);
    Matrix B = generateRandomMatrix(n);

    auto start = chrono::high_resolution_clock::now();
    traditionalMultiplication(A, B);
    auto end = chrono::high_resolution_clock::now();
    auto traditional_duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    DR1(A, B);
    end = chrono::high_resolution_clock::now();
    auto dr1_duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    DR2(A, B);
    end = chrono::high_resolution_clock::now();
    auto dr2_duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "\nn = " << n << ":\n";
    cout << "Tradicional: " << traditional_duration << " ms\n";
    cout << "DR1: " << dr1_duration << " ms\n";
    cout << "DR2: " << dr2_duration << " ms\n";
}

int main() {
    // Medir tiempos para diferentes tamaños de matriz
    int sizes[] = {32, 64, 128, 256, 512, 1024, 2048, 4096};
    for(int n : sizes) {
        measureTime(n);
    }
    return 0;
}
