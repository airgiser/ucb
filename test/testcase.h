/*!
 * Copyright (c) airfox 2012
 *
 * \brief a simple test framework.
 */

#ifndef UCB_TEST_CASE_H
#define UCB_TEST_CASE_H

#include "test.h"
#include <string>

namespace ucb
{

using std::string;

/*
 * Test Case.
 */
class TestCase : public Test
{
public:
    TestCase(TestResult *testResult = NULL);
    virtual ~TestCase();

    void Run();
    int GetTestCaseCount() const;
    string ToString() const;
protected:
    TestCase(const TestCase &other);
    TestCase& operator=(const TestCase &other);

    virtual void DoTest() = 0;

    void AssertImp(bool condition, const string &Expression,
        string fileName, long lineNumber);
private:
    TestResult *m_testResult;
};

// Macro Assert
#define Assert(condition) \
    (this->AssertImp((condition), (#condition), \
                     __FILE__, __LINE__))
} // namespace ucb

#endif// UCB_TEST_CASE_H
