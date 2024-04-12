// Class for managing a student's grades for Dr. Goode's English classes
// By Mary Elaine Califf
// Edited by Jackson Clark
// 3/13/19

#include <string>
#include <iostream>
using namespace std;

class Student
{
  // useful constants
public:
  static const int MAX_QUIZ_POINTS = 5;
  static const int MAX_EXAM_POINTS = 100;
  static const int MAX_PAPER_POINTS = 40;
  static constexpr double QUIZ_WEIGHT = 0.4;
  static constexpr double EXAM_WEIGHT = 0.3;
  static constexpr double PAPER_WEIGHT = 0.3;
  static const int MAX_NUM_QUIZZES = 45;
  static const int MAX_NUM_EXAMS = 4;
  static const int MAX_NUM_PAPERS = 8;

private:
  string studentID;
  string firstName;
  string lastName;
  int numAbsences;
  int numExamGrades;
  int examScores[MAX_NUM_EXAMS];
  int numQuizGrades;
  int quizScores[MAX_NUM_QUIZZES];
  int numPaperGrades;
  int paperScores[MAX_NUM_PAPERS];

public:
  // constructors
  Student(string id, string fName, string lName);
  Student(istream& infile);

  // getters
  string getStudentID() const { return studentID; }
  string getFirstName() const { return firstName; }
  string getLastName() const { return lastName; }
  int getNumAbsences() const { return numAbsences; }
  int getQuizScore(int index) const { return quizScores[index]; }
  int getExamScore(int index) const { return examScores[index]; }
  int getPaperScore(int index) const { return paperScores[index]; }

  // methods for modifying existing examScores
  void updateQuizScore(int score, int index) 
  {
    if(index < MAX_NUM_QUIZZES)
    {
      quizScores[index]=score; 
    }
    else
    {
      cout<<"\nThe index given is over the specified limit for the amount of quiz scores available."<<endl;
    }
  }
  void updateExamScore(int score, int index) 
  { 
    if(index < MAX_NUM_EXAMS)
    {
      examScores[index]=score; 
    }
    else
    {
      cout<<"\nThe index given is over the specified limit for the amount of exam scores available."<<endl;
    }
  }
  void updatePaperScore(int score, int index) 
  { 
    if(index < MAX_NUM_PAPERS)
    {
      paperScores[index]=score; 
    }
    else
    {
      cout<<"\nThe index given is over the specified limit for the amount of paper scores available."<<endl;
    }
  }

  // compute and return the student's grade in the course
  // the value will be as a percentage
  double calcGrade();

  // provide a neatly formatted string containing all relevant info
  // about a student
  string createReport();

  // write data about a student to a file in a standard formatted
  void writeData(ostream& outfile);

  // record a student's absence
  void recordAbsence() { numAbsences++; }

  // methods to record new grades for the student
  void recordQuiz(int grade);
  void recordExam(int grade);
  void recordPaper(int grade);

};
