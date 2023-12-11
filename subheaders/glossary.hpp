#pragma once

#include <map>
#include <optional>

#include "id_pool.hpp"

namespace more_collections {

    template <typename K, typename V>
    class Glossary {
        public:

            typedef typename IdPool<V>::Token Token;

            Token insert(K key, V value) {
                Token t = _pool.add(value);
                _resolver.insert(key, t);
            }

            std::optional<Token> get_token(K key) const {

            }

        private:
            IdPool<V> _pool;
            std::map<K,Token> _resolver;
            
    };

}
