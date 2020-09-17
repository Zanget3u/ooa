#pragma once

#include <string>
#include "edge.hpp"
#include "liste.hpp"
#include "node.hpp"
#include <fstream>
#include "tokenizer.hpp"
#include <ctime>
#include "pqueue.hpp"
#include <map>

using namespace std;

class DiGraph
{
private:
	Liste<Node*>* _nodes;														// Zeiger auf eine Liste von Zeigern (auf Knoten) mit dem Bezeichner nodes, in dem alle Knoten des Graphen gespeichert sind.
	Liste<Node*>* _neighbours;													// Zeiger auf eine Liste von Zeigern (auf Knoten) mit dem Bezeichner neighbours, in dem alle direkt verbundenen Nachbarn des Knotens gespeichert sind.	
	Liste<Edge*>* _shortestPathResult;											// Zeiger auf eine Liste von Zeigern (auf Kanten) welche zusammen den kuerzesten Pfad zwischen zwei angegebenen Knoten beschreiben.
	Node input_node_array[10];													// Array von Nodes als Puffer fuer die Dateieinlesung.


public:
	DiGraph();																	// Konstruktor.
	~DiGraph();																	// Destruktor.
	void PrintNodes();															// Gibt Keys der Nodes in der _nodes-Liste auf der Konsole aus.	
	void PrintAllEdges();														// Gibt alle ausgehenden Kanten in uebersichtlicher Form aus.
	void addNode(Node* node);													// Fuegt die Adresse eines Klassenobjekts vom Typ Node dem Graphen hinzu.
	void eraseNode(Node* node);													// Loescht ein Node aus dem Graphen.
	void addEdge(string key1, string key2, float weight);						// Erstellt ein neues Klassenobjekt vom Typ Edge mit Startknoten key1, Endknoten key2 sowie einem Kantengewicht von weight. Anschliessend wird die Kante der Adjazenzliste des Knotens key1 hinzugefuegt.
	void eraseEdge(string key1, float weight);									// Loescht eine Kante aus der _edges Liste.
	void writeToFile(string dateiname);											// Speichert den aktuellen Graphen in bestimmter Syntax in einer Textdatei.
	void changeEdgeWeight(string key1, float old_weight, float new_weight);		// Aendert das Kantengewicht.
	void createGraphFromFile(string dateiname);									// Erstellt einen Graphen aus einer Textdatei mit bestimmter Syntax.
	void deleteAllData();														// Loescht alle Knoten und Kanten des Graphen.
	void createDOTGraph();														// Wandelt den Graphen in die DOT-Notation um und gibt diesen auf der Konsole aus.
	void dijkstraDOTGraph(string start, string end);							// Graph in DOT-Notation, speziell fuer den Dijkstra-Algorithmus.
	float getFirstEdgeWeight(string node_key);									// Liefert Gewicht der ersten ausgehenden Kante des eingegebenen node_key zurueck.
	Liste<Node*>* getNeighbours(string key);									// Gibt eine Liste aller benachbarter Knoten des Knotens mit dem Schluessel key zurueck.
	Liste<Edge*>* getEdges(string key);											// Gibt eine Liste aller abgehenden Kanten des Knotens mit dem Schluessel key zurueck.
	Liste<Node*>* getNodes();													// Gibt eine Liste aller Knoten des Graphen zuruck.
	Liste<Edge*>* dijkstraShortestPath(string start, string end);				// Gibt eine Liste aus Kanten zurueck welche den kuerzesten Pfad bilden.	
};

DiGraph::DiGraph()
{
	_nodes = new Liste<Node*>(10);
	_neighbours = new Liste<Node*>(10);
	_shortestPathResult = new Liste<Edge*>(10);
}

DiGraph::~DiGraph()
{
	delete _nodes;
	delete _neighbours;
}

void DiGraph::PrintNodes()
{
	cout << "Ausgabe der Liste von _nodes:" << endl;
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		cout << i << ". Listenelement: " << _nodes->getValueAt(i)->getKey() << endl;
	}
}

