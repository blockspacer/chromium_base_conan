#pragma once

#include <basic/dependency_hierarchy/dependency_hierarchy.h>

#include <set>
#include <string>

namespace basic {

// Transform dependency hierarchy into vector of hierarchy levels
//
// Given dependency hierarchy
//
// A -> B -> D
//      B -> C -> D
//                D -> F
//                D -> H
//      B -> E -> C
// A -> G
//      G -> D
//      G -> E
//      B -> G
//
// Hierarchy implicitly expands to
//
// A -- B
//      B -- D -- F
//           D -- H
//      B -- C -- D -- F
//                D -- H
//      B -- G
//           G -- D -- F
//                D -- H
//           G -- E -- C -- D -- F
//                          D -- H
//      B -- E -- C -- D -- F
//                     D -- H
// A -- G
//      G -- E -- C -- D -- F
//                     D -- H
//
// nestedTreeLevels(A)[0] is [B,G]
// nestedTreeLevels(A)[1] is [C,D,E,G]
// nestedTreeLevels(A)[2] is [C,D,E,F,H]
// nestedTreeLevels(A)[3] is [C,D,F]
// nestedTreeLevels(A)[4] is [D,F]
// nestedTreeLevels(A)[5] is [F]
//
/// \note elements does not repeat at same hierarchy level,
/// but can repeat between levels
//
std::vector<
  DependencySet
> nestedTreeLevels(scoped_refptr<Dependencies> dep);

std::vector<
  DependencySet
> nestedTreeLevels(scoped_refptr<Dependency> dep);

// Transform dependency hierarchy into vector of sorted dependencies
// (from bottom hierarchy elements to hierarchy root element)
//
// Given dependency hierarchy
//
// A -> B -> D
//      B -> C -> D
//                D -> F
//                D -> H
//      B -> E -> C
// A -> G
//      G -> D
//      G -> E
//      B -> G
//
// Hierarchy implicitly expands to
//
// A -- B
//      B -- D -- F
//           D -- H
//      B -- C -- D -- F
//                D -- H
//      B -- G
//           G -- D -- F
//                D -- H
//           G -- E -- C -- D -- F
//                          D -- H
//      B -- E -- C -- D -- F
//                     D -- H
// A -- G
//      G -- E -- C -- D -- F
//                     D -- H
//
// will flattenNestedDependencies to (walking from last level to first)
//
// iteration 1 (order of F and H does not matter)
//                               [F, H] or [H, F]
// iteration 2
//                          D
// iteration 3
//                     C
// iteration 4
//                E
// iteration 5
//           G
// iteration 6
//      B
//
// flattenNestedDependencies(A) = [B,G,E,C,D,F,H]
// This is also correct (order of some elements does not matter):
// flattenNestedDependencies(A) = [B,G,E,C,D,H,F]
//
std::vector<scoped_refptr<Dependency>> flattenNestedDependencies(
  scoped_refptr<Dependencies> dep);

std::vector<scoped_refptr<Dependency>> flattenNestedDependencies(
  scoped_refptr<Dependency> dep);

}  // namespace basic
