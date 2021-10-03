#include "ComplexNum.hpp"

ComplexNum::ComplexNum(double new_real, double new_im): real(new_real), im(new_im) {}

ComplexNum::ComplexNum(const ComplexNum& another): real(another.real), im(another.im){}

ComplexNum::ComplexNum(): real(0), im(0){}

ComplexNum::~ComplexNum() {
    real = 0;
    im = 0;
}
//Найти сопряженное
ComplexNum ComplexNum::conjugate() const{
    return ComplexNum(real, -im);
}
double ComplexNum::AbsSquare() const{
    return real * real - im * im;
}

ComplexNum& ComplexNum::operator=(const ComplexNum& other){
    im = other.im;
    real = other.real;

    return *this;
}

ComplexNum ComplexNum::operator+(const ComplexNum &other) const{
    return ComplexNum(real + other.real, im + other.im);
}

ComplexNum ComplexNum::operator+(double x) const{
    return ComplexNum(real + x, im);
}

ComplexNum ComplexNum::operator-(const ComplexNum &other) const{
    return ComplexNum(real - other.real, im - other.im);
}

ComplexNum ComplexNum::operator-(double x) const{
    return ComplexNum(real - x, im);
}

ComplexNum ComplexNum::operator-() const{
    return ComplexNum(-real, -im);
}

ComplexNum ComplexNum::operator*(const ComplexNum &other) const{
    return ComplexNum(real * other.real - im * other.im,
                      im * other.real + real * other.im);
}

ComplexNum ComplexNum::operator*(double k) const{
    return ComplexNum(real * k, im * k);
}

ComplexNum ComplexNum::operator/(const ComplexNum &other) const{
    ComplexNum res(*this);
    res.operator*(other.conjugate());
    res.operator*(1/other.AbsSquare());

    return res;
}

ComplexNum ComplexNum::operator/(double k) const{
    return ComplexNum(real / k, im / k);
}

bool ComplexNum::operator==(const ComplexNum &other) const{
    if (abs(this->im - other.im) < 0.0000001 && abs(real - other.real) < 0.0000001)
        return true;
    return false;
}

std::ostream& operator<< (std::ostream& os, const ComplexNum& z){
    if (z.im < 0)
        os << z.real << " - " << -z.im << 'i';
    else if (z.im > 0)
        os << z.real << " + " << z.im << 'i';
    else
        os << z.real;
    return os;
}

ComplexNum& ComplexNum::operator+=(const ComplexNum& other){
    im += other.im;
    real += other.real;

    return *this;
}

ComplexNum& ComplexNum::operator+=(double x){
    real += x;
    return *this;
}

ComplexNum& ComplexNum::operator-=(const ComplexNum& other){
    real -= other.real;
    im -= other.im;
    return *this;
}

ComplexNum& ComplexNum::operator-=(double x){
    real -= x;
    return *this;
}

ComplexNum& ComplexNum::operator*=(const ComplexNum& other){
    operator=(operator*(other));
    return *this;
}

ComplexNum& ComplexNum::operator*=(double x){
    operator=(operator*(x));
    return *this;
}