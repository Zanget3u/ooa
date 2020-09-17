#include <iostream>
#include "digraph.hpp"
#include "liste.hpp"
#include "console_menu.hpp"

using namespace std;

void PrintDebug(DiGraph* uebergabe_graph)
{

	cout << endl << "-------------------------------DEBUG BEGINN----------------------------" << endl << endl;

	Liste<Node*>* my_nodes = (*uebergabe_graph).getNodes();

	//--- Liste mit allen Nodes auf der Konsole ausgeben 
	(*uebergabe_graph).PrintNodes();

	//--- Liste mit allen ausgehenden Kanten von allen Knoten auf der Konsole ausgeben
	(*uebergabe_graph).PrintAllEdges();

	cout << "-------------------------------DEBUG ENDE------------------------------" << endl;
}

void CreateDefaultGraph()
{
	//--- Graph und Knoten erstellen
	DiGraph graph;
	DiGraph* uebergabe = &graph;
	Node node1, node2, node3, node4, node5, node6, node7, node8;

	//--- Keys der Knoten setzen
	node1.setKey("Krefeld");
	node2.setKey("Koeln");
	node3.setKey("Wuppertal");
	node4.setKey("Hamburg");
	node5.setKey("Berlin");
	node6.setKey("Leipzig");
	node7.setKey("Stuttgart");
	node8.setKey("Muenchen");

	//--- Knoten dem Graphen hinzufuegen
	graph.addNode(&node1);
	graph.addNode(&node2);
	graph.addNode(&node3);
	graph.addNode(&node4);
	graph.addNode(&node5);
	graph.addNode(&node6);
	graph.addNode(&node7);
	graph.addNode(&node8);

	//--- Kanten zwischen den Knoten erstellen, Gewicht festlegen und dem Graphen hinzufuegen
	graph.addEdge("Krefeld", "Koeln", 50);
	graph.addEdge("Krefeld", "Wuppertal", 40);
	graph.addEdge("Krefeld", "Hamburg", 260);

	graph.addEdge("Koeln", "Stuttgart", 240);
	graph.addEdge("Koeln", "Wuppertal", 50);

	graph.addEdge("Stuttgart", "Muenchen", 140);
	graph.addEdge("Stuttgart", "Berlin", 420);

	graph.addEdge("Muenchen", "Berlin", 430);
	graph.addEdge("Muenchen", "Leipzig", 270);

	graph.addEdge("Wuppertal", "Hamburg", 230);

	graph.addEdge("Hamburg", "Leipzig", 240);
	graph.addEdge("Hamburg", "Berlin", 210);
	graph.addEdge("Hamburg", "Muenchen", 410);

	//--- Debug-Funktionen zum auslesen verschiedener Parameter	
	PrintDebug(uebergabe);

	//--- Graph in Datei schreiben
	graph.writeToFile("output_graph.txt");

	//--- Dijkstra Algorithmus	
	graph.dijkstraShortestPath("Koeln", "Leipzig");

	//--- Graph in DOT Notation auf der Konsole ausgeben (speziell fuer Dijkstra)
	graph.dijkstraDOTGraph("Koeln", "Leipzig");
}

int main()
{
	//--- Grosser Beispielgraphen fuer PrintToFile, Debug, Dijkstra und DOT-Notation auf der Konsole
	CreateDefaultGraph();

	//--- Beispielgraph aus Datei einlesen und in DOT umwandeln
	//DiGraph file_graph;
	//file_graph.createGraphFromFile("input_graph.txt");
	//PrintGraph(&file_graph);

	//--- Graphenverwaltungsmenue
	//GraphCreationMenu menu;
	//menu.startMenu();

	std::cin.get();
	return 0;
}