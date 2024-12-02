#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <string>

class Course;

class Student{
private:
    std::string name;
    int ID;
    Course** courses;
    int courseCount;
    static const int MAX_COURSES = 10;
public:
    Student();
    Student(const std::string& sName,int sID);
    void setName(const std::string& sName);
    void setID(int sID);
    void setCourseReferences(Course** course);
    const std::string& getName() const;
    int getID() const;
    Course** getCourseReferences();
    ~Student();
};

#endif // STUDENT_H_INCLUDED
