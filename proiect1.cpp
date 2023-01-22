#include <iostream>

using namespace std;

class Multime{
    int n, *v;
public:
    Multime(int n, int *v); /// constructor de initializare
    Multime(const Multime &ob); /// constructor de copiere
    ~Multime(); /// destructor
    void afisare(); /// functie membru de afisare pe ecran
    void transformare_multime(); /// metoda prin care elimin dublicatele

    int get_n(){return n;} ///getter n
    int* get_v(){return v;} ///getter v
    void set_n(int n){this -> n = n;} ///setter n
    void set_v(int* v){this -> v = v;} ///setter v

    /// supraincarcari de operatori

    Multime& operator=(const Multime &ob); /// operator de egalitate
    friend const Multime operator+(const Multime &ob1, const Multime &ob2); /// + = reuniune de multimi folosind functie prieten
    friend const Multime operator*(const Multime &ob1, const Multime &ob2); /// * = intersectie de multimi folosind functie prieten
    friend const Multime operator-(const Multime &ob1, const Multime &ob2); /// - = diferenta de multimi folosind functie prieten
    Multime& operator++(); /// incrementare prefixata (Adauga un element in multime)
    Multime& operator++(int); /// incrementare postfixata (Adauga un element in multime)
    Multime& operator--(); /// decrementare prefixata (Elimina un element din multime)
    Multime& operator--(int); /// decrementare postfixata (Elimina un element din multime)
};

Multime::Multime(int n, int *v){ /// constructor de initializare
    this -> v = new int[n + 1];
    this -> n = n;
    for(int i = 0; i < n; i++)
        this -> v[i] = v[i];
}

Multime::Multime(const Multime &ob){ /// constructor de copiere
    this -> n = ob.n;
    this -> v = new int[n + 1];
    for(int i = 0; i < n; i++)
        this -> v[i] = ob.v[i];
}

void Multime::afisare(){ /// functie membru de afisare pe ecran
    cout << "Multimea are " << this -> n << " elemente." << endl;
    cout << "{";
    for(int i = 0; i < n - 1; i++)
        cout << this -> v[i] << ", ";
    cout << this -> v[n - 1] << "}";
    cout << endl;
}

Multime::~Multime(){ /// destructor
    n = 0;
    delete []v; v = NULL;
}

void Multime::transformare_multime(){ /// metoda prin care elimin dublicatele
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(v[i] > v[j])
                swap(v[i], v[j]);
    for(int i = 0; i < n - 1; i++)
        if(v[i] == v[i + 1]){
            for(int j = i; j < n - 1; j++)
                v[j] = v[j + 1];
            v[n - 1] = NULL;
            i = i - 1; n = n - 1;
        }
}

/// supraincarcari de operatori

Multime& Multime::operator=(const Multime& ob){
    this -> n = ob.n;
    for(int i = 0; i < this -> n; i++)
        this->v[i] = ob.v[i];
    return *this;
}

const Multime operator+(const Multime &ob1, const Multime &ob2){ /// + = reuniune de multimi
    int *r = new int[ob1.n + ob2.n + 1];
    int k = 0;
    for(int i = 0; i < ob1.n; i++)
        r[k++] = ob1.v[i];
    for(int i = 0; i < ob2.n; i++){
        bool ok = true;
        for(int j = 0; j < k; j++)
            if(r[j] == ob2.v[i])
                ok = false;
        if(ok)
            r[k++] = ob2.v[i];
    }
    if(k == 0) r = NULL;
    Multime C(k, r);
    C.transformare_multime();
    return C;
}

const Multime operator*(const Multime &ob1, const Multime &ob2){ /// * = intersectie de multimi
    int k = 0, *in;
    in = new int[ob1.n + ob2.n + 1];
    for(int i = 0; i < ob1.n; i++){
        bool ok = false;
        for(int j = 0; j < ob2.n; j++)
            if(ob1.v[i] == ob2.v[j])
                ok = true;
        if(ok)
            in[k++] = ob1.v[i];
    }
    if(k == 0) in = NULL;
    Multime C(k, in);
    C.transformare_multime();
    return C;
}

