// BinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// The following 3 statements are required to enable heap debug functions for
// detecting memory leaks
// Reference: https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <chrono>

#include "BinaryTree.h"
#include "BinaryTreeClassic.h"

/// <summary>
/// Construct a Binary Tree from the specified vector. This Binary Tree uses
/// smart pointers.
/// </summary>
/// <param name="v"></param>
void makeManagedTree(std::vector<int>& v)
{
    BinaryTree<int> t1;
    t1.makeTree(v);
}

/// <summary>
/// Construct a Binary Tree from a locally declared vector. This function
/// is purely for comparison purposes with respect to memory usage of makeManagedTree.
/// </summary>
void makeManagedTreeLocal()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    BinaryTree<int> t1;
    t1.makeTree(v);
}

/// <summary>
/// Construct a smart pointer Binary Tree from the specified vector 10000 times.
/// </summary>
/// <param name="v"></param>
void makeManagedTreeStressTest(std::vector<int>& v)
{
    for (int i = 0; i < 1e4; ++i)
    {
        BinaryTreeClassic<int> t1;
        t1.makeTree(v);
    }
}

/// <summary>
/// Construct a Binary Tree from the specified vector. This Binary Tree uses
/// traditional pointers.
/// </summary>
/// <param name="v"></param>
void makeClassicTree(std::vector<int>& v)
{
    BinaryTreeClassic<int> t1;
    t1.makeTree(v);
}

/// <summary>
/// Construct a Binary Tree from a locally declared vector. This function
/// is purely for comparison purposes with respect to memory usage of makeClassicTree.
/// </summary>
void makeClassicTreeLocal()
{
    std::vector<int> v = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    BinaryTreeClassic<int> t1;
    t1.makeTree(v);
}

/// <summary>
/// Construct a traditional pointer Binary Tree from the specified vector 10000 times.
/// </summary>
/// <param name="v"></param>
void makeClassicTreeStressTest(std::vector<int>& v)
{
    for (int i = 0; i < 1e4; ++i)
    {
        BinaryTreeClassic<int> t1;
        t1.makeTree(v);
    }
}

int main()
{
    const bool makeLocal = false;
    const bool runStressTest = true;

    if (runStressTest)
    {
        std::vector<int> v1;

        for (int i = 0; i < 1000; ++i)
        {
            v1.emplace_back(i);
        }

        auto start = std::chrono::high_resolution_clock::now();
        makeClassicTreeStressTest(v1);
        auto stop = std::chrono::high_resolution_clock::now();
        auto durationClassic = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        
        start = std::chrono::high_resolution_clock::now();
        makeManagedTreeStressTest(v1);
        stop = std::chrono::high_resolution_clock::now();
        auto durationManaged = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "Classic execution time (ms): " << durationClassic.count() << std::endl;
        std::cout << "Managed execution time (ms): " << durationManaged.count() << std::endl;
    }
    else
    {
        if (makeLocal)
        {
            makeClassicTreeLocal();
            makeManagedTreeLocal();
        }
        else
        {
            std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            std::vector<int> v2 = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

            makeClassicTree(v2);

            makeManagedTree(v1);
        }
    }

    // Display a memory leak report when app exits
    _CrtDumpMemoryLeaks();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu