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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_DIV_PAIR_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_DIV_PAIR_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

template<typename T>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
mpfr_bin_ieee754_flavor<T>::div_to_pair(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (x.first <= 0.0 && x.second >= 0.0)
        return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
               (div(x, y), empty());

    if (y.first < 0.0 && y.second > 0.0) {
        representation a =  div(x, representation(y.first, 0.0));
        representation b =  div(x, representation(0.0, y.second));

        if (is_interior(representation(0.0,0.0), intersect(a,b)))
            return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
               (hull(a,b), empty());

        return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
               (less(a,b) ? a : b, less(a,b) ? b : a);
    }

    return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
           (div(x, y), empty());
}

template<typename T>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
mpfr_bin_ieee754_flavor<T>::div_to_pair(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (y.first.first < 0.0 && y.first.second > 0.0)
        return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
               (div(x, representation_dec(representation(y.first.first, 0.0), y.second)),
                div(x, representation_dec(representation(0.0, y.first.second), y.second)));

    return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
           (div(x, y), empty_dec());
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_DIV_PAIR_FUNC_IMPL_HPP
