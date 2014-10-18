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

#define BOOST_TEST_MODULE "IO operators [infsup/interval, infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include "p1788/p1788.hpp"


template<typename T>
using flavor = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T, p1788::flavor::infsup::setbased::subnormalize::yes, p1788::flavor::infsup::setbased::auto_setup::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;


BOOST_AUTO_TEST_CASE(minimal_ostream_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_istream_test)
{
    BOOST_CHECK(false);
}

