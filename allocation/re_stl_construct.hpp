#ifndef __RE_STL_CONSTRUCT_H
#define __RE_STL_CONSTRUCT_H
#include <new>

namespace new_std {

template<class T1, class T2>
inline void construct(T1 *p, const T2 &value) {
    new(p) T1(value);
}

template<class T>
inline void destroy(T *point) {
    point->~T();
}

template <class ForwardInterator>
inline void destroy(ForwardInterator first, ForwardInterator end) {
    __destroy(first, end, value_type(first));
}

template <class ForwardInterator, class T>
inline void __destroy(ForwardInterator first, ForwardInterator last, T*) {
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destroy_aux(first, last, trivial_destructor());
}

template <class ForwardInterator>
inline void __destroy_aux(ForwardInterator first, ForwardInterator last, __false_type) {
    for(; first < last; ++first) {
        destroy(&*first);   //why it is &*
    }
}

template <class ForwardInterator>
inline void __destroy_aux(ForwardInterator, ForwardInterator, __true_type) {}

inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}

} //end for namespace

#endif