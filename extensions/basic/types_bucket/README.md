# About

`TypesBucket` can store arbitrary typed objects.

You can add `MyObjectType` to `TypesBucket`.

You can remove `MyObjectType` from `TypesBucket`.

But you can not can add `MyObjectType` twice into same `TypesBucket`.

`TypesBucket` inspired by `context variables` from `entt`

## Implementation

`TypesBucket` is `std::vector<variable_data>`.

`variable_data` stores void pointer to value.

```cpp
std::unique_ptr<void, void(*)(void *)> value;
```

Void pointer used to store arbitrary typed object

## Usage

```cpp
TypesBucket typesBucket;

// creates a new context variable initialized with the given values
typesBucket.set<my_type>(42, 'c');

// gets the context variable
const auto &var = typesBucket.ctx<my_type>();

// if in doubts, probe the typesBucket to avoid assertions in case of errors
if(auto *ptr = typesBucket.try_ctx<my_type>(); ptr) {
  // uses the context variable associated with the typesBucket, if any
}

// unsets the context variable
typesBucket.unset<my_type>();
```

## Thread safety

`TypesBucket` is NOT thread-safe.

Prefer to use `ThreadLocalTypesBucket` to avoid thread-safety issues.

```cpp
TypesBucket& typesBucket = ThreadLocalTypesBucket::CurrentTypesBucket();

typesBucket.set<my_type>(42, 'c');

const auto &var = typesBucket.ctx<my_type>();
```
