#include <core/Core.h>

namespace glsg {

uint32_t hash(uint32_t x) {
    x += ( x << 10u );
    x ^= ( x >>  6u );
    x += ( x <<  3u );
    x ^= ( x >> 11u );
    x += ( x << 15u );
    return x;
}

uint32_t hash_seed(std::string string) {
    std::hash<std::string> str_hasher;
    uint32_t str_hash = (str_hasher(string)) % (2^31 - 1);

    return hash(str_hash);
}

}
