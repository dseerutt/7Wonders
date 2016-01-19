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
			Assert::AreEqual(0, m.getMarvelMoney());
			Assert::AreEqual(0, m.getMarvelScore());
			Assert::AreEqual(3, m.getMarvelMaxLevel());
		}

		TEST_METHOD(UpgradeMarvelTest)
		{
			DefaultMarvel m;
			std::vector<std::array<int, RESOURCES_COUNT>> vec;
			std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 1, 0, 0 };
			std::array<int, RESOURCES_COUNT> rec2 = { 1, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec);
			Assert::IsFalse(m.canUpgrade(vec));
			vec.push_back(rec2);
			Assert::IsTrue(m.canUpgrade(vec));
		}

		TEST_METHOD(UpgradeMarvelTest2)
		{
			DefaultMarvel m;
			std::vector<std::array<int, RESOURCES_COUNT>> vec;
			std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 1, 0, 0 };
			std::array<int, RESOURCES_COUNT> rec2 = { 1, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec);
			Assert::IsFalse(m.canUpgrade(vec));
			vec.push_back(rec2);
			Assert::IsTrue(m.canUpgrade(vec));

			m.upgrade(vec);
			Assert::AreEqual(1, m.getMarvelLevel());
			std::array<int, RESOURCES_COUNT> rec3 = { 2, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec3);
			Assert::IsTrue(m.canUpgrade(vec));
			m.upgrade(vec);
			Assert::AreEqual(2, m.getMarvelLevel());
		}

		TEST_METHOD(UpgradeMarvelTest3)
		{
			DefaultMarvel m;
			std::vector<std::array<int, RESOURCES_COUNT>> vec;
			std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 1, 0, 0 };
			std::array<int, RESOURCES_COUNT> rec2 = { 1, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec);
			Assert::IsFalse(m.canUpgrade(vec));
			vec.push_back(rec2);
			Assert::IsTrue(m.canUpgrade(vec));

			m.upgrade(vec);
			Assert::AreEqual(1, m.getMarvelLevel());
			std::array<int, RESOURCES_COUNT> rec3 = { 2, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec3);
			Assert::IsTrue(m.canUpgrade(vec));

			m.upgrade(vec);
			Assert::AreEqual(2, m.getMarvelLevel());
			std::array<int, RESOURCES_COUNT> rec4 = { 3, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec4);
			Assert::IsTrue(m.canUpgrade(vec));
			m.upgrade(vec);
			Assert::AreEqual(3, m.getMarvelLevel());
		}

		TEST_METHOD(UpgradeMarvelTest4)
		{
			DefaultMarvel m;
			std::vector<std::array<int, RESOURCES_COUNT>> vec;
			std::array<int, RESOURCES_COUNT> rec = { 0, 0, 0, 0, 1, 0, 0 };
			std::array<int, RESOURCES_COUNT> rec2 = { 1, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec);
			Assert::IsFalse(m.canUpgrade(vec));
			vec.push_back(rec2);
			Assert::IsTrue(m.canUpgrade(vec));

			m.upgrade(vec);
			Assert::AreEqual(1, m.getMarvelLevel());
			std::array<int, RESOURCES_COUNT> rec3 = { 2, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec3);
			Assert::IsTrue(m.canUpgrade(vec));

			m.upgrade(vec);
			Assert::AreEqual(2, m.getMarvelLevel());
			std::array<int, RESOURCES_COUNT> rec4 = { 3, 0, 0, 0, 1, 0, 0 };
			vec.push_back(rec4);
			Assert::IsTrue(m.canUpgrade(vec));
			m.upgrade(vec);
			Assert::AreEqual(3, m.getMarvelLevel());

			Assert::IsFalse(m.canUpgrade(vec));
		}

	};
}