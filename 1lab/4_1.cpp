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

#include <iostream>
#include <cmath>

class matrix {
    double **matr;
    //память
    size_t size_column;
    size_t size_line;
public:
    matrix(size_t str, size_t column) : size_line(str), size_column(column) {
        //выделение памяти
        matr = new double *[str];

        for (size_t i = 0; i < str; ++i) {
            matr[i] = new double[column];
        }

        //присваивание 0

        for (size_t i = 0; i < size_line; i++) {
            for (size_t j = 0; j < size_column; i++) {
                matr[i][j] = 0;
            }
        }
    }


    // операторные методы, осуществляющие сложение матриц, умножение матриц, умножение матрицы на
    //         число, умножение числа на матрицу, вычитание матриц

    matrix operator+(matrix const &two) const {

        if (size_column != two.size_column && size_line != two.size_line) {
            //поймать ошибку
        }

        matrix new_matrix(size_line, size_column);

        for (int i = 0; i < size_line; i++) {
            for (int j = 0; j < size_column; j++) {
                new_matrix.matr[i][j] = matr[i][j] + two.matr[i][j];
            }
        }
        return (new_matrix);
    }


//если число столбцов в первом сомножителе равно числу строк во втором
    matrix operator*(matrix const &two) const {
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
            //ошибка
        }

    }


//умножение матрицы на число

    matrix operator*(double value) const {
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
    friend matrix operator*(double baaaabyyybeeee, matrix &babybe);


    //вычитание матриц
    matrix operator-(matrix const &two) {
        if (size_column == two.size_column && size_line == two.size_line) {
            matrix new_matrix(size_line, size_line);
            for (int i = 0; i < size_line; i++) {
                for (int j = 0; j < size_column; j++)
                    new_matrix.matr[i][j] = matr[i][j] - two.matr[i][j];
            }
            return (new_matrix);
        } else {
            //поймать ошибку
        }
    }


    //транспонирование - выловить ошибки
    matrix trans() {
        matrix new_matrix(size_line, size_column);

        for (int row = 0; row < size_line; row++) {
            for (int col = 0; col < size_column; col++) {
                new_matrix.matr[col][row] = matr[row][col]; //копируем значения с изменением индексов
            }
        }
        return (new_matrix);

    }


    //метод, возвращающий значение определителя матрицы, вычисленный при помощи метода Гаусса
    double computeDeterminant() {
        if (size_line != size_column) return 0; //не квадратная матрица

        double det = 1.0;
        const double eps = 1e-10; //точность для сравнения с нулём

        for (size_t i = 0; i < size_line; ++i) {
            //поиск ведущего элемента в столбце i
            size_t max_row = i;
            for (size_t k = i + 1; k < size_line; ++k) {
                if (std::abs(matr[k][i]) > std::abs(matr[max_row][i])) {
                    max_row = k;
                }
            }

            //если ведущий элемент нулевой матрица вырождена
            if (std::abs(matr[max_row][i]) < eps) {
                return 0.0;
            }

            //перестановка строк, если нужно
            if (max_row != i) {
                // Меняем строки местами
                for (size_t j = 0; j < size_column; ++j) {
                    double temp = matr[i][j];
                    matr[i][j] = matr[max_row][j];
                    matr[max_row][j] = temp;
                }
                det = -det; //при перестановке строк знак определителя меняется
            }

            //зануление элементов ниже ведущего
            for (size_t k = i + 1; k < size_line; ++k) {
                double factor = matr[k][i] / matr[i][i];
                for (size_t j = i; j < size_column; ++j) {
                    matr[k][j] -= factor * matr[i][j];
                }
            }
        }

        //вчисление определителя как произведения диагональных элементов
        for (size_t i = 0; i < size_line; ++i) {
            det *= matr[i][i];
        }

        return det;
    }






    //метод, возвращающий обратную матрицу

    //1/detA * на матрицу алг доп
    //найти матрицу миноров (-1)^i+j * Mij в месте Mij мы сначала вычеркиваем строки,
    // а потом находим определитель из оставшихся (n−1)×(n−1).

    matrix revers_matrix() {



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


};



    matrix operator*(double baaaabyyybeeee, matrix &babybe) { //свапать нельзя
        return (babybe * baaaabyyybeeee);
    }


    int main() {
        matrix minamina (10, 10);
        minamina. []
        minamina.
        std::cout << " " << std::endl;
        return 0;
    }
