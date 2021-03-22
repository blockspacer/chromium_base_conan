#include "basic/dependency_hierarchy/dependency_util.h" // IWYU pragma: associated
#include <basic/recursion_checker.h>

#include <base/logging.h>

#include <algorithm>

namespace basic {

using namespace basic::dependency_error_space;
using namespace basic::error;

namespace {

// detect infinite recursion while walking tree
static FUNCTION_RECURSION_CHECKER_LIMIT_999(nestedTreeLevelsLimit);

// detect infinite recursion while walking tree
static FUNCTION_RECURSION_CHECKER_LIMIT_999(flattenNestedDependenciesLimit);

} // namespace

std::vector<
  DependencySet
> nestedTreeLevels(scoped_refptr<Dependencies> dep)
{
  DCHECK_FUNCTION_RECURSION(nestedTreeLevelsLimit);

  DCHECK(dep);

  std::vector<
    DependencySet
  > levels;

  // will store dependencies at some hierarchy level
  DependenciesSet dependenciesToProcess{dep};

  // prevent infinite loops in dependency tree
  static const size_t kMaxTreeLevel = std::numeric_limits<size_t>::max();

  /// \note recursion replaced with iteration
  size_t treeLevelIndex = 0;
  do {
    DependenciesSet dependenciesToAdd;
    DependencySet dependenciesAtLevel;
    // iterate elements in current hierarchy level
    for(auto dep_it = dependenciesToProcess.begin(); dep_it != dependenciesToProcess.end(); dep_it++)
    {
      DCHECK(*dep_it);

      const DependencySet& storage = (*dep_it)->storage();
      // process dependencies from element in current hierarchy level
      for(auto store_it = storage.begin(); store_it != storage.end(); store_it++)
      {
        DCHECK(*store_it);

        dependenciesAtLevel.insert(*store_it);

        // add dependencies from element in nested hierarchy level
        if((*store_it)->dependencies()->size()) {
          dependenciesToAdd.insert((*store_it)->dependencies());
        }
      }
    }

    if(!dependenciesAtLevel.empty())
    {
      levels.push_back(RVALUE_CAST(dependenciesAtLevel));
    }

    // reset dependencies to dependencies from nested hierarchy levels
    {
      dependenciesToProcess.clear();
      dependenciesToProcess = dependenciesToAdd;
    }

    treeLevelIndex++;
    DCHECK(treeLevelIndex < kMaxTreeLevel)
      << "detected infinite loop in dependency tree";
  } while (!dependenciesToProcess.empty() && treeLevelIndex < kMaxTreeLevel);

  return levels;
}

std::vector<
  DependencySet
> nestedTreeLevels(scoped_refptr<Dependency> dep)
{
  return nestedTreeLevels(dep->dependencies());
}

std::vector<scoped_refptr<Dependency>> flattenNestedDependencies(
  scoped_refptr<Dependencies> dep)
{
  DCHECK_FUNCTION_RECURSION(flattenNestedDependenciesLimit);

  DCHECK(dep);

  std::vector<
    DependencySet
  > levels = nestedTreeLevels(dep);

  std::vector<scoped_refptr<Dependency>> result;

  // Walk tree from leafs to root.
  // Deep tree leafs must be processed first because each leaf
  // is `Dependency` (think about dependency hierarchy for plugin system)
  // and dependency must be loaded before dependant (parent element).
  for(auto levelIt = levels.rbegin(); levelIt != levels.rend(); levelIt++)
  {
    DependencySet& level = *levelIt;
    for(const scoped_refptr<Dependency>& dependency : level)
    {
      auto found = std::find(result.begin(), result.end(), dependency);
      // Process each tree leaf only if it was not processed before.
      if (found != result.end()) {
        continue;
      }
      result.push_back(dependency);
    }
  }

  std::reverse(result.begin(), result.end());

  return result;
}

std::vector<scoped_refptr<Dependency>> flattenNestedDependencies(
  scoped_refptr<Dependency> dep)
{
  return flattenNestedDependencies(dep->dependencies());
}

}  // namespace basic
