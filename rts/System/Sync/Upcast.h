/* Author: Tobi Vollebregt */

#ifndef UPCAST_H
#define UPCAST_H

// for Sint64, Uint64
#include <SDL_types.h>

namespace upcast {
	template<class T> struct UnaryUpcast {};
	template<class U, class V> struct BinaryUpcast {};

	/* To reduce size of the BinaryUpcast matrix, UnaryUpcast small types
	to (unsigned) int before attempting to BinaryUpcast them. */
	template<> struct UnaryUpcast<          bool  > { typedef   signed int  type; };
	template<> struct UnaryUpcast<   signed char  > { typedef   signed int  type; };
	template<> struct UnaryUpcast<   signed short > { typedef   signed int  type; };
	template<> struct UnaryUpcast<   signed int   > { typedef   signed int  type; };
	template<> struct UnaryUpcast<   signed long  > { typedef   signed long type; };
	template<> struct UnaryUpcast< unsigned char  > { typedef   signed int  type; };
	template<> struct UnaryUpcast< unsigned short > { typedef   signed int  type; };
	template<> struct UnaryUpcast< unsigned int   > { typedef unsigned int  type; };
	template<> struct UnaryUpcast< unsigned long  > { typedef unsigned long type; };
	template<> struct UnaryUpcast<          float > { typedef         float type; };
	template<> struct UnaryUpcast<         double > { typedef        double type; };
	template<> struct UnaryUpcast<    long double > { typedef   long double type; };
	template<> struct UnaryUpcast<         Sint64 > { typedef        Sint64 type; };
	template<> struct UnaryUpcast<         Uint64 > { typedef        Uint64 type; };

#define UPCAST1(U, V, W) \
	template<> struct BinaryUpcast<U,V> { typedef W type; }
#define UPCAST2(U, V, W) \
	template<> struct BinaryUpcast<U,V> { typedef W type; }; \
	template<> struct BinaryUpcast<V,U> { typedef W type; }

	/* Note: this was checked using GCC 4 on AMD64 */
	/*           param1    +    param2    --> return type  */
	UPCAST1(   signed int  ,   signed int  ,   signed int  );
	UPCAST2(   signed int  ,   signed long ,   signed int  );
	UPCAST2(   signed int  , unsigned int  , unsigned int  );
	UPCAST2(   signed int  , unsigned long , unsigned long );
	UPCAST2(   signed int  ,        Sint64 ,        Sint64 );
	UPCAST2(   signed int  ,        Uint64 ,        Uint64 );
	UPCAST2(   signed int  ,         float ,         float );
	UPCAST2(   signed int  ,        double ,        double );
	UPCAST2(   signed int  ,   long double ,   long double );
	UPCAST1(   signed long ,   signed long ,   signed long );
	UPCAST2(   signed long , unsigned int  ,   signed long );
	UPCAST2(   signed long , unsigned long , unsigned long );
	UPCAST2(   signed long ,        Sint64 ,        Sint64 );
	UPCAST2(   signed long ,        Uint64 ,        Uint64 );
	UPCAST2(   signed long ,         float ,         float );
	UPCAST2(   signed long ,        double ,        double );
	UPCAST2(   signed long ,   long double ,   long double );
	UPCAST1( unsigned int  , unsigned int  , unsigned int  );
	UPCAST2( unsigned int  , unsigned long , unsigned long );
	UPCAST2( unsigned int  ,        Sint64 ,        Sint64 );
	UPCAST2( unsigned int  ,        Uint64 ,        Uint64 );
	UPCAST2( unsigned int  ,         float ,         float );
	UPCAST2( unsigned int  ,        double ,        double );
	UPCAST2( unsigned int  ,   long double ,   long double );
	UPCAST1( unsigned long , unsigned long , unsigned long );
	UPCAST2( unsigned long ,        Sint64 ,        Sint64 );
	UPCAST2( unsigned long ,        Uint64 ,        Uint64 );
	UPCAST2( unsigned long ,         float ,         float );
	UPCAST2( unsigned long ,        double ,        double );
	UPCAST2( unsigned long ,   long double ,   long double );
	UPCAST1(        Sint64 ,        Sint64 ,        Sint64 );
	UPCAST2(        Sint64 ,        Uint64 ,        Uint64 );
	UPCAST2(        Sint64 ,         float ,         float );
	UPCAST2(        Sint64 ,        double ,        double );
	UPCAST2(        Sint64 ,   long double ,   long double );
	UPCAST1(        Uint64 ,        Uint64 ,        Uint64 );
	UPCAST2(        Uint64 ,         float ,         float );
	UPCAST2(        Uint64 ,        double ,        double );
	UPCAST2(        Uint64 ,   long double ,   long double );
	UPCAST1(         float ,         float ,         float );
	UPCAST2(         float ,        double ,        double );
	UPCAST2(         float ,   long double ,   long double );
	UPCAST1(        double ,        double ,        double );
	UPCAST2(        double ,   long double ,   long double );
	UPCAST1(   long double ,   long double ,   long double );
#undef UPCAST1
#undef UPCAST2

	template<class U, class V> struct Upcast {
		typedef typename BinaryUpcast<typename UnaryUpcast<U>::type, typename UnaryUpcast<V>::type>::type type;
	};

#define UPCAST(U, V) \
	typename upcast::Upcast< U, V >::type
};

#endif // UPCAST_H
