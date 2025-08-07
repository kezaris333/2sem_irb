#include <iostream>
#include <cmath>

class complex_num {
    double mnim;
    double valid;

public:

    complex_num(double mnim1 = 0, double valid1 = 0);

    complex_num operator+(const complex_num & other) const;
    complex_num operator+(double num) const;
    complex_num operator-(const complex_num & other) const;
    complex_num operator-(double num) const;
    complex_num operator*(const complex_num & other) const;
    complex_num operator*(double num) const;
    complex_num operator/(const complex_num & other) const;
    complex_num operator/(double num) const;

    complex_num& operator+=(const complex_num & other) ;
    complex_num& operator+=(double num) ;
    complex_num& operator-=(const complex_num & other) ;
    complex_num& operator-=(double num) ;
    complex_num& operator*=(const complex_num & other) ;
    complex_num& operator*=(double num) ;
    complex_num& operator/=(const complex_num & other) ;
    complex_num& operator/=(double num) ;

    double modul () const;
    double arg() const;

    friend std::ostream& operator<<(std::ostream& os, const complex_num& cn);
    friend std::istream& operator>>(std::istream& is, complex_num& cn);

};
