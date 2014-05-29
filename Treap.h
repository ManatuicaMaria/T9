// Manatuica Maria 313CA

#ifndef TREAP_H
#define TREAP_H

#include <cstdlib>


template <typename T> struct Treap {

    T key;
    int priority;
    Treap<T> *left, *right;
    bool nil;

    // Pentru a putea determina a k-a cheie din treap trebuie ca 
    // fiecare nod sa retina numarul de noduri din subarborele sau
 
    int nr_nodes;

    // Creaza un nod nil
    Treap() : priority(-1),left(NULL), right(NULL), nil(true), nr_nodes(0) {}

    // Elibereaza memoria alocata treap-ului
    ~Treap(){
        if (left) delete left;
        if (right) delete right;
    }

    // Adauga date, transformand un nod nil intr-un nod obisnuit
    void addData(T key, int priority) {
        this->nil = false;
        this->key = key;
        this->priority = priority;
        this->nr_nodes = 1;
        this->left = new Treap();
        this->right = new Treap();
    }
  
    // Sterge un nod obisnuit, transformandu-l intr-unul nil
    void delData() {
        this->nil = true;
        this->priority = -1;
        delete this->left;
        delete this->right;
	    left = right = NULL;
        this->nr_nodes = 0;
    }

    // Determina daca un nod este nil sau nu
    bool isNil() {
        return this->nil;
    }

    // Determina daca o cheie se afla sau nu in treap
    // folosindu-se de invariantul de BST
    bool find(T key) {

        if (this->isNil()) {
           return false;
        }
        if( key == this->key){
		    return true;
	    }
	
    	if (key<this->key){
    		return this->left->find(key);
    	}else{
    		return this->right->find(key);
    	}
        return false;
    }

    // Face o rotatie la dreapta a subarborelui dat de nod
    void rotateRight(Treap<T> *&nod) {
        // Nodul din stanga va deveni noul nod radacina
        // iar nodul radacina va deveni fiul dreapta al acestuia
        // ce va avea ca fiu stanga vechiul fiu dreapta al nodului
        // devenit radacina
        Treap<T> *p = nod->left;
        nod->left = p->right;
        p->right = nod;
        nod = p;
   	
        // Recalculeaza dimensiunea subarborilor in functie de subarborii stanga 
        // dreapta ai fiului dreapta care nu si-au modificat dimensiunea
   
        nod->right->nr_nodes = nod->right->left->nr_nodes+nod->right->right->nr_nodes+1;
        nod->nr_nodes = nod->left->nr_nodes+nod->right->nr_nodes+1;
    }

    // Face o rotatie la stanga a subarborelui dat de nod
    void rotateLeft(Treap<T> *&nod) {
  	    // Nodul din dreapta va deveni noul nod radacina
        // iar nodul radacina va deveni fiul stanga al acestuia
        // ce va avea ca fiu dreapta vechiul fiu stanga al nodului
        // devenit radacina
        Treap<T> *p = nod->right;
   	    nod->right = p->left;
        p->left = nod;
        nod = p;
    
        // Recalculeaza dimensiunea subarborilor in functie de subarborii stanga 
        // dreapta ai fiului stanga care nu si-au modificat dimensiunea

        nod->left->nr_nodes = nod->left->left->nr_nodes+nod->left->right->nr_nodes+1;
        nod->nr_nodes= nod->left->nr_nodes+nod->right->nr_nodes+1;
    
    }

    // Insereaza in treap nodul cu cheia key si prioritatea priority
    void insert(Treap<T> *&fatherPointer, T& key,int priority) {
        // Daca am gasit nodul corespunzator adaugam datele in acesta
        if (this->isNil()) {
            this->addData(key, priority);
            return ;
        }

        // Altfel inserez recursiv pastrand invariantul de BST
        if (key < this->key) {
		    this->left->insert(this->left,key,priority);
        } else {
            this->right->insert(this->right,key,priority);
        }

        // Incrementez dimensiunea subarborelui curent
        this->nr_nodes++;

        // Fac rotatii daca este nevoie, pentru a pastra
        // invariantul de heap
        if (this->left->priority > this->priority) {
		    rotateRight(fatherPointer);
        } else if (this->right->priority > this->priority) {
		    rotateLeft(fatherPointer);
        }
	
    }

    // Sterge nodul cu cheia key din treap
    void erase(Treap<T> *&fatherPointer, T key) {
        // Daca nu il gaseste nu modifica treapul
        if (this->isNil()  ) {
            return ;
        }
   
        // Decrementez dimensiunea subarborelui curent
	    this->nr_nodes--;
	
        // Daca cheia este mai mica sau mai mare cu cea curenta
        // mergem pe subarborele stanga sau dreapta
        // Altfel inseamna ca l-am gasit si mai intai
        // verific daca are fii, si fac rotatiile corespunzatoare 
        // pentru a pastra invariantele 
        // daca nu are fii stergem datele din nod si il facem nil
        if (key < this->key ) {
		    this->left->erase(this->left,key);
        } else if (key > this->key ) {
		    this->right->erase(this->right,key);
        } else if (this->left->isNil() && this->right->isNil()) {
      	    this->delData();
        } else {
            if (this->left->priority > this->right->priority) {
			    rotateRight(fatherPointer);
			    fatherPointer->erase(fatherPointer,key);
            } else {
			    rotateLeft(fatherPointer);
    		    fatherPointer->erase(fatherPointer,key);
            }
        }
    
    }

    // Intoarce a k-a cheie din treap in ordine descrescatoare
    // pe baza nr_nodes
    T& findK(int k) {
        // Daca in subarborele drept sunt k-1 noduri
        // nodul curent este nodul k , altfel caut recursiv in
        // subarborele drept daca are mai mult de k-1 noduri
        // sau in cel stang altfel, cautand doar k-nr_noduri_deja_verificate
        if ( this->right->nr_nodes == k-1){
        	return this->key;
        }else{
	    	if ( this->right->nr_nodes > k-1){	
			    return this->right->findK(k);
		    }else{
			    return this->left->findK(k-(this->right->nr_nodes)-1);
		    }
	    }
    
    }
    
    // Intoarce dimensiunea din subarborele curent
    int& get_nr_nodes(){
        return this->nr_nodes;
    }

    
};

#endif
