#include "../include/Student.h"
#include "../include/Administrator.h"
#include "../include/CONSTANTS.h"
#include "../include/Course.h"
#include "./inputValidation.cpp"
#include "swapIndices.cpp"
#include <iomanip>

Student::Student()
    : numCourses(0), ADMIN(nullptr), MAX_COURSES(STUDENT_MAX_COURSES) {
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
}

Student::Student(const string &username, const string &password,
                 const Administrator &admin)
    : User(username, password), numCourses(0), ADMIN(&admin),
      MAX_COURSES(STUDENT_MAX_COURSES) {
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
  if (username == "") // A flag indicating that the User constructor failed to
                      // set invalid credentials
    cout << "Student can not be created due to invalid credentials." << endl;
}

Student::~Student() {
  delete[] courses;
  delete[] grades;
}

void Student::registerCourse(const string &code) {
  if (numCourses < MAX_COURSES) {
    Course *course =
        ADMIN->getCourse(code); // Getting the course from the system
    if (course) {
      // Course already registered
      bool courseFound = false;
      for (int i = 0; i < numCourses; ++i) {
        if (courses[i].getCode() == code) {
          courseFound = true;
          cout << "Course with that code already registered" << endl;
          break;
        }
      }
      if (!courseFound) {
        courses[numCourses] = *course;
        grades[numCourses++] =
            -1; // Indicating that the grade is not yet set by the instructor
        course->addStudent(getId(), -1);
        cout << course->getName() << " is registered successfully." << endl;
      }
    } else
      cout << "Course with that specified code is not found in the system."
           << endl;
  } else
    cout << "Failed to register a course exceeding the maximum number of "
            "courses. "
            "Please remove a course and add later."
         << endl;
}

void Student::dropCourse(const string &code) {
  if (numCourses == 0) {
    cout << "No courses to drop." << endl;
    return;
  }

  int initialNumCourses = numCourses;
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      swapIndices(courses[i], courses[numCourses - 1]);
      swapIndices(grades[i], grades[numCourses - 1]);
      courses[i].removeStudent(getId());
      numCourses--;
    }
  }

  if (initialNumCourses == numCourses) // Did not find the course
    cout << "The course with the specified code was not found!" << endl;
  else
    cout << "Course dropped successfully." << endl;
}

void Student::setGrade(const string &code, const double &grade) {
  bool courseFound = false;
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      courseFound = true;
      grades[i] = grade;
      courses[i].addStudent(getId(), grade);
      Course *course = ADMIN->getCourse(
          code); // Reflecting the addition of student in the system
      course->addStudent(getId(), grade);
    }
  }
  if (!courseFound) {
    cout << "Student is not registered in that course yet.\nRegistering.."
         << endl;
    registerCourse(code);
    setGrade(code, grade);
  }
}

double Student::getGrade(const string &code) {
  if (numCourses == 0) {
    cout << "No courses to view your grade in" << endl;
    return -1;
  }
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      int numStudents = courses[i].getNumStudents();
      for (int j = 0; j < numStudents; ++j) {
        if (courses[i].getStudentIds()[j] == getId()) {
          return courses[i].getStudentGrades()[j];
        }
      }
    }
  }
  return -1;
}

double Student::getStats(const string &type) {
  if (type == "avg") {
    double sum = 0;
    for (int i = 0; i < numCourses; ++i) {
      double grade = courses[i].getGrade(getId());
      if (grade >= 0) // Grade is -1 when when it is not set by the instructor
        sum += grade;
    }
    return sum / numCourses;
  } else if (type == "max") {
    double max = 0.0;
    for (int i = 0; i < numCourses; ++i) {
      double grade = courses[i].getGrade(getId());
      if (grade > max)
        max = grade;
    }
    return max;
  } else if (type == "min") {
    double min = courses[0].getGrade(getId());
    for (int i = 1; i < numCourses; ++i) {
      double grade = courses[i].getGrade(getId());
      if (grade < min &&
          grade != -1) // Grade is -1 when when it is not set by the instructor
        min = grade;
    }
    return min;
  } else {
    cout << "Invalid statistics' type. Please enter 'avg', 'max', or 'min'."
         << endl;
    return -1;
  }
}

