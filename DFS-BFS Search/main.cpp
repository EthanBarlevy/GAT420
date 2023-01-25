#include <vector>
#include <stack>
#include <queue>
#include <iostream>

template <typename T>
struct node
{
	node(const T& data) : data{ data } {}

	T data = T();
	bool visited = false;
	std::vector<node*> children;
	node* parent = nullptr;
};

using char_node_t = node<char>;

std::vector<char_node_t*> getDFS(char_node_t* root, char target)
{
	if (root == nullptr) return std::vector<char_node_t*>();

	std::stack<char_node_t*> node_stack;
	root->visited = true;
	node_stack.push(root);
	
	while (node_stack.size())
	{
		// get current node
		char_node_t* current = node_stack.top();
		// check current node
		if (current->data == target)
		{
			std::cout << "found: " << current->data << std::endl;
			break;
		}
		else
		{
			std::cout << "visit: " << current->data << std::endl;
		}

		// if target not found go down tree
		// push unvisited children onto stack
		bool popNode = true;
		for (auto node : current->children)
		{
			// if child is unvisited, mark then push
			if (!node->visited)
			{
				node->visited = true;
				node_stack.push(node);
				popNode = false;
				break;
			}
		}

		// if no more children, pop the stack
		if (popNode)
		{
			node_stack.pop();
		}
	}

	// convert stack to vector
	// revert the stack
	std::vector<char_node_t*> path;
	while (!node_stack.empty())
	{
		path.insert(path.begin(), node_stack.top());
		node_stack.pop();
	}

	return path;
}

std::vector<char_node_t*> getBFS(char_node_t* root, char target)
{
	// check for valid node
	if (!root) return std::vector<char_node_t*>();

	// create the queue
	std::queue<char_node_t*> node_queue;
	root->visited = true;
	node_queue.push(root);

	while (!node_queue.empty())
	{
		// get current node
		char_node_t* current = node_queue.front();

		if (current->data == target)
		{
			std::cout << "found: " << current->data << std::endl;
			break;
		}
		else
		{
			std::cout << "visit: " << current->data << std::endl;
		}

		// if not found, push children into queue
		for (auto node : current->children)
		{
			if (!node->visited)
			{
				node->visited = true;
				node->parent = current;
				node_queue.push(node);
			}
		}
		node_queue.pop();
	}

	// convert queue to vector
	// reverse order
	std::vector<char_node_t*> path;
	char_node_t* node = node_queue.front();
	while (node)
	{
		// add node then set node to parent
		path.insert(path.begin(), node);
		node = node->parent;
	}

	return path;
}

int main()
{
	// create nodes
	char_node_t* nodeA = new char_node_t{ 'A' };
	char_node_t* nodeB = new char_node_t{ 'B' };
	char_node_t* nodeC = new char_node_t{ 'C' };
	char_node_t* nodeD = new char_node_t{ 'D' };
	char_node_t* nodeE = new char_node_t{ 'E' };
	char_node_t* nodeF = new char_node_t{ 'F' };

	// create tree from nodes
	nodeA->children.push_back(nodeB);
	nodeA->children.push_back(nodeC);
	nodeB->children.push_back(nodeD);
	nodeB->children.push_back(nodeE);
	nodeC->children.push_back(nodeE);
	nodeC->children.push_back(nodeF);

	// find seatch path to 'F' from node 'A'
	auto path = getBFS(nodeA, 'F');
	// display path
	std::cout << "path: ";
	for (auto node : path)
	{
		std::cout << "->" << node->data;
	}
	std::cout << std::endl;
}