#pragma once

#include <string>
#include "liste.hpp"

class Edge;						 // Vorwaertsdeklaration.

using namespace std;

class Node
{
private:
	string _node_key;			 // Attribut zur eindeutigen Identifikation des Knotens.
	Liste<Edge*>* _edges;		 // Attribut fuer die Adjazenzliste im Knoten, in der die Adressen aller ausgehenden	Kanten gespeichert sind.
								 // -> edges ist ein Pointer auf die Adjadenzliste eines jedes Knotens.
public:
	Node();						 // Konstruktor.
	~Node();					 // Destruktor.
	void setKey(string key);     // Setzt den Namen eines Knoten.		
	void setNewEdge(Edge* edge); // Fuegt dem Knoten eine neue abgehende Kante hinzu.
	void deleteEdge(Edge* edge); // Loescht eine Kante aus der _edges Liste.
	void deleteAllEdges();		 // Loescht alle Kanten eines Knoten.
	string getKey();			 // Liefert den Namen eines Knoten.	
	Liste <Edge*>* getEdges();   // Gibt die Liste aller dem Knoten zugeordneten Kanten zurueck.
								 // -> Gibt einen Pointer auf eine Liste (bestehend aus Edge-Pointern) zurueck.
};

Node::Node()
{
	_node_key = "Unknown";
	_edges = new Liste<Edge*>(2);
}

Node::~Node()
{
	delete _edges;
}

void Node::setKey(string key)
{
	this->_node_key = key;
}

string Node::getKey()
{
	return this->_node_key;
}

void Node::setNewEdge(Edge* edge)
{
	this->_edges->append(edge);
}

Liste<Edge*>* Node::getEdges()
{
	return this->_edges;
}

void Node::deleteEdge(Edge* edge)
{
	this->_edges->erase(edge);
}

void Node::deleteAllEdges()
{
	while (_edges->size() > 0)
	{
		for (unsigned int i = 0; i < _edges->size(); i++)
		{
			cout << _edges->getValueAt(i) << " wurde geloescht" << endl;
			this->_edges->erase(_edges->getValueAt(i));
		}
	}
}