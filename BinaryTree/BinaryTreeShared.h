#ifndef _BINARY_TREE_SHARED_H
#define _BINARY_TREE_SHARED_H

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class NodeShared
{
public:
    T data;
    std::shared_ptr<NodeShared<T>> left;
    std::shared_ptr<NodeShared<T>> right;

    NodeShared(T& val) : data(val)
    {
#ifdef _DEBUG
        std::cout << "NodeShared{" << val << "}@" << this << std::endl;
#endif
    }

    ~NodeShared()
    {
#ifdef _DEBUG
        std::cout << "~NodeShared@" << this << std::endl;
#endif
        left.reset();
        right.reset();
    }
};

template <typename T>
class BinaryTreeShared
{
public:
    std::shared_ptr<NodeShared<T>> root;

    BinaryTreeShared()
    {
#ifdef _DEBUG
        std::cout << "BinaryTreeShared@" << this << std::endl;
#endif
    }

    ~BinaryTreeShared()
    {
#ifdef _DEBUG
        std::cout << "~BinaryTreeShared@" << this << std::endl;
#endif
        root.reset();
    }

    void makeTree(std::vector<T>& nodeValues)
    {
        std::queue<std::shared_ptr<NodeShared<T>>> children;
        std::shared_ptr<NodeShared<T>> left;
        std::shared_ptr<NodeShared<T>> right;
        std::shared_ptr<NodeShared<T>> currentNode;

        std::size_t numOfNodes = nodeValues.size();

        // Construct the root node
        root = std::make_shared<NodeShared<T>>(nodeValues[0]);

        // Left child of root
        if (numOfNodes > 1)
        {
            left = std::make_shared<NodeShared<T>>(nodeValues[1]);
            root->left = std::move(left);
            children.emplace(root->left);
        }

        // Right child of root
        if (numOfNodes > 2)
        {
            right = std::make_shared<NodeShared<T>>(nodeValues[2]);
            root->right = std::move(right);
            children.emplace(root->right);
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

                left = std::make_shared<NodeShared<T>>(nodeValues[i++]);
                currentNode->left = std::move(left);
                children.emplace(currentNode->left);

                if (i < numOfNodes)
                {
                    right = std::make_shared<NodeShared<T>>(nodeValues[i++]);
                    currentNode->right = std::move(right);
                    children.emplace(currentNode->right);
                }

            }
        }
    }
};


#endif