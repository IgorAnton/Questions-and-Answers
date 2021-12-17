#include <iostream>
#include <vector>
#include <string.h>
#include <stack>
#include <queue>
#include <algorithm>


using namespace std;

int ID = 100;

struct Cvor{
    int ocena = 0;
    int id;

    string pitanje;
    vector<Cvor*> deca;

    Cvor(string p){
        pitanje = p;
        id = ID++;
    }

};

Cvor* kreirajCvor(string p){

    Cvor *pit = new Cvor(p);

    return pit;
}


void dodajPitanje(vector<Cvor *> &pitanja,Cvor* pitanje){

    pitanja.push_back(pitanje);

    cout << "\nDodato pitanje\n";

}

void dodajOdgovor(vector<Cvor *> &pitanja,string p1, string odg){

    int sz = pitanja.size();


    for(int i = 0 ; i < sz;  ){

        stack<Cvor*> st;
        st.push(pitanja[i++]);

        while(st.empty() != true){

            Cvor* tr = st.top();
            st.pop();

            if(tr != 0){
                if(tr->pitanje == p1 && tr->deca.size() <10){
                    Cvor *nw = new Cvor(odg);
                    tr->deca.push_back(nw);
                    cout << "\nUspesno dodato\n";

                }
                int n = tr->deca.size();
                n = n - 1 ;
                for(auto  j = n ; j>=0; j = j - 1){

                    st.push(tr->deca[j]);
                }

            }
        }

    }


}

Cvor* pretragaPitanja(vector<Cvor *> &pitanja,string p1){

    int n = pitanja.size();
    for(int i = 0 ; i < n ; i++ ){
        if(p1 == pitanja[i]->pitanje){
            return pitanja[i];
        }
    }
    cout << "\nNeuspesno nadjeno\n";
    return nullptr;


}

void povecajOcenu(vector<Cvor*> &pitanja,string odg,int br){

    int sz = pitanja.size();


    for(int i = 0 ; i < sz;  ){

        stack<Cvor*> st;
        st.push(pitanja[i++]);

        while(st.empty() != true){

            Cvor* tr = st.top();
            st.pop();

            if(tr != 0){
                if(tr->pitanje == odg){
                    tr->ocena+= br;
                    cout << "\nUspesno uvecano\n";
                }
                int n = tr->deca.size();
                n = n - 1 ;
                for(auto  j = n ; j>=0; j = j - 1){
                    st.push(tr->deca[j]);
                }

            }
        }

    }

}
void ispisPitanja(vector<Cvor*> &pitanja){

    int n = pitanja.size();

    if(n == 0)
    {
        cout << "\nNiste uneli ni jedno pitanje\n";
        return;
    }

    for(int i = 0 ; i < n ; i++){
        cout << pitanja[i]->pitanje << endl;
    }
}

void izbrisiPitanje(vector<Cvor*> &pitanja, string pit){

    int n = pitanja.size();

    for(int i = 0 ; i < n ; i++){
        if(pitanja[i]->pitanje == pit){
            pitanja.erase(pitanja.begin()+i);
            cout << "\nIzbirsano pitanje\n";
            break;
        }
    }
}

Cvor* pretragaOdgovora(vector<Cvor*> &pitanja, string pit, string odg){

    int n = pitanja.size();

    for(int i = 0 ; i < n ; i++){

        if(pitanja[i]->pitanje == pit ) {

            stack<Cvor *> st;
            st.push(pitanja[i]);

            while (st.empty() != true) {

                Cvor *tr = st.top();
                st.pop();

                if (tr != 0) {
                    if (tr->pitanje == odg) {
                        cout << "\nUsepsno pronajdeno\n";
                        return pitanja[i];
                    }
                    int n = tr->deca.size();
                    n = n - 1;
                    for (auto j = n; j >= 0; j = j - 1) {
                        st.push(tr->deca[j]);
                    }

                }
            }
        }
    }
    cout << "\nNesupesno\n";
    return nullptr;
}

