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
    EXPECT_DOUBLE_EQ(t.answer, static_cast<double>(t.num_1) / t.num_2);
}

TEST(MathTest, ZeroQuestionsClampedToOne) {
    MathTest mt(0);
    EXPECT_FALSE(mt.submit_answer(1, 0));
}

TEST(MathTest, NegativeQuestionsClampedToOne) {
    MathTest mt(-5);
    EXPECT_FALSE(mt.submit_answer(1, 0));
}

TEST(MathTest, InitialCountIsZero) {
    MathTest mt(5);
    EXPECT_EQ(mt.get_current_count(), 0);
}

TEST(MathTest, SubmitOutOfRangeNegative) {
    MathTest mt(2, 1, 10, '+');
    EXPECT_FALSE(mt.submit_answer(-1, 5));
}

TEST(MathTest, SubmitOutOfRangeTooBig) {
    MathTest mt(2, 1, 10, '+');
    EXPECT_FALSE(mt.submit_answer(2, 5));
}

TEST(MathTest, SubmitOutOfRangeDoesNotCount) {
    MathTest mt(3, 1, 10, '+');
    mt.submit_answer(-1, 5);
    mt.submit_answer(99, 5);
    EXPECT_EQ(mt.get_current_count(), 0);
}

TEST(MathTest, SubmitAndIsCorrectConsistentTrue) {
    MathTest mt(1, 2, 2, '+');  
    bool ok = mt.submit_answer(0, 4);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(mt.is_correct(0));
}

TEST(MathTest, SubmitAndIsCorrectConsistentFalse) {
    MathTest mt(1, 2, 2, '+');
    bool ok = mt.submit_answer(0, 999);
    EXPECT_FALSE(ok);
    EXPECT_FALSE(mt.is_correct(0));
}

TEST(MathTest, IsCorrectOutOfRange) {
    MathTest mt(2, 1, 10, '+');
    EXPECT_FALSE(mt.is_correct(-1));
    EXPECT_FALSE(mt.is_correct(2));
}

TEST(MathTest, CorrectCountIncrements) {
    MathTest mt(3, 2, 2, '+');   
    EXPECT_EQ(mt.get_current_count(), 0);
    mt.submit_answer(0, 4);
    EXPECT_EQ(mt.get_current_count(), 1);
    mt.submit_answer(1, 4);
    EXPECT_EQ(mt.get_current_count(), 2);
    mt.submit_answer(2, 4);
    EXPECT_EQ(mt.get_current_count(), 3);
}

TEST(MathTest, MarkAllCorrect) {
    MathTest mt(10, 2, 2, '+');
    for (int i = 0; i < 10; ++i) mt.submit_answer(i, 4);
    EXPECT_EQ(mt.calculate_mark(), '5'); 
}

TEST(MathTest, Mark90Percent) {
    MathTest mt(10, 2, 2, '+');
    for (int i = 0; i < 9; ++i) mt.submit_answer(i, 4);
    EXPECT_EQ(mt.calculate_mark(), '5');
}

TEST(MathTest, Mark75Percent) {
    MathTest mt(4, 2, 2, '+');
    for (int i = 0; i < 3; ++i) mt.submit_answer(i, 4);   
    EXPECT_EQ(mt.calculate_mark(), '4');
}

TEST(MathTest, Mark60Percent) {
    MathTest mt(5, 2, 2, '+');
    for (int i = 0; i < 3; ++i) mt.submit_answer(i, 4);  
    EXPECT_EQ(mt.calculate_mark(), '3');
}

TEST(MathTest, MarkBelow60) {
    MathTest mt(10, 2, 2, '+');
    for (int i = 0; i < 5; ++i) mt.submit_answer(i, 4);  
    EXPECT_EQ(mt.calculate_mark(), '2');
}

TEST(MathTest, MarkZero) {
    MathTest mt(5, 2, 2, '+');
    EXPECT_EQ(mt.calculate_mark(), '2');   
}

TEST(MathTest, AdditionCorrect) {
    MathTest mt(5, 5, 10, '+');
    for (int i = 0; i < 5; ++i) {
        const Task& t = mt.get_task(i);
        int expected = t.num_1 + t.num_2;
        EXPECT_TRUE(mt.submit_answer(i, expected));
        EXPECT_TRUE(mt.is_correct(i));
    }
    EXPECT_EQ(mt.get_current_count(), 5);
    EXPECT_EQ(mt.calculate_mark(), '5');
}

TEST(MathTest, MultiplicationCorrect) {
    MathTest mt(5, 5, 10, '*');
    for (int i = 0; i < 5; ++i) {
        const Task& t = mt.get_task(i);
        int expected = t.num_1 * t.num_2;
        EXPECT_TRUE(mt.submit_answer(i, expected));
        EXPECT_TRUE(mt.is_correct(i));
    }
    EXPECT_EQ(mt.get_current_count(), 5);
}

TEST(MathTest, SubtractionCorrect) {
    MathTest mt(5, 5, 10, '-');
    for (int i = 0; i < 5; ++i) {
        const Task& t = mt.get_task(i);
        int expected = t.num_1 - t.num_2;
        EXPECT_TRUE(mt.submit_answer(i, expected));
        EXPECT_TRUE(mt.is_correct(i));
    }
    EXPECT_EQ(mt.get_current_count(), 5);
}

TEST(MathTest, DivisionCorrect) {
    MathTest mt(5, 5, 10, '/');
    for (int i = 0; i < 5; ++i) {
        const Task& t = mt.get_task(i);
        int expected = static_cast<int>(std::llround(t.answer));
        EXPECT_TRUE(mt.submit_answer(i, expected));
        EXPECT_TRUE(mt.is_correct(i));
    }
    EXPECT_EQ(mt.get_current_count(), 5);
}