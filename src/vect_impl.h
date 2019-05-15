#include <algorithm>
#include <memory>
#include <iostream>
#include <ostream>
#include <cmath>


using namespace std;

// Ctor
template <typename T>
Vect<T>::Vect(size_t n, T v) {
  mdata = alloc.allocate(n+1);
  mfirst_free = mdata;
  mend = mdata + n;

  if (n){
    uninitialized_fill(mdata, mend, v);
    mfirst_free = mend;
  }
}

// Dtor
template <typename T>
Vect<T>::~Vect() {
  free();
}

// CCtor
template <typename T>
Vect<T>::Vect(const Vect &v) : mdata(alloc.allocate(v.capacity() + 1)){
  uninitialized_copy_n(v.mdata, size(), mdata);
  mfirst_free = mdata + size();
  mend = mdata + capacity();
}

// MCtor
template <typename T>
Vect<T>::Vect(Vect && v) noexcept : mdata(v.mdata),
                                    mfirst_free(v.mfirst_free),
                                    mend(v.mend)
{
  v.mdata = nullptr;
  v.mfirst_free = nullptr;
  v.mend = nullptr;
}

// OP
template <typename T>
Vect<T>& Vect<T>::operator=(const Vect& v)
{
  if(mdata != v.mdata) {
    auto pom_velicina = size();
    auto pom_kapacitet = capacity();
    free();
    mdata = alloc.allocate(capacity() + 1);
    uninitialized_copy_n(v.mdata, pom_velicina, mdata);
    mfirst_free = mdata + pom_velicina;
    mend = mdata + pom_kapacitet;
  }
  return *this;
}

// MOP
template <typename T>
Vect<T>& Vect<T>::operator=(Vect && v) noexcept
{
  if (this != &v) {
    free();
    mdata = v.mdata;
    mfirst_free = v.mfirst_free;
    mend = v.mend;
    v.mdata = nullptr;
    v.mfirst_free = nullptr;
    v.mend = nullptr;
  }
  return *this;
}

// Operator []
template <typename T>
T Vect<T>::operator[](unsigned int i) const{
  auto it = mdata + i;
  return *it;
}

//operator [] const
template <typename T>
T& Vect<T>::operator[](unsigned int i){
  auto it = mdata + i;
  return *it;
}

// Push back
template <typename T>
void Vect<T>::push_back(T element) {
  if (mfirst_free != mend){
    alloc.construct(mfirst_free, element);
    ++mfirst_free;
  }
  else {
    reallocate();
    alloc.construct(mfirst_free, element);
    ++mfirst_free;
  }
}

// Operator +=
template <typename T>
Vect<T>& Vect<T>::operator+=(const Vect& v) {
  auto itv = v.mdata;
  for (auto it = mdata;
      it != mfirst_free && itv != v.mfirst_free;
      ++it, ++itv)
    *it += *itv;

  return *this;
}

// Operator -=
template <typename T>
Vect<T>& Vect<T>::operator-=(const Vect& v) {
  auto it = mdata;
  for (auto itv = v.mdata;
      it != mfirst_free && itv != v.mfirst_free;
      ++it, ++itv)
    *it -= *itv;

  return *this;
}

// Operator *=
template <typename T>
Vect<T>& Vect<T>::operator*=(T const & scalar) {
  for (auto it = mdata; it != mfirst_free; ++it)
    *it *= scalar;

  return *this;
}

// Euklidska norma
template <typename T>
double Vect<T>::two_norm() const {
  double suma = 0;
  for(auto it = mdata; it != mfirst_free; it++)
    suma += ((*it) * (*it));
  return sqrt(suma);
}
// Size
template <typename T>
size_t Vect<T>::size() const {
  return mfirst_free - mdata;
}

// Capacity
template <typename T>
size_t Vect<T>::capacity() const {
  return mend - mdata;
}

// free
template <typename T>
void Vect<T>::free(){
  for (auto it = mdata; it != mfirst_free; ++it)
    alloc.destroy(it);
  alloc.deallocate(mdata, capacity() + 1);
}

// Reallocate
template <typename T>
void Vect<T>::reallocate(){
  T *pom_data;
  T *pom_first;
  T *pom_end;

  //rezerviram preko pomocne
  if (capacity() == 0)
    pom_data = alloc.allocate(2);
  else
    pom_data = alloc.allocate(2 * capacity() + 1);
  //prebacim na adresu pomocne
  uninitialized_copy(mdata, mfirst_free, pom_data);
  pom_first = pom_data + size();
  pom_end = pom_data + capacity() * 2;
  //oslobodimo staru memoriju
  free();
  //prebacim staru na novu
  mdata = pom_data;
  mfirst_free = pom_first;
  mend = pom_end;
}

// operator +
template <typename T>
Vect<T> operator+(Vect<T> const & p1, Vect<T> const & p2){
  Vect<T> tmp;
  auto it1 = p1.mdata;
  for (auto it2 = p2.mdata;
      it1 != p1.mfirst_free && it2 != p2.mfirst_free;
      ++it1, ++it2) {
    tmp.push_back((*it1) + (*it2));
  }

    return tmp;
}

// operator -
template <typename T>
Vect<T> operator-(Vect<T> const & p1, Vect<T> const & p2) {
  Vect<T> tmp;
  auto it1 = p1.mdata;
  for (auto it2 = p2.mdata;
      it1 != p1.mfirst_free && it2 != p2.mfirst_free;
      ++it1, ++it2) {
    tmp.push_back((*it1) - (*it2));
  }

    return tmp;
}

// operator <<
template <typename T>
std::ostream & operator<<(std::ostream & out, Vect<T> const & p) {
  auto it = p.mdata;
  out << "[";

  if (p.size() < 1) {
    out << "]";
    return out;
  }

  for (size_t i = 0; i < p.size() - 1; ++i, ++it)
    out << *it << ",";

  out << *it << "]";
  return out;
}
