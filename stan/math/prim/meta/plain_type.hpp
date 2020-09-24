#ifndef STAN_MATH_PRIM_META_PLAIN_TYPE_HPP
#define STAN_MATH_PRIM_META_PLAIN_TYPE_HPP

#include <stan/math/prim/meta/plain_type.hpp>
#include <stan/math/prim/meta/is_eigen.hpp>
#include <stan/math/prim/meta/is_detected.hpp>
#include <type_traits>

namespace stan {

/**
 * Determines plain (non expression) type associated with \c T. For non \c Eigen
 * types it is the decayed input type.
 * @tparam T type to determine plain type of
 */
template <typename T, typename Enable = void>
struct plain_type {
  using type = std::decay_t<T>;
};

template <typename T>
using plain_type_t = typename plain_type<T>::type;

/**
 * Determines return type of calling \c .eval() on Eigen expression.
 *
 * If input type \c T is a plain type (\c plain_type_t<T> equals \c
 * std::decay<T>), than member \c type is defined as <code> const
 * plain_type_t<T>& </code>. Otherwise member \c type is defined as \c
 * plain_type_t<T>.
 *
 * @tparam T type to determine eval return type of
 */
template <typename T>
struct eval_return_type {
  using T1 = plain_type_t<T>;
  using type = std::conditional_t<std::is_same<std::decay_t<T>, T1>::value,
                                  const T1&, T1>;
};

template <typename T>
using eval_return_type_t = typename eval_return_type<T>::type;

namespace internal {
template <typename T>
using has_plain_object_t = typename std::decay_t<T>::PlainObject;
template <typename T>
using has_nested_expression_t =
    typename std::decay_t<T>::ExpressionTypeNestedCleaned;
}  // namespace internal

/**
 * Template metaprogram defining the base scalar type of
 * values stored in an Eigen `VectorWiseOp` expression
 *
 * @tparam T type to check.
 * @ingroup type_trait
 */
template <typename T>
struct scalar_type<
    T, require_t<is_detected<T, internal::has_nested_expression_t>>> {
  using type = scalar_type_t<typename std::decay_t<T>::Scalar>;
};

/**
 * Template metaprogram defining the type of values stored in an
 * Eigen `VectorWiseOp` expression
 *
 * @tparam T type to check
 * @ingroup type_trait
 */
template <typename T>
struct value_type<
    T, require_t<is_detected<T, internal::has_nested_expression_t>>> {
  using type = typename std::decay_t<T>::Scalar;
};

/**
 * Determines plain (non expression) type associated with \c T. For \c Eigen
 * expression it is a type the expression can be evaluated into.
 * @tparam T type to determine plain type of
 */
template <typename T>
struct plain_type<T, require_t<is_detected<T, internal::has_plain_object_t>>> {
  using type = typename std::decay_t<T>::PlainObject;
};

template <typename T>
struct plain_type<
    T, require_t<is_detected<T, internal::has_nested_expression_t>>> {
  using type = typename std::decay_t<T>::ExpressionTypeNestedCleaned;
};

}  // namespace stan

#endif  // STAN_MATH_PRIM_META_PLAIN_TYPE_HPP
