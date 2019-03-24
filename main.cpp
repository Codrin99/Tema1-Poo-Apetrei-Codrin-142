#include <iostream>
#include <BigInt.h>
using namespace std;

int main()
{
    BigInt N1,N2,Suma,Dif,Produs,Impartire,Putere;
    cin>>N1>>N2;
    Suma=(N1 + N2);
    Dif=N2-N1;
    Produs=N1*N2;
    Impartire=N1/N2;
    Putere=Putere.putere(N1,3);
    cout<<Suma<<'\n'<<Dif<<'\n'<<Produs<<'\n'<<Impartire<<'\n';
    cout<<Putere<<'\n';
    Putere.palindrom(Putere);
    Putere.paritate(Putere);
    Putere.suma_cifre(Putere);
    return 0;
}
