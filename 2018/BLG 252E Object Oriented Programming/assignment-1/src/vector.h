/*
 * vector.h
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */

class Vector{
    private:
        int size;
        double* contents;
        static int vector_count;
        int id;
    public:
        Vector();
        Vector(int&, double*);
        Vector(const Vector&);
        int get_size() const;
        double get_content(int) const;
        Vector operator+(const Vector&);
        double operator*(const Vector&);
        Vector operator*(const double&);
        Vector& operator=(const Vector&);

        ~Vector();
        int get_vector_count() const {return vector_count;}
        int get_id() const {return id;}
};