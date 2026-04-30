#include <iostream>
using namespace std;


struct Point {
    int x;
    int y;
};


int main(){

    Point p1; // Declare a variable of type Point named p1. Memory is allocated for p1, which contains two integer members: x and y.
    p1.x = 10; // Assign the value 10 to the x member of p1. This means that the x coordinate of point p1 is now 10.
    p1.y = 20; // Assign the value 20 to the y member of p1. This means that the y coordinate of point p1 is now 20.

    Point* ptr; // Declare a pointer variable named 'ptr' that can hold the address of a Point structure. It does not point to any valid memory location yet.
    ptr = &p1; // Assign the address of variable 'p1' to the pointer 'ptr'. Now, 'ptr' points to the memory location of 'p1'.

    cout << "Value of p1.x: " << p1.x << endl; // Output: 10
    cout << "Value of p1.y: " << p1.y << endl; //

    cout << "Address of p1: " << &p1 << endl; // Output: Address of p1
    cout << "Value stored in ptr (address of p1): " << ptr << endl; // Output: Address of p1
    cout << "Value pointed to by ptr (value of p1.x): " << (*ptr).x << endl; // Output: 10
    cout << "Value pointed to by ptr (value of p1.y): " << (*ptr).y << endl; // Output: 20

    // ptr->x is a shorthand for (*ptr).x, and ptr->y is a shorthand for (*ptr).y.
    cout << "Value pointed to by ptr (value of p1.x using arrow operator): " << ptr->x << endl; // Output: 10
    cout << "Value pointed to by ptr (value of p1.y using arrow operator): " << ptr->y << endl; // Output: 20   

    // The arrow operator (->) is used to access members of a structure or class through a pointer.
    // When you have a pointer to a structure or class, you can use the arrow operator to access its members directly without needing to dereference the pointer first.
    


    return 0;
}