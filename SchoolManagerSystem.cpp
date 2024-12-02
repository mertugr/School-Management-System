#include "SchoolManagerSystem.h"
#include <iostream>
#include <string>
#define MAX_STUDENTS 20

using namespace std;
//Constructor for Management System
SchoolManagerSystem::SchoolManagerSystem(){
    students=new Student*[10];
    courses=new Course*[10];
    studentCount=0;
    courseCount=0;
    }
//Deconstructor for delete everything
SchoolManagerSystem::~SchoolManagerSystem() {
    for (int i = 0; i < studentCount; ++i) {
        delete students[i];
    }
    delete[] students;

    for (int i = 0; i < courseCount; ++i) {
        delete courses[i];
    }
    delete[] courses;
}
//expandarray function for when the size not enough
void SchoolManagerSystem::expandStudentsArray() {
    Student** temp = new Student*[studentCount * 2];
    for (int i = 0; i < studentCount; ++i) {
        temp[i] = students[i];
    }
    delete[] students;
    students = temp;
}
//expandarray function for when the size not enough
void SchoolManagerSystem::expandCoursesArray() {
    Course** temp = new Course*[courseCount * 2];
    for (int i = 0; i < courseCount; ++i) {
        temp[i] = courses[i];
    }
    delete[] courses;
    courses = temp;
}
//addstudent function
void SchoolManagerSystem::addStudent(const string& name, int ID) {
    if (studentCount >= 10) {
        expandStudentsArray();
    }
    students[studentCount++] = new Student(name, ID);
}
//delete student function
void SchoolManagerSystem::deleteStudent(const string& name, int ID) {
    for (int i = 0; i < studentCount; ++i) {
        if (students[i]->getName() == name && students[i]->getID() == ID) {
            delete students[i];
            for (int j = i; j < studentCount - 1; ++j) {
                students[j] = students[j + 1];
            }
            --studentCount;
            return;
        }
    }
}
//findstudent function for return the existing student
Student* SchoolManagerSystem::findStudent(const string& name, int ID) const {
    for (int i = 0; i < studentCount; ++i) {
        if (students[i]->getName() == name && students[i]->getID() == ID) {
            return students[i];
        }
    }
    return nullptr;
}
//addcourse function
void SchoolManagerSystem::addCourse(const string& code, const string& name) {
    if (courseCount >= 10) {
        expandCoursesArray();
    }
    courses[courseCount++] = new Course(name, code);
}

//findCourse function for return the existing course
Course* SchoolManagerSystem::findCourse(const string& code) const {
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i]->getCode() == code) {
            return courses[i];
        }
    }
    return nullptr;
}
//listing all the students
void SchoolManagerSystem::listAllStudents() const {
    for (int i = 0; i < studentCount; ++i) {
        cout <<i<<" "<< students[i]->getName() << " " << students[i]->getID() << endl;
    }
}
//listing all the courses
void SchoolManagerSystem::listAllCourses() const {
    for (int i = 0; i < courseCount; ++i) {
        cout <<i<<" "<< courses[i]->getCode() << " " << courses[i]->getName() << endl;
    }
}
//listing students registired to existing course
void SchoolManagerSystem::listStudentsRegisteredToCourse(const string& code) const {
    Course* course = findCourse(code); // to determine existing course
    if (course) {
        Student** registeredStudents = course->getStudentReferences();
        if (registeredStudents) {
            for (int i = 0; i < MAX_STUDENTS; ++i) {
                if (registeredStudents[i] != nullptr) {
                    string studentName = registeredStudents[i]->getName();
                    if (!studentName.empty()) {
                        cout << studentName << " " << registeredStudents[i]->getID() <<endl;
                    }
                }
            }
        }
    }
}
//adding student to existing course
void SchoolManagerSystem::addStudentToCourse(const string& studentName, int studentID, const string& courseCode) {
    Student* student = findStudent(studentName, studentID); //determine the existing student
    if (!student) {
        return;
    }
    Course* course = findCourse(courseCode);
    if (!course) {
        return;
    }
    Student** studentPtr = new Student*[1];
    studentPtr[0] = student;
    course->setStudentReferences(studentPtr);
}
//drops student from a course
void SchoolManagerSystem::dropStudentFromCourse(const string& studentName, int studentID, const string& courseCode) {
      Student* student = findStudent(studentName, studentID); // Find the student
    if (!student) {
        return;
    }

    Course* course = findCourse(courseCode); // Find the course
    if (!course) {
        return;
    }
    Student** studentPtrs = course->getStudentReferences();

    // Find the student in the list and remove it
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (studentPtrs[i] == student) {
            studentPtrs[i] = nullptr; // Set the pointer to null to "remove" the student-
            return;
        }
    }

}

