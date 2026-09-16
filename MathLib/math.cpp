#include <random>
#include <iostream>
#include <ctime>
#include "../MathLib/math_lib.h"

Task::Task() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	num_1 = 1 + std::rand() % 10000;   
	num_2 = 1 + std::rand() % 10000;   
	operation = 1 + std::rand() % 4;  
	Result(operation);
}

Task::Task(int min, int max, char oper) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	num_1 = std::rand() % (max - min + 1) + min;   
	num_2 = std::rand() % (max - min + 1) + min;   

	if (oper == '*')      operation = 3;
	else if (oper == '+') operation = 1;
	else if (oper == '-') operation = 2;
	else if (oper == '/') operation = 4;
	else                  operation = 1 + std::rand() % 4; 

	Result(operation);
}

void Task::Result(char oper) {
	switch (oper) {
	case 1:
		answer = num_1 + num_2;
		break;
	case 2:
		answer = num_1 - num_2;
		break;
	case 3:
		answer = num_1 * num_2;
		break;
	case 4:
		answer = num_1 / num_2;
		break;
	}
}

void Task::print_question() const {
	char sign;
	switch (operation) {
	case 1: sign = '+'; break;
	case 2: sign = '-'; break;
	case 3: sign = '*'; break;
	case 4: sign = '/'; break;
	default: sign = '?'; break;
	}
	std::cout << num_1 << " " << sign << " " << num_2 << " = ?";
}

MathTest::MathTest(int questions_count) {
	if (questions_count < 1) {
		questions_count = 1;
	}

	count = questions_count;
	correct_count = 0;

	tasks = new Task[count];
	user_answers = new int[count];
	for (int i = 0; i < count; i++) {
		user_answers[i] = 0;
	}
}

MathTest::MathTest(int questions_count, int min, int max) {
	if (questions_count < 1) questions_count = 1;
	if (max < min) std::swap(min, max);

	count = questions_count;
	correct_count = 0;

	tasks = new Task[count];
	user_answers = new int[count]();

	for (int i = 0; i < count; ++i) {
		tasks[i] = Task(min, max, '\0');  
	}
}

MathTest::MathTest(int questions_count, int min, int max, char oper) {
	if (questions_count < 1) questions_count = 1;
	if (max < min) std::swap(min, max);

	count = questions_count;
	correct_count = 0;

	tasks = new Task[count];
	user_answers = new int[count]();

	for (int i = 0; i < count; ++i) {
		tasks[i] = Task(min, max, oper);   
	}
}

MathTest::~MathTest() {
	delete[] tasks;
	delete[] user_answers;
}