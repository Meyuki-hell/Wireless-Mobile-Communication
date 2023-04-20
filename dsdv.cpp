#include <iostream>
#include <climits>
using namespace std;
int main()
{
	int n, m;
	cout << "Enter number of nodes: ";
	cin >> n;
	cout << "Enter number of edges: ";
	cin >> m;
	int dist[n][n], next[n][n];
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			dist[i][j] = INT_MAX;
			next[i][j] = -1;
		}
		dist[i][i] = 0;
	}
	for(int i=0; i<m; i++) {
		int u, v, w;
		cout << "Enter edge " << i+1 << ": source: ";
		cin >> u;
		cout << "destination: ";
		cin >> v;
		cout << "cost: ";
		cin >> w;
		dist[u-1][v-1] = w;
		next[u-1][v-1] = v-1;
	}
	for(int k=0; k<n; k++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k]+dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k]+dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
	for(int i=0; i<n; i++) {
		cout << "\nThe routing table for node " << i+1 << " is:\n";
		cout << "Destination\tNext Hop\tCost\n";
		for(int j=0; j<n; j++) {
			cout << j+1 << "\t\t" << next[i][j]+1 << "\t\t" << dist[i][j] << "\n";
		}
	}
	return 0;
}
