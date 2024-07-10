/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/
#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <string>

class Complex {
// private by default    
    double _real;
    double _img;
public:
    // Constructors
    Complex(double real = 0.0, double img = 0.0) : _real(real), _img(img) {};     // inline constructor - defaults to 0, 0
    Complex(const Complex& c) : _real(c._real), _img(c._img) {};                    // copy constructor

    // Destructor
    ~Complex() = default;         // can be removed but its better practice to keep it

    // Getters - all inline for simplicity
    double getReal() const { return _real; }
    double getImg() const { return _img; }

    // Setters - all inline for simplicity
    void setReal(double real) { this->_real = real; }
    void setImg(double img) { this->_img = img; }

    // Getter & Setter - flexible using reference and non-const
    double& real() { return this->_real;}
    double& img() { return this->_img;}

    // Overloaded operators - not really required in assignment
    Complex operator+(const Complex& c) const {
        return Complex(_real + c._real, _img + c._img);
    }

    Complex operator-(const Complex& c) const {
        return Complex(_real - c._real, _img - c._img);
    }

    Complex operator*(const Complex& c) const {
        return Complex(_real * c._real - _img * c._img, _real * c._img + _img * c._real);
    }

    Complex operator/(const Complex& c) const {
        double denominator = c._real * c._real + c._img * c._img;
        return Complex((_real * c._real + _img * c._img) / denominator, (_img * c._real - _real * c._img) / denominator);
    }

    Complex& operator+=(const Complex& c) {
        _real += c._real;
        _img += c._img;
        return *this;
    }

    Complex& operator-=(const Complex& c) {
        _real -= c._real;
        _img -= c._img;
        return *this;
    }

    Complex& operator*=(const Complex& c) {
        double temp = _real;
        _real = _real * c._real - _img * c._img;
        _img = temp * c._img + _img * c._real;
        return *this;
    }

    Complex& operator/=(const Complex& c) {
        double denominator = c._real * c._real + c._img * c._img;
        double temp = _real;
        _real = (_real * c._real + _img * c._img) / denominator;
        _img = (_img * c._real - temp * c._img) / denominator;
        return *this;
    }

    Complex& operator=(const Complex& c) {
        _real = c._real;
        _img = c._img;
        return *this;
    }

    bool operator==(const Complex& c) const {
        return _real == c._real && _img == c._img;
    }

    bool operator!=(const Complex& c) const {
        return _real != c._real || _img != c._img;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c._real << "+";
        if (c._img != 1 && c._img != 0){
            os << c._img;
        }
        os << "i";
        return os;
    }

    // Conversion functions
    operator double() const { return _real; }

    // to string
    operator std::string() const { return to_string(); }
    std::string to_string() const { 
        return std::to_string(_real)+"+"+std::to_string(_img)+"i";
    }
};

#endif // COMPLEX_HPP