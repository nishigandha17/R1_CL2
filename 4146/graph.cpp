//============================================================================
// Name        : Graph.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Graph C++, Ansi-style
//============================================================================

/*
 * first line of input file contains a integer representing number of nodes
 * second line contains single integer representing threshold value
 * third line contains single integer L i.e. number of links
 * next L lines contains three space saperated integer i,j and d where
 * i and j is node number and d is distance between them.
 *
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <iomanip>
using namespace std;
//int num_nodes=100;
int graph[10][10];
fstream myfile;

class node {
public:

	int node_num, dist;
	node *next;
	node(int n, int d) {
		this->node_num = n;
		this->dist = d;
		next = NULL;
	}
};

void insert_node(node *graph_list[], int num, node * p) {

	if (graph_list[num] == NULL) {
		graph_list[num] = p;
		return;
	}
	node *temp = graph_list[num];

	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = p;

}

int get_max_links(int nodes) {
	return (nodes * (nodes - 1)) >> 1;
}

void BFS(int num_nodes) {

	cout << "BFS ";
	bool visit[num_nodes];
	for (int i = 0; i < num_nodes; i++) {
		visit[i] = 0;
	}
	visit[0] = 1;
	queue<int> q;
	q.push(1);
	int num;
	while (!q.empty()) {
		num = q.front();
		cout << num << " --> ";
		q.pop();
		for (int i = 0; i < num_nodes; i++) {
			if (graph[num - 1][i] && !visit[i]) {
				visit[i] = 1;
				q.push(i + 1);
			}
		}

	}

	cout << endl;
}

void DFS(int num_nodes) {
	cout << "DFS  ";
	stack<int> s;
	bool visit[num_nodes];
	for (int i = 0; i < num_nodes; i++) {
		visit[i] = 0;
	}
	visit[0] = 1;
	s.push(1);
	int temp;
	while (!s.empty()) {
		a: temp = s.top();
		cout << temp << " --> ";
		s.pop();
		for (int i = 0; i < num_nodes; i++) {
			if (graph[temp - 1][i] && !visit[i]) {
				temp = i + 1;
				s.push(temp);
				visit[i] = 1;
				goto a;
			}
		}

	}
	cout << endl;

}

void matrix(int num_nodes, int num_links) {
	//init to zero
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++) {
			graph[i][j] = 0;
		}
	string stemp;
	int source, dest, dist;
	for (int i = 0; i < num_links; i++) {
		myfile >> stemp;
		source = atoi(stemp.c_str());
		myfile >> stemp;
		dest = atoi(stemp.c_str());
		myfile >> stemp;
		dist = atoi(stemp.c_str());
		--source;
		--dest;
		graph[source][dest] = dist;
		graph[dest][source] = dist;
	}

	cout << "Matrix:" << endl;
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_nodes; j++) {
			cout << setw(5) << graph[i][j];
		}
		cout << endl;
	}

}

node *graph_list[10];
void list(int num_nodes, int num_links) {
	//init to null;
	for (int i = 0; i < num_nodes; i++) {
		graph_list[i] = NULL;
	}
	string stemp;
	int source, dest, dist;
	for (int i = 0; i < num_links; i++) {
		myfile >> stemp;
		source = atoi(stemp.c_str());
		myfile >> stemp;
		dest = atoi(stemp.c_str());
		myfile >> stemp;
		dist = atoi(stemp.c_str());

		node *p = new node(dest, dist);
		node *q = new node(source, dist);
		--source;
		--dest;
		insert_node(graph_list, source, p);
		insert_node(graph_list, dest, q);

	}

	cout << "Adjacency List:" << endl;
	for (int i = 0; i < num_nodes; i++) {
		cout << i + 1;
		node * temp = graph_list[i];
		while (temp != NULL) {
			cout << " " << temp->node_num;
			temp = temp->next;
		}
		cout << endl;
	}

}

void BFS(int num_nodes, bool a) {
	cout << "BFS ";
	bool visit[num_nodes];
	for (int i = 0; i < num_nodes; i++) {
		visit[i] = 0;
	}
	visit[0] = 1;
	queue<int> q;
	q.push(1);
	int num;
	node * temp;

	while (!q.empty()) {
		num = q.front();
		cout << num << " --> ";
		temp = graph_list[num - 1];
		q.pop();

		while (temp) {
			if (!visit[temp->node_num - 1]) {
				visit[temp->node_num - 1] = 1;
				q.push(temp->node_num);
			}
			temp = temp->next;

		}

	}

	cout << endl;

}

void DFS(int num_nodes, bool a) {
	cout << "DFS  ";

	stack<int> s;
	bool visit[num_nodes];
	for (int i = 0; i < num_nodes; i++) {
		visit[i] = 0;
	}
	visit[0] = 1;
	s.push(1);

	node* temp;
	int itemp;
	while (!s.empty()) {

		b: itemp = s.top();
		temp = graph_list[itemp - 1];
		cout << itemp << " --> ";
		s.pop();

		while (temp) {
			if (!visit[temp->node_num - 1]) {
				itemp = temp->node_num;
				visit[itemp - 1] = 1;
				s.push(itemp);
				goto b;
			}
			temp = temp->next;

		}

	}
	cout << endl;

}
int main() {

	string str;
	int num_nodes, num_links, max_links, threshold;
	myfile.open("input.txt");

	if (!myfile.is_open()) {
		cout << "File not found" << endl;
		exit(1);
	}

	myfile >> str;
	num_nodes = atoi(str.c_str());

	max_links = get_max_links(num_nodes);

	myfile >> str;
	threshold = atoi(str.c_str());

	myfile >> str;
	num_links = atoi(str.c_str());

	if (((num_links * 100) / (float) max_links) >= threshold) {
		matrix(num_nodes, num_links);
		BFS(num_nodes);
		DFS(num_nodes);

	} else {
		list(num_nodes, num_links);
		BFS(num_nodes, true);
		DFS(num_nodes, true);

	}


	return 0;
}
