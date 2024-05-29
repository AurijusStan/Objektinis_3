#include "funkcijos.h"

using namespace std;

bool sort1(const duom &a, const duom &b){
    return(a.vard()<b.vard());
}
bool sort2(const duom &a, const duom &b){
    return(a.pav()<b.pav());
}
bool sort3(const duom &a, const duom &b){
    return(a.galvid()<b.galvid());
}
bool sort4(const duom &a, const duom &b){
    return(a.galmed()<b.galmed());
}
bool sort1u(const duom &a, const duom &b){
    return(a.vard()>b.vard());
}
bool sort2u(const duom &a, const duom &b){
    return(a.pav()>b.pav());
}
bool sort3u(const duom &a, const duom &b){
    return(a.galvid()>b.galvid());
}
bool sort4u(const duom &a, const duom &b){
    return(a.galmed()>b.galmed());
}

duom::duom(istream &cin){
    cin>>vard_>>pav_;

    // ndrez_.reserve(ndsk);

    int j=0;

    while(true){
        int a;
        if(!(cin>>a)){
            egzrez_=ndrez_[j-1];
            ndrez_.resize(j-1);
            ndrez_.shrink_to_fit();
            break;
        }
        ndrez_.push_back(a);
        j++;
    }

    calc();
}

istream &operator>>(istream &cin, duom &s) {
    string line;
    getline(cin, line);
    istringstream a(line);
    duom temp(a);
    s = temp;
    return cin;
}

ostream &operator<<(ostream &cout, duom &s) {
    s.spausdinti();
    return cout;
}

template <typename sk=int, typename talpa> 
void rusiuoti(sk &x, sk &t, talpa &mok){
    if(t==1){
        if(x==1) sort(mok.begin(), mok.end(), sort1);
        if(x==2) sort(mok.begin(), mok.end(), sort2);
        if(x==3) sort(mok.begin(), mok.end(), sort3);
        if(x==4) sort(mok.begin(), mok.end(), sort4);
    }
    else{
        if(x==1) sort(mok.begin(), mok.end(), sort1u);
        if(x==2) sort(mok.begin(), mok.end(), sort2u);
        if(x==3) sort(mok.begin(), mok.end(), sort3u);
        if(x==4) sort(mok.begin(), mok.end(), sort4u);
    }
}

template <typename sk=int>
void rusiuotilist(sk &x, sk &t, list<duom> &mok) {
    if(t==1) {
        if(x==1) mok.sort(sort1);
        if(x==2) mok.sort(sort2);
        if(x==3) mok.sort(sort3);
        if(x==4) mok.sort(sort4);
    } else {
        if(x==1) mok.sort(sort1u);
        if(x==2) mok.sort(sort2u);
        if(x==3) mok.sort(sort3u);
        if(x==4) mok.sort(sort4u);
    }
}

void duom::calc(){
    int a=accumulate(ndrez_.begin(), ndrez_.end(), 0);
    double sum=a;
    double egz=0;
    double med=0;
    
    sort(ndrez_.begin(), ndrez_.end());

    if(ndrez_.getSize()!=0){
        sum=sum/(ndrez_.getSize());

        auto it = ndrez_.begin();
        advance(it, ndrez_.getSize()/2);

        if (ndrez_.getSize()%2==0){
            auto it1 = it;
            std::advance(it1, -1);
            med = (*it + *it1) / 2.0;
        } 
        else{
            med = *it;
        }
    }
    egz=egzrez_;

    galvid_=sum*0.4+egz*0.6;
    galmed_=med*0.4+egz*0.6;
}

bool pagalVid(const duom &x, const double d){ 
    return x.galvid()<d; 
}
bool pagalMed(const duom &x, const double d){ 
    return x.galmed()<d; 
}

template <typename talpa, typename sk> 
void strategija3(talpa &x, talpa &y, sk t){
    auto it=x.begin();
    auto end=x.end();
    auto tarp=end;

    if(t==3){
        tarp=lower_bound(x.begin(), x.end(), 5.0, pagalVid);
    }
    if(t==4){
        tarp=lower_bound(x.begin(), x.end(), 5.0, pagalMed);
    }

    if(tarp!=end){
        y.insert(y.end(), tarp, end);
        x.erase(tarp, x.end());
    }
}

template <typename talpa, typename sk>
void strategija2(talpa &x, talpa &y, sk t){
    auto it=x.begin();
    auto end=x.end();
    auto tarp=end;

    for(; it!=end; ++it){
        if(t==3&&it->galvid()>=5){
            tarp=it;
            break;
        }
        if(t==4 && it->galmed()>=5){
            tarp=it;
            break;
        }
    }

    if(tarp!=end){
        y.insert(y.end(), tarp, end);
        x.erase(tarp, x.end());
    }
}