void ispisiJednogPitanja(vector<Cvor*> &pitanja,string pit){
    int n = pitanja.size();

    for(int i = 0 ; i < n ; i++){

        if(pitanja[i]->pitanje == pit ) {
            int dubina=0;
            stack<pair<Cvor *,int>> st;
            st.push({pitanja[i],dubina});

            while (st.empty() != true) {

                Cvor *tr = st.top().first;


                if (tr != 0) {

                    cout<<string(3* st.top().second,' ')  <<tr->pitanje << "\n";
                    st.pop();
                    int n = tr->deca.size();
                    n = n - 1;
                    dubina++;
                    for (auto j = n; j >= 0; j = j - 1) {
                        st.push({tr->deca[j],dubina});

                    }

                }
            }
        }
    }
}


bool veci(Cvor *c1, Cvor *c2){

    return c1->ocena > c2->ocena;
}

Cvor* nadjiMax(vector<Cvor*> &pitanja){

    Cvor* maxOdg = pitanja[0];
    auto maxi = pitanja[0]->ocena;
    auto n = pitanja.size();

    for(int i = 1 ; i < n ; i++){
        stack<Cvor *> st;
        st.push(pitanja[i]);

        while (st.empty() != true) {

            Cvor *tr = st.top();
            st.pop();

            if (tr != 0) {

                if(tr->ocena > maxi) {

                    maxi = tr->ocena;
                    maxOdg = pitanja[i];
                }


                int n = tr->deca.size();
                n = n - 1;
                for (auto j = n; j >= 0; j = j - 1) {
                    st.push(tr->deca[j]);
                }

            }
        }
    }
    return maxOdg;
    }

void brisiOdogovr(vector<Cvor*> &pitanja,string pit,string odg){

    int sz = pitanja.size();
    Cvor *otac;

    bool nasao = false;
    for(int i = 0 ; i < sz; i = i+1 ){

        if(pitanja[i]->pitanje == pit){
            stack<Cvor*> st;
            st.push(pitanja[i]);

            while(st.empty() != true){

                Cvor* tr = st.top();
                st.pop();

                if(tr != nullptr){

                    int n = tr->deca.size();
                    n = n - 1 ;
                    for(auto  j = n ; j>=0; j = j - 1){

                        if(tr->deca[j]->pitanje == odg){
                            otac = tr;
                            nasao = true;
                            break;
                        }

                        st.push(tr->deca[j]);
                    }

                    if(nasao)
                        break;

                }
            }
            if(nasao){
                int ind = 0;
                for(int j = 0 ; j < otac->deca.size(); j = j+1)
                {
                    if(otac->deca[j]->pitanje == odg)
                    {
                        ind = i;
                        break;
                    }
                }
                otac->deca.erase(otac->deca.begin()+ind);
                cout << "\nObrisano\n";
            }
        }
    }

}

void sortiraj(vector<Cvor*> &pitanja){

    int sz = pitanja.size();

    for(int i = 0 ; i < sz; i = i+1 ){

            stack<Cvor*> st;
            st.push(pitanja[i]);

            while(st.empty() != true) {

                Cvor *tr = st.top();
                st.pop();

                if (tr != nullptr) {

                    sort(tr->deca.begin(), tr->deca.end(), veci);

                    int n = tr->deca.size();
                    n = n - 1;
                    for (auto j = n; j >= 0; j = j - 1) {
                        st.push(tr->deca[j]);
                    }
                }
            }
    }

}

int findMaxDepth(vector<Cvor*> &pitanja, string pit){
    int maxDepth;
    for(int i = 0 ; i < pitanja.size(); i++){

        if(pitanja[i]->pitanje == pit){

            maxDepth = 1;
            queue<Cvor*> q;
            q.push(pitanja[i]);

            cout << q.front()->pitanje << endl;
            int br = q.front()->deca.size();

            while(!q.empty()){
                Cvor *tmp = q.front();
                q.pop();
                br--;
                if(br == 0){
                    br = tmp->deca.size();
                    maxDepth++;
                }
                for(int j = 0 ; j < tmp->deca.size(); j++){
                    q.push(tmp->deca[j]);
                    cout << tmp->deca[j]->pitanje <<  endl;
                }
            }
        }
    }

    return maxDepth;
}


