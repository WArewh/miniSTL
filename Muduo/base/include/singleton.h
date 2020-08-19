#ifndef BASE_SINGLETION_H_
#define BASE_SINGLETION_H_

#include <pthread.h>

#include "noncopyable.h"

namespace furry {
    template <typename T>
    class singleton : noncopyable {
    public:
        singleton() = delete;
        ~singleton() = delete;
        static T* getInstance();

    private:
        static void init();
        static void destory();

    private:
        static pthread_once_t m_once;
        static T*             m_data;
    };
}  // namespace furry


#endif