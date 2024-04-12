// Implementation of the Student class
// By Mary Elaine Califf
// Edited by Jackson Clark
// 3/13/19

#include "Student.h"
#include <iomanip>

Student::Student(string id, string fName, string lName)
{
  studentID = id;
  firstName = fName;
  lastName = lName;
  numAbsences = 0;
  numExamGrades = 0;
  numQuizGrades = 0;
  numPaperGrades = 0;
}

Student::Student(istream &infile)
{
  int quizzesDiff = 0;
  int papersDiff = 0;
  int examsDiff = 0;
  string junk;
  // infile should be open and ready to read the getStudentID
  getline(infile, studentID);
  getline(infile, lastName);
  getline(infile, firstName);
  infile >> numAbsences;
  infile >> numQuizGrades;
  if(numQuizGrades > MAX_NUM_QUIZZES)
  {
    quizzesDiff = numQuizGrades - MAX_NUM_QUIZZES;
    numQuizGrades = MAX_NUM_QUIZZES;
    cout<<"\nThe number of quizzes you requested for " << firstName <<" "<< lastName <<" "<< "(ID: " << studentID << ") is over the specified limit. Quizzes past the maximum number allowed have not been added in the list of scores for the student."<<endl;
  }
  for (int i = 0; i < numQuizGrades; i++)
  {
    infile >> quizScores[i];
  }
  if(quizzesDiff > 0)
  {
    for (int i = 0; i < quizzesDiff; i++)
    {
      infile >> junk;
    }
  }
  infile >> numPaperGrades;
  if(numPaperGrades > MAX_NUM_PAPERS)
  {
    papersDiff = numPaperGrades - MAX_NUM_PAPERS;
    numPaperGrades = MAX_NUM_PAPERS;
    cout<<"\nThe number of papers you requested for " << firstName <<" "<< lastName << " " << "(ID: " << studentID << ") is over the specified limit. Papers past the maximum number allowed have not been added in the list of scores for the student."<<endl;
  }
  for (int i = 0; i < numPaperGrades; i++)
  {
    infile >> paperScores[i];
  }
  if(papersDiff > 0)
  {
    for (int i = 0; i < papersDiff; i++)
    {
      infile >> junk;
    }
  }
  infile >> numExamGrades;
  if(numExamGrades > MAX_NUM_EXAMS)
  {
    examsDiff = numExamGrades - MAX_NUM_EXAMS;
    numExamGrades = MAX_NUM_EXAMS;
    cout<<"\nThe number of exams you requested for " << firstName <<" "<< lastName << " " << "(ID: " << studentID << ") is over the specified limit. Exams past the maximum number allowed have not been added in the list of scores for the student."<<endl;
  }
  for (int i = 0; i < numExamGrades; i++)
  {
    infile >> examScores[i];
  }
  if(examsDiff > 0)
  {
    for (int i = 0; i < examsDiff; i++)
    {
      infile >> junk;
    }
  }
  getline(infile, junk); // toss the newline after the last exam score
}

// compute and return the student's grade in the course
double Student::calcGrade()
{
  int totalQuizPoints = 0;
  int totalPaperPoints = 0;
  int totalExamPoints = 0;
  double quizGrade = 0.0;
  double examGrade = 0.0;
  double paperGrade = 0.0;

  // get the student's totals
  for (int i = 0; i < numQuizGrades; i++)
  {
    totalQuizPoints += quizScores[i];
  }
  for (int i = 0; i < numExamGrades; i++)
  {
    totalExamPoints += examScores[i];
  }
  for (int i = 0; i < numPaperGrades; i++)
  {
    totalPaperPoints += paperScores[i];
  }

  if (numQuizGrades > 0)
    quizGrade = QUIZ_WEIGHT * totalQuizPoints / (numQuizGrades * MAX_QUIZ_POINTS);
  if (numExamGrades > 0)
    examGrade = EXAM_WEIGHT * totalExamPoints / (numExamGrades * MAX_EXAM_POINTS);
  if (numPaperGrades > 0)
    paperGrade = PAPER_WEIGHT * totalPaperPoints / (numPaperGrades * MAX_PAPER_POINTS);

  return quizGrade + examGrade + paperGrade;
}

// provide a neatly formatted string containing all relevant info
// about a student
string Student::createReport()
{
  std::stringstream report;
  report << studentID << "\t" << firstName << " " << lastName << "\n";
  report << "Current overall grade: " << setprecision(3) << this->calcGrade() * 100 << "%\n";
  report << "Absences: " << numAbsences << "\n";
  report << "Exam scores: ";
  for (int i = 0; i < numExamGrades; i++)
  {
    report << examScores[i] << " ";
  }
  report << "\nPaper scores: ";
  for (int i = 0; i < numPaperGrades; i++)
  {
    report << paperScores[i] << " ";
  }
  report << "\nQuiz Scores:\n";
  for (int i = 0; i < numQuizGrades; i++)
  {
    report << quizScores[i] << " ";
    if (i % 10 == 0)
      report << "\n";
  }
  report << "\n";
  return report.str();
}

// write data about a student to a file in a standard formatted
void Student::writeData(ostream &outfile)
{
  // outtfile should be open and ready to write this student
  outfile << studentID << "\n";
  outfile << lastName << "\n";
  outfile << firstName << "\n";
  outfile << numAbsences << "\n";
  outfile << numQuizGrades << "\n";
  for (int i = 0; i < numQuizGrades; i++)
  {
    outfile << quizScores[i] << "\n";
  }
  outfile << numPaperGrades << "\n";
  for (int i = 0; i < numPaperGrades; i++)
  {
    outfile << paperScores[i] << "\n";
  }
  outfile << numExamGrades << "\n";
  for (int i = 0; i < numExamGrades; i++)
  {
    outfile << examScores[i] << "\n";
  }
}

void Student::recordQuiz(int grade)
{
  if(numQuizGrades + 1 < MAX_NUM_QUIZZES)
  {
    quizScores[numQuizGrades++] = grade;
  }
  else
  {
    cout<<"\nYou have reached the limit for the number of quizzes allowed."<<endl;
  }
}

void Student::recordExam(int grade)
{
  if(numExamGrades + 1 < MAX_NUM_EXAMS)
  {
    examScores[numExamGrades++] = grade;
  }
  else
  {
    cout<<"\nYou have reached the limit for the number of exams allowed."<<endl;
  }
}

void Student::recordPaper(int grade)
{
  if(numPaperGrades + 1 < MAX_NUM_PAPERS)
  {
    paperScores[numPaperGrades++] = grade;
  }
  else
  {
    cout<<"\nYou have reached the limit for the number of papers allowed."<<endl;
  }
}
