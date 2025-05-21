# Liturgical Calendar (LiturgicCalendar Project)

LiturgicCalendar is a C++ project that generates the General Roman Calendar of the Catholic Church.

## Purpose

The Liturgical Calendar, also known as the church calendar or Christian year, is an annual cycle of seasons and feasts observed in many Christian denominations. It governs the cycle of readings, prayers, and celebrations throughout the year.

This project, LiturgicCalendar, provides a C++ implementation to programmatically generate the General Roman Calendar. Such a programmatic approach is useful for:

*   Integrating liturgical information into applications (like calendar apps, daily prayer guides).
*   Displaying liturgical data on websites.
*   Academic research involving liturgical patterns.
*   Personal use for those interested in the church year.

This particular implementation is designed for use by [CathAssist](http://www.cathassist.org).

## Architecture

The LiturgicCalendar project is built around several key C++ components:

*   **`Date.h`**: Handles basic date representations and calculations. It uses Julian Day for date storage and includes support for the Chinese Lunar calendar (for the period 1901-2050).
*   **`CalendarDefine.h`**: Contains definitions for various liturgical elements, such as seasons (Advent, Christmas, Lent, Easter, Ordinary Time), liturgical ranks (Solemnity, Feast, Memorial, etc.), and liturgical colors.
*   **`LiturgicDay.h`**: Represents a single day within the Liturgical Calendar. An object of `LiturgicDay` encapsulates information about the day's season (e.g., Lent, Easter), the week of the season, its liturgical rank, color, and any specific celebrations (feasts, memorials, or solemnities) occurring on that day.
*   **`LiturgicYear.h`**: Responsible for calculating and managing the liturgical details for an entire year. It determines the dates of movable feasts (like Easter, Ash Wednesday, Pentecost) and integrates fixed celebrations (e.g., Christmas, saints' days) to build a complete liturgical year.
*   **`Calendar.h`**: Provides the primary public interface for the library. It includes static methods to initialize the calendar system (`Calendar::initCalendar()`), retrieve `LiturgicDay` objects for specific dates (`Calendar::getLiturgicDay()`), and release calendar resources (`Calendar::releaseCalendar()`).

**External Libraries:**
The project also utilizes:

*   **RapidJSON**: A fast JSON parser and generator for C++, used for serializing calendar data into JSON format (as seen in `export_month_json_test` in `main.cpp` and test files).
*   **SQLite**: A C-language library that implements a small, fast, self-contained, high-reliability, full-featured, SQL database engine, used for storing and querying liturgical data (as seen in `export_to_sqlite` in `main.cpp` and test files).

**Data Flow:**
Typically, a user interacts with the `Calendar` class. When liturgical information for a date is requested, the `Calendar` class consults the appropriate `LiturgicYear` object (creating it if necessary). The `LiturgicYear` object calculates the properties of each `LiturgicDay` based on the rules of the General Roman Calendar, including the timing of liturgical seasons and the occurrence of specific celebrations.

## How to Compile

This project uses CMake to compile. For more information, please visit: [CMake](https://cmake.org/).

To build the project:
```bash
# Use `cmake` to generate Makefile
cmake .
# Compile the project
make
```

## How to Use

Here's a basic example of how to use LiturgicCalendar to get information for a few days in January 2022:

```cpp
#include <iostream>
#include <vector>
#include "Calendar.h" // Main header for the library
#include "LiturgicDay.h" // For LiturgicDay object
#include "Date.h" // For Date object

// Using namespace for convenience
using namespace CathAssist::Calendar;

int main() {
    // 1. Initialize the Calendar system
    // This loads necessary data and prepares the calculator.
    Calendar::initCalendar();

    // 2. Define the date(s) you want to query
    // Let's check the first three days of January 2022.
    std::vector<Date> dates_to_check;
    dates_to_check.push_back(Date(2022, 1, 1));
    dates_to_check.push_back(Date(2022, 1, 2));
    dates_to_check.push_back(Date(2022, 1, 3));

    // 3. Retrieve and print LiturgicDay information
    std::cout << "Liturgical Information for January 2022:" << std::endl;
    for (const auto& date : dates_to_check) {
        LiturgicDay dayInfo = Calendar::getLiturgicDay(date);

        // Print the date
        std::cout << "Date: " << dayInfo.toString();

        // Print liturgical color
        // Note: dayInfo.getColor() returns an enum (color_t).
        // A helper function would be needed to convert this to a string (e.g., "White", "Red").
        std::cout << " | Color (Enum): " << dayInfo.getColor();

        // Print celebrations
        std::cout << " | Celebrations: ";
        auto cells = dayInfo.getCellInfos();
        if (cells.empty()) {
            std::cout << " (Ordinary Day)";
        } else {
            for (const auto& cell : cells) {
                // Note: cell.rank is an enum (rank_t).
                // A helper function would be needed to convert this to a string (e.g., "Solemnity", "Feast").
                std::cout << cell.celebration << " (Rank Enum: " << cell.rank << ") ";
            }
        }
        std::cout << std::endl;
    }

    // 4. Release the Calendar system
    // This cleans up any resources used by the calendar.
    Calendar::releaseCalendar();

    return 0;
}

```

### Expected Output

The output of the above code would look something like this (exact celebration names and ranks might vary based on the calendar data):

```
Liturgical Information for January 2022:
Date: 2022-01-01 | Color (Enum): 0 | Celebrations: Mary, Mother of God (Rank Enum: 7) 
Date: 2022-01-02 | Color (Enum): 0 | Celebrations: Epiphany of the Lord (Rank Enum: 7) 
Date: 2022-01-03 | Color (Enum): 4 | Celebrations: The Most Holy Name of Jesus (Rank Enum: 2) 
```
*(Note: The color and rank are printed as integer representations of their respective enums. You would typically implement helper functions to convert `color_t` and `rank_t` enums to human-readable strings like "White", "Red", "Green", or "Solemnity", "Feast", "Memorial" for display purposes.)*

This example demonstrates the basic workflow: initialize, get day information, and release. You can adapt this to retrieve information for any date or range of dates supported by the library.

## Project Structure

The project is organized into the following main directories and files:

*   **`include/`**: Contains all header files (`.h`) for the LiturgicCalendar library.
    *   `include/rapidjson/`: Contains header files for the RapidJSON library (third-party), used for JSON parsing and generation.
    *   `include/sqlite/`: Contains header files for the SQLite library (third-party), used for database management.
*   **`src/`**: Contains the C++ source code implementation files (`.cpp`) for the LiturgicCalendar library.
*   **`test/`**: Contains test files for the library. These tests appear to use the Google Test framework.
*   **`liturgic.db`**: An SQLite database file that stores the core liturgical data (e.g., fixed feast days, rules for movable feasts) used by the calendar generation logic.
*   **`months/`**: This directory is generated by the program (e.g., via the `export_month_json_test()` function found in `test/main.cpp`) and contains monthly calendar data in JSON format. This is typically used for testing or exporting data.
*   **`CMakeLists.txt`**: The main CMake script used for building the project. It defines how the code is compiled and linked.

## Thanks

This project gratefully acknowledges the following resources:

*   [Romcal](http://www.romcal.net/): A valuable resource for Roman Calendar information.
*   [我灵赞颂主 (Chinese Catholic Liturgical Site)](http://www.mhchina.net/): A comprehensive resource for Chinese Catholic liturgical information.

---
*This README was last updated on YYYY-MM-DD.*