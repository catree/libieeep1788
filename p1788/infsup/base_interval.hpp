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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP


#include "p1788/infsup/forward_declaration.hpp"




//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class base_interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------




namespace p1788
{

namespace infsup
{


/// \brief Base class for a level 2 infsup interval
///
///
/// Base class representing a level 2 infsup interval, see P1788/D7.0 Sect. 4.1.
///
/// This class only serves as a uniform interface/representation of an
/// interval. All the behavior will be specified by the template policy class
/// Flavor<T> which implements the flavors concept of the standard in coherent way,
/// see P1788/D7.0 Sect. 5.
///
/// \tparam T                  Number system / parent format
/// \tparam Flavor<typename>   Generic flavor which will be instantiated with the
///                           number system T
/// \tparam RepType            Type of the internal representation
/// \tparam ConcreteInterval   Type of the concrete interval type (sub class)
///
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
class base_interval
{
//    static_assert(
//    std::is_same<typename Flavor<T>::representation, RepType>::value
//        || std::is_same<typename Flavor<T>::representation_dec, RepType>::value,
//        "Representation is not supported!");
//
//    static_assert(p1788::util::is_infsup_base_interval_implementation<ConcreteInterval>::value, "Concrete interval type is not supported!");
//
//    static_assert(std::is_same<typename ConcreteInterval::bound_type, T>::value, "Bound types are different!");
//
//    static_assert(std::is_same<typename ConcreteInterval::flavor_type, Flavor<T>>::value, "Flavor types are different!");



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// public
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


public:

    typedef T bound_type;

    typedef Flavor<T> flavor_type;

    typedef RepType representation_type;


// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


    // \brief Foo Bar baz
    // Implementation specific
    // \return T
    //
    //
    T lower() const {
        return Flavor<T>::method_lower(rep_);
    }

// Implementation specific
    T upper() const {
        return Flavor<T>::method_upper(rep_);
    }

// Implementation specific
    T mid() const {
        return Flavor<T>::method_mid(rep_);
    }

// Implementation specific
    T rad() const {
        return Flavor<T>::method_rad(rep_);
    }


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// protected
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

protected:


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

    explicit base_interval(representation_type const& rep) : rep_(rep)
    { }


// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

    static ConcreteInterval concrete_interval(representation_type rep) {
        return ConcreteInterval(rep);
    }

// -----------------------------------------------------------------------------
// Members
// -----------------------------------------------------------------------------

    representation_type rep_;



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Friends
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

    template<typename, template<typename> class, typename, class>
    friend class base_interval;

    template<typename, template<typename> class>
    friend class interval;

    template<typename, template<typename> class>
    friend class decorated_interval;



public:

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Operations on intervals (Friends)
// Corresponding mixed-type operations (static members)
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// IO operators
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_, typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_, typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_>&);


// -----------------------------------------------------------------------------
// Non-arithmetic set operations
// -----------------------------------------------------------------------------

///@name Set operations
///
///
///@{


// \brief Intersection of two intervals <B>x</B> and <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// The intersection of two intervals <B>x</B>  and <B>y</B> is defined as:
// \f[
//    \mathbf{x} \cap \mathbf{y}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::intersect(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #intersect(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \return intersection of <B>x</B>  and <B>y</B>
//


