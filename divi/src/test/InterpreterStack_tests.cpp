#include <gmock/gmock.h>
#include <script/InterpreterStack.h>
#include <test_only.h>

BOOST_AUTO_TEST_SUITE(InterpreterStackTests)

BOOST_AUTO_TEST_CASE(StackIsByDefaultEmpty)
{
    RandomAccessStack stack;
    EXPECT_TRUE(stack.empty());
}

BOOST_AUTO_TEST_CASE(WillNotThrowExceptionTryingToRemoveFromAnEmptyStack)
{
    RandomAccessStack stack;
    EXPECT_NO_THROW(stack.pop());
}

BOOST_AUTO_TEST_CASE(WillNotThrowExceptionTryingToReadFromAnEmptyStack)
{
    RandomAccessStack stack;
    EXPECT_NO_THROW(stack.top());
}

StackElement createRandomElement(std::string suffix = std::string(""))
{
    std::string values = std::string("abc")+suffix;
    StackElement stackElement(values.begin(), values.end());
    return stackElement;
}
unsigned getRandomUInt(unsigned minimum = 10, unsigned maximum = 100)
{
    return minimum;
}

BOOST_AUTO_TEST_CASE(WillPushElementToTop)
{
    RandomAccessStack stack;
    StackElement stackElement = createRandomElement();
    stack.push(stackElement);
    EXPECT_TRUE(stackElement==stack.top());
}

BOOST_AUTO_TEST_CASE(WillHaveSizeEqualToNumberOfPushes)
{
    unsigned pushCount = getRandomUInt();
    RandomAccessStack stack;
    for(unsigned pushIndex = 0; pushIndex < pushCount; ++pushIndex)
    {
        StackElement stackElement = createRandomElement();
        stack.push(stackElement);
    }
    EXPECT_EQ(stack.size(), pushCount);
}

BOOST_AUTO_TEST_CASE(WillNotThrowWhenAccessingDeeperThanAvailableOnStack)
{
    RandomAccessStack stack;
    StackElement stackElement = createRandomElement();
    stack.push(stackElement);
    EXPECT_NO_THROW(stack.top(stack.size()+1));
}

#define EXPECT_VECTOR_EQ(x, y) EXPECT_TRUE(std::equal(x.begin(),x.end(),y.begin()) && std::equal(y.begin(),y.end(),x.begin()))

BOOST_AUTO_TEST_CASE(WillModifyReferenceDuringPush)
{
    unsigned pushCount = getRandomUInt();
    RandomAccessStack stack;
    const BasicStack& internalStack = stack.getStack();
    for(unsigned pushIndex = 0; pushIndex < pushCount; ++pushIndex)
    {
        StackElement stackElement = createRandomElement();
        stack.push(stackElement);
    }
    EXPECT_VECTOR_EQ(internalStack, stack.getStack());
}

BOOST_AUTO_TEST_SUITE_END()
