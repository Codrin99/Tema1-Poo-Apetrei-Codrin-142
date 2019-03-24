#include "BigInt.h"
#include "cstring"
#include <iostream>

BigInt::BigInt()                            //constructorul fara parametri
{
    dimensiune=0,numar=NULL;
}
BigInt::BigInt(int i, char *s)              //constructorul cu parametri pentru siruri de caractere
{
    dimensiune=i;
    numar=new int[i];
    for(int j=0; j <dimensiune; j++)
        numar[j]=(int)s[j]-'0';
}
BigInt::BigInt(int nr)                     // constructorul cu parametrei pentru numere intregi
{
    dimensiune=0;
    while(nr)
    {
        numar[dimensiune++]=nr%10;
        nr/=10;
    }
    this->oglindire();
}
BigInt::BigInt(BigInt &Nr)                  //constructorul prin copiere
{
    int i;
    dimensiune=Nr.dimensiune;
    numar=new int[Nr.dimensiune];
    for(i=0; i<Nr.dimensiune; i++)
        numar[i]=Nr.numar[i];
}
void BigInt::set_nr_pointer(int *p)         //pun in numar un pointer deja alocat
{
    numar=p;
}
int* BigInt:: alocare(int dim)          //functie de alocare a memoriei
{
    return new int[dim];
}
int BigInt:: get_dim()                  //functie ce returneaza dimensiunea
{
    return dimensiune;
}
int BigInt::get_nr(int i)               //functie ce returneaza o cifra din numar
{
    return numar[i];
}
void BigInt::set_dim( int dim)          //functie ce seteaza dimensiunea
{
    dimensiune=dim;
}
void BigInt::set_numar( int i, int nr)          //functie ce seteaza o cifra din numar
{
    numar[i]=nr;
}
istream& operator>>(istream& in, BigInt &Nr)    //supraincarcarea op de citire
{
    int x;
    in>>x;              // citesc dimensiunea numarului
    Nr.set_dim(x);         // setez dimensiunea numarului citit
    Nr.set_nr_pointer(Nr.alocare(Nr.get_dim()));    //aloc "dim" spatii la pointerul numar
    for(int i=0; i<Nr.dimensiune; i++)
    {
        in>>x;
        Nr.set_numar(i,x);      //citesc cifra cu cifra din numar de la stanga la dreapta
    }
    return in;
}
ostream& operator<<(ostream& out, BigInt &Nr)
{
    out<<"Lungimea numarului este: "<<Nr.get_dim()<<'\n';   //afisare dimensiune
    out<<"Numarul este: ";
    for(int i=0; i<Nr.get_dim(); i++)
        out<<Nr.get_nr(i);      //afisare cifre una cate una
    return out;
}
BigInt BigInt::operator=(char *s)           //supraincarcare op= pentru siruri de caractere
{
    dimensiune=strlen(s);
    numar=new int[dimensiune];
    for(int j=0; j <dimensiune; j++)
        numar[j]=(int)s[j]-'0';
    return *this;
}
BigInt BigInt::operator=(const BigInt &Nr)          //supraincarcare op= pentru obiecte
{
    dimensiune=Nr.dimensiune;
    numar=new int[dimensiune];
    for( int i=0; i<dimensiune; i++)
        numar[i]=Nr.numar[i];
    return *this;
}
void BigInt::inm_zece()             //inmultirea unui numar mare cu 10( adaugarea de 0 la sfarsit) va ajuta la impartire
{
    BigInt Aux(*this);
    Aux.dimensiune++;
    Aux.numar=new int[Aux.dimensiune];
    for(int i=0; i<dimensiune; i++)
        Aux.numar[i+1]=numar[i];
    Aux.numar[0]=0;
    *this=Aux;
}
void BigInt::elim_zero()
{
    while(numar[dimensiune-1]==0 and dimensiune!=1)             //elimin zerourile nesemnificative de la inceputul numaruilui
        dimensiune--;
}
void BigInt::oglindire()                        //functie de oglindire ce va ajuta la intoarcerea numarului pentru a fi mai usor de lucrat cu numarul
{
    BigInt Oglindit(*this);
    for(int i=0; i <dimensiune; i++)
        Oglindit.numar[i]=numar[dimensiune-i-1];
    *this=Oglindit;
}
BigInt BigInt::operator+(BigInt Nr1)        //supraincaracare op+
{
    int i=0, T=0;
    BigInt Nr2;
    this->oglindire();
    Nr1.oglindire();        //oglindesc numerele pentru a le putea aduna mai usor
    if(Nr1.dimensiune>dimensiune)
    {
        Nr2.set_dim(Nr1.dimensiune+1);
        Nr2.numar=new int[Nr1.dimensiune+1]; //aloc un spatiu in plus pentru evitarea pierderii ultimuluji transport1
        for(int j=0; j <Nr2.dimensiune; j++)
            Nr2.numar[j]=0;             //initializez spatiul alocat cu 0
        for( i=0; i<dimensiune; i++)
        {
            Nr2.numar[i]=Nr1.numar[i]+numar[i]+T;       //adun cifrele rand pe rand pana la finalizarea numarului cu mai putine cifre
            T=Nr2.numar[i]/10;
            Nr2.numar[i]%=10;
        }
        for(; i<Nr1.dimensiune; i++)
        {
            Nr2.numar[i]=Nr1.numar[i]+T;                //continui sa adun restul de cifre reamase in numarul mai mare adunand si trasnportul
            T=Nr2.numar[i]/10;
            Nr2.numar[i]%=10;
        }
        if (T)
            Nr2.numar[i]=T;
    }
    else
    {
        Nr2.set_dim(dimensiune+1);
        Nr2.numar=new int[dimensiune+1];
        for(int j=0; j <Nr2.dimensiune; j++)
            Nr2.numar[j]=0;
        for( i=0; i<Nr1.dimensiune; i++)
        {
            Nr2.numar[i]=Nr1.numar[i]+numar[i]+T;
            T=Nr2.numar[i]/10;
            Nr2.numar[i]%=10;                                         //la fel ca mai sus
        }
        for(; i<dimensiune; i++)
        {
            Nr2.numar[i]=numar[i]+T;
            T=Nr2.numar[i]/10;
            Nr2.numar[i]%=10;
        }
        if (T)
            Nr2.numar[i]=T;
    }
    Nr2.elim_zero();
    this->oglindire();
    Nr1.oglindire();                //oglindesc din nou numamrul pentru a fi in in forma normala (de la stanga la dreapta)
    Nr2.oglindire();
    return Nr2;
}
int BigInt::operator>(BigInt Nr1)           //supraincarcarea op >
{
    if(dimensiune>Nr1.dimensiune)
        return 1;
    else if(dimensiune==Nr1.dimensiune)
    {
        for(int i=0; i <dimensiune; i++)
            if(numar[i]>Nr1.numar[i])
                return 1;
    }
    return 0;
}
BigInt BigInt::operator-(BigInt Nr1)            //supraincarcarea op -
{
    int i=0, T=0;
    BigInt Nr_mic, Nr_mare;             //se vor copia numarul mai mic in nr_mic si cel mare in nr_mare dupa inversare
    this->oglindire();
    Nr1.oglindire();
    if(Nr1>*this)
    {
        Nr_mic=*this;
        Nr_mare=Nr1;
    }
    else
    {
        Nr_mic=Nr1;
        Nr_mare=*this;
    }
    for(; i<Nr_mic.dimensiune; i++)         // scad cifrele rand pe rand pana la terminarea numarului de dimensiune mai mica
    {
        Nr_mare.numar[i]-=(Nr_mic.numar[i]+T);
        if(Nr_mare.numar[i]<0)              // setez transportul ce urmeaza sa fie scazut
            T=1;
        else
            T=0;
        if(T==1)
            Nr_mare.numar[i]+=10;
    }
    for(i=Nr_mic.dimensiune; i<Nr_mare.dimensiune and T==1; i++)            //completez restul de cifre cu cifrele din numarul ramas scazand transportul
    {
        Nr_mare.numar[i]-=T;
        if(Nr_mare.numar[i]<0)
            T=1;
        else
            T=0;
        if(T==1)
            Nr_mare.numar[i]+=10;
    }
    Nr_mare.elim_zero();
    this->oglindire();                  //oglindim din nou numerele pentru a le avea in forma normala
    Nr1.oglindire();
    Nr_mare.oglindire();
    return Nr_mare;
}
void BigInt::palindrom(BigInt Nr)               //functia de verificare daca un numar e palindrom ( ne vom ajuta de functia de oglindire)
{
    int ok=0;
    BigInt Nr1( Nr);
    Nr1.oglindire();
    for( int i=0; i<Nr.dimensiune; i++)
        if(Nr1.numar[i]!=Nr.numar[i])
        {
            cout<<"Numarul nu este palindrom"<<'\n';
            ok=1;
            break;
        }
    if(ok==0)
        cout<<"Numarul este palindrom"<<'\n';
}
BigInt BigInt::operator*(BigInt Nr1)            //supraincarcare op*
{
    int i=0,j=0, T=0;
    BigInt Nr_rez;
    this->oglindire();
    Nr1.oglindire();
    Nr_rez.dimensiune=dimensiune+Nr1.dimensiune-1;      // setam dimensiunea rezultautlui ca fiind suma celor 2 dimensiuni ale numarului-1
    Nr_rez.numar=new int[Nr_rez.dimensiune+1];          // si alocam spatiu pentru numarul rezultat si intilizam vectorul cu 0
    for(i=0; i<Nr_rez.dimensiune; i++)
        Nr_rez.numar[i]=0;
    for(i=0; i<dimensiune; i++)
        for(j=0; j<Nr1.dimensiune; j++)                 //efectuarea produselor intermediare si adunarea lor
            Nr_rez.numar[i+j]+=numar[i]*Nr1.numar[j];
    for(i=0; i<Nr_rez.dimensiune; i++)
    {
        Nr_rez.numar[i]+=T;
        T=Nr_rez.numar[i]/10;
        Nr_rez.numar[i]%=10;                //Corectarea sumelor rezultate pastrand doar cifra unitatilor si steand transportul
    }
    if(T)
    {
        Nr_rez.dimensiune++;
        Nr_rez.numar[Nr_rez.dimensiune-1]= T;
    }
    this->oglindire();
    Nr1.oglindire();                    //aducerea numerelor in forma normala
    Nr_rez.oglindire();
    return Nr_rez;
}
BigInt BigInt::operator/(BigInt Nr1)                // supraincarcarea op/
{
    int i=0;
    BigInt Nr_rez, Nr_rest;
    this->oglindire();
    Nr1.oglindire();                    //oglindirea numerelor
    Nr_rez.dimensiune=dimensiune;
    Nr_rez.numar=new int[Nr_rez.dimensiune+1];      //alocarea spatiului necesar pentru rezultat si initializarea vectorului cu 0
    Nr_rest.dimensiune=0;
    for(i=0; i<Nr_rez.dimensiune; i++)
        Nr_rez.numar[i]=0;
    for(i=dimensiune-1; i>-1; i--)
    {
        //asemanator cu cea de pe infoarena ( prin scaderi repetate)
        Nr_rest.inm_zece();
        Nr_rest.numar[0]=numar[i];
        Nr_rez.numar[i]=0;
        Nr_rest.oglindire();
        Nr1.oglindire();
        while((Nr1>Nr_rest)!=1)
        {
            Nr_rez.numar[i]++;
            Nr_rest=Nr_rest-Nr1;

        }
        Nr_rest.oglindire();
        Nr1.oglindire();
    }
    Nr_rez.elim_zero();
    this->oglindire();
    Nr1.oglindire();
    Nr_rez.oglindire();         //oglindirea numarului la forma initiala
    return Nr_rez;
}
BigInt BigInt::putere(BigInt Nr, int putere)            //functia de ridicare la putere
{
    BigInt Nr_putere(Nr);
    for(int i=0; i<putere-1; i++)
    {
        Nr_putere=Nr_putere*Nr;                 //inmultiri repetate cu ajutorul op *
    }
    return Nr_putere;
}
void BigInt::paritate(BigInt Nr)            //functia de determinare a paritatii
{
    if(Nr.numar[dimensiune-1]%2==0)
        cout<<"Numarul este par"<<'\n';
    else
        cout<<"Numarul nu este par"<<'\n';
}
void BigInt::suma_cifre(BigInt Nr)          //functia de determinare a sumei cifrelor unui numar
{
    int suma=0;
    for(int i=0; i<Nr.dimensiune; i++)
        suma+=Nr.numar[i];
    cout<<suma;
}
BigInt::~BigInt()                   //destructor
{
    delete[]numar;
}
