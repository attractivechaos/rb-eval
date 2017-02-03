This micro-benchmark generates 2 million random integers with duplicates. We
insert an integer to the tree if it is absent; remove it from the tree if
present. The following table shows run time on my Macbook. I took the fastest
out of three runs for each program.

|Program|User time (s)|Comment|
|:------|:------------|:------|
|rb-c   |2.31|libavl two-pointer red-black tree; with `void*`|
|rb-cpp |1.60|libavl translated to C++ template|
|rb-c-mp|2.20|libavl, combined with a memory pool|
|rb-map |1.58|`std::map`|
|btree-c|0.81|kbtree|
