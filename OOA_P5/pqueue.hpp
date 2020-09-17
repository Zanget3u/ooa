#pragma once

#include <string>
#include <iostream>

using namespace std;

template <typename T>
class PriorityQueue
{
private:
	typedef struct pqentry
	{
		float _prio;
		string _key;
		T* _value;
		pqentry* next;
		pqentry* previous;
	} *pqentryPtr;											// Praefix um nicht immer "struct pqentry*" schreiben zu muessen.

	int size;
	pqentryPtr head;
	pqentryPtr tail;
	pqentryPtr current;
	pqentryPtr temp;

public:
	bool isEmpty();
	PriorityQueue();										// Konstruktor.
	~PriorityQueue();										// Destruktor.
	void insert(T* value, string key, float priority);		// Fuegt ein Objekt in die Warteschlange ein.
	T* extractMin(void);									// gibt einfach den Value von head zurueck und setzt head auf das zweite Element.
	void decreaseKey(T* value, string key, float priority);	// die Funktion sollte eigentlich "changePrio" heissen ...
	void remove(string key);								// Loescht ein Objekt aus der Warteschlange.
	void printQueue();										// Gibt den Inhalt der Warteschlange auf der Konsole aus.
	void printDebug();										// Debug Infos.
};

//---------------------------------------------------Konstruktor und Destruktor-------------------------------------------------------
template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	size = 0;
	head = NULL;
	tail = NULL;
	current = NULL;
	temp = NULL;

	cout << " ------ PriorityQueue wurde erstellt ---------------------------------------------------------------- " << endl << endl;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	current = head;

	while (current != NULL)
	{
		pqentryPtr delPtr = current;
		current = current->next;
		delete delPtr;
		size -= 1;
	}

	cout << endl << endl << " ------ PriorityQueue wurde zerstoert ---------------------------------------------------------------- ";
}
//---------------------------------------------------Private Funktionen---------------------------------------------------------------
template <typename T>
bool PriorityQueue<T>::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//---------------------------------------------------Public Funktionen----------------------------------------------------------------
template <typename T>
void PriorityQueue<T>::insert(T* value, string key, float priority)
{
	pqentryPtr pqe = new pqentry;										//Objekt wird auf dem Heap angelegt
	pqe->_value = value;
	pqe->_key = key;
	pqe->_prio = priority;
	pqe->next = NULL;
	pqe->previous = NULL;

	if (head != NULL)													//falls eine Liste vorhanden ist
	{
		current = head;
		if (priority >= current->_prio) {								//falls prio groesser ist als die vom aktuellen Eintrag
			while (current->next != NULL && priority >= current->_prio)	//solange noch Elemente in der Liste vorhanden sind
			{															//und die einzufuegende Prioritaet groesser ist
				current = current->next;								//aktueller-Zeiger geht weiter
			}
			if (priority > current->_prio) {
				current->next = pqe;									//new pqentry am Ende einfuegen
				pqe->previous = current;								//Vorgaenger Element = aktuellen-Zeiger setzen
				tail = pqe;												//tail ist nun = new Node
				size += 1;												//Element-Zaehler wird um 1 hochgesetzt
			}
			else if (priority <= current->_prio)
			{
				temp = current->previous;								//Vorgaenger merken
				current->previous = pqe;								//pqe vor current einsetzen
				pqe->next = current;									//pqe next-Zeiger auf current zeigen lassen
				pqe->previous = temp;									//pqe prev-Zeiger auf temp zeigen lassen
				temp->next = pqe;										//temp next-Zeiger auf pqe zeigen lassen (Liste schliessen)
				size += 1;												//Element-Zaehler wird um 1 hochgesetzt
			}
		}
		else if (priority < current->_prio)								//falls prio kleiner ist als die vom aktuellen Eintrag	
		{
			while (current->previous != NULL && priority < current->_prio)
			{
				current = current->previous;
			}
			if (priority < current->_prio) {
				current->previous = pqe;
				pqe->next = current;
				head = pqe;
				size += 1;
			}
			else if (priority >= current->_prio)
			{
				temp = current->next;
				current->next = pqe;
				pqe->previous = current;
				pqe->next = temp;
				temp->previous = pqe;
				size += 1;
			}
		}
	}
	else																//falls keine Liste vorhanden ist
	{																	//setze alle Zeiger (ausser temp) auf den neuen Eintrag
		head = pqe;
		tail = pqe;
		current = pqe;
		size += 1;
	}
}

