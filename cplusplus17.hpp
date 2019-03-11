//
// Created by lianhe on 2019/3/8.
//

#include <string>
#include <optional>
#include <variant>
#include <any>

template <auto value>
constexpr auto constant = value;

template <typename First, typename... Rest>
auto sum(First&& first, Rest&&... rest) {
    return (first + ... + rest);
}

template <typename T>
constexpr bool isIntegral() {
    if constexpr (std::is_integral<T>::value) {
        return true;
    }
    else {
        return false;
    }
}

namespace A::B::C {
    int i{1};
}

class TestCpp17 {
public:
    void testOption() {
        auto create = [](bool b) -> std::optional<std::string> {
            if (b) {
                return "connor";
            }
            else {
                return {};
            }
        };
        std::cout << create(false).value_or("empty") << std::endl;

        auto create2 = [](bool b) {
            return b ? std::optional<std::string>("connor") : std::nullopt;
        };
        if (auto str = create2(true)) {
            std::cout << *str << std::endl;
        }

        auto create3 = [](bool b) {
            static std::string value = "connor";
            return b ? std::optional<std::reference_wrapper<std::string>>{value} : std::nullopt;
        };
        if (auto str = create3(true)) {
            std::cout << str->get() << std::endl;
            str->get() = "connorconnor";
            std::cout << str->get() << std::endl;
        }
    }

    void testVariant() {
        std::variant<int, std::string> u("hello");
        std::cout << std::get<1>(u) << std::endl;
        std::cout << std::get<std::string>(u) << std::endl;
    }

    void testAny() {
        std::any x{5};
        std::cout << x.has_value() << std::endl;
        std::cout << x.type().name() << std::endl;
        std::cout << std::any_cast<int>(x) << std::endl;
        std::any_cast<int&>(x) = 10;
        std::cout << std::any_cast<int>(x) << std::endl;

        auto a = std::any(12);
        std::cout << std::any_cast<int>(a) << std::endl;
        try {
            std::cout << std::any_cast<std::string>(a) << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

        a = std::string("hello");
        auto& ra = std::any_cast<std::string&>(a);
        ra[1] = 'o';
        std::cout << std::any_cast<const std::string&>(a) << std::endl;
    }

    void testStringView() {
        std::string str = "   trim me";
        std::string_view v(str);
        v.remove_prefix(std::min(v.find_first_not_of(" "), v.size()));
        std::cout << "string: " << str << std::endl << "view: " << v << std::endl;
    }

    void testInvoke() {
        struct Foo {
            Foo(int num) : num_(num) {}
            void print_add(int i) const { std::cout << num_ + i << std::endl; }
            int num_;
        };

        auto print_num = [](int i) {
            std::cout << i << std::endl;
        };

        struct PrintNum {
            void operator()(int i) const {
                std::cout << i << std::endl;
            }
        };

        std::invoke(print_num, -9);

        const Foo foo(4567843);
        std::invoke(&Foo::print_add, foo, 1);

        std::cout << "num_: " << std::invoke(&Foo::num_, foo) << std::endl;

        std::invoke(PrintNum(), 18);
    }

    void testApply() {
        auto add = [](int x, int y) {
            return x + y;
        };
        auto r = std::apply(add, std::make_tuple(1, 2));
        std::cout << r << std::endl;
        r = std::apply(add, std::make_pair(1, 2));
        std::cout << r << std::endl;
        std::array arr = {2, 3};
        r = std::apply(add, arr);
        std::cout << r << std::endl;
    }

    void testClassParaDeduce() {
        std::vector a = {1, 2, 4};
        std::pair b = {1, "hello"};
    }

    void testAutoTemplate() {
        constexpr auto IntConstant42 = constant<42>;
        std::cout << IntConstant42 << std::endl;
    }

    void testFoldExpression() {
        std::cout << sum(1, 4, 7) << std::endl;
    }

    void testAutoDeduction() {
        auto x1{1};
        std::cout << x1 << std::endl;
    }

    void testConstexprLambda() {
        constexpr auto add = [] (int x, int y) {
            auto L = [=] {return x;};
            auto R = [=] {return y;};
            return [=] {return L() + R();};
        };

        static_assert(add(1, 2)() == 3);
    }

    void testLambdaThis() {
        struct MyObj {
            int value{123};
            auto getValueCopy() {
                return [*this] {return value;};
            }
            auto getValueRef() {
                return [this] {return value;};
            }
        };

        MyObj mo;
        auto valueCopy = mo.getValueCopy();
        auto valueRef = mo.getValueRef();
        mo.value = 321;
        std::cout << valueCopy() << std::endl;
        std::cout << valueRef() << std::endl;
    }

    void testNestNamespace() {
        std::cout << A::B::C::i << std::endl;
    }

    void testStructureBinding() {
        auto lambda = [] { return std::tuple{3, 4};};
        auto [x, y] = lambda();
        std::cout << x << ", " << y << std::endl;
    }

    void testConstexprIf() {
        static_assert(isIntegral<int>() == true);
        static_assert(isIntegral<char>() == true);
        static_assert(isIntegral<double>() == false);

        struct S {};
        static_assert(isIntegral<S>() == false);
    }

    void testUtf8() {
    }

    void run() {
//        testOption();
//        testVariant();
//        testAny();
//        testStringView();
//        testInvoke();
//        testApply();
//        testClassParaDeduce();
//        testAutoTemplate();
//        testFoldExpression();
//        testAutoDeduction();
//        testAutoDeduction();
//        testConstexprLambda();
//        testLambdaThis();
//        testNestNamespace();
//        testStructureBinding();
//        testConstexprIf();
//        testUtf8();
    }
};