    /// \todo Docu, Test
    ///
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_
    intersect(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T1_, typename RepType1_, class ConcreteInterval1_, typename T2_, typename RepType2_, class ConcreteInterval2_>
    static ConcreteInterval
    intersect(base_interval<T1_, Flavor, RepType1_, ConcreteInterval1_> const&, base_interval<T2_, Flavor, RepType2_, ConcreteInterval2_> const&);


// \brief Interval hull of two intervals <B>x</B> and <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// The interval hull of two intervals <B>x</B>  and <B>y</B> is defined as:
// \f[
//    \operatorname{hull}(\mathbf{x} \cup\mathbf{y})
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::intersect(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #hull(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \return interval hull of <B>x</B>  and <B>y</B>
//

    /// \todo Docu, Test
    ///
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_
    hull(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T1_, typename RepType1_, class ConcreteInterval1_, typename T2_, typename RepType2_, class ConcreteInterval2_>
    static ConcreteInterval
    hull(base_interval<T1_, Flavor, RepType1_, ConcreteInterval1_> const&, base_interval<T2_, Flavor, RepType2_, ConcreteInterval2_> const&);


///@}


// -----------------------------------------------------------------------------
// Numeric functions on intervals
// -----------------------------------------------------------------------------

///@name Numeric functions on intervals
///
///
///@{


    /// \brief Infimum of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::inf(representation const& x)</c>
    /// or <c>Flavor<T>::inf(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li \f$+\infty\f$ if \p x is empty
    ///         \li -0 if the lower bound of \p x is zero
    ///         \li lower bound of \p x otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::inf(representation const& x) mpfr_bin_ieee754_flavor::inf(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::inf(representation_dec const& x) mpfr_bin_ieee754_flavor::inf(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ inf(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x);

    /// \brief Mixed-type version of the infimum of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::inf(representation_type<T_> const& x)</c>
    /// or <c>Flavor<T>::inf(representation_dec_type<T_> const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li \f$+\infty\f$ if \p x is empty
    ///         \li -0 if the lower bound of \p x is zero
    ///         \li lower bound of \p x otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::inf(representation_type<T_> const& x) mpfr_bin_ieee754_flavor::inf(representation_type<T_> const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::inf(representation_dec_type<T_> const& x) mpfr_bin_ieee754_flavor::inf(representation_dec_type<T_> const& x) \endlink</c>
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static T inf(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);



    /// \brief Supremum of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::sup(representation const& x)</c>
    /// or <c>Flavor<T>::sup(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li \f$-\infty\f$ if \p x is empty
    ///         \li +0 if the upper bound of \p x is zero
    ///         \li upper bound of \p x otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::sup(representation const& x) mpfr_bin_ieee754_flavor::sup(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::sup(representation_dec const& x) mpfr_bin_ieee754_flavor::sup(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ sup(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x);

    /// \brief Mixed-type version of the supremum of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::sup(representation_type<T_> const& x)</c>
    /// or <c>Flavor<T>::sup(representation_dec_type<T_> const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li \f$-\infty\f$ if \p x is empty
    ///         \li +0 if the upper bound of \p x is zero
    ///         \li upper bound of \p x otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::sup(representation_type<T_> const& x) mpfr_bin_ieee754_flavor::sup(representation_type<T_> const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::sup(representation_dec_type<T_> const& x) mpfr_bin_ieee754_flavor::sup(representation_dec_type<T_> const& x) \endlink</c>
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static T sup(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    /// \brief Midpoint of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::mid(representation const& x)</c>
    /// or <c>Flavor<T>::mid(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li NaN if \p x is empty
    ///         \li +0 if \p x is entire
    ///         \li finite negative number with largest magnitude of type \p T if  \f$\underline{x} = -\infty\f$ and \f$\overline{x}\f$ is finite
    ///         \li finite positive number with largest magnitude of type \p T if \f$\underline{x}\f$ is finite and \f$\overline{x} = +\infty\f$
    ///         \li \f$(\underline{x} + \overline{x}) / 2\f$ rounded to the nearest number of type \p T if \f$\underline{x}, \overline{x}\f$ are both finite.
    ///              It returns +0.0 in case of a zero
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mid(representation const& x) mpfr_bin_ieee754_flavor::mid(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mid(representation_dec const& x) mpfr_bin_ieee754_flavor::mid(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ mid(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static T mid(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const&);


    /// \brief Radius of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::rad(representation const& x)</c>
    /// or <c>Flavor<T>::rad(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li NaN if \p x is empty
    ///         \li smallest number of type \p T such that \f$mid(x) - rad(x) \leq \underline{x}\f$ and \f$\overline{x} \leq mid(x) + rad(x)\f$, otherwise.
    ///              It returns +0.0 in case of a zero
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::rad(representation const& x) mpfr_bin_ieee754_flavor::rad(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::rad(representation_dec const& x) mpfr_bin_ieee754_flavor::rad(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ rad(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static T rad(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const&);


    /// \brief Midpoint and radius of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::mid_rad(representation const& x)</c>
    /// or <c>Flavor<T>::mid_rad(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return <c>std::pair<T,T></c> containing the results of
    /// <c>\link mid(p1788::infsup::base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x) mid\endlink</c>
    /// and <c>\link rad(p1788::infsup::base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x) rad\endlink</c>
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mid_rad(representation const& x) mpfr_bin_ieee754_flavor::mid_rad(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mid_rad(representation_dec const& x) mpfr_bin_ieee754_flavor::mid_rad(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend std::pair<T_, T_> mid_rad(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static std::pair<T, T> mid_rad(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const&);


    /// \brief Width of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::wid(representation const& x)</c>
    /// or <c>Flavor<T>::wid(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li NaN if \p x is empty
    ///         \li \f$\overline{x} -\underline{x}\f$ rounded upward, otherwise.
    ///              It returns +0.0 in case of a zero
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::wid(representation const& x) mpfr_bin_ieee754_flavor::wid(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::wid(representation_dec const& x) mpfr_bin_ieee754_flavor::wid(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ wid(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static T wid(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const&);


    /// \brief Magnitude of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::mag(representation const& x)</c>
    /// or <c>Flavor<T>::mag(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li NaN if \p x is empty
    ///         \li \f$ sup \{ |x| \mid x \in \mathbf{x} \}\f$  rounded upward, otherwise.
    ///              It returns +0.0 in case of a zero
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mag(representation const& x) mpfr_bin_ieee754_flavor::mag(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mag(representation_dec const& x) mpfr_bin_ieee754_flavor::mag(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ mag(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static T mag(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const&);


    /// \brief Mignitude of an interval \p x
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::mig(representation const& x)</c>
    /// or <c>Flavor<T>::mig(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \return \li NaN if \p x is NaI
    ///         \li NaN if \p x is empty
    ///         \li \f$ inf \{ |x| \mid x \in \mathbf{x} \}\f$  rounded downward, otherwise.
    ///              It returns +0.0 in case of a zero
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mig(representation const& x) mpfr_bin_ieee754_flavor::mig(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::mig(representation_dec const& x) mpfr_bin_ieee754_flavor::mig(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ mig(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    /// \brief Mixed-type
    /// \todo Docu, Test
    ///
    ///
    template<typename T_, typename RepType_, class ConcreteInterval_>
    static T mig(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const&);

///@}


// -----------------------------------------------------------------------------
// Boolean functions on intervals
// -----------------------------------------------------------------------------

///@name Boolean functions on intervals
///
///
///@{

    /// \brief Checks if an interval \p x is the empty set
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::is_empty(representation const& x)</c>
    /// or <c>Flavor<T>::is_empty(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \retval true    \p x is the empty set
    /// \retval false   otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::is_empty(representation const& x) mpfr_bin_ieee754_flavor::is_empty(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::is_empty(representation_dec const& x) mpfr_bin_ieee754_flavor::is_empty(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_empty(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x);

    /// \brief Checks if an interval \p x is the entire set
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::is_entire(representation const& x)</c>
    /// or <c>Flavor<T>::is_entire(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param  x   interval
    /// \retval true    \p x is the entire set
    /// \retval false   otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::is_entire(representation const& x) mpfr_bin_ieee754_flavor::is_entire(representation const& x) \endlink</c>
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::is_entire(representation_dec const& x) mpfr_bin_ieee754_flavor::is_entire(representation_dec const& x) \endlink</c>
    ///
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_entire(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x);

// \brief Check if two intervals <B>x</B> and <B>y</B> are equal
//
// <B>Required by IEEE P1788</B>
//
// Two intervals <B>x</B> and <B>y</B> are equal if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x = y  \,
//     \wedge \, \forall_{y \in \mathbf{y}}\exists_{x \in \mathbf{x}} \, y = x
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::is_equal(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #is_equal(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> and <B>y</B> are equal
// \retval false   otherwise
//
//    /// \todo Docu, Test
//    ///
//    ///
template<typename T_, typename RepType_, class ConcreteInterval_>
static bool is_equal(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool operator==(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& y);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool operator!=(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& y);


//    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
//    friend bool is_equal(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);
//
//    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
//    friend bool operator==(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);
//
//    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
//    friend bool operator!=(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);


// \brief Check if intervals <B>x</B> is a subset of interval <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// An interval <B>x</B> is a subset of an interval <B>y</B> if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x = y
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::subset(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #subset(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> is subset of <B>y</B>
// \retval false   otherwise
//
    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool subset(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool superset(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

// \brief Check if intervals <B>x</B> is weakly less then interval <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// An interval <B>x</B> is weakly less then an interval <B>y</B> if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x \leq y  \,
//     \wedge \, \forall_{y \in \mathbf{y}}\exists_{x \in \mathbf{x}} \, x \leq y
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::less(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #less(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> is weakly less then <B>y</B>
// \retval false   otherwise
//
    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool less(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool greater(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

// \brief Check if intervals <B>x</B> is to left of but may touch interval <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// An interval <B>x</B> is to left of but may touch an interval <B>y</B> if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\forall_{y \in \mathbf{y}} \, x \leq y
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::precedes(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #precedes(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> is to left of but may touch <B>y</B>
// \retval false   otherwise
//
    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool precedes(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool succeeds(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);


// \brief Check if intervals <B>x</B> is interior to interval <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// An interval <B>x</B> is interior to an interval <B>y</B> if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x < y  \,
//     \wedge \, \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, y < x
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::is_interior(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #is_interior(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> is interior to <B>y</B>
// \retval false   otherwise
//
    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool is_interior(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool contains_interior(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

// \brief Check if intervals <B>x</B> is strictly less then interval <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// An interval <B>x</B> is strictly less then an interval <B>y</B> if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x < y  \,
//     \wedge \, \forall_{y \in \mathbf{y}}\exists_{x \in \mathbf{x}} \, x < y
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::strictly_less(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #strictly_less(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> is strictly less then <B>y</B>
// \retval false   otherwise
//
    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool strictly_less(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool strictly_greater(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

// \brief Check if intervals <B>x</B> is strictly to left of interval <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// An interval <B>x</B> is strictly to left of an interval <B>y</B> if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\forall_{y \in \mathbf{y}} \, x < y
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::strictly_precedes(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #strictly_precedes(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> is strictly to left of <B>y</B>
// \retval false   otherwise
//
    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool strictly_precedes(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool strictly_succeeds(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

// \brief Check if intervals <B>x</B> and interval <B>y</B> are disjoint
//
// <B>Required by IEEE P1788</B>
//
// The intervals <B>x</B> and <B>y</B> are disjoint if the condition
// \f[
//     \forall_{x \in \mathbf{x}}\forall_{y \in \mathbf{y}} \, x \not= y
// \f]
// is fulfilled.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::are_disjoint(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #are_disjoint(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \retval true    <B>x</B> and <B>y</B> are disjoint
// \retval false   otherwise
//
    /// \todo Docu, Test
    ///
    ///
    template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
    friend bool are_disjoint(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y);

///@}

// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pos(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ neg(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ add (base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sub(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ mul(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ recip(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqr(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqrt(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ fma(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                 base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                 base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

//TODO notwendig?
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ interval_case(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                           base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                           base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pown(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int p);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp10(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log10(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asin(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ acos(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sinh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tanh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asinh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ acosh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atanh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sign(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ ceil(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ floor(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ trunc(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ round_ties_to_even(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ round_ties_to_away(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ abs(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ min(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ max(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
//  Recommended div to pair function
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend std::pair<ConcreteInterval_, ConcreteInterval_>
    div_to_pair(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Reverse elementary functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqr_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqr_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ recip_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ recip_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ abs_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ abs_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pown_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pown_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ mul_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                       base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                       base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ mul_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cancel_plus(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cancel_minus(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended boolean functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_common(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_singleton(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_member(T_ m, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ rootn(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ expm1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp2m1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp10m1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ logp1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log2p1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log10p1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ compoundm1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ hypot(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ r_sqrt(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asin_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ acos_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended interval overlapping
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend p1788::overlapping::overlapping_state overlap(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
            base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended slope functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp_slope1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log_slope1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asin_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sinh_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


};


// funktionen
template<typename T1_, template<typename> class Flavor1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, template<typename> class Flavor2_, typename RepType2_, class ConcreteInterval2_>
bool is_equal(base_interval<T1_, Flavor1_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor2_, RepType2_, ConcreteInterval2_> const& y);








} // namespace infsup

} // namespace p1788


#include "p1788/infsup/base_interval_io_impl.hpp"
#include "p1788/infsup/base_interval_set_op_impl.hpp"
#include "p1788/infsup/base_interval_num_func_impl.hpp"
#include "p1788/infsup/base_interval_bool_func_impl.hpp"
#include "p1788/infsup/base_interval_elem_func_impl.hpp"
#include "p1788/infsup/base_interval_div_pair_func_impl.hpp"
#include "p1788/infsup/base_interval_rev_elem_func_impl.hpp"
#include "p1788/infsup/base_interval_cancel_func_impl.hpp"
#include "p1788/infsup/base_interval_rec_bool_func_impl.hpp"
#include "p1788/infsup/base_interval_rec_elem_func_impl.hpp"
#include "p1788/infsup/base_interval_rec_overlap_impl.hpp"
#include "p1788/infsup/base_interval_rec_slope_func_impl.hpp"

#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP
