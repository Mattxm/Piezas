/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};


// Tests that should pass

TEST(PiezasTest, TieCheck)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(2);
	test.dropPiece(2);
	test.dropPiece(0);
	test.dropPiece(0);
	test.dropPiece(2);
	test.dropPiece(0);
	ASSERT_TRUE(test.gameState() == Blank);
}

TEST(PiezasTest, OWinCheck)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(3);
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(1);
	test.dropPiece(0);
	test.dropPiece(0);
	test.dropPiece(2);
	test.dropPiece(0);
	test.dropPiece(2);
	test.dropPiece(2);
	ASSERT_TRUE(test.gameState() == O);
}

TEST(PiezasTest, XWinCheck)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(3);
	test.dropPiece(0);
	test.dropPiece(2);
	test.dropPiece(1);
	test.dropPiece(0);
	test.dropPiece(0);
	test.dropPiece(3);
	test.dropPiece(2);
	test.dropPiece(1);
	test.dropPiece(2);
	ASSERT_TRUE(test.gameState() == X);
}

TEST(PiezasTest, VerticalWinCheck)
{
	Piezas test;
	test.dropPiece(0);
	test.dropPiece(0);
	test.dropPiece(0);
	test.dropPiece(1);
	test.dropPiece(1);
	test.dropPiece(1);
	test.dropPiece(2);
	test.dropPiece(3);
	test.dropPiece(2);
	test.dropPiece(1);
	test.dropPiece(2);
	test.dropPiece(3);
	test.dropPiece(3);
	ASSERT_TRUE(test.gameState() == X);
}

TEST(PiezasTest, FailToPlacePiece)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(3);
	test.dropPiece(3);
	ASSERT_TRUE(test.dropPiece(3) == Blank);
}

TEST(PiezasTest, FailToPlacePieceOOBPositive)
{
	Piezas test;
	ASSERT_TRUE(test.dropPiece(100) == Invalid);
}

TEST(PiezasTest, FailToPlacePieceOOBNegative)
{
	Piezas test;
	ASSERT_TRUE(test.dropPiece(-1) == Invalid);
}

TEST(PiezasTest, PlacePieceCheckX)
{
	Piezas test;
	test.dropPiece(3);
	ASSERT_TRUE(test.pieceAt(0,3) == X);
}

TEST(PiezasTest, PlacePieceCheckO)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(3);
	ASSERT_TRUE(test.pieceAt(1,3) == O);
}

TEST(PiezasTest, PieceAtOOB)
{
	Piezas test;
	ASSERT_TRUE(test.pieceAt(-1,4) == Invalid);
}


TEST(PiezasTest, PlacePieceResetPlaceX)
{
	Piezas test;
	test.dropPiece(3);
	test.reset();
	test.dropPiece(3);
	ASSERT_TRUE(test.pieceAt(0,3) == X);
}

TEST(PiezasTest, GameNotOver)
{
	Piezas test;
	test.dropPiece(1);
	ASSERT_TRUE(test.gameState() == Invalid);
}


// Tests that should fail


TEST(PiezasTest, XFailCheck)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(2);
	test.dropPiece(2);
	ASSERT_TRUE(test.gameState() == X);
}

TEST(PiezasTest, OFailCheck)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(0);
	test.dropPiece(2);
	test.dropPiece(0);
	test.dropPiece(2);
	test.dropPiece(2);
	ASSERT_TRUE(test.gameState() == O);
}

TEST(PiezasTest, TieFailCheck)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(3);
	test.dropPiece(0);
	test.dropPiece(2);
	test.dropPiece(0);
	test.dropPiece(3);
	test.dropPiece(1);
	test.dropPiece(2);
	ASSERT_TRUE(test.gameState() == Blank);
}

TEST(PiezasTest, PlacePieceFail)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(3);
	test.dropPiece(3);
	ASSERT_TRUE(test.dropPiece(3) == X);
}

TEST(PiezasTest, PieceAtFailX)
{
	Piezas test;
	test.dropPiece(3);
	ASSERT_TRUE(test.pieceAt(0,3) == O);
}

TEST(PiezasTest, PieceAtFailO)
{
	Piezas test;
	test.dropPiece(3);
	test.dropPiece(3);
	ASSERT_TRUE(test.pieceAt(1,3) == X);
}

TEST(PiezasTest, PlacePieceResetFail)
{
	Piezas test;
	test.dropPiece(3);
	test.reset();
	test.dropPiece(3);
	ASSERT_TRUE(test.pieceAt(0,3) == O);
}

TEST(PiezasTest, GameOverFail)
{
	Piezas test;
	Piece res = test.gameState();
	ASSERT_TRUE(( res == Blank) || ( res == X) || ( res == O));
}
