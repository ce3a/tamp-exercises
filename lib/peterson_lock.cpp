#include <peterson_lock.hpp>
#include <thread>

namespace tamp {
namespace lock {

peterson::peterson() : flag{}, turn{} {}

void peterson::acquire(int me)
{
    int he = !!(me == 0);
    flag.at(me).store(true, std::memory_order_relaxed);    // I'm interested,...
    turn.store(he);                                        // but it's your turn
    while (flag.at(he).load(std::memory_order_acquire)
            && turn.load(std::memory_order_relaxed) == he)
        std::this_thread::yield();                         // waiting
}

void peterson::release(int me)
{
    flag.at(me).store(false, std::memory_order_release);   // I'm not interested
}

} // namespase lock
} // namespase tamp

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
