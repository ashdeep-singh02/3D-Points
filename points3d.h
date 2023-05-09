/*
Ashdeep Singh 
CSCI 335 
Assignment 1
Date: 02/18/2022
File Name: pointsd.h
Purpose: Implementation of the Points3D class. Code contains the implementation of the "Big 5" and operator overload functions to create objects and perform operations on them.
*/

#ifndef CSCI335_HOMEWORK1_POINTS3D_H_
#define CSCI335_HOMEWORK1_POINTS3D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

/*
Assignment 1 required us to implement a Points3D class. The class' main objective was to store a sequence of 3D points. 
The class contained a private data member named "sequence_", which was a pointer to an array on the heap. 
The elements of sequence_ themselves were of the type std::array<Object, 3>, which stored the actual point values. 
Constructors and Methods are descirbed as they appear in code below.
*/
template<typename Object>
class Points3D {
  public:
    // Zero-parameter constructor.
    // Set size to 0.
    // @post: empty Points3D onject instance has been created
    Points3D() : sequence_{nullptr}, size_{0}{}

    // Copy-constructor.
    // constructs a new Points3D object by making a deep copy of a pre-existing Points3D object (lvalue).
    // @param: rhs- a reference to an existing Points3D object
    // @post: new object is created, which is a deep copy of rhs
    Points3D(const Points3D &rhs){
        size_ = rhs.size();
        sequence_ = new std::array<Object, 3>[size_];
        for(size_t i = 0; i < rhs.size(); i++){
            (sequence_)[i] = (rhs.sequence_)[i]; //deep copy
        }
    }

    // Copy-assignment
    // allows the data members of Points3D object A to be replaced by that of Points3D object B (copies)
    // @pre: rhs and the current object are existing points3D object instances
    // @param: rhs- a reference to an exsisting Points3D object
    // @post: current object now stores the same data member values as rhs
    Points3D& operator=(const Points3D &rhs){
        Points3D copy = rhs; //copy rhs into copy
        std::swap(*this, copy);
        return *this;
    }

    // Move-constructor.
    // constructs a new Points3D object by moving data from a pre-existing Points3D object (rvalue)
    // @pre: rhs is an existing Points3D object instance (rvalue)
    // @param: rhs- a pre-existing Points3D object, passed in by rvalue
    // @post: rhs' data members are moved into the current object instance
    Points3D(Points3D &&rhs) :sequence_{rhs.sequence_}, size_{rhs.size_}{
        rhs.size_ = 0;
        rhs.sequence_ = nullptr; //set tot null to delete safely
    }

    // Move-assignment.
    // moves the data members from an existing Points3D object into the current instance
    // Just use std::swap() for all variables.
    // @pre: rhs is an existing Points3D object instance (rvalue)
    // @param: rhs- a pre-existing Points3D object, passed in by rvalue
    // @post: a new object is created with the same values as in rhs
    Points3D& operator=(Points3D &&rhs){
        std::swap(this->size_, rhs.size_);
        std::swap(this->sequence_, rhs.sequence_);
        return *this;
    }

    // @post: the object instance has been destroyed 
    ~Points3D() = default;
    // End of big-five.

    // One parameter constructor.
    // @param: item- a const reference to a std::array<Object, 3> type
    // @post: a new object instance has been created, the first element in sequence is set to item
    Points3D(const std::array<Object, 3>& item) {
        size_ = 1;
        sequence_ = new std::array<Object, 3>[size_];
        (sequence_)[0] = item; //set the first element in sequence to item
    }

    //@return: size of sequence_; number of points
    size_t size() const {
        return size_;
    }

    // returns an indexed element of sequence_
    // @location: an index to a location in the sequence.
    // @pre- location is less than or equal to the number of elements in the Object 
    // @returns the point at @location.
    // @param: location- index of element to be returned
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 3>& operator[](size_t location) const {
        if(location > (size_-1)){
            abort(); //if out of range, abort
        }
        return sequence_[location];
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    // @pre- c1 and c2 are existing Points3D objects 
    // @param- Const References to Point3D objects c1 and c2
    // @post- a new Points3D object is returned, composed of the sum of c2 and c1's point entries
    friend Points3D operator+(const Points3D &c1, const Points3D &c2) {
        Points3D smallerObj = c1.size_ > c2.size_ ? c2 : c1; 
        Points3D largerObj = c1.size_ > c2.size_ ? c1 : c2;
        Points3D ans; //new obj to store the resulting Points3D object in
        ans.size_ = largerObj.size_;
        ans.sequence_ = new std::array<Object, 3>[ans.size_];
        for(size_t i = 0; i < smallerObj.size_; i++){
            ans.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0]; //add the points of the 2 existing objects, store in the new obj
            ans.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            ans.sequence_[i][2] = c1.sequence_[i][2] + c2.sequence_[i][2];
        }
        for(size_t i = smallerObj.size_; i < largerObj.size_; i++){
            ans.sequence_[i] = largerObj.sequence_[i]; //append remaining points to end
        }
        return ans;
    }

    // Overloading the << operator.
    // prints out all the values in an pre-existing Points3d Object; format- (x,y,z) (a,b,c) ...
    // @pre- some_points is an existing Points3D object
    // @param: out- reference to the out stream; some_points- a Points3D object whose entries will be displayed
    // @post- points in some_points have been displayed to the user
    friend std::ostream &operator<<(std::ostream &out, const Points3D &some_points) {
        if(some_points.size() == 0){
             out << "()";
        }
        else{
            for(size_t i = 0; i < some_points.size(); i++){
                out << "(";
                for(size_t j = 0; j < 3; j++){
                    if(j != 2){
                        out << some_points.sequence_[i][j] << ", ";
                    }
                    else{
                        out << some_points.sequence_[i][j];
                    }
                }
                out << ") ";
            }
        }
        out << "\n";
        return out;
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    // allows the user to input values and fill in a pre-existing Points3D object with the values passed in
    // @param- in- reference to the input stream; some_points- Points3D object to be updated with values passed through in-stream
    // @post- some_points has been filled with values passed through instream
    friend std::istream &operator>>(std::istream &in, Points3D &some_points) {
        // Code missing.
        in >> some_points.size_;
        Object temp;
        some_points.sequence_ = new std::array<Object, 3>[some_points.size_]; 
        for(size_t i = 0; i < some_points.size(); i++){
            for(size_t k = 0; k < 3; k++){
                in >> temp; //read from in stream, store in temp var
                some_points.sequence_[i][k] = temp; //update value in some_points using temp 
            }
        }
        std::cout << std::endl; //formatting bug issue
        return in;
    }

  private:
    // Sequence of points.
    std::array<Object, 3> *sequence_; //array<type, size> 
    size_t size_;
    // Size of sequence.
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS3D_H_