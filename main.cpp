#include <iostream>

using namespace std;
template <class MultiSetType> class MultiSet
{
    int Size;
    MultiSetType *Multi_set;
public:
    MultiSet()                      //constructor fara parametri
    {
        Size=0;
    }
    MultiSet(const  MultiSetType &Obj);                 //constructorul de copiere
    MultiSetType &operator= (MultiSetType & Obj);
    void Adaugare (MultiSetType elem);                //metoda pentru adaugarea unui element
    void Stergere ();                                 //metoda pentru stergerea unui element
    int Nr_elem(MultiSetType elem);                   //metoda ce intoarce numarul de aparatii a unui element
    int Verificare( MultiSetType elem);               //metoda pentru verificarea daca un anumit element se afla in multiset
    void Eliminare(MultiSetType elem);                //metoda pentru eliminarea tuturor apritiilor unui element din multiset
    int Elem_dist();                                  //metoda ce returneaza numarul de elemente distincte dintr-un multiset
    friend ostream& operator<<( ostream& o, const MultiSet& Obj )
    {
        o<<"Numarul elementelor din MultiSet este: "<<Obj.Size<<'\n';               //supraincarcarea oepratorului de afisare
        for(int i=0; i<Obj.Size; i++)
            o<<Obj.Multi_set[i]<<" ";
        o<<'\n';
    }
    ~MultiSet();
};
template <class MultiSetType> MultiSet<MultiSetType>:: MultiSet(const MultiSetType & Obj)
{
    this.Size=Obj.Size;
    this->Multi_set= new MultiSetType[Size];            //alocam spatiu pentru multisetul nostru si copiem elementele si dimensiunea din celalat multiset
    for(int i=0; i<Size; i++)
        this->Multi_set[i]=Obj.Multi_set[i];
}
template <class MultiSetType> MultiSetType &MultiSet<MultiSetType>:: operator=(MultiSetType & Obj)
{
    Size=Obj.Size;
    this->Multi_set= new MultiSetType[Size];            //supraincarcarea op= la fel ca la constructor de copiere doar ca cu return
    for(int i=0; i<Size; i++)
        this->Multi_set[i]=Obj.Multi_set[i];
    return *this;
}
template <class MultiSetType> void MultiSet<MultiSetType>:: Adaugare(MultiSetType elem)
{
    Size++;
    MultiSetType *Nobj;                                 //crestem dimensiunea multisetului cu 1 si ne creeam un nou multiset in care
    Nobj= new MultiSetType[Size-1];                     //vom copia multisetul actual
    for(int i=0; i<Size-1; i++)
        Nobj[i]=this->Multi_set[i];
    this->Multi_set= new MultiSetType[Size];             //urmand sa alocam din nou multisetul in care vrem sa adaugam, dar tura asta de noul SIZE
    for(int i=0; i<Size-1; i++)
        this->Multi_set[i]=Nobj[i];             //copiem elementele salate in multisetul auxiliar si adaugam la sfarsit element dorit sa fie adaugat
    this->Multi_set[Size-1]=elem;
}
template <class MultiSetType> void MultiSet<MultiSetType>:: Stergere( )
{
    try
    {
        throw Size;
    }
    catch( int k)
        {if( k==0 )
        {
            cout<<"Nu se afla elemente in MultiSet"<<endl;
            return;
        }
        }
    Size--;
    MultiSetType *Nobj;                 //la fel ca si la adaugare doar ca tura asta vom scadea SIZEULsi nu vom mai copia ultimul element
    Nobj= new MultiSetType[Size];
    for(int i=0; i<Size; i++)
        Nobj[i]=this->Multi_set[i];
    this->Multi_set= new MultiSetType[Size];            //realocam multisetul original si copiem inapoi elementele in el deoarece
    for(int i=0; i<Size; i++)                           //nu vrem sa avem spatiu alocat in plus si sa se ajunga din greseala acolo
        this->Multi_set[i]=Nobj[i];

}
template <class MultiSetType> int MultiSet<MultiSetType>:: Verificare(MultiSetType elem)
{
    for(int i=0; i<Size; i++)
        if(this->Multi_set[i]==elem)                    //parcurgem multisetul iar cand gasim elementul returnam 1
            return 1;
    return 0;
}
template <class MultiSetType> int MultiSet<MultiSetType>:: Nr_elem(MultiSetType elem)
{
    int aparitii=0;
    for(int i=0; i<Size; i++)
        if(this->Multi_set[i]==elem)                    //parcurgem vectorul iar cand gasim elementul dorit actualizam nr lui de aparatii
            aparitii++;
    return aparitii;                    //in final returnam numarul de aparitii a elemnetului
}
template <class MultiSetType> void MultiSet<MultiSetType>:: Eliminare( MultiSetType elem)
{
    int nr_aparitii=this->Nr_elem(elem);
    Size-=nr_aparitii;
    MultiSetType *Nobj;                         //actualizam dimensiunea multisetului folosindu-ne de metoda ce returneaza numarul de aparitii
    Nobj= new MultiSetType[Size];               //Creeam un multiset auxilar si luam un indice j reprezentand pozitia in multisetul auxiliar
    int j=0;                                    //Bu folosim metoda de adugare pentru a evita realocarea reptata de memorie
    for(int i=0; i<Size+nr_aparitii; i++)
        if(this->Multi_set[i]!=elem)
        {
            Nobj[j]=this->Multi_set[i];     //parcurgem multisetul original si copiem doar elementele diferite de elementul ce dorim sa il stergem
            j++;
        }
    this->Multi_set = new MultiSetType[Size];       //realocam spatiu pentru multisetul original si copiem elementele din multisetul auxiliar
    for(int i=0; i<Size; i++)
        this->Multi_set[i]=Nobj[i];
}
template <class MultiSetType> int MultiSet<MultiSetType>:: Elem_dist()
{
    MultiSet<MultiSetType> Obj;
    MultiSet<MultiSetType> Aux(*this);           //creaam 2 multiseturi auxiliare unu in care copiem multisetul original pentru a nu il strica
    for( int i=0; i<=Aux.Size; i++)              // si unul in care vom adauga fiecare element dar fara sa se repete
    {
        i=0;
        Obj.Adaugare(Aux.Multi_set[i]);             // pentru a face asta vom elimina toate aparitiile a fiecarui element din multisetul auxliar
        Aux.Eliminare(Aux.Multi_set[i]);            // si il vom adauga o singura data in celalat auxilar
    }
    return Obj.Size;                    //in final returnam dimensiunea multisetului format doar din elemente distincte
}
template <class MultiSetType> MultiSet<MultiSetType>:: ~MultiSet()
{
delete[]Multi_set;
Size=0;
}
main()
{
    MultiSet<int> Obiect;
    MultiSet<char> Obiect3;
    Obiect3.Stergere();
    Obiect3.Adaugare('a');
    Obiect3.Adaugare('8');
    Obiect3.Adaugare('a');
    Obiect3.Adaugare('a');
    Obiect3.Adaugare('2');
    Obiect3.Adaugare('K');
    Obiect3.Adaugare('&');
    Obiect.Adaugare(2);
    Obiect.Adaugare(5);
    Obiect.Adaugare(3);
    Obiect.Adaugare(7);
    Obiect.Adaugare(2);
    Obiect.Adaugare(5);
    Obiect.Adaugare(1);
    Obiect.Adaugare(5);
    cout<<Obiect;
    cout<<Obiect3;
    Obiect3.Eliminare('a');
    cout<<Obiect3;
    MultiSet <int> Obiect2(Obiect);
    if(Obiect.Verificare(5)==1)
        cout<<"Elementul se afla in MultiSet"<<'\n';
        else cout<<"Elementul nu se afla in MultiSet"<<'\n';
    cout<<Obiect.Nr_elem(3)<<'\n';
    cout<<Obiect2.Elem_dist()<<'\n';
    cout<<Obiect2;
    return 0;
}
