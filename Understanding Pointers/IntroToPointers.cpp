#include <iostream>
using namespace std;

int main() {
    int a; // Declare an integer variable , having a name 'a' and type 'int' , 100c memory is allocated for variable a
    a = 10; // put the value 10 in variable a at 100c memory location

    int* ptr; // Declare a pointer variable named 'ptr' that can hold the address of an integer. It does not point to any valid memory location yet.
    ptr = &a; // Assign the address of variable 'a' to the pointer 'ptr'. Now, 'ptr' points to the memory location of 'a'.

    cout << "Value of a: " << a << endl; // Output: 10
    cout << "Address of a: " << &a << endl; // Output: Address of a
    cout << "Value stored in ptr (address of a): " << ptr << endl; // Output: Address of a
    cout << "Value pointed to by ptr (value of a): " << *ptr << endl; // Output: 10


    // What is * operator in C++?
    // The * operator is used to declare a pointer variable and to dereference a pointer. 
    // When used in a declaration, it indicates that the variable is a pointer. 
    // When used in an expression, it retrieves the value stored at the memory address that the pointer points to.

    // What is & operator in C++?
    // The & operator is used to get the address of a variable.
    // When you use & before a variable, it returns the memory address of that variable.
    // In the context of pointers, the & operator is used to assign the address of a variable to a pointer.


    return 0;
}