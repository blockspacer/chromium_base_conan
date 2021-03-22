# About

## NOTE

It is an error to add a dependency to a `Dependency` that is not disabled.

When a `Dependency` is disabled, it will first recursively disable any other
`Dependency` that depend on it.

All `Dependency` MUST be disabled before they are deleted.
