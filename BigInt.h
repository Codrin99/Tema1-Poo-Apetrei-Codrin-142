#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
using namespace std;

class BigInt
{   int dimensiune;
    int *numar;
    public:
        BigInt();
        BigInt(int i, char *s);
        BigInt(BigInt &Nr);
        BigInt(int nr);
        void set_nr_pointer(int *p);
        int* alocare(int dim);
        int get_dim();
        int get_nr(int i);
        void set_dim(int dim);
        void set_numar(int i, int nr);
        void elim_zero();
        friend istream& operator>>(istream& in, BigInt &Nr);
        friend ostream& operator<<(ostream& out,BigInt &Nr);
        BigInt operator=(char *s);
        void oglindire ();
        int operator>(BigInt Nr1);
        void inm_zece();
        BigInt operator+(BigInt Nr1);
        BigInt operator=( const BigInt &Nr);
        BigInt operator-(BigInt Nr1);
        BigInt operator*(BigInt Nr1);
        BigInt operator/(BigInt Nr1);
        BigInt putere (BigInt Nr, int putere);
        void palindrom (BigInt Nr);
        void paritate (BigInt Nr);
        void suma_cifre (BigInt Nr);
        ~BigInt();

};

#endif // BIGINT_H
