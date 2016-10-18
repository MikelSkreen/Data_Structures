// Cpt S 223 - Directed Graph Homework
// DirectedGraph.cpp
// (put student name here)
#include "DirectedGraph.h"

DirectedGraph::DirectedGraph()
{
	// No initialization needed
}

DirectedGraph::~DirectedGraph()
{
	// Free all nodes and edges
	for (int i = 0; i < m_nodes.size(); i++)
	{
		delete m_nodes[i];
	}
	m_nodes.clear();
	for (int i = 0; i < m_edges.size(); i++)
	{
		delete m_edges[i];
	}
	m_edges.clear();

	// Make sure the node map is cleared too
	m_nodeMap.clear();
}

bool DirectedGraph::AddNode(const string& nodeName, const string& nodeData)
{
	Node* newNode = new Node(nodeName, nodeData);
	m_nodes.push_back(newNode);
	m_nodeMap.emplace(nodeName, m_nodes.size()-1);
}
	
// Adds an edge to the graph that starts at the source node, 
// and goes to the target node.
// If the graph already contains an edge going from the specified 
// source to target node then false is returned and no modification 
// occurs.
// If either or both of the two nodes don't exist in the graph then 
// false is returned and no modification occurs.
// Otherwise the edge will be added. Note that an edge from N1 (source) 
// to N2 (target) is different than an edge from N2 (source) to N1 (target).
bool DirectedGraph::AddEdge(const string& sourceNodeName, const string& targetNodeName)
{
	string target = targetNodeName;
	string source = sourceNodeName;

	if(NodeExists(source) == false)
		return false;
	else if (NodeExists(target) == false)
		return false;
	else
	{
		for (int i=0; i < m_edges.size(); i++)
		{
			if(m_edges[i]->srcI == GetNodeIndex(source) && m_edges[i]->targetI == GetNodeIndex(target))
				return false;
		}

		Edge* newEdge = new Edge(GetNodeIndex(source), GetNodeIndex(target));
		m_edges.push_back(newEdge);
	}
}

// Gets the degree of the node with the specified name. -1 is returned 
// if no such node exists in the graph.
int DirectedGraph::GetDegree(const string& nodeName) const
{
	if (NodeExists(nodeName) == false)
		return -1;

	int nodeIndex = m_nodeMap(nodeName);
	int degree = m_nodes[nodeIndex]->In.size() + m_nodes[nodeIndex]->Out.size();
	
	return degree;
}

int DirectedGraph::GetNodeIndex(const string& nodeName) const
{
	// Get the index of the node from the hash map
	unordered_map<string, int>::const_iterator it = m_nodeMap.find(nodeName);
	if (it == m_nodeMap.end()) { return -1; }
	return it->second;
}

DirectedGraph::Edge* DirectedGraph::findEdge(string& source, string& target) const
{
	Edge* curr = new Edge(m_edges[0]->srcI, m_edges[0]->targetI);
	int i = 0;
	for (i = 1; curr->srcI != m_edges[i]->srcI && curr->targetI != m_edges[i]->targetI; i++){}

	return m_edges[i];
}

bool DirectedGraph::findShortestData(Node* current, string& end, list<Node*> queue, vector<Edge*> &trail) const
{
	//visited[GetNodeIndex(current->Data)] = true;
	if (current->Data == end)
	{
		return true;
	}
	else if (current->Out.size() == 0) // checks to see if Node has any children
	{
		queue.pop_front();
		trail.pop_back(); // pop edge off stack
		findShortestData(queue.front(), end, queue, trail);
	}
	else
	{
		for (int i = 0; i < current->Out.size(); i++)
		{
			if (m_nodes[current->Out[i]->targetI]->Data == end) // checks to see if node has been checked
			{
				trail.push_back(findEdge(current->Data, m_nodes[current->Out[i]->targetI]->Data));
				return true;
			}
			queue.push_back(m_nodes[current->Out[i]->targetI]); // if not then adds node to queue
		}

	} // at this point the queue should be populated with all current children and parent of node

	queue.pop_front();
	trail.push_back(findEdge(current->Data, queue.front()->Data)); // add edge to stack
	findShortestData(queue.front(), end, queue, trail);

	return false;
}

bool DirectedGraph::findShortestName(Node* current, string& end, list<Node*> queue, vector<Edge*> &trail) const
{
	//visited[GetNodeIndex(current->Data)] = true;
	if (current->Name == end)
	{
		return true;
	}
	else if (current->Out.size() == 0) // checks to see if Node has any children
	{
		queue.pop_front();
		trail.pop_back(); // pop edge off stack
		findShortestName(queue.front(), end, queue, trail);
	}
	else
	{
		for (int i = 0; i < current->Out.size(); i++)
		{
			if (m_nodes[current->Out[i]->targetI]->Name == end) // checks to see if node has been checked
			{
				trail.push_back(findEdge(current->Name, m_nodes[current->Out[i]->targetI]->Name));
				return true;
			}
			queue.push_back(m_nodes[current->Out[i]->targetI]); // if not then adds node to queue
		}

	} // at this point the queue should be populated with all current children and parent of node

	queue.pop_front();
	trail.push_back(findEdge(current->Name, queue.front()->Name)); // add edge to stack
	findShortestName(queue.front(), end, queue, trail);

	return false;
}

// Gets the shortest path from the specified start to end nodes. If no path exists 
// from the start to end nodes then false is returned and the traversalList object 
// is not modified. Otherwise the traversalList is filled with strings representing 
// the sequence of nodes for the shortest path from start to end. These strings 
// will be the node names if nodeDataInsteadOfName is false, otherwise they will be 
// the node data values (which are strings).
bool DirectedGraph::GetShortestPath(const string& startNode, const string& endNode, 
									bool nodeDataInsteadOfName, vector<string>& traversalList) const
{
	Node* Cur;
	bool success;
	list<Node*> queue;

	string start = startNode;
	string end = endNode;

	vector<Edge*> trail;

	bool *visited = new bool[m_nodes.size()];
	for (int i = 0; i < m_nodes.size()-1; i++)
		visited[i] = false;

	if (nodeDataInsteadOfName == 0)
	{
		success = findShortestName(m_nodes[GetNodeIndex(start)], end, queue, trail);
	}
	else
	{
		success = findShortestData(m_nodes[GetNodeIndex(start)], end, queue, trail);
	}

	vector<Edge*> final;
	final[0] = trail.pop_back();
	int i = 1;
	while (trail.size() != 0)
	{
		
	}
	

	return success;
}

bool DirectedGraph::NodeExists(const string& nodeName) const
{
	for(int i=0; i < m_nodes.size(); i++)
	{
		if(m_nodes[i]->Name == nodeName)
			return true;
	}
	return false;
}