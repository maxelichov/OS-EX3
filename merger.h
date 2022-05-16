





#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#define MAX_ROW_SIZE 80
#define STDOUT 1



typedef struct Student {
	char name[10];
	float average;
	int numOfGrades;
	int grades[10];	
}student;


typedef struct ListNode {
	struct ListNode* next;
	student* stdnt;
}listNode;

typedef struct StudentsList {
	listNode*	head;	
	listNode*	tail;
	listNode* next;
}studentsList;



void sigpipe_handler(int dummy);
void customize_writing(char* file_to_write);
void insert_to_tail(studentsList* studentsList, listNode* stdntNode);
void sort_grades(studentsList* student_list);
int read_and_write(char* inputFile, studentsList* SudentsList);
void free_list(studentsList* SudentsList);
void write_to_file(char* inputFile, studentsList* SudentsList);
void print_all_avg(studentsList* studList);
void report_input_file(const char* file_name, int num_stud);
void report_data_summary(int num_stud, double avg);
int cmpfunc (const void * a, const void * b);
void calc_avg(studentsList* StudentsList);
void print_list(studentsList* studentList);
studentsList* init_list();
student*  get_student(char* studentName, studentsList* list );
int is_student_exist(char* studentName, studentsList* list );
student* add_to_list(studentsList* StudentsList, char* studentName) ;
void add_grade(int gradesArr[], int gardeToAdd, int index);
int handle_row(char* buffer, studentsList* stdntList);
int handle_file(char* fileName, studentsList* studentsList);
