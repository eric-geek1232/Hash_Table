/*By Eric 12/01/2021*/
#include <iostream>

using namespace std;

struct Node
{
	string key;
	string data;
	Node *next;	
};

class HashTable
{
	private:
		Node **lists;
		int max_elements;
		int items;
		
		Node *searchItem(Node *list, string key);
		void printList(Node *list, int count);
		void insertList(Node *&list, string key, string content);
		void removeItem(Node *&list, string key);
		Node *createNode(string key, string content);
		
	public:
		HashTable();
		int hashFunction(string key);
		void put(string key, string content);
		void del(string key);
		void get(string key);
		void show();
		void size();
};

HashTable::HashTable()
{
	items = 0;
	max_elements = 10;
	lists = new Node*[max_elements];
	
	for (int i = 0; i < max_elements; i++) {
		lists[i] = NULL;	
	}
}

Node *HashTable::createNode(string key, string content)
{
	Node *newNode = new Node();
	
	newNode->key = key;
	newNode->data = content;
	newNode->next = NULL;
	
	return newNode;
}

int HashTable::hashFunction(string key) 
{
	int ascii = 0;
	
	for (int i = 0; i < key.size(); i++) {
		ascii += int(key[i]);				// sum the ascii values of keyword	
	}
	
	return ascii % max_elements;			// return mod
}

void HashTable::put(string key, string content)
{
	int hash = hashFunction(key);
	
	insertList(lists[hash], key, content);
}

void HashTable::insertList(Node *&list, string key, string content)
{
	if (list == NULL) {			// insert always at the end of the list
		Node *newNode = createNode(key, content);
		list = newNode;
		
		cout<< "\n\n [Info]-Item Add "<< "["<< newNode->key<< " | "<< newNode->data<< "]"<< endl;
		items++;
		return;		
	}
	
	if (list->key == key) {		// if similar data is found while this function keeps searching
		char option;
		
		cout<< "\n\n [Warning]-key: "<< list->key<< " exists\n"<< endl; 
		cout<< " [Info]-Old content: "<< list->data<< " New content: "<< content<< "\n"<<endl;
		cout<< " Would you like to replace the content? \n [S/N] ";
		cin>> option;
		
		if (option == 'S' || option == 's') {
			list->data = content;
			cout<< "\n\n [Info]-Content replaced"<< endl;
		}
		
		return;
	}
	
	insertList(list->next, key, content);			// keep searching
}

void HashTable::del(string key) 
{
	int hash = hashFunction(key);					// get hash
	
	removeItem(lists[hash], key);
}

void HashTable::removeItem(Node *&list, string key)
{
	if (list == NULL) {									// end of the list
		cout<< "\n\n [Warning]-Key doesn't exist: "<< key<< "\n"<< endl;
		return;
	}
	
    Node *list_aux;
    list_aux = list;									// get current list
    
    if (list_aux->key == key) {
        list = list->next;								// save list from next node
        
		cout<< "\n\n [Info]-[ "<< list_aux->key <<" | " <<list_aux->data << " ]"<< " removed\n"<< endl;
		items--;
		
	    delete(list_aux);								// delete old list
	    return;
    }
    
    removeItem(list->next, key);
}

void HashTable::get(string key)
{
	int hash = hashFunction(key);
	Node *item_aux = searchItem(lists[hash], key);
	
	if (item_aux != NULL) {
		cout<< "\n\n [Info]-Key: "<< key<< " Key found --> data: "<< item_aux->data<< endl;
	} else {
		cout<< "\n\n [Warning]-Key: "<< key<< " Key doesn't exist"<< endl;
	}
	
}

Node *HashTable::searchItem(Node *list, string key)
{
    if (list == NULL) {
    	return NULL;							// end of the list
	}
	
	if (key != list->key) {
		return searchItem(list->next, key);		// keep searching
	} else {
		return list;							// node found
	}
}

void HashTable::printList(Node *list, int count)
{
	if (list == NULL) {							// end of the list
		if (count != 0) {
			cout<< "NULL"<< endl;
		}
		return;
	}
    
	cout<< "[ "<< list->key <<" | " <<list->data << " ]"<< "  ->  ";
	
    printList(list->next, count+1);				// keep iterating
}

void HashTable::show() 
{
	cout<< "\n\n\tShowing...\n"<< endl;
	
	for (int i = 0; i < max_elements; i++) {	// iterate each of the lists
		if (lists[i] != NULL) {
			cout<< " ["<< i+1<< "]\t";
			printList(lists[i], 0);	
		} else {
			cout<< " ["<< i+1<< "]"<< "\t----Empty---->"<< endl;
		}
	}
	
	cout<< "\n\n [Info]-Total Items: "<< items<< "\n"<< endl;
}

int main()
{
	
	HashTable *hashTable = new HashTable();
	
	int option;
    string key;
    string content;
 
    do {
    	cout<< "\t Hash Table OOP\n\n"<< endl;
    	cout<< "\t..::Menu::..\n"<< endl;
    	cout<< " [1] Insert"<< endl;
    	cout<< " [2] Show"<< endl;
    	cout<< " [3] Search"<< endl;
    	cout<< " [4] Remove item"<< endl;
    	cout<< " [5] Exit"<< endl;
 
    	cout<< "\n Select: ";
        cin>> option;
        
        switch(option){
            case 1:
                cout<< "\n Type one key: "; 
				cin>> key;
				cout<< "\n\n what's  on your mind: ";
				cin>> content;
				
                hashTable->put(key, content);
                cout<< "\n"<< endl;
            break;
 
            case 2:
                hashTable->show();
            break;
            
            case 3:
				cout<< "\n Type the key to search: "; 
				cin>> key;
				
                hashTable->get(key);
                cout<< "\n"<< endl;
            break;
            
            case 4:
            	hashTable->show();
            	
            	cout<< "\n Type the key to delete: "; 
				cin>> key;
            	
            	hashTable->del(key);
            break;
            
            case 5:
                cout<< "\n\n\t**Big thanks for using this software**\n"<< endl;
            break;
            
            default:
            	cout<< "\n\n [warning] wrong option... try again!\n"<< endl;
        }
        
        system("pause");  
		system("cls");
    } while(option != 5);
    
	return 0;
}
