#include <random>
#include <iostream>
#include <ctime>
#include "../MathLib/math.h"

Task::Task() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int num_1 = 1 + std::rand() % 10000; 
	int num_2 = 1 + std::rand() % 10000;
	char operation = 1 + std::rand() % 4; 

	Result(operation);
}

Task::Task(int min, int max, char oper) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int num_1 = std::rand() % (max - min + 1) + min;
	int num_2 = std::rand() % (max - min + 1) + min;

	if (oper != '\0') {
		if (oper == '*') {
			operation = 3;
		}
		else if (oper == '+') {
			operation = 1;
		}
		else if (oper == '-') {
			operation = 2;
		}
		else if (oper == '/') {
			operation = 4;
		}
	}
	else {
		char operation = 1 + std::rand() % 4;
	}

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