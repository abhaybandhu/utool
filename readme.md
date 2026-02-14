
# utool

utool short for utils tool is a cli including:
 - Generating GUID version 4 and 7
 - Generating ULID
 - Keep a History of what was generated which can be filtered

## How to compile

### Compile tool:
```bash
gcc main.c directive/* -o utool
```
### How to compile unit test:

```bash
gcc tests/unitTest.c tests/Unity/* tests/unitTests/*  directive/* -Iunity -o .bin/unitTest
```

## Commands

### GUID

Generate a GUID version 4:
```bash
$ utool guid v4
550e8400-e29b-41d4-a716-446655440000
```

Generate a GUID version 7:
```bash
$ utool guid v7 -n 2
018f5c2a-d8e0-7000-8000-000000000001
018f5c2a-d8e0-7000-8000-000000000002
```

### ULID

Generate a ULID:
```bash
$ utool ulid
01ARZ3NDEKTSV4RRFFQ69G5FAV
```

### History

View generation history:
```bash
$ utool history -l
GUIDv4 [Timestamp] 550e8400-e29b-41d4-a716-446655440000
GUIDv7 [Timestamp] 018f5c2a-d8e0-7000-8000-000000000001
GUIDv7 [Timestamp] 018f5c2a-d8e0-7000-8000-000000000002 
ULID   [Timestamp] 01ARZ3NDEKTSV4RRFFQ69G5FAV
```

Filter history by type:
```bash
$ utool history --filter guidv7
GUIDv7 [Timestamp] 018f5c2a-d8e0-7000-8000-000000000001
GUIDv7 [Timestamp] 018f5c2a-d8e0-7000-8000-000000000002 
```

## Planned Improvements
- Add unit tests
- Set up Github Actions
- Add copy to clipboard when generated (which can be enable or disable)
- Refactoring code

## Feedback is welcome!
If you have any suggestions, recommendations, or constructive criticism, I’d really appreciate it. Feel free to open an issue or submit a pull request.
