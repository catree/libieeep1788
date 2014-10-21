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

#include <iostream>

#include "p1788/p1788.hpp"
#include <mpfr.h>
#include <limits>

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

int main()
{

using namespace p1788::infsup;


    I<double> id_a(-1.0,2.0), id_b(3.0,4.0), id_c(1.0,6.0);
    I<float> if_a(1.0f,2.0f), if_b(3.0f,4.0f), if_c(5.0f,6.0f);
    DI<double> dd_a(-1.0,2.0), dd_b(3.0,4.0), dd_c(1.0,6.0);
    DI<float> df_a(1.0f,2.0f), df_b(3.0f,4.0f), df_c(5.0f,6.0f);
//    std::cout << d_a << std::endl;
//    std::cout << d_a.rad() << std::endl;
//    std::cout << d_a.decoration() << std::endl;


//    p1788::decoration::decoration dec = p1788::decoration::decoration::trv;
//
//    std::cin >> dec;
//    std::cout << dec << std::endl;

    I<float> x = static_cast<I<float>>(id_a);
    std::cout << x << std::endl;
    I<double> y = static_cast<I<double>>(if_a);
    std::cout << y << std::endl;
    I<float> z(id_a);
    std::cout << z << std::endl << std::endl;

    std::cout << intersect(id_a, id_c) << std::endl;
    std::cout << I<float>::intersect(id_a, if_a) << std::endl;
    std::cout << intersect(dd_a, dd_c) << std::endl;
    std::cout << DI<float>::intersect(dd_a, df_a) << std::endl;

    std::cout << hull(id_a, id_c) << std::endl;
    std::cout << I<float>::hull(id_a, if_a) << std::endl;
    std::cout << hull(dd_a, dd_c) << std::endl;
    std::cout << DI<float>::hull(dd_a, df_a) << std::endl << std::endl;

    I<double> a(0.0,  std::numeric_limits<double>::infinity());
    double m = mid(a);
    double r = rad(a);
    //I<double> b = I<double>(m) + I<double>(-r,r);

    //std::cout << b << std::endl;
    //std::cout << subset(a,b) << std::endl;


    printf("%f %A\n\n", m, m);
    printf("%f %A\n\n", r, r);
    //std::cout << (0X1.FFFFFFFFFFFFFP+1023 - 0X1.FFFFFFFFFFFFCP+1023) / 2 << std::endl;



//
//    std::cout << inf(d_a) << std::endl;
//    std::cout << sup(d_a) << std::endl;
//    std::cout << mid_rad(d_a).first << std::endl;
//    std::cout << mid_rad(d_a).second << std::endl;
//    std::cout << is_empty(d_a) << std::endl;
//    std::cout << is_equal(d_a, d_b) << std::endl;
//    std::cout << (d_a != d_b) << std::endl;
//    std::cout << less(d_a, d_b) << std::endl;
//    std::cout << subset(d_a, d_b) << std::endl;
//
//    std::cout << d_a + d_b << std::endl;
//    std::cout << div(d_a, d_b) << std::endl;
//    std::cout << sin(d_a) << std::endl;
//
//    std::cout << div_to_pair(d_a, d_b).first << std::endl;
//    std::cout << div_to_pair(d_a, d_b).second << std::endl;
//    std::cout << div_to_pair(d_b, d_a).first << std::endl;
//    std::cout << div_to_pair(d_b, d_a).second << std::endl;
//
//    std::cout << sqr_rev(d_b) << std::endl;
//    std::cout << sin_rev(d_b) << std::endl;
//
//    std::cout << cancel_plus(d_b, d_a) << std::endl;
//    std::cout << cancel_minus(d_b, d_a) << std::endl;
//
//    std::cout << is_singleton(d_b) << std::endl;
//    std::cout << is_member(5.1, d_b) << std::endl;
//
//    std::cout << rootn(d_b, 3) << std::endl;
//    std::cout << expm1(d_b) << std::endl;
//    std::cout << compoundm1(d_a, d_b) << std::endl;
//
//    std::cout << static_cast<int>(overlap(d_a, d_b)) << std::endl;
//
//    std::cout << log_slope2(d_a) << std::endl;
//    std::cout << asin_slope3(d_a) << std::endl;
//
//
//    std::cout << add<I<double>>(f_a, d_b) << std::endl;
//    std::cout << sqrt<I<double>>(f_a) << std::endl;
//    std::cout << fma<I<double>>(f_a, d_b, d_a) << std::endl;
}
