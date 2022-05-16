#ifndef _BINARY_TREE_CLASSIC_H
#define _BINARY_TREE_CLASSIC_H

#include <iostream>

template <typename T>
class NodeClassic
{
public:
	T data;
	NodeClassic<T>* left;
	NodeClassic<T>* right;

    NodeClassic(T val) : data(val), left(NULL), right(NULL)
    {

    }

	~NodeClassic()
	{
#ifdef _DEBUG
		std::cout << "~NodeClassic@" << this << std::endl;
#endif
		if (left)
		{
			delete left;
		}

		if (right)
		{
			delete right;
		}
	}
};

template <typename T>
class BinaryTreeClassic
{
public:
    NodeClassic<T>* root;

    BinaryTreeClassic() : root(NULL)
    {
#ifdef _DEBUG
        std::cout << "BinaryTreeClassic@" << this << std::endl;
#endif
    }

    ~BinaryTreeClassic()
    {
#ifdef _DEBUG
        std::cout << "~BinaryTreeClass@" << this << std::endl;
#endif
        
        if (root)
        {
            delete root;
        }
    }

    void makeTree(std::vector<T>& nodeValues)
    {
        std::queue<NodeClassic<T>*> children;
        NodeClassic<T>* left;
        NodeClassic<T>* right;
        NodeClassic<T>* currentNode;

        std::size_t numOfNodes = nodeValues.size();

        // Construct the root node
        root = new NodeClassic<T>(nodeValues[0]);

        // Left child of root
        if (numOfNodes > 1)
        {
            left = new NodeClassic<T>(nodeValues[1]);
            root->left = left;
            children.emplace(left);
        }

        // Right child of root
        if (numOfNodes > 2)
        {
            right = new NodeClassic<T>(nodeValues[2]);
            root->right = right;
            children.emplace(right);
        }

        std::size_t numOfChildren = 0;

        // Iterate through the child nodes, and for each node:
        // 1. Construct its left child
        // 2. Construct its right child
        // 3. Add the new children to the list of nodes to be processed    
        for (std::size_t i = 3; i < numOfNodes; )
        {
            numOfChildren = children.size();
            for (int childIdx = 0; childIdx < numOfChildren && i < numOfNodes; ++childIdx)
            {
                // Construct new children for the current node
                // NOTE: the call to std::move has deallocated the pointer that existed at children.front(),
                // leaving a null pointer at the front of the queue, so it is vital that we pop it out of the queue
                currentNode = children.front();
                children.pop();

                left = new NodeClassic<T>(nodeValues[i++]);
                currentNode->left = left;
                children.emplace(left);

                if (i < numOfNodes)
                {
                    right = new NodeClassic<T>(nodeValues[i++]);
                    currentNode->right = right;
                    children.emplace(right);
                }

            }
        }
    }
};
#endif