void DiGraph::PrintAllEdges()
{
	cout << endl << "Ausgabe der Liste von _edges: " << endl;
	Node* element;
	Liste <Edge*>* edges;

	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		element = _nodes->getValueAt(i);
		edges = _nodes->getValueAt(i)->getEdges();
		for (unsigned j = 0; j < edges->size(); j++)
		{
			cout << "Gewicht der " << j << ". ausgehenden Kante von " << element->getKey() << ": " << edges->getValueAt(j)->getWeight() << endl;
		}

	}
	cout << endl;
}

float DiGraph::getFirstEdgeWeight(string node_key)
{
	Node* element;
	Liste <Edge*>* edges;
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == node_key)
		{
			element = _nodes->getValueAt(i);
			edges = element->getEdges();

			return edges->getValueAt(0)->getWeight();
		}
	}
}

void DiGraph::addNode(Node* node)
{
	_nodes->append(node);
}

void DiGraph::addEdge(string key1, string key2, float weight)
{
	bool key1gefunden = false;
	bool key2gefunden = false;

	Edge* tmp_e = new Edge();
	tmp_e->setWeight(weight);

	Node* start = nullptr;
	Node* end = nullptr;

	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == key1)
		{
			start = _nodes->getValueAt(i);
			tmp_e->setStartNode(start);
			start->setNewEdge(tmp_e);
			key1gefunden = true;
		}

		if (_nodes->getValueAt(i)->getKey() == key2)
		{
			end = _nodes->getValueAt(i);
			tmp_e->setEndNode(end);
			key2gefunden = true;
		}
	}

	if (key1gefunden == true)
	{
		cout << key1 << " wurde gefunden!" << endl;
	}
	else if (key1gefunden == false)
	{
		cout << key1 << " wurde nicht gefunden!" << endl;
	}

	if (key2gefunden == true)
	{
		cout << key2 << " wurde gefunden!" << endl;
	}
	else if (key2gefunden == false)
	{
		cout << key2 << "wurde nicht gefunden!" << endl;
	}

	if ((key1gefunden == true) && (key2gefunden == true))
	{
		cout << "Die Kante wurde erfolgreich hinzugefuegt!" << endl;
	}
}

Liste<Node*>* DiGraph::getNodes()
{
	return _nodes;
}

Liste<Edge*>* DiGraph::getEdges(string key)
{
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == key)
		{
			return _nodes->getValueAt(i)->getEdges();
		}
	}
}

Liste<Node*>* DiGraph::getNeighbours(string node_key)
{
	Node* start = nullptr;
	Node* end = nullptr;
	Liste <Edge*>* edges;

	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == node_key)
		{
			start = _nodes->getValueAt(i);
			edges = start->getEdges();

			for (unsigned int j = 0; j < edges->size(); j++)
			{
				//cout << j << ". Kante geht von " << node_key << " bis " << edges->getValueAt(j)->getEndNode()->getKey() << ", hat das Gewicht " << edges->getValueAt(j)->getWeight() << " und die Adresse " << edges->getValueAt(j)->getEndNode() << endl << endl;
				end = edges->getValueAt(j)->getEndNode();
				_neighbours->append(end);
			}
		}
	}

	cout << "Ausgabe der Liste von _neighbours von dem Knoten: " << node_key << endl;
	for (unsigned int i = 0; i < _neighbours->size(); i++)
	{
		cout << _neighbours->getValueAt(i) << " | "
			<< _neighbours->getValueAt(i)->getKey() << endl;
	}
	return _neighbours;
}

void DiGraph::writeToFile(string dateiname)
{
	ofstream myfile(dateiname);
	if (myfile.is_open())
	{
		myfile << "# Alle Knoten" << endl;

		for (unsigned int i = 0; i < _nodes->size(); i++)
		{
			myfile << "+ " << _nodes->getValueAt(i)->getKey() << endl;
		}

		myfile << "# Alle Kanten" << endl;

		Node* element;
		Liste <Edge*>* edges;

		for (unsigned int i = 0; i < _nodes->size(); i++)
		{
			{
				element = _nodes->getValueAt(i);
				edges = element->getEdges();

				for (unsigned int j = 0; j < edges->size(); j++)
				{
					myfile << "- " << element->getKey() << " " << edges->getValueAt(j)->getEndNode()->getKey() << " " << edges->getValueAt(j)->getWeight() << endl;
				}
			}
		}

		myfile << "ende";
		myfile.close();
		cout << "Der Graph wurde erfolgreich in eine Datei geschrieben!" << endl;
	}
	else cout << "Unable to open file";
}

void DiGraph::eraseNode(Node* node)
{
	_nodes->erase(node);
}

void DiGraph::eraseEdge(string key1, float weight)
{
	Node* start = nullptr;
	bool start_gefunden = false;
	bool weight_gefunden = false;

	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == key1)
		{
			Liste<Edge*>* tmp_edge_list = _nodes->getValueAt(i)->getEdges();
			start = _nodes->getValueAt(i);
			start_gefunden = true;

			for (unsigned int j = 0; j < tmp_edge_list->size(); j++)
			{
				if (tmp_edge_list->getValueAt(j)->getWeight() == weight)
				{
					start->deleteEdge(tmp_edge_list->getValueAt(j));
					weight_gefunden = true;
				}
			}
		}
	}

	if (start_gefunden == false)
	{
		cout << "Startknoten wurde nicht gefunden!" << endl;
	}
	if (weight_gefunden == false)
	{
		cout << "Das angegebene Kantengewicht konnte keiner Kante zugeordnet werden!" << endl;
	}
	if ((start_gefunden == true) && (weight_gefunden == true))
	{
		cout << "Die Kante wurde erfolgreich geloescht!" << endl;
	}

}

void DiGraph::changeEdgeWeight(string key1, float old_weight, float new_weight)
{
	Node* start = nullptr;
	bool start_gefunden = false;
	bool weight_gefunden = false;

	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == key1)
		{
			Liste<Edge*>* tmp_edge_list = _nodes->getValueAt(i)->getEdges();
			start = _nodes->getValueAt(i);
			start_gefunden = true;

			for (unsigned int j = 0; j < tmp_edge_list->size(); j++)
			{
				if (tmp_edge_list->getValueAt(j)->getWeight() == old_weight)
				{
					tmp_edge_list->getValueAt(j)->setWeight(new_weight);
					weight_gefunden = true;
				}
			}
		}
	}

	if (start_gefunden == false)
	{
		cout << "Startknoten wurde nicht gefunden!" << endl;
	}
	if (weight_gefunden == false)
	{
		cout << "Das alte angegebene Kantengewicht konnte keiner Kante zugeordnet werden!" << endl;
	}
	if ((start_gefunden == true) && (weight_gefunden == true))
	{
		cout << "Das Gewicht der Kante wurde erfolgreich geaendert!" << endl;
	}
}

void DiGraph::createGraphFromFile(string dateiname)
{
	//--- Vorbereitung zur Erstellung eines Graphen aus einer Textdatei
	string line;
	ifstream myfile(dateiname);

	//--- Datei wird eingelesen
	if (myfile.is_open())
	{
		int counter = 0;

		//--- solange noch Zeilen vorhanden sind
		while (getline(myfile, line))
		{
			Tokenizer Token(line, " ");	 //Tokenizer-Objekt wird erstellt

			//--- Abfrage auf Knotensyntax
			if (Token.countTokens() == 2)
			{
				string first_Token = Token.nextToken();
				string second_Token = Token.nextToken();

				if (first_Token == "+")
				{
					this->input_node_array[counter].setKey(second_Token);
					this->addNode(&input_node_array[counter]);
					counter++;
				}
			}

			//--- Abfrage auf Kantensyntax
			if (Token.countTokens() == 4)
			{
				string first_Token = Token.nextToken();
				string second_Token = Token.nextToken();
				string third_Token = Token.nextToken();
				string fourth_Token = Token.nextToken();
				this->addEdge(second_Token, third_Token, atof(fourth_Token.c_str()));	//atof := string -> float conversion
			}
		}
		myfile.close();

		cout << endl << "Folgender Graph wurde erfasst:" << endl << endl;
		this->PrintNodes();
		this->PrintAllEdges();
	}
	else cout << "Unable to open file";

	cout << endl;
}

void DiGraph::deleteAllData()
{
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		_nodes->getValueAt(i)->deleteAllEdges();
	}

	cout << endl;

	while (_nodes->size() > 0)
	{
		for (unsigned j = 0; j < _nodes->size(); j++)
		{
			string node_key = _nodes->getValueAt(j)->getKey();
			cout << node_key << " wurde geloescht" << endl;
			_nodes->erase(_nodes->getValueAt(j));
		}
	}
}

