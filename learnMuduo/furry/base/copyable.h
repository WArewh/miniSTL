#ifndef BASE_COPYABLE_H_
#define BASE_COPYABLE_H_

namespace furry {
    class copyable {
    protected:
        copyable() = default;
        ~copyable() = default;
    };
}  // namespace furry

#endif