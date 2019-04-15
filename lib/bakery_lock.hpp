#ifndef LIBTAMP_BAKERY_LOCK_HPP
#define LIBTAMP_BAKERY_LOCK_HPP

#include <atomic>
#include <array>

namespace tamp {
namespace lock {

class bakery {
public:
    static constexpr std::size_t max_threads = 8;
    bakery();
    void acquire(unsigned long me);
    void release(unsigned long me);
private:
    std::array<std::atomic<bool>, max_threads> entering;
    std::array<std::atomic<unsigned long>, max_threads> token;
};

} // namespase lock
} // namespase tamp

#endif // LIBTAMP_BAKERY_LOCK_HPP

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
