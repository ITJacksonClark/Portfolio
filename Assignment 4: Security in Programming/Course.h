// Manages all student grades for one of Dr. Goode's English courses
// By Mary Elaine Califf
// Edited by Jackson Clark
// 3/13/19

#include "Student.h"

class Course
{
public:
  static const int MAX_STUDENTS = 40;

private:
  string name;
  int numStudents;
  Student* studentList[MAX_STUDENTS];
  int quizzesGiven;
  int examsGiven;
  int papersGiven;


public:
  // constructors
  Course(string courseName);
  Course(istream& infile);
  Course(const Course& orig); // copy constructor

  // destructor
  ~Course(); // not worrying about making it virtual, because we're not allowing for inheritance

  // assignment operator
  Course& operator=(const Course& rhs);


  // getters
  string getName() const { return name; }
  int getNumStudents() const { return numStudents; }
  int getQuizzesGiven() const { return quizzesGiven; }
  int getExamsGiven() const { return examsGiven; }
  int getPapersGiven() const { return papersGiven; }

  // add a student to the course
  void addStudent(string id, string fName, string lName);

  // record grade from file methods
  void recordExam(string fileName);
  void recordQuiz(string fileName);
  void recordPaper(string fileName);

  // methods to correct scores for a particular student
  void correctExamScore(string id, int grade, int gradeIndex);
  void correctQuizScore(string id, int grade, int gradeIndex);
  void correctPaperScore(string id, int grade, int gradeIndex);

  // record a student's absence
  void recordAbsence(string id);

  // get a particular student's current course grade
  double getCourseGrade(string id);

  // returns a string containing a formatted reported with all
  //  of the student's data
  string createStudentReport(string id);

  // returns a string containing a formatted report of all
  // students' ids, names, and current course grades
  string createCourseReport();

  // write out the course data in our standard file format
  void writeData(ostream& outfile);

private:
  int findStudent(string id);

};
