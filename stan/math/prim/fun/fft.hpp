#ifndef STAN_MATH_PRIM_FUN_FFT_HPP
#define STAN_MATH_PRIM_FUN_FFT_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/fun/Eigen.hpp>
#include <unsupported/Eigen/FFT>
#include <complex>
#include <type_traits>
#include <vector>

namespace stan {
namespace math {

  /**
   * Return the discrete Fourier transform of the specified complex
   * vector.  The input vector may be considered to be in the time
   * domain and the output will be in the frequency domain. 
   *
   * Given an input complex vector `x[0:N-1]` of size `N`, the discrete
   * Fourier transform computes entries of the resulting complex
   * vector `y[0:N-1]` by 
   *
   * ```
   * y[i] = SUM_{j < N} x[j] exp(-2 * pi * i * j * sqrt(-1) / n)
   * ```
   * 
   * If `y` is of size zero, the result is a size zero vector.
   *
   * @tparam T scalar type of real and imaginary components
   * @param x complex time domain vector to transform
   * @return discrete Fourier transform of `x`
   */
  template <typename V, require_eigen_vector_vt<is_complex, V>* = nullptr>
  inline Eigen::Matrix<scalar_type_t<V>, -1, 1> fft(const V& x) {
    Eigen::Matrix<scalar_type_t<V>, -1, 1> xv = x;
    if (xv.size() <= 1) return xv;
    Eigen::FFT<typename scalar_type_t<V>::value_type> fft;
    return fft.fwd(xv);
  }


  /**
   * Return the inverse discrete Fourier transform of the specified
   * complex vector.  The input may be considered to be in the
   * frequency domain and the output will be in the time domain.
   *
   * Given an input complex vector `y[0:N-1]` of size `N`, the inverse
   * discrete Fourier transform computes entries of the resulting
   * complex vector `x[0:N-1]` by 
   *
   * ```
   * x[i] = SUM_{j < N} y[j] exp(2 * pi * i * j * sqrt(-1) / n)
   * ```
   *
   * If the input is size zero, the output will be size zero.
   *
   * @tparam T scalar type of real and imaginary components
   * @param y complex frequency domain vector to inverse transform
   * @return inverse discrete Fourier transform of `x`
   */
  template <typename V, require_eigen_vector_vt<is_complex, V>* = nullptr>
  inline Eigen::Matrix<scalar_type_t<V>, -1, 1> inv_fft(const V& y) {
    Eigen::Matrix<scalar_type_t<V>, -1, 1> yv = y;
    if (y.size() <= 1) return yv;
    Eigen::FFT<typename scalar_type_t<V>::value_type> fft;
    return fft.inv(yv);
  }
  
}  // namespace math
}  // namespace stan

#endif
