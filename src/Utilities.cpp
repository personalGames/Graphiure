/* 
 * File:   Utilities.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 17:53
 */

#include "Utilities.h"

namespace {
    /**
     * Inicializa el random del motor
     * @return 
     */
    std::default_random_engine createRandomEngine() {
        auto seed = static_cast<unsigned long> (std::time(nullptr));
        return std::default_random_engine(seed);
    }

    auto RandomEngine = createRandomEngine();
}

void centerOrigin(sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void centerOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

float toDegree(float radian) {
    return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree) {
    return 3.141592653589793238462643383f / 180.f * degree;
}

int randomInt(int exclusiveMax) {
    std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
    return distr(RandomEngine);
}

float length(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector) {
    assert(vector != sf::Vector2f(0.f, 0.f));
    return vector / length(vector);
}

std::vector<char>* convertString(std::string convert) {
    std::vector<char>* writable = new std::vector<char>();
    writable->assign(convert.begin(), convert.end());
    writable->push_back('\0');
    return writable;
}

std::vector<std::string> &split(const std::string &s,
        char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool LineCollision(const sf::Vector2f& A1, const sf::Vector2f& A2,
        const sf::Vector2f& B1, const sf::Vector2f& B2,
        double* out) {
    sf::Vector2f a(A2 - A1);
    sf::Vector2f b(B2 - B1);

    double f = PerpDot(a, b);
    if (!f) // lines are parallel
        return false;

    sf::Vector2f c(B2 - A2);
    double aa = PerpDot(a, c);
    double bb = PerpDot(b, c);

    if (f < 0) {
        if (aa > 0) return false;
        if (bb > 0) return false;
        if (aa < f) return false;
        if (bb < f) return false;
    } else {
        if (aa < 0) return false;
        if (bb < 0) return false;
        if (aa > f) return false;
        if (bb > f) return false;
    }

    if (out)
        *out = 1.0 - (aa / f);
    return true;
}

template <typename T>
wchar_t* toString(const T& value) {
    std::wstring stream;
    stream << value;
    return stream.c_str();
}

template <typename T>
std::string toStringKey(const T& value) {
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template <typename T>
const std::wstring toString(const T& value) {
    std::stringstream stream1;
    stream1<<value;
    std::string key=stream1.str();
    std::wstring result=std::wstring(key.begin(), key.end());
    return result;
}

/**
 * Convierte los códigos de teclado en strings
 * @param key código de tecla
 * @return string representando la tecla
 */
std::string toString(sf::Keyboard::Key key) {
#define BOOK_KEYTOSTRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

    switch (key) {
            BOOK_KEYTOSTRING_CASE(Unknown)
            BOOK_KEYTOSTRING_CASE(A)
            BOOK_KEYTOSTRING_CASE(B)
            BOOK_KEYTOSTRING_CASE(C)
            BOOK_KEYTOSTRING_CASE(D)
            BOOK_KEYTOSTRING_CASE(E)
            BOOK_KEYTOSTRING_CASE(F)
            BOOK_KEYTOSTRING_CASE(G)
            BOOK_KEYTOSTRING_CASE(H)
            BOOK_KEYTOSTRING_CASE(I)
            BOOK_KEYTOSTRING_CASE(J)
            BOOK_KEYTOSTRING_CASE(K)
            BOOK_KEYTOSTRING_CASE(L)
            BOOK_KEYTOSTRING_CASE(M)
            BOOK_KEYTOSTRING_CASE(N)
            BOOK_KEYTOSTRING_CASE(O)
            BOOK_KEYTOSTRING_CASE(P)
            BOOK_KEYTOSTRING_CASE(Q)
            BOOK_KEYTOSTRING_CASE(R)
            BOOK_KEYTOSTRING_CASE(S)
            BOOK_KEYTOSTRING_CASE(T)
            BOOK_KEYTOSTRING_CASE(U)
            BOOK_KEYTOSTRING_CASE(V)
            BOOK_KEYTOSTRING_CASE(W)
            BOOK_KEYTOSTRING_CASE(X)
            BOOK_KEYTOSTRING_CASE(Y)
            BOOK_KEYTOSTRING_CASE(Z)
            BOOK_KEYTOSTRING_CASE(Num0)
            BOOK_KEYTOSTRING_CASE(Num1)
            BOOK_KEYTOSTRING_CASE(Num2)
            BOOK_KEYTOSTRING_CASE(Num3)
            BOOK_KEYTOSTRING_CASE(Num4)
            BOOK_KEYTOSTRING_CASE(Num5)
            BOOK_KEYTOSTRING_CASE(Num6)
            BOOK_KEYTOSTRING_CASE(Num7)
            BOOK_KEYTOSTRING_CASE(Num8)
            BOOK_KEYTOSTRING_CASE(Num9)
            BOOK_KEYTOSTRING_CASE(Escape)
            BOOK_KEYTOSTRING_CASE(LControl)
            BOOK_KEYTOSTRING_CASE(LShift)
            BOOK_KEYTOSTRING_CASE(LAlt)
            BOOK_KEYTOSTRING_CASE(LSystem)
            BOOK_KEYTOSTRING_CASE(RControl)
            BOOK_KEYTOSTRING_CASE(RShift)
            BOOK_KEYTOSTRING_CASE(RAlt)
            BOOK_KEYTOSTRING_CASE(RSystem)
            BOOK_KEYTOSTRING_CASE(Menu)
            BOOK_KEYTOSTRING_CASE(LBracket)
            BOOK_KEYTOSTRING_CASE(RBracket)
            BOOK_KEYTOSTRING_CASE(SemiColon)
            BOOK_KEYTOSTRING_CASE(Comma)
            BOOK_KEYTOSTRING_CASE(Period)
            BOOK_KEYTOSTRING_CASE(Quote)
            BOOK_KEYTOSTRING_CASE(Slash)
            BOOK_KEYTOSTRING_CASE(BackSlash)
            BOOK_KEYTOSTRING_CASE(Tilde)
            BOOK_KEYTOSTRING_CASE(Equal)
            BOOK_KEYTOSTRING_CASE(Dash)
            BOOK_KEYTOSTRING_CASE(Space)
            BOOK_KEYTOSTRING_CASE(Return)
            BOOK_KEYTOSTRING_CASE(BackSpace)
            BOOK_KEYTOSTRING_CASE(Tab)
            BOOK_KEYTOSTRING_CASE(PageUp)
            BOOK_KEYTOSTRING_CASE(PageDown)
            BOOK_KEYTOSTRING_CASE(End)
            BOOK_KEYTOSTRING_CASE(Home)
            BOOK_KEYTOSTRING_CASE(Insert)
            BOOK_KEYTOSTRING_CASE(Delete)
            BOOK_KEYTOSTRING_CASE(Add)
            BOOK_KEYTOSTRING_CASE(Subtract)
            BOOK_KEYTOSTRING_CASE(Multiply)
            BOOK_KEYTOSTRING_CASE(Divide)
            BOOK_KEYTOSTRING_CASE(Left)
            BOOK_KEYTOSTRING_CASE(Right)
            BOOK_KEYTOSTRING_CASE(Up)
            BOOK_KEYTOSTRING_CASE(Down)
            BOOK_KEYTOSTRING_CASE(Numpad0)
            BOOK_KEYTOSTRING_CASE(Numpad1)
            BOOK_KEYTOSTRING_CASE(Numpad2)
            BOOK_KEYTOSTRING_CASE(Numpad3)
            BOOK_KEYTOSTRING_CASE(Numpad4)
            BOOK_KEYTOSTRING_CASE(Numpad5)
            BOOK_KEYTOSTRING_CASE(Numpad6)
            BOOK_KEYTOSTRING_CASE(Numpad7)
            BOOK_KEYTOSTRING_CASE(Numpad8)
            BOOK_KEYTOSTRING_CASE(Numpad9)
            BOOK_KEYTOSTRING_CASE(F1)
            BOOK_KEYTOSTRING_CASE(F2)
            BOOK_KEYTOSTRING_CASE(F3)
            BOOK_KEYTOSTRING_CASE(F4)
            BOOK_KEYTOSTRING_CASE(F5)
            BOOK_KEYTOSTRING_CASE(F6)
            BOOK_KEYTOSTRING_CASE(F7)
            BOOK_KEYTOSTRING_CASE(F8)
            BOOK_KEYTOSTRING_CASE(F9)
            BOOK_KEYTOSTRING_CASE(F10)
            BOOK_KEYTOSTRING_CASE(F11)
            BOOK_KEYTOSTRING_CASE(F12)
            BOOK_KEYTOSTRING_CASE(F13)
            BOOK_KEYTOSTRING_CASE(F14)
            BOOK_KEYTOSTRING_CASE(F15)
            BOOK_KEYTOSTRING_CASE(Pause)
    }

    return "";
}