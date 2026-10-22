
/*
 * Course: COEN 2220 - Programming 2
 * Name: Joewel Maldonado
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic queue of tutoring requests
 * Due date: 22 October 2026
 */

#include <iostream>
#include <string>
using namespace std;

class TutoringQueue
{
private:
    struct Node
    {
        string studentId; // Store one student waiting for tutoring.
        Node *next;       // Point to the student immediately behind this one.
    };

    Node *front; // Point to the student who must be served next.
    Node *rear;  // Point to the student most recently added.

public:
    TutoringQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~TutoringQueue()
    {
        while (front != nullptr)
        {
            Node *nodeToDelete = front;
            front = front->next; // Advance before releasing the current node.
            delete nodeToDelete;
        }

        rear = nullptr;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    // ===== Part E: Queue operations =====

    // Add a new student to the rear of the queue.
    void enqueue(const string& newStudentId)
    {
        Node *newNode = new Node;
        newNode->studentId = newStudentId;
        newNode->next = nullptr;

        if (rear == nullptr)
        {
            // The first node is both front and rear.
            front = newNode;
            rear = newNode;
            return;
        }

        rear->next = newNode; // Connect the new node after the old rear.
        rear = newNode;       // Update rear to the new last node.
    }

    // Remove the student at the front of the queue.
    bool dequeue(string& servedStudentId)
    {
        if (front == nullptr)
        {
            return false; // Cannot remove a student from an empty queue.
        }

        Node *nodeToDelete = front;
        servedStudentId = front->studentId;
        front = front->next; // Move front to the next student.

        if (front == nullptr)
        {
            rear = nullptr; // The queue is empty after removing the last node.
        }

        delete nodeToDelete;
        return true;
    }
};

int main()
{
    cout << boolalpha;

    // ===== Part E: Test the dynamic tutoring queue =====

    // Create a TutoringQueue object.
    TutoringQueue tutoringQueue;
    string studentId;

    // Add TU-301, TU-318, and TU-327 in arrival order.
    tutoringQueue.enqueue("TU-301");
    tutoringQueue.enqueue("TU-318");
    tutoringQueue.enqueue("TU-327");

    // Dequeue and print the first two served student IDs.
    tutoringQueue.dequeue(studentId);
    cout << "Served student: " << studentId << endl;

    tutoringQueue.dequeue(studentId);
    cout << "Served student: " << studentId << endl;

    // Dequeue the last student and check whether the queue is empty.
    tutoringQueue.dequeue(studentId);
    cout << "Served student: " << studentId << endl;

    cout << "Queue empty: "
         << tutoringQueue.isEmpty() << endl;

    // Add TU-340 after the queue becomes empty.
    tutoringQueue.enqueue("TU-340");
    tutoringQueue.dequeue(studentId);

    cout << "Served student after empty queue: "
         << studentId << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * E1 — First arrival
 * Why must the first call to enqueue assign newNode to both front and rear?
 * Answer:
 * The first node is both the front and rear because
 * it is the only student in the queue.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer:
 * rear must become nullptr because the queue is empty.
 * Otherwise, it would point to a deleted node.
 *
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer:
 * The order is TU-301, TU-318, and TU-327.
 * A queue uses FIFO, while a stack uses LIFO.
 * The queue serves the first student added, but
 * the stack removes the last function added first.
 *
 */
