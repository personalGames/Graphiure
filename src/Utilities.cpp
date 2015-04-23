/* 
 * File:   Utilities.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 17:53
 */

#include "Utilities.h"

namespace {

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

//void centerOrigin(Animation& animation) {
//    sf::FloatRect bounds = animation.getLocalBounds();
//    animation.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
//}

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