void SchoolManagerSystem::deleteStudent(Student* studentToDelete) {
    if (!studentToDelete) {
        return;
    }

    for (int i = 0; i < studentCount; ++i) {
        if (students[i] == studentToDelete) {
            delete students[i];
            for (int j = i; j < studentCount - 1; ++j) {
                students[j] = students[j + 1];
            }
            students[studentCount - 1] = nullptr;
            --studentCount;
            return;
        }
    }
}

void SchoolManagerSystem::deleteCourse(Course* courseToDelete) {
    if (!courseToDelete) {
        return;
    }

    for (int i = 0; i < courseCount; ++i) {
        if (courses[i] == courseToDelete) {
            delete courses[i];
            for (int j = i; j < courseCount - 1; ++j) {
                courses[j] = courses[j + 1];
            }
            courses[courseCount - 1] = nullptr;
            --courseCount;
            return;
        }
    }
}

void SchoolManagerSystem::addSelectedStudentToCourse(Student* selectedStudent) {
    if (!selectedStudent) {
        return;
    }

    int availableCourseCount = 0;
    for (int i = 0; i < courseCount; ++i) {
        // Check if the student is already registered for the course
        Student** registeredStudents = courses[i]->getStudentReferences();
        bool isRegistered = false;
        for (int j = 0; j < MAX_STUDENTS; ++j) {
            if (registeredStudents[j] == selectedStudent) {
                isRegistered = true;
                break;
            }
        }

        if (!isRegistered) {
            cout << availableCourseCount << " " << courses[i]->getName() << " " << courses[i]->getCode() << endl;
            ++availableCourseCount;
        }
    }
    int courseNumber;
    cout<<">>";
    cin >> courseNumber;

    if (courseNumber >= 0 && courseNumber < availableCourseCount) {

        int count = 0;
        for (int i = 0; i < courseCount; ++i) {
            // Check if the student is already registered for the course
            Student** registeredStudents = courses[i]->getStudentReferences();
            bool isRegistered = false;
            for (int j = 0; j < MAX_STUDENTS; ++j) {
                if (registeredStudents[j] == selectedStudent) {
                    isRegistered = true;
                    break;
                }
            }

            if (!isRegistered) {
                if (count == courseNumber) {
                    // Add the student to the selected course
                    addStudentToCourse(selectedStudent->getName(), selectedStudent->getID(), courses[i]->getCode());
                    return;
                }
                ++count;
            }
        }
    }
}

void SchoolManagerSystem::dropSelectedStudentFromCourse(Student* selectedStudent) {
    if (!selectedStudent) {
        return;
    }

    int availableCourseCount = 0;
    for (int i = 0; i < courseCount; ++i) {
        // Check if the student is already registered for the course
        Student** registeredStudents = courses[i]->getStudentReferences();
        bool isRegistered = false;
        for (int j = 0; j < MAX_STUDENTS; ++j) {
            if (registeredStudents[j] == selectedStudent) {
                isRegistered = true;
                break;
            }
        }

        if (isRegistered) {
            cout << availableCourseCount << " " << courses[i]->getName() << " " << courses[i]->getCode() <<endl;
            ++availableCourseCount;
        }
    }
    int courseNumber;
    cout<<">>";
    cin >> courseNumber;
    // Check if the selected course number is valid
    if (courseNumber >= 0 && courseNumber < availableCourseCount) {
        // Find the selected course based on the course number
        int count = 0;
        for (int i = 0; i < courseCount; ++i) {

            Student** registeredStudents = courses[i]->getStudentReferences();
            bool isRegistered = false;
            for (int j = 0; j < MAX_STUDENTS; ++j) {
                if (registeredStudents[j] == selectedStudent) {
                    isRegistered = true;
                    break;
                }
            }

            if (isRegistered) {
                if (count == courseNumber) {
                    // drop the student to the selected course
                    dropStudentFromCourse(selectedStudent->getName(), selectedStudent->getID(), courses[i]->getCode());
                    return;
                }
                ++count;
            }
        }
    }
}
void SchoolManagerSystem::main_menu() {
    int choice;
    do {
        cout << "Main Menu" <<endl;
        cout << "0 exit" <<endl;
        cout << "1 student" <<endl;
        cout << "2 course" <<endl;
        cout << "3 list_all_students" <<endl;
        cout << "4 list_all_courses" <<endl;
        cout<<">>";
        cin >> choice;

        switch (choice) {
            case 0:
                break;
            case 1:
                student_menu();
                break;
            case 2:
                course_menu();
                break;
            case 3:
                listAllStudents();
                break;
            case 4:
                listAllCourses();
                break;
            default:
                break;
        }
    } while (choice != 0);
}


