// TODO: Add licence
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: $
// $Id: $
// 
//
// Author(s)     : Michael Hemmer <mhemmer@uni-mainz.de>
//
// ============================================================================

// TODO: The comments are all original EXACUS comments and aren't adapted. So
//         they may be wrong now.

/*! \file NiX/Coercion_traits.h
 *  \brief Defines class NiX::Coercion_traits. 
 * 
 *  Provides the general definition of the \c Coercion_traits<A,B> class, with
 *  specializations for the builtin number types.
 */

#ifndef CGAL_COERCION_TRAITS_H
#define CGAL_COERCION_TRAITS_H 1

//#include <NiX/basic.h>
//#include <NiX/NT_traits.h> 
#include <CGAL/basic.h>
//#include <CGAL/LiS/basic.h>
#include <iterator>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/if.hpp>

//#include <NiX/Polynomial.h>
//#include <NiX/Sqrt_extension.h>

// Makro to define an additional operator for binary functors which takes
// two number types as parameters that are interoperable with the
// number type
#define CGAL_IMPLICIT_INTEROPERABLE_BINARY_OPERATOR_WITH_RT( NT, Result_type  )    \
  template < class NT1, class NT2 >                                        \
  Result_type operator()( const NT1& x, const NT2& y ) const {             \
    BOOST_STATIC_ASSERT((::boost::is_same<                                 \
          typename Coercion_traits< NT1, NT2 >::Coercion_type, NT          \
                                         >::value));                       \
                                                                           \
    typename Coercion_traits< NT1, NT2 >::Cast cast;                       \
    return operator()( cast(x), cast(y) );                                 \
  }

#define CGAL_IMPLICIT_INTEROPERABLE_BINARY_OPERATOR( NT ) \
CGAL_IMPLICIT_INTEROPERABLE_BINARY_OPERATOR_WITH_RT( NT, NT )

#define CGAL_DEFINE_COERCION_TRAITS_FROM_TO(FROM,TO)                    \
    template <>                                                         \
    struct Coercion_traits< FROM , TO >{                                    \
        typedef CGAL::Tag_true  Are_explicit_interoperable;             \
        typedef CGAL::Tag_true  Are_implicit_interoperable;             \
        typedef TO Coercion_type;                                       \
        struct Cast{                                                    \
            typedef Coercion_type result_type;                          \
            Coercion_type operator()(const TO& x)   const { return x;}  \
            Coercion_type operator()(const FROM& x) const {             \
                return Coercion_type(x);}                               \
        };                                                              \
    };                                                                  \
    template <>                                                         \
    struct Coercion_traits< TO , FROM >{                                    \
        typedef CGAL::Tag_true  Are_explicit_interoperable;             \
        typedef CGAL::Tag_true  Are_implicit_interoperable;             \
        typedef TO Coercion_type;                                       \
        struct Cast{                                                    \
            typedef Coercion_type result_type;                          \
            Coercion_type operator()(const TO& x)   const { return x;}  \
            Coercion_type operator()(const FROM& x) const {             \
                return Coercion_type(x);}                               \
        };                                                              \
    };      

#define CGAL_DEFINE_COERCION_TRAITS_FROM_TO_TEM(FROM,TO,TEM)            \
    template <TEM>                                                      \
    struct Coercion_traits< FROM , TO >{                                    \
        typedef CGAL::Tag_true  Are_explicit_interoperable;             \
        typedef CGAL::Tag_true  Are_implicit_interoperable;             \
        typedef TO Coercion_type;                                       \
        struct Cast{                                                    \
            typedef Coercion_type result_type;                          \
            Coercion_type operator()(const TO& x)   const { return x;}  \
            Coercion_type operator()(const FROM& x) const {             \
                return Coercion_type(x);}                               \
        };                                                              \
    };                                                                  \
    template <TEM>                                                      \
    struct Coercion_traits< TO , FROM >{                                    \
        typedef CGAL::Tag_true  Are_explicit_interoperable;             \
        typedef CGAL::Tag_true  Are_implicit_interoperable;             \
        typedef TO Coercion_type;                                       \
        struct Cast{                                                    \
            typedef Coercion_type result_type;                          \
            Coercion_type operator()(const TO& x)   const { return x;}  \
            Coercion_type operator()(const FROM& x) const {             \
                return Coercion_type(x);}                               \
        };                                                              \
    };   

                                                 

