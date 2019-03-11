//
// Created by lianhe on 2019/3/8.
//

class TestCpp14 {
public:
    void testLambda() {
        auto lambda = [](auto x, auto y) {return x + y;};
        std::cout << lambda(1, 2) << std::endl;
    }

    void testMove() {
        std::unique_ptr<int> ptr(new int(10));
        auto lambda = [value = std::move(ptr)] {return *value;};
        std::cout << lambda() << std::endl;
    }

    constexpr int testConstexpr(int i) {
        int a = 1;
        return i + a;
    }

    auto testAuto(int a, int b) {
        return a + b;
    }

    void testDecltype() {
        int i;
        const int& ci = i;
        auto i1 = ci;//int
        decltype(auto) i2 = ci;//const int&
    }

    void run() {
//        testLambda();
//        testMove();
//        testConstexpr(5);
//        testAuto(1, 2);
//        testDecltype();
    }
};