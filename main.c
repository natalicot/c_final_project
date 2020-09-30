
#include"school.h"
#include <Windows.h>

typedef struct menu_item {
	int num;
	char* str;
}menu_t,*p_menu_t;

menu_t menu_arr[11] = {
	
	{1, "add student"},
	{2, "add grade"},
	{3, "delete student"},
	{4, "delete grade"},
	{5, "print students grades"},
	{6, "print class students"},
	{7, "save data"},
	{8, "exit"},
	{0, NULL}
};

void print_menu(p_menu_t menu);
int choose_class(p_class_t clases, int num_of_clases);
p_student_t get_student_by_id(p_class_t class, int id_stud);
void main_loop(p_class_t all_clases,int num_of_clases);
int is_load_data();
void free_all(p_class_t* all_clases,int num_of_clases);


int main() {

	int num_of_clases=0,flag=1;
	p_class_t all_clases=NULL;

	if (is_load_data()==1) {
		all_clases = load_data(&num_of_clases);
		if (!all_clases)
			return 0;
		system("pause");
	}
	else {
		while (flag) {
			all_clases = init_class( &num_of_clases);
			if (all_clases)
				flag = 0;
		}
		
	}
	main_loop(all_clases,num_of_clases);

	delete_school(all_clases,num_of_clases);


	return 0;
}

void print_menu(p_menu_t menu) {
	system("cls");
	printf("*******  menu *******\n");
	while (menu->str) {
		printf("\t %d \t %s \n", menu->num, menu->str);
		menu++;
	}
}

int choose_class(p_class_t clases,int num_of_clases) {
	int choice;
	system("cls");
	if (!clases) {
		printf("no clases to show");
		return;
	}
	printf("\nwitch class would you like to work with? :\n\n");
	for (int i = 0; i < num_of_clases; i++) {
		printf("* pres %d for class id: %d\n", i + 1, clases[i]);
	}
	printf("\nyour answer: ");
	scanf("%d", &choice);
	if (choice<1 || choice>num_of_clases) {
		printf("\n****ERROR****\nthe class doesnt exists. try again.\n");
		return -1;
	}
	return choice-1;
}

p_student_t get_student_by_id(p_class_t class,int id_stud) {
	int flag = 0;
	p_student_t choice=NULL;
	p_student_t temp = class->head_student;

	
	while(temp) {
		if (temp->id == id_stud) {
			choice = temp;
			flag = 1;
		}
		temp = temp->next;
	}
	if (!flag) {
		printf("\tthere is no student with this id. try again.\n");
		
	}
	return choice;
}

void main_loop(p_class_t all_clases,int num_of_clases) {
	int choice=0,id_stud,test_id, grade ;
	char name[20];
	p_student_t student = NULL;

	while (1) {
		print_menu(menu_arr);
		printf("\nplease enter what to do : \n");
		scanf("%d", &choice);
		_getchar_nolock();
		switch (choice) {
		case 1:

			choice = choose_class(all_clases, num_of_clases);
			if (choice == -1)
				break;
			printf("\n\teneter new students name: ");
			scanf("%s", &name);
			_getchar_nolock();
			printf("\teneter new students id: ");
			scanf("%d", &id_stud);
			_getchar_nolock();
			add_student((all_clases + choice), id_stud, name);
			break;
		case 2:
			choice = choose_class(all_clases, num_of_clases);
			if (choice == -1)
				break;
			if (!print_students(&(all_clases[choice])))
				break;
			printf("\t\nenter the id of your chosen student: ");
			scanf("%d", &id_stud);
			student = get_student_by_id(&(all_clases[choice]), id_stud);
			if (!student)
				break;
			printf("\t\t\nenter test id: ");
			scanf("%d", &test_id);
			printf("\t\tenter grade: ");
			scanf("%d", &grade);
			add_grade(student, test_id, grade);

			break;
		case 3:
			choice = choose_class(all_clases, num_of_clases);
			if (choice == -1)
				break;
			if (!print_students(&(all_clases[choice])))
				break;
			printf("enter student id: \n");
			scanf("%d", &id_stud);
			delete_student(&(all_clases[choice]), id_stud);
			break;
		case 4:
			choice = choose_class(all_clases, num_of_clases);
			if (choice == -1)
				break;
			if (!print_students(&(all_clases[choice])))
				break;
			printf("enter student id: \n");
			scanf("%d", &id_stud);
			student = get_student_by_id(&(all_clases[choice]), id_stud);
			if (!student)
				break;
			if(!print_students_grades(student))
				break;
			printf("enter test id to delete: \n");
			scanf("%d", &test_id);
			delete_grade(student, test_id);
			break;
		case 5:
			choice = choose_class(all_clases, num_of_clases);
			if (choice == -1)
				break;
			if (!print_students(&(all_clases[choice])))
				break;
			printf("enter student id: \n");
			scanf("%d", &id_stud);
			student = get_student_by_id(&(all_clases[choice]), id_stud);
			if (!student)
				break;
			print_students_grades(student);
			break;
		case 6:
			choice = choose_class(all_clases, num_of_clases);
			if (choice == -1)
				break;
			print_students(&(all_clases[choice]));
			break;
		case 7:
			save_data(all_clases, num_of_clases);
			break;
		case 8:
			return 0;
			break;
		default:
			printf("something went wrong try again\n");

		}
		printf("\n\n");
		system("pause");
	}
}

int is_load_data() {
	char answear;
	p_class_t all_clases = NULL;

	printf("hello! would you like to load old data? (y\\n)");
	scanf("%c", &answear);

	if (answear == 'y' || answear == 'Y') {
		return 1;
	}
	return 0;
}

void free_all(p_class_t* all_clases,int num_of_clases) {
	
	for (int i = 0; i < num_of_clases; i++) {
		delete_all_students(*(all_clases+i));
		free(*(all_clases+i));
	}
}
