#include <iostream>
#include <string>

#include "Student.h"
#include "Course.h"

using namespace std;

Student::Student() = default;

 Student::Student(const string& sName,int sID){
 name=sName;
 ID=sID;
courses = nullptr;
courseCount = 0;
 }

 void Student::setName(const std::string& sName) {
    name = sName;
}

void Student::setID(int sID) {
    ID = sID;
}

void Student::setCourseReferences(Course** coursesArray) {
    courses = coursesArray;
}

const string& Student::getName() const{
    return name;
}

int Student::getID() const {
    return ID;
}

Course** Student::getCourseReferences() {
    return courses;
}

Student::~Student() {
    delete[] courses;
}
