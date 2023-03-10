// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/game/Game.hpp"
#include <algorithm>

TEST(BoardTest, methods) {
  Board board1 = Board();
  Board board2 = Board(BLACK, true);

  ASSERT_EQ(board1.getTurn(), WHITE);
  ASSERT_EQ(board1.countPiecesByColor(WHITE), 12);
  ASSERT_EQ(board1.countPiecesByColor(BLACK), 12);

  ASSERT_EQ(board2.getTurn(), BLACK);
  ASSERT_EQ(board2.countPiecesByColor(WHITE), 0);
  ASSERT_EQ(board2.countPiecesByColor(BLACK), 0);

  Board board3 = Board(true);
  board3(D, 5) = new Pawn(WHITE);
  board3(E, 6) = new Pawn(BLACK);
  board3(B, 1) = new Pawn(WHITE);
  board3(B, 2) = new Pawn(BLACK);

  EXPECT_EQ(board3.getTurn(), WHITE);
  Board board4 = *board3.clone();

  ASSERT_EQ(board4.countPiecesByColor(WHITE), 2);
  ASSERT_EQ(board4.countPiecesByColor(BLACK), 2);

  EXPECT_EQ(board4.getTurn(), WHITE);
  board4.makeMove(Move("D5F7"));
  EXPECT_EQ(board4.getTurn(), BLACK);
  EXPECT_EQ(board4(D, 5).isEmpty(), true);
  EXPECT_EQ(board4(E, 6).isEmpty(), true);
  EXPECT_EQ(board4(F, 7).isEmpty(), false);
  EXPECT_EQ(board4(B, 1).isEmpty(), false);
  EXPECT_EQ(board4(B, 2).isEmpty(), false);

  EXPECT_EQ(board3.getTurn(), WHITE);
  EXPECT_EQ(board3(D, 5).isEmpty(), false);
  EXPECT_EQ(board3(E, 6).isEmpty(), false);
  EXPECT_EQ(board3(F, 7).isEmpty(), true);
  EXPECT_EQ(board3(B, 1).isEmpty(), false);
  EXPECT_EQ(board3(B, 2).isEmpty(), false);

  Board noGameOverBoard = Board(true);
  noGameOverBoard(D, 5) = new Pawn(WHITE);
  noGameOverBoard(C, 3) = new Pawn(BLACK);
  ASSERT_EQ(noGameOverBoard.isGameOver(), false);
  ASSERT_EQ(noGameOverBoard.getGameResult(), GameResult::gameNotOver());

  Board whiteWinnerBoardNoPieces = Board(WHITE, true);
  whiteWinnerBoardNoPieces(A, 5) = new Pawn(WHITE);
  whiteWinnerBoardNoPieces(B, 6) = new Pawn(BLACK);
  whiteWinnerBoardNoPieces.makeMove(Move("A5C7"));
  ASSERT_EQ(whiteWinnerBoardNoPieces.isGameOver(), true);
  ASSERT_EQ(whiteWinnerBoardNoPieces.getGameResult(),
            GameResult::winner(WHITE));

  Board whiteWinnerBoardBlocked = Board(WHITE, true);
  whiteWinnerBoardNoPieces(C, 6) = new Pawn(WHITE);
  whiteWinnerBoardNoPieces(B, 7) = new Pawn(WHITE);
  whiteWinnerBoardNoPieces(A, 8) = new Pawn(BLACK);
  ASSERT_EQ(whiteWinnerBoardNoPieces.isGameOver(), true);
  ASSERT_EQ(whiteWinnerBoardNoPieces.getGameResult(),
            GameResult::winner(WHITE));

  Board blackWinnerBoardNoPieces = Board(BLACK, true);
  blackWinnerBoardNoPieces(A, 6) = new Pawn(BLACK);
  blackWinnerBoardNoPieces(B, 5) = new Pawn(WHITE);
  blackWinnerBoardNoPieces.makeMove(Move("A6C4"));
  ASSERT_EQ(blackWinnerBoardNoPieces.isGameOver(), true);
  ASSERT_EQ(blackWinnerBoardNoPieces.getGameResult(),
            GameResult::winner(BLACK));

  Board blackWinnerBoardBlocked = Board(BLACK, true);
  blackWinnerBoardNoPieces(C, 3) = new Pawn(BLACK);
  blackWinnerBoardNoPieces(B, 2) = new Pawn(BLACK);
  blackWinnerBoardNoPieces(A, 1) = new Pawn(WHITE);
  ASSERT_EQ(blackWinnerBoardNoPieces.isGameOver(), true);
  ASSERT_EQ(blackWinnerBoardNoPieces.getGameResult(),
            GameResult::winner(BLACK));
}

TEST(BoardTest, reprMethod) {
  Board board1 = Board();
  Board board2 = Board(WHITE, true);
  board2(A, 5) = new Pawn(WHITE);
  board2(B, 5) = new Queen(WHITE);
  Board board3 = Board(BLACK, true);
  board3(A, 5) = new Pawn(BLACK);
  board3(B, 5) = new Queen(BLACK);

  ASSERT_STREQ(
      board1.repr().c_str(),
      ".b.b.b.bb.b.b.b..b.b.b.b................w.w.w.w..w.w.w.ww.w.w.w./W");
  ASSERT_STREQ(
      board2.repr().c_str(),
      "........................wW....................................../W");
  ASSERT_STREQ(
      board3.repr().c_str(),
      "........................bB....................................../B");
}

TEST(BoardTest, madeMoves) {
  std::vector<Move> madeMoves = std::vector<Move>();
  madeMoves.push_back(Move("A1B2"));
  madeMoves.push_back(Move("D5F2"));

  Board board = Board(WHITE, true, madeMoves);
  board(D, 1) = new Pawn(WHITE);
  board(D, 8) = new Pawn(BLACK);
  board.makeMove(Move("D1E2"));
  ASSERT_EQ(board.getMadeMoves().size(), 3);
  ASSERT_EQ(board.getMadeMoves()[0], Move("A1B2"));
  ASSERT_EQ(board.getMadeMoves()[1], Move("D5F2"));
  ASSERT_EQ(board.getMadeMoves()[2], Move("D1E2"));

  Board boardCloned = *board.clone();

  boardCloned.makeMove(Move("D8E7"));
  ASSERT_EQ(boardCloned.getMadeMoves().size(), 4);
  ASSERT_EQ(boardCloned.getMadeMoves()[0], Move("A1B2"));
  ASSERT_EQ(boardCloned.getMadeMoves()[1], Move("D5F2"));
  ASSERT_EQ(boardCloned.getMadeMoves()[2], Move("D1E2"));
  ASSERT_EQ(boardCloned.getMadeMoves()[3], Move("D8E7"));
}

TEST(BoardTest, operators) {
  Board board = Board();

  EXPECT_NO_THROW(board(A, 1));
  EXPECT_NO_THROW(board(H, 8));
  EXPECT_THROW(board(A, 9), std::runtime_error);
  EXPECT_THROW(board(A, 10), std::runtime_error);
  EXPECT_THROW(board(A, 0), std::runtime_error);
  EXPECT_THROW(board(9, 1), std::runtime_error);
  EXPECT_THROW(board(10, 10), std::runtime_error);
  EXPECT_THROW(board(0, 0), std::runtime_error);
}

TEST(BoardTest, representations) {
  Board board = Board();

  ASSERT_EQ(board(A, 1).repr(), 'w');
  ASSERT_EQ(board(B, 1).repr(), ' ');
  ASSERT_EQ(board(G, 7).repr(), 'b');
  ASSERT_EQ(board(H, 7).repr(), ' ');
}

TEST(BoardTest, bounds) {
  Board board = Board();

  ASSERT_EQ(board.checkPositionInBound(A, 1), true);
  ASSERT_EQ(board.checkPositionInBound(B, 1), true);
  ASSERT_EQ(board.checkPositionInBound(G, 7), true);
  ASSERT_EQ(board.checkPositionInBound(H, 7), true);
  ASSERT_EQ(board.checkPositionInBound(E, 8), true);
  ASSERT_EQ(board.checkPositionInBound(F, 8), true);
  ASSERT_EQ(board.checkPositionInBound(H, 8), true);

  ASSERT_EQ(board.checkPositionInBound(A, 0), false);
  ASSERT_EQ(board.checkPositionInBound(A, 9), false);
  ASSERT_EQ(board.checkPositionInBound(9, 2), false);
  ASSERT_EQ(board.checkPositionInBound(9, 9), false);
  ASSERT_EQ(board.checkPositionInBound(10, 0), false);
  ASSERT_EQ(board.checkPositionInBound(10, 10), false);
  ASSERT_EQ(board.checkPositionInBound(0, 0), false);
}

TEST(BoardTest, countPiecesInBoard) {
  Board board = Board();
  ASSERT_EQ(board.countPiecesByColor(WHITE), 12);
  ASSERT_EQ(board.countPiecesByColor(BLACK), 12);

  Board board_2_whites = Board(true);
  board_2_whites(G, 3) = new Pawn(WHITE);
  board_2_whites(H, 5) = new Queen(WHITE);
  ASSERT_EQ(board_2_whites.countPiecesByColor(WHITE), 2);
  ASSERT_EQ(board_2_whites.countPiecesByColor(BLACK), 0);

  Board board_2_blacks = Board(true);
  board_2_blacks(G, 3) = new Pawn(BLACK);
  board_2_blacks(H, 5) = new Queen(BLACK);
  ASSERT_EQ(board_2_blacks.countPiecesByColor(WHITE), 0);
  ASSERT_EQ(board_2_blacks.countPiecesByColor(BLACK), 2);
}

TEST(BoardTest, customBoards) {
  Board board = Board();
  Board customBoard = Board(true);
  customBoard(G, 3) = new Pawn(WHITE);
  customBoard(H, 5) = new Queen(WHITE);
  customBoard(H, 1) = new Queen(BLACK);

  ASSERT_EQ(board.countPiecesByColor(WHITE), 12);
  ASSERT_EQ(board.countPiecesByColor(BLACK), 12);

  ASSERT_EQ(customBoard.countPiecesByColor(WHITE), 2);
  ASSERT_EQ(customBoard.countPiecesByColor(BLACK), 1);
}

TEST(BoardTest, boardMoves) {
  Board board1 = Board();

  std::vector<Move> board1Moves = board1.getMoves();

  ASSERT_EQ(board1Moves.size(), 7);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("A3B4")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("C3B4")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("C3D4")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("E3D4")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("E3F4")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("G3F4")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("G3H4")) !=
                board1Moves.end(),
            true);

  Board board2 = Board(BLACK, true);
  board2(C, 3) = new Queen(BLACK);
  board2(D, 4) = new Pawn(WHITE);

  std::vector<Move> board2Moves = board2.getMoves();

  Move moveCapturedPawn = Move("C3E5");
  moveCapturedPawn.addCapture(PieceLocation{D, 4});

  ASSERT_EQ(board2Moves.size(), 4);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(), Move("C3B4")) !=
                board2Moves.end(),
            true);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(),
                      moveCapturedPawn) != board2Moves.end(),
            true);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(), Move("C3B2")) !=
                board2Moves.end(),
            true);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(), Move("C3D2")) !=
                board2Moves.end(),
            true);
}

TEST(BoardTest, makeIllegalMove) {
  Board board = Board();
  EXPECT_THROW(board.makeMove(Move("G5E4")), std::runtime_error);
  EXPECT_THROW(board.makeMove(Move("H2H3")), std::runtime_error);
  EXPECT_THROW(board.makeMove(Move("G5E4")), std::runtime_error);
  EXPECT_THROW(board.makeMove(Move("B6C4")), std::runtime_error);
}

TEST(BoardTest, makeMovesNoCapture) {
  Board board = Board(true);
  board(D, 4) = new Pawn(WHITE);
  board(A, 4) = new Pawn(BLACK);

  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_NO_THROW(board.makeMove(Move("D4E5")));
  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_EQ(board(D, 4).isEmpty(), true);
  EXPECT_EQ(board(E, 5).isEmpty(), false);
  EXPECT_EQ(board(E, 5).getPiece().getColor(), WHITE);
  EXPECT_EQ(board(E, 5).getPiece().getType(), PieceType::PAWN);

  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_NO_THROW(board.makeMove(Move("A4B3")));
  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_EQ(board(A, 4).isEmpty(), true);
  EXPECT_EQ(board(B, 3).isEmpty(), false);
  EXPECT_EQ(board(B, 3).getPiece().getColor(), BLACK);
  EXPECT_EQ(board(B, 3).getPiece().getType(), PieceType::PAWN);
}

TEST(BoardTest, makeMovesOneCapture) {
  Board board = Board(true);
  board(D, 4) = new Pawn(WHITE);
  board(E, 5) = new Pawn(BLACK);
  board(A, 4) = new Pawn(BLACK);
  board(B, 3) = new Pawn(WHITE);

  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_NO_THROW(board.makeMove(Move("D4F6")));
  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_EQ(board(D, 4).isEmpty(), true);
  EXPECT_EQ(board(E, 5).isEmpty(), true);
  EXPECT_EQ(board(F, 6).isEmpty(), false);
  EXPECT_EQ(board(F, 6).getPiece().getColor(), WHITE);
  EXPECT_EQ(board(F, 6).getPiece().getType(), PieceType::PAWN);

  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_NO_THROW(board.makeMove(Move("A4C2")));
  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_EQ(board(A, 4).isEmpty(), true);
  EXPECT_EQ(board(B, 3).isEmpty(), true);
  EXPECT_EQ(board(C, 2).isEmpty(), false);
  EXPECT_EQ(board(C, 2).getPiece().getColor(), BLACK);
  EXPECT_EQ(board(C, 2).getPiece().getType(), PieceType::PAWN);
}

TEST(BoardTest, makeMoveMultiCaptures) {
  Board board = Board(true);
  board(D, 4) = new Pawn(WHITE);
  board(E, 5) = new Pawn(BLACK);
  board(E, 7) = new Pawn(BLACK);

  board(A, 5) = new Pawn(BLACK);
  board(B, 4) = new Pawn(WHITE);
  board(B, 2) = new Pawn(WHITE);

  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_NO_THROW(board.makeMove(Move("D4D8")));
  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_EQ(board(D, 4).isEmpty(), true);
  EXPECT_EQ(board(E, 5).isEmpty(), true);
  EXPECT_EQ(board(E, 7).isEmpty(), true);
  EXPECT_EQ(board(D, 8).isEmpty(), false);
  EXPECT_EQ(board(D, 8).getPiece().getColor(), WHITE);
  // pawn promotion: WHITE in rank 8
  EXPECT_EQ(board(D, 8).getPiece().getType(), PieceType::QUEEN);

  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_NO_THROW(board.makeMove(Move("A5A1")));
  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_EQ(board(A, 5).isEmpty(), true);
  EXPECT_EQ(board(B, 4).isEmpty(), true);
  EXPECT_EQ(board(B, 2).isEmpty(), true);
  EXPECT_EQ(board(A, 1).isEmpty(), false);
  EXPECT_EQ(board(A, 1).getPiece().getColor(), BLACK);
  // pawn promotion: BLACK in rank 1
  EXPECT_EQ(board(A, 1).getPiece().getType(), PieceType::QUEEN);
}

TEST(BoardTest, makeMovePawnPromotion) {
  Board board = Board(WHITE, true);
  board(D, 7) = new Pawn(WHITE);
  board(B, 2) = new Pawn(BLACK);

  board.makeMove(Move("D7C8"));

  EXPECT_EQ(board(D, 7).isEmpty(), true);
  EXPECT_EQ(board(C, 8).isEmpty(), false);
  EXPECT_EQ(board(C, 8).getPiece().getColor(), WHITE);
  EXPECT_EQ(board(C, 8).getPiece().getType(), PieceType::QUEEN);

  board.makeMove(Move("B2A1"));

  EXPECT_EQ(board(B, 2).isEmpty(), true);
  EXPECT_EQ(board(A, 1).isEmpty(), false);
  EXPECT_EQ(board(A, 1).getPiece().getColor(), BLACK);
  EXPECT_EQ(board(A, 1).getPiece().getType(), PieceType::QUEEN);
}

TEST(BoardTest, threeFoldRepetition) {
  std::vector<Move> madeMoves = std::vector<Move>();
  madeMoves.push_back(Move("D1E2"));
  madeMoves.push_back(Move("A1B2"));
  madeMoves.push_back(Move("D1E2"));
  madeMoves.push_back(Move("D5F2"));
  madeMoves.push_back(Move("D6F3"));

  Board board = Board(WHITE, true, madeMoves);
  board(D, 1) = new Pawn(WHITE);
  board(D, 8) = new Pawn(BLACK);
  board.makeMove(Move("D1E2"));

  ASSERT_EQ(board.getMoves().size(), 0);
  ASSERT_EQ(board.isGameOver(), true);
  ASSERT_EQ(board.getGameResult(), GameResult::threeFoldRepetition());
}
