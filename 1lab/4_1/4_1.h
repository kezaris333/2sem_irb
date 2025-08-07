#include <iostream>
#include <cmath>
#include <stdexcept>


class matrix {
    double **matr;
    //память
    size_t size_column;
    size_t size_line;
public:
    matrix(size_t str, size_t column) : size_line(str), size_column(column);

    ~matrix();

    matrix(const matrix &other) : size_line(other.size_line), size_column(other.size_column);

    matrix &operator=(const matrix &other);

    matrix operator+(matrix const &two) const;


    matrix operator*(matrix const &two) const;

    matrix operator*(double value) const;

    friend matrix operator*(double baaaabyyybeeee, matrix &babybe);

    matrix operator-(matrix const &two);

    matrix trans();

    double computeDeterminant() const;

    double *operator[](size_t index);

    const double *operator[](size_t index) const;

    matrix revers_matrix();


};