int main() {

    vector<Cvor*> pitanja;

    int odgovor = 1;

    while(odgovor) {
        cout << "Dobrodosli u najbolje resenje ovog domaceg :) \n";
        cout << "Izaberite jednu od sledecih opcija!\n";
        cout << "1.  Dodajte jedno pitanje\n";
        cout << "2.  Dodajte odgovor na zadato pitanje\n";
        cout << "3.  Pronadjite zadato pitanje\n";
        cout << "4.  Povecajte ocenu nekog odgovora na osnovu zadate vrednosti\n";
        cout << "5.  Ispisi sva pitanja\n";
        cout << "6.  Izbrisi dato pitanje\n";
        cout << "7.  Proandji pitanje na osnovu datog odgovora\n";
        cout << "8.  Ispisi jedno pitanje\n";
        cout << "9.  Pornadji pitanje sa najbolje ocenjenim odgovorom\n";
        cout << "10. Izbirsi odgovor na zadato pitanje\n";
        cout << "11. Sortiraj stablo\n";
        cout << "12. Obrisi sva pitanja\n";
        cout << "13. Nadji maksimalnu dubinu (level orderom)\n";
        cout << "0.  Zavrsi program\n";
        cin >> odgovor;
        getchar();

            switch (odgovor) {
                case 1: {
                    string s;
                    getline(cin,s);
                    //cin >> s;
                    Cvor *p = new Cvor(s);
                    dodajPitanje(pitanja, p);
                    cout << endl;
                    break;
                }
                case 2: {
                    string pit;
                    string odg;

                    getline(cin,pit);
                    getline(cin,odg);

                   /* cin >> pit;
                    cin >> odg;*/
                    dodajOdgovor(pitanja, pit, odg);
                    cout << endl;
                    break;
                }
                case 3: {
                    string pit;
                    getline(cin,pit);
                    //cin >> pit;
                    cout << pretragaPitanja(pitanja, pit);
                    cout << endl;
                    break;
                }
                case 4: {
                    string odg;
                    int br;
                    getline(cin,odg);
                    //cin >> odg;
                    cin >> br;
                    povecajOcenu(pitanja, odg, br);
                    cout << endl;
                    break;
                }
                case 5: {
                    ispisPitanja(pitanja);
                    cout << endl;
                    break;
                }
                case 6: {
                    string pit;
                    getline(cin,pit);
                    //cin >> pit;
                    izbrisiPitanje(pitanja, pit);
                    cout << endl;
                    break;
                }
                case 7: {
                    string pit;
                    string odg;

                    getline(cin,pit);
                    getline(cin,odg);
                   /* cin >> pit;
                    cin >> odg;*/
                    cout << pretragaOdgovora(pitanja, pit, odg);
                    cout << endl;
                    break;
                }
                case 8: {
                    string pit;
                    getline(cin,pit);
                    //cin >> pit;
                    ispisiJednogPitanja(pitanja, pit);
                    cout << endl;
                    break;
                }
                case 9: {
                    cout << nadjiMax(pitanja)->pitanje << endl;
                    break;
                }
                case 10: {
                    string pit, odg;

                    getline(cin,pit);
                    getline(cin,odg);
                    /*cin >> pit;
                    cin >> odg;*/
                    brisiOdogovr(pitanja, pit, odg);
                    cout << endl;
                    break;
                }
                case 11: {
                    sortiraj(pitanja);
                    cout<<"\nSortirano";

                    cout << endl;
                    break;
                }
                case 12:{
                    pitanja.erase(pitanja.begin(),pitanja.end());
                    cout << "\nObrisana sva pitanja\n";
                    break;
                }
                case 13:{
                    string p;
                    getline(cin,p);
                    cout << findMaxDepth(pitanja,p) << endl;

                }
                case 0 :{
                    cout << "Hvala na koriscenju!\nUzivajte u zivotu! :)\n";
                    break;
                }
                default:
                {
                    cout << "Pogresan unos, probajte ponovo!" <<endl<< endl;
                    break;
                }


            }
        }


    return 0;
}
