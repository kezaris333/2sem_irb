/*Реализовать класс матрицы с вещественными значениями. В классе определить и реализовать:
● поля для хранения элементов матрицы в динамической памяти (типа double **) и размерностей матрицы
(типа size_t)
● конструктор, инициализирующий состояние матрицы на основе размерностей, с заполнением всех
элементов значением 0
● операторные методы, осуществляющие сложение матриц, умножение матриц, умножение матрицы на
число, умножение числа на матрицу, вычитание матриц
● метод, возвращающий транспонированную матрицу
● метод, возвращающий значение определителя матрицы, вычисленный при помощи метода Гаусса
● метод, возвращающий обратную матрицу
● * перегруженный оператор [], возвращающий значение элемента по его индексам строки и столбца
(индексирование начинается с 0), с возможностью модификации возвращённого элемента в вызывающем
коде
В случае невозможности её вычисления, должна быть сгенерирована исключительная ситуация типа, nested по
отношению к типу матрицы.
Продемонстрируйте работу реализованного функционала*/

//STR COLUM

#include "matr.h"


//конструктор
matrix::matrix(size_t str, size_t column) : size_line(str), size_column(column) {
    //выделение памяти
    matr = new double *[str];

    for (size_t i = 0; i < str; ++i) {
        matr[i] = new double[column];
    }

    //присваивание 0

    for (size_t i = 0; i < size_line; i++) {
        for (size_t j = 0; j < size_column; j++) {
            matr[i][j] = 0;
        }
    }
}


matrix::~matrix() {
    for (size_t i = 0; i < size_line; i++) {
        delete[] matr[i];
    }
    delete[] matr;
}

//this - pointer on class, на адрес
//*this - сам объект



//конструктор копирования - новый объект как копия существующего
matrix::matrix(const matrix &other) : size_line(other.size_line), size_column(other.size_column) {

    matr = new double *[size_line];
//копирование данных и выделение памяти
    for (size_t i = 0; i < size_line; i++) {
        matr[i] = new double[size_column];
        for (size_t j = 0; j < size_column; j++) {
            matr[i][j] = other.matr[i][j];

        }
    }
}


//оператор присваивания копированием - существующий объект копируем
matrix &matrix::operator=(const matrix &other) {
    if (this == &other)
        return *this;

    //освобождаем старую память
    for (size_t i = 0; i < size_line; i++) {
        delete[] matr[i]; //удаляем каждую строку, это double* (строка матрицы)
    }
    delete[] matr; //удаляем массив указателей


    size_column = other.size_column;
    size_line = other.size_line;
    matr = new double *[size_line];

    for (size_t i = 0; i < size_line; i++) {
        matr[i] = new double[size_column];
        for (size_t j = 0; j < size_column; j++) {
            matr[i][j] = other.matr[i][j];
        }
    }

    return *this;

}





// операторные методы, осуществляющие сложение матриц, умножение матриц, умножение матрицы на
//         число, умножение числа на матрицу, вычитание матриц

matrix matrix::operator+(matrix const &two) const {

    if (size_column != two.size_column || size_line != two.size_line) {
        throw std::invalid_argument("неподходящий разщмер для сложения");
    }

    matrix new_matrix(size_line, size_column);

    for (size_t i = 0; i < size_line; i++) {
        for (size_t j = 0; j < size_column; j++) {
            new_matrix.matr[i][j] = matr[i][j] + two.matr[i][j];
        }
    }
    return (new_matrix);
}


//если число столбцов в первом сомножителе равно числу строк во втором
matrix matrix::operator*(matrix const &two) const {
    if (size_column != two.size_line) {
        throw std::invalid_argument("неверный аргумент для унож");
    }

    matrix new_matrix(size_line, two.size_column);

    if (size_column == two.size_line) {
        for (size_t i = 0; i < size_line; i++) {
            for (size_t j = 0; j < two.size_column; j++) {
                new_matrix.matr[i][j] = 0;
                for (size_t k = 0; k < size_column; k++) {
                    new_matrix.matr[i][j] += matr[i][k] * two.matr[k][j];//почему +=
                }
            }
        }
        return (new_matrix);
    } else {
        throw std::invalid_argument("Invalid matrix dimensions for multiplication"); //ИСПРАВЛЕНО - добавлено исключение
    }

}


//умножение матрицы на число

matrix matrix::operator*(double value) const {
    double val = value;
    matrix new_matrix(size_line, size_column);
    for (size_t j = 0; j < size_line; j++) {
        for (size_t i = 0; i < size_column; i++) {
            new_matrix.matr[j][i] = matr[j][i] * val;
        }
    }
    return (new_matrix);
}


//умножение числа на матрицу
matrix operator*(double baaaabyyybeeee, matrix &babybe);


//вычитание матриц
matrix matrix::operator-(matrix const &two) {
    if (size_column == two.size_column && size_line == two.size_line) {
        matrix new_matrix(size_line, size_column);
        for (size_t i = 0; i < size_line; i++) {
            for (size_t j = 0; j < size_column; j++)
                new_matrix.matr[i][j] = matr[i][j] - two.matr[i][j];
        }
        return (new_matrix);
    } else {
        throw std::invalid_argument("бебебабаба разность проверь");
    }
}


//транспонирование - выловить ошибки
matrix matrix::trans() {
    matrix new_matrix(size_column, size_line);

    for (size_t row = 0; row < size_line; row++) {
        for (size_t col = 0; col < size_column; col++) {
            new_matrix.matr[col][row] = matr[row][col]; //копируем значения с изменением индексов
        }
    }
    return (new_matrix);

}


//метод, возвращающий значение определителя матрицы, вычисленный при помощи метода Гаусса
double matrix::computeDeterminant() const {
    if (size_line != size_column)
        throw std::invalid_argument("матрица не квадратная, опередеитель");


    matrix temp(*this);

    double det = 1.0;
    const double eps = 1e-10; //точность для сравнения с нулём

    for (size_t i = 0; i < temp.size_line; ++i) {
        //поиск ведущего элемента в столбце i
        size_t max_row = i;
        for (size_t k = i + 1; k < temp.size_line; ++k) {
            if (std::abs(temp.matr[k][i]) > std::abs(temp.matr[max_row][i])) {
                max_row = k;
            }
        }

        //если ведущий элемент нулевой матрица вырождена
        if (std::abs(temp.matr[max_row][i]) < eps) {
            return 0.0;
        }

        //перестановка строк, если нужно
        if (max_row != i) {
            // Меняем строки местами
            for (size_t j = 0; j < temp.size_column; ++j) {
                double temp_val = temp.matr[i][j]; //ИСПРАВЛЕНО - переименована переменная temp
                temp.matr[i][j] = temp.matr[max_row][j];
                temp.matr[max_row][j] = temp_val;
            }
            det = -det; //при перестановке строк знак определителя меняется
        }

        //зануление элементов ниже ведущего
        for (size_t k = i + 1; k < temp.size_line; ++k) {
            double factor = temp.matr[k][i] / temp.matr[i][i];
            for (size_t j = i; j < temp.size_column; ++j) {
                temp.matr[k][j] -= factor * temp.matr[i][j];
            }
        }
    }

    //вчисление определителя как произведения диагональных элементов
    for (size_t i = 0; i < temp.size_line; ++i) {
        det *= temp.matr[i][i];
    }

    return det;
}


double *matrix::operator[](size_t index) {
    if (index >= size_line) {
        throw std::out_of_range("Index out of range");
    }
    return matr[index];
}

const double *matrix::operator[](size_t index) const {
    if (index >= size_line) {
        throw std::out_of_range("Index out of range");
    }
    return matr[index];
}





//метод, возвращающий обратную матрицу

//1/detA * на матрицу алг доп
//найти матрицу миноров (-1)^i+j * Mij в месте Mij мы сначала вычеркиваем строки,
// а потом находим определитель из оставшихся (n−1)×(n−1).

matrix matrix::revers_matrix() {


    if (size_line != size_column) {
        throw std::logic_error("Matrix is not square");
    }

    // Вычисляем определитель
    double det = computeDeterminant();
    if (det == 0) {
        //ошибка
    }


    matrix cofactors(size_line, size_column);

    for (size_t i = 0; i < size_line; ++i) {
        for (size_t j = 0; j < size_column; ++j) {
            //создание матрицы без стрки и столбца
            matrix minor(size_line - 1, size_column - 1);

            //заполнение матриц минора
            for (size_t mi = 0, mii = 0; mi < size_line; ++mi) {
                if (mi == i) continue;  //пропуск строки ай
                for (size_t mj = 0, mjj = 0; mj < size_column; ++mj) {
                    if (mj == j) continue;  //столбца джей
                    minor.matr[mii][mjj] = matr[mi][mj];
                    ++mjj;
                }
                ++mii;
            }

            //алг доп
            double minor_det = minor.computeDeterminant();
            cofactors.matr[i][j] = ((i + j) % 2 ? -1 : 1) * minor_det;
        }
    }

    matrix adjugate = cofactors.trans();

    return adjugate * (1.0 / det);
}


matrix operator*(double baaaabyyybeeee, matrix &babybe) { //свапать нельзя
    return (babybe * baaaabyyybeeee);
}


int main() {
    matrix A(2, 2);
    matrix B(2, 2);

    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;

    B[0][0] = 2;
    B[0][1] = 1;
    B[1][0] = 1;
    B[1][1] = 3;

    matrix C = A + B;
    std::cout << "сложение выполнено\n";

    matrix D = A * B;
    std::cout << "умножение выполнено\n";

    // Определитель
    double det = A.computeDeterminant();
    std::cout << "определитель A: " << det << std::endl;

    // Обратная матрица
    matrix inv = A.revers_matrix();
    std::cout << "обратная матрица вычислена\n";


    return 0;
}
