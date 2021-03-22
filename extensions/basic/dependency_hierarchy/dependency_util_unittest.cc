// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0

#include "basic/dependency_hierarchy/dependency_util.h"
#include "basic/strong_types/strong_bool.h"
#include <basic/recursion_checker.h>

#include <base/test/gtest_util.h>
#include <base/strings/string_number_conversions.h>

#include "testing/gtest/include/gtest/gtest.h"

#include <cstdio>
#include <algorithm>
#include <numeric>

namespace basic {

namespace {

STRONGLY_TYPED_BOOL(NeedSortNames);

// detect infinite recursion while walking tree
static FUNCTION_RECURSION_CHECKER_LIMIT_999(printDependencyTreeHorizontallyLimit);

}  // namespace

class DependencyUtilTest : public testing::Test {
 public:
  void SetUp() override {
    dependencyA
      = ::base::MakeRefCounted<Dependency>();

    dependencyB
      = ::base::MakeRefCounted<Dependency>();

    dependencyC
      = ::base::MakeRefCounted<Dependency>();

    dependencyD
      = ::base::MakeRefCounted<Dependency>();

    dependencyE
      = ::base::MakeRefCounted<Dependency>();

    dependencyF
      = ::base::MakeRefCounted<Dependency>();

    dependencyG
      = ::base::MakeRefCounted<Dependency>();

    dependencyH
      = ::base::MakeRefCounted<Dependency>();

    dependencyNames.clear();
    dependencyNames[dependencyA] = "A";
    dependencyNames[dependencyB] = "B";
    dependencyNames[dependencyC] = "C";
    dependencyNames[dependencyD] = "D";
    dependencyNames[dependencyE] = "E";
    dependencyNames[dependencyF] = "F";
    dependencyNames[dependencyG] = "G";
    dependencyNames[dependencyH] = "H";

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
    // A -> B -> D
    EXPECT_OK(dependencyA->addDependency(dependencyB));
    EXPECT_OK(dependencyB->addDependency(dependencyD));
    //
    // B -> C -> D
    EXPECT_OK(dependencyB->addDependency(dependencyC));
    EXPECT_OK(dependencyC->addDependency(dependencyD));
    //
    // B -> E -> C
    EXPECT_OK(dependencyB->addDependency(dependencyE));
    EXPECT_OK(dependencyE->addDependency(dependencyC));
    //
    // D -> F
    EXPECT_OK(dependencyD->addDependency(dependencyF));
    //
    // D -> H
    EXPECT_OK(dependencyD->addDependency(dependencyH));
    //
    // A -> G
    EXPECT_OK(dependencyA->addDependency(dependencyG));
    //
    // G -> D
    EXPECT_OK(dependencyG->addDependency(dependencyD));
    //
    // G -> E
    EXPECT_OK(dependencyG->addDependency(dependencyE));
    //
    // B -> G
    EXPECT_OK(dependencyB->addDependency(dependencyG));
  }

  template<typename T>
  std::vector<std::string> mapNames(
    const T& vec
    , NeedSortNames need_sort)
  {
    std::vector<std::string> result;
    for(auto dep: vec) {
      result.push_back(dependencyNames[dep]);
    }
    if(need_sort) {
      std::sort(result.begin(), result.end());
    }
    return result;
  }

  void printDependencyTreeHorizontally(const std::string& prefix
    , scoped_refptr<Dependency> node
    , bool isLeft
    , std::string& result
    , scoped_refptr<Dependency> parent)
  {
    DCHECK_FUNCTION_RECURSION(printDependencyTreeHorizontallyLimit);

    if(node)
    {
      result += prefix;

      result += (isLeft ? "|-" : "|_" );

      if(parent)
        result += ::base::StrCat({dependencyNames[parent], "->", dependencyNames[node]});
      else
        result += ::base::StrCat({"____", dependencyNames[node]});

      result += "\n";

      // enter the next tree level - left and right branch
      const DependencySet& storage = node->dependencies()->storage();

      /// \note replaces pointer comparison with custom comparator
      /// to make tests deterministic
      std::vector<scoped_refptr<Dependency>> vector;
      vector.insert(vector.end(), storage.begin(), storage.end());
      std::sort(vector.begin(), vector.end(),
        [this](const scoped_refptr<Dependency> & a, const scoped_refptr<Dependency> & b) -> bool
      {
          return dependencyNames[a] < dependencyNames[b];
      });

      // process dependencies from element in current hierarchy level
      size_t index = 0;
      for(auto store_it = vector.begin(); store_it != vector.end(); store_it++)
      {
        const bool isLeft = !(*store_it)->dependencies()->storage().size();
        printDependencyTreeHorizontally(prefix + (isLeft ? "|     " : "      ")
          , *store_it
          , isLeft
          , result
          , node);
        index++;
      }
    }
  }

 public:
  std::map<scoped_refptr<Dependency>, std::string> dependencyNames;

  scoped_refptr<Dependency> dependencyA;

  scoped_refptr<Dependency> dependencyB;

