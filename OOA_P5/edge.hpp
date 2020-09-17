#pragma once

#include "node.hpp"

class Node;						  //Vorwaertsdeklaration.

using namespace std;

class Edge
{
private:
	Node* _startnode, * _endnode;  // Zum Speichern der Adressen der verbundenen Knoten.
	float _weight;				  // Zum Speichern des Kantengewichts.

public:
	Edge();						  // Konstruktor.	
	void setWeight(float weight); // Setzt das Gewicht der Kante.
	void setStartNode(Node* n);   // Legt den Startknoten fest.
	void setEndNode(Node* n);     // Legt den Endknoten fest.
	float getWeight();            // Liefert das Gewicht der Kante.
	Node* getStartNode();         // Liefert Zeiger auf Startknoten.
	Node* getEndNode();			  // Liefert Zeiger auf Endknoten.	
};

Edge::Edge()
{
	_startnode = nullptr;
	_endnode = nullptr;
	_weight = 0;
}

void Edge::setWeight(float weight)
{
	this->_weight = weight;
}

void Edge::setStartNode(Node* n)
{
	this->_startnode = n;
}

void Edge::setEndNode(Node* n)
{
	this->_endnode = n;
}

float Edge::getWeight()
{
	return this->_weight;
}

Node* Edge::getStartNode()
{
	return this->_startnode;
}

Node* Edge::getEndNode()
{
	return this->_endnode;
}