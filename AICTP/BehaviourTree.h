#pragma once

#include <iostream>
#include <List>

class BehaviourTree
{
public: 

	class Node
	{
	public:
		virtual bool run() = 0;
	};

	class CompositeNode : public Node
	{
	private:
		std::list<Node*> children;
	public:
		const std::list<Node*>& GetChildren() const { return children; }
		void AddChild(Node* child) { children.emplace_back(child); }
	};

	//Decorator Nodes have one child which the decorator can repeat, terminate or invert the child's result
	class DecoratorNode : public Node
	{
	private:
		Node* child;
	protected: 
		Node* GetChild() const { return child; }
	public:
		void SetChild(Node* newChild) { child = newChild; }
	};

	class Selector : public CompositeNode
	{
	public:
		virtual bool run() override 
		{
			//If one child succeeds run() succeeds
			for (Node* child : GetChildren()) 
				if (child->run())  
					return true;
			
			//All children failed so run() fails
			return false;  
		}
	};

	class Sequence : public CompositeNode
	{
	public:
		virtual bool run() override 
		{
			//If one child fails run() fails
			for (Node* child : GetChildren()) 
				if (!child->run())  
					return false;
			
			return true;  //All children suceeded
		}
	};

	class Root : public Node 
	{
	private:
		Node * child;
		friend class BehaviourTree;
		void setChild(Node* newChild) { child = newChild; }
		virtual bool run() override { return child->run(); }
	};

private:
	Root * root;
public:
	BehaviourTree() : root(new Root) {}
	void setRootChild(Node* rootChild) const { root->setChild(rootChild); }
	bool run() const { return root->run(); }

};

