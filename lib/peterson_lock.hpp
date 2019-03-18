#ifndef LIBTAMP_PETERSON_LOCK_HPP
#define LIBTAMP_PETERSON_LOCK_HPP

#include <atomic>
#include <array>

namespace tamp {
namespace lock {

class peterson {
    std::array<std::atomic<bool>, 2> flag;
    std::atomic<int>  turn;
public:
    peterson();
    void acquire(int me);
    void release(int me);
};

} // namespase lock
} // namespase tamp

#endif // LIBTAMP_PETERSON_LOCK_HPP

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
