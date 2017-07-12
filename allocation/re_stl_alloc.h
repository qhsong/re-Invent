#ifndef __RE_STL_ALLOC_H
#define __RE_STL_ALLOC_H

namespace new_std {
template<class T, class Alloc>
class simple_alloc {
public:
    static T *allocate(size_t n) {
        return n==0 ? NULL : (T *)Alloc::allocate(n * sizeof(T)); 
    }

    static T *allocate(void) { 
        return (T *) Alloc::allocate(sizeof(T));
    }

    static void deallocate(T *p, size_t n) {
        if( n != 0 ) {
            Alloc::deallocate(p, n * sizeof(T));
        }
    }

    static void deallocate(T *p) {
        Alloc::deallocate(p, sizeof(T));
    }
}

#ifndef __THROW_BAD_ALLOC
#include<iostream>
#define __THROW_BAD_ALLOC cerr<<"Out of Memory"<<endl; exit(1);
#endif

//First Class allocate
template <int inst>
class __malloc_alloc_template {
private:
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    static void (* __malloc_alloc_oom_handler) ();
public:
    static void *allocate(size_t n) {
        void *result = malloc(n);
        if(result == NULL) {
            result == oom_malloc(n);
        }
        return result;
    }

    static void deallocate(void *p, size_t) {
        free(p);
    }

    static void *reallocate(void *p, size_t /*old_sz */ , size_t new_sz) {
        void *result = realloc(p, new_sz);
        if(result == 0) {
            result = oom_realloc(p, new_sz);
        }
        return result;
    }
    
    // hand to understand
    static void (* set_malloc_handler(void (*f) ())) () {
        void (* old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return (old);

    }
}; //end of class __malloc_alloc_template

template <int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = NULL;

template <int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n) {
    void (*my_malloc_handler)();
    void *result;

    for(;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(my_malloc_handler == NULL) { __THROW_BAD_ALLOC;}
        (*my_malloc_handler)();
        result = malloc(n);
        if(result) return ()
    }
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
    void (* my_malloc_handler)();
    void *result;

    for(;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(my_malloc_handler == NULL) { __THROW_BAD_ALLOC;}
        (*my_malloc_handler) ();
        result = realloc(p, n);
        if(result) return(result);
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;
}//end of namespace

#endif
