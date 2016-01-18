#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/Marvel.cpp"
#include "../7Wonders/DefaultMarvel.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(MarvelDefaultTest)
	{
	public:
		
		TEST_METHOD(DefaultMarvelConstructor)
		{
			DefaultMarvel m;
			Assert::AreEqual(0, m.getMarvelLevel());
			Assert::AreEqual(3, m.getMarvelMaxLevel());
		}

	};
}