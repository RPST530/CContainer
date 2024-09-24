// numbers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<ostream>
#include <iterator>
#include "CContainer.h"
using namespace std;
class Natural {
private:
    unsigned int value; 

public:
    Natural(unsigned int val) : value(val) {} 
    Natural() { value = 0; }

    unsigned int getValue() const { return value; } 

  
    Natural operator+(const Natural& other) const {
        return Natural(value + other.value);
    }

    Natural operator-(const Natural& other) const {
        if (value >= other.value) {
            return Natural(value - other.value);
        }
        else {
            return Natural(value + other.value);
        }
    }
    bool operator<=(const Natural& other) const {
        return value <= other.value;
    }
    bool operator>=(const Natural& other) const {
        return value >= other.value;
    }
    bool operator==(const Natural& other) const {
        return value == other.value;
    }
    bool operator!=(const Natural& other) const {
        return value != other.value;
    }
    bool operator<(const Natural& other) const {
        return value < other.value;
    }
    bool operator>(const Natural& other) const {
        return value > other.value;
    }

};

class Integer : public Natural {
private:
    bool isNegative; 

public:
    Integer(int val) : Natural(abs(val)), isNegative(val < 0) {};
    Integer() : Natural(0) { isNegative = false; };

    bool getIsNegative() const { return isNegative; } 

    Integer operator+(const Integer& other) const {
        int resultValue = getValue() + other.getValue();
        return Integer(resultValue);
    }

    Integer operator-(const Integer& other) const {
        int resultValue = getValue() - other.getValue();
        return Integer(resultValue);
    }

    Integer operator*(const Integer& other) const {
        int resultValue = getValue() * other.getValue();
        return Integer(resultValue);
    }

    Integer operator/(const Integer& other) const {
        if (other.getValue() != 0) {
            int resultValue = getValue() / other.getValue();
            return Integer(resultValue);
        }
        else
        {
            return Integer(0);
        }
    }
    bool operator<=(const Natural& other) const {
        int a = getValue();
        bool b = a <= other.getValue();
        if (a < 0 && !other.getValue() > 0)
            return true;
        if (a > 0 && other.getValue() < 0)
            return false;
        if (a < 0 && other.getValue() < 0)
            return !b;
        return b;
    }
    bool operator<(const Natural& other) const {
        int a = getValue();
        bool b = a < other.getValue();
        if (a < 0 && !other.getValue() > 0)
            return true;
        if (a > 0 && other.getValue() < 0)
            return false;
        if (a < 0 && other.getValue() < 0)
            return !b;
        return b;
    }
    bool operator>=(const Natural& other) const {
        int a = getValue();
        bool b = a >= other.getValue();
        if (a < 0 && !other.getValue() > 0)
            return false;
        if (a > 0 && other.getValue() < 0)
            return true;
        if (a < 0 && other.getValue() < 0)
            return b;
        return !b;
    }
    bool operator==(const Natural& other) const {
        int a = getValue();
        bool b = a == other.getValue();
        if ((a > 0 && other.getValue() > 0) or (a <= 0) and (other.getValue() <= 0))
            return b;
    }

    bool operator <<(Integer c)
    {
        std::cout << c.getValue();
    }
    friend std::ostream& operator<<(std::ostream& out, const Integer& i) {
        out << (i.isNegative ? "-" : "") << i.getValue();
        return out;
    }
};

class Real : public Integer {
private:
    Integer num;   
    Integer denom; 

public:
    Real(Integer n, Integer d) : Integer(n / d), num(n), denom(d) {  };
    Real() { num = Integer(0); denom = Integer(0); }
    Real operator+(const Real& other) const {
        Integer resultNum = (num * other.denom) + (other.num * denom);
        Integer resultDenom = denom * other.denom;
        return Real(resultNum, resultDenom);
    }

    Real operator-(const Real& other) const {
        Integer resultNum = (num * other.denom) - (other.num * denom);
        Integer resultDenom = denom * other.denom;
        return Real(resultNum, resultDenom);
    }

    Real operator*(const Real& other) const {
        Integer resultNum = num * other.num;
        Integer resultDenom = denom * other.denom;
        return Real(resultNum, resultDenom);
    }

    Real operator/(const Real& other) const {
        Integer resultNum = num * other.denom;
        Integer resultDenom = denom * other.num;
        return Real(resultNum, resultDenom);
    }
    Integer getNum()
    {
        return num;
    }
    Integer getDenom()
    {
        return denom;
    }

    bool operator<=(const Real& other) const {
        if (num <= other.num)
            return true;
        else
            return false;
    }

    bool operator>=(const Real& other) const {
        if (num >= other.num)
            return true;
        else
            return false;
    }

    bool operator<(const Real& other) const {
        if (num < other.num)
            return true;
        else
            return false;
    }
    bool operator>(const Real& other) const {
        if (num > other.num)
            return true;
        else
            return false;
    }

    bool operator==(const Real& other) const {
        if (num == other.num)
            return true;
        else
            return false;
    }
    friend std::ostream& operator<<(std::ostream& out, const Real& r) {
        out << r.num << "/" << r.denom;
        return out;
    }
};

class Complex : public Real{
private:
    Real real;     
    Real img;   

public:
    Complex(Real r, Real i) : Real(r), real(r), img(i) {};
    Complex() { real = Real(0, 0); img = Real(0, 0); }

    Complex operator+(const Complex& other) const {
        Real resultReal = real + other.real;
        Real resultImg = img + other.img;
        return Complex(resultReal, resultImg);
    }

    Complex operator-(const Complex& other) const {
        Real resultReal = real - other.real;
        Real resultImg = img - other.img;
        return Complex(resultReal, resultImg);
    }

    Complex operator*(const Complex& other) const {
        Real resultReal = real * other.real - img * other.img;
        Real resultImg = img * other.real + real * other.img;
        return Complex(resultReal, resultImg);
    }

    bool operator==(const Complex& other) const {
        return real == other.real && img == other.img;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    Real getReal()
    {
        return real;
    }
    Real getImg()
    {
        return img;
    }
    
    bool operator>=(const Complex& other) const {
        if (real >= other.real)
            return true;
    }
    bool operator<(const Complex& other) const {
        if (real < other.real)
            return true;
    }
    bool operator>(const Complex& other) const {
        if (real > other.real)
            return true;
    }
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real;
        if (c.img.getValue() >= 0)
            out << "+";
        out << c.img << "i";
        return out;
    }

};

int main()
{
    Real r(8,1);
    Real a(12, 1);
    Real r2(14, 1);
    Real a2(6, 1);
    Complex c(a, r);


    Complex c2(r2, a2);
    Complex c3;
    c3 = c * c2;
    CContainer<Complex, 20> arr;
    CContainer<Complex, 20> arr2;
    arr2.fill(c2);
    arr.fill(c3);
    arr.swap(arr2);
    arr[0] = c;
    arr = arr2;

    for (auto it = arr.begin(), end = arr.end(); it != end; ++it)
    {
        cout << *it << ", ";
    }
    cout << "\n" << arr.size();
    
}

