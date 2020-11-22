// Macros definitions for loading strings from Windows Resources
// _LS( <identifier> )  - TCHAR
// _LSA( <identifier> ) - char
// _LSW( <identifier> ) - wchar_t

#pragma once

#include "windows.h"
#include <list>

#define _LSA( id )  Lingobit::LoadAnsiString_Static< id >()
#define _LSW( id )  Lingobit::LoadUnicodeString_Static< id >()

#ifdef UNICODE
    #define _LS( id )   Lingobit::LoadUnicodeString_Static< id >()
#else
    #define _LS( id )   Lingobit::LoadAnsiString_Static< id >()
#endif

namespace Lingobit
{
    namespace Detail
    {
        class CAutoFreeAnsiStr
        {
        public:
            CAutoFreeAnsiStr( char const * str, int len )
            {
                str_ = new char[ len + 1 ];
                strncpy_s( str_, len + 1, str, len );
                str_[ len ] = '\0';
            }

            ~CAutoFreeAnsiStr() { delete str_; }

            operator char *() { return str_; }

        private:
            char * str_;
        };

        static inline char * LoadAnsiString_Global( UINT id, UINT & len )
        {
            static UINT const MAX_STR_LEN = 4097;
            static char GlobalStrBuffer[ MAX_STR_LEN ];
            HINSTANCE hinstance = ::GetModuleHandle( NULL );
            len = ::LoadStringA( hinstance, id, GlobalStrBuffer, sizeof( GlobalStrBuffer ) );
            return GlobalStrBuffer;
        }

        class CAutoFreeUnicodeStr
        {
        public:
            CAutoFreeUnicodeStr( wchar_t const * str, int len )
            {
                str_ = new wchar_t[ len + 1 ];
                wcsncpy_s( str_, len + 1, str, len );
                str_[ len ] = L'\0';
            }

            ~CAutoFreeUnicodeStr() { delete str_; }

            operator wchar_t *() { return str_; }

        private:
            wchar_t * str_;
        };

        static inline wchar_t * LoadUnicodeString_Global( UINT id, UINT & len )
        {
            static UINT const MAX_STR_LEN = 4097;
            static wchar_t GlobalStrBuffer[ MAX_STR_LEN ];
            HINSTANCE hinstance = ::GetModuleHandle( NULL );
            len = ::LoadStringW( hinstance, id, GlobalStrBuffer, sizeof( GlobalStrBuffer )/sizeof( wchar_t ) );
            return GlobalStrBuffer;
        }
    };

    template< UINT id >
    char * LoadAnsiString_Static()
    {
        UINT len;
        char * buf = Detail::LoadAnsiString_Global( id, len );
        if( len == 0 )
            return NULL;
        static Detail::CAutoFreeAnsiStr str( buf, len );
        return str;
    }

    template< UINT id >
    wchar_t * LoadUnicodeString_Static()
    {
        UINT len;
        wchar_t * buf = Detail::LoadUnicodeString_Global( id, len );
        if( len == 0 )
            return NULL;
        static Detail::CAutoFreeUnicodeStr str( buf, len );
        return str;
    }
}