void Student::operator=(const Student &student) {
  User::operator=(student);
  numCourses = student.numCourses;
  ADMIN = student.ADMIN;
  delete[] courses;
  delete[] grades;
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
  for (int i = 0; i < numCourses; ++i) {
    courses[i] = student.courses[i];
    grades[i] = student.grades[i];
  }
}

void Student::display() const {
  User::display();

  // Display header for Courses and Grades
  cout << "Student Courses and Grades" << endl;
  cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << "Code"
       << setw(COURSE_NAME_MAX_LENGTH + SPACE) << "Name"
       << setw(COURSE_CREDITS_MAX_LENGTH + 2 * SPACE) << "Credits"
       << setw(GRADE_MAX_LENGTH + SPACE) << "Grade" << endl;
  cout << string(COURSE_CODE_MAX_LENGTH + SPACE, '-') << ' '
       << string(COURSE_NAME_MAX_LENGTH + SPACE - 1, '-') << ' '
       << string(COURSE_CREDITS_MAX_LENGTH + 2 * SPACE - 1, '-') << ' '
       << string(GRADE_MAX_LENGTH + SPACE - 1, '-') << endl;

  for (int i = 0; i < numCourses; ++i) {
    cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << courses[i].getCode()
         << setw(COURSE_NAME_MAX_LENGTH + SPACE) << courses[i].getName()
         << setw(COURSE_CREDITS_MAX_LENGTH + 2 * SPACE)
         << courses[i].getCredits() << setw(GRADE_MAX_LENGTH + SPACE)
         << grades[i] << endl;
  }
  cout << endl;
}

void Student::handleMenu() {
  int choice;
  do {
    cout << "1. Enroll in a new Course\n2. Drop a Course\n3. View Grade in a "
            "Specific Course\n4. Get statistics in all courses\n"
         << "5. Display All Information\n6. Logout\n";
    choice = getValidatedInteger();

    cout << endl;
    switch (choice) {
    case 1: {
      if (ADMIN->getNumCourses() == 0) {
        cout << "No courses in the system yet." << endl;
        break;
      }
      string *codes = ADMIN->getCourseCodes();
      string code;
      cout << "Available courses to register in:" << endl;
      for (int i = 0; i < ADMIN->getNumCourses(); ++i) {
        bool isRegistered = false;
        for (int j = 0; j < numCourses; ++j) {
          if (codes[i] == courses[j].getCode())
            isRegistered = true;
        }
        cout << ADMIN->getCourse(codes[i])->getName() << '(' << codes[i] << ')';
        if (isRegistered)
          cout << "<-- Already registered";
        if (i != ADMIN->getNumCourses() - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Type the course code: ";
      cin >> code;
      registerCourse(code);
      delete[] codes;
      break;
    }
    case 2: {
      string code;
      if (numCourses == 0) {
        cout << "No courses you're enrolled in yet." << endl;
        break;
      }
      cout << "Available courses to drop:" << endl;
      for (int i = 0; i < numCourses; ++i) {
        cout << courses[i].getName() << '(' << courses[i].getCode() << ')';
        if (i != numCourses - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Enter the course code to drop: ";
      cin >> code;
      dropCourse(code);
      break;
    }
    case 3: {
      string code;
      if (numCourses == 0) {
        cout << "No courses you're enrolled in yet." << endl;
        break;
      }
      cout << "Available courses to view:" << endl;
      for (int i = 0; i < numCourses; ++i) {
        cout << courses[i].getName() << '(' << courses[i].getCode() << ')';
        if (i != numCourses - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Enter the course code to view: ";
      cin >> code;
      double grade = getGrade(code);
      if (grade == -1)
        cout << "Your grade in the course with the specified code was not "
                "found or not yet graded."
             << endl;
      else
        cout << "Your grade in " << code << " is: " << getGrade(code) << endl;
      break;
    }
    case 4: {
      if (numCourses == 0) {
        cout << "No courses you're enrolled in yet." << endl;
        break;
      }
      cout << "1. Get the average grade\n2. Get the maximum grade\n3. Get the "
              "minimum grade\n";
      cin >> choice;
      if (choice == 1)
        cout << getStats("avg");
      else if (choice == 2)
        cout << getStats("max");
      else if (choice == 3)
        cout << getStats("min");
      else
        cout << "Invalid input.";
      cout << endl;
      break;
    }
    case 5:
      display();
      break;
    case 6:
      // Logout
      return;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 6);
}
