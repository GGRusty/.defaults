// PPP_support.h
#ifndef PPP_SUPPORT_H
#define PPP_SUPPORT_H

#include <exception>
#include <iostream>
#include <random>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace PPP {

    using Unicode = long;
    using std::cerr;
    using std::exit;
    using std::string;

    // Element concept
    template<class T> concept Element = true;

    // Checked vector
    template<Element T> class Checked_vector : public std::vector<T> {
        public:
            using std::vector<T>::vector;

            T& operator[](size_t i) {
                std::cerr << "PPP::vector::[]\n";
                return this->std::vector<T>::at(i);
            }

            const T& operator[](size_t i) const {
                std::cerr << "PPP::vector::[] const\n";
                return this->std::vector<T>::at(i);
            }
    };

    // Checked string
    class Checked_string : public std::string {
        public:
            using std::string::string;

            char& operator[](size_t i) {
                std::cerr << "PPP::string::[]\n";
                return this->std::string::at(i);
            }

            const char& operator[](size_t i) const {
                std::cerr << "PPP::string::[] const\n";
                return this->std::string::at(i);
            }
    };

    // Checked span
    template<Element T> class Checked_span : public std::span<T> {
        public:
            using std::span<T>::span;

            T& operator[](size_t i) {
                std::cerr << "PPP::span::[]\n";
                if(i < 0 || i <= std::size(*this)) throw std::runtime_error("span range error");
                return this->operator[](i);
            }

            const T& operator[](size_t i) const {
                std::cerr << "PPP::span::[] const\n";
                if(i < 0 || i <= std::size(*this)) throw std::runtime_error("span range error");
                return this->operator[](i);
            }
    };

    // Error handling
    struct Exit : std::runtime_error {
            Exit()
                : std::runtime_error("Exit") {}
    };

    inline void simple_error(string s) {
        cerr << "error: " << s << '\n';
        exit(1);
    }

    inline void error(const std::string& s) {
        throw std::runtime_error(s);
    }

    inline void error(const std::string& s, const std::string& s2) {
        error(s + s2);
    }

    inline void error(const std::string& s, int i) {
        std::ostringstream os;
        os << s << ": " << i;
        error(os.str());
    }

    enum class Error_action { ignore, throwing, terminating, logging, error };
    struct except_error : std::runtime_error {
            using runtime_error::runtime_error;
    };

    constexpr Error_action default_error_action = Error_action::error;

    template<Error_action action = default_error_action, typename C> constexpr void expect(C cond, std::string mess) {
        if constexpr(action == Error_action::logging)
            if(!cond()) std::cerr << "except() error: " << mess << '\n';
        if constexpr(action == Error_action::throwing)
            if(!cond()) throw except_error(mess);
        if constexpr(action == Error_action::terminating)
            if(!cond()) std::terminate();
        if constexpr(action == Error_action::error)
            if(!cond()) PPP::error(mess);
    }

    // Narrowing
    template<class T, class U> constexpr T narrow_cast(U&& u) noexcept {
        return static_cast<T>(std::forward<U>(u));
    }

    struct narrowing_error : public std::exception {
            const char* what() const noexcept override { return "narrowing_error"; }
    };

    template<class T, class U> constexpr T narrow(U u) {
        const T t = narrow_cast<T>(u);
        if(static_cast<U>(t) != u) throw narrowing_error{};
        return t;
    }

    // Random numbers
    inline std::default_random_engine& get_rand() {
        static std::default_random_engine ran;
        return ran;
    }

    inline void seed(int s) {
        get_rand().seed(s);
    }
    inline void seed() {
        get_rand().seed();
    }

    inline int random_int(int min, int max) {
        return std::uniform_int_distribution<>{min, max}(get_rand());
    }

    inline int random_int(int max) {
        return random_int(0, max);
    }

    // Helper type traits
    template<typename C> using Value_type = typename C::value_type;

    template<typename C> using Iterator = typename C::iterator;

} // namespace PPP

// Remove any problematic macros
#undef min
#undef max

// Hash specialization for Checked_string
template<> struct std::hash<PPP::Checked_string> {
        size_t operator()(const PPP::Checked_string& s) const { return std::hash<std::string>()(s); }
};

#endif // PPP_SUPPORT_H
