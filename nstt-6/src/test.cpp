#include "main.hpp"

#include "gtest/gtest.h"
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>

std::string MatrixToString(const SquareMatrix& mtr) {
  std::ostringstream result;
  for (int i = 0; i < mtr.getSize(); i++) {
    for (int j = 0; j < mtr.getSize(); j++) {
      result << mtr[i][j] << " ";
    }
    if (i != mtr.getSize() - 1) {
      result << "\n";
    }
  }
  return result.str();
}

TEST(SquareMatrix, ConstructorAndBaseAccess) {
  SquareMatrix mtr(3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtr[i][i] = 1.0;
    }
  }

  EXPECT_EQ(mtr.getSize(), 3);
  EXPECT_EQ(mtr[1][1], 1.0);
}

TEST(SquareMatrix, VectorConstructor) {
  std::vector<double> vect{1.0, 2.0, 3.0};
  SquareMatrix mtr(vect);


  EXPECT_EQ(mtr.getSize(), vect.size());
  EXPECT_EQ(mtr[1][0], 0.0);
  EXPECT_EQ(mtr[0][0], vect[0]);
}

TEST(SquareMatrix, CopyConstructor) {
  std::vector<double> vect{1.0, 2.0, 3.0};
  SquareMatrix mtr(vect);

  SquareMatrix copy(mtr);


  EXPECT_EQ(mtr.getSize(), copy.getSize());
  EXPECT_EQ(mtr[1][0], copy[1][0]);
  EXPECT_EQ(mtr[0][0], copy[0][0]);
}

TEST(SquareMatrix, CopyOperator) {
  std::vector<double> vect{1.0, 2.0, 3.0};
  SquareMatrix mtr(vect);

  SquareMatrix copy(3);
  copy = mtr;


  EXPECT_EQ(mtr.getSize(), copy.getSize());
  EXPECT_EQ(mtr[1][0], copy[1][0]);
  EXPECT_EQ(mtr[0][0], copy[0][0]);
}

TEST(SquareMatrix, MoveConstructor) {
  std::vector<double> vect{1.0, 2.0, 3.0};
  SquareMatrix mtr(vect);

  SquareMatrix moved(std::move(mtr));


  EXPECT_EQ(moved.getSize(), vect.size());
  EXPECT_EQ(moved[1][0], 0.0);
  EXPECT_EQ(moved[0][0], vect[0]);
  EXPECT_EQ(mtr.getSize(), 0);
}

TEST(SquareMatrix, MoveOperator) {
  std::vector<double> vect{1.0, 2.0, 3.0};
  SquareMatrix mtr(vect);

  SquareMatrix moved(3);
  moved = std::move(mtr);


  EXPECT_EQ(moved.getSize(), vect.size());
  EXPECT_EQ(moved[1][0], 0.0);
  EXPECT_EQ(moved[0][0], vect[0]);
  EXPECT_EQ(mtr.getSize(), 0);
}

TEST(SquareMatrix, AdditionOperator) {
  SquareMatrix mtr1(3);
  SquareMatrix mtr2(3);
  SquareMatrix res(3);

  // 0 1 2
  // 3 4 5
  // 6 7 8
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtr1[i][j] = (double) (i * 3 + j);
    }
  }

  // 0 1 2
  // 0 1 2
  // 0 1 2
  for (double i = 0; i < 3; i++) {
    for (double j = 0; j < 3; j++) {
      mtr2[i][j] = j;
    }
  }

  res = mtr1 + mtr2;


  //std::cout << MatrixToString(mtr1) << std::endl;
  EXPECT_EQ(mtr1[1][1], 4.0);
  EXPECT_EQ(mtr2[1][1], 1.0);
  EXPECT_EQ(res[1][1], 5.0);

  EXPECT_EQ(mtr1[2][0], 6.0);
  EXPECT_EQ(mtr2[2][0], 0.0);
  EXPECT_EQ(res[2][0], 6.0);
}

TEST(SquareMatrix, AdditionEqOperator) {
  SquareMatrix mtr(3);
  SquareMatrix res(3);

  // 0 1 2
  // 3 4 5
  // 6 7 8
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtr[i][j] = (double) (i * 3 + j);
    }
  }

  // 0 1 2
  // 0 1 2
  // 0 1 2
  for (double i = 0; i < 3; i++) {
    for (double j = 0; j < 3; j++) {
      res[i][j] = j;
    }
  }

  res += mtr;


  //std::cout << MatrixToString(mtr) << std::endl;
  EXPECT_EQ(mtr[1][1], 4.0);
  EXPECT_EQ(res[1][1], 5.0);

  EXPECT_EQ(mtr[2][0], 6.0);
  EXPECT_EQ(res[2][0], 6.0);
}

TEST(SquareMatrix, MultiplexionOperator) {
  SquareMatrix mtr1(3);
  SquareMatrix mtr2(3);
  SquareMatrix res(3);

  // 0 1 2
  // 3 4 5
  // 6 7 8
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtr1[i][j] = (double) (i * 3 + j);
    }
  }

  // 0 1 2
  // 0 1 2
  // 0 1 2
  for (double i = 0; i < 3; i++) {
    for (double j = 0; j < 3; j++) {
      mtr2[i][j] = j;
    }
  }

  res = mtr1 * mtr2;


  //std::cout << MatrixToString(res) << std::endl;
  EXPECT_EQ(mtr1[1][0], 3.0);
  EXPECT_EQ(mtr2[1][0], 0.0);
  EXPECT_EQ(res[1][0], 0.0);

  EXPECT_EQ(mtr1[1][1], 4.0);
  EXPECT_EQ(mtr2[1][1], 1.0);
  EXPECT_EQ(res[1][1], 12.0);
}

TEST(SquareMatrix, MultiplexionEqOperator) {
  SquareMatrix mtr(3);
  SquareMatrix res(3);

  // 0 1 2
  // 3 4 5
  // 6 7 8
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      res[i][j] = (double) (i * 3 + j);
    }
  }

  // 0 1 2
  // 0 1 2
  // 0 1 2
  for (double i = 0; i < 3; i++) {
    for (double j = 0; j < 3; j++) {
      mtr[i][j] = j;
    }
  }

  res *= mtr;


  //std::cout << MatrixToString(res) << std::endl;
  EXPECT_EQ(mtr[1][0], 0.0);
  EXPECT_EQ(res[1][0], 0.0);

  EXPECT_EQ(mtr[1][1], 1.0);
  EXPECT_EQ(res[1][1], 12.0);
}

TEST(SquareMatrix, EqualityOperator) {
  SquareMatrix mtr1(3);
  SquareMatrix mtr2(3);

  // 0 1 2
  // 3 4 5
  // 6 7 8
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtr1[i][j] = (double) (i * 3 + j);
    }
  }

  // 0 1 2
  // 0 1 2
  // 0 1 2
  for (double i = 0; i < 3; i++) {
    for (double j = 0; j < 3; j++) {
      mtr2[i][j] = j;
    }
  }


  //std::cout << MatrixToString(res) << std::endl;
  EXPECT_TRUE(mtr1 != mtr2);
  EXPECT_FALSE(mtr1 == mtr2);
  EXPECT_TRUE(mtr1 == mtr1);
  EXPECT_FALSE(mtr1 != mtr1);
}
