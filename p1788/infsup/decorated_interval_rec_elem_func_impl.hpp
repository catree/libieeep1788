//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Institute of Computer Science,
//   University of Wuerzburg, Germany
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#ifndef LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REC_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REC_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name Recommended forward elementary functions on intervals, see P1788/D7.0 Sect. 9.7.1 Table 5
///
///@{


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> rootn(decorated_interval<T, Flavor> const& x, int n) {
    return decorated_interval<T, Flavor>(Flavor<T>::rootn_dec(x.rep_, n));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval rootn(decorated_interval<T, Flavor> const& x, int n) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(rootn(static_cast<decorated_interval<TMax, Flavor>>(x), n));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> expm1(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::expm1_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval expm1(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(expm1(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> exp2m1(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::exp2m1_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval exp2m1(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(exp2m1(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> exp10m1(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::exp10m1_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval exp10m1(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(exp10m1(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> logp1(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::logp1_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval logp1(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(logp1(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> log2p1(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::log2p1_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval log2p1(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(log2p1(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> log10p1(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::log10p1_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval log10p1(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(log10p1(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> compoundm1(decorated_interval<T, Flavor> const& x,
                                      decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::compoundm1_dec(x.rep_, y.rep_));
}

//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval compoundm1(decorated_interval<T, Flavor> const& x,
//                           decorated_interval<Ty, Flavor> const& y) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T,
//             Ty
//             >::type TMax;
//
//    return Interval(compoundm1(static_cast<decorated_interval<TMax, Flavor>>(x),
//                               static_cast<decorated_interval<TMax, Flavor>>(y)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> hypot(decorated_interval<T, Flavor> const& x,
                                 decorated_interval<T, Flavor> const& y) {   ///< tightest, required or recommended?
    return decorated_interval<T, Flavor>(Flavor<T>::hypot_dec(x.rep_, y.rep_));
}

//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval hypot(decorated_interval<T, Flavor> const& x,
//                      decorated_interval<Ty, Flavor> const& y) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T,
//             Ty
//             >::type TMax;
//
//    return Interval(hypot(static_cast<decorated_interval<TMax, Flavor>>(x),
//                          static_cast<decorated_interval<TMax, Flavor>>(y)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> r_sqrt(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::r_sqrt_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval r_sqrt(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(r_sqrt(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sin_pi(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::sin_pi_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval sin_pi(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(sin_pi(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> cos_pi(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::cos_pi_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval cos_pi(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(cos_pi(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> tan_pi(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::tan_pi_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval tan_pi(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(tan_pi(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> asin_pi(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::asin_pi_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval asin_pi(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(asin_pi(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> acos_pi(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::acos_pi_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval acos_pi(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(acos_pi(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan_pi(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::atan_pi_dec(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval atan_pi(decorated_interval<T, Flavor> const& x) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type TMax;
//
//    return Interval(atan_pi(static_cast<decorated_interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan2_pi(decorated_interval<T, Flavor> const& x,
                                    decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::atan2_pi_dec(x.rep_, y.rep_));
}

//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval atan2_pi(decorated_interval<T, Flavor> const& x,
//                         decorated_interval<Ty, Flavor> const& y) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T,
//             Ty
//             >::type TMax;
//
//    return Interval(atan2_pi(static_cast<decorated_interval<TMax, Flavor>>(x),
//                             static_cast<decorated_interval<TMax, Flavor>>(y)));
//}

///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REC_ELEM_FUNC_IMPL_HPP
