#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class Node
{
public:
    T data;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    Node(T& val) : data(val)
    {

    }

    ~Node()
    {
        std::cout << "~Node@" << this << std::endl;
    }
};

template <typename T>
class BinaryTree
{
public:
    std::unique_ptr<Node<T>> root;

    ~BinaryTree()
    {
        std::cout << "~BinaryTree@" << this << std::endl;
        root.reset();
    }

    void makeTree(std::vector<T>& nodeValues)
    {
        std::queue<std::unique_ptr<Node<T>>> children;
        std::unique_ptr<Node<T>> left;
        std::unique_ptr<Node<T>> right;
        std::unique_ptr<Node<T>> currentNode;

        std::size_t numOfNodes = nodeValues.size();

        // Construct the root node
        root = std::make_unique<Node<T>>(nodeValues[0]);

        // Left child of root
        if (numOfNodes > 1)
        {
            left = std::make_unique<Node<T>>(nodeValues[1]);
            root->left = std::move(left);
            children.emplace(std::make_unique<Node<T>>(nodeValues[1]));
        }

        // Right child of root
        if (numOfNodes > 2)
        {
            right = std::make_unique<Node<T>>(nodeValues[2]);
            root->right = std::move(right);
            children.emplace(std::make_unique<Node<T>>(nodeValues[2]));
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
                currentNode = std::move(children.front());
                children.pop();
                
                left = std::make_unique<Node<T>>(nodeValues[i]);
                children.emplace(std::make_unique<Node<T>>(nodeValues[i++]));

                if (i < numOfNodes)
                {
                    right = std::make_unique<Node<T>>(nodeValues[i]);
                    children.emplace(std::make_unique<Node<T>>(nodeValues[i++]));
                }

                currentNode->left = std::move(left);
                currentNode->right = std::move(right);               
            }
        }
    }
};


#endif