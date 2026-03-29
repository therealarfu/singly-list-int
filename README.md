# 🧩 Singly Linked List in C — `intlist`

A C library for manipulating singly linked lists of integers, focused on simplicity, modularity, and functional-style operations (inspired by JavaScript and Python).

---

## 🚀 Features

### 🔹 Basic operations
- Create from array (`array_to_list`)
- Insert (`list_append`, `list_prepend`, `list_insert`)
- Remove (`list_pop`, `list_shift`, `list_remove_at`)
- Length (`list_length`)

### 🔹 Access and search
- Access by index (`list_at`)
- Find index (`list_index_of`)
- Find by condition (`list_find`)
- Count occurrences (`list_count`)

### 🔹 Statistics
- Minimum (`list_min`)
- Maximum (`list_max`)
- Average (`list_average`)

### 🔹 Functional operations
- `map` → transform elements (`list_map`)
- `filter` → filter elements (`list_filter`)
- `reduce` → accumulate values (`list_reduce`)
- `for_each` → iterate with function (`list_for_each`)

### 🔹 Utilities
- Sort (`list_sort`)
- Reverse (`list_reverse`)
- Swap elements (`list_swap`)
- Concatenate lists (`list_concat`)
- Convert to string (`list_join`)

---

## 📁 Project Structure

```
├── include/
│ └── intlist.h
├── src/
│ └── intlist.c
├── lib/
│ └── libintlist.a
└── main.c
```

---
## ⚙️ Build Instructions

### 1️⃣ Compile source file
```bash
gcc -c src/intlist.c -Iinclude -o src/intlist.o
```

### 2️⃣ Create static library
```bash
ar rcs lib/libintlist.a src/intlist.o
```

### 3️⃣ Compile main program
```bash
gcc main.c -Iinclude -Llib -lintlist -o program
```

### 4️⃣ Run
```bash
./program
```

## 💡 Example Usage
```c
#include <stdio.h>
#include "intlist.h"

int main()
{
    int arr[] = {1, 2, 3, 4};

    node *list = array_to_list(arr, 4);

    printf("Length: %zu\n", list_length(list));

    unload_list(list);
    return 0;
}
```

## 🧠 Concepts Covered

### This project demonstrates:

- Data structures (``linked lists``)
- Dynamic memory management (``malloc`` / ``free``)
- Modular C design (``.h`` + ``.c``)
- Separate compilation (``.o``)
- Static libraries (``.a``)
- Function pointers (``callbacks`` / ``higher-order functions``)

## ⚠️ Memory Management
### Every list must be freed with:
```c
unload_list(list);
```
### Strings returned by ``list_join`` must be freed:
```c
free(string);
```

## 📌 Notes
- The library operates on integers (int) only
- Functions handle null pointers safely when applicable
- Allocation failures return NULL or false
