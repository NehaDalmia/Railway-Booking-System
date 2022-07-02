## Directories

### `./include`
#### *contains the header files (`.h`) for implementation*
### `./src`
#### *contains the source files (`.cpp`) for implementation*
### `./test`
#### *contains the source (`.cpp`) and header (`.h`) files for test applications*

## Files

### In `./include`
1. `Date.h`

2. `Station.h`

3. `Railways.h`

4. `Booking.h`

5. `BookingClasses.h`

6. `Concessions.h`

7. `Divyaang.h`

8. `DivyaangConcession.h`

9. `Exceptions.h`

10. `Gender.h`

11. `GeneralConcessions.h`

12. `LadiesConcessions.h`

13. `Name.h`

14. `Passenger.h`

15. `SeniorCitizenConcession.h`

16. `BookingCategory.h`

### In `./src`
1. `Date.cpp`

2. `Station.cpp`

3. `Railways.cpp`

4. `Booking.cpp`

5. `BookingClasses.cpp`

6. `Berth.cpp`

7. `Seat.cpp`

8. `Concessions.cpp`

9. `Gender.cpp`

10. `Name.cpp`

11. `Passenger.cpp`

### In `./test`


1. `Application.cpp`

    For running custom made application test

2. `UnitTest.cpp`

    For running custom made unit tests for all classes 

4. `Test.h`

    Contains the declaration of the testing functions

## Compiler
- `G++ v8.1.0`
- Options during compilation:
    - `-o test` : creates the executable in the `src` directory
    - `-I ../include` : includes the path to the `include` directory which contains all the header files 

## Running Tests
-  Run commandline in the project directory and change directory to `src` using `cd src`
   OR  Run commandline in the directory - `./src`

-  Two kinds of tests can be ran:
    - UNIT TEST:
        - Compile using `make unit`
        - Run the executable using `.\test`
        - Output gets written to `./UnitTestOut.txt`
    - APPLICATION TEST:
        - Compile using `make app`
        - Run the executable using `.\test`
        - Output gets written to `./ApplicationOut.txt`