const Multime operator-(const Multime &ob1, const Multime &ob2){ /// - = diferenta de multimi
    int k = 0, *dif;
    dif = new int[ob1.n + 1];
    for(int i = 0; i < ob1.n; i++){
        bool ok = true;
        for(int j = 0; j < ob2.n; j++)
            if(ob1.v[i] == ob2.v[j])
                ok = false;
        if(ok)
            dif[k++] = ob1.v[i];
    }
    if(k == 0) dif == NULL;
    Multime C(k, dif);
    C.transformare_multime();
    return C;
}

Multime& Multime::operator++(){ /// incrementare prefixata (Adauga un element in multime)
    int *w = new int[this -> n + 2];
    for(int i = 0; i < this -> n; i++)
        w[i] = this -> v[i];
    int nr;
    bool ok;
    do{
        ok = true;
        cout << "Introduceti un element care NU este in multime: "; cin >> nr;
        for(int i = 0; i < this -> n; i++)
            if(w[i] == nr)
                ok = false;
    }
    while(!ok);
    w[n] = nr;
    this -> v = w;
    this -> n = this -> n + 1;
    return *this;
}

Multime& Multime::operator++(int){ /// incrementare postfixata (Adauga un element in multime)
    int *w = new int[this -> n + 2];
    for(int i = 0; i < this -> n; i++)
        w[i] = this -> v[i];
    int nr;
    bool ok;
    do{
        ok = true;
        cout << "Introduceti un element care NU este in multime: "; cin >> nr;
        for(int i = 0; i < this -> n; i++)
            if(w[i] == nr)
                ok = false;
    }
    while(!ok);
    w[n] = nr;
    this -> v = w;
    this -> n = this -> n + 1;
    return *this;
}

Multime& Multime::operator--(){ /// decrementare prefixata (Elimina un element din multime)
    int nr, *w = new int[this->n]; /// -1+1
    int k = 0;
    bool ok;
    do{
        ok = false;
        cout << "Numarul eliminat DIN multime este: "; cin >> nr;
        for(int i = 0; i < this -> n; i++)
            if(v[i] == nr)
                ok = true;
    }
    while(!ok);
    for(int i = 0; i < n; i++)
        if(v[i] != nr)
            w[k++] = v[i];
    this -> v = w;
    this -> n = this->n - 1;
    return *this;
}

Multime& Multime::operator--(int){ ///decrementare postfixata (Elimina un element din multime)
    int nr, *w = new int[this->n]; /// -1+1
    int k = 0;
    bool ok;
    do{
        ok = false;
        cout << "Numarul eliminat DIN multime este: "; cin >> nr;
        for(int i = 0; i < this -> n; i++)
            if(v[i] == nr)
                ok = true;
    }
    while(!ok);
    for(int i = 0; i < n; i++)
        if(v[i] != nr)
            w[k++] = v[i];
    this -> v = w;
    this -> n = this->n - 1;
    return *this;
}

class Meniu{
    int n = 0, m = 0, *v, *w;
    static bool okA, okB;
public:
    void afisare_meniu();
    void introducere_multimi();
    void afisare_multimi();
    void reuniune_multimi1();
    void reuniune_multimi2();
    void intersectie_multimi1();
    void intersectie_multimi2();
    void adaugare_element();
    void eliminare_element();
    void diferenta_multimi();
};

void Meniu::afisare_meniu(){
    int opt;
    cout << "MENIU - TEMA 8 HOARA DUMITRU IONUT" << endl<<endl;
    if(okA)
        cout << "Status introducere multime A: INTRODUS"<< endl;
    else cout << "Status introducere multime A: NEINTRODUS "<< endl;
    if(okB)
        cout << "Status introdecere multime B: INTRODUS "<< endl;
    else cout << "Status introducere multime B: NEINTRODUS "<< endl;
    cout << endl;
    cout << "1. Introduceti multimile in program" << endl;
    cout << "2. Afisati multimile introduse" << endl;
    cout << "3. Reuniune multimi" << endl;
    cout << "4. Reuniune multimi (3 multimi)" << endl;
    cout << "5. Intersectie multimi" << endl;
    cout << "6. Intersectie multimi (3 multimi)" << endl;
    cout << "7. Adaugare elemente in multimi" << endl;
    cout << "8. Eliminare elemente din multimi" << endl;
    cout << "9. Diferenta a doua multimi(A-B)" << endl;
    cout << "10. Parasire program" << endl << endl;
    cout << "MENTIUNE: Pentru utilizarea programului trebuie ca ambele multimi sa fie INTRODUSE."<<endl;
    cout << endl;
    do{
        cout << "Optiunea dorita este: "; cin >> opt;
    }
    while(opt < 1 || opt > 10);
    if(opt == 1)
        introducere_multimi();
    if(opt == 2)
        afisare_multimi();
    if(opt == 3)
        reuniune_multimi1();
    if(opt == 4)
        reuniune_multimi2();
    if(opt == 5)
        intersectie_multimi1();
    if(opt == 6)
        intersectie_multimi2();
    if(opt == 7)
        adaugare_element();
    if(opt == 8)
        eliminare_element();
    if(opt == 9)
        diferenta_multimi();
    if(opt == 10){
        system("CLS");
        cout << "Multumesc pentru utilizarea programului. O zi frumoasa!";
    }

}

