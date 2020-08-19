#include "include/singleton.h"

#include <cassert>
#include <cstdlib>

namespace furry {
    template <typename T>
    T* singleton<T>::getInstance() {
        pthread_once(&m_once, init);
        assert(m_data != nullptr);
        return m_data;
    }

    template <typename T>
    void singleton<T>::init() {
        m_data = new T();
        atexit(destory);
    }

    template <typename T>
    void singleton<T>::destory() {
        delete m_data;
        m_data = nullptr;
    }
};  // namespace furry