// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0

#include "basic/dependency_hierarchy/dependency_hierarchy.h"
#include "basic/files/scoped_temp_file.h"

#include <base/strings/strcat.h>
#include <base/strings/string_number_conversions.h>
#include <base/test/gtest_util.h>

#include "testing/gtest/include/gtest/gtest.h"

#include <stdio.h>

#include <algorithm>

namespace basic {

using namespace basic::dependency_error_space;
using namespace basic::error;

TEST(DependencyHierarchy, AddDependencyTwice) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependencies> dependencies1
    = ::base::MakeRefCounted<Dependencies>();

  EXPECT_EQ(dependencies1->size(), 0u);
  EXPECT_OK(dependencies1->addDependency(dependencyA));
  EXPECT_EQ(dependencies1->size(), 1u);

  // does nothing
  EXPECT_OK(dependencies1->addDependency(dependencyA));

  // can add dependency only once
  EXPECT_EQ(dependencies1->size(), 1u);
}

TEST(DependencyHierarchy, NullptrDepends) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  EXPECT_DCHECK_DEATH({ ignore_result(dependencyA->hasNestedDependency(nullptr)); });
  EXPECT_DCHECK_DEATH({ ignore_result(dependencyA->addDependency(nullptr)); });
}

TEST(DependencyHierarchy, AddSelfDependency) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  EXPECT_FALSE(dependencyA->hasNestedDependency(dependencyA));
  EXPECT_EQ(dependencyA->dependencies()->size(), 0u);

  EXPECT_ERROR_CODE(ERR_CIRCULAR_DEPENDENCY, dependencyA->addDependency(dependencyA));
  EXPECT_FALSE(dependencyA->hasNestedDependency(dependencyA));
  EXPECT_EQ(dependencyA->dependencies()->size(), 0u);
}

TEST(DependencyHierarchy, RemoveSelfDependency) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  EXPECT_FALSE(dependencyA->hasNestedDependency(dependencyA));
  EXPECT_EQ(dependencyA->dependencies()->size(), 0u);

  EXPECT_DEATH(ignore_result(dependencyA->removeDependency(dependencyA)), "Can not remove self from dependencies");
  EXPECT_FALSE(dependencyA->hasNestedDependency(dependencyA));
  EXPECT_EQ(dependencyA->dependencies()->size(), 0u);
}

TEST(DependencyHierarchy, AddRemoveDependencies) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyB
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependencies> dependencies1
    = ::base::MakeRefCounted<Dependencies>();

  EXPECT_OK(dependencies1->addDependency(dependencyA));
  EXPECT_OK(dependencies1->addDependency(dependencyB));

  scoped_refptr<Dependency> dependencyAll
    = ::base::MakeRefCounted<Dependency>();

  ignore_result(dependencyAll->removeDependencies(dependencies1));
  EXPECT_EQ(dependencyAll->dependencies()->size(), 0u);

  ignore_result(dependencyAll->addDependencies(dependencies1));
  EXPECT_EQ(dependencyAll->dependencies()->size(), 2u);
  ignore_result(dependencyAll->addDependencies(dependencies1));
  EXPECT_EQ(dependencyAll->dependencies()->size(), 2u);

  ignore_result(dependencyAll->removeDependencies(dependencies1));
  EXPECT_EQ(dependencyAll->dependencies()->size(), 0u);
  ignore_result(dependencyAll->removeDependencies(dependencies1));
  EXPECT_EQ(dependencyAll->dependencies()->size(), 0u);

  ignore_result(dependencyAll->addDependencies(dependencies1));
  EXPECT_EQ(dependencyAll->dependencies()->size(), 2u);
  ignore_result(dependencyAll->removeDependencies(dependencies1));
  EXPECT_EQ(dependencyAll->dependencies()->size(), 0u);
}

// A -> B -> C
// D -> B -> C
// A -> D
TEST(DependencyHierarchy, SimpleDependencyHierarchy) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyB
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyC
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyD
    = ::base::MakeRefCounted<Dependency>();
}

// A -> B -> A
TEST(DependencyHierarchy, SimpleCircularDependency) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyB
    = ::base::MakeRefCounted<Dependency>();

  EXPECT_FALSE(dependencyA->hasNestedDependency(dependencyB));
  EXPECT_OK(dependencyA->addDependency(dependencyB));
  EXPECT_TRUE(dependencyA->hasNestedDependency(dependencyB));
  EXPECT_FALSE(dependencyA->hasNestedDependency(dependencyA));

  EXPECT_ERROR_CODE(ERR_CIRCULAR_DEPENDENCY, dependencyB->addDependency(dependencyA));
  EXPECT_FALSE(dependencyB->hasNestedDependency(dependencyA));
}

// A -> B -> C -> A
TEST(DependencyHierarchy, CircularDependency) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyB
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyC
    = ::base::MakeRefCounted<Dependency>();

  EXPECT_OK(dependencyA->addDependency(dependencyB));
  EXPECT_TRUE(dependencyA->hasNestedDependency(dependencyB));

  EXPECT_OK(dependencyB->addDependency(dependencyC));
  EXPECT_TRUE(dependencyB->hasNestedDependency(dependencyC));

  EXPECT_ERROR_CODE(ERR_CIRCULAR_DEPENDENCY, dependencyC->addDependency(dependencyA));
  EXPECT_FALSE(dependencyC->hasNestedDependency(dependencyA));
}

TEST(DependencyHierarchy, AllTest) {
  scoped_refptr<Dependency> dependencyA
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependency> dependencyB
    = ::base::MakeRefCounted<Dependency>();

  scoped_refptr<Dependencies> dependencies1
    = ::base::MakeRefCounted<Dependencies>();

  EXPECT_OK(dependencies1->addDependency(dependencyA));
  EXPECT_OK(dependencies1->addDependency(dependencyB));

  scoped_refptr<Dependency> dependencyC
    = ::base::MakeRefCounted<Dependency>();

  EXPECT_OK(dependencies1->addDependencies(dependencies1));

  scoped_refptr<Dependencies> dependencies2
    = ::base::MakeRefCounted<Dependencies>();

  EXPECT_OK(dependencies2->addDependency(dependencyA));
  EXPECT_OK(dependencies2->addDependency(dependencyB));
  EXPECT_OK(dependencies2->addDependency(dependencyC));

  scoped_refptr<Dependencies> dependencies3
    = ::base::MakeRefCounted<Dependencies>();

  EXPECT_OK(dependencies3->addDependency(dependencyA));
  EXPECT_OK(dependencies3->addDependency(dependencyB));
  ignore_result(dependencies2->addDependencies(dependencies1));
  ignore_result(dependencies2->addDependencies(dependencies2));
}

} // basic
