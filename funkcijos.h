#ifndef FUNKCIJOS_H  
#define FUNKCIJOS_H  

#include <bits/stdc++.h>
#include "Vector.h" 

using namespace std;
using namespace std::chrono;
using std::setw;
using std::left;

class zmogus{
    protected:
        string vard_;
        string pav_;
    public:  
        virtual void vardas(const string &va) = 0;
        virtual void pavarde(const string &pa) = 0;

        virtual string vard() const = 0;
        virtual string pav() const = 0;

        zmogus() {}
        ~zmogus() {}

        // copy c
        zmogus(const zmogus &temp)
            : vard_(temp.vard_), pav_(temp.pav_) {}

        // move c
        zmogus(zmogus &&temp) noexcept 
            : vard_(move(temp.vard_)), pav_(move(temp.pav_)) {}

        // copy a
        zmogus& operator=(const zmogus &temp) {
            if(this!=&temp){
                vard_=temp.vard_;
                pav_=temp.pav_;
            }
            return *this;
        }

        // move a
        zmogus& operator=(zmogus &&temp) noexcept { 
            if(this!=&temp){
                vard_=move(temp.vard_);
                pav_=move(temp.pav_);
            }
            return *this;
        }
};

class duom : public zmogus{
    private:
        Vector<int> ndrez_;
        int egzrez_;
        double galvid_, galmed_;
    public:
        duom() : galvid_(0), galmed_(0) {}
        ~duom() {}
        duom(istream &cin);

        // copy c
        duom(const duom &temp)
            : zmogus(temp), ndrez_(temp.ndrez_), egzrez_(temp.egzrez_), galvid_(temp.galvid_), galmed_(temp.galmed_) {}

        // move c
        duom(duom &&temp) noexcept 
            : zmogus(move(temp)), ndrez_(move(temp.ndrez_)), egzrez_(move(temp.egzrez_)), galvid_(move(temp.galvid_)), galmed_(move(temp.galmed_)) {
                temp.egzrez_=NULL;
                temp.galvid_=NULL;
                temp.galmed_=NULL;
            }

        // copy a
        duom& operator=(const duom &temp) {
            if(this!=&temp){
                zmogus::operator=(temp);
                ndrez_=temp.ndrez_;
                egzrez_=temp.egzrez_;
                galvid_=temp.galvid_;
                galmed_=temp.galmed_;
            }
            return *this;
        }

        // move a
        duom& operator=(duom &&temp) noexcept {
            if(this!=&temp){
                zmogus::operator=(move(temp));
                ndrez_=move(temp.ndrez_);
                egzrez_=move(temp.egzrez_);
                temp.egzrez_=NULL;
                galvid_=move(temp.galvid_);
                temp.galvid_=NULL;
                galmed_=move(temp.galmed_);
                temp.galmed_=NULL;
            }
            return *this;
        }

        inline string vard() const override { return this->vard_; }
        inline string pav() const override { return this->pav_; }
        inline double galvid() const { return galvid_; }
        inline double galmed() const { return galmed_; }

        void vardas(const string &va) override { this->vard_=va; }
        void pavarde(const string &pa) override { this->pav_=pa; }
        void nd(int nd) { ndrez_.push_back(nd); }
        void egz(int egz) { egzrez_=egz; }
        void calc();

        void vpskait();
        void skaitduom();
        void spausdinti();
        void vardoGen();
        void ndGen();
        void egzGen();

        friend istream& operator>>(istream &cin, duom &s);
        friend ostream& operator<<(ostream &cout, const duom &s);

};

bool sort1(const duom &, const duom &);
bool sort2(const duom &, const duom &);
bool sort3(const duom &, const duom &);
bool sort4(const duom &, const duom &);
bool sort1u(const duom &, const duom &);
bool sort2u(const duom &, const duom &);
bool sort3u(const duom &, const duom &);
bool sort4u(const duom &, const duom &);
bool pagalVid(const duom &x, const double d);
bool pagalMed(const duom &x, const double d);

template <typename sk=int, typename talpa>
void rusiuoti(sk &, sk &, talpa &);

template <typename talpa, typename sk> 
void strategija3(talpa &, talpa &, sk);

template <typename talpa, typename sk> 
void strategija2(talpa &, talpa &, sk);

template <typename talpa, typename sk> 
void strategija1(talpa &, talpa &, sk, talpa &);

template <typename sk, typename talpa>
void skaitymas(sk &, talpa &);

template <typename talpa, typename sk=int>
void isfailo(talpa &, sk &);

void kurtifaila();

template <typename sk, typename talpa>
double rankinis(sk &, talpa &, sk &);

void input();

void testas();

#endif