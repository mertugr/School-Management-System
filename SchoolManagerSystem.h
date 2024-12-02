#ifndef SCHOOL_MANAGER_SYSTEM_H
#define SCHOOL_MANAGER_SYSTEM_H

#include <string>
#include "Course.h"
#include "Student.h"

class SchoolManagerSystem {
private:
    Student** students;
    Course** courses;
    int studentCount;
    int courseCount;

    void expandStudentsArray();
    void expandCoursesArray();

public:
    SchoolManagerSystem();
    ~SchoolManagerSystem();

    void addStudent(const std::string& name, int ID);
    void deleteStudent(const std::string& name, int ID);
    Student* findStudent(const std::string& name, int ID) const;
    void addCourse(const std::string& code, const std::string& name);
    Course* findCourse(const std::string& code) const;
    void listAllStudents() const;
    void listAllCourses() const;
    void listStudentsRegisteredToCourse(const std::string& code) const;
    void addStudentToCourse(const std::string& studentName, int studentID, const std::string& courseCode);
    void dropStudentFromCourse(const std::string& studentName, int studentID, const std::string& courseCode);
    void main_menu();
    void student_menu();
    void course_menu();
    void deleteStudent(Student* studentToDelete);
    void deleteCourse(Course* courseToDelete);
    void addSelectedStudentToCourse(Student* selectedStudent);
    void dropSelectedStudentFromCourse(Student* selectedStudent);

};

#endif // SCHOOL_MANAGER_SYSTEM_H
