#include "pch.h"
#include "math_lib.h"

TEST(Task, DefaultNumbersInRange) {
    for (int i = 0; i < 100; ++i) {
        Task t;
        EXPECT_GE(t.num_1, 1);
        EXPECT_LE(t.num_1, 10000);
        EXPECT_GE(t.num_2, 1);
        EXPECT_LE(t.num_2, 10000);
    }
}

TEST(Task, DefaultOperationInRange) {
    for (int i = 0; i < 100; ++i) {
        Task t;
        EXPECT_GE(t.operation, 1);
        EXPECT_LE(t.operation, 4);
    }
}

TEST(Task, DefaultAnswerMatchesOperation) {
    for (int i = 0; i < 100; ++i) {
        Task t;
        switch (t.operation) {
        case 1: EXPECT_EQ(t.answer, t.num_1 + t.num_2); break;
        case 2: EXPECT_EQ(t.answer, t.num_1 - t.num_2); break;
        case 3: EXPECT_EQ(t.answer, t.num_1 * t.num_2); break;
        case 4: EXPECT_EQ(t.answer, t.num_1 / t.num_2); break;
        default: FAIL() << "unknown operation: " << (int)t.operation;
        }
    }
}

TEST(Task, RangeRespectsMinMax) {
    for (int i = 0; i < 200; ++i) {
        Task t(5, 10, '+');
        EXPECT_GE(t.num_1, 5);
        EXPECT_LE(t.num_1, 10);
        EXPECT_GE(t.num_2, 5);
        EXPECT_LE(t.num_2, 10);
    }
}

TEST(Task, SingleValueRange) {
    Task t(7, 7, '+');
    EXPECT_EQ(t.num_1, 7);
    EXPECT_EQ(t.num_2, 7);
    EXPECT_EQ(t.answer, 14);
}

TEST(Task, PlusOperation) {
    Task t(3, 8, '+');
    EXPECT_EQ(t.operation, 1);
    EXPECT_EQ(t.answer, t.num_1 + t.num_2);
}

TEST(Task, MinusOperation) {
    Task t(3, 8, '-');
    EXPECT_EQ(t.operation, 2);
    EXPECT_EQ(t.answer, t.num_1 - t.num_2);
}

TEST(Task, MultiplyOperation) {
    Task t(3, 8, '*');
    EXPECT_EQ(t.operation, 3);
    EXPECT_EQ(t.answer, t.num_1 * t.num_2);
}

TEST(Task, DivideOperation) {
    Task t(1, 100, '/');
    EXPECT_EQ(t.operation, 4);
    EXPECT_EQ(t.answer, t.num_1 / t.num_2);
}