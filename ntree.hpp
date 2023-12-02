#pragma once
#include <vector>


#ifdef UNIT_TESTS
	#define PRINT_DEBUG(mesg) std::cout << mesg << "\n"
#else
	#define PRINT_DEBUG(mesg)
#endif

/*
	tree where each branch has a number

	1 -> 1
		 2
		 3	-> 1
		 	   2
			   3
			   4
		 4

	etc



*/

#ifdef NTREE_SEPERATE_NAMESPACE
namespace OrderedTree {
#endif

// class for dealing with thing that
// need to be allocated {rewrite this}
template <typename T>
class IdPool {
	public:

		typedef unsigned long int AllocationNumber;
		typedef unsigned int SlotNumber;

		struct Token{
			// This is so it can be used in maps
			bool operator<(const Token& other) const {
				return slot_number < other.slot_number;
			}
			AllocationNumber alloc_number;
			SlotNumber slot_number;
		};

		typedef struct {
			AllocationNumber alloc_number;
			T* content;
		} AllocNode;

		T* get_mut(Token t) {
			if (!is_valid_token(t)) {
				return nullptr;
			}
			return (pool[t.slot_number].content);
		}

		const T* get(Token t) const {
			if (!is_valid_token(t)) {
				return nullptr;
			}
			return (pool[t.slot_number].content);
		}

		Token add(const T& proto) {
			AllocationNumber alloc_number = _get_next_alloc_number();

			Token t = _find_or_create_free_spot();
			t.alloc_number = alloc_number;
			
			pool[t.slot_number] = (AllocNode) {
				.alloc_number = alloc_number,
				.content = new T(proto),
			};
			return t;
		}

		bool remove(Token t) {
			if (!is_valid_token(t)) {PRINT_DEBUG("Invalid token."); return false;}
			T* d = pool[t.slot_number].content;
			if (d != nullptr) {
				delete d;
				pool[t.slot_number].content = nullptr;
				return true;
			}
			else {
				return false;
			}
		}

		bool is_valid_token(Token t) const {
			unsigned int& slot_number = t.slot_number;
			AllocationNumber& alloc_number = t.alloc_number;

			//check if slot is valid
			if (slot_number < 0 || slot_number > pool.size()) {
				return false;
			}

			AllocNode node = pool[slot_number];

			// Check if token number matches slot
			return (alloc_number == node.alloc_number);

		}

	private:

		AllocationNumber last_used_alloc_number = 0;
		AllocationNumber _get_next_alloc_number() {
			AllocationNumber next = last_used_alloc_number + 1;
			if (last_used_alloc_number > next) {
				// todo: handle overflow
			}

			return next;
		}

		Token _find_or_create_free_spot() {
			AllocationNumber alloc_number = _get_next_alloc_number();
			SlotNumber slot_number = 0;

			for (AllocNode& node : pool) {
				if (node.content == nullptr) {
					node.alloc_number = alloc_number;
					return (Token) {
						.alloc_number = alloc_number,
						.slot_number = slot_number,
					};
				}

				slot_number++;
			}

			pool.push_back((AllocNode) {
				.alloc_number = alloc_number,
				.content = nullptr,
			});

			return Token {
				.alloc_number = alloc_number,
				.slot_number = slot_number,
			};

		}
		std::vector<AllocNode> pool;
};



/*
template <typename T>
class OrderedTree {
	public:
		class Node {
			public:
				bool is_leaf() {
					return !(data > 0) ;
				}
			private:
				int data_idx = -1; // nothing.
		};
    
	private:

		struct {
			// Should a node have its contents moved
			// to its first child if it ceases to be a leaf?
			bool create_child_shift_data = false;
		} config;


		
};

#ifdef NTREE_SEPERATE_NAMESPACE
}
#endif
*/