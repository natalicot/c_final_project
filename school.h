#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>



typedef struct grades_item {
	int grade;
	int id_test;
	struct grades_item* next;
}grades_t, *p_grades_t;

typedef struct student_item {
	char *name;
	int id;
	p_grades_t head_grades;
	struct student_item* next;

}student_t,*p_student_t;

typedef struct class_item {
	int class_code;
	p_student_t head_student;
	

}class_t,*p_class_t;

p_class_t init_class( int *num_of_clases);
void add_student(p_class_t class, int id, char name[]);
void add_grade(p_student_t student, int id_test, int grade);
int print_students(p_class_t class);
int print_students_grades(p_student_t student);
void delete_student(p_class_t class, int id);
void delete_grade(p_student_t student, int test_id);
void delete_all_grades(p_student_t student);
void delete_all_students(p_class_t class);
void delete_school(p_class_t all_clases, int num_of_clases);
void save_data(p_class_t clases, int num_of_clases);
p_class_t load_data(int* num_of_clases);


