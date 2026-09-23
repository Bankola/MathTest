#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "../MathLib/math_lib.h"

Task::Task() {
    num_1 = 1 + std::rand() % 10000;
    num_2 = 1 + std::rand() % 10000;
    operation = static_cast<char>(1 + std::rand() % 4);
    calculate_result();
}

Task::Task(int min, int max, char oper) {
    if (max < min) {
        std::swap(min, max);
    }

    num_1 = std::rand() % (max - min + 1) + min;
    num_2 = std::rand() % (max - min + 1) + min;

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
    else {
        operation = static_cast<char>(1 + std::rand() % 4);
    }

   calculate_result();
}

void Task::calculate_result() {
    switch (operation) {
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
        if (num_2 == 0) { 
            num_2 = 1; 
        }
        answer = static_cast<double>(num_1) / num_2;
        break;
    default:
        answer = 0;
        break;
    }
}

void Task::print_question() const noexcept{
    char sign;
    switch (operation) {
    case 1: 
        sign = '+'; 
        break;
    case 2: 
        sign = '-'; 
        break;
    case 3: 
        sign = '*'; 
        break;
    case 4: 
        sign = '/'; 
        break;
    default: 
        sign = '?'; 
        break;
    }
    std::cout << num_1 << " " << sign << " " << num_2 << " = ?";
}

MathTest::MathTest(int questions_count) 
    : MathTest(questions_count, 1, 10000, '\0'){ }

MathTest::MathTest(int questions_count, int min, int max)
: MathTest(questions_count, min, max, '\0'){ }

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

bool MathTest::submit_answer(int index, int user_answer) {
    if (index < 0 || index >= count) {
        return false;
    }

    user_answers[index] = user_answer;

    long expected = std::llround(tasks[index].answer);
    bool ok = (static_cast<long>(user_answer) == expected);

    if (ok) {
        correct_count++;
    }
    return ok;
}

bool MathTest::is_correct(int index) const {
    if (index < 0 || index >= count) {
        return false;
    }
    long expected = std::llround(tasks[index].answer);
    bool ok = (static_cast<long>(user_answers[index]) == expected);
    return ok;
}

char MathTest::calculate_mark() const {
    if (count == 0) return '2';

    double percent = 100.0 * correct_count / count;

    if (percent >= 90.0) return '5';
    if (percent >= 75.0) return '4';
    if (percent >= 60.0) return '3';
    return '2';
}

void MathTest::run() {
    std::cout << "=== Math Test (" << count << " questions) ===\n";

    for (int i = 0; i < count; ++i) {
        std::cout << "\n[" << (i + 1) << "/" << count << "] ";
        tasks[i].print_question();
        std::cout << "\n> ";

        int user_input;
        if (!(std::cin >> user_input)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            user_input = 0;
        }

        submit_answer(i, user_input);
    }

    show_statistics();
}

void MathTest::show_statistics() const {
    std::cout << "\n=== Statistics ===\n";

    for (int i = 0; i < count; ++i) {
        std::cout << (i + 1) << ") ";
        tasks[i].print_question();
        std::cout << "  True: " << static_cast<long>(tasks[i].answer)
            << "  Your: " << user_answers[i]
            << "  [" << (is_correct(i) ? '+' : '-') << "]\n";
    }

    std::cout << "\nTotal Result: " << correct_count << " / " << count
        << " (mark: " << calculate_mark() << ")\n";
}