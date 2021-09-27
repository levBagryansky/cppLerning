#pragma once
#include "iostream"

struct ComplexNum{
    double real_;
    double im_;

    ComplexNum(double real, double im);
    ComplexNum(const ComplexNum& another);
    ComplexNum();

    ComplexNum FindConjugate() const;
    double AbsSquare() const;

    ComplexNum operator+(const ComplexNum &other) const;
    ComplexNum operator+(double x) const;
    ComplexNum operator-(const ComplexNum &other) const;
    ComplexNum operator-(double x) const;
    ComplexNum operator*(const ComplexNum &other) const;
    ComplexNum operator*(double k) const;
    ComplexNum operator/(const ComplexNum &other) const;
    ComplexNum operator/(double k) const;
    bool operator==(const ComplexNum &other) const;
    std::ostream& operator<< (std::ostream& os);
    std::istream& operator>> (std::istream& is);
};