#include <iostream>
#include <fstream>
using namespace std;

/*
Упражнение 1. Неориентированный граф задан произвольной последовательностью ребер.
Исходные данные находятся в текстовом файле. Создайте матрицу смежности для неориентированного графа.
Выведите результат в отдельный текстовый файл.

Упражнение 2. Используя данные из текстового файла, полученного при выполнении упр. 1,
постройте массив номеров смежных вершин для неориентированного графа. Выведите результат в отдельный текстовый файл.

Упражнение 3. Используя данные из текстового файла, полученного при выполнении упр. 2,
сформируйте последовательность ребер неориентированного графа. Выведите результат в отдельный текстовый файл.
*/

void create_matrix(const char* filename, const char* outname)
{
    int** M, i, j, n, m, k;

	ifstream in(filename);
    if (!in) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    in >> n >> m; 

    // выделение памяти под матрицу n x n 
    M = new int* [n];
    for (i = 0; i < n; i++) {
        M[i] = new int[n];
        for (j = 0; j < n; j++)
            M[i][j] = 0;
    }

    // матрица смежности
    for (k = 0; k < m; k++) {
        in >> i >> j;
		i--; j--; // индексы -1
        M[i][j] = 1;
        M[j][i] = 1;
    }
    in.close();

    ofstream out(outname);
    out << n << "\n"; // размер матрицы
    for (i = 0; i < n; i++) { // содержимое
        for (j = 0; j < n; j++) {
            out << M[i][j] << " ";
        }
        out << "\n";
    }
    out.close();

    for (i = 0; i < n; i++)
		delete[] M[i];
	delete[] M;
}


void create_array(const char* filename, const char* outname)
{
    int** M, i, j, k, n;
    int* D;
	int* S;
	int* L;
	int* U;
    int m_total = 0; // количество ребер

	ifstream in(filename);
    if (!in) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    in >> n;

    M = new int* [n];
    for (i = 0; i < n; i++) {
        M[i] = new int[n];
        for (j = 0; j < n; j++) {
            in >> M[i][j];
            if (M[i][j] == 1)
				m_total++;
        }
    }
    in.close();

    D = new int[m_total];
    S = new int[n];
    L = new int[n];
    U = new int[n];

    for (j = 0; j < n; j++)
        L[j] = 0;

    for (i = 0; i < n; i++) { // подсчёт степеней вершин (сколько единиц в строке i)
        for (j = 0; j < n; j++)
            if (M[i][j] == 1) L[i]++;
    }

    S[0] = 0;
    for (j = 1; j < n; j++)
		S[j] = S[j - 1] + L[j - 1];

    for (j = 0; j < n; j++) // временный массив
		U[j] = S[j];

    for (i = 0; i < n; i++) { // все смежные вершины подряд
        for (j = 0; j < n; j++) {
            if (M[i][j] == 1) {
                k = i;
                D[U[k]] = j;
                U[k]++;
            }
        }
    }

    ofstream out(outname);
    out << n << " " << m_total << "\n";

    for (i = 0; i < n; i++)
		out << L[i] << " "; // степени вершин
    out << "\n";
    for (i = 0; i < n; i++)
		out << S[i] << " "; // индексы начала в D
    out << "\n";
    for (i = 0; i < m_total; i++)
		out << D[i] << " "; // смежные вершины
    out << "\n";
    out.close();

    for (i = 0; i < n; i++)
		delete[] M[i];
    delete[] M;
    delete[] D;
	delete[] S;
	delete[] L;
	delete[] U;
}


void create_edges(const char* filename, const char* outname)
{
    int* D;
	int* S;
	int* L;
    int n, m_total, i, j, k;

    ifstream in(filename);
    if (!in) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    in >> n >> m_total;

    L = new int[n];
    S = new int[n];
    D = new int[m_total];

    for (i = 0; i < n; i++)
        in >> L[i];
    for (i = 0; i < n; i++)
        in >> S[i];
    for (i = 0; i < m_total; i++)
        in >> D[i];
    in.close();

    ofstream out(outname);

    for (k = 0; k < n; k++) {
        for (i = S[k]; i <= S[k] + L[k] - 1; i++) {
            j = D[i];
            if (k < j)
            	out << (k + 1) << " " << (j + 1) << "\n"; // индексы +1, см. стр 41
        }
    }
    out.close();

    delete[] D;
    delete[] S;
    delete[] L;
}


int main()
{
    create_matrix("../lab14/in2.txt", "ex1.txt");
    create_array("ex1.txt", "ex2.txt");
    create_edges("ex2.txt", "ex3.txt");

    return 0;
}

