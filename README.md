# 3D Points
Ashdeep Singh

This project required us to implement a Points3D class (points3d.h). The class' main objective was to store a sequence of 3D points. The class contained a private data member named "sequence_", which was a pointer to an array on the heap. The elements of sequence_ themselves were of the type std::array<Object, 3>, which stored the actual point values. 

In order to implement Points3D objects, we implemented the "Big 5", which consisted of the Copy-Constructor, Copy-Assignment, Move-Constructor, Move-Assignment, and Desctuctor. Along with thses constructors, the user had the option to utilize the one-parameter and/or zero-parameter constructors. 
  
  * Copy-Constructor: constructs a new Points3D object by making a deep copy of a pre-existing Points3D object (lvalue).
  * Move-Consturctor: constructs a new Points3D object by moving data from a pre-existing Points3D object (rvalue).
  * Copy-Assignment: allows the values of Points3D object A to be replaced by that of Points3D object B (lvalue). 
  * Move-Assignment: moves the values from Points3D object B (rvalue) into Points3D object A.
  * Zero-Parameter Constructor: creates an empty Points3D object instance.
  * One-Parameter Conctructor: initializes the first set of 3D points using a std::array<Object, 3> type passed in.
 
 Besides the constructors, we also had to overload the "[]", "<<", ">>", and "+" operators to manipulate and access the sequence of points. 
  * "[]": returns an indexed element of sequence_.
  * "+": returns a new Points3D object which calculates the sum of two seperate Points3D objects. 
  * ">>": allows the user to input values and fill in a pre-existing Points3D object with the values passed in.
  * "<<": prints out all the values in an pre-existing Points3d Object; format- (x,y,z) (a,b,c) ...

Bugs Encountered:
  * Bug while outputting points stored in Points3D object. Formatting was incorrect. Solution: adding an endl at the end of the ">>" operator.
  * While using initializer list, date members had to be assigned values based on the order which they were declared in. Failure to do so, would cause a compiler error. 
  * When indexing the sequence_ data member, dereferencing is not necessary. The indexing operator dereferences and returns the value of the desired element. Dereferencing and indexing would return the element in the inner array, stored as an element. 


## To compile on terminal, type:

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points3d
```

## Providing Input from Standard Input

Input File: text_input_file.txt

To run with a given file that is redirected to standard input:

```bash
./test_points3d < test_input_file.txt
```
