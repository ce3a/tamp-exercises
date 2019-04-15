#include <boost/test/unit_test.hpp>
#include <bakery_lock.hpp>
#include <thread>

static constexpr int m = tamp::lock::bakery::max_threads;
static constexpr int n = 100000000 / m;
static int k = 0;
static tamp::lock::bakery lock;

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
    std::thread t2(work, 2);
    std::thread t3(work, 3);
    std::thread t4(work, 4);
    std::thread t5(work, 5);
    std::thread t6(work, 6);
    std::thread t7(work, 7);

    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    BOOST_CHECK(k == (m * n));
}

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
