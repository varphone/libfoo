
#ifndef _EXPORT_H
#define _EXPORT_H

#ifdef FOO_STATIC_DEFINE
#  define _EXPORT
#  define FOO_NO_EXPORT
#else
#  ifndef _EXPORT
#    ifdef foo_EXPORTS
        /* We are building this library */
#      define _EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define _EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef FOO_NO_EXPORT
#    define FOO_NO_EXPORT 
#  endif
#endif

#ifndef FOO_DEPRECATED
#  define FOO_DEPRECATED __declspec(deprecated)
#endif

#ifndef FOO_DEPRECATED_EXPORT
#  define FOO_DEPRECATED_EXPORT _EXPORT FOO_DEPRECATED
#endif

#ifndef FOO_DEPRECATED_NO_EXPORT
#  define FOO_DEPRECATED_NO_EXPORT FOO_NO_EXPORT FOO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FOO_NO_DEPRECATED
#    define FOO_NO_DEPRECATED
#  endif
#endif

#endif /* _EXPORT_H */
