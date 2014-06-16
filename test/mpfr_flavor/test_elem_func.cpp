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

#define BOOST_TEST_MODULE "Forward elementary functions [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <limits>
#include "p1788/p1788.hpp"


template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;

const double INF = std::numeric_limits<double>::infinity();
const double MAX = std::numeric_limits<double>::max();
const double MIN = std::numeric_limits<double>::min();


BOOST_AUTO_TEST_CASE(minimal_pos_test)
{
    BOOST_CHECK_EQUAL( pos(I<double>(1.0,2.0)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( +I<double>(1.0,2.0), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( pos(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( +I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( pos(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( +I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( pos(I<double>(1.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( +I<double>(1.0,INF), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( pos(I<double>(-INF,-1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( +I<double>(-INF,-1.0), I<double>(-INF,-1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_neg_test)
{
    BOOST_CHECK_EQUAL( neg(I<double>(1.0,2.0)), I<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( -I<double>(1.0,2.0), I<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( neg(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( -I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( neg(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( -I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( neg(I<double>(1.0,INF)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( -I<double>(1.0,INF), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( neg(I<double>(-INF,1.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( -I<double>(-INF,1.0), I<double>(-1.0,INF) );
}

BOOST_AUTO_TEST_CASE(minimal_add_test)
{
    BOOST_CHECK_EQUAL( add(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() + I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) + I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() + I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() + I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>::empty(), I<double>::empty() );

    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>(-INF,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>(-INF,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>(-1.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>(-1.0,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>(-1.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>(-1.0,INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(-INF,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,1.0) + I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(-1.0,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) + I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(-1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) + I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( add(I<double>(-INF,2.0), I<double>(-INF,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) + I<double>(-INF,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(-INF,2.0), I<double>(3.0,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) + I<double>(3.0,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(-INF,2.0), I<double>(3.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) + I<double>(3.0,INF), I<double>::entire() );

    BOOST_CHECK_EQUAL( add(I<double>(1.0,2.0), I<double>(-INF,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) + I<double>(-INF,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,2.0), I<double>(3.0,4.0)), I<double>(4.0,6.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) + I<double>(3.0,4.0), I<double>(4.0,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,2.0), I<double>(3.0,INF)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) + I<double>(3.0,INF), I<double>(4.0,INF) );

    BOOST_CHECK_EQUAL( add(I<double>(1.0,INF), I<double>(-INF,4.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) + I<double>(-INF,4.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,INF), I<double>(3.0,4.0)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) + I<double>(3.0,4.0), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,INF), I<double>(3.0,INF)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) + I<double>(3.0,INF), I<double>(4.0,INF) );

    BOOST_CHECK_EQUAL( add(I<double>(1.0,MAX), I<double>(3.0,4.0)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,MAX) + I<double>(3.0,4.0), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( add(I<double>(-MAX,2.0), I<double>(-3.0,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) + I<double>(-3.0,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(-MAX,2.0), I<double>(-3.0,MAX)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) + I<double>(-3.0,MAX), I<double>::entire() );

    BOOST_CHECK_EQUAL( add(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) + I<double>(0X1.999999999999AP-4), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( add(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.999999999999AP-4)), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) + I<double>(-0X1.999999999999AP-4), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( add(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(-0X1.E666666666657P+0,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0) + I<double>(0X1.999999999999AP-4), I<double>(-0X1.E666666666657P+0,0X1.0CCCCCCCCCCC5P+1) );
}

BOOST_AUTO_TEST_CASE(minimal_sub_test)
{
    BOOST_CHECK_EQUAL( sub(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() - I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) - I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() - I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() - I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>::empty(), I<double>::empty() );

    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>(-INF,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>(-INF,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>(-1.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>(-1.0,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>(-1.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>(-1.0,INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-INF,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,1.0) - I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-1.0,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) - I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) - I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( sub(I<double>(-INF,2.0), I<double>(-INF,4.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) - I<double>(-INF,4.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-INF,2.0), I<double>(3.0,4.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) - I<double>(3.0,4.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( sub(I<double>(-INF,2.0), I<double>(3.0,INF)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) - I<double>(3.0,INF), I<double>(-INF,-1.0) );

    BOOST_CHECK_EQUAL( sub(I<double>(1.0,2.0), I<double>(-INF,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) - I<double>(-INF,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,2.0), I<double>(3.0,4.0)), I<double>(-3.0,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) - I<double>(3.0,4.0), I<double>(-3.0,-1.0) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,2.0), I<double>(3.0,INF)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) - I<double>(3.0,INF), I<double>(-INF,-1.0) );

    BOOST_CHECK_EQUAL( sub(I<double>(1.0,INF), I<double>(-INF,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) - I<double>(-INF,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,INF), I<double>(3.0,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) - I<double>(3.0,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,INF), I<double>(3.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) - I<double>(3.0,INF), I<double>::entire() );

    BOOST_CHECK_EQUAL( sub(I<double>(1.0,MAX), I<double>(-3.0,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,MAX) - I<double>(-3.0,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(-MAX,2.0), I<double>(3.0,4.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) - I<double>(3.0,4.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( sub(I<double>(-MAX,2.0), I<double>(-MAX,4.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) - I<double>(-MAX,4.0), I<double>::entire() );

    BOOST_CHECK_EQUAL( sub(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) - I<double>(0X1.999999999999AP-4), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( sub(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.999999999999AP-4)), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) - I<double>(-0X1.999999999999AP-4), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( sub(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(-0X1.0CCCCCCCCCCC5P+1,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0) - I<double>(0X1.999999999999AP-4), I<double>(-0X1.0CCCCCCCCCCC5P+1,0X1.E666666666657P+0) );
}

BOOST_AUTO_TEST_CASE(minimal_mul_test)
{
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>(0.0), I<double>::empty() );

    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-5.0, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-5.0, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(1.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(1.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-5.0, -1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-5.0, -1.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(1.0, 3.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(1.0, 3.0), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-INF, -1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-INF, -1.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(1.0, INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(1.0, INF), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-5.0, -1.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-5.0, -1.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(1.0, 3.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(1.0, 3.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-5.0, -1.0)), I<double>(-15.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-5.0, -1.0), I<double>(-15.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(1.0, 3.0)), I<double>(-INF,9.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(1.0, 3.0), I<double>(-INF,9.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-5.0, -1.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-5.0, -1.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(1.0, 3.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(1.0, 3.0), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-INF, -1.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-INF, -1.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(1.0, INF)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(1.0, INF), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-5.0, -1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-5.0, -1.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-5.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-5.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(1.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(1.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-INF, -1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-INF, -1.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-INF, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-INF, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-5.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-5.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(1.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(1.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>::entire()), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>::entire(), I<double>(0.0) );

    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-5.0, -1.0)), I<double>(-25.0,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-5.0, -1.0), I<double>(-25.0,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-5.0, 3.0)), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-5.0, 3.0), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(1.0, 3.0)), I<double>(1.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(1.0, 3.0), I<double>(1.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-INF, -1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-INF, -1.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-INF, 3.0)), I<double>(-INF,15.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-INF, 3.0), I<double>(-INF,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-5.0, INF)), I<double>(-25.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-5.0, INF), I<double>(-25.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(1.0, INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(1.0, INF), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-5.0, -1.0)), I<double>(-25.0,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-5.0, -1.0), I<double>(-25.0,5.0) );
    //min max
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-5.0, 3.0)), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-5.0, 3.0), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,2.0), I<double>(-5.0, 3.0)), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,2.0) * I<double>(-5.0, 3.0), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-1.0, 10.0)), I<double>(-10.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-1.0, 10.0), I<double>(-10.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-2.0,2.0), I<double>(-5.0, 3.0)), I<double>(-10.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-2.0,2.0) * I<double>(-5.0, 3.0), I<double>(-10.0,10.0) );
    //end min max
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(1.0, 3.0)), I<double>(-3.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(1.0, 3.0), I<double>(-3.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0)), I<double>(5.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-5.0, -1.0), I<double>(5.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0)), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-5.0, 3.0), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(1.0, 3.0)), I<double>(-30.0,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(1.0, 3.0), I<double>(-30.0,-5.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-INF, -1.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-INF, -1.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-INF, 3.0)), I<double>(-30.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-INF, 3.0), I<double>(-30.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-5.0, INF)), I<double>(-INF,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-5.0, INF), I<double>(-INF,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(1.0, INF)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(1.0, INF), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>::entire(), I<double>::entire() );


    BOOST_CHECK_EQUAL( mul(I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.FFFFFFFFFFFFP+0, INF)), I<double>(-0X1.FFFFFFFFFFFE1P+1,INF) );
    BOOST_CHECK_EQUAL( I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0) * I<double>(-0X1.FFFFFFFFFFFFP+0, INF), I<double>(-0X1.FFFFFFFFFFFE1P+1,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4)), I<double>(-0X1.FFFFFFFFFFFE1P+1,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0) * I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4), I<double>(-0X1.FFFFFFFFFFFE1P+1,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( mul(I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-4), I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4)), I<double>(-0X1.999999999998EP-3,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-4) * I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4), I<double>(-0X1.999999999998EP-3,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( mul(I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4), I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0)), I<double>(-0X1.FFFFFFFFFFFE1P+1,-0X1.47AE147AE147BP-7) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4) * I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.FFFFFFFFFFFE1P+1,-0X1.47AE147AE147BP-7) );
}


BOOST_AUTO_TEST_CASE(minimal_div_test)
{
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(0.1,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(0.1,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(-1.0,-0.1)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(-1.0,-0.1), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(0.0), I<double>::empty() );

    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-5.0, -3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-5.0, -3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(3.0, 5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(3.0, 5.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-INF, -3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-INF, -3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(3.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(3.0,INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-5.0, -3.0)), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-5.0, -3.0), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(3.0, 5.0)), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(3.0, 5.0), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-INF, -3.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-INF, -3.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(3.0,INF)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(3.0,INF), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-3.0, 0.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-3.0, 0.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(0.0, 3.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(0.0, 3.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-5.0, -3.0)), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-5.0, -3.0), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(3.0, 5.0)), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(3.0, 5.0), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-INF, -3.0)), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-INF, -3.0), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(3.0,INF)), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(3.0,INF), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-5.0, -3.0)), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-5.0, -3.0), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(3.0, 5.0)), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(3.0, 5.0), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-INF, -3.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-INF, -3.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(3.0,INF)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(3.0,INF), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-3.0, 0.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-3.0, 0.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(0.0, 3.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(0.0, 3.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-5.0, -3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-5.0, -3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(3.0, 5.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(3.0, 5.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-INF, -3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-INF, -3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(3.0,INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(3.0,INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-3.0, 0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-3.0, 0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-3.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-3.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(0.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(0.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-INF, 0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-INF, 0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-INF, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-INF, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-3.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-3.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(0.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(0.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>::entire()), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>::entire(), I<double>(0.0) );

    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-5.0, -3.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-5.0, -3.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(3.0, 5.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(3.0, 5.0), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-INF, -3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-INF, -3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(3.0,INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(3.0,INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-3.0, 0.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-3.0, 0.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(0.0, 3.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(0.0, 3.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-5.0, -3.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-5.0, -3.0), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(3.0, 5.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(3.0, 5.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-INF, -3.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-INF, -3.0), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(3.0,INF)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(3.0,INF), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-5.0, -3.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-5.0, -3.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(3.0, 5.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(3.0, 5.0), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-INF, -3.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-INF, -3.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(3.0,INF)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(3.0,INF), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-5.0, -3.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-5.0, -3.0), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(3.0, 5.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(3.0, 5.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-INF, -3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-INF, -3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(3.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(3.0,INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-3.0, 0.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-3.0, 0.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(0.0, 3.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(0.0, 3.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>::entire(), I<double>::entire() );


    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-5.0, -3.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-5.0, -3.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(3.0, 5.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(3.0, 5.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-INF, -3.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-INF, -3.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(3.0,INF)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(3.0,INF), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-3.0, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-3.0, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(0.0, 3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(0.0, 3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-5.0, -3.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-5.0, -3.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(3.0, 5.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(3.0, 5.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-INF, -3.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-INF, -3.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(3.0,INF)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(3.0,INF), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-3.0, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-3.0, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(0.0, 3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(0.0, 3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-5.0, -3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-5.0, -3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(3.0, 5.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(3.0, 5.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-INF, -3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-INF, -3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(3.0,INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(3.0,INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-3.0, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-3.0, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(0.0, 3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(0.0, 3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-5.0, -3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-5.0, -3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(3.0, 5.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(3.0, 5.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-INF, -3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-INF, -3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(3.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(3.0,INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-3.0, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-3.0, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-3.0, 3.0)), I<double>::entire()  );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-3.0, 3.0), I<double>::entire()  );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(0.0, 3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(0.0, 3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>::entire(), I<double>::entire() );



    BOOST_CHECK_EQUAL( div(I<double>(-2.0,-1.0), I<double>(-10.0, -3.0)), I<double>(0X1.9999999999999P-4,0X1.5555555555556P-1) );
    BOOST_CHECK_EQUAL( I<double>(-2.0,-1.0) / I<double>(-10.0, -3.0), I<double>(0X1.9999999999999P-4,0X1.5555555555556P-1) );
    BOOST_CHECK_EQUAL( div(I<double>(-2.0,-1.0), I<double>(0.0, 10.0)), I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( I<double>(-2.0,-1.0) / I<double>(0.0, 10.0), I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( div(I<double>(-1.0,2.0), I<double>(10.0,INF)), I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-3) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,2.0) / I<double>(10.0,INF), I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-3) );
    BOOST_CHECK_EQUAL( div(I<double>(1.0,3.0), I<double>(-INF, -10.0)), I<double>(-0X1.3333333333334P-2,0.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,3.0) / I<double>(-INF, -10.0), I<double>(-0X1.3333333333334P-2,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-1.0), I<double>(1.0, 3.0)), I<double>(-INF,-0X1.5555555555555P-2) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-1.0) / I<double>(1.0, 3.0), I<double>(-INF,-0X1.5555555555555P-2) );
}

BOOST_AUTO_TEST_CASE(minimal_recip_test)
{
    BOOST_CHECK_EQUAL( recip(I<double>(-50.0, -10.0)), I<double>(-0X1.999999999999AP-4,-0X1.47AE147AE147AP-6) );
    BOOST_CHECK_EQUAL( recip(I<double>(10.0, 50.0)), I<double>(0X1.47AE147AE147AP-6,0X1.999999999999AP-4) );
    BOOST_CHECK_EQUAL( recip(I<double>(-INF, -10.0)), I<double>(-0X1.999999999999AP-4,0.0) );
    BOOST_CHECK_EQUAL( recip(I<double>(10.0,INF)), I<double>(0.0,0X1.999999999999AP-4) );
    BOOST_CHECK_EQUAL( recip(I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( recip(I<double>(-10.0, 0.0)), I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( recip(I<double>(-10.0, 10.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( recip(I<double>(0.0, 10.0)), I<double>(0X1.9999999999999P-4,INF) );
    BOOST_CHECK_EQUAL( recip(I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( recip(I<double>(-INF, 10.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( recip(I<double>(-10.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( recip(I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( recip(I<double>::entire()), I<double>::entire() );
}

BOOST_AUTO_TEST_CASE(minimal_sqr_test)
{
    BOOST_CHECK_EQUAL( sqr(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sqr(I<double>::entire()), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-INF,-MIN)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-1.0,1.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-5.0,3.0)), I<double>(0.0,25.0) );
    BOOST_CHECK_EQUAL( sqr(I<double>(0X1.999999999999AP-4)), I<double>(0X1.47AE147AE147BP-7,0X1.47AE147AE147CP-7) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4)), I<double>(0.0,0X1.FFFFFFFFFFFE1P+1) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-0X1.FFFFFFFFFFFFP+0)), I<double>(0X1.FFFFFFFFFFFEP+1,0X1.FFFFFFFFFFFE1P+1) );
}

BOOST_AUTO_TEST_CASE(minimal_sqrt_test)
{
    BOOST_CHECK_EQUAL( sqrt(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sqrt(I<double>::entire()), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-INF,-MIN)), I<double>::empty() );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-1.0,1.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-5.0,25.0)), I<double>(0.0,5.0) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-5.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(0X1.999999999999AP-4)), I<double>(0X1.43D136248490FP-2,0X1.43D136248491P-2) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4)), I<double>(0.0,0X1.43D136248491P-2) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0)), I<double>(0X1.43D136248490FP-2,0X1.6A09E667F3BC7P+0) );
}

BOOST_AUTO_TEST_CASE(minimal_fma_test)
{
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>(-INF,2.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,7.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,11.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>(-INF,2.0) );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,7.0) );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,12.0) );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>(-2.0,2.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,7.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-17.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-INF,11.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-27.0,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-27.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-1.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-27.0,7.0) );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-27.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>(-2.0,2.0)), I<double>(-12.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-12.0,12.0) );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-5.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(3.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>(-2.0,INF)), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-17.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>(-2.0,INF) );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>(-2.0,INF)), I<double>(-12.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-12.0,INF) );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>::entire()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );


    BOOST_CHECK_EQUAL( fma(I<double>(0.1,0.5), I<double>(-5.0, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.4CCCCCCCCCCCDP+1,0X1.999999999999AP+0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-0.5,0.2), I<double>(-5.0, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.999999999999AP+0,0X1.4CCCCCCCCCCCDP+1) );
    BOOST_CHECK_EQUAL( fma(I<double>(-0.5,-0.1), I<double>(2.0, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.999999999999AP+0,-0X1.999999999999AP-4) );
    BOOST_CHECK_EQUAL( fma(I<double>(-0.5,-0.1), I<double>(-INF, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.999999999999AP+0,INF) );
}

//BOOST_AUTO_TEST_CASE(minimal_interval_case_test)
//{
//TODO noch notwendig?
//    BOOST_CHECK(false);
//}


BOOST_AUTO_TEST_CASE(minimal_pown_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_pow_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_exp_test)
{
    BOOST_CHECK_EQUAL( exp(I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( exp(I<double>(-INF,0.0)),I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( exp(I<double>(0.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( exp(I<double>::entire()), I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( exp(I<double>(-INF,0X1.62E42FEFA39FP+9)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( exp(I<double>(0X1.62E42FEFA39FP+9)), I<double>( 0X1.FFFFFFFFFFFFFP+1023,INF) );
    BOOST_CHECK_EQUAL( exp(I<double>(0.0,0X1.62E42FEFA39EP+9)), I<double>(1.0,0X1.FFFFFFFFFC32BP+1023) );
    BOOST_CHECK_EQUAL( exp(I<double>(-0X1.6232BDD7ABCD3P+9,0X1.62E42FEFA39EP+9)), I<double>(0.0,0X1.FFFFFFFFFC32BP+1023) );
    BOOST_CHECK_EQUAL( exp(I<double>(-0X1.6232BDD7ABCD3P+8,0X1.62E42FEFA39EP+9)), I<double>(0X1.FFFFFFFFFFE7BP-512,0X1.FFFFFFFFFC32BP+1023) );
    BOOST_CHECK_EQUAL( exp(I<double>(-0X1.6232BDD7ABCD3P+8,0.0)), I<double>(0X1.FFFFFFFFFFE7BP-512,1.0) );
    BOOST_CHECK_EQUAL( exp(I<double>(-0X1.6232BDD7ABCD3P+8,1.0)), I<double>(0X1.FFFFFFFFFFE7BP-512,0X1.5BF0A8B14576AP+1) );

    BOOST_CHECK_EQUAL( exp(I<double>(1.0,5.0)), I<double>(0X1.5BF0A8B145769P+1,0X1.28D389970339P+7) );

    BOOST_CHECK_EQUAL( exp(I<double>(-0X1.A934F0979A372P+1,0X1.CEAECFEA8085AP+0)), I<double>(0X1.2797F0A337A5FP-5,0X1.86091CC9095C5P+2) );
    BOOST_CHECK_EQUAL( exp(I<double>(0X1.87F42B972949CP-1,0X1.8B55484710029P+6)), I<double>(0X1.1337E9E45812AP+1, 0X1.805A5C88021B6P+142) );
    BOOST_CHECK_EQUAL( exp(I<double>(0X1.78025C8B3FD39P+3,0X1.9FD8EEF3FA79BP+4)), I<double>(0X1.EF461A783114CP+16,0X1.691D36C6B008CP+37)  );
}

BOOST_AUTO_TEST_CASE(minimal_exp2_test)
{
    BOOST_CHECK_EQUAL( exp2(I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( exp2(I<double>(-INF,0.0)),I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( exp2(I<double>(0.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( exp2(I<double>::entire()), I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( exp2(I<double>(-INF,1024.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( exp2(I<double>(1024.0)), I<double>(0X1.FFFFFFFFFFFFFP+1023,INF) );
    BOOST_CHECK_EQUAL( exp2(I<double>(0.0,1023.0)), I<double>(1.0,0X1P+1023) );
    BOOST_CHECK_EQUAL( exp2(I<double>(-1022.0,1023.0)), I<double>(0X1P-1022,0X1P+1023) );
    BOOST_CHECK_EQUAL( exp2(I<double>(-1022.0,0.0)), I<double>(0X1P-1022,1.0) );
    BOOST_CHECK_EQUAL( exp2(I<double>(-1022.0,1.0)), I<double>(0X1P-1022,2.0) );

    BOOST_CHECK_EQUAL( exp2(I<double>(1.0,5.0)), I<double>(2.0,32.0) );

    BOOST_CHECK_EQUAL( exp2(I<double>(-0X1.A934F0979A372P+1,0X1.CEAECFEA8085AP+0)), I<double>(0X1.9999999999998P-4,0X1.C000000000001P+1) );
    BOOST_CHECK_EQUAL( exp2(I<double>(0X1.87F42B972949CP-1,0X1.8B55484710029P+6)), I<double>(0X1.B333333333332P+0,0X1.C81FD88228B4FP+98) );
    BOOST_CHECK_EQUAL( exp2(I<double>(0X1.78025C8B3FD39P+3,0X1.9FD8EEF3FA79BP+4)), I<double>(0X1.AEA0000721857P+11,0X1.FCA0555555559P+25)  );
}

BOOST_AUTO_TEST_CASE(minimal_exp10_test)
{
    BOOST_CHECK_EQUAL( exp10(I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( exp10(I<double>(-INF,0.0)),I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( exp10(I<double>(0.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( exp10(I<double>::entire()), I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( exp10(I<double>(-INF,0X1.34413509F79FFP+8)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( exp10(I<double>(0X1.34413509F79FFP+8)), I<double>(0X1.FFFFFFFFFFFFFP+1023,INF) );

    BOOST_CHECK_EQUAL( exp10(I<double>(0.0,0X1.34413509F79FEP+8)), I<double>(1.0,0X1.FFFFFFFFFFBA1P+1023) );
    BOOST_CHECK_EQUAL( exp10(I<double>(-0X1.33A7146F72A42P+8,0X1.34413509F79FEP+8)), I<double>(0.0,0X1.FFFFFFFFFFBA1P+1023) );
    BOOST_CHECK_EQUAL( exp10(I<double>(-0X1.22P+7,0X1.34413509F79FEP+8)), I<double>(0X1.3FAAC3E3FA1F3P-482,0X1.FFFFFFFFFFBA1P+1023) );
    BOOST_CHECK_EQUAL( exp10(I<double>(-0X1.22P+7,0.0)), I<double>(0X1.3FAAC3E3FA1F3P-482,1.0) );
    BOOST_CHECK_EQUAL( exp10(I<double>(-0X1.22P+7,1.0)), I<double>(0X1.3FAAC3E3FA1F3P-482,10.0) );

    BOOST_CHECK_EQUAL( exp10(I<double>(1.0,5.0)), I<double>(10.0,100000.0) );

    BOOST_CHECK_EQUAL( exp10(I<double>(-0X1.A934F0979A372P+1,0X1.CEAECFEA8085AP+0)), I<double>(0X1.F3A8254311F9AP-12,0X1.00B18AD5B7D56P+6) );
    BOOST_CHECK_EQUAL( exp10(I<double>(0X1.87F42B972949CP-1,0X1.8B55484710029P+6)), I<double>(0X1.75014B7296807P+2,0X1.3EEC1D47DFB2BP+328) );
    BOOST_CHECK_EQUAL( exp10(I<double>(0X1.78025C8B3FD39P+3,0X1.9FD8EEF3FA79BP+4)), I<double>(0X1.0608D2279A811P+39,0X1.43AF5D4271CB8P+86) );
}

BOOST_AUTO_TEST_CASE(minimal_log_test)
{
    BOOST_CHECK_EQUAL( log(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( log(I<double>(-INF,0.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( log(I<double>(0.0,1.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( log(I<double>(1.0,INF)), I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( log(I<double>(0.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( log(I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( log(I<double>(0.0,MAX)), I<double>(-INF,0X1.62E42FEFA39FP+9) );
    BOOST_CHECK_EQUAL( log(I<double>(1.0,MAX)), I<double>(0.0,0X1.62E42FEFA39FP+9) );
    BOOST_CHECK_EQUAL( log(I<double>(MIN,MAX)), I<double>(-0X1.6232BDD7ABCD3P+9,0X1.62E42FEFA39FP+9) );
    BOOST_CHECK_EQUAL( log(I<double>(MIN,1.0)), I<double>(-0X1.6232BDD7ABCD3P+9,0.0) );

    BOOST_CHECK_EQUAL( log(I<double>(0X1.5BF0A8B145769P+1)), I<double>(0X1.FFFFFFFFFFFFFP-1,0X1P+0) );
    BOOST_CHECK_EQUAL( log(I<double>(0X1.5BF0A8B14576AP+1)), I<double>(0X1P+0,0X1.0000000000001P+0) );

    BOOST_CHECK_EQUAL( log(I<double>(MIN,0X1.5BF0A8B14576AP+1)), I<double>(-0X1.6232BDD7ABCD3P+9,0X1.0000000000001P+0) );

    BOOST_CHECK_EQUAL( log(I<double>(0X1.5BF0A8B145769P+1,32.0)), I<double>(0X1.FFFFFFFFFFFFFP-1,0X1.BB9D3BEB8C86CP+1) );

    BOOST_CHECK_EQUAL( log(I<double>(0X1.999999999999AP-4,0X1.CP+1)), I<double>(-0X1.26BB1BBB55516P+1,0X1.40B512EB53D6P+0) );
    BOOST_CHECK_EQUAL( log(I<double>(0X1.B333333333333P+0,0X1.C81FD88228B2FP+98)), I<double>(0X1.0FAE81914A99P-1,0X1.120627F6AE7F1P+6) );
    BOOST_CHECK_EQUAL( log(I<double>(0X1.AEA0000721861P+11,0X1.FCA055555554CP+25)), I<double>(0X1.04A1363DB1E63P+3,0X1.203E52C0256B5P+4) );
}


BOOST_AUTO_TEST_CASE(minimal_log2_test)
{
    BOOST_CHECK_EQUAL( log2(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( log2(I<double>(-INF,0.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( log2(I<double>(0.0,1.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( log2(I<double>(1.0,INF)), I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( log2(I<double>(0.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( log2(I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( log2(I<double>(0.0,MAX)), I<double>(-INF,1024.0) );
    BOOST_CHECK_EQUAL( log2(I<double>(1.0,MAX)), I<double>(0.0,1024.0) );
    BOOST_CHECK_EQUAL( log2(I<double>(MIN,MAX)), I<double>(-1022.0,1024.0) );
    BOOST_CHECK_EQUAL( log2(I<double>(MIN,1.0)), I<double>(-1022.0,0.0) );
    BOOST_CHECK_EQUAL( log2(I<double>(MIN,2.0)), I<double>(-1022.0,1.0) );

    BOOST_CHECK_EQUAL( log2(I<double>(2.0,32.0)), I<double>(1.0,5.0) );

    BOOST_CHECK_EQUAL( log2(I<double>(0X1.999999999999AP-4,0X1.CP+1)), I<double>(-0X1.A934F0979A372P+1,0X1.CEAECFEA8085AP+0) );
    BOOST_CHECK_EQUAL( log2(I<double>(0X1.B333333333333P+0,0X1.C81FD88228B2FP+98)), I<double>(0X1.87F42B972949CP-1,0X1.8B55484710029P+6) );
    BOOST_CHECK_EQUAL( log2(I<double>(0X1.AEA0000721861P+11,0X1.FCA055555554CP+25)), I<double>(0X1.78025C8B3FD39P+3,0X1.9FD8EEF3FA79BP+4) );
}

BOOST_AUTO_TEST_CASE(minimal_log10_test)
{
    BOOST_CHECK_EQUAL( log10(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( log10(I<double>(-INF,0.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( log10(I<double>(0.0,1.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( log10(I<double>(1.0,INF)), I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( log10(I<double>(0.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( log10(I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( log10(I<double>(0.0,MAX)), I<double>(-INF,0X1.34413509F79FFP+8) );
    BOOST_CHECK_EQUAL( log10(I<double>(1.0,MAX)), I<double>(0.0,0X1.34413509F79FFP+8) );
    BOOST_CHECK_EQUAL( log10(I<double>(MIN,MAX)), I<double>(-0X1.33A7146F72A42P+8 ,0X1.34413509F79FFP+8) );
    BOOST_CHECK_EQUAL( log10(I<double>(MIN,1.0)), I<double>(-0X1.33A7146F72A42P+8 ,0.0) );
    BOOST_CHECK_EQUAL( log10(I<double>(MIN,10.0)), I<double>(-0X1.33A7146F72A42P+8 ,1.0) );

    BOOST_CHECK_EQUAL( log10(I<double>(10.0,100000.0)), I<double>(1.0,5.0) );

    BOOST_CHECK_EQUAL( log10(I<double>(0X1.999999999999AP-4,0X1.CP+1)), I<double>(-0X1P+0,0X1.1690163290F4P-1) );
    BOOST_CHECK_EQUAL( log10(I<double>(0X1.999999999999AP-4,0X1.999999999999AP-4)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( log10(I<double>(0X1.B333333333333P+0,0X1.C81FD88228B2FP+98)), I<double>(0X1.D7F59AA5BECB9P-3,0X1.DC074D84E5AABP+4) );
    BOOST_CHECK_EQUAL( log10(I<double>(0X1.AEA0000721861P+11,0X1.FCA055555554CP+25)), I<double>(0X1.C4C29DD829191P+1,0X1.F4BAEBBA4FA4P+2) );
}

BOOST_AUTO_TEST_CASE(minimal_sin_test)
{
    BOOST_CHECK_EQUAL( sin(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sin(I<double>(0.0,INF)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-INF,0.0)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>::entire()), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0.0)), I<double>(0.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D18P+0)), I<double>(0X1.FFFFFFFFFFFFFP-1,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D19P+0)), I<double>(0X1.FFFFFFFFFFFFFP-1,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+0)), I<double>(0X1.FFFFFFFFFFFFFP-1,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0.0,0X1.921FB54442D18P+0)), I<double>(0.0,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0.0,0X1.921FB54442D19P+0)), I<double>(0.0,0X1P+0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D18P+1)), I<double>(0X1.1A62633145C06P-53,0X1.1A62633145C07P-53) );
    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D19P+1)), I<double>(-0X1.72CECE675D1FDP-52,-0X1.72CECE675D1FCP-52) );
    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D18P+1,0X1.921FB54442D19P+1)), I<double>(-0X1.72CECE675D1FDP-52,0X1.1A62633145C07P-53) );
    BOOST_CHECK_EQUAL( sin(I<double>(0.0,0X1.921FB54442D18P+1)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0.0,0X1.921FB54442D19P+1)), I<double>(-0X1.72CECE675D1FDP-52,1.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D18P+1)), I<double>(0X1.1A62633145C06P-53,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+1)), I<double>(-0X1.72CECE675D1FDP-52,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D19P+0,0X1.921FB54442D18P+1)), I<double>(0X1.1A62633145C06P-53,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(0X1.921FB54442D19P+0,0X1.921FB54442D19P+1)), I<double>(-0X1.72CECE675D1FDP-52,0X1P+0) );

    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+0)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+0)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+0,-0X1.921FB54442D18P+0)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+0,0.0)), I<double>(-0X1P+0,0.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+0,0.0)), I<double>(-0X1P+0,0.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+1)), I<double>(-0X1.1A62633145C07P-53,-0X1.1A62633145C06P-53) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+1)), I<double>(0X1.72CECE675D1FCP-52,0X1.72CECE675D1FDP-52) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+1,-0X1.921FB54442D18P+1)), I<double>(-0X1.1A62633145C07P-53,0X1.72CECE675D1FDP-52) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+1,0.0)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+1,0.0)), I<double>(-1.0,0X1.72CECE675D1FDP-52) );

    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+1,-0X1.921FB54442D18P+0)), I<double>(-0X1P+0,-0X1.1A62633145C06P-53) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+1,-0X1.921FB54442D18P+0)), I<double>(-0X1P+0,0X1.72CECE675D1FDP-52) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+1,-0X1.921FB54442D19P+0)), I<double>(-0X1P+0,-0X1.1A62633145C06P-53) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+1,-0X1.921FB54442D19P+0)), I<double>(-0X1P+0,0X1.72CECE675D1FDP-52) );

    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+0,0X1.921FB54442D18P+0)), I<double>(-0X1P+0,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D18P+0,0X1.921FB54442D19P+0)), I<double>(-0X1P+0,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D18P+0)), I<double>(-0X1P+0,0X1P+0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D19P+0)), I<double>(-0X1P+0,0X1P+0) );

    BOOST_CHECK_EQUAL( sin(I<double>(-0.7,0.1)), I<double>(-0X1.49D6E694619B9P-1,0X1.98EAECB8BCB2DP-4) );
    BOOST_CHECK_EQUAL( sin(I<double>(1.0,2.0)), I<double>(0X1.AED548F090CEEP-1,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-3.2,-2.9)), I<double>(-0X1.E9FB8D64830E3P-3,0X1.DE33739E82D33P-5) );
    BOOST_CHECK_EQUAL( sin(I<double>(2.0,3.0)), I<double>(0X1.210386DB6D55BP-3,0X1.D18F6EAD1B446P-1) );
}

BOOST_AUTO_TEST_CASE(minimal_cos_test)
{
    BOOST_CHECK_EQUAL( cos(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( cos(I<double>(0.0,INF)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(-INF,0.0)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>::entire()), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( cos(I<double>(0.0)), I<double>(1.0) );

    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D18P+0)), I<double>(0X1.1A62633145C06P-54,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D19P+0)), I<double>(-0X1.72CECE675D1FDP-53,-0X1.72CECE675D1FCP-53) );
    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+0)), I<double>(-0X1.72CECE675D1FDP-53,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(0.0,0X1.921FB54442D18P+0)), I<double>(0X1.1A62633145C06P-54,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(0.0,0X1.921FB54442D19P+0)), I<double>(-0X1.72CECE675D1FDP-53,1.0) );

    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D18P+1)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D19P+1)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D18P+1,0X1.921FB54442D19P+1)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(0.0,0X1.921FB54442D18P+1)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(0.0,0X1.921FB54442D19P+1)), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D18P+1)), I<double>(-1.0,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+1)), I<double>(-1.0,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D19P+0,0X1.921FB54442D18P+1)), I<double>(-1.0,-0X1.72CECE675D1FCP-53) );
    BOOST_CHECK_EQUAL( cos(I<double>(0X1.921FB54442D19P+0,0X1.921FB54442D19P+1)), I<double>(-1.0,-0X1.72CECE675D1FCP-53) );

    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+0)), I<double>(0X1.1A62633145C06P-54,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+0)), I<double>(-0X1.72CECE675D1FDP-53,-0X1.72CECE675D1FCP-53) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+0,-0X1.921FB54442D18P+0)), I<double>(-0X1.72CECE675D1FDP-53,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+0,0.0)), I<double>(0X1.1A62633145C06P-54,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+0,0.0)), I<double>(-0X1.72CECE675D1FDP-53,1.0) );

    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+1)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+1)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+1,-0X1.921FB54442D18P+1)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+1,0.0)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+1,0.0)), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+1,-0X1.921FB54442D18P+0)), I<double>(-1.0,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+1,-0X1.921FB54442D18P+0)), I<double>(-1.0,0X1.1A62633145C07P-54) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+1,-0X1.921FB54442D19P+0)), I<double>(-1.0,-0X1.72CECE675D1FCP-53) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+1,-0X1.921FB54442D19P+0)), I<double>(-1.0,-0X1.72CECE675D1FCP-53) );

    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+0,0X1.921FB54442D18P+0)), I<double>(0X1.1A62633145C06P-54,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D18P+0,0X1.921FB54442D19P+0)), I<double>(-0X1.72CECE675D1FDP-53,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D18P+0)), I<double>(-0X1.72CECE675D1FDP-53,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D19P+0)), I<double>(-0X1.72CECE675D1FDP-53,1.0) );

    BOOST_CHECK_EQUAL( cos(I<double>(-0.7,0.1)), I<double>(0X1.87996529F9D92P-1,1.0) );
    BOOST_CHECK_EQUAL( cos(I<double>(1.0,2.0)), I<double>(-0X1.AA22657537205P-2,0X1.14A280FB5068CP-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(-3.2,-2.9)), I<double>(-1.0,-0X1.F1216DBA340C8P-1) );
    BOOST_CHECK_EQUAL( cos(I<double>(2.0,3.0)), I<double>(-0X1.FAE04BE85E5D3P-1,-0X1.AA22657537204P-2) );
}

BOOST_AUTO_TEST_CASE(minimal_tan_test)
{
    BOOST_CHECK_EQUAL( tan(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( tan(I<double>(0.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(-INF,0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( tan(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1.921FB54442D18P+0)), I<double>(0X1.D02967C31CDB4P+53,0X1.D02967C31CDB5P+53) );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1.921FB54442D19P+0)), I<double>(-0X1.617A15494767BP+52,-0X1.617A15494767AP+52) );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( tan(I<double>(0X1.921FB54442D18P+1)), I<double>(-0X1.1A62633145C07P-53,-0X1.1A62633145C06P-53) );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1.921FB54442D19P+1)), I<double>(0X1.72CECE675D1FCP-52,0X1.72CECE675D1FDP-52) );

    BOOST_CHECK_EQUAL( tan(I<double>(0.0,0X1.921FB54442D18P+0)), I<double>(0.0,0X1.D02967C31CDB5P+53) );
    BOOST_CHECK_EQUAL( tan(I<double>(0.0,0X1.921FB54442D19P+0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(0.0,0X1.921FB54442D18P+1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(0.0,0X1.921FB54442D19P+1)), I<double>::entire() );

    BOOST_CHECK_EQUAL( tan(I<double>(0X1P-51,0X1.921FB54442D18P+1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1P-51,0X1.921FB54442D19P+1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1P-52,0X1.921FB54442D18P+1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1P-52,0X1.921FB54442D19P+1)), I<double>::entire() );

    BOOST_CHECK_EQUAL( tan(I<double>(-0X1.921FB54442D18P+0,0X1.921FB54442D18P+0)), I<double>(-0X1.D02967C31CDB5P+53,0X1.D02967C31CDB5P+53) );
    BOOST_CHECK_EQUAL( tan(I<double>(-0X1.921FB54442D18P+0,0X1.921FB54442D19P+0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D18P+0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D19P+0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( tan(I<double>(-0X1.555475A31A4BEP-2,0X1.999999999999AP-4)), I<double>(-0X1.628F4FD931FEFP-2,0X1.9AF8877430B81P-4) );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1.4E18E147AE148P+12,0X1.4E2028F5C28F6P+12)), I<double>(-0X1.D6D67B035B6B4P+2,-0X1.7E42B0760E3F3P+0) );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1.4E18E147AE148P+12,0X1.546028F5C28F6P+12)), I<double>::entire() );
    BOOST_CHECK_EQUAL( tan(I<double>(0X1.FAE147AE147AEP-1,0X1.028F5C28F5C29P+0)), I<double>(0X1.860FADCC59064P+0,0X1.979AD0628469DP+0) );
}

BOOST_AUTO_TEST_CASE(minimal_asin_test)
{
    BOOST_CHECK_EQUAL( asin(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( asin(I<double>(0.0,INF)), I<double>(0.0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(-INF,0.0)), I<double>(-0X1.921FB54442D19P+0,0.0) );
    BOOST_CHECK_EQUAL( asin(I<double>::entire()), I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(-1.0,1.0)), I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(-INF,-1.0)), I<double>(-0X1.921FB54442D19P+0,-0X1.921FB54442D18P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(1.0,INF)), I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(-1.0)), I<double>(-0X1.921FB54442D19P+0,-0X1.921FB54442D18P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(1.0)), I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( asin(I<double>(-INF,-0X1.0000000000001P+0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( asin(I<double>(0X1.0000000000001P+0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( asin(I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-4)), I<double>(-0X1.9A49276037885P-4,0X1.9A49276037885P-4) );
    BOOST_CHECK_EQUAL( asin(I<double>(-0X1.51EB851EB851FP-2,0X1.FFFFFFFFFFFFFP-1)), I<double>(-0X1.585FF6E341C3FP-2,0X1.921FB50442D19P+0) );
    BOOST_CHECK_EQUAL( asin(I<double>(-0X1.FFFFFFFFFFFFFP-1,0X1.FFFFFFFFFFFFFP-1)), I<double>(-0X1.921FB50442D19P+0,0X1.921FB50442D19P+0) );
}

BOOST_AUTO_TEST_CASE(minimal_acos_test)
{
    BOOST_CHECK_EQUAL( acos(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( acos(I<double>(0.0,INF)), I<double>(0.0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( acos(I<double>(-INF,0.0)), I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+1) );
    BOOST_CHECK_EQUAL( acos(I<double>::entire()), I<double>(0.0,0X1.921FB54442D19P+1) );
    BOOST_CHECK_EQUAL( acos(I<double>(-1.0,1.0)), I<double>(0.0,0X1.921FB54442D19P+1) );
    BOOST_CHECK_EQUAL( acos(I<double>(-INF,-1.0)), I<double>(0X1.921FB54442D18P+1,0X1.921FB54442D19P+1) );
    BOOST_CHECK_EQUAL( acos(I<double>(1.0,INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( acos(I<double>(-1.0)), I<double>(0X1.921FB54442D18P+1,0X1.921FB54442D19P+1) );
    BOOST_CHECK_EQUAL( acos(I<double>(1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( acos(I<double>(0.0)), I<double>(0X1.921FB54442D18P+0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( acos(I<double>(-INF,-0X1.0000000000001P+0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( acos(I<double>(0X1.0000000000001P+0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( acos(I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-4)), I<double>(0X1.787B22CE3F59P+0,0X1.ABC447BA464A1P+0) );
    BOOST_CHECK_EQUAL( acos(I<double>(-0X1.51EB851EB851FP-2,0X1.FFFFFFFFFFFFFP-1)), I<double>(0X1P-26,0X1.E837B2FD13428P+0) );
    BOOST_CHECK_EQUAL( acos(I<double>(-0X1.FFFFFFFFFFFFFP-1,0X1.FFFFFFFFFFFFFP-1)), I<double>(0X1P-26,0X1.921FB52442D19P+1) );
}

BOOST_AUTO_TEST_CASE(minimal_atan_test)
{
    BOOST_CHECK_EQUAL( atan(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( atan(I<double>(0.0,INF)), I<double>(0.0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( atan(I<double>(-INF,0.0)), I<double>(-0X1.921FB54442D19P+0,0.0) );
    BOOST_CHECK_EQUAL( atan(I<double>::entire()), I<double>(-0X1.921FB54442D19P+0,0X1.921FB54442D19P+0) );
    BOOST_CHECK_EQUAL( atan(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( atan(I<double>(1.0,0X1.4C2463567C5ACP+25)), I<double>(0X1.921FB54442D18P-1,0X1.921FB4E19ABD7P+0) );
    BOOST_CHECK_EQUAL( atan(I<double>(-0X1.FD219490EAAC1P+38,-0X1.1AF1C9D74F06DP+9)), I<double>(-0X1.921FB54440CEBP+0,-0X1.91ABE5C1E4C6DP+0) );
}

BOOST_AUTO_TEST_CASE(minimal_atan2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sinh_test)
{
    BOOST_CHECK_EQUAL( sinh(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sinh(I<double>(0.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sinh(I<double>(-INF,0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( sinh(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( sinh(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( sinh(I<double>(1.0,0X1.2C903022DD7AAP+8)), I<double>(0X1.2CD9FC44EB982P+0,0X1.89BCA168970C6P+432) );
    BOOST_CHECK_EQUAL( sinh(I<double>(-0X1.FD219490EAAC1P+38,-0X1.1AF1C9D74F06DP+9)), I<double>(-INF,-0X1.53045B4F849DEP+815) );
    BOOST_CHECK_EQUAL( sinh(I<double>(-0X1.199999999999AP+0,0X1.2666666666666P+1)), I<double>(-0X1.55ECFE1B2B215P+0,0X1.3BF72EA61AF1BP+2) );
}

BOOST_AUTO_TEST_CASE(minimal_cosh_test)
{
    BOOST_CHECK_EQUAL( cosh(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( cosh(I<double>(0.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( cosh(I<double>(-INF,0.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( cosh(I<double>::entire()), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( cosh(I<double>(0.0)), I<double>(1.0) );

    BOOST_CHECK_EQUAL( cosh(I<double>(1.0,0X1.2C903022DD7AAP+8)), I<double>(0X1.8B07551D9F55P+0,0X1.89BCA168970C6P+432) );
    BOOST_CHECK_EQUAL( cosh(I<double>(-0X1.FD219490EAAC1P+38,-0X1.1AF1C9D74F06DP+9)), I<double>(0X1.53045B4F849DEP+815,INF) );
    BOOST_CHECK_EQUAL( cosh(I<double>(-0X1.199999999999AP+0,0X1.2666666666666P+1)), I<double>(1.0,0X1.4261D2B7D6181P+2) );
}

BOOST_AUTO_TEST_CASE(minimal_tanh_test)
{
    BOOST_CHECK_EQUAL( tanh(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( tanh(I<double>(0.0,INF)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( tanh(I<double>(-INF,0.0)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( tanh(I<double>::entire()), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( tanh(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( tanh(I<double>(1.0,0X1.2C903022DD7AAP+8)), I<double>(0X1.85EFAB514F394P-1,0X1P+0) );
    BOOST_CHECK_EQUAL( tanh(I<double>(-0X1.FD219490EAAC1P+38,-0X1.1AF1C9D74F06DP+9)), I<double>(-0X1P+0,-0X1.FFFFFFFFFFFFFP-1) );
    BOOST_CHECK_EQUAL( tanh(I<double>(-0X1.199999999999AP+0,0X1.2666666666666P+1)), I<double>(-0X1.99DB01FDE2406P-1,0X1.F5CF31E1C8103P-1) );
}

BOOST_AUTO_TEST_CASE(minimal_asinh_test)
{
    BOOST_CHECK_EQUAL( asinh(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( asinh(I<double>(0.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( asinh(I<double>(-INF,0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( asinh(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( asinh(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( asinh(I<double>(1.0,0X1.2C903022DD7AAP+8)), I<double>(0X1.C34366179D426P-1,0X1.9986127438A87P+2) );
    BOOST_CHECK_EQUAL( asinh(I<double>(-0X1.FD219490EAAC1P+38,-0X1.1AF1C9D74F06DP+9)), I<double>(-0X1.BB86380A6CC45P+4,-0X1.C204D8EB20827P+2) );
    BOOST_CHECK_EQUAL( asinh(I<double>(-0X1.199999999999AP+0,0X1.2666666666666P+1)), I<double>(-0X1.E693DF6EDF1E7P-1,0X1.91FDC64DE0E51P+0) );
}

BOOST_AUTO_TEST_CASE(minimal_acosh_test)
{
    BOOST_CHECK_EQUAL( acosh(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( acosh(I<double>(0.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( acosh(I<double>(1.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( acosh(I<double>(-INF,1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( acosh(I<double>(-INF,0X1.FFFFFFFFFFFFFP-1)), I<double>::empty() );
    BOOST_CHECK_EQUAL( acosh(I<double>::entire()), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( acosh(I<double>(1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( acosh(I<double>(1.0,0X1.2C903022DD7AAP+8)), I<double>(0.0,0X1.9985FB3D532AFP+2) );
    BOOST_CHECK_EQUAL( acosh(I<double>(0X1.199999999999AP+0,0X1.2666666666666P+1)), I<double>(0X1.C636C1A882F2CP-2,0X1.799C88E79140DP+0) );
    BOOST_CHECK_EQUAL( acosh(I<double>(0X1.14D4E82B2B26FP+15,0X1.72DBE91C837B5P+29)), I<double>(0X1.656510B4BAEC3P+3,0X1.52A415EE8455AP+4) );
}

BOOST_AUTO_TEST_CASE(minimal_atanh_test)
{
    BOOST_CHECK_EQUAL( atanh(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( atanh(I<double>(0.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( atanh(I<double>(1.0,INF)), I<double>::empty());
    BOOST_CHECK_EQUAL( atanh(I<double>(-INF,0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( atanh(I<double>(-INF,-1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( atanh(I<double>(-1.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( atanh(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( atanh(I<double>(-1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( atanh(I<double>(1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( atanh(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( atanh(I<double>(0X1.4C0420F6F08CCP-2,0X1.FFFFFFFFFFFFFP-1)), I<double>(0X1.5871DD2DF9102P-2,0X1.2B708872320E2P+4) );
    BOOST_CHECK_EQUAL( atanh(I<double>(-0X1.FFB88E9EB6307P-1,0X1.999999999999AP-4)), I<double>(-0X1.06A3A97D7979CP+2,0X1.9AF93CD234413P-4) );
}

BOOST_AUTO_TEST_CASE(minimal_sign_test)
{
    BOOST_CHECK_EQUAL( sign(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sign(I<double>(1.0,2.0)), I<double>(1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-1.0,2.0)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-1.0,0.0)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(0.0,2.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-5.0,-2.0)), I<double>(-1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-0.0,0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>::entire()), I<double>(-1.0,1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_ceil_test)
{
    BOOST_CHECK_EQUAL( ceil(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( ceil(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( ceil(I<double>(1.1,2.0)), I<double>(2.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.9,2.2)), I<double>(-1.0,3.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.0,2.2)), I<double>(-1.0,3.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.5,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-INF,2.2)), I<double>(-INF,3.0) );
}

BOOST_AUTO_TEST_CASE(minimal_floor_test)
{
    BOOST_CHECK_EQUAL( floor(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( floor(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( floor(I<double>(1.1,2.0)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.1,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.1,-0.4)), I<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.9,2.2)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.5,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( floor(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_trunc_test)
{
    BOOST_CHECK_EQUAL( trunc(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( trunc(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( trunc(I<double>(1.1,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.9,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.5,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_even_test)
{
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(1.1,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.9,2.2)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(1.5,2.1)), I<double>(2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.5,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.1,-0.5)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.9,2.5)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.5,2.5)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.5,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_away_test)
{
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(1.1,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.9,2.2)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(0.5,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-2.5,2.0)), I<double>(-3.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.1,-0.5)), I<double>(-1.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.9,2.5)), I<double>(-2.0,3.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.5,2.5)), I<double>(-2.0,3.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.5,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_abs_test)
{
    BOOST_CHECK_EQUAL( abs(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( abs(I<double>::entire()), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( abs(I<double>(1.1,2.1)), I<double>(1.1,2.1) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.1,2.0)), I<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.1,-0.4)), I<double>(0.4,1.1) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.9,0.2)), I<double>(0.0,1.9) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.5,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( abs(I<double>(-INF,-2.2)), I<double>(2.2,INF) );
}

BOOST_AUTO_TEST_CASE(minimal_min_test)
{
//TODO ist das so gedacht?
    BOOST_CHECK_EQUAL( min(I<double>::empty(),I<double>(1.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,2.0),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>::empty(),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>::entire(),I<double>(1.0,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,2.0),I<double>::entire()), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( min(I<double>::entire(),I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( min(I<double>::empty(),I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,5.0),I<double>(2.0,4.0)), I<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,5.0),I<double>(2.0,8.0)), I<double>(1.0,5.0) );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,5.0),I<double>::entire()), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( min(I<double>(-7.0,-5.0),I<double>(2.0,4.0)), I<double>(-7.0,-5.0) );
}

BOOST_AUTO_TEST_CASE(minimal_max_test)
{
//TODO ist das so gedacht?
    BOOST_CHECK_EQUAL( max(I<double>::empty(),I<double>(1.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,2.0),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>::empty(),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>::entire(),I<double>(1.0,2.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,2.0),I<double>::entire()), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( max(I<double>::entire(),I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( max(I<double>::empty(),I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,5.0),I<double>(2.0,4.0)), I<double>(2.0,5.0) );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,5.0),I<double>(2.0,8.0)), I<double>(2.0,8.0) );
    BOOST_CHECK_EQUAL( max(I<double>(-1.0,5.0),I<double>::entire()), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( max(I<double>(-7.0,-5.0),I<double>(2.0,4.0)), I<double>(2.0,4.0) );
}
