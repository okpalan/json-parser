# json-parser

A simple JSON parser written in C.

## Usage

To use the parser, simply include the header file `json.h` and compile with `json.c`.

```sh
$ make -f makefile.win
```

```c
#include "json.h"

int main()
{
    json_object* object = json_parse("example.json");
    char* data = json_stringify(object);
    printf("%s\n", data);
    json_free(object);
    free(data);
    
    return 0;
}
```

## API

The parser has two functions: `json_parse` and `json_stringify`.

### `json_object* json_parse(const char* filename)`

Parses the JSON file `filename` and returns a `json_object` representing the root object.

### `char* json_stringify(json_object* object)`

Returns a JSON string representation of the given `json_object`.

### `void json_free(json_object* object)`

Frees the given `json_object` and all its children.

## Example

Given the following JSON file, `example.json`:

```json
{
    "key1": "value1",
    "key2": {
        "nested_key": "nested_value"
    },
    "key3": [
        1,
        2,
        3
    ]
}
```

The following program will print the following output:

```
{"key1":"value1","key2":{"nested_key":"nested_value"},"key3":[1,2,3]}
```