#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

#include <string>

class Student;

class Course{
private:
    std::string name;
    std::string code;
    Student** students;
    static const int MAX_STUDENTS = 20;
public:
    Course();
    Course(const std::string& sName,const std::string& sCode);
    void setName(const std::string& sName);
    void setCode(const std::string& sCode);
    void setStudentReferences(Student** studentsArray);
    const std::string& getName() const;
    const std::string& getCode() const;
    Student** getStudentReferences();
    ~Course();
};


#endif // COURSE_H_INCLUDED
