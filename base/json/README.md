 # About

Some usage examples.

```cpp
std::unique_ptr<base::DictionaryValue> ParseJSONDict(const std::string& data) {
  std::unique_ptr<base::DictionaryValue> response_dict;
  base::Optional<base::Value> message_value = base::JSONReader::Read(data);
  if (message_value && message_value->is_dict()) {
    response_dict = std::make_unique<base::DictionaryValue>();
    response_dict->MergeDictionary(base::OptionalOrNullptr(message_value));
  }
  return response_dict;
}
```

```cpp
basis::StatusOr<base::Value> parseJSONData(
  const std::string& json_data)
{
  // This could be really slow.
  base::ScopedBlockingCall scoped_blocking_call(
    FROM_HERE, base::BlockingType::MAY_BLOCK);

  base::JSONReader::ValueWithError value_with_error =
    base::JSONReader::ReadAndReturnValueWithError(
      json_data
      , base::JSON_PARSE_RFC);

  if (!value_with_error.value) {
    RETURN_ERROR().with_dvlog(99)
      << "Failed to parse JSON: "
      << "JSON error "
      << base::StringPrintf(
           "%s (%d:%d)"
           , value_with_error.error_message.c_str()
           , value_with_error.error_line
           ,  value_with_error.error_column)
      << " JSON data starts with: "
      << json_data.substr(0, kMaxDebugLogItemSize)
      << " ...";
  }

  base::Value& root
    = value_with_error.value.value();

  if (!root.is_dict()) {
    RETURN_ERROR().with_dvlog(99)
      << "Failed to parse JSON:"
      << " Root item must be a dictionary."
      << " But it is: "
      << base::Value::GetTypeName(root.type())
      << " and it has type index: "
      << static_cast<size_t>(root.type())
      << " JSON data starts with: "
      << json_data.substr(0, kMaxDebugLogItemSize)
      << " ...";
  }

  return std::move(value_with_error.value.value());
}
```
