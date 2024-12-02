#include <iostream>
#include <string>

#include "Course.h"
#include "Student.h"

using namespace std;

Course::Course(){
    name="";
    code="";
    students=new Student*[MAX_STUDENTS];
}

Course::Course(const string& sName,const string& sCode){
    name=sName;
    code=sCode;
    students=new Student*[MAX_STUDENTS];
}

void Course::setName(const string& sName) {
    name = sName;
}

void Course::setCode(const string& sCode) {
    code = sCode;
}

void Course::setStudentReferences(Student** studentsArray) {
    students = studentsArray;
}

const string& Course::getName() const {
    return name;
}

const string& Course::getCode() const{
    return code;
}

Student** Course::getStudentReferences() {
    return students;
}


Course::~Course() {
   delete[] students;
}
