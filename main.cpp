#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

template <typename T>
class List
{
protected:
    size_t size;
public:
    virtual bool isEmpty() const = 0;
    virtual T& topElement() {}
    virtual void display() const = 0;
    virtual ~List() {}
};

template <typename T>
struct Node
{
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
    Node(): next(nullptr) {}
};

template <typename T>
class Stack : public List<T>
{
private:
    Node<T>* top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() const override
    {
        return top == nullptr;
    }

    void push(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode -> next = top;
        top = newNode;
        List<T>::size++;
    }

    void pop()
    {
        if (!isEmpty())
        {
            Node<T>* temp = top;
            top = top -> next;
            delete temp;
        }

        List<T>::size--;
    }

    T& topElement()
    {
        if (!isEmpty())
        {
            return top -> data;
        }

        static T DefaultValue;
        return DefaultValue;
    }

    void display() const
    {
        Node<T>* current = top;
        while (current)
        {
            cout <<"Operation -> " <<  current -> data.OperationName << " Number -> " << current -> data.OperationNo << endl;
            current = current->next;
        }
        cout << endl;
    }

    void reverse()
    {
        Stack<T> auxStack;
        while (!isEmpty())
        {
            auxStack.push(this -> topElement());
            this -> pop();
        }

        *this = auxStack;
    }
};

template <typename T>
class Queue : public List<T>
{
private:
    static const int Q_SIZE = 4;
    T arr[Q_SIZE];
    int front;
    int rear;

public:
    Queue() : front(-1), rear(-1) {}

    bool isEmpty() const
    {
        return front == -1;
    }

    bool isFull() const
    {
        return (rear + 1) % Q_SIZE == front;
    }

    void enqueue(const T& value)
    {

        if (isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % Q_SIZE;
        }

        arr[rear] = value;
        List<T>::size++;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty! Cannot Dequeue From An Empty Queue!" << endl;
            return;
        }

        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % Q_SIZE;
        }

        List<T>::size--;
    }

    T& topElement()
    {
        if (!isEmpty())
        {
            return arr[front];
        }

        static T DefaultValue;
        return DefaultValue;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        int counter = 0;

        for(int i = front; i != rear;  i = (i + 1) % Q_SIZE)
        {
            cout << "For Product Number #" << (counter = counter + 1) << endl;
            arr[i].display();
        }

        cout << "For Product Number #" << counter + 1 << endl;
        arr[rear].display();
    }
};

template <typename T>
class LinkedList : public List<T>
{
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void insert(const T& value)
    {
        Node<T>* newNode = new Node<T>();
        newNode -> data = value;

        if (isEmpty())
        {
            head = newNode;
        }
        else
        {
            newNode -> next = head;
            head = newNode;
        }

        List<T>::size++;
    }

    void remove()
    {
        if (!isEmpty())
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            List<T>::size--;
        }

    }

    T& topElement() const
    {
        if (!isEmpty())
        {
            return head -> data.topElement();
        }

        static T def;
        return def;
    }

    void display() const
    {
        Node<T>* current = head;
        while (current)
        {
            current -> data.display();
            current = current -> next;
        }
    }

    Node<T>* getHead() const
    {
        return head;
    }
};

struct Step
{
    string OperationName;
    int OperationNo;
};

class SmartManufacturing
{
private:
    LinkedList<Queue<Stack<Step>>> LList;

public:

    void addProduct()
    {
        system("cls");
        system("color 7");

        Stack<Step> newStack;

        int OpNum;
        cout << "Enter the number of operations for the product: ";
        cin >> OpNum;

        while (OpNum <= 0)
        {
            cout << "\n!Invalid Input! , Please ReType The Number: ";
            cin >> OpNum;
        }

        for (int i = 0; i < OpNum; ++i)
        {
            Step operation;
            cout << "Enter operation #" << i + 1 << " Name: ";
            cin >> operation.OperationName;
            operation.OperationNo = i + 1;
            newStack.push(operation);
        }

        if (LList.isEmpty())
        {
            Queue<Stack<Step>> productStepsQueue;
            newStack.reverse();
            productStepsQueue.enqueue(newStack);

            LList.insert(productStepsQueue);
        }
        else
        {
            Node<Queue<Stack<Step>>>* firstNode = LList.getHead();

            while (firstNode -> next != nullptr)
            {
                firstNode = firstNode -> next;
            }

            if (firstNode -> data.isFull())
            {
                Node<Queue<Stack<Step>>>* newNode = new Node<Queue<Stack<Step>>>;
                newStack.reverse();
                newNode->data.enqueue(newStack);

                firstNode -> next = newNode;
            }
            else
            {
                newStack.reverse();
                firstNode -> data.enqueue(newStack);
            }
        }

        system("pause");
        system("cls");
    }


    void processNextStep()
    {
        system("cls");
        system("color 7");

        if (!LList.isEmpty())
        {
            Node<Queue<Stack<Step>>>* productNode = LList.getHead();

            if (!productNode->data.isEmpty())
            {
                Step currentProduct = productNode->data.topElement().topElement();

                cout << "Processing step for product: " << currentProduct.OperationName << endl;

                productNode->data.topElement().pop();

                if (productNode->data.topElement().isEmpty())
                {
                    productNode->data.dequeue();

                    if (productNode->data.isEmpty())
                    {
                        LList.remove();
                    }
                }
            }
            else
            {
                cout << "No products in the manufacturing process" << endl;
            }
        }
        else
        {
            cout << "No products in the manufacturing process" << endl;
        }

        system("pause");
        system("cls");
    }


    void Display()
    {
        system("cls");
        system("color 7");

        LList.display();

        system("pause");
        system("cls");
    }

    bool isEmpty() const
    {
        return LList.isEmpty();
    }

};

int main()
{
    SmartManufacturing sm;

    char ch;
    do
    {
        system("cls");
        system("color 0A");

        cout << "\t\t\t------------------------------------"<<endl;
        cout << "\t\t\t|--    SMART FACTORY SYSTEM    ----|"<<endl;
        cout << "\t\t\t------------------------------------"<<endl;
        cout << "\t\t\t[1] Add A Product"<<endl;
        cout << "\t\t\t[2] Process Next Step"<<endl;
        cout << "\t\t\t[3] Display Product Sequence"<<endl;
        cout << "\t\t\t[0] Exit"<<endl;
        cout << "Enter Your Choice: ";
        cin >> ch;

        switch(ch)
        {
        case '1':
            sm.addProduct();
            break;

        case '2':
            sm.processNextStep();
            break;

        case '3':
            sm.Display();
            break;

        case '0':
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            sleep(3);
        }
    }
    while(ch != '0');

    cout << "\t\t\t\tTHANK YOU!\n";
    return 0;
}
