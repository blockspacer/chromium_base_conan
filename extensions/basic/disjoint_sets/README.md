# About

Disjoint-Set datastructure, also called a union–find data structure
or merge–find set, is a data structure that stores a collection
of disjoint (non-overlapping) sets.

Each set is represented by its representative (leader or parent) which is one of its members.

It often does not matter which element is the
representative, but if we ask for the representative twice without
modifying the set, we should get the same
answer.
In some applications, representative is the smallest member
In some applications, representative is a user selected member (ex.: photo albums where user can select cover photo for any album)
How to calculate root of a element? Simply we can run a loop until we get a element which is a parent of itself.

Disjoint-set organizes items into trees where every item has a parent.

Two items belong to the same set when they have same parent.

Provided operations:

* Adding new sets.
* Merging sets (replacing them by their union).
  Merging two items into set is about assigning one as a parent of the other one:
* Finding a representative member of a set.
  Finds out efficiently if any two elements are in the same or different sets.

See:
* https://observablehq.com/@bryangingechen/union-find-data-structure
* https://www.mathblog.dk/disjoint-set-data-structure/
* https://red-green-rewrite.github.io/2016/09/30/Curious-case-of-disjoint-set/
* https://blogarithms.github.io/articles/2017-12/diving-into-disjoint-sets
* https://en.wikipedia.org/wiki/Disjoint-set_data_structure
* http://www.algorithmsandme.com/disjoint-set-data-structure/
* http://www.algorithmsandme.com/tag/disjoint-set-data-structure/
* https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-design-and-analysis-of-algorithms-spring-2012/lecture-notes/MIT6_046JS12_lec16.pdf
* https://web.stanford.edu/class/archive/cs/cs166/cs166.1146/lectures/16/Small16.pdf
* http://hjemmesider.diku.dk/~pawel/ad/ds.pdf
* https://courses.cs.washington.edu/courses/cse373/18sp/files/slides/lecture-25.pdf
* https://url.cs.qc.cuny.edu/teaching/CSCI323Spring2018Afternoon/Ch21.pdf
* http://umsl.edu/~adhikarib/cs4130-fall2017/slides/04%20-%20Data%20Structures%20for%20Disjoint%20Sets.pdf
* https://cp-algorithms.com/data_structures/disjoint_set_union.html
* https://www.topcoder.com/thrive/articles/Disjoint-set%20Data%20Structures

## Implementations

Disjoint sets may be represented by several
different data structures: lookup table,
linked-list, trees.

### Kruskal algorithm

Union-find is used in Kruskal algorithm,
which repeatedly adds edge of minimum weight which doesn't make a cycle.

Kruskal's Algorithm is used to find the minimum spanning tree
for a connected weighted graph.

Spanning tree is the sum of weights of all the edges in a tree.

A minimum spanning tree (MST) is one which costs the least among all spanning trees.

The main target of the algorithm is to find the subset of edges by using which,
we can traverse every vertex of the graph.

Kruskal's algorithm follows greedy approach which finds
an optimum solution at every stage instead of focusing on a global optimum.

Usage example:
The best use for Kruskal algorithm would be finding out the shortest path
for laying down telephone or cable wires.
In this way, the telephone or the cable company saves huge amount
on the cost of wires and at the same time,
the redundancy of path from which information travels
decreases and hence much less noise.

Usage example:
They are also often used in computer networking.
For example, if you have a large LAN with many switches,
finding a minimum spanning tree will be vital to ensure
that only a minimum number of packets will be transmitted across the network.

Note: Prim’s Algorithm is another algorithm that also can be used to solve Minimum Spanning Tree problem.

Usage example:
You plan to visit all the important world heritage sites but are short on time.
To make your itinerary work, you decide to use Kruskal’s algorithm using disjoint sets.

See:
* https://www.hackerearth.com/blog/developers/kruskals-minimum-spanning-tree-algorithm-example/

## When to use Disjoint-Set

Use Disjoint-Set when data can not be removed.

For example, you can use Disjoint-Set to find common ancestors (i.e. common ancestors of multiple family trees).

Lets assume that each human must have biological mother and father (even if they are donors).

Even if somebody made mistake in family tree - you do not need to remove elements from Disjoint-Set, just fix typos.

## No deletion operation

Note that you may need another data structure if you need to support element removal operation.

See:
* https://stackoverflow.com/questions/12689651/disjoint-set-data-structure-supporting-deletion
* https://www.cs.princeton.edu/courses/archive/fall05/cos528/handouts/Union-Find%20with%20Constant%20Time%20Deletions.pdf

## No split operation

Standard disjoint set structure doesn't support de-unioning.

You may need dynamic trees or link-cut trees for split operation.

## How to Parallelize it

See:
* https://stanford.edu/~rezab/classes/cme323/S15/projects/parallel_union_find_presentation.pdf

## Visualization of the union-find (or disjoint-set) data structure

See:

* https://observablehq.com/@bryangingechen/union-find-data-structure
* https://www.cs.usfca.edu/~galles/visualization/DisjointSets.html

## No item inside disjoint-set can be in more than one set

For example set {1, 2, 3} and set {1, 5, 6} are not disjoint
because they have in common {1}, but the sets {1, 2, 3} and {5, 6}
are disjoint because their intersection is null.

## Why not graph data structure?

When we talk about the connections or relationships,
we immediately will think of graph data structure.
The node is the person and the edge is the relationship between two persons.
So, first, we have to figure out whether
it will be a directed graph or an undirected graph.
In this problem, the friendship is a mutual relationship,
thus the graph is undirected.

When you are reading this problem,
the concept of Strongly Connected Components (SCC) will come into your mind.
If A is a friend of B, B is a friend of C,
then A will be a friend of C.
A is indirectly connected to C.
It means that every friend can reach every other friend
through a path if they are directly or indirectly connected.
So in this way, they are forming a strong group or circle,
in which every vertex is connected directly or indirectly in its group/circle.
Notice that all friends (both direct and indirect), who should be
in one friend circle are also in one connected component in the graph.

### Using Depth first traversal method

Finding connected components for an undirected graph is very easy.
We can do either BFS (Breadth First traversal) or DFS (Depth first traversal)
starting from every unvisited vertex,
and we get all strongly connected components.

Time Complexity: Since we just go along the edges and visit every node, it will be O(n).
Space Complexity: O(n), to store the visited nodes.

### Using Disjoint Sets (Union Find) that use union by Rank algorithm.

Time Complexity: For each of the edge, we need to find the parents  and do the union, which is O(mlogn).
Space Complexity: We used a map to store the parent information, O(n).

### Cycles problem

See:
* https://red-green-rewrite.github.io/2016/09/30/Curious-case-of-disjoint-set/

## Example: friends without removal

There are N students in a class.
Some of them are friends, while some are not.
Their friendship is transitive in nature.
For example, if A is a direct friend of B, and B is a direct friend of C,
then A is an indirect friend of C.
And we defined a friend circle is a group of students who are direct
or indirect friends.

How might you keep track of the groups as they grow and merge together?
How might you quickly determine whether two given people are in the same friend group?

A first observation is that the friend groups are connected components
of the "friendship graph", a graph (or network) whose nodes (or vertices)
are the individuals and whose links (or edges) are all friendships between them.

Na?vely, you might create an array or list for each component
and then join them when two people from different groups befriend each other.
However, when the groups get large, merging arrays (to update the groups)
is slow, as is searching lists (to determine what cluster a person is in).

## Example: Maze generator

See:
* https://people.cs.vt.edu/shaffer/Book/Assignments/Mazes.pdf

## Example: Tarjan's off-line least common ancestors algorithm

https://en.wikipedia.org/wiki/Tarjan%27s_off-line_lowest_common_ancestors_algorithm

## Example: Connected component labeling

http://www.codeding.com/articles/connected-sets-labeling

## Example: Online maintenance of biconnected components

https://www.geeksforgeeks.org/biconnected-components/

## Example: Detect Cycle in an Undirected Graph

https://www.geeksforgeeks.org/union-find/
https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
