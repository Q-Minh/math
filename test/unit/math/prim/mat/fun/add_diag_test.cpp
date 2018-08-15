#include <gtest/gtest.h>
#include <stan/math/prim/mat.hpp>
#include <limits>
#include <string>
#include <vector>

TEST(MathPrimMat, double_mat_double_add_diag) {
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> mat(2, 3);
  mat << 1, 1, 1, 1, 1, 1;

  double jitter = 1e-10;

  Eigen::MatrixXd out_mat;
  EXPECT_NO_THROW(out_mat = stan::math::add_diag(mat, jitter));
  for (int i = 0; i < 2; ++i)
    EXPECT_FLOAT_EQ(1.0 + jitter, out_mat(i, i))
        << "index: ( " << i << ", " << i << ")";
}

TEST(MathPrimMat, double_mat_double_vec_add_diag) {
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> mat(2, 3);
  mat << 1, 1, 1, 1, 1, 1;

  Eigen::Matrix<double, 1, -1> to_add(2);
  to_add << 0, 1;

  Eigen::MatrixXd out_mat;
  EXPECT_NO_THROW(out_mat = stan::math::add_diag(mat, to_add));
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j)
        EXPECT_FLOAT_EQ(1 + to_add[i], out_mat(i, j))
            << "index: ( " << i << ", " << i << ")";
      else
        EXPECT_FLOAT_EQ(1, out_mat(i, j))
            << "index: ( " << i << ", " << i << ")";
    }
  }
}

TEST(MathPrimMat, double_mat_double_rvec_add_diag) {
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> mat(2, 3);
  mat << 1, 1, 1, 1, 1, 1;

  Eigen::Matrix<double, -1, 1> to_add(2);
  to_add << 0, 1;

  Eigen::MatrixXd out_mat;
  EXPECT_NO_THROW(out_mat = stan::math::add_diag(mat, to_add));
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j)
        EXPECT_FLOAT_EQ(1 + to_add[i], out_mat(i, i))
            << "index: ( " << i << ", " << i << ")";
      else
        EXPECT_FLOAT_EQ(1, out_mat(i, j))
            << "index: ( " << i << ", " << i << ")";
    }
  }
}

TEST(MathPrimMat, double_mat_double_rvec_add_diag) {
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> mat(2, 3);
  mat << 1, 1, 1, 1, 1, 1;

  Eigen::Matrix<double, -1, 1> to_add(2);
  to_add << 0, 1;

  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> out_mat;
  EXPECT_NO_THROW(out_mat = stan::math::add_diag(mat, to_add));
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j)
        EXPECT_FLOAT_EQ(1 + to_add[i], out_mat(i, i))
            << "index: ( " << i << ", " << i << ")";
      else
        EXPECT_FLOAT_EQ(1, out_mat(i, j))
            << "index: ( " << i << ", " << i << ")";
    }
  }
}
