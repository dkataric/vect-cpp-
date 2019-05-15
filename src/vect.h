#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <ostream>
#include <memory>
#include <cmath>

using namespace std;

// deklaracija potrebna za testiranje
template <typename> class VectTest;

template <typename T>
class Vect
{
    friend class VectTest<T>;  // da testovi mogu dohvatiti privatne varijable
    friend class VectTestPair;
public:
    // Ctor
    explicit Vect(size_t n = 0, T v = {});
    // Dtor
    ~Vect();


    // CCtor
    Vect(const Vect& v);
    // MCtor
    Vect(Vect && v) noexcept;

    // OP
    Vect& operator=(const Vect& v);
    // MOP
    Vect& operator=(Vect && v) noexcept;


    // dohvat elemenata (operator [])
    T operator[](unsigned int i) const;
    T& operator[](unsigned int i);
    // push_back metoda
    void push_back (T element);

    size_t size() const;
    size_t capacity() const;

    // operatori +=, -=, *=
    Vect& operator+=(const Vect& v);
    Vect& operator-=(const Vect& v);
    Vect& operator*=(T const & scalar);

     // euklidska norma vraća double !
     double two_norm() const;
private:
        T *mdata;       // pokazivač na prvi element
        T *mfirst_free; // pokazivač na prvo slobodno mjesto,razlikuje br el od kapaciteta
        T *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)
                             //ubacujemo el dok free ne postane end

        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();

      	// realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je
        // vektor prazan alociraj jedan element.
        void reallocate();

        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo
        // statičkim. Ne zaboraviti definirati ga.
        static std::allocator<T> alloc;
        template<typename U>
        friend Vect<U> operator+(Vect<U> const & p1, Vect<U> const & p2);
        template<typename U>
        friend Vect<U> operator-(Vect<U> const & p1, Vect<U> const & p2);
        template <typename U>
        friend std::ostream & operator<<(std::ostream &, Vect<U> const &);
};
template<typename T>
std::allocator<T> Vect<T>::alloc;

// Operator +
template <typename T>
Vect<T> operator+(Vect<T> const & p1, Vect<T> const & p2);

// Operator -
template <typename T>
Vect<T> operator-(Vect<T> const & p1, Vect<T> const & p2);

// Operator <<
template <typename T>
std::ostream & operator<<(std::ostream & out, Vect<T> const &);

// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
