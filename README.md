# Time-Calculator
A basic tool written in C++ to perform basic calculations involving time durations.



## Installation
Simply use the `make` command in the repo's directory to compile the code and then run the executable with the command `./time_calculator`.

## Usage
```
./time_calculator <algorithm> <time_1> <time_2>

    <algorithm> must be either "--add" or "--subtract"
    <time_1> and <time_2> must be formatted as <hr>:<min>:<sec>
```


## Output Examples
Addition: 
```
./time_calculator --add 1:65:65 1:500:500 3:45:900

###################################################
                Time  Calculator
                By Sean Allgaier
###################################################
Chosen algorithm: "add"

Time #1 = 01:65:65 -> 02:06:05
Time #2 = 01:500:500 -> 09:28:20
Time #3 = 03:45:900 -> 04:00:00

02:06:05 + 09:28:20 + 04:00:00 = 15:34:25

Result = 15:34:25
```
Subtraction:
```
./time_calculator --subtract 10:50:10 0:45:310 5:00:00 3:45:900


###################################################
                 Time  Calculator
                 By Sean Allgaier
###################################################
Chosen algorithm: "subtract"

Time #1 = 10:50:10 -> 10:50:10
Time #2 = 00:45:310 -> 00:50:10
Time #3 = 05:00:00 -> 05:00:00
Time #4 = 03:45:900 -> 04:00:00

10:50:10 - 00:50:10 - 05:00:00 - 04:00:00 = 01:00:00

Result = 01:00:00
```




## Features (Current & Planned)
- [x] Take two different time durations as input, perform either addition or subtraction, and spit out the results.
- [x] Overflow correction 
    - Ex: 1:65:65 (1hr 65 min 65 sec) -> 2:06:05 (2hr 6min 5 sec)
- [x] Change the input parameters to accept any amount of time duration inputs (aka dynamic input parameters)
- [ ] Accept time parameters contained within an input file
