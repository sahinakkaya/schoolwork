/*
 * polynomial.h
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */


class Polynomial{
    private:
        int degree;
        double* contents;
        static int polynomial_count;
        int id;
    public:
        Polynomial();
        Polynomial(int&, double*);
        Polynomial(const Polynomial&);
        int get_degree() const;
        double get_content(int) const;
        Polynomial operator+(const Polynomial&);
        Polynomial operator*(const Polynomial&);
        Polynomial& operator=(const Polynomial&);

        ~Polynomial();
        int get_polynomial_count() const {return polynomial_count;}
        int get_id() const {return id;}
};