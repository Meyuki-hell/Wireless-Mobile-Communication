#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 1e9;

struct Node {
	int distance;
	int prev;
	bool visited;
	vector<pair<int, int> > neighbors;
};

void aodv(vector<Node>& nodes, int start, int end) {
 // Initialize all nodes
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].distance = INF;
		nodes[i].prev = -1;
		nodes[i].visited = false;
	}
	 // Set the distance to the start node to 0
	nodes[start].distance = 0;
	 // Create a priority queue to store unvisited nodes
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	 // Add the start node to the queue 
	 // Loop until the queue is empty
	while (!pq.empty()) {
		 // Get the node with the smallest distance
		int curr = pq.top().second;
		pq.pop();
		 // If the node has already been visited, skip it
		if (nodes[curr].visited) {
			continue;
		}
		 // Mark the node as visited
		nodes[curr].visited = true;
		 // If we've reached the end node, we're done
		if (curr == end) {
			return;
		}
		 // Update the distances of the node's neighbors
		for (int i = 0; i < nodes[curr].neighbors.size(); i++) {
			int neighbor = nodes[curr].neighbors[i].first;
			int distance = nodes[curr].neighbors[i].second;
			if (!nodes[neighbor].visited && nodes[curr].distance + distance < nodes[neighbor].distance) {
				nodes[neighbor].distance = nodes[curr].distance + distance;
				nodes[neighbor].prev = curr;
				pq.push(make_pair(nodes[neighbor].distance, neighbor));
			}
		}
	}
}
int main() {
 // Create the graph
	vector<Node> nodes(5);
	nodes[0].neighbors.push_back(make_pair(1, 2));
	nodes[0].neighbors.push_back(make_pair(3, 6));
	nodes[1].neighbors.push_back(make_pair(0, 2));
	nodes[1].neighbors.push_back(make_pair(2, 3));
	nodes[2].neighbors.push_back(make_pair(1, 3));
	nodes[2].neighbors.push_back(make_pair(4, 4));
	nodes[3].neighbors.push_back(make_pair(0, 6));
	nodes[3].neighbors.push_back(make_pair(4, 5));
	nodes[4].neighbors.push_back(make_pair(2, 4));
	nodes[4].neighbors.push_back(make_pair(3, 5));
	 // Run AODV to find the shortest path between nodes 0 and 4
	aodv(nodes, 0, 4);
	 // Print the shortest path
	cout << "Shortest path from node 0 to node 4: ";
	int curr = 4;
	while (curr != -1) {
		cout << curr << " ";
		curr = nodes[curr].prev;
	}
	cout << endl;
	return 0;
}
