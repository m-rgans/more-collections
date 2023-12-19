# more-collections
A collection of miscellaneous collection templates.

## Templates
All templates have unique accessors for if the contained data needs to be mutable.

### Id Pool \<T\>

The Idpool Allocates and stores a number of objects of type T as needed, providing a unique token for accessing an individual object it stores.
- Order is not important
- Duplicates are allowed

### Glossary \<K\> \<V\>

A glossary is basically an ID pool with a hashmap that associates its access tokens with a value of type K. This can be used in place of a hashmap alone in situations where the map is accessed often enough that hashing time is an issue.

The glossary can instead use the K type value to find the appropriate access token once, which can then be stored by the thing which needs access to it, allowing constant access time to the member in the future.

For an analogy, this can be thought of like having a phone booth with a phone book in it down the street from where you live. If you want to call your friend, you can go to the phone booth and look up their number. After this, instead of walking to the booth every time you want to call them, you can instead write down their number on a piece of paper and take it with you.

- Duplicate Keys not allowed.
- Unordered.

### Ordered Tree \<T\> (Unimplemented)

todo

### Double Buffer \<T\> (Unimplemented)

todo