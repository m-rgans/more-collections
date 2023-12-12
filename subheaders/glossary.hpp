#pragma once

#include <map>
#include <optional>
#include <exception>

#include "id_pool.hpp"

//

namespace more_collections {

    /**
        @class Glossary
        @brief class similar to maps, but allows faster resolution through use of cached tokens, to skip hashing
        @author m-rgans
    */
    template <typename K, typename V>
    class Glossary {
        public:
            
            typedef typename IdPool<V>::Token Token;

            Token insert(K key, V value) {
                Token t = _pool.add(value);
                _resolver.insert({key, t});
                return t;
            }

            Token add(K key, V value) {
                insert(key, value);
            }

            Token get_token(K key) const {
                if ( _resolver.count(key) > 0){
                    return _resolver.at(key);
                }
                else {
                    throw std::out_of_range("");
                }
            }

            const K& get_key(const Token& t) {
                // really bad
                for (const auto& pair : _resolver) {
                    if (pair.second == t) {
                        return pair.first;
                    }
                }

                // todo: fix this warning
                // also todo: better exceptions
                throw std::out_of_range("");
            }

            const V& get(const Token& t ) const {
                return _pool.get(t);
            }

            const V& get(const K& key) const {
                Token t = get_token(key);
                return get(t);
            }

            V& get_mut(const Token& t) {
                return _pool.get(t);
            }

            V& get_mut(const K& key) {
                Token t = get_token(key);
                return get_mut(t);
            }

            bool remove(const Token& t) {

            }

        private:
            IdPool<V> _pool;
            std::map<K,Token> _resolver;
            
    };

}
