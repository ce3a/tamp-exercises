#include <peterson_lock.hpp>
#include <thread>

namespace tamp {
namespace lock {

peterson::peterson() : flag{}, turn{} {}

void peterson::acquire(int me)
{
    int he = !!(me == 0);
    flag.at(me).store(true);    // I'm interested
    turn.store(he);             // you go first
    while (flag.at(he).load() && turn.load() == he)
        std::this_thread::yield(); // wait
}

void peterson::release(int me)
{
    flag.at(me).store(false);   // I'm not interested
}

} // namespase lock
} // namespase tamp

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
