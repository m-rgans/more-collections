#pragma once
#include <vector>

namespace more_collections {

    template <typename T>
    class IdPool {
        public:
            typedef long unsigned int AllocationNumber;
            typedef long unsigned int SlotNumber;

            struct AllocationNode {
                AllocationNumber alloc_number;
                T* content;
            };

            struct Token {
                AllocationNumber alloc_number;
                SlotNumber slot_number;
            };

            const T* get(const Token& t) const {
                return _resolve_token(t);
            }

            T* get_mut(const Token& t) {
                return _resolve_token(t);
            }

            const Token add(const T& proto) {
                Token slot = _get_or_create_slot();
                pool[slot.slot_number].content = new T(proto);

                return slot;
            }

            bool is_valid_token(Token t) const {
                if (t.alloc_number > pool.size()) {
                    return false;
                }
                return pool[t.slot_number].alloc_number == t.alloc_number;
            }

        private:

            Token _get_or_create_slot() {
                for (unsigned int i = 0; i < pool.size(); i++) {
                    if (pool[i].content != nullptr) {
                        AllocationNumber alloc_number = _get_next_alloc_number();
                        pool[i].alloc_number = alloc_number;
                        return Token {
                            .alloc_number = alloc_number,
                            .slot_number = i,
                        };
                    }
                }

                AllocationNode next_alloc = {
                    .alloc_number = _get_next_alloc_number(),
                    .content = nullptr,
                };

                pool.push_back(next_alloc);
                return Token {
                    .alloc_number = next_alloc.alloc_number,
                    .slot_number = pool.size() - 1
                };
            }

            T* _resolve_token(Token t) const {
                if (!is_valid_token(t)) {
                    return nullptr;
                }

                return pool[t.slot_number].content;

            }

            AllocationNumber next_alloc_number = 0;
            AllocationNumber _get_next_alloc_number() {
                const AllocationNumber r = next_alloc_number;
                next_alloc_number++;
                return r;
            }

            std::vector<AllocationNode> pool;
    };
    
}