  scoped_refptr<Dependency> dependencyC;

  scoped_refptr<Dependency> dependencyD;

  scoped_refptr<Dependency> dependencyE;

  scoped_refptr<Dependency> dependencyF;

  scoped_refptr<Dependency> dependencyG;

  scoped_refptr<Dependency> dependencyH;
};

using namespace basic::dependency_error_space;
using namespace basic::error;

TEST_F(DependencyUtilTest, PrintDependencyTreeHorizontally) {
  std::string result;
  printDependencyTreeHorizontally("", dependencyA, false, result, nullptr);
  EXPECT_EQ(result,
"|_____A\n\
      |_A->B\n\
            |_B->C\n\
                  |_C->D\n\
                  |     |-D->F\n\
                  |     |-D->H\n\
            |_B->D\n\
            |     |-D->F\n\
            |     |-D->H\n\
            |_B->E\n\
                  |_E->C\n\
                        |_C->D\n\
                        |     |-D->F\n\
                        |     |-D->H\n\
            |_B->G\n\
                  |_G->D\n\
                  |     |-D->F\n\
                  |     |-D->H\n\
                  |_G->E\n\
                        |_E->C\n\
                              |_C->D\n\
                              |     |-D->F\n\
                              |     |-D->H\n\
      |_A->G\n\
            |_G->D\n\
            |     |-D->F\n\
            |     |-D->H\n\
            |_G->E\n\
                  |_E->C\n\
                        |_C->D\n\
                        |     |-D->F\n\
                        |     |-D->H\n\
");
}

TEST_F(DependencyUtilTest, NestedTreeLevels) {
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
  EXPECT_EQ(nestedTreeLevels(dependencyA).size(), 6);

  // Hierarchy implicitly expands to
  //
  // A -- B
  // A -- G
  EXPECT_EQ(mapNames(nestedTreeLevels(dependencyA)[0], NeedSortNames::kTrue)
    , mapNames(DependencySet{
      dependencyB,
      dependencyG,
    }, NeedSortNames::kTrue));

  // Hierarchy implicitly expands to
  //
  // A -- B
  //      B -- D
  //      B -- C
  //      B -- G
  //      B -- E
  // A -- G
  //      G -- E
  //
  EXPECT_EQ(mapNames(nestedTreeLevels(dependencyA)[1], NeedSortNames::kTrue)
    , mapNames(DependencySet{
      dependencyC,
      dependencyD,
      dependencyE,
      dependencyG,
    }, NeedSortNames::kTrue));

  // Hierarchy implicitly expands to
  //
  // A -- B
  //      B -- D -- F
  //           D -- H
  //      B -- C -- D
  //      B -- G
  //           G -- D
  //           G -- E
  //      B -- E -- C
  // A -- G
  //      G -- E -- C
  //
  EXPECT_EQ(mapNames(nestedTreeLevels(dependencyA)[2], NeedSortNames::kTrue)
    , mapNames(DependencySet{
      dependencyC,
      dependencyD,
      dependencyE,
      dependencyF,
      dependencyH,
    }, NeedSortNames::kTrue));

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
  //           G -- E -- C
  //      B -- E -- C -- D
  //
  // A -- G
  //      G -- E -- C -- D
  //                     D
  EXPECT_EQ(mapNames(nestedTreeLevels(dependencyA)[3], NeedSortNames::kTrue)
    , mapNames(DependencySet{
      dependencyC,
      dependencyD,
      dependencyF,
      dependencyH,
    }, NeedSortNames::kTrue));

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
  //           G -- E -- C -- D
  //      B -- E -- C -- D -- F
  //                     D -- H
  // A -- G
  //      G -- E -- C -- D -- F
  //                     D -- H
  EXPECT_EQ(mapNames(nestedTreeLevels(dependencyA)[4], NeedSortNames::kTrue)
    , mapNames(DependencySet{
      dependencyD,
      dependencyF,
      dependencyH,
    }, NeedSortNames::kTrue));

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
  EXPECT_EQ(mapNames(nestedTreeLevels(dependencyA)[5], NeedSortNames::kTrue)
    , mapNames(DependencySet{
      dependencyF,
      dependencyH,
    }, NeedSortNames::kTrue));
}

TEST_F(DependencyUtilTest, FlattenNestedDependencies) {

  auto result = mapNames(flattenNestedDependencies(dependencyA), NeedSortNames::kFalse);
  /// \note Order of some elements does not matter.
  /// So we can not compare containers for equality.
  /// Source of non-determinism is the reliance on pointer comparison.
  /// Tests need determinism.
  EXPECT_EQ(result.size(), 7);
  size_t indexB = std::distance(result.begin()
    , std::find(result.begin(), result.end(), dependencyNames[dependencyB]));
  EXPECT_NE(indexB, result.size());
  size_t indexG = std::distance(result.begin()
    , std::find(result.begin(), result.end(), dependencyNames[dependencyG]));
  EXPECT_NE(indexG, result.size());
  size_t indexE = std::distance(result.begin()
    , std::find(result.begin(), result.end(), dependencyNames[dependencyE]));
  EXPECT_NE(indexE, result.size());
  size_t indexC = std::distance(result.begin()
    , std::find(result.begin(), result.end(), dependencyNames[dependencyC]));
  EXPECT_NE(indexC, result.size());
  size_t indexD = std::distance(result.begin()
    , std::find(result.begin(), result.end(), dependencyNames[dependencyD]));
  EXPECT_NE(indexD, result.size());
  size_t indexH = std::distance(result.begin()
    , std::find(result.begin(), result.end(), dependencyNames[dependencyH]));
  EXPECT_NE(indexH, result.size());
  size_t indexF = std::distance(result.begin()
    , std::find(result.begin(), result.end(), dependencyNames[dependencyF]));
  EXPECT_NE(indexF, result.size());

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
  // Result of `flattenNestedDependencies`:
  // dependencyB,
  // dependencyG,
  // dependencyE,
  // dependencyC,
  // dependencyD,
  // dependencyH,
  // dependencyF,
  //
  // -> B
  EXPECT_LT(indexB, indexD);
  EXPECT_LT(indexB, indexC);
  EXPECT_LT(indexB, indexE);
  EXPECT_LT(indexB, indexG);
  // -> C
  EXPECT_LT(indexC, indexD);
  // -> D
  EXPECT_LT(indexD, indexF);
  EXPECT_LT(indexD, indexH);
  // -> G
  EXPECT_LT(indexG, indexD);
  EXPECT_LT(indexG, indexE);
  // -> E
  EXPECT_LT(indexE, indexC);
}

TEST_F(DependencyUtilTest, FlattenCombined) {
  scoped_refptr<Dependencies> dependenciesCombined
    = ::base::MakeRefCounted<Dependencies>();

  // repeat
  EXPECT_OK(dependenciesCombined->addDependency(dependencyA));
  EXPECT_OK(dependenciesCombined->addDependency(dependencyA));

  // repeat
  EXPECT_OK(dependenciesCombined->addDependency(dependencyB));
  EXPECT_OK(dependenciesCombined->addDependency(dependencyB));

  // repeat
  EXPECT_OK(dependenciesCombined->addDependency(dependencyC));
  EXPECT_OK(dependenciesCombined->addDependency(dependencyC));

  scoped_refptr<Dependency> dependencyJ
    = ::base::MakeRefCounted<Dependency>();
  dependencyNames[dependencyJ] = "J";
  EXPECT_OK(dependencyC->addDependency(dependencyJ));
  EXPECT_OK(dependencyD->addDependency(dependencyJ));
  EXPECT_OK(dependencyJ->addDependency(dependencyF));
  EXPECT_OK(dependencyH->addDependency(dependencyJ));

  // does nothing
  EXPECT_ERROR_CODE(ERR_CIRCULAR_DEPENDENCY, dependencyJ->addDependency(dependencyA));

  // Given dependency hierarchy
  //
  // L -> Q -> O -> M
  //      Q -> M
  scoped_refptr<Dependency> dependencyO
    = ::base::MakeRefCounted<Dependency>();
  dependencyNames[dependencyO] = "O";
  scoped_refptr<Dependency> dependencyM
    = ::base::MakeRefCounted<Dependency>();
  dependencyNames[dependencyM] = "M";
  scoped_refptr<Dependency> dependencyQ
    = ::base::MakeRefCounted<Dependency>();
  dependencyNames[dependencyQ] = "Q";
  scoped_refptr<Dependency> dependencyL
    = ::base::MakeRefCounted<Dependency>();
  dependencyNames[dependencyL] = "L";

  EXPECT_OK(dependencyO->addDependency(dependencyM));
  EXPECT_OK(dependencyL->addDependency(dependencyQ));
  EXPECT_OK(dependencyQ->addDependency(dependencyO));
  EXPECT_OK(dependencyQ->addDependency(dependencyM));

  EXPECT_OK(dependenciesCombined->addDependency(dependencyL));
  EXPECT_OK(dependenciesCombined->addDependency(dependencyQ));

  // Given dependency hierarchy
  //
  // A -> B -> D
  //      B -> C -> D
  //                D -> F
  //                D -> J
  //                D -> H -> J -> F
  //           C -> J
  //      B -> E -> C
  // A -> G
  //      G -> D
  //      G -> E
  //      B -> G
  // L -> Q -> O -> M
  //      Q -> M
  //
  EXPECT_EQ(mapNames(flattenNestedDependencies(dependenciesCombined), NeedSortNames::kTrue)
    , mapNames(std::vector<scoped_refptr<Dependency>>{
      dependencyA,
      dependencyL,
      dependencyB,
      dependencyQ,
      dependencyO,
      dependencyG,
      dependencyM,
      dependencyE,
      dependencyC,
      dependencyD,
      dependencyH,
      dependencyJ,
      dependencyF,
    }, NeedSortNames::kTrue));
}

} // basic
