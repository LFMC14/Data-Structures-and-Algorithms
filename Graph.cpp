#include <iostream>
#include <list>
#include <stack>
using namespace std;

struct Vertex {
	int node = ' '; // value/key of vertex
	mutable list<Vertex> edges; // adjacent vertices
	int parent = -1; // stores vertex which expands this vertex in CycleDFS
};

class Graph {
public:
	Graph() {};
	~Graph() {
		nodes.clear();
		visited.clear();
		
		while (!vstack.empty()) {
			vstack.pop();
		}
	};

	void addEdge(int a, int b) {
		Vertex* first;
		Vertex* second;

		if (!inGraph(a) && !inGraph(b)) { // neither vertex in graph
			first = new Vertex;
			second = new Vertex;

			first->node = a;
			second->node = b;

			first->edges.push_back(*second); // add other vertex to this vertex's adjacent list
			second->edges.push_back(*first);

			nodes.push_back(*first); // add vertices to graph
			nodes.push_back(*second);
		}
		else if (inGraph(a) && !inGraph(b)) { // if graph contains a but not b
			second = new Vertex;

			first = &getVertex(a); // access vertex a
			second->node = b;

			first->edges.push_back(*second);
			second->edges.push_back(*first);

			nodes.push_back(*second);
		}
		else if (!inGraph(a) && inGraph(b)) { // if graph contains b but not a
			first = new Vertex;

			second = &getVertex(b);
			first->node = a;

			second->edges.push_back(*first);
			first->edges.push_back(*second);

			nodes.push_back(*first);
		}
		else if (inGraph(a) && inGraph(b) && !existingEdge(a, b)) { // if both a, b in graph but no connecting edge
			first = &getVertex(a);
			second = &getVertex(b);
			
			first->edges.push_back(*second);
			second->edges.push_back(*first);
		}
	};

	Vertex& getVertex(int a) { // access vertex a
		// No default returned since this function only called when inGraph(a) returns true
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			if (it->node == a) // if vertex value equals value a
				return *it;
		}
	}

	bool inGraph(int a) { // check if vertex a is in graph
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			if (it->node == a)
				return true;
		}
		return false;
	}

	bool existingEdge(int a, int b) { // checks for existing edge between a and b
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			if (it->node == a || it->node == b) {
				for (auto k = it->edges.begin(); k != it->edges.end(); k++) {
					if (k->node == a || k->node == b)
						return true;
				}
			}
		}
		return false;
	}

	bool inVisited(Vertex a) {
		for (auto it = visited.begin(); it != visited.end(); it++) {
			if (it->node == a.node)
				return true;
		}
		return false;
	}

	bool CycleDFS() {
		list<Vertex>::iterator it;
		Vertex currNode;
		Vertex tempNode;

		if (nodes.empty())
			return false;

		it = nodes.begin();
		currNode = *it;

		vstack.push(currNode);

		while (!vstack.empty()) {
			currNode = vstack.top();
			vstack.pop(); // remove node from stack

			if (!inVisited(currNode)) { // if vertex not visited
				visited.push_back(currNode); // add to visited 

				for (auto it = currNode.edges.begin(); it != currNode.edges.end(); it++) { //iterate through adjacent vertices
					if (it->node != currNode.parent) { // ignore adjacent vertex if it's the one that expanded this vertex (currNode)
						tempNode = getVertex(it->node);
						tempNode.parent = currNode.node; // set currNode as parent to vertex going in stack
						vstack.push(tempNode);
					}
				}
			}
			else
				return true; // cycle exists if currNode in visited
		}
		return false;
	}

private:
	list<Vertex> nodes;
	list<Vertex> visited;
	stack<Vertex> vstack;
};

int main() {
	int a, b;
	char c;
	Graph g;

	cout << "Input (e.g enter edge(1, 2) as 1,2), enter -1 to stop: \n";
	do {
		cin >> a;

		if (a == -1)
			continue;

		cin >> c >> b;

		g.addEdge(a, b);
	} while (a != -1);

	if (g.CycleDFS())
		cout << "There is a cycle.";
	else
		cout << "There is not a cycle.";
}