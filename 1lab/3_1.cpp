#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
   
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}


    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex& operator*=(const Complex& other) {
        double newReal = real * other.real - imag * other.imag;
        double newImag = real * other.imag + imag * other.real;
        real = newReal;
        imag = newImag;
        return *this;
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                        real * other.imag + imag * other.real);
    }

    Complex& operator/=(const Complex& other) {
        double denom = other.real * other.real + other.imag * other.imag;
        if (denom == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        double newReal = (real * other.real + imag * other.imag) / denom;
        double newImag = (imag * other.real - real * other.imag) / denom;
        real = newReal;
        imag = newImag;
        return *this;
    }

    Complex operator/(const Complex& other) const {
        double denom = other.real * other.real + other.imag * other.imag;
        if (denom == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        return Complex((real * other.real + imag * other.imag) / denom,
                       (imag * other.real - real * other.imag) / denom);
    }


    double Modulus() const {
        return std::sqrt(real * real + imag * imag);
    }


    double Argument() const {
        return std::atan2(imag, real);
    }

    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    
    friend std::istream& operator>>(std::istream& is, Complex& c);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << ", " << c.imag << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}

int main() {
    Complex c1(2.0, 3.0);
    Complex c2(1.0, 4.0);

    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;

    std::cout << "c1 + c2 = " << c1 + c2 << std::endl;
    std::cout << "c1 - c2 = " << c1 - c2 << std::endl;
    std::cout << "c1 * c2 = " << c1 * c2 << std::endl;
    std::cout << "c1 / c2 = " << c1 / c2 << std::endl;

    std::cout << "Modulus of c1 = " << c1.Modulus() << std::endl;
    std::cout << "Argument of c1 = " << c1.Argument() << std::endl;

    return 0;
}
