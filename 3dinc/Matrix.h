#ifndef MATRIX_H
#define MATRIX_H

//#include <iostream>
//#include <random>
//#include <ctime>
//#include <cmath>

//using namespace std;

template <typename Cell = double>
class Matrix;


// Индексация с 1
// Класс для работы с квадратными и прямоугольными матрицами
template <typename Cell>
struct Matrix
{
protected:
    // rows - строка
    // cols - столбец
    int rows, cols;

    // матрица размера ROWxCOLUMN
    Cell **cells;

    void AllocateCells(int rows, int cols);     // Выделение памяти
    void FreeCells();                           // Очистка

    double randomDouble(int left, int right);   // случайное double число из диапазона

public:
    Matrix() : rows(0), cols(0), cells(nullptr){}		    // Конструктор по умолчанию

    Matrix(const Matrix&);					                // Конструктор копирования
    Matrix(int rows, int cols);					            // Конструктор нулевой матрицы
    explicit Matrix(int rows);					            // Конструктор нулевой квадратной матрицы
    Matrix(int rows, int cols, Cell* list);					// Конструктор матрицы из списка
    Matrix(int rows, Cell* list);                           // Конструктор квадратной матрицы из списка
    ~Matrix();								                // Деструктор

    inline Cell& operator() (int i, int j) { return cells[i-1][j-1]; }             // получение элемента
    inline void operator() (int i, int j, Cell data) { cells[i-1][j-1] = data; }   // установка элемента

    int getRows() const;
    int getCols() const;

    Matrix<Cell> getTranspose();    // вернет транспонированную матрицу
    void transpose();             // транспонирование матрицы
    double norm();                  // норма вектора sqrt(sum (x[i]*x[i]))

    operator double();                      // функция приведения к типу double
    Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
    Matrix  operator + (const Matrix&);		// Сложение матриц
    Matrix  operator - (const Matrix&);		// Вычитание матриц
    Matrix  operator - (double num);		// Вычитание числа из матрицы
    Matrix  operator * (const Matrix&);		// Умножение матриц
    Matrix  operator * (double num);        // Умножение матрицы на число
};

// Конструктор копирования
template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
    //FreeCells();
    AllocateCells(M.rows, M.cols);
    for (int i=0; i < rows; i++)
        for (int j=0; j < cols; j++)
            cells[i][j] = M.cells[i][j];
}

// Конструктор нулевой матрицы
template <typename Cell>
Matrix<Cell>::Matrix(int rows, int cols)
{
    AllocateCells(rows, cols);
    for (int i=0; i < rows; i++)
        for (int j=0; j < cols; j++)
            cells[i][j] = 0;
}

// Конструктор нулевой квадратной матрицы
template <typename Cell>
Matrix<Cell>::Matrix(int rows)
{
    AllocateCells(rows, rows);
    for (int i=0; i < rows; i++)
        for (int j=0; j < rows; j++)
            cells[i][j] = 0;
}

// Конструктор матрицы из списка
template <typename Cell>
Matrix<Cell>::Matrix(int rows, int cols, Cell* list)
{
    AllocateCells(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cells[i][j] = list[cols*i + j];
}

// Конструктор квадратной матрицы из списка
template <typename Cell>
Matrix<Cell>::Matrix(int rows, Cell* list)
{
    AllocateCells(rows, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            cells[i][j] = list[rows*i + j];
}

// Деструктор
template <typename Cell>
Matrix<Cell>::~Matrix()
{
    FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
    if (rows != M.rows || cols != M.cols)
    {
        FreeCells();
        AllocateCells(M.rows, M.cols);
    }
    for (int i=0; i<rows; i++)
        for (int j=0; j<cols; j++)
            cells[i][j] = M.cells[i][j];
    return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
    Matrix<Cell> res(*this);
    if (rows == M.rows && cols == M.cols)
        for (int i=0; i < rows; i++)
            for (int j=0; j < cols; j++)
                res.cells[i][j] += M.cells[i][j];

    return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
    Matrix<Cell> res(*this);
    if (rows == M.rows && cols == M.cols)
        for (int i=0; i < rows; i++)
            for (int j=0; j < cols; j++)
                res.cells[i][j] -= M.cells[i][j];
    else
    if (M.cols == 1 && M.rows) // если в другой матрице одна ячейка
        return (*this).operator-(M.cells[0][0]);

    return res;
}

template<typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(double num)
{
    Matrix<Cell> res(*this);
    for (int i=0; i < rows; i++)
        for (int j=0; j < cols; j++)
            res.cells[i][j] -= num;

    return res;
}

// UPD global FIX
template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
    Matrix<Cell> res(rows, M.cols);

    if ( cols == M.rows ) // число столбцов = числу строк у матриц
        for (int i=0; i < rows; i++)
            for (int j = 0; j < M.cols; j++)
                for (int k = 0; k < cols; k++)
                    res.cells[i][j] += this->cells[i][k] * M.cells[k][j];
    else
        if (M.rows == 1 && M.cols == 1) // если в другой матрице одна ячейка
            return (*this).operator*(M.cells[0][0]);

    return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(double num)
{
    Matrix<Cell> res(*this);

    for (int i=0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res.cells[i][j] *= num;
    return res;
}

// Выделение памяти для матрицы
template <typename Cell>
void Matrix<Cell>::AllocateCells(int rows, int cols)
{
    cells = new Cell*[rows];
    for (int i=0; i < rows; i++)
        cells[i] = new Cell[cols];
    this->rows = rows;
    this->cols = cols;
}

// Освобождение памяти
template <typename Cell>
void Matrix<Cell>::FreeCells()
{
    if (cells)
    {
        for (int i=0; i < rows; i++)
            delete cells[i];
        delete[] cells;
    }
    rows = cols = 0;
}

// транспонированная матрица
template<typename Cell>
Matrix<Cell> Matrix<Cell>::getTranspose()
{
    // выделяем память для новой матрицы
    Matrix<Cell> trans(cols, rows);

    // транспонируем
    for (int i = 0; i < cols; ++i)
        for (int j = 0; j < rows; ++j)
            trans.cells[i][j] = cells[j][i];

    return trans;
}

template<typename Cell>
void Matrix<Cell>::transpose()
{
    cells = (this->getTranspose()).cells;

    int temp = rows;
    rows = cols;
    cols = temp;
    return;
}

// норма вектора (sqrt(sum x[i]*x[i]))
template<typename Cell>
double Matrix<Cell>::norm()
{
    double norm = 0;
    if (rows == 1)
        for (int i = 0; i < cols; i++)
            norm += cells[0][i]*cells[0][i];
    else
    if (cols == 1)
        for (int i = 0; i < rows; i++)
            norm += cells[i][0]*cells[i][0];

    return norm; //sqrt(norm); нет sqrt!!!
}

template<typename Cell>
Matrix<Cell>::operator double() {
    return (rows == 1 && cols == 1) ? cells[0][0] : 0;
}

template<typename Cell>
int Matrix<Cell>::getRows() const {
    return rows;
}

template<typename Cell>
int Matrix<Cell>::getCols() const {
    return cols;
}

#endif // MATRIX_H
