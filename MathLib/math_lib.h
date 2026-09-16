#pragma once

struct Task {
	int num_1;
	int num_2;
	char operation;
	double answer;

	Task();
	Task(int min, int max, char oper = '\0');
	void Result(char oper);

	void print_question() const;
};

class MathTest {
private:
	Task* tasks;
	int count;
	int* user_answers;
	int correct_count;
public:
	MathTest(int questions_count);
	MathTest(int questions_count, int min, int max);
	MathTest(int questions_count, int min, int max, char oper);
	~MathTest();
};

