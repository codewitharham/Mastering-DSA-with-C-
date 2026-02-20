#include <iostream>
using namespace std;

template <class T, int SIZE>
class Stack {
    private:
        int top;
        T arr[SIZE]; // Fixed-size array known at compile time
    
    public:
        Stack() {
            top = -1;
        }
        
        void push(T value) {
            if (top == SIZE - 1) {
                cout << "Stack overflow. Cannot push " << value << "." << endl;
            } else {
                top = top + 1;
                arr[top] = value;
            }
        }

        T pop() {
            if (top == -1) {
                cout << "Stack underflow. Cannot pop from an empty stack." << endl;
                return T();
            } else {
                T value = arr[top]; 
                top = top - 1; 
                return value; 
            }
        }
};

int main() {
    Stack<int, 5> intStack; // Size specified as template parameter
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.push(40);
    intStack.push(50);
    intStack.push(60); // Stack overflow

    cout << "Popped value: " << intStack.pop() << endl;
    cout << "Popped value: " << intStack.pop() << endl;
    cout << "Popped value: " << intStack.pop() << endl;
    cout << "Popped value: " << intStack.pop() << endl;
    cout << "Popped value: " << intStack.pop() << endl;
    cout << "Popped value: " << intStack.pop() << endl; // Underflow

    return 0;
}