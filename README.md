# PostgreSQL C++ Connection Library

A lightweight C++ wrapper around the PostgreSQL `libpq` client library demonstrating common database operations such as connecting to a PostgreSQL database, inserting records, searching, retrieving data, and clearing tables.

> This project is intended as a learning reference and example implementation for using PostgreSQL with C++.

---

## Features

- Connect to a PostgreSQL database
- Insert demand clients
- Insert supply clients
- Search demand clients
- Search supply clients
- Retrieve all records
- Delete records from tables
- Parameterized SQL queries using `PQexecParams`
- Automatic database connection cleanup

---

## Project Structure

```
.
├── connettodb.h
├── connettodb.cpp
├── main.cpp
└── README.md
```

---

## Requirements

- C++17 or later
- PostgreSQL
- libpq (PostgreSQL C Client Library)
- GCC / Clang / MSVC

---

## Database Schema

This example assumes the following tables already exist.

### listofall

| Column | Type |
|---------|------|
| vesselid | TEXT |
| imo | TEXT |
| vesselname | TEXT |
| owner | TEXT |
| date | DATE |

### demandlist

| Column | Type |
|---------|------|
| vesselid | TEXT |
| workforcesize | INTEGER |

### supplylist

| Column | Type |
|---------|------|
| vesselid | TEXT |
| services | TEXT |
| workforcesize | INTEGER |

---

## Configuration

Update the PostgreSQL connection string inside the constructor.

```cpp
PQconnectdb(
    "host=localhost "
    "dbname=sealinedatabase "
    "user=cppprogram "
    "password=YOUR_PASSWORD"
);
```

---

## Example

```cpp
connettodb db;

db.insertDemandClient(
    "VES001",
    "IMO123456",
    "Sea Queen",
    "ABC Shipping",
    "2026-07-12",
    "45"
);
```

Search:

```cpp
std::string vessel = db.searchDemandClient("VES001");

std::cout << vessel << std::endl;
```

Retrieve all demand vessels:

```cpp
auto vessels = db.getalldemand();

for (const auto& row : vessels)
{
    std::cout << row << std::endl;
}
```

---

## Public API

### Constructor

```cpp
connettodb();
```

Connects to the PostgreSQL database.

---

### Insert

```cpp
insertDemandClient(...)
```

Adds a demand client.

```cpp
insertSupplyClient(...)
```

Adds a supply client.

---

### Search

```cpp
searchDemandClient(vesselid)
```

Returns demand vessel information.

```cpp
searchSupplyClient(vesselid)
```

Returns supply vessel information.

---

### Retrieve

```cpp
getalldemand()
```

Returns all demand records.

```cpp
getallsupply()
```

Returns all supply records.

```cpp
getalllistofall()
```

Returns all vessels.

---

### Delete

```cpp
cleardatabase(choice)
```

| Choice | Table |
|--------:|-------|
| 1 | demandlist |
| 2 | supplylist |
| 3 | listofall |

---

## Error Handling

The library checks:

- Database connection
- SQL execution status
- PostgreSQL errors

Errors are printed using

```cpp
PQerrorMessage()
```

---

## Notes

- Uses parameterized queries (`PQexecParams`) to reduce SQL injection risks.
- Demonstrates basic CRUD operations with PostgreSQL.
- Intended for educational purposes and small projects.
- Production applications should avoid calling `exit()` inside library functions and instead return errors or throw exceptions.

---

## Future Improvements

- Transactions
- Prepared statements
- Connection pooling
- Exception-based error handling
- RAII wrapper for `PGresult`
- Configuration file support
- Logging
- Unit tests

---

## License

MIT License

---

## Author

Shravan Bhandary