bool Meniu::okA = false;
bool Meniu::okB = false;

void Meniu::introducere_multimi(){
    system("CLS");
    char buton;
    cout << "MENIU :: INTRODUCETI MULTIMILE IN PROGRAM " << endl << endl;
    do{
    cout << "Nr elemente prima multime = "; cin >> n;}
    while(n < 0);
    if(n != 0)
        okA = true;
    else
        okA = false;
    v = new int[n + 1];
    for(int i = 0; i < n; i++){
        cout << "Introduceti element: "; cin >> v[i];
    }
    do{
    cout << "Nr elemente a doua multime = "; cin >> m;
    }while(m < 0);
    if(m != 0)
        okB = true;
    else
        okB = false;
    w = new int[m + 1];
    for(int i = 0; i < m; i++){
        cout << "Introduceti element: "; cin >> w[i];
    }
    cout << endl << endl;
    cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
    system("CLS");
    afisare_meniu();
}

void Meniu::afisare_multimi(){
    system("CLS");
    char buton;
    cout << "MENIU :: MULTIMI INTRODUSE IN PROGRAM " << endl << endl;
    if(n != 0 && m != 0){
        Multime A(n, v), B(m, w);
        A.transformare_multime();
        B.transformare_multime();
        A.afisare();
        B.afisare();
        cout << endl << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
        }
    else{
        cout << "Cel putin una dintre multimi este vida." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}

void Meniu::reuniune_multimi1(){
    char buton;
    system("CLS");
    cout << "MENIU :: REUNIUNE MULTIMI INTRODUSE IN PROGRAM " << endl << endl;
    if(n != 0 && m != 0){
        Multime A(n, v), B(m, w);
        A.transformare_multime();
        B.transformare_multime();
        Multime C(0, NULL);
        C = A + B;
        cout << "AM CALCULAT REUNIUNEA ELEMENTELOR INTRODUSE " << endl << endl;
        C.afisare();
        cout << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
        }
    else{
        cout << "Cel putin una dintre multimi este vida." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}

void Meniu::reuniune_multimi2(){
    char buton;
    system("CLS");
    cout << "MENIU :: REUNIUNE 3 MULTIMI INTRODUSE IN PROGRAM " << endl << endl;
    if(n != 0 && m != 0){
        Multime A(n, v), B(m, w);
        int k, *z;
        do{
            cout << "Nr elemente multimea 3: "; cin >> k;}
        while(k < 0);
        z = new int[k + 1];
        for(int i = 0; i < k; i++){
            cout << "Introduceti element: "; cin >> z[i];
        }
        cout << endl << endl;
        Multime C(k, z);
        A.transformare_multime();
        B.transformare_multime();
        C.transformare_multime();
        Multime D(0, NULL);
        D = A + B + C;
        cout << "AM CALCULAT REUNIUNEA ELEMENTELOR INTRODUSE " << endl << endl;
        D.afisare();
        cout << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
        }
    else{
        cout << "Cel putin una dintre multimi este vida." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}

void Meniu::intersectie_multimi1(){
    char buton;
    system("CLS");
    cout << "MENIU :: INTERSECTIE MULTIMI INTRODUSE IN PROGRAM " << endl << endl;
    if(n != 0 && m != 0){
        Multime A(n, v), B(m, w);
        A.transformare_multime();
        B.transformare_multime();
        Multime C(0, NULL);
        C = A * B;
        cout << "AM CALCULAT INTERSECTIA ELEMENTELOR INTRODUSE " << endl << endl;
        if(C.get_n() == 0)
            cout << "Interesectia este vida." << endl;
        else
            C.afisare();
        cout << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
    else{
        cout << "Cel putin una dintre multimi este vida." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}

void Meniu::intersectie_multimi2(){
    char buton;
    system("CLS");
    cout << "MENIU :: INTERSECTIE 3 MULTIMI INTRODUSE IN PROGRAM " << endl << endl;
    if(n != 0 && m != 0){
        Multime A(n, v), B(m, w);
        int k, *z;
        do{
            cout << "Nr elemente multimea 3: "; cin >> k;}
        while(k < 0);
        z = new int[k + 1];
        for(int i = 0; i < k; i++){
            cout << "Introduceti element: "; cin >> z[i];
        }
        cout << endl << endl;
        Multime C(k, z);
        A.transformare_multime();
        B.transformare_multime();
        C.transformare_multime();
        Multime D(0, NULL);
        D = A * B;
        if(D.get_n() == 0)
            cout << "Intersectia este vida.";
        else{
            D = A * B * C;
            cout << "AM CALCULAT INTERSECTIA MULTIMILOR INTRODUSE " << endl << endl;
            if(D.get_n() == 0)
                cout << "Intersectia este vida.";
            else
                D.afisare();
        }
        cout << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
        }
    else{
        cout << "Cel putin una dintre multimi este vida." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}


void Meniu::adaugare_element(){
    int k;
    char buton;
    system("CLS");
    cout << "MENIU :: ADAUGARE ELEMENTE IN MULTIMI " << endl << endl;
    Multime A(n, v), B(m, w);
    A.transformare_multime();
    B.transformare_multime();
    if(n != 0 && m != 0){
        A.afisare();
        cout << endl;
        do{
            cout << "Nr de elemente pe care doriti sa le adaugati in prima multime: "; cin >> k;}
        while(k < 0);
        for(int i = 0; i < k; i++)
            A++;
        n = A.get_n();
        v = A.get_v();
        cout << endl;
        B.afisare();
        do{
        cout << "Nr de elemente pe care doriti sa le adaugati in a doua multime: "; cin >> k;
        }
        while(k < 0);
        for(int i = 0; i < k; i++)
            ++B; ///doar pt a arata ca functioneaza ambele
        m = B.get_n();
        w = B.get_v();
        system("CLS");
        afisare_meniu();
    }
    else{
        cout << "Inca nu au fost introduse multimi." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}

void Meniu::eliminare_element(){
    int k;
    char buton;
    system("CLS");
    cout << "MENIU :: ELIMINARE ELEMENTE DIN MULTIMI " << endl << endl;
    Multime A(n, v), B(m, w);
    A.transformare_multime();
    B.transformare_multime();
    if(n != 0 && m != 0){
        A.afisare();
        cout << endl;
        do{
            cout << "Nr de elemente pe care doriti sa le eliminati din prima multime: "; cin >> k;}
        while(k > A.get_n() || k < 0);
        for(int i = 0; i < k; i++)
            A--;
        n = A.get_n();
        v = A.get_v();
        cout << endl;
        B.afisare();
        do{
            cout << "Nr de elemente pe care doriti sa le eliminati din a doua multime: "; cin >> k;}
        while(k > B.get_n() || k < 0);
        for(int i = 0; i < k; i++)
            --B; ///doar pt a arata ca functioneaza ambele
        m = B.get_n();
        w = B.get_v();
        system("CLS");
        if(!n)
            okA = false;
        if(!m)
            okB = false;
        afisare_meniu();
    }
    else{
        cout << "Cel putin una dintre multimi este vida." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}

void Meniu::diferenta_multimi(){
    char buton;
    system("CLS");
    cout << "MENIU :: DIFERENTA MULTIMI INTRODUSE IN PROGRAM " << endl << endl;
    if(n != 0 && m != 0){
        Multime A(n, v), B(m, w);
        A.transformare_multime();
        B.transformare_multime();
        Multime C(0, NULL);
        C = A - B;
        cout << "AM CALCULAT DIFERENTA ELEMENTELOR INTRODUSE " << endl << endl;
        if(C.get_n() != 0)
            C.afisare();
        else
            cout << "Prin diferenta obtinem multimea vida.";
        cout << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
    else{
        cout << "Inca nu au fost introduse multimi." << endl;
        cout << "Introduceti orice caracter pentru a reveni la meniul principal..."; cin >> buton;
        system("CLS");
        afisare_meniu();
    }
}

int main()
{
    Meniu M;
    M.afisare_meniu();
}
