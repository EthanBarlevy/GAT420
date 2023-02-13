#include <iostream>

using namespace std;

class Node
{
public:
	Node(const string& description) : description{ description } 
	{}

	virtual Node* Execute();

protected:
	string description;
};

class DecisionNode : public Node
{
public:
	DecisionNode(const string& description) : Node(description) {}

	virtual bool IsTrue();

	Node* Execute() override
	{
		bool isTrue = IsTrue();
		cout << "DECISION: " << description;
		cout << ((isTrue) ? " -> TRUE" : " -> FALSE");
		cout << endl;

		return (isTrue) ? trueNode : falseNode;;
	}
public:
	Node* trueNode;
	Node* falseNode;
};

class DecisionBoolNode : public DecisionNode
{
public:
	DecisionBoolNode(const string& description, bool condition) :
		DecisionNode(description),
		condition{ condition }
	{}

	bool IsTrue() override
	{
		return (value == condition);
	}

public:
	bool value = true;
	bool condition = true;
};

class DecisionFloatNode : public DecisionNode
{
public:
	enum class Predicate
	{
		EQUAL,
		LESS,
		GREATER
	};

	DecisionFloatNode(const string& description, float condition, Predicate predicate) :
		DecisionNode(description),
		condition{ condition },
		predicate{ predicate }
	{}

	bool IsTrue() override
	{
		switch (predicate)
		{
		case Predicate::EQUAL:
			return (value == condition);
			break;
		case Predicate::LESS:
			return (value < condition);
			break;
		case Predicate::GREATER:
			return (value > condition);
			break;
		default:
			return false;
			break;
		}
	}

public:
	float value = 0;
	float condition = 0;
	Predicate predicate = Predicate::EQUAL;
};

struct ActionNode : public Node
{
	ActionNode(const string& description) : Node(description) {}

	virtual Node* Execute() override
	{
		cout << "ACTION: " << description << endl;
		return nullptr;
	}
};

void Transverse(Node* node)
{
	while (node != nullptr)
	{
		node = node->Execute();
	}
}

int main()
{
	DecisionFloatNode* 
}