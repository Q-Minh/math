#include <test/unit/math/test_ad.hpp>

void expect_fft(const Eigen::VectorXcd& x) {
  stan::test::ad_tolerances tols = stan::test::reverse_only_ad_tolerances();
  int i = 0;
  int m = 0;
  auto g = [&](const auto& x) {
    using stan::math::fft;
    return i ? real(fft(x)(m)) : imag(fft(x)(m));
  };
  for (int i = 0; i < 2; ++i)
    for (int m = 0; m < x.rows(); ++m)
      stan::test::expect_ad(tols, g, x);
}

TEST(mathMixFun, fft) {
  typedef Eigen::VectorXcd cvec_t;

  cvec_t x0(0);
  expect_fft(x0);

  cvec_t x1(1);
  x1[0] = {1, 2};
  expect_fft(x1);

  cvec_t x2(2);
  x2[0] = {1, 2};
  x2[1] = {-1.3, 2.9};
  expect_fft(x2);

  Eigen::VectorXcd x3(3);
  x3[0] = {1, -1.3};
  x3[1] = {2.9, 14.7};
  x3[2] = {-12.9, -4.8};
  expect_fft(x3);

  Eigen::VectorXcd x4(4);
  x4[0] = {1, -1.3};
  x4[1] = {-2.9, 14.7};
  x4[2] = {-12.9, -4.8};
  x4[3] = {8.398, 9.387};
  expect_fft(x4);
}

void expect_inv_fft(const Eigen::VectorXcd& x) {
  stan::test::ad_tolerances tols = stan::test::reverse_only_ad_tolerances();
  int i = 0;
  int m = 0;
  auto g = [&](const auto& x) {
    using stan::math::inv_fft;
    return i ? real(inv_fft(x)(m)) : imag(inv_fft(x)(m));
  };
  for (int i = 0; i < 2; ++i)
    for (int m = 0; m < x.rows(); ++m)
      stan::test::expect_ad(tols, g, x);
}

TEST(mathMixFun, invFft) {
  typedef Eigen::VectorXcd cvec_t;

  cvec_t x0(0);
  expect_inv_fft(x0);

  cvec_t x1(1);
  x1[0] = {1, 2};
  expect_inv_fft(x1);

  cvec_t x2(2);
  x2[0] = {1, 2};
  x2[1] = {-1.3, 2.9};
  expect_inv_fft(x2);

  Eigen::VectorXcd x3(3);
  x3[0] = {1, -1.3};
  x3[1] = {2.9, 14.7};
  x3[2] = {-12.9, -4.8};
  expect_inv_fft(x3);

  Eigen::VectorXcd x4(4);
  x4[0] = {1, -1.3};
  x4[1] = {-2.9, 14.7};
  x4[2] = {-12.9, -4.8};
  x4[3] = {8.398, 9.387};
  expect_inv_fft(x4);
}

void expect_fft2(const Eigen::MatrixXcd& x) {
  stan::test::ad_tolerances tols = stan::test::reverse_only_ad_tolerances();
  int i = 0;
  int m = 0;
  int n = 0;
  auto g = [&](const auto& x) {
    using stan::math::fft2;
    return i ? real(fft2(x)(m, n)) : imag(fft2(x)(m, n));
  };
  for (int i = 0; i < 2; ++i)
    for (int n = 0; n < x.cols(); ++n)
      for (int m = 0; m < x.rows(); ++m)
        stan::test::expect_ad(tols, g, x);
}

TEST(mathMixFun, fft2) {
  typedef Eigen::MatrixXcd cmat_t;

  cmat_t x00(0, 0);
  expect_fft2(x00);

  cmat_t x11(1, 1);
  x11(0, 0) = {1, 2};
  expect_fft2(x11);

  cmat_t x21(2, 1);
  x21(0, 0) = {1, 2};
  x21(1, 0) = {-1.3, 2.9};
  expect_fft2(x21);

  cmat_t x22(2, 2);
  x22(0, 0) = {3, 9};
  x22(0, 1) = {-13.2, 8.345};
  x22(1, 0) = {-4.23, 7.566};
  x22(1, 1) = {1, -12.9};
  expect_fft2(x22);

  cmat_t x33(3, 3);
  x33(0, 0) = {3, 9};
  x33(0, 1) = {-13.2, 8.345};
  x33(0, 2) = {4.333, -1.9};
  x33(1, 0) = {-4.23, 7.566};
  x33(1, 1) = {1, -12.9};
  x33(1, 2) = {-1.01, -4.01};
  x33(2, 0) = {3.87, 5.89};
  x33(2, 1) = {-2.875, -2.999};
  x33(2, 2) = {12.98, 14.5555};
  expect_fft2(x33);
}

void expect_inv_fft2(const Eigen::MatrixXcd& x) {
  stan::test::ad_tolerances tols = stan::test::reverse_only_ad_tolerances();
  int i = 0;
  int m = 0;
  int n = 0;
  auto g = [&](const auto& x) {
    using stan::math::inv_fft2;
    return i ? real(inv_fft2(x)(m, n)) : imag(inv_fft2(x)(m, n));
  };
  for (int i = 0; i < 2; ++i)
    for (int n = 0; n < x.cols(); ++n)
      for (int m = 0; m < x.rows(); ++m)
        stan::test::expect_ad(tols, g, x);
}

TEST(mathMixFun, inv_fft2) {
  typedef Eigen::MatrixXcd cmat_t;

  cmat_t x00(0, 0);
  expect_inv_fft2(x00);

  cmat_t x11(1, 1);
  x11(0, 0) = {1, 2};
  expect_inv_fft2(x11);

  cmat_t x21(2, 1);
  x21(0, 0) = {1, 2};
  x21(1, 0) = {-1.3, 2.9};
  expect_inv_fft2(x21);

  cmat_t x22(2, 2);
  x22(0, 0) = {3, 9};
  x22(0, 1) = {-13.2, 8.345};
  x22(1, 0) = {-4.23, 7.566};
  x22(1, 1) = {1, -12.9};
  expect_inv_fft2(x22);

  cmat_t x33(3, 3);
  x33(0, 0) = {3, 9};
  x33(0, 1) = {-13.2, 8.345};
  x33(0, 2) = {4.333, -1.9};
  x33(1, 0) = {-4.23, 7.566};
  x33(1, 1) = {1, -12.9};
  x33(1, 2) = {-1.01, -4.01};
  x33(2, 0) = {3.87, 5.89};
  x33(2, 1) = {-2.875, -2.999};
  x33(2, 2) = {12.98, 14.5555};
  expect_inv_fft2(x33);
}