void SchoolManagerSystem::student_menu() {
    int choice;
    do {
        cout << "0 up" <<endl;
        cout << "1 add_student" <<endl;
        cout << "2 select_student" <<endl;
        cout<<">>";
        cin >> choice;

        switch (choice) {
            case 0:
                main_menu();
                break;
            case 1: {
                cout<<">>";
                string name, line, tempID;
                cin.ignore();
                getline(cin, line);
                int index = line.find_last_of(" ");
                if(index != string::npos){
                    name = line.substr(0, index);
                tempID = line.substr(index + 1);
            }
                int ID = stoi(tempID);
                addStudent(name,ID);
                break;
            }
            case 2: {
                cout<<">>";
                string name, line, tempID;
                cin.ignore();
                getline(cin, line);
                int index = line.find_last_of(" ");
                if(index != string::npos){
                    name = line.substr(0, index);
                tempID = line.substr(index + 1);
            }
                int ID = stoi(tempID);
                Student* selectedStudent = findStudent(name, ID);
                if (selectedStudent) {
                    int student_choice;
                        cout << "0 up" <<endl;
                        cout << "1 delete_student" <<endl;
                        cout << "2 add_selected_student_to_a_course" <<endl;
                        cout << "3 drop_selected_student_from_a_course" <<endl;
                        cout<<">>";
                        cin>>student_choice;
                            switch(student_choice){
                            case 0:
                                student_menu();
                                break;
                            case 1:
                                deleteStudent(selectedStudent);
                                break;
                            case 2:
                                addSelectedStudentToCourse(selectedStudent);
                                break;
                            case 3:
                                dropSelectedStudentFromCourse(selectedStudent);
                                break;
                                default:
                                    break;
                                    }

                }
                break;
            }
            default:
                break;
        }
    } while (choice != 0);
}

void SchoolManagerSystem::course_menu() {
    int choice;
    do {
        cout << "0 up" <<endl;
        cout << "1 add_course" <<endl;
        cout << "2 select_course" <<endl;
        cout<<">>";
        cin >> choice;

        switch (choice) {
            case 0:
                main_menu();
                break;
            case 1: {
                cout<<">>";
                string code, name,line;
                cin.ignore();
                getline(cin,line);
                int a=0;
                while(line[a] != ' '){
                    code += line[a];
                    a++;
                }
                a++;
                while(a<line.size()){
                    name += line[a];
                    a++;
                }
                addCourse(code, name);
                break;
            }
            case 2: {
                cout<<">>";

                string code, name,line;
                cin.ignore();
                getline(cin,line);
                int a=0;
                while(line[a] != ' '){
                    code += line[a];
                    a++;
                }
                a++;
                while(a<line.size()){
                    name += line[a];
                    a++;
                }
                Course* selectedCourse = findCourse(code);
                if (selectedCourse) {
                    int course_choice;
                        cout << "0 up" <<endl;
                        cout << "1 delete_course" <<endl;
                        cout << "2 list_students_registered_to_the_selected_course" <<endl;
                        cin>>course_choice;
                            switch(course_choice){
                            case 0:
                                course_menu();
                                break;
                            case 1:
                                deleteCourse(selectedCourse);
                                break;
                            case 2:
                                 listStudentsRegisteredToCourse(selectedCourse->getCode());
                                 break;
                                default:
                                    break;
                                    }
                }
                break;
            }
            default:
                break;
        }
    } while (choice != 0);
}
