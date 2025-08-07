//Реализовать класс комплексного числа. В классе определить и реализовать:
//● поля, соответствующие действительной и мнимой части комплексного числа (типа double)
//● конструктор, который принимает значения действительной и мнимой части (оба параметра по умолчанию
//        равны 0)
//● операторные методы, производящие операции сложения, вычитания, умножения и деления комплексных
//чисел (с модификацией и без модификации вызывающего объекта: +=/+, ...)
//● метод, возвращающий модуль комплексного числа
//● метод, возвращающий аргумент комплексного числа
//● перегруженный оператор вставки в поток
//● перегруженный оператор выгрузки из потока
//        Продемонстрируйте работу реализованного функционала


#include "complex_num.h"

complex_num::complex_num(double valid1, double mnim1) : valid(valid1), mnim(mnim1) {}


complex_num complex_num::operator+(const complex_num &other) const {
    complex_num result(0.0, 0.0);
    result.mnim = this->mnim + other.mnim;
    result.valid = this->valid + other.valid;
    return result;
}

complex_num complex_num::operator+(double num) const {
    complex_num result(0.0, 0.0);
    result.mnim = this->mnim;
    result.valid = this->valid + num;
    return result;
}

complex_num complex_num::operator-(const complex_num &other) const {
    complex_num result(0.0, 0.0);
    result.mnim = this->mnim - other.mnim;
    result.valid = this->valid - other.valid;
    return result;
}

complex_num complex_num::operator-(double num) const {
    complex_num result(0.0, 0.0);
    result.mnim = this->mnim;
    result.valid = this->valid - num;
    return result;
}

//(a+bi)*(c+di) = (ac-bd)+(ad+bc)i
complex_num complex_num::operator*(const complex_num &other) const {
    complex_num result(0.0, 0.0);
    result.mnim = this->valid * other.mnim + this->mnim * other.valid;
    result.valid = (this->valid * other.valid) - (this->mnim * other.mnim);
    return result;
}

complex_num complex_num::operator*(double num) const {
    complex_num result(0.0, 0.0);
    result.mnim = this->mnim * num;
    result.valid = this->valid * num;
    return result;
}

complex_num complex_num::operator/(const complex_num &other) const {
    complex_num result(0.0, 0.0);
    result.mnim = ((this->mnim * other.valid) - (this->valid * other.mnim)) /
                  ((other.valid * other.valid + other.mnim * other.mnim));
    result.valid = ((this->valid * other.valid) + (this->mnim * other.mnim)) /
                   ((other.valid * other.valid + other.mnim * other.mnim));
    return result;
}

complex_num complex_num::operator/(double num) const {
    if (num == 0.0) {
        throw std::invalid_argument("zero!");
    }
    complex_num result(0.0, 0.0);
    result.mnim = this->mnim / num;
    result.valid = this->valid / num;
    return result;
}


complex_num &complex_num::operator+=(const complex_num &other) {
    valid += other.valid;
    mnim += other.mnim;
    return *this;
}

complex_num &complex_num::operator+=(double num) {
    valid += num;
    return *this;
}

complex_num &complex_num::operator-=(const complex_num &other) {
    valid -= other.valid;
    mnim -= other.mnim;
    return *this;
}

complex_num &complex_num::operator-=(double num) {
    valid -= num;
    return *this;
}

complex_num &complex_num::operator*=(const complex_num &other) {
    this->mnim = this->valid * other.mnim + this->mnim * other.valid;
    this->valid = (this->valid * other.valid) - (this->mnim * other.mnim);
    return *this;
}

complex_num &complex_num::operator*=(double num) {

    this->mnim *= num;
    this->valid *= num;
    return *this;
}

complex_num &complex_num::operator/=(const complex_num &other) {
    double denominator = other.valid * other.valid + other.mnim * other.mnim;
    if (denominator == 0.0) {
        throw std::invalid_argument("zero!");
    }
    double new_real = (valid * other.valid + mnim * other.mnim) / denominator;
    double new_imag = (mnim * other.valid - valid * other.mnim) / denominator;
    valid = new_real;
    mnim = new_imag;
    return *this;
}

complex_num &complex_num::operator/=(double num) {
    if (num == 0.0) {
        throw std::invalid_argument("zero!");
    }
    this->mnim /= num;
    this->valid /= num;
    return *this;
}


double complex_num::modul() const {
    double temp = valid * valid + mnim * mnim;
    double modul_num = sqrt(temp);
    return modul_num;
}

double complex_num::arg() const  {
    if ((valid == 0.0) && (mnim == 0.0)) {
        throw std::runtime_error("Argument is undefined");
    }
    return atan2(mnim, valid);
}


#include <iostream>

 std::ostream& operator<<(std::ostream& os, const complex_num& cn) {
    os << cn.valid;

    if (cn.mnim >= 0) {
        os << " + " << cn.mnim << "i";
    } else {
        os << " - " << -cn.mnim << "i";
    }

    return os;
}


std::istream& operator>>(std::istream& is, complex_num& cn) {
    char plus_minus, i_symbol;
    double real, imag;

    //"a + bi" или "a - bi"
    is >> real >> plus_minus >> imag >> i_symbol;

    if (i_symbol != 'i') {
        is.setstate(std::ios::failbit);
        return is;
    }

    //знак мним част
    if (plus_minus == '+') {
        cn.valid = real;
        cn.mnim = imag;
    }
    else if (plus_minus == '-') {
        cn.valid = real;
        cn.mnim = -imag;
    }
    else {
        is.setstate(std::ios::failbit);
    }

    return is;
}



    int main() {

        complex_num a(3.0, 4.0);
        complex_num b(1.0, -2.0);

        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;

        std::cout << "a + b = " << a + b << std::endl;
        std::cout << "a - b = " << a - b << std::endl;
        std::cout << "a * b = " << a * b << std::endl;
        std::cout << "a / b = " << a / b << std::endl;

        complex_num c = a;
        c += b;
        std::cout << "a += b → " << c << std::endl;

        c = a;
        c -= b;
        std::cout << "a -= b → " << c << std::endl;

        std::cout << "|a| = " << a.modul() << std::endl;
        std::cout << "arg(a) = " << a.arg() << " radians" << std::endl;

        complex_num d;
        std::cout << "Enter complex number (format: a + bi or a - bi): ";
        std::cin >> d;

        return 0;
    }



