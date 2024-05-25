#include<iostream>

using namespace std;

template<class T>
class LinkedList
{
    public :
        class Node
        {
            public :
                Node() : next(nullptr), data(0) {}
                Node(int d) : next(nullptr), data(d) {}
                Node(Node *n) : next(n), data(0) {}
                Node(Node *n, int d) : next(n), data(d) {}
                int data;
                Node *next;
        };

        LinkedList() : head(NULL) {}
        ~LinkedList() {
            while(head != NULL){
                Node *nextDel = head;
                head = head -> next;
                delete nextDel;
            }
        }
        bool addFromHead(int d) {
            
            Node *newnode = new Node(d);
            if ( newnode == NULL ) return false;
            newnode -> next = head;
            head = newnode;
            return true;
        
        }

        bool addFromTail(int d) {
            Node *newnode = new Node(d);
            if ( newnode == NULL ) return false;
            if ( head == NULL ) {
                head = newnode;
                return true;
            }
            Node *temp;
            for ( temp = head ; temp -> next != NULL ; temp = temp -> next ) continue;
            temp -> next = newnode;
            return true;

        }

        bool removeFromHead() {
            if ( head == NULL ) return false;
            Node *temp = head->next;
            delete head;
            head = temp;
            return true;
        }

        bool removeFromTail() {
            if ( head == NULL ) return false;
            if ( head -> next == NULL ) {
                delete head;
                head = NULL;
                return true;
            }
            Node *temp;
            for ( temp = head ; temp -> next != NULL && temp -> next -> next != NULL ; temp = temp -> next ) continue;
            delete temp -> next;
            temp -> next = NULL;
            return true;
        }

        friend ostream &operator<<(ostream &o, LinkedList *l) {
            o << "{";
            Node *temp;
            for ( temp = l -> head ; temp != NULL ; temp = temp -> next ) {
                o << temp -> data;
                if ( temp -> next != NULL ) o << ", ";
            }
            o << "}\n";
            return o; 
        
        }

        size_t getSize() const {
            size_t count = 0;
            Node *temp;
            for ( temp = head ; temp != NULL ; temp = temp ->next ) {
                count++;
            }
            return count;
        }

        int searchData(int d) {
            Node *temp = head;
            while (temp != nullptr) {
                if (temp->data == d) {
                    return true; 
                }
                temp = temp->next;
            }
            return false;
    
        }

        int operator[](int i) {
            Node *temp = head;
            int count = 0;
            
            while (temp != nullptr) {
                if (count == i) {
                    return temp->data;
                }
            count++;
            temp = temp->next;
            }
            
        }
    
    protected :
        Node *head;
} ;

template<class T>
class Set : private LinkedList<T>
{
    public :
    
        Set<T>() : LinkedList<T>() {}
        ~Set<T>(){}

        bool addElement(T d) {
            if ( LinkedList<T>::addFromHead(d) ) {
                return true;
            }
            else {
                return false;
            }
        }

        friend ostream &operator<<(ostream &o, Set<T> *s) {
            o << "{";
            typename LinkedList<T>::Node *temp;

            temp = s -> head;
            while ( temp != NULL ) {
                o << temp;   
                if ( temp -> next != NULL ) o << ", ";        
                temp = temp -> next;
            }
            o << "}\n";
            return o;
        }

        Set<T>* operator+(Set<T> *s) {
            
            Set *temp;
            temp = this;

            typename LinkedList<T>::Node *temp2;
            temp2 = s ->head;

            while ( temp2 != NULL ) {

               temp->addElement( temp2 -> data );
               temp2 = temp2 -> next;

            }
            
            
            return temp;
        }

        Set<T>* operator-(Set<T> *s) {
            
            typename LinkedList<T>::Node *temp , *temp2;
            temp = this->head;
            temp2 = s->head;
            
            Set *total;
            for ( temp ; temp != NULL ; temp = temp -> next  ) {
                while ( temp != NULL ) {
                    if ( temp == temp2 ) {
                        total->addElement(temp->data);
                    }
                    temp2 = temp2 -> next;
                }
            }
            delete temp , temp2;
            Set *fina;
            for ( temp2 = total -> head ; temp2 != NULL ; temp2 = temp2 -> next ) {
                for ( temp = this -> head ; temp != NULL ; temp = temp -> next ) {
                    if ( temp2 == temp ) {
                        continue;
                    }
                }
                fina->addElement(temp2->data);
            }

            return total;
        }

        Set<T>* operator*(Set<T> *s) {

            typename LinkedList<T>::Node *temp , *temp2;
            
            temp = this->head;
            temp2 = s->head;

            Set *total;
            for ( temp ; temp != NULL ; temp = temp -> next  ) {
                while ( temp != NULL ) {
                    if ( temp == temp2 ) {
                        total->addElement(temp->data);
                    }
                    temp2 = temp2 -> next;
                }
                
            }
            return total;
        }
        
};
