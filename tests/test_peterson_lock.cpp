#include <boost/test/unit_test.hpp>
#include <peterson_lock.hpp>
#include <thread>

static constexpr int n = 100000000 / 2;
static int k = 0;
static tamp::lock::peterson lock;

static void work(int id)
{
    for (int i = 0; i < n; i++) {
        lock.acquire(id);
        k++;    // critical section
        lock.release(id);
    }
}

BOOST_AUTO_TEST_CASE(peterson)
{
    std::thread t0(work, 0);
    std::thread t1(work, 1);

    t0.join();
    t1.join();

    BOOST_CHECK(k == (2 * n));
}

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
