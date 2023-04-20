#include <iostream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;
const int MAX_ROUND = 1000;
const int NUM_NODES = 100;
const int CLUSTER_SIZE = 10;
const double P = 0.05; // Probability of a node becoming a cluster head
const double E_INIT = 0.5; // Initial energy of each node
const double E_ELEC = 50e-9; // Energy required to run the radio transceiver circuitry for one bit
const double E_AMP = 100e-12; // Energy required to transmit one bit over a distance of one meter
const double D = sqrt(2); // Distance between nodes
const double ALPHA = 1; // Parameter for calculating the threshold energy
const int INF = 1e9;
struct Node {
 int id;
 double x;
 double y;
 double energy;
 bool cluster_head;
 int cluster_id;
 vector<int> neighbors;
};
double distance(Node a, Node b) {
 return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
void leach(vector<Node> &nodes) {
 // Initialize the round counter
 int round = 0;
 // Loop until the maximum number of rounds is reached
 while (round < MAX_ROUND) {
 // Reset the cluster IDs of all nodes
 for (int i = 0; i < nodes.size(); i++) {
 nodes[i].cluster_id = -1;
 }
 // Decide which nodes will become cluster heads
 random_device rd;
 mt19937 gen(rd());
 uniform_real_distribution<> dis(0, 1);
 for (int i = 0; i < nodes.size(); i++) {
 if (dis(gen) < P) {
 nodes[i].cluster_head = true;
 } else {
 nodes[i].cluster_head = false;
 }
 }
 // Form clusters around the cluster heads
 int cluster_id = 0;
 for (int i = 0; i < nodes.size(); i++) {
 if (nodes[i].cluster_head) {
 nodes[i].cluster_id = cluster_id;
 cluster_id++;
 }
 }
 for (int i = 0; i < nodes.size(); i++) {
 if (!nodes[i].cluster_head) {
 double min_distance = INF;
 int cluster_id = -1;
 for (int j = 0; j < nodes.size(); j++) {
 if (nodes[j].cluster_head) {
 double d = distance(nodes[i], nodes[j]);
 if (d < min_distance) {
 min_distance = d;
 cluster_id = nodes[j].cluster_id;
 }
 }
 }
 nodes[i].cluster_id = cluster_id;
 }
 }
 // Calculate the threshold energy for each node
 for (int i = 0; i < nodes.size(); i++) {
 nodes[i].energy = E_INIT - (E_ELEC + E_AMP * pow(distance(nodes[i], nodes[0]), ALPHA));
 }
 // Transmit data from each node to its cluster head
 for (int i = 0; i < nodes.size(); i++) {
 if (!nodes[i].cluster_head) {
 nodes[nodes[i].cluster_id].energy -=
 E_ELEC + E_AMP * pow(distance(nodes[i], nodes[nodes[i].cluster_id]), ALPHA);
 }
 }
 // Compute the average energy
 double total_energy = 0;
 int num_alive = 0;
 for (int i = 0; i < nodes.size(); i++) {
 if (nodes[i].energy > 0) {
 total_energy += nodes[i].energy;
 num_alive++;
 }
 }
 double avg_energy = total_energy / num_alive;
 cout << "Round " << round << ": Average energy = " << avg_energy << endl;
 // Advance to the next round
 round++;
 }
}
int main() {
// Generate the nodes and their locations
 random_device rd;
 mt19937 gen(rd());
 uniform_real_distribution<> dis(0, 1);
 vector<Node> nodes;
 for (int i = 0; i < NUM_NODES; i++) {
 Node node;
 node.id = i;
 node.x = dis(gen);
 node.y = dis(gen);
 node.energy = E_INIT;
 node.cluster_head = false;
 node.cluster_id = -1;
 nodes.push_back(node);
 }
 // Compute the neighbors of each node
 for (int i = 0; i < nodes.size(); i++) {
 for (int j = 0; j < nodes.size(); j++) {
 if (i != j && distance(nodes[i], nodes[j]) <= D) {
 nodes[i].neighbors.push_back(j);
 }
 }
 }
// Run LEACH
 leach(nodes);
 return 0;
}
