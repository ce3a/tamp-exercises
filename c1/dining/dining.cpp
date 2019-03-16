#include <iostream>
#include <iomanip>
#include <array>
#include <atomic>
#include <memory>
#include <thread>
#include <utility>
#include <random>
#include <chrono>

namespace tamp {

void rand_busy_wait()
{
    std::mt19937_64 eng{std::random_device{}()};
    std::uniform_int_distribution<> dist{100, 1000};
    int delay = dist(eng);
    while (delay-- > 0)
        ; // wait
}

class chopstick {
    int _id;
    int _count;

public:
    chopstick()
    {
        static int id = 0;
        _id = id++;
        _count = 0;
    }

    ~chopstick()
    {
        std::cout << "chopstick " << _id
                  << " was used " << _count << " times" << std::endl;
    }

    void use()
    {
        _count++;
    }
};

class table {
    std::array<std::pair<
            std::shared_ptr<chopstick>, std::atomic<bool>>, 5> sticks;

public:
    table()
    {
        for (auto& stick : sticks) {
            stick.first = std::make_shared<chopstick>();
            stick.second.store(false);
        }
    }

    auto size() -> std::size_t const
    {
        return sticks.size();
    }

    auto stick_acquire(std::size_t pos) -> std::shared_ptr<chopstick>
    {
        std::shared_ptr<chopstick> stick;
        bool expected = false;

        if (sticks.at(pos).second.compare_exchange_weak(expected, true))
            stick = sticks.at(pos).first;

        return stick;
    }

    void stick_release(std::size_t pos)
    {
        sticks.at(pos).second.store(false);
    }
};

class philosopher {
    tamp::table& _table;
    std::size_t _pos;
    std::array<std::size_t, 2> _sids;

    struct stat {
        std::chrono::duration<double, std::milli> tot_wait;
        std::chrono::duration<double, std::milli> tot_eat;
        std::chrono::duration<double, std::milli> tot_think;
        stat() : tot_wait(0), tot_eat(0), tot_think(0) { }
    } _stat;

    void eat()
    {
        std::array<std::shared_ptr<chopstick>, 2> sticks;

        auto t1 = std::chrono::high_resolution_clock::now();
        do {
            // Try to acquire both sticks
            for (int i = 0; i < 2; i++)
                sticks[i] = _table.stick_acquire(_sids[i]);

            // On success, start eating
            if (sticks[0] && sticks[1])
                break;

            // Otherwise, release acquired stick to avoid blocking others
            for (int i = 0; i < 2; i++)
                if (sticks[i])
                    _table.stick_release(_sids[i]);
        } while(true);
        auto t2 = std::chrono::high_resolution_clock::now();
        _stat.tot_wait += (t2 - t1);

        // now eat
        for (const auto& stick : sticks)
            stick->use();

        t1 = std::chrono::high_resolution_clock::now();
        rand_busy_wait();
        t2 = std::chrono::high_resolution_clock::now();
        _stat.tot_eat += (t2 - t1);

        // release the sticks again
        for (const auto& id : _sids)
            _table.stick_release(id);
    }

    void think()
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        rand_busy_wait();
        auto t2 = std::chrono::high_resolution_clock::now();
        _stat.tot_think += (t2 - t1);
    }

public:
    philosopher(tamp::table& table, int pos) : _table(table), _pos(pos)
    {
        for (std::size_t i = 0; i < _sids.size(); i++)
            _sids.at(i) = (pos + i) % _table.size();

        std::cout << _sids[0] << "[" << pos << "]" << _sids[1] << std::endl;
    }

    ~philosopher()
    {
        auto sum = _stat.tot_wait.count()
                 + _stat.tot_eat.count()
                 + _stat.tot_think.count();

        std::cout << "philosopher " << _pos << " [w e t s]:"
                  << std::fixed << std::setprecision(2)
                  << std::setw(9) << _stat.tot_wait.count()
                  << std::setw(9) << _stat.tot_eat.count()
                  << std::setw(9) << _stat.tot_think.count()
                  << std::setw(9) << sum << std::endl;
    }

    void work()
    {
        for (int i = 500000; i-- > 0; ) {
            eat();
            think();
        }
    }
};

} // namespase tamp

int main()
{
    tamp::table table;
    std::array<std::pair<std::thread,
            std::unique_ptr<tamp::philosopher>>, 5> threads;

    auto i = 0;
    for (auto& t : threads) {
        t.second = std::make_unique<tamp::philosopher>(table, i++);
        t.first  = std::thread{&tamp::philosopher::work, &*t.second};
    }

    for (auto& t : threads) {
        t.first.join();
    }

    return 0;
}

// vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
