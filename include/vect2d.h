#include <cmath>

#ifndef VECT_H
#define VECT_H

class Vect2D {
    friend Vect2D operator*(double, const Vect2D&);
    friend Vect2D operator/(double, const Vect2D&);

   private:
    double x, y;

   public:
    Vect2D();
    Vect2D(double coord_x, double coord_y);
    Vect2D(const Vect2D& v);

    // getters

    double getX() const;
    double getY() const;
    Vect2D getXVect() const;
    Vect2D getYVect() const;

    // non-const edit functions with chain return

    Vect2D& set(double, double);
    Vect2D& add(const Vect2D&);
    Vect2D& rem(const Vect2D&);
    Vect2D& mult(double);
    Vect2D& div(double);
    Vect2D& min(Vect2D&);
    Vect2D& max(Vect2D&);
    Vect2D& normalize();
    Vect2D& setMagnitude(double);
    Vect2D& limit(const Vect2D&);
    Vect2D& limit(double s);

    // const edit functions with chain return

    Vect2D set(double, double) const;
    Vect2D add(const Vect2D&) const;
    Vect2D rem(const Vect2D&) const;
    Vect2D mult(double) const;
    Vect2D div(double) const;
    Vect2D min(const Vect2D&) const;
    Vect2D max(const Vect2D&) const;
    Vect2D normalize() const;
    Vect2D setMagnitude(double) const;
    Vect2D limit(const Vect2D&) const;
    Vect2D limit(double s) const;
    double mag() const;
    double dot(const Vect2D& v) const;
    double distance(const Vect2D& v) const;
    double angleBetween(const Vect2D& v) const;
    Vect2D scalarProjection(const Vect2D& v) const;

    //static

    static Vect2D set(const Vect2D&, double, double);
    static Vect2D sum(const Vect2D&, const Vect2D&);
    static Vect2D rem(const Vect2D&, const Vect2D&);
    static Vect2D mult(const Vect2D&, double);
    static Vect2D div(const Vect2D&, double);
    static Vect2D min(const Vect2D&, const Vect2D&);
    static Vect2D max(const Vect2D&, const Vect2D&);
    static Vect2D normalize(const Vect2D&);
    static Vect2D setMagnitude(const Vect2D&, double);
    static Vect2D limit(const Vect2D&, const Vect2D&);
    static Vect2D limit(const Vect2D&, double);
    static double mag(const Vect2D&);
    static double dot(const Vect2D&, const Vect2D&);
    static double distance(const Vect2D&, const Vect2D&);
    static double angleBetween(const Vect2D&, const Vect2D&);
    static Vect2D scalarProjection(const Vect2D&, const Vect2D&);

    // operators

    Vect2D operator+(const Vect2D&) const;  // call sum
    Vect2D operator-(const Vect2D&) const;  // call sub
    Vect2D operator*(double) const;         // call mult
    Vect2D operator/(double) const;         // call div

    Vect2D& operator+=(const Vect2D&);  // call sum
    Vect2D& operator-=(const Vect2D&);  // call div
    Vect2D& operator*=(double);         // call mult
    Vect2D& operator/=(double);         // call div

    // comparison operators

    bool operator>(const Vect2D&) const;
    bool operator>=(const Vect2D&) const;
    bool operator<(const Vect2D&) const;
    bool operator<=(const Vect2D&) const;
    virtual bool operator==(const Vect2D&) const;
    virtual bool operator!=(const Vect2D&) const;  // controllo riferimento
};

#endif