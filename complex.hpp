

class Complex {
// private by default    
    double real;
    double img;
public:
    // Constructors
    Complex(double real = 0.0, double img = 0.0) : real(real), img(img) {};     // inline constructor - defaults to 0, 0
    Complex(const Complex& c) : real(c.real), img(c.img) {};                    // copy constructor

    // Destructor
    ~Complex() = default;         // can be removed but its better practice to keep it

    // Getters - all inline for simplicity
    double get_real() const { return real; }
    double get_img() const { return img; }

    // Setters - all inline for simplicity
    void set_real(double real) { this->real = real; }
    void set_img(double img) { this->img = img; }

    // Getter & Setter - flexible using reference and non-const
    double& real() { return this->real;}
    double& real() { return this->img;}

    // Overloaded operators - not really required in assignment
    Complex operator+(const Complex& c) const {
        return Complex(real + c.real, img + c.img);
    }

    Complex operator-(const Complex& c) const {
        return Complex(real - c.real, img - c.img);
    }

    Complex operator*(const Complex& c) const {
        return Complex(real * c.real - img * c.img, real * c.img + img * c.real);
    }

    Complex operator/(const Complex& c) const {
        double denominator = c.real * c.real + c.img * c.img;
        return Complex((real * c.real + img * c.img) / denominator, (img * c.real - real * c.img) / denominator);
    }

    Complex& operator+=(const Complex& c) {
        real += c.real;
        img += c.img;
        return *this;
    }

    Complex& operator-=(const Complex& c) {
        real -= c.real;
        img -= c.img;
        return *this;
    }

    Complex& operator*=(const Complex& c) {
        double temp = real;
        real = real * c.real - img * c.img;
        img = temp * c.img + img * c.real;
        return *this;
    }

    Complex& operator/=(const Complex& c) {
        double denominator = c.real * c.real + c.img * c.img;
        double temp = real;
        real = (real * c.real + img * c.img) / denominator;
        img = (img * c.real - temp * c.img) / denominator;
        return *this;
    }

    Complex& operator=(const Complex& c) {
        real = c.real;
        img = c.img;
        return *this;
    }

    bool operator==(const Complex& c) const {
        return real == c.real && img == c.img;
    }

    bool operator!=(const Complex& c) const {
        return real != c.real || img != c.img;
    }

    // Conversion functions
    operator double() const { return real; }

    // to string
    operator std::string() const { return to_string(); }
    string to_string() const { 
        return std::to_string(real)+"+"+std::to_string(img)+"i";
    }
};