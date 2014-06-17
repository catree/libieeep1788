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

#ifndef LIBIEEEP1788_P1788_UTIL_EFT_HPP
#define LIBIEEEP1788_P1788_UTIL_EFT_HPP

#include <utility>

namespace p1788
{

namespace util
{

template<typename T>
std::pair<T,T> two_sum(T const& a, T const& b)
{
    T s = a + b;
    T a_eps = s - b;
    T b_eps = s - a_eps;
    T a_delta = a - a_eps;
    T b_delta = b - b_eps;
    T r = a_delta + b_delta;

    return std::pair<T,T>(s,r);
}



} // namespace util

} // namespace p1788

#endif // LIBIEEEP1788_P1788_UTIL_EFT_HPP