#define CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(A)                         \
    template <>                                                         \
    struct Coercion_traits< A , A >{                                        \
        typedef CGAL::Tag_true  Are_explicit_interoperable;             \
        typedef CGAL::Tag_true  Are_implicit_interoperable;             \
        typedef A Coercion_type;                                        \
        struct Cast{                                                    \
            typedef Coercion_type result_type;                          \
            Coercion_type operator()(const A& x) const { return x;}     \
        };                                                              \
    };    

#define CGAL_DEFINE_COERCION_TRAITS_FOR_SELF_TEM(A,TEM)                 \
    template <TEM>                                                      \
    struct Coercion_traits< A , A >{                                        \
        typedef CGAL::Tag_true  Are_explicit_interoperable;             \
        typedef CGAL::Tag_true  Are_implicit_interoperable;             \
        typedef A Coercion_type;                                        \
        struct Cast{                                                    \
            typedef Coercion_type result_type;                          \
            Coercion_type operator()(const A& x) const {return x;}      \
        };                                                              \
    };    

CGAL_BEGIN_NAMESPACE


namespace INTERN_CT{ 
template< class FROM, class TO >struct Cast_from_to{
    typedef TO result_type;
    TO operator()(const TO& x){return x;}
    TO operator()(const FROM& x){return TO(x);}
};
template< class TO>
struct Cast_from_to<TO,TO>{
    typedef TO result_type;
    TO operator()(const TO& x){return x;}
};
}


template<class A , class B> class Coercion_traits;
template<class A , class B, int > class Coercion_traits_for_level;
    


CGAL_DEFINE_COERCION_TRAITS_FROM_TO(short,int);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(short,long);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(short,long long);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(short,float);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(short,double);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(short,long double);
        
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(int,long);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(int,long long);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(int,float);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(int,double);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(int,long double);

CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long,long long);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long,float);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long,double);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long,long double);

CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long long,float);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long long,double);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long long,long double);

CGAL_DEFINE_COERCION_TRAITS_FROM_TO(float,double);
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(float,long double);
      
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(double,long double);

//! Specialization for equal types.
template <class A>    
struct Coercion_traits<A,A>{ 
    typedef CGAL::Tag_true  Are_explicit_interoperable;
    typedef CGAL::Tag_false Are_implicit_interoperable;
    typedef A Coercion_type; 
    struct Cast{                                        
        typedef Coercion_type result_type;                             
        Coercion_type inline operator()(const A& x) const { 
            return x;
        }       
    };
};
    
CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(short);
CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(int);   
CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(long);
CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(long long);
CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(float);
CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(double);
CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(long double);

enum COERCION_TRAITS_LEVEL {
    CTL_TOP          = 4,
    CTL_POLYNOMIAL   = 4, 
    CTL_COMPLEX      = 3,
    CTL_INTERVAL     = 2,
    CTL_SQRT_EXT     = 1 
};

template <class A, class B, int i > 
class Coercion_traits_for_level: public Coercion_traits_for_level<A,B,i-1>{};

template <class A, class B> 
class Coercion_traits_for_level<A,B,0> {
public:
    typedef CGAL::Tag_false Are_explicit_interoperable;
    typedef CGAL::Tag_false Are_implicit_interoperable;
    typedef void               Coercion_type;
    typedef CGAL::Null_functor Cast;
};

template<class A , class B> 
class Coercion_traits :public Coercion_traits_for_level<A,B,CTL_TOP>{};

 
CGAL_END_NAMESPACE

#endif //NiX_COERCION_TRAITS_H