void DiGraph::createDOTGraph()
{
	cout << endl << endl << "digraph {" << endl << endl;
	cout << " rankdir=LR;" << endl << endl;
	cout << " edge [fontname=" << '"' << "helvetica" << '"' << ", fontsize=5];" << endl;
	cout << " node [fontname=" << '"' << "helvetica" << '"' << ", fontsize=8];" << endl << endl;

	Liste<Edge*>* my_edges;
	float weight = 0;
	string endnode_key;
	string farben[10];
	farben[0] = "orange";
	farben[1] = "purple";
	farben[2] = "green";
	farben[3] = "cyan";
	farben[4] = "firebrick1";
	farben[5] = "forestgreen";
	farben[6] = "aquamarine";
	farben[7] = "cornflowerblue";
	farben[8] = "burlywood1";
	farben[9] = "crimson";

	srand(time(NULL)); // Seed-Reset

	// ---Zwei for-Schleifen da sonst die Farben der Kreise nicht mehr aenderbar sind
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		cout << " node [shape = doublecircle, color=" << farben[rand() % 9] << "] " << '"' << _nodes->getValueAt(i)->getKey() << '"' << ';' << endl;
	}

	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		//cout << " node [shape = doublecircle, color=black ] " << '"' << my_nodes->getValueAt(i)->getKey() << '"' << ';' << endl;
		my_edges = _nodes->getValueAt(i)->getEdges();

		for (unsigned j = 0; j < my_edges->size(); j++)
		{
			weight = my_edges->getValueAt(j)->getWeight();
			endnode_key = my_edges->getValueAt(j)->getEndNode()->getKey();
			cout << " " << '"' << _nodes->getValueAt(i)->getKey() << '"' << " -> " << '"' << endnode_key << '"' << " [label=" << weight << ", style=bold, color=" << farben[rand() % 9] << "];" << endl;
		}
	}

	cout << endl << "}";
	cout << endl << endl;
}

Liste<Edge*>* DiGraph::dijkstraShortestPath(string start, string end)
{
	cout << endl;

	//--- map<const key, value type T> 
	//--- die gemappten values werden (mit dem Key assoziiert) abgespeichert
	//--- wie ein Array aus structs{Node*, float} aber mit bereits ueberladenem [] Operator
	map<Node*, float> dist;
	map<Node*, Edge*> previous;

	//--- Initialisierung der benoetigten lokalen Variablen
	Node* startNode = nullptr;
	Node* endNode = nullptr;
	PriorityQueue<Node> pqueue;

	//--- Finden der Start- und Endknoten (ohne Fehlerbehandlung)
	for (unsigned int a = 0; a < _nodes->size(); a++)
	{
		if (_nodes->getValueAt(a)->getKey() == start)
			startNode = _nodes->getValueAt(a);
		if (_nodes->getValueAt(a)->getKey() == end)
			endNode = _nodes->getValueAt(a);
	}

	//--- Hinzufuegen aller Knoten zur PQ (Startknoten mit hoechster Prioritaet)
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == start)
		{
			dist[_nodes->getValueAt(i)] = 0;
		}
		else
		{
			dist[_nodes->getValueAt(i)] = 999999;
		}

		previous[_nodes->getValueAt(i)] = nullptr;
		pqueue.insert(_nodes->getValueAt(i), _nodes->getValueAt(i)->getKey(), dist[_nodes->getValueAt(i)]);
	}

	//--- Ausgabe der Priorityqueue
	pqueue.printQueue();

	//--- solange noch Elemente in der PQ vorhanden sind
	while (!pqueue.isEmpty())
	{
		//--- entfernt den Knoten mit der hoechsten Prioritaet und bearbeitet diesen
		Node* u = pqueue.extractMin();

		//--- geht alle ausgehenden Kanten des Knotens durch
		for (unsigned int h = 0; h < u->getEdges()->size(); h++)
		{
			//--- verrechnet Gewicht der Kante mit Knotenprioritaet
			Node* v = u->getEdges()->getValueAt(h)->getEndNode();
			float alt = dist[u] + u->getEdges()->getValueAt(h)->getWeight();

			//--- wenn prio + weight (alt) niedriger sind als die prio vom Endknoten der jeweiligen Kante, bekommt Knoten neue prioritaet
			if (alt < dist[v])
			{
				dist[v] = alt;
				previous[v] = u->getEdges()->getValueAt(h);
				pqueue.decreaseKey(v, v->getKey(), alt);
			}
		}
	}

	Node* u = endNode;

	//--- hinzufuegen der herausgefundenen Kanten zur results-Liste
	while (u != nullptr && previous[u] != nullptr)
	{
		_shortestPathResult->append(previous[u]);
		u = previous[u]->getStartNode();
	}

	//--- Ausgabe des kuerzesten Pfades
	cout << endl << endl;
	cout << " Shortest Path: ";
	cout << startNode->getKey();
	for (int p = (_shortestPathResult->size() - 1); p > -1; p--)
	{
		cout << " -> " << _shortestPathResult->getValueAt(p)->getEndNode()->getKey();
	}

	return _shortestPathResult;
}

void DiGraph::dijkstraDOTGraph(string start, string end)
{
	cout << endl << endl << "digraph {" << endl;
	cout << " rankdir=LR;" << endl << endl;
	cout << " edge [fontname=" << '"' << "helvetica" << '"' << ", fontsize=5];" << endl;
	cout << " node [fontname=" << '"' << "helvetica" << '"' << ", fontsize=8];" << endl << endl;

	Liste<Edge*>* my_edges;
	float weight = 0;
	string endnode_key;
	string startnode_key;
	string farben[10];

	farben[0] = "gray13";
	farben[1] = "gray22";
	farben[2] = "gray31";
	farben[3] = "gray40";
	farben[4] = "gray54";
	farben[5] = "gray63";
	farben[6] = "gray72";
	farben[7] = "gray81";
	farben[8] = "gray90";
	farben[9] = "gray95";

	string ersatz_farben[3] = { "red", "green", "blue" };
	bool shortpath = false; // damit nur Dijkstra-Kanten farbig gezeichnet werden

	srand(time(NULL)); // Seed-Reset

	// ---Zeichnen der Knoten
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		if (_nodes->getValueAt(i)->getKey() == start)
		{
			cout << " node [shape = house, color=" << ersatz_farben[1] << "] " << '"' << _nodes->getValueAt(i)->getKey() << '"' << ';' << endl;
		}
		else if (_nodes->getValueAt(i)->getKey() == end)
		{
			cout << " node [shape = cds, color=" << ersatz_farben[0] << "] " << '"' << _nodes->getValueAt(i)->getKey() << '"' << ';' << endl;
		}
		else
		{
			cout << " node [shape = circle, color=" << farben[rand() % 9] << "] " << '"' << _nodes->getValueAt(i)->getKey() << '"' << ';' << endl;
		}
	}

	//--- Zeichnen der Kanten
	for (unsigned int i = 0; i < _nodes->size(); i++)
	{
		shortpath = false;
		my_edges = _nodes->getValueAt(i)->getEdges();

		for (unsigned j = 0; j < my_edges->size(); j++)
		{
			weight = my_edges->getValueAt(j)->getWeight();
			startnode_key = my_edges->getValueAt(j)->getStartNode()->getKey();
			endnode_key = my_edges->getValueAt(j)->getEndNode()->getKey();

			for (unsigned h = 0; h < _shortestPathResult->size(); h++)
			{
				shortpath = false;

				if ((weight == _shortestPathResult->getValueAt(h)->getWeight()) &&
					(startnode_key == _shortestPathResult->getValueAt(h)->getStartNode()->getKey()) &&
					(endnode_key == _shortestPathResult->getValueAt(h)->getEndNode()->getKey()))
				{
					shortpath = true;
					break;
				}
			}

			if (shortpath == true)
			{
				cout << " " << '"' << _nodes->getValueAt(i)->getKey() << '"' << " -> " << '"' << endnode_key << '"' << " [label=" << weight << ", style=bold, color=" << ersatz_farben[2] << ", arrowhead=normal];" << endl;
			}
			else
			{
				shortpath = false;
				cout << " " << '"' << _nodes->getValueAt(i)->getKey() << '"' << " -> " << '"' << endnode_key << '"' << " [label=" << weight << ", style=bold, color=" << farben[rand() % 9] << ", arrowhead=none];" << endl;
			}
		}
	}

	cout << "}";
	cout << endl << endl;
}