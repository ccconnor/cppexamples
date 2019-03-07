#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <atomic>
#include <list>
#include <mutex>
#include <condition_variable>


class Test {
public:
    void testForRange() {
        std::vector<double> v;
        v.push_back(0.1);
        v.push_back(0.2);
        v.push_back(0.3);
        for (auto d : v) {
            std::cout << d << std::endl;
        }
    }

    void testThread() {
        auto threadFunc = []() {
            std::cout << "this is a c++11 thread" << std::endl;
        };
        std::thread t(threadFunc);
        t.join();
    }

    void testLambda1() {
        std::vector<int> array{8,2,10,5,47,21,11,19};
        std::sort(array.begin(), array.end(), [](int a, int b) -> bool { return a < b; });
        for (auto v : array) {
            std::cout << v << ' ';
        }
    }

    void testLambda2() {
        auto a = 123;
        auto f = [a] { std::cout << a << std::endl; };
        f();
        [](int b) { std::cout << b << std::endl; }(a);
    }

    void testLambda3() {
        auto a = 123;
        auto f = [a] ()mutable { std::cout << ++a << std::endl; };
        std::cout << "before lambda, a=" << a << std::endl;
        f();
        std::cout << "after lambda, a=" << a << std::endl;
    }

    void testLambda4() {
        auto m = [](int x) { return [](int y) { return y * 2; }(x) + 6; }(5);
        std::cout << m << std::endl;
        auto n = [](int x, int y) { return x + y; }(5, 4);
        std::cout << n << std::endl;
    }

    void testLambda5() {
        auto gfunc = [](int x) -> std::function<int(int)> { return [=](int y) { return x + y; }; };
        auto lfunc = gfunc(4);
        std::cout << lfunc(5) << std::endl;
    }

    void testLambda6() {
        auto a = 111;
        auto b = 222;
        auto func = [=, &b]()mutable {
            a = 22;
            b = 33;
            std::cout << "a=" << a << " b=" << b << std::endl;
        };
        func();
        std::cout << "a=" << a << " b=" << b << std::endl;
    }

    void testDecltype() {
        int v;
        decltype(v) v2;
        std::cout << typeid(v2).name() << std::endl;
    }

    void testNull(int ptr) {
        std::cout << "testNull 1" << std::endl;
    }

    void testNull(int * ptr) {
        std::cout << "testNull 2" << std::endl;
    }

    void testArray() {
        std::array<int, 4> arr = {1,2,3,4};
        for (auto it : arr) {
            std::cout << it << std::endl;
        }
        std::cout << "array size: " << sizeof(arr) << std::endl;
        std::cout << "array size: " << arr.size() << std::endl;
    }

    void testForwardList() {
        std::forward_list<int> numbers = {5,8,6,9,4,2,6};
        for (auto number : numbers) {
            std::cout << number << std::endl;
        }
        numbers.remove(4);
        std::cout << "after remove" << std::endl;
        for (auto number : numbers) {
            std::cout << number << std::endl;
        }
    }

    void testUnorderedMap() {
        std::unordered_map<std::string, std::string> mymap = {
                {"house", "maison"},
                {"apple", "pomme"},
                {"tree", "arbre"},
                {"book", "livre"},
                {"door", "porte"},
                {"grapefruit", "pamplemousse"}
        };
        size_t n = mymap.bucket_count();
        std::cout << "mymap has " << n << " buckets." << std::endl;
        for (auto it = mymap.begin(); it != mymap.end(); it++) {
            std::cout << it->first << ":" << it->second << std::endl;
        }
    }

    void testUnorderedSet() {
        std::unordered_set<int> unorder_set;
        unorder_set.insert(7);
        unorder_set.insert(5);
        unorder_set.insert(3);
        unorder_set.insert(4);
        unorder_set.insert(6);
        std::cout << "unordered set: " << std::endl;
        for (auto it : unorder_set) {
            std::cout << it << std::endl;
        }

        std::set<int> set;
        set.insert(7);
        set.insert(5);
        set.insert(3);
        set.insert(4);
        set.insert(6);
        std::cout << "set: " << std::endl;
        for (auto it : set) {
            std::cout << it << std::endl;
        }
    }

