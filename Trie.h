// Manatuica Maria 313CA

#ifndef TRIE_H
#define TRIE_H
#include "Treap.h"


template <typename T>
class Trie{
    // Vectorul de fii
    Trie<T>* next[10];
    // Container-ului nodului
    Treap<T>* treap;
    
public:
    // Constructor
    Trie(){
        this->treap = NULL;
        for(int i =2;i<10;i++){
            this->next[i] = NULL;
        }   
    }

    // Destructor
	~Trie(){
		if (treap) delete treap;
		for ( int i=2; i<10; i++){
			if( next[i]) delete next[i];
		}
	}
   
    // Insereaza nodul cu cheia key si prioritatea priority
    // in treap-ul corespunzator combinatiei de cifre din 
    // vectorul indici. fin reprezinta sfarsitul combinatiei
    // iar poz pozitia curenta in vectorul de indici
    void insert(T& key,int priority ,int indici[],int fin,  int poz){
        // Daca am ajuns la finalul combinatiei de cifre
        // inseram in treap-ul curent
        if (poz == fin+1){
			if (! treap) treap = new Treap<T>();
           
            this->treap->insert(this->treap,key,priority);
			return;
        }
        // Altfel avansam in fiul corespunzator indicelui
         else{
            if ( this->next[indici[poz]] == NULL ){
                this->next[indici[poz]] = new Trie<T>();
            }
            this->next[indici[poz]]->insert(key,priority,indici,fin,poz+1);
            return;
        }
    }
    
    // Intoarce a k-a cheie din treap-ul corespunzator combinatiei de 
    // cifre din vectorul indici. fin si poz au aceleasi semnificatii
    // ca si la functia insert
    T& findK(int indici[], int fin,int poz, int k,int priority){
        // Daca am ajuns la sfarsitul combinatiei de cifre
        // returnez a k-a cheie din treap-ul curent
        if( poz == fin+1){
            // Daca k este mai mare decat numarul de noduri din treap
            // consideram cautarea ciclic pana cand k va fi mai mic sau egal
            // decat dimensiunea treap-ului
            k = k%treap->get_nr_nodes();
            k++;
			return treap->findK(k);

        }
        // Altfel avansez in fiul corespunzator indicelui
        else
            return this->next[indici[poz]]->findK(indici,fin,poz+1,k,priority);
    }

    
    // Sterge cheia key din treap-ul corespunzator combinatiei de cifre
    // din vectorul indici. fin si poz au aceleasi seminificatii ca si
    // la functia insert 
    void erase( T& key,int indici[], int fin,int poz){
        // Daca am ajuns la finalul combinatiei de cifre
        // sterg cheia din treap-ul curent   
        if ( poz == fin+1){
            this->treap->erase(this->treap,key);
			return;
        }
        // Altfel avansez in fiul corespunzator indicelui
        else
        this->next[indici[poz]]->erase(key,indici,fin,poz+1);
    }
    
};

#endif
