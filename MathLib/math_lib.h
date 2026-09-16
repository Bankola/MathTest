#pragma once

struct Task {
	int num_1;
	int num_2;
	char operation;
	double answer;

	Task();
	Task(int min, int max, char oper = '\0');
	void Result(char oper);
};

class MathTest;