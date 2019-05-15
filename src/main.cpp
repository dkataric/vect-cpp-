#include "vect.h"
#include <iostream>
#include <ostream>

using namespace std;

int main()
{
    Vect<int> vektor(2,3);
    Vect<int> vektor2;

    vektor2.push_back(5); vektor2.push_back(5);

    cout << "vektor: " << vektor << endl;
    cout << "vektor2: " << vektor2 << endl;

    vektor += vektor2;
    cout << "vektor nakon zbrajanja sa vektor2: " << vektor << endl;

    vektor *= 2;
    cout << "vektor nakon množenja sa dva: " << vektor << endl;

    vektor -= vektor2;
    cout << "vektor nakon oduzimanja sa vektor2: " << vektor << endl;

    vektor.push_back(9);
    cout << "vektor nakon ubacivanja 9 na kraj: " << vektor << endl;

    cout << "dohvat treceg elementa: " << vektor[2] << endl;

    cout << "velicina vektora: " << vektor.size() << endl;
    cout << "kapacitet vektora: " << vektor.capacity() << endl;

    cout << "euklidska norma vektora: " << vektor.two_norm() << endl;

    cout << "vektor: " << vektor << endl;
    cout << "vektor2: " <<  vektor2 << endl;
    Vect<int> vektor3 = vektor + vektor2;
    cout << "vektor3 dobiven kao zbroj prva dva: " <<  vektor3 << endl;

    Vect<int> vektor4(10);
    cout << "vektor4: " << vektor4 << endl;
    cout << "velicina vektor4 od 10 elemenata: " << vektor4.size() << endl;
    cout << "kapacitet vektor4 od 10 elmenata: " << vektor4.capacity() << endl;

    vektor4.push_back(30);
    cout << "vektor4 nakon ubacenog push_back(30) " << vektor4 << endl;
    cout << "kapacitet od vektor4 nakon push_back: " << vektor4.capacity() << endl;

    Vect<int> vektor5(11,56);
    cout << "vektor5: " << vektor5 << endl;
    Vect<int> vektor6 = vektor5 - vektor4;
    cout << "vektor6 dobiven kao vektor5 - vektor4: " << vektor6 << endl;

    //Vect<int> vektor7 = vektor6;
    //cout << "vektor7 = vektor6...vekor7: " << vektor7 << endl;

    return 0;
}
