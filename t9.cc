// Manatuica Maria 313CA

#include "Trie.h"
#include <fstream>
#include <string>
#include <cstdlib>
   
// Structura ce va reprezenta o cheie a treap-urilor
struct nod{
    // Cuvantul
    std::string word;
    // Numarul de aparitii ale lui
    int nr_ap;
	
    // Supraincarcarea operatorilor relationali
    bool operator==(const nod& b){
        return (nr_ap == b.nr_ap && word.compare(b.word)==0 );
    }
    bool operator<(const nod& b){
        if (nr_ap<b.nr_ap){
            return true;
        }
        if(nr_ap == b.nr_ap && word.compare(b.word) > 0)
                return true;
        return false;
        
    }
    bool operator>(const nod& b){
        if (nr_ap>b.nr_ap){
            return true;
        }
        if(nr_ap == b.nr_ap && word.compare(b.word) <0)
                return true;
        return false;
    }
	
};

int main(){
    std::ifstream fin;
    std::ofstream fout;
    int N,M,i,l,k,j,end;
    std::string cuvant,nr_ord;
    Trie<nod >* dictionar = new Trie<nod >();
    int cifre[30];
    nod treap_key;
    int val_num[26];

    fin.open("date.in");
    fout.open("date.out");
    srand(time(0));

    // Construiesc val_num, vectorul ce va determina ce cifra ii corespunde
    // fiecarei litere din alfabetul englez. ex: literei 'a' ii va corespunde
    // val_num[0] si asa mai departe
    l = 0;
    for ( i=0;i<8;i++){
        if ( i == 5 || i == 7){
            k = 4;
        } else {
            k = 3;
        }
        for(j = 0;j<k;j++){
            val_num[l] = i+2; 
            l++;    
        }
    }  
	
	// Pentru fiecare cuvant din lista disponibila softului
    // calculez combinatia de cifre care ii corespunde 
    // dupa care il inserez in baza de date ( trie-ul dictionar)
    fin>>N;
    for (i =0;i<N;i++){
        fin>>treap_key.word>>treap_key.nr_ap;
        for( j =0; j<(int)treap_key.word.size();j++){
            cifre[j] =val_num[treap_key.word[j] - 'a'];
        }
        dictionar->insert(treap_key,rand()%1000,cifre,treap_key.word.size()-1,0);
    }
    
    // Pentru fiecare combinatie de taste primite de la tastatura
    // cifre va retine combinatia de cifre pentru care trebuie sa
    // determin cuvantul, in nr_ord se va afla indicele pentru a determina
    // al catelea cuvant in functie de nr de aparitii trebuie returnat 
    // Odata gasit il sterg din dictionar pentru a-i incrementa nr de aparitii
    // si a-l insera cu aceasta noua valoare
    fin>>M;
    for(i = 0;i<M;i++){
        fin>>cuvant;
        j = 0;
        while (cuvant[j]!='*' && j<(int)cuvant.size()){
            cifre[j]=(cuvant[j]-'0');
            j++;
        }
        end = j-1;
        j++;
        nr_ord = "";
        while ( j<(int)cuvant.size()){
            nr_ord+=cuvant[j];
            j++;
        }
        k = atoi(nr_ord.c_str());
        treap_key = dictionar->findK(cifre,end,0,k,rand()%1000);
        fout<<treap_key.word<<"\n";
        dictionar->erase(treap_key,cifre,end,0);
        treap_key.nr_ap++;
        dictionar->insert(treap_key,rand()%1000,cifre,end,0);
         
    }

    fin.close();
    fout.close();
    delete dictionar;      
    return 0;
}