template <typename T>
T* PriorityQueue<T>::extractMin(void)
{
	if (isEmpty()) { cout << " -> Warteschlange ist leer" << endl; return nullptr; }
	else
	{
		T* element = head->_value;
		string copy = head->_key;											//!!! ACHTUNG SICHTBARKEIT/LEBENSDAUER !!!
		remove(copy);
		return element;
	}
}

template <typename T>
void PriorityQueue<T>::decreaseKey(T* value, string key, float priority)
{
	string delvalue = key;
	remove(delvalue);
	insert(value, delvalue, priority);
	cout << " -> Das Element " << delvalue << " wurde abgeaendert wieder hinzugefuegt" << endl << endl;
}

template <typename T>
void PriorityQueue<T>::remove(string key)
{
	if (isEmpty()) { cout << " -> Warteschlange ist leer" << endl; }
	else {
		pqentryPtr delPtr = NULL;
		temp = head;
		current = head;

		while (current != NULL && current->_key != key)						//solange die Liste nicht leer ist und das Element 
		{																	//noch nicht gefunden wurde, gehe weiter	
			temp = current;													//temp-Zeiger bleibt stehen
			current = current->next;										//aktueller-Zeiger geht weiter	
		}

		if (current == NULL)												//Wenn am letzten Element angekommen
		{
			cout << endl << " -> Element ist nicht in der Liste" << endl << endl;	//ist das Element nicht in der Liste vorhanden
		}
		else if (current->_key == key && size > 1)							//Wenn das Element gefunden wurde
		{
			delPtr = current;												//Setze Loesch-Zeiger auf das aktuelle Element

			if (delPtr == head)												//Wenn das erste Element der Liste geloescht wird
			{
				head = head->next;											//Setze den head-Zeiger auf das zweite Element
				head->previous = NULL;
			}

			else if (delPtr == tail)										//Wenn das letzte Element der Liste geloescht wird
			{
				tail = tail->previous;
				tail->next = NULL;
			}

			else
			{
				current = current->next;									//Setze den aktuellen Zeiger eins weiter
				temp->next = current;										//Setze den alten Vorgaenger auf den neuen Nachfolger (Liste wieder schliessen)
				current->previous = temp;									//wenn n geloescht wird --> (n-1) zeigt auf (n+1) und umgekehrt
			}

			delete delPtr;													//Loesche das Element
			size -= 1;
			cout << endl << " -> Das Element " << key << " wurde entfernt" << endl;
		}
		else if (current->_key == key && size == 1)
		{
			delPtr = current;

			head->previous = NULL;
			head->next = NULL;
			head = NULL;

			tail->previous = NULL;
			tail->next = NULL;
			tail = NULL;

			delete delPtr;
			size -= 1;
			cout << endl << " -> Das Element " << key << " wurde entfernt" << endl;
		}
	}
}

template <typename T>
void PriorityQueue<T>::printQueue()
{
	if (isEmpty()) {}
	else {
		current = head;
		cout << endl << "       Objekt:          Prioritaet:" << endl << endl;
		while (current != NULL)
		{
			cout.width(14);													//Zum sauberen einruecken der Werte
			cout << current->_key << "              " << current->_prio << endl;
			current = current->next;
		}
	}
}

template <typename T>
void PriorityQueue<T>::printDebug()
{
	cout << endl
		<< endl << " ------ Debug-Info ---------------------------------------------------------------------------------- "
		<< endl << "Elemente in der Queue: " << size
		<< endl << "head->previous: " << head->previous
		<< endl << "head->next->previous->prio: " << head->next->previous->_prio
		<< endl << "Head: " << head->_prio << "  | " << "head->next->prio: " << head->next->_prio
		<< endl << "Tail: " << tail->_prio << " | " << "tail->previous->prio: " << tail->previous->_prio << endl;
}
//------------------------------------------------------------------------------------------------------------------------------------