# Library Management System

**Course:** Data Structures and Algorithms (DSA)
**Language:** C++
**Type:** Console-Based Mini Application

---

## Table of Contents

1. [Introduction](#introduction)
2. [Objectives of the Project](#objectives)
3. [Methodology / System Design](#methodology)
4. [Implementation / Source Code](#implementation)
5. [Conclusion](#conclusion)

---

<a name="introduction"></a>
## 1. Introduction

### Overview

The Library Management System is a **console-based C++ application** that simulates the core operations of a library — adding books, issuing and returning them, searching the catalog, and managing a waiting list for unavailable titles. Built entirely within `main()` using fundamental C++ constructs, it demonstrates how real-world application logic can be structured using arrays, loops, switch-case control flow, and careful input handling — without requiring object-oriented features or external libraries.

This project is part of a structured DSA practice series. Unlike the single-algorithm programs that precede it, this is a **complete interactive system** with persistent state, multiple data entities, and a user-driven menu loop — making it the most architecturally rich program in the series.

### Problem Context

Libraries deal with a fixed catalog of books, each of which can be in one of two states — available or issued. When a book is unavailable, interested readers need a way to register their intent to borrow it. Managing these operations interactively, with formatted display and graceful error handling, requires more than a single data structure or algorithm — it requires coordinated state management across multiple data arrays and a well-designed control flow.

### Sample Library Catalog

The system is pre-loaded with 10 books:

| ID | Title | Author |
|----|-------|--------|
| 1  | No Shadow Without Light | Luke Gracias |
| 2  | One Arranged Murder | Chetan Bhagat |
| 3  | Twisted Love | Ana Huang |
| 4  | Twisted Games | Ana Huang |
| 5  | Twisted Hate | Ana Huang |
| 6  | Twisted Lies | Ana Huang |
| 7  | It Ends With Us | Colleen Hoover |
| 8  | It Starts With Us | Colleen Hoover |
| 9  | The Spanish Love Deception | Elena Armas |
| 10 | Too Good To Be True | Prajakta Kohli |

---

<a name="objectives"></a>
## 2. Objectives of the Project

### Primary Objectives

**O1 — Book Catalog Management**
Maintain a dynamic catalog of up to 50 books, each identified by a unique sequential ID, a title, an author, and an availability status. Allow new books to be added at runtime.

**O2 — Issue and Return Operations**
Enable books to be issued to borrowers and returned. Prevent issuing an already-issued book and prevent returning a book that was never issued.

**O3 — Search Functionality**
Allow a user to look up any book by its ID and view its complete details — title, author, and current availability status — in a formatted single-record display.

**O4 — Catalog Display**
Provide a tabular, formatted view of the entire catalog with all titles, authors, and statuses visible simultaneously, along with a total book count.

**O5 — Waiting List**
When a book is unavailable, allow users to register their name on a waiting list for that book. On return, notify the desk that a waiting user exists. Support up to 100 waiting entries.

**O6 — Robust Input Handling**
Handle invalid menu input (non-numeric characters, out-of-range IDs) gracefully — clearing the input buffer and prompting again without crashing.

### Secondary Objectives

- Demonstrate **parallel array design** as an alternative to struct-based records
- Demonstrate **`do-while` menu loop** for persistent interactive applications
- Apply **`setw()`-based column formatting** for aligned tabular output
- Apply **`cin.fail()` detection** for defensive input reading
- Show **1-indexed user-facing IDs** mapped to **0-indexed array storage**

---

<a name="methodology"></a>
## 3. Methodology / System Design

### 3.1 Data Representation — Parallel Arrays

The system stores book data across three parallel arrays rather than a single array of structs:

```cpp
string title[50];    // book titles
string author[50];   // book authors
int    issued[50];   // 0 = available, 1 = issued
```

Each index `i` (0 to 49) represents one book. The three arrays are kept in sync — `title[i]`, `author[i]`, and `issued[i]` all describe the same book.

**Why parallel arrays instead of a struct?**

```cpp
// Struct-based alternative (not used):
struct Book {
    string title;
    string author;
    int issued;
};
Book library[50];
```

The parallel array design uses only fundamental C++ — no `struct`, no class, no `vector`. This is a deliberate scope constraint that keeps the implementation accessible while still managing multi-field records. The trade-off is that the programmer must manually keep the three arrays synchronized — adding to one requires adding to all three.

### 3.2 Waiting List — Manual Queue

The waiting list is a second set of parallel arrays:

```cpp
string waitName[100];    // name of person waiting
int    waitBookID[100];  // 1-indexed book ID they are waiting for
int    waitCount = 0;    // current number of waiting entries
```

New entries are appended at `waitCount` and `waitCount` is incremented — a manual append-only queue. The list is never dequeued in this implementation — it only grows and is scanned on return. This is a known scope limitation discussed in the Conclusion.

### 3.3 Control Flow — `do-while` Menu Loop

```cpp
do {
    // display menu
    cin >> choice;
    // handle input errors
    switch(choice) { ... }
} while(choice != 0);
```

The `do-while` guarantees the menu is displayed **at least once** before the exit condition is checked — the correct structure for any interactive menu. A `while` loop would require checking the condition before the first display, making the code less natural.

### 3.4 Index Convention — 1-Indexed Display, 0-Indexed Storage

User-facing IDs are displayed starting from `1` for readability. Internally, arrays are 0-indexed. The conversion is applied on every ID input:

```cpp
cin >> id;
id = id - 1;   // convert to 0-based index before array access
```

And reversed on display:

```cpp
cout << i + 1;   // display 1-based ID
```

This pattern is applied consistently across all four ID-consuming operations (Issue, Return, Search, and Display).

### 3.5 Input Handling — `cin.fail()` Guard

```cpp
if(cin.fail()) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input! Enter a number.\n";
    continue;
}
cin.ignore(1000, '\n');
```

Two layers of input safety:

- **`cin.fail()` detection** — triggered when a non-numeric character is entered for `choice`. `cin.clear()` resets the error flag; `cin.ignore(1000, '\n')` flushes the bad input from the buffer. The `continue` restarts the loop without entering the switch.
- **`cin.ignore(1000, '\n')` after every `cin >>` read** — flushes the newline left in the buffer before any subsequent `getline()` call. Without this, `getline()` would immediately read an empty string.

This is the **first program in this series with explicit `cin` error handling** — a meaningful step toward production-quality input management.

### 3.6 Formatted Output — `setw()` Column Alignment

```cpp
cout << left << setw(5)  << "ID"
             << setw(35) << "Title"
             << setw(20) << "Author"
             << "Status" << "\n";
cout << string(70, '-') << "\n";
```

`setw(n)` from `<iomanip>` pads each field to exactly `n` characters wide. `left` left-aligns all fields. `string(70, '-')` generates a separator line of exactly 70 dashes — matching the total column width. This produces clean, aligned tabular output regardless of title or author length (up to the column width).

### 3.7 System Flow Diagram

```
                    ┌─────────────────────────┐
                    │   Start / Load Catalog   │
                    └──────────┬──────────────┘
                               │
                    ┌──────────▼──────────────┐
                    │     Display Menu         │◄──────────────────┐
                    └──────────┬──────────────┘                   │
                               │                                   │
            ┌──────────────────┼──────────────────────┐           │
            │                  │                       │           │
     ┌──────▼─────┐    ┌───────▼──────┐    ┌──────────▼──────┐   │
     │  Add Book  │    │ Issue / Return│   │ Search / Display │   │
     │  (case 1)  │    │ (case 2 / 3) │   │  (case 4 / 5)    │   │
     └──────┬─────┘    └───────┬──────┘   └──────────┬────────┘   │
            │                  │                       │            │
            │           ┌──────▼──────┐                │           │
            │           │  Waiting    │                │           │
            │           │  List Ops   │                │           │
            │           │ (case 6)    │                │           │
            │           └──────┬──────┘                │           │
            └──────────────────┴───────────────────────┘           │
                               │                                   │
                    ┌──────────▼──────────────┐                   │
                    │    choice != 0?          ├───── Yes ─────────┘
                    └──────────┬──────────────┘
                            No │
                    ┌──────────▼──────────────┐
                    │         Exit             │
                    └─────────────────────────┘
```

---

<a name="implementation"></a>
## 4. Implementation / Source Code

### 4.1 Complete Source Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){

    string title[50];
    string author[50];
    int issued[50];

    // Waiting list
    string waitName[100];
    int waitBookID[100];
    int waitCount = 0;

    // Sample Books (0-indexed internally, 1-indexed for display)
    title[0] = "No Shadow Without Light";    author[0] = "Luke Gracias";    issued[0] = 0;
    title[1] = "One Arranged Murder";        author[1] = "Chetan Bhagat";   issued[1] = 0;
    title[2] = "Twisted Love";               author[2] = "Ana Huang";       issued[2] = 0;
    title[3] = "Twisted Games";              author[3] = "Ana Huang";       issued[3] = 0;
    title[4] = "Twisted Hate";               author[4] = "Ana Huang";       issued[4] = 0;
    title[5] = "Twisted Lies";               author[5] = "Ana Huang";       issued[5] = 0;
    title[6] = "It Ends With Us";            author[6] = "Colleen Hoover";  issued[6] = 0;
    title[7] = "It Starts With Us";          author[7] = "Colleen Hoover";  issued[7] = 0;
    title[8] = "The Spanish Love Deception"; author[8] = "Elena Armas";     issued[8] = 0;
    title[9] = "Too Good To Be True";        author[9] = "Prajakta Kohli";  issued[9] = 0;

    int totalBooks = 10;
    int choice, id;

    cout << "\n--- Welcome to Library Management System ---\n";

    do{
        cout << "\n1. Add Book";
        cout << "\n2. Issue Book";
        cout << "\n3. Return Book";
        cout << "\n4. Search Book";
        cout << "\n5. Display All Books";
        cout << "\n6. View Waiting List";
        cout << "\n0. Exit";
        cout << "\n\nEnter choice: ";
        cin >> choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter a number.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        switch(choice){
            // ... (see full source in repository)
        }

    }while(choice != 0);

    return 0;
}
```

### 4.2 Feature Walkthrough

#### Feature 1 — Add Book (Case 1)

```cpp
case 1:
    if(totalBooks >= 50){
        cout << "Library is full!\n";
        break;
    }
    cout << "\nEnter Title  : ";
    getline(cin, title[totalBooks]);
    cout << "Enter Author : ";
    getline(cin, author[totalBooks]);
    issued[totalBooks] = 0;
    totalBooks++;
    cout << "Book added successfully!\n";
    break;
```

**Key details:**
- Capacity guard (`totalBooks >= 50`) prevents writing beyond the 50-element arrays
- `getline()` is used instead of `cin >>` to support titles and authors with spaces
- `issued[totalBooks] = 0` explicitly initializes the new book as available
- `totalBooks++` after all three parallel writes — ensures all three arrays stay synchronized

---

#### Feature 2 — Issue Book (Case 2)

```cpp
case 2:
    cin >> id;
    cin.ignore(1000, '\n');
    id = id - 1;   // convert to 0-based

    if(id < 0 || id >= totalBooks)
        cout << "Invalid ID!\n";
    else if(issued[id] == 1){
        cout << "Book is already issued!\n";
        // offer waiting list enrollment
    }
    else{
        issued[id] = 1;
        cout << "Book issued successfully!\n";
    }
```

**Key details:**
- Three distinct outcomes: invalid ID, already issued (→ waiting list offer), or successfully issued
- The waiting list enrollment is opt-in — the user is asked before being added
- `id - 1` converts the user's 1-based input to the 0-based array index

---

#### Feature 3 — Return Book (Case 3)

```cpp
case 3:
    // validate id, check if issued
    issued[id] = 0;
    cout << "Book returned successfully!\n";

    for(int i = 0; i < waitCount; i++){
        if(waitBookID[i] == id + 1){
            cout << "** Notice: " << waitName[i]
                 << " is waiting for this book! **\n";
        }
    }
```

**Key details:**
- After successful return, the waiting list is scanned for anyone waiting on this book
- **All** matching waiting entries are notified — the loop does not stop at the first match
- The notification is display-only — the book is not automatically re-issued to the first waiter
- `id + 1` converts back to 1-based for the `waitBookID` comparison

---

#### Feature 4 — Search Book (Case 4)

```cpp
cout << left << setw(5)  << "ID"
             << setw(35) << "Title"
             << setw(20) << "Author"
             << "Status" << "\n";
cout << string(70, '-') << "\n";
cout << left << setw(5)  << id+1
             << setw(35) << title[id]
             << setw(20) << author[id]
             << (issued[id] == 0 ? "Available" : "Issued") << "\n";
```

**Key details:**
- Single-record display using the same column format as the full catalog view — visual consistency
- Ternary operator for inline status display: `issued[id] == 0 ? "Available" : "Issued"`
- Header and separator printed even for a single result — matches tabular display convention

---

#### Feature 5 — Display All Books (Case 5)

```cpp
for(int i = 0; i < totalBooks; i++){
    cout << left << setw(5)  << i+1
                 << setw(35) << title[i]
                 << setw(20) << author[i]
                 << (issued[i] == 0 ? "Available" : "Issued") << "\n";
}
cout << string(70, '-') << "\n";
cout << "Total Books: " << totalBooks << "\n";
```

**Sample Output:**
```
ID   Title                              Author              Status
----------------------------------------------------------------------
1    No Shadow Without Light            Luke Gracias        Available
2    One Arranged Murder                Chetan Bhagat       Available
3    Twisted Love                       Ana Huang           Available
...
10   Too Good To Be True                Prajakta Kohli      Available
----------------------------------------------------------------------
Total Books: 10
```

---

#### Feature 6 — View Waiting List (Case 6)

```cpp
cout << left << setw(5)  << "No."
             << setw(25) << "Name"
             << setw(5)  << "Book ID"
             << "Book Title" << "\n";

for(int i = 0; i < waitCount; i++){
    cout << left << setw(5)  << i+1
                 << setw(25) << waitName[i]
                 << setw(8)  << waitBookID[i]
                 << title[waitBookID[i]-1] << "\n";
}
cout << "Total Waiting: " << waitCount << "\n";
```

**Key details:**
- `title[waitBookID[i]-1]` retrieves the book title from the 1-based stored `waitBookID` — the `-1` converts back to 0-based index
- Empty waiting list handled with a clean message before the table header is printed

---

### 4.3 Known Limitations

| Limitation | Description | Impact |
|------------|-------------|--------|
| No persistent storage | All data lost on exit — no file I/O | Data does not survive between sessions |
| Waiting list grows only | No dequeue mechanism — entries never removed | Over time, waiting list fills with stale entries |
| Auto-issue not implemented | Return notifies waiters but does not issue to them | Librarian must manually re-issue |
| Fixed capacity (50 books) | Adding beyond 50 is blocked | Catalog cannot grow beyond hardcoded limit |
| Waiting list overflow | `waitCount` can exceed 100 with no guard | Buffer overflow on `waitName[100]` — undefined behavior ⚠️ |
| No ISBN / unique identifier | Books identified only by sequential array index | Deleting or reordering books would break all IDs |
| Parallel arrays not encapsulated | Three arrays must be kept in sync manually | Adding a field requires modifying three separate arrays |
| Search by title not supported | Search requires knowing the book ID | Users cannot find a book by name |

---

### 4.4 How to Compile and Run

**Prerequisites:** GCC / G++

```bash
# Clone the repository
git clone https://github.com/rishita-ops/DSA-Library-Management.git
cd DSA-Library-Management

# Compile
g++ library.cpp -o library

# Run
./library
```

**On Windows:**
```bash
g++ library.cpp -o library.exe
library.exe
```

---

<a name="conclusion"></a>
## 5. Conclusion

### What Was Built

This project implements a functional, interactive library management system in C++ using only arrays, loops, and switch-case control flow — no object-oriented features, no external libraries, no file system access. It demonstrates that a meaningful multi-feature application can be built from DSA fundamentals alone, and that disciplined state management across parallel data structures is achievable without classes or structs.

The six features — Add, Issue, Return, Search, Display, and Waiting List — cover the operational core of a real library desk. The input handling, formatted output, and waiting list notification add production-facing polish that most algorithm-level programs in this series do not require.

### What Was Learned

**From the data design:**
The parallel array approach (`title[]`, `author[]`, `issued[]`) makes clear what a struct exists to solve — keeping related fields co-located and eliminating the risk of synchronization errors. Every `totalBooks++` in the Add case must be preceded by writes to all three arrays, and a bug that increments only two would silently corrupt the catalog. This fragility is the motivation for encapsulation in object-oriented design.

**From the control flow:**
The `do-while` loop is the natural structure for persistent menus. The `cin.fail()` guard — the first explicit input error handling in this series — is the correct way to handle non-numeric input without crashing. The `cin.ignore(1000, '\n')` pattern after every `cin >> id` is a critical habit that prevents `getline()` from reading empty strings.

**From the waiting list:**
Implementing a notify-only waiting list exposes the gap between notification and fulfillment. A complete system would maintain a FIFO queue and automatically re-issue to the first waiter on return. The current implementation is the first step — awareness — without the second step — action. This gap illustrates exactly why queue data structures exist.

**From the output formatting:**
`setw()` from `<iomanip>` is the simplest path to aligned tabular output. The consistent column schema across Search (single record) and Display (all records) demonstrates that formatting should be a shared convention, not repeated independently per feature.

### Natural Next Steps

The following extensions would move this system from a learning exercise toward a production-quality application:

| Extension | Technique Required |
|-----------|-------------------|
| Persistent data storage | File I/O (`fstream`) — save/load catalog to `.txt` or `.csv` |
| Struct-based book record | `struct Book { string title, author; int issued; }` |
| Class-based design | `class Library` with encapsulated members and methods |
| Automatic waiting list fulfillment | `queue<string>` per book — FIFO auto-issue on return |
| Search by title | Linear scan comparing `title[i]` against input string |
| Delete book operation | Shift array elements left; decrement `totalBooks` |
| Issue history / borrower name | Add `string borrower[50]` parallel array |
| Dynamic capacity | `std::vector<string>` replacing fixed arrays |

Each of these extensions maps directly to a DSA or C++ concept — making this project a natural bridge from foundational DSA into applied software development.

### Final Note

This is the capstone program of this DSA practice series. Every concept encountered in the preceding programs — linear scan, flag initialization, loop boundaries, input handling, string operations, counter variables — appears in some form inside this one. The Library Management System is not a harder algorithm; it is the same fundamental ideas organized at a larger scale, working together to solve a real problem.

---

## Repository Structure

```
DSA-Library-Management/
│
├── library.cpp         # Complete C++ source
└── README.md           # Project documentation
```

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

*Capstone project of a structured DSA practice series — fundamentals, applied.*
