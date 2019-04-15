#include <bakery_lock.hpp>
#include <thread>
#include <algorithm>

namespace tamp {
namespace lock {

bakery::bakery() : entering{}, token{} {}

void bakery::acquire(unsigned long me)
{
    entering.at(me) = true;
    token.at(me) = *std::max_element(token.begin(), token.end()) + 1;
    entering.at(me) = false;

    for (std::size_t he = 0; he < token.size(); ++he) {
        while (entering.at(he));
        while (token.at(he) != 0 && ((token.at(he) < token.at(me))
                || ((token.at(he) == token.at(me)) && (he < me))));
    }
}

void bakery::release(unsigned long me)
{
    token.at(me) = 0;
}

} // namespase lock
} // namespase tamp

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
