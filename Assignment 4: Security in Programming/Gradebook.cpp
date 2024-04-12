// Program to manage Dr. Goode's grades using Course and Student classes
// Only deals with one course
// Takes command line arguments that are not required
// First is starting file for the course; Second is file in which to save the course
// By Mary Elaine Califf
// Edited by Jackson Clark
// 3/14/19

// note that Student.h will be automatically included
#include "Course.h"
#include <fstream>
#include <ctype.h>
#include <iomanip>
#include <cstring>

// function prototypes

// create the course object using a starting file
Course* initializeCourse(const char* startingFile);

// create the course object without a file (but ask to see if one is wanted)
Course* initializeCourse();

// main program loop
void runProgram(Course* theCourse);

// program cleanup
void cleanUp(Course* theCourse, const char* saveFile);
void cleanUp(Course* theCourse);

// display the program menu and get the user's choice
int getMenuChoice();

// display the possible grade types and get the user's choice
int pickGradeType();

// get a student ID from the user
string getStudentID();

// add student to course with info from user
void addNewStudent(Course* theCourse);

// record grades given info from user
void recordGrades(Course* theCourse);

// change a student's grade with info from user
void changeGrade(Course* theCourse);

int main(int argc, char** argv)
{
  cout << "Welcome to Dr. Goode's Gradebook"<<endl;
  Course* theCourse = NULL;
  if (argc >1)
  {
    theCourse = initializeCourse(argv[1]);
  }
  else
  {
    theCourse = initializeCourse();
  }
  runProgram(theCourse);
  if (argc >2)
  {
    cleanUp(theCourse,argv[2]);
  }
  else
  {
    cleanUp(theCourse);
  }
  cout << "Thank you for using Dr. Goode's Gradebook"<< endl;
}

Course* initializeCourse(const char* startingFile)
{
  Course* myCourse = NULL;
  ifstream infile(startingFile); //opens the file
  myCourse = new Course(infile);
  infile.close();
  return myCourse;
}

Course* initializeCourse()
{
  char ans;
  string name;
  string junk;
  // ask the user if there is a file to start with
  cout << "Do you have a file that you want to read the course from? (y/n): ";
  cin.get(ans);
  getline(cin,junk);
  ans = tolower(ans);
  // if yes, get the file name and call the other init function
  if (ans == 'y')
  {
      cout << "Please enter the file name: ";
      getline(cin, name);
      return initializeCourse(name.c_str());
  }
  // else request the course name and create the Course object
  cout << "Please enter the course name: ";
  getline(cin, name);
  return new Course(name);
}

void runProgram(Course* theCourse)
{
  string id;
  int choice = getMenuChoice();
  double grade = 0.0;
  // loop to process response
  while (choice != 0)
  {
    switch (choice) {
      case 1:
        // add a student to the course
        addNewStudent(theCourse);
        break;
      case 2:
        // record a set of grades
        recordGrades(theCourse);
        break;
      case 3:
        // record a student's absence
        id = getStudentID();
        theCourse->recordAbsence(id);
        break;
      case 4:
        // change a particular grade for a student
        changeGrade(theCourse);
        break;
      case 5:
        // calculate and display a student's current course grade
        id=getStudentID();
      
        grade = theCourse->getCourseGrade(id);
        cout << "\nCurrent course grade: "<<setprecision(3)<<grade*100<<"%"<<endl;
        
        break;
      case 6:
        // display all info about a student
        id = getStudentID();
        cout << theCourse->createStudentReport(id);
        break;
      case 7:
        // display info about the class
        cout << theCourse->createCourseReport();
        break;
      default:
       cout << "That was not a valid menu choice. Please try again" << endl;
    }
    choice = getMenuChoice();
  }

}

void cleanUp(Course* theCourse, const char* fileName)
{
  ofstream outfile(fileName);
  theCourse->writeData(outfile);
  outfile.close();
}

void cleanUp(Course* theCourse)
{
  string name;
  // ask for file name and then call the other cleanUp
  // we're going to make them save the data
  cout << "Please enter a file name for the course data: ";
  cin >> name;
  cleanUp(theCourse, name.c_str());
}

int getMenuChoice()
{
  int choice;
  string junk;

  cout << "\n  1  Add Student\n";
  cout << "  2  Record Grades\n";
  cout << "  3  Record Student Absence\n";
  cout << "  4  Change Student Grade\n";
  cout << "  5  Check Student Course Grade\n";
  cout << "  6  Display Student\n";
  cout << "  7  Display Class Summary\n";
  cout << "  0  Exit\n\n";


  cout << "Enter your choice (0-7): ";
  cin >> choice;
  getline(cin,junk);
  return choice;
}

int pickGradeType()
{
  int choice;
  string junk;

  cout << "  1  Quiz\n";
  cout << "  2  Exam\n";
  cout << "  3  Paper\n\n";

  cout << "Enter the number for the grade type you want (1-3): ";
  cin >> choice;
  getline(cin,junk);
  return choice;
}

string getStudentID()
{
  string id;
  string junk;

  cout << "Please enter the student's id: ";
  cin >> id;
  getline(cin, junk);
  return id;
}

void addNewStudent(Course* theCourse)
{
  string id = getStudentID();
  string fName;
  string lName;
  cout << "Please enter the student's first name: ";
  getline(cin, fName);
  cout << "Please enter the student's last name: ";
  getline(cin, lName);
  theCourse->addStudent(id, fName, lName);
}

void recordGrades(Course* theCourse)
{
  string fileName;
  int gradeType;

  cout << "Please enter the name of the file the grades are in: ";
  cin >> fileName;
  gradeType = pickGradeType();
  switch (gradeType)
  {
    case 1:
      theCourse->recordQuiz(fileName);
      break;
    case 2:
      theCourse->recordExam(fileName);
      break;
    case 3:
      theCourse->recordPaper(fileName);
      break;
    default:
      cout << "I don't recognize that grade type";
  }
}

void changeGrade(Course* theCourse)
{
  string id = getStudentID();
  int gradeType = pickGradeType();
  int grade;
  int gradeIndex;
  string junk;

  cout << "Please enter the number of the assignment to be changed: ";
  cin >> gradeIndex;
  --gradeIndex;
  cout << "Please enter the new grade: ";
  cin >> grade;
  getline(cin, junk);
  switch (gradeType)
  {
    case 1:
      theCourse->correctQuizScore(id,grade,gradeIndex);
      break;
    case 2:
      theCourse->correctExamScore(id,grade,gradeIndex);
      break;
    case 3:
      theCourse->correctPaperScore(id,grade,gradeIndex);
      break;
    default:
      cout << "I don't recognize that grade type";
  }

}
