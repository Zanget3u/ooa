#pragma once

#include "node.hpp"
#include "digraph.hpp"
#include <string>
#include <iostream>

class DiGraph;
class Node;

using namespace std;

class GraphCreationMenu
{
private:
	// --- Optionen fuer die User-Eingabe
	int knoten_counter = 0;
	int menu_option = 0;
	int node_option = 0;
	int edge_option = 0;
	int graph_option = 0;

	Node node_array[8];		  // Array von Nodes als Puffer fuer die Dateieinlesung.
	DiGraph graph;

	void mainMenu();          // Hauptmenue zum Erreichen der Untermenues.
	void nodeMenu();          // Menue zur Verwaltung der Nodes.
	void edgeMenu();          // Menue zur Verwaltung der Edges.
	void graphMenu();         // Menue zur Verwaltung des Graphen.
	void exitMenu();          // Beendet das console_menu.

public:
	void startMenu();		  // Schnittstelle (ruft mainMenu auf)
};

void GraphCreationMenu::startMenu()
{
	mainMenu();
}

void GraphCreationMenu::mainMenu()
{
	cout << "------------------ Graph Creation Menu ------------------" << endl << endl
		<< "Options: (1) Knotenverwaltung | (2) Kantenverwaltung | (3) Graphenverwaltung | (4) Beenden" << endl;

	cin >> menu_option;

	if (menu_option == 1)
	{
		nodeMenu();
	}
	else if (menu_option == 2)
	{
		edgeMenu();
	}
	else if (menu_option == 3)
	{
		graphMenu();
	}
	else if (menu_option == 4)
	{
		exitMenu();
	}
	else
	{
		cout << "Menu: Keine valide Eingabe. Programm wird beendet!";
		std::cin.get();
		exitMenu();
	}
}

void GraphCreationMenu::nodeMenu()
{
	cout << "------------------ Knotenverwaltung ------------------" << endl << endl
		<< "Options: (1) Knoten erstellen | (2) Knoten loeschen | (3) Zurueck | (4) Beenden" << endl;

	cin >> node_option;

	if (node_option == 1)
	{
		string knoten_name = "Unknown";
		cout << "Geben Sie den Namen des Knotens ein: ";
		cin >> knoten_name;
		node_array[knoten_counter].setKey(knoten_name);
		graph.addNode(&node_array[knoten_counter]);
		knoten_counter += 1;
		cout << "Knoten wurde erstellt!" << endl << endl;
		nodeMenu();
	}
	else if (node_option == 2)
	{
		string knoten_name = "Unknown";
		cout << "Geben Sie den Namen des Knotens ein: ";
		cin >> knoten_name;
		for (int i = 0; i < knoten_counter; i++)
		{
			if (node_array[i].getKey() == knoten_name)
			{
				graph.eraseNode(&node_array[i]);
				cout << "Knoten wurde geloescht" << endl;
			}
			else
			{
				cout << "Knoten existiert nicht!" << endl;
			}
		}
		nodeMenu();
	}
	else if (node_option == 3)
	{
		mainMenu();
	}
	else if (node_option == 4)
	{
		exitMenu();
	}
	else
	{
		cout << "Menu: Keine valide Eingabe. Programm wird beendet!";
		std::cin.get();
		exitMenu();
	}
}

void GraphCreationMenu::edgeMenu()
{
	cout << "------------------ Kantenverwaltung ------------------" << endl << endl
		<< "Options: (1) Kante hinzufuegen | (2) Kante loeschen | (3) Gewicht einer Kante aendern | (4) Zurueck | (5) Beenden" << endl;

	cin >> edge_option;

	if (edge_option == 1)
	{
		string knoten_name_1 = "Unknown";
		string knoten_name_2 = "Unknown";
		float kanten_gewicht = 0;

		cout << "Bitte geben Sie den Namen des Startknotens ein: ";
		cin >> knoten_name_1;
		cout << endl << "Bitte geben Sie den Namen des Endknotens ein: ";
		cin >> knoten_name_2;
		cout << endl << "Bitte geben Sie das gewuenschte Kantengewicht ein: ";
		cin >> kanten_gewicht;

		graph.addEdge(knoten_name_1, knoten_name_2, kanten_gewicht);
		edgeMenu();
	}
	else if (edge_option == 2)
	{
		string knoten_name_1 = "Unknown";
		float kanten_gewicht = 0;

		cout << "Bitte geben Sie den Namen des Startknotens ein: ";
		cin >> knoten_name_1;
		cout << endl << "Bitte geben Sie das Kantengewicht ein: ";
		cin >> kanten_gewicht;

		graph.eraseEdge(knoten_name_1, kanten_gewicht);
		edgeMenu();
	}
	else if (edge_option == 3)
	{
		string knoten_name_1 = "Unknown";
		float altes_kanten_gewicht = 0;
		float neues_kanten_gewicht = 0;

		cout << "Bitte geben Sie den Namen des Startknotens ein: ";
		cin >> knoten_name_1;
		cout << endl << "Bitte geben Sie das alte bisherige Kantengewicht ein: ";
		cin >> altes_kanten_gewicht;
		cout << endl << "Bitte geben Sie das neue gewuenschte Kantengewicht ein: ";
		cin >> neues_kanten_gewicht;

		graph.changeEdgeWeight(knoten_name_1, altes_kanten_gewicht, neues_kanten_gewicht);
		edgeMenu();
	}
	else if (edge_option == 4)
	{
		mainMenu();
	}
	else if (edge_option == 5)
	{
		exitMenu();
	}
	else
	{
		cout << "Menu: Keine valide Eingabe. Programm wird beendet!";
		std::cin.get();
		exitMenu();
	}
}

void GraphCreationMenu::graphMenu()
{
	cout << "------------------ Graphenverwaltung ------------------" << endl << endl
		<< "Options: (1) Graph speichern | (2) Graph laden | (3) Graph ausgeben | (4) Knoten und Kanten loeschen | (5) Zurueck | (6) Beenden" << endl;

	cin >> graph_option;

	if (graph_option == 1)
	{
		graph.writeToFile("console_graph_output.txt");
		graphMenu();
	}
	else if (graph_option == 2)
	{
		graph.createGraphFromFile("console_graph_input.txt");
		graphMenu();
	}
	else if (graph_option == 3)
	{
		graph.PrintNodes();
		graph.PrintAllEdges();
		graphMenu();
	}
	else if (graph_option == 4)
	{
		graph.deleteAllData();
		graphMenu();
	}
	else if (graph_option == 5)
	{
		mainMenu();
	}
	else if (graph_option == 6)
	{
		exitMenu();
	}
	else
	{
		cout << "Menu: Keine valide Eingabe. Programm wird beendet!";
		std::cin.get();
		exitMenu();
	}
}

void GraphCreationMenu::exitMenu()
{
	cout << "Programm wird beendet!" << endl;
}