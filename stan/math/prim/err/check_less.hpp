#ifndef STAN_MATH_PRIM_ERR_CHECK_LESS_HPP
#define STAN_MATH_PRIM_ERR_CHECK_LESS_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/err/throw_domain_error.hpp>
#include <stan/math/prim/err/throw_domain_error_vec.hpp>
#include <stan/math/prim/fun/get.hpp>
#include <stan/math/prim/fun/size.hpp>
#include <stan/math/prim/fun/to_ref.hpp>
#include <string>

namespace stan {
namespace math {

namespace internal {
template <typename T_y, typename T_high, bool is_vec>
struct less {
  static void check(const char* function, const char* name, const T_y& y,
                    const T_high& high) {
    scalar_seq_view<T_high> high_vec(high);
    for (size_t n = 0; n < stan::math::size(high); n++) {
      if (!(y < high_vec[n])) {
        [&]() STAN_COLD_PATH {
          std::stringstream msg;
          msg << ", but must be less than ";
          msg << high_vec[n];
          std::string msg_str(msg.str());
          throw_domain_error(function, name, y, "is ", msg_str.c_str());
        }();
      }
    }
  }
};

template <typename T_y, typename T_high>
struct less<T_y, T_high, true> {
  static void check(const char* function, const char* name, const T_y& y,
                    const T_high& high) {
    scalar_seq_view<T_high> high_vec(high);
    const auto& y_ref = to_ref(y);
    for (size_t n = 0; n < stan::math::size(y_ref); n++) {
      if (!(stan::get(y_ref, n) < high_vec[n])) {
        [&]() STAN_COLD_PATH {
          std::stringstream msg;
          msg << ", but must be less than ";
          msg << high_vec[n];
          std::string msg_str(msg.str());
          throw_domain_error(function, name, y_ref, "is ",
			     msg_str.c_str());
        }();
      }
    }
  }
};
}  // namespace internal

/**
 * Check if <code>y</code> is strictly less than <code>high</code>.
 * This function is vectorized and will check each element of
 * <code>y</code> against each element of <code>high</code>.
 * @tparam T_y Type of y
 * @tparam T_high Type of upper bound
 * @param function Function name (for error messages)
 * @param name Variable name (for error messages)
 * @param y Variable to check
 * @param high Upper bound
 * @throw <code>domain_error</code> if y is not less than low
 *   or if any element of y or high is NaN.
 */
template <typename T_y, typename T_high,
	  require_stan_scalar_t<T_y>* = nullptr,
	  require_all_nonscalar_prim_or_rev_kernel_expression_t<T_high>* = nullptr>
inline void check_less(const char* function, const char* name, const T_y& y,
                       const T_high& high) {
  internal::less<T_y, T_high, is_vector_like<T_y>::value>::check(function, name,
                                                                 y, high);
}
  
/**
 * Check if <code>y</code> is strictly less than <code>high</code>.
 * This function is vectorized and will check each element of
 * <code>y</code> against each element of <code>high</code>.
 * @tparam T_y Type of y
 * @tparam T_high Type of upper bound
 * @param function Function name (for error messages)
 * @param name Variable name (for error messages)
 * @param y Variable to check
 * @param high Upper bound
 * @throw <code>domain_error</code> if y is not less than low
 *   or if any element of y or high is NaN.
 */
template <typename T_y, typename T_high,
          require_all_stan_scalar_t<T_y, T_high>* = nullptr>
inline void check_less(const char* function, const char* name, const T_y& y,
                       const T_high& high) {
  if (!(y < high)) {
    [&]() STAN_COLD_PATH {
      std::stringstream msg;
      msg << ", but must be less than ";
      msg << high;
      std::string msg_str(msg.str());
      throw_domain_error(function, name, y, "is ", msg_str.c_str());
    }();
  }
}

/**
 * Check if <code>y</code> is strictly less than <code>high</code>.
 * This function is vectorized and will check each element of
 * <code>y</code> against each element of <code>high</code>.
 * @tparam T_y A container type
 * @tparam T_high A container type
 * @param function Function name (for error messages)
 * @param name Variable name (for error messages)
 * @param y Variable to check
 * @param high Upper bound
 * @throw <code>domain_error</code> if y is not less than low
 *   or if any element of y or high is NaN.
 */
template <typename T_y, typename T_high,
          require_all_container_t<T_y, T_high>* = nullptr>
inline void check_less(const char* function, const char* name, const T_y& y,
                       const T_high& high) {
  const auto& high_ref = as_array_or_scalar(to_ref(high));
  const auto& y_ref = as_array_or_scalar(to_ref(y));
  Eigen::Index n = 0;
  for (Eigen::Index j = 0; j < y_ref.cols(); ++j) {
    for (Eigen::Index i = 0; i < y_ref.rows(); ++i) {
      if (!(y_ref.coeff(i, j) < high_ref.coeff(i, j))) {
        [&]() STAN_COLD_PATH {
          std::stringstream msg;
          msg << ", but must be less than ";
          msg << high_ref.coeff(i, j);
          std::string msg_str(msg.str());
          throw_domain_error_vec(function, name, y_ref.coeff(i, j), i + j,
                                 "is ", msg_str.c_str());
        }();
      }
    }
  }
}

/**
 * Check if <code>y</code> is strictly less than <code>high</code>.
 * This function is vectorized and will check each element of
 * <code>y</code> against each element of <code>high</code>.
 * @tparam T_y A container type
 * @tparam T_high A scalar type
 * @param function Function name (for error messages)
 * @param name Variable name (for error messages)
 * @param y Variable to check
 * @param high Upper bound
 * @throw <code>domain_error</code> if y is not less than low
 *   or if any element of y or high is NaN.
 */
template <typename T_y, typename T_high, require_container_t<T_y>* = nullptr,
          require_stan_scalar_t<T_high>* = nullptr>
inline void check_less(const char* function, const char* name, const T_y& y,
                       const T_high& high) {
  const auto& y_ref = as_array_or_scalar(to_ref(y));
  Eigen::Index n = 0;
  for (Eigen::Index j = 0; j < y_ref.cols(); ++j) {
    for (Eigen::Index i = 0; i < y_ref.rows(); ++i) {
      if (!(y_ref.coeff(i, j) < high)) {
        [&]() STAN_COLD_PATH {
          std::stringstream msg;
          msg << ", but must be less than ";
          msg << high;
          std::string msg_str(msg.str());
          throw_domain_error_vec(function, name, y_ref.coeff(i, j), i + j,
                                 "is ", msg_str.c_str());
        }();
      }
    }
  }
}

/**
 * Check if <code>y</code> is strictly less than <code>high</code>.
 * This function is vectorized and will check each element of
 * <code>y</code> against each element of <code>high</code>.
 * @tparam T_y A container type
 * @tparam T_high A scalar type
 * @param function Function name (for error messages)
 * @param name Variable name (for error messages)
 * @param y Variable to check
 * @param high Upper bound
 * @throw <code>domain_error</code> if y is not less than low
 *   or if any element of y or high is NaN.
 */
template <typename T_y, typename T_high, require_container_t<T_high>* = nullptr,
          require_stan_scalar_t<T_y>* = nullptr,
	  require_all_not_nonscalar_prim_or_rev_kernel_expression_t<T_high>* = nullptr>
inline void check_less(const char* function, const char* name, const T_y& y,
                       const T_high& high) {
  const auto& high_ref = as_array_or_scalar(to_ref(high));
  Eigen::Index n = 0;
  for (Eigen::Index j = 0; j < high_ref.cols(); ++j) {
    for (Eigen::Index i = 0; i < high_ref.rows(); ++i) {
      if (!(y < high_ref.coeff(i, j))) {
        [&]() STAN_COLD_PATH {
          std::stringstream msg;
          msg << ", but must be less than ";
          msg << high_ref(i, j);
          std::string msg_str(msg.str());
          throw_domain_error(function, name, y, "is ", msg_str.c_str());
        }();
      }
    }
  }
}

}  // namespace math
}  // namespace stan
#endif
