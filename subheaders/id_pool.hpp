#pragma once
#include <vector>

namespace more_collections {

    template <typename T>
    class IdPool {
        public:
            typedef long unsigned int AllocationNumber;
            typedef long unsigned int SlotNumber;

            struct AllocationNode {
                AllocationNumber alloc_number = 0;
                T* content = nullptr;
            };

            struct Token {
                AllocationNumber alloc_number;
                SlotNumber slot_number;
                std::string to_string() {
                    std::string str = "Token with slot number " + std::to_string(slot_number) + " and alloc number " + std::to_string(alloc_number);
                    return str;
                }
            };

            const T& get(const Token& t) const {
                return _resolve_token(t);
            }

            T& get_mut(const Token& t) {
                return _resolve_token(t);
            }

            const Token add(const T& proto) {
                Token slot = _get_or_create_slot();
                //DEBUG_PRINT("Got slot number " << slot.slot_number);
                pool[slot.slot_number].content = new T(proto);

                return slot;
            }

            bool remove(const Token& token) {
                if (!is_valid_token(token)) {
                    return false;
                }
                AllocationNode& node = pool[token.slot_number];
                delete node.content;
                node.content = nullptr;
                return true;
            }

            bool is_valid_token(Token t) const {
                if (t.alloc_number > pool.size()) {
                    return false;
                }

                const AllocationNode& node = pool[t.slot_number];
                return (node.alloc_number == t.alloc_number) && (node.content != nullptr);
            }

        private:

            Token _get_or_create_slot() {
                for (unsigned int i = 0; i < pool.size(); i++) {
                    if (pool[i].content == nullptr) {
                        //DEBUG_PRINT("Slot number " << i << "is available.");
                        AllocationNumber alloc_number = _get_next_alloc_number();
                        pool[i].alloc_number = alloc_number;
                        return Token {
                            .alloc_number = alloc_number,
                            .slot_number = i,
                        };
                    }
                }

                //DEBUG_PRINT("No slots available, creating new");
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

            T& _resolve_token(Token t) const {
                if (!is_valid_token(t)) {
                    //DEBUG_PRINT("Invalid token.");
                    throw std::out_of_range(t.to_string());
                }

                return *pool[t.slot_number].content;
            }

            AllocationNumber next_alloc_number = 1;
            AllocationNumber _get_next_alloc_number() {
                const AllocationNumber r = next_alloc_number;
                next_alloc_number++;
                return r;
            }

            std::vector<AllocationNode> pool;
    };
    
}

