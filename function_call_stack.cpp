
/*
 * Course: COEN 2220 - Programming 2
 * Name: Joewel Maldonado
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic stack of active function calls
 * Due date: 22 October 2026
 */

#include <iostream>
#include <string>
using namespace std;

class FunctionCallStack
{
private:
    // ===== Part C: Node and class data members =====

    struct Node
    {
        string functionName;
        Node *next;
    };

    Node *top;

public:
    // ===== Part C: Constructor =====

    FunctionCallStack()
    {
        top = nullptr;
    }

    // ===== Part D: Stack operations =====

    bool isEmpty() const
    {
        return top == nullptr;
    }

    void push(const string& newFunctionName)
    {
        Node *newNode = new Node;
        newNode->functionName = newFunctionName;
        newNode->next = top;
        top = newNode;
    }

    bool pop(string& removedFunctionName)
    {
        if (isEmpty())
        {
            return false;
        }

        Node *nodeToDelete = top;
        removedFunctionName = top->functionName;
        top = top->next;

        delete nodeToDelete;
        return true;
    }

    bool peek(string& topFunctionName) const
    {
        if (isEmpty())
        {
            return false;
        }

        topFunctionName = top->functionName;
        return true;
    }

    ~FunctionCallStack()
    {
        while (top != nullptr)
        {
            Node *nodeToDelete = top;
            top = top->next;
            delete nodeToDelete;
        }
    }
};

int main()
{
    cout << boolalpha;

    FunctionCallStack callStack;
    string functionName;

    callStack.push("main");
    callStack.push("loadSchedule");
    callStack.push("formatSchedule");

    callStack.peek(functionName);
    cout << "Current function: " << functionName << endl;

    while (callStack.pop(functionName))
    {
        cout << "Returned from function: "
             << functionName << endl;
    }

    cout << "Stack empty: " << callStack.isEmpty() << endl;

    cout << "Pop from empty stack succeeded: "
         << callStack.pop(functionName) << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer:
 * newNode->next must point to the old top first. Otherwise,
 * changing top too early would lose the previous node.
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer:
 * The order is formatSchedule, loadSchedule, and main.
 * A stack uses LIFO, so the last function added is the first removed.
 *
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer:
 * The destructor must save the next node before deleting the current one.
 * Otherwise, it would lose access to the rest of the stack.
 *
 */
