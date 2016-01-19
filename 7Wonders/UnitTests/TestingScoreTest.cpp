#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/HumanPlayer.h"
#include "../7Wonders/ComputerPlayer.h"
#include "../7Wonders/World.h"
#include "../7Wonders/Player.h"
#include <string>
#include <regex>
#include <stdio.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(TestingScoreTest)
	{
	public:
		
		TEST_METHOD(TestingScore1)
		{
			World w(3, 2);
			Assert::IsFalse(w.m_gameOver);
		}

		//TOTEST
		/*
		3 GUILDE_DES_TRAVAILLEURS
		3 GUILDE_DES_ARTISANS
		3 GUILDE_DES_COMMERCANTS
		3 GUILDE_DES_PHILOSOPHES
		3 GUILDE_DES_ESPIONS
		3 GUILDE_DES_STRATEGES
		3 GUILDE_DES_ARMATEURS 
		3 GUILDE_DES_SCIENTIFIQUES
		3 GUILDE_DES_MAGISTRATS
		3 GUILDE_DES_BATISSEURS
		Points de merveille
		Points jaunes
		WAR,
		GOLD,
		WONDER_LEVEL,
		BLUE_CARDS,
		YELLOW_CARDS,
		GUILDS,
		*/
	};
}