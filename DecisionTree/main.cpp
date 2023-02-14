#include <iostream>

using namespace std;

class Node
{
public:
	Node(const string& description) : description{ description } 
	{}

	virtual Node* Execute() = 0;

protected:
	string description;
};

class DecisionNode : public Node
{
public:
	DecisionNode(const string& description) : Node(description) {}

	virtual bool IsTrue() = 0;

	Node* Execute() override
	{
		bool isTrue = IsTrue();
		cout << "DECISION: " << description;
		cout << ((isTrue) ? " -> TRUE" : " -> FALSE");
		cout << endl;

		return (isTrue) ? trueNode : falseNode;;
	}
public:
	Node* trueNode = nullptr;
	Node* falseNode = nullptr;
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
	DecisionFloatNode* Health = new DecisionFloatNode("is health lower than 20", 20, DecisionFloatNode::Predicate::LESS);
	DecisionBoolNode* PlayerSeen = new DecisionBoolNode("is player seen", true);
	DecisionFloatNode* Healthpack = new DecisionFloatNode("is healthpack closer than 10m", 10, DecisionFloatNode::Predicate::LESS);
	DecisionFloatNode* PlayerDistance = new DecisionFloatNode("is player closer than 10m", 10, DecisionFloatNode::Predicate::LESS);

	ActionNode* Patrol = new ActionNode("patrol");
	ActionNode* MoveToPlayer = new ActionNode("move towards player");
	ActionNode* Attack = new ActionNode("attack");
	ActionNode* SearchForHP = new ActionNode("search for healthpack");
	ActionNode* Heal = new ActionNode("heal up");

	Health->trueNode = Healthpack;
	Health->falseNode = PlayerSeen;

	Healthpack->trueNode = Heal;
	Healthpack->falseNode = SearchForHP;

	PlayerSeen->trueNode = PlayerDistance;
	PlayerSeen->falseNode = Patrol;

	PlayerDistance->trueNode = Attack;
	PlayerDistance->falseNode = MoveToPlayer;

	Health->value = 55;
	Healthpack->value = 20;
	PlayerSeen->value = true;
	PlayerDistance->value = 5;

	Transverse(Health);
}