template <typename talpa, typename sk>
void strategija1(talpa &x, talpa &y, sk t, talpa &z){
    auto it=x.begin();
    auto begin=x.begin();
    auto end=x.end();
    auto tarp=end;

    for(; it!=end; ++it){
        if(t==3&&it->galvid()>=5){
            tarp=it;
            break;
        }
        if(t==4&&it->galmed()>=5){
            tarp=it;
            break;
        }
    }

    if(tarp!=end){
        cout<<"amangas"<<endl;
        y.insert(y.end(), tarp, end);
        cout<<"amangas"<<endl;
        z.insert(z.end(), begin, tarp);
        cout<<"amangas"<<endl;
        x.erase(x.begin(), x.end());
    }
}

template <typename sk, typename talpa>
void skaitymas(sk &moksk, talpa &mok){
    string temp;

    cin>>temp;
    cin>>temp;
    
    getline(cin, temp);  

    if constexpr (is_same<talpa, Vector<duom>>::value){
        mok.reserve(moksk);
    }

    for(int i=0; i<moksk; i++){
        duom m;

        cin>>m;

        mok.push_back(m);
        
        // cin.ignore(255, '\n');
    }
}

void duom::spausdinti(){
    cout<<setw(25)<<left<<vard_<<setw(25)<<left<<pav_<<setw(18)<<left<<setprecision(3)<<galvid_<<setw(18)<<left<<setprecision(3)<<galmed_;
    cout<<endl;
}

template <typename talpa, typename sk=int>
void isfailo(talpa &mok, sk &s){
    int moksk=0;
    int ndsk=0;
    int maxmoksk=0;
    string failas;

    while(true){
        cout<<"Iveskite faila is kurio imti duomenis"<<endl;
        cin>>failas;

        ifstream file(failas+".txt");

        if(!file.is_open()){
            try{
                throw runtime_error("Klaidingai ivesti duomenys\n"); 
            }
            catch(const runtime_error &e){
                cout<<e.what();
            }
        }
        else{
            string line;

            while(getline(file, line)){
                maxmoksk++;
            }

            file.close();
            break;
        };
    }

    cout<<"Kiek asmenu nuskaityti nuo duoto failo?"<<endl;
    while(!(cin>>moksk)||moksk<0||moksk>=maxmoksk){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
        }
    }

    int x=0;
    int t=0;

    cout<<"Rusiuoti pagal: 1-varda; 2-pavarde; 3-galutini(vid); 4-galutini(med)"<<endl;
    while(!(cin>>x)||x<1||x>4){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
        }
    }

    cout<<"Tvarka: 1-didejimo; 2-mazejimo"<<endl;
    while(!(cin>>t)||t<1||t>2){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
            cout<<"Pasirinkite viena is variantu"<<endl;
        }
    }

    bool uzd4=false;

    cout<<"Ar atliekama 0.4 uzduotis?(1/0)"<<endl;
    while(!(cin>>uzd4)){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
            cout<<"Pasirinkite viena is variantu"<<endl;
        }
    }

    int str;

    if(uzd4==true){
        cout<<"Kuria strategija pasiremti: 1, 2, 3"<<endl;
        while(!(cin>>str)||str<1||str>3){
            try{
                throw runtime_error("Klaidingai ivesti duomenys\n");
            }
            catch(const runtime_error &e){
                cin.clear();
                cin.ignore();
                cout<<e.what();
            }
        }
    }

    freopen((failas+".txt").c_str(), "r", stdin);

    auto start = high_resolution_clock::now();

    skaitymas(moksk, mok);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);

    cout<<"Skaitymo laikas: "<<duration.count()<<endl;

    start = high_resolution_clock::now();

    if constexpr (is_same<talpa, list<duom>>::value){
        rusiuotilist(x, t, mok);
    }
    else{
        // kazkas blogai su situ sortu
        rusiuoti(x, t, mok);
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    cout<<"Rusiavimo laikas: "<<duration.count()<<endl;

    if(uzd4==true){
        auto pazenge=mok;
        pazenge.erase(pazenge.begin(), pazenge.end());
        auto zluge=mok;
        zluge.erase(zluge.begin(), zluge.end());

        start = high_resolution_clock::now();

        if(str==1){
            strategija1(mok, pazenge, x, zluge);
        }
        else if(str==2){
            strategija2(mok, pazenge, x);
        }
        else if(str==3){
            strategija3(mok, pazenge, x);
        }

        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        cout<<"Skirstymo laikas: "<<duration.count()<<endl;

        start = high_resolution_clock::now();

        ifstream file("pazenge.txt");

        if(file.is_open()){
            remove("pazenge.txt");
        }
        file.close();

        freopen("pazenge.txt", "r", stdin);
        freopen("pazenge.txt", "w", stdout);

        cout<<setw(25)<<left<<"Vardas"<<setw(25)<<left<<"Pavarde"<<setw(18)<<left<<"Galutinis (Vid.)"<<setw(18)<<left<<"Galutinis (Med.)";
        cout<<endl;


        for (auto& elem : pazenge) {
            cout<<elem;
        }

        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        freopen("CON", "r", stdin);
        freopen("CON", "w", stdout);

        cout<<"Pazengusiu spausdinimo laikas: "<<duration.count()<<endl;

        auto start = high_resolution_clock::now();

        ifstream filez("zluge.txt");

        if(filez.is_open()){
            remove("zluge.txt");
        }
        filez.close();

        freopen("zluge.txt", "r", stdin);
        freopen("zluge.txt", "w", stdout);

        cout<<setw(25)<<left<<"Vardas"<<setw(25)<<left<<"Pavarde"<<setw(18)<<left<<"Galutinis (Vid.)"<<setw(18)<<left<<"Galutinis (Med.)";
        cout<<endl;

        if(str!=1){
            for (auto& elem : mok) {
                cout<<elem;
            }
        }
        else{
            for (auto& elem : zluge) {
                cout<<elem;
            }
        }

        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        freopen("CON", "r", stdin);
        freopen("CON", "w", stdout);

        cout<<"Zlugusiu spausdinimo laikas: "<<duration.count();

        exit(0);
    }
    return;
}

void kurtifaila(){
    string failas;
    while(true){
        cout<<"Iveskite failo pavadinima"<<endl;
        cin>>failas;

        ifstream file(failas+".txt");

        if(file.is_open()){
            try{
                throw runtime_error("Toks failas jau yra\n"); 
            }
            catch(const runtime_error &e){
                cout<<e.what();
            }
            file.close();
        }
        else{
            file.close();
            freopen((failas+".txt").c_str(), "r", stdin);
            break;
        };
    }
    freopen("CON", "r", stdin);

    cout<<"Iveskite kiek asmenu bus faile"<<endl;
    int moksk;
    while(!(cin>>moksk)||moksk<0){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
        }
    }

    cout<<"Iveskite kiek namu darbu buvo paskirta"<<endl;
    int ndsk;
    while(!(cin>>ndsk)||ndsk<0){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
        }
    }

    auto start = high_resolution_clock::now();

    freopen((failas+".txt").c_str(), "r", stdin);
    freopen((failas+".txt").c_str(), "w", stdout);

    cout<<setw(25)<<left<<"Vardas"<<setw(25)<<left<<"Pavarde";
    
    for(int i=1; i<=ndsk; i++){
        cout<<"ND"<<setw(6)<<left<<i;
    }

    cout<<"Egz."<<endl;

    for(int i=1; i<=moksk; i++){
        cout<<"Vardas"<<setw(19)<<left<<i;
        cout<<"Pavarde"<<setw(19)<<left<<i;

        for(int j=1; j<=ndsk; j++){
            cout<<setw(8)<<rand()%10+1;
        }

        cout<<rand()%10+1;
        if(i!=moksk){
            cout<<endl;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);

    cout<<"Failo kurimo laikas: "<<duration.count()<<endl;
}

void duom::vpskait(){
    cout<<"Irasykite varda"<<endl;
    while(!(cin>>vard_)){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
        }
    }
    cout<<"Irasykite pavarde"<<endl;
    while(!(cin>>pav_)){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
        }
    }
}

void duom::vardoGen(){
    for(int i=0; i<4+rand()%6; i++){
        if(i==0) vard_+=(char) (65+rand()%25);
        else vard_+=(char) (97+rand()%25);
    }
    for(int i=0; i<4+rand()%8; i++){
        if(i==0) pav_+=(char) (65+rand()%25);
        else pav_+=(char) (97+rand()%25);
    }
}

void duom::ndGen(){
    for(int i=0; i<1+rand()%15; i++){
        nd(rand()%11);
    }
}

void duom::egzGen(){
    egz(rand()%11);
}

template <typename sk, typename talpa>
void rankinis(sk &x, sk &moksk, talpa &mok){
    if(moksk!=-1){
        while(true){
            cout<<"1-ranka; 2-generuoti pazymius; 3-generuoti pazymius ir varda/pavarde; 5-sukurti nauja faila; 6-baigti darba"<<endl;
            if(!(cin>>x)||x<1||x>6||x==4){
                try{
                    throw runtime_error("Klaidingai ivesti duomenys\n");
                }
                catch(const runtime_error &e){
                    cin.clear();
                    cin.ignore();
                    cout<<e.what();
                }
            }
            else break;
        }
    }
    
    duom m;
    moksk++;

    if(x==3){
        m.vardoGen();
    }
    else{
        m.vpskait();
    }
    if(x==2||x==3){
        m.ndGen();
    }
    else{
        cout<<"Irasykite nd rezultatus po kiekvieno spaudziant enter, jei baigete parasykite skaiciu netelpanti i desimtbales sistemos intervala"<<endl;
        int h;
        while(true){
            while(!(cin>>h)){
                try{
                    throw runtime_error("Klaidingai ivesti duomenys\n");
                }
                catch(const runtime_error &e){
                    cin.clear();
                    cin.ignore();
                    cout<<e.what();
                }
            }
            if(h<0||h>10){
                break;
            }
            m.nd(h);
        }
    }
    int eg;
    if(x==2||x==3){
        m.egzGen();
    }
    else{
        cout<<"Irasykite egzamino rezultata"<<endl;
        while(!(cin>>eg)||eg<0||eg>10){
            try{
                throw runtime_error("Klaidingai ivesti duomenys\n");
            }
            catch(const runtime_error &e){
                cin.clear();
                cin.ignore();
                cout<<e.what();
            }
        }
    }

    m.egz(eg);

    m.calc();
    
    cout<<"Jei norite prideti daugiau mokiniu spauskite 1, jei baigete, spauskite bet koki kita svaika skaiciu"<<endl;
    int a;

    while(!(cin>>a)){
        try{
            throw runtime_error("Klaidingai ivesti duomenys\n");
        }
        catch(const runtime_error &e){
            cin.clear();
            cin.ignore();
            cout<<e.what();
        }
    }

    mok.push_back(m);

    if(a==1) rankinis(x, moksk, mok);

    moksk++;
}

void input(){

    srand(time(nullptr));

    int x;
    int s;

    while(true){
        cout<<"1-Vector; 2-List; 3-Deque"<<endl;
        if(!(cin>>s)||s<1||s>3){
            try{
                throw runtime_error("Klaidingai ivesti duomenys\n");
            }
            catch(const runtime_error &e){
                cin.clear();
                cin.ignore();
                cout<<e.what();
            }
        }
        else break;
    }

    Vector<duom> mokV;
    list<duom> mokL;
    deque<duom> mokD;

    double duration = 0;

    while(true){
        cout<<"1-ranka; 2-generuoti pazymius; 3-generuoti pazymius ir varda/pavarde; 4-skaityti duomenis is failo; 5-sukurti nauja faila; 6-baigti darba"<<endl;
        if(!(cin>>x)||x<1||x>6){
            try{
                throw runtime_error("Klaidingai ivesti duomenys\n");
            }
            catch(const runtime_error &e){
                cin.clear();
                cin.ignore();
                cout<<e.what();
            }
        }
        else break;
    }

    if(x==6) exit(0);

    if(x==5){
        kurtifaila();
        input();
    }

    if(x==4){
        if(s==1) isfailo(mokV, s);
        if(s==2) isfailo(mokL, s);
        if(s==3) isfailo(mokD, s);
    }
    else{
        int moksk=-1;
        if(s==1) rankinis(x, moksk, mokV);
        if(s==2) rankinis(x, moksk, mokL);
        if(s==3) rankinis(x, moksk, mokD);
    }

    cout<<setw(25)<<left<<"Vardas"<<setw(25)<<left<<"Pavarde"<<setw(18)<<left<<"Galutinis (Vid.)"<<setw(18)<<left<<"Galutinis (Med.)"<<endl;
    cout<<"------------------------------------------------------------------------------------"<<endl;

    if(s==1){
        for(auto& elem : mokV){
            cout<<elem;
        }
    }
    else if(s==2){
        for(auto& elem : mokL){
            cout<<elem;
        }
    }
    else if(s==3){
        for(auto& elem : mokD){
            cout<<elem;
        }
    }

    return;
}

// void testas(){
//     duom t1;

//     // input operation test
//     istringstream is("Vardas1                  Pavarde1                  5       9       4       5       10      8       7       10      10");

//     is>>t1;

//     // output operation test
//     cout<<t1;

//     // copy constructor test
//     duom t2(t1);

//     cout<<t2;

//     // move constructor test
//     duom t3(move(t2));

//     cout<<t2;
//     cout<<t3;

//     duom t10;

//     istringstream iss("Lebronas Dzeimsas 10 10 10 10 10 10 7 10 9");

//     iss>>t10;

//     // copy assignment test
//     duom t4=t10;

//     cout<<t4;

//     // move assignment test
//     duom t5=move(t10);
    
//     cout<<t5;
//     cout<<t10;
// }