    void testAtomic() {
        std::atomic_int count(100);
        auto printAtomic = [&]() {
            std::this_thread::yield();
            while (count > 0) {
                std::cout << "count: " << --count << std::endl;
            }
        };

        std::list<std::thread> threadGroup;
        for (int i = 0; i < 10; i++) {
            threadGroup.push_back(std::thread(printAtomic));
        }
        for (auto& t : threadGroup) {
            t.join();
        }
    }

    void testCondition() {
        bool ready = false;
        std::mutex mtx;
        std::condition_variable cv;
        auto printId = [&](int id) {
            std::unique_lock<std::mutex> lck(mtx);
            while (!ready) cv.wait(lck);
            std::cout << "thread: " << id << std::endl;
        };

        std::cout << "10 threads ready to race..." << std::endl;
        std::thread threads[10];
        for (int i = 0; i < 10; i++) {
            threads[i] = std::thread(printId, i);
        }

        auto go = [&]() {
            std::unique_lock<std::mutex> lck(mtx);
            ready = true;
            cv.notify_all();
        };
        go();

        for (auto& t : threads) {
            t.join();
        }
    }

    void testSharedPtr() {
        class TestPtr {
        public:
            TestPtr() {
                std::cout << "constructing..." << std::endl;
            }
            ~TestPtr() {
                std::cout << "destructing..." << std::endl;
            }
        };

        auto p1 = std::make_shared<TestPtr>();
        std::cout << "ref: " << p1.use_count() << std::endl;
        {
            auto p2 = p1;
            std::cout << "ref: " << p1.use_count() << std::endl;
        }
        std::cout << "ref: " << p1.use_count() << std::endl;
    }

    void testWeakPtr() {
        class TestPtrB;
        class TestPtrA {
        public:
            TestPtrA() {
                std::cout << "TestPtrA constructing..." << std::endl;
            }
            ~TestPtrA() {
                std::cout << "TestPtrA destructing..." << std::endl;
            }
            void referTestB(std::shared_ptr<TestPtrB> ptr) {
                m_pTestB = ptr;
            }
            void print() {
                std::cout << "print TestPtrA" << std::endl;
            }

        private:
            std::weak_ptr<TestPtrB> m_pTestB;
        };

        class TestPtrB {
        public:
            TestPtrB() {
                std::cout << "TestPtrB constructing..." << std::endl;
            }
            ~TestPtrB() {
                std::cout << "TestPtrB destructing..." << std::endl;
            }
            void referTestA(std::shared_ptr<TestPtrA> ptr) {
                m_pTestA = ptr;
            }
            void printTestA() {
                auto pTestA = m_pTestA.lock();
                std::cout << "ref A: " << pTestA.use_count() << std::endl;
                pTestA->print();
            }

        private:
            std::weak_ptr<TestPtrA> m_pTestA;
        };

        auto pTestA = std::make_shared<TestPtrA>();
        auto pTestB = std::make_shared<TestPtrB>();
        pTestA->referTestB(pTestB);
        pTestB->referTestA(pTestA);
        std::cout << "ref A: " << pTestA.use_count() << std::endl;
        std::cout << "ref B: " << pTestB.use_count() << std::endl;
        pTestB->printTestA();
        std::cout << "ref A: " << pTestA.use_count() << std::endl;
        std::cout << "ref B: " << pTestB.use_count() << std::endl;
    }

    void testBind() {
        std::function<int(int, int)> add;
        auto add1 = [](int a, int b) -> int {
            return a + b;
        };
        add = std::bind(add1, std::placeholders::_1, std::placeholders::_2);
        std::cout << add(1, 2) << std::endl;

        class Add {
        public:
            int add(int a, int b) {
                return a + b;
            }
        };
        auto add2 = std::make_shared<Add>();
        add = std::bind(&Add::add, add2, std::placeholders::_1, std::placeholders::_2);
        std::cout << add(3, 4) << std::endl;
    }
};

int main() {
    Test test;
//    test.testForRange();
//    test.testThread();
//    test.testLambda1();
//    test.testLambda2();
//    test.testLambda3();
//    test.testLambda4();
//    test.testLambda5();
//    test.testLambda6();
//    test.testDecltype();
//    test.testNull(0);
//    test.testNull(nullptr);
//    test.testArray();
//    test.testForwardList();
//    test.testUnorderedMap();
//    test.testUnorderedSet();
//    test.testAtomic();
//    test.testCondition();
//    test.testSharedPtr();
//    test.testWeakPtr();
//    test.testBind();
    return 0;
}