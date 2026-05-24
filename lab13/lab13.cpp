#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*
Задана система из M линейных уравнений с N неизвестными. Напишите функцию с параметрами
приведения матрицы этой системы к ступенчатому виду на основе метода Гаусса-Жордана. В комментариях
в исходном коде укажите, какие элементарные преобразования матриц использованы в методе Гаусса-Жордана.

Входные данные находятся в текстовом файле. В первой строке файла указано количество уравнений, затем
количество неизвестных. После этого следуют M строк коэффициентов и свободных членов уравнений.
В каждой строке N коэффициентов и свободный член определенного уравнения.

Результат выводится в текстовый файл в наглядном виде

Используя функцию приведения матрицы системы к ступенчатому виду, напишите программу, которая находит
единственное решение системы или сообщает, что такого решения нет.
*/

void gauss(double** matrix, int M, int N) {
    int row = 0;
    int col = 0;

    while (row < M && col < N) { // приведение к ступенчатому виду
		int max_row = row; // Поиск опорного элемента (максимального по модулю в текущем столбце)
        double max_val = fabs(matrix[row][col]);
        for (int i = row + 1; i < M; i++) {
            if (fabs(matrix[i][col]) > max_val) {
                max_val = fabs(matrix[i][col]);
                max_row = i;
            }
        }
        
        if (max_val < 1e-10) { // Если опорный элемент близок к нулю, переходим к следующему столбцу
            col++;
            continue;
        }
        
        if (max_row != row) { // перестановка строк
            for (int j = col; j <= N; j++) {
                double temp = matrix[row][j];
                matrix[row][j] = matrix[max_row][j];
                matrix[max_row][j] = temp;
            }
        }
        
        double pivot = matrix[row][col]; // умножение строки на число
        for (int j = col; j <= N; j++)
            matrix[row][j] /= pivot;
        
        // Вычитание из других строк текущей, умноженной на коэффициент
        for (int i = 0; i < M; i++) {
            if (i != row && fabs(matrix[i][col]) > 1e-10) {
                double factor = matrix[i][col];
                for (int j = col; j <= N; j++)
                    matrix[i][j] -= factor * matrix[row][j];
            }
        }
        row++;
        col++;
    }
}

void print_matrix_to_file(double** matrix, int M, int N, const char* filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    out << "Матрица в ступенчатом виде:" << endl;

    for (int i = 0; i < M; i++) { // Вывод коэффициентов
        for (int j = 0; j < N; j++) {
            if (fabs(matrix[i][j]) < 1e-10) {
                out << " 0 ";
            } else {
                out << " " << matrix[i][j] << " ";
            }
        }

        out << " | ";
        if (fabs(matrix[i][N]) < 1e-10) {
            out << " 0";
        } else {
            out << " " << matrix[i][N];
        }
        out << endl;
    }

    out.close();
}

int get_rank(double** matrix, int M, int N) {
    int rank = 0;
    for (int i = 0; i < M; i++) {
        bool all_zero = true;
        for (int j = 0; j < N; j++) {
            if (fabs(matrix[i][j]) > 1e-10) {
                all_zero = false;
                break;
            }
        }
        if (!all_zero)
			rank++;
    }
    return rank;
}

int main(int argc, char* argv[]) {
	argc = 1;
	const char* input_file = argv[1];
    const char* output_file = "../lab13/out.txt";
	cout << input_file << endl;
    
    ifstream in(input_file);
    if (!in) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }
    
    int M, N;
    in >> M >> N;
    
    if (M <= 0 || N <= 0) {
        cout << "Неверный размер матрицы" << endl;
        return 1;
    }
    
    // Расширенная матрица (M строк, N+1 столбцов)
    double** matrix = new double*[M];
    for (int i = 0; i < M; i++) {
        matrix[i] = new double[N + 1];
    }
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            in >> matrix[i][j];
        }
        in >> matrix[i][N]; // свободный член
    }
    in.close();
    
    gauss(matrix, M, N);

	print_matrix_to_file(matrix, M, N, output_file);
    
    int rank = get_rank(matrix, M, N);
    int rank_ext = get_rank(matrix, M, N + 1);
    
    ofstream out(output_file, ios::app); // app - режим добавления в конец потока
    out << "Ранг матрицы коэффициентов: " << rank << endl;
    out << "Ранг расширенной матрицы: " << rank_ext << "\n\n";
    
    if (rank != rank_ext) {
        out << "Нет решений" << endl;
    } else if (rank == N) {
        out << "Система имеет единственное решение:" << endl;
        for (int i = 0; i < min(M, N); i++) {
            out << "x" << i + 1 << " = ";
            if (fabs(matrix[i][N]) < 1e-10)
                out << "0";
            else
                out << matrix[i][N];
            out << endl;
        }
    } else {
        out << "Система имеет бесконечно много решений" << endl;
    }
    
    out.close();
    
    // Освобождение памяти
    for (int i = 0; i < M; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    return 0;
}
