#pragma once

struct Task {
    int    num_1;
    int    num_2;
    char   operation;   // 1:'+', 2:'-', 3:'*', 4:'/' уточнение при проверке
    double answer;

    Task();
    Task(int min, int max, char oper = '\0');
    void Result(char oper);

    void print_question() const;
};

class MathTest {
private:
    Task* tasks;
    int   count;
    int* user_answers;
    int   correct_count;

public:
    MathTest(int questions_count);
    MathTest(int questions_count, int min, int max);
    MathTest(int questions_count, int min, int max, char oper);
    ~MathTest();

    void run();
    void show_statistics() const;

    bool submit_answer(int index, int user_answer);
    bool is_correct(int index) const;
    char calculate_mark() const;

    int get_current_count() const { return correct_count; }
};

