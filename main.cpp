#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>

void menu();
std::string addTimes(int argc, char **argv);
std::string subtractTimes(int argc, char **argv);
int convertTimeToSeconds(int hrs, int min, int sec);
std::string simplifyTime(int seconds);
void errorMessage();
bool verifyTimeFormat(std::string inputtedTimeVal);
void print_error(std::string errorVal);
std::string singlePadding(std::string timeInput);

//-------------------------------------------------------------------------------------------------

bool verifyTimeFormat(std::string inputtedTimeVal)
{
    int hours, minutes, seconds;
    char colon1;
    char colon2;
    
    std::istringstream inputString(inputtedTimeVal);

    if (inputString >> hours >> colon1 >> minutes >> colon2 >> seconds
        && colon1 == ':' && colon2 == ':')
    {
        // Return true only if the inputted time durations are properly simplified.
        // return (hours >= 0 && hours <= 23) &&
        //         (minutes >= 0 && minutes <= 59) &&
        //         (seconds >= 0 && seconds <= 59);


        // Return true if the time values are formatted properly regardless of the values contained within the inputted time durations.
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------

void print_usage(const char* argv0)
{
    std::cerr << "\nUsage: " << argv0 << " <algorithm> <time_1> <time_2>\n"
              << "         <algorithm> must be \"--add\" or \"--subtract\"\n"
              << "         <time_1> and <time_2> must be formatted as <hr>:<min>:<sec>\n";
}

//-------------------------------------------------------------------------------------------------

void print_error(std::string errorVal)
{
    std::cerr << "\nError: " << errorVal << "\n";
}

//-------------------------------------------------------------------------------------------------

auto main(int argc, char** argv) -> int
{

    // Verify that enough arguments were passed
    if ( argc < 4 )
    {
        std::string errorVal = "Not enough arguments.";
        print_usage(argv[0]);
        print_error(errorVal);
        return 1;
    }

    std::string inputtedAlgorithm = argv[1];

    // Verify that a valid algorithm option was provided
    if ( inputtedAlgorithm != "--add" && inputtedAlgorithm != "--subtract" )
    {
        std::string errorVal = "Invalid algorithm.";
        print_usage(argv[0]);
        print_error(errorVal);
        return 1;
    }

    // Verify that all inputted time values are properly formatted
    for (int i = 2; i < argc; i++)
    {
        if (!verifyTimeFormat(argv[i]))
        {
            std::string errorVal = "Invalid time format.";
            print_usage(argv[0]);
            print_error(errorVal);
            return 1;
        }
    }

    try
    {
        // select and perform the chosen time calculation algorithm
        //  (or throw an exception if the argument is bad)
        menu();

        if ( inputtedAlgorithm == "--add" )
        {
            std::cout << addTimes(argc, argv);
        }
        else if ( inputtedAlgorithm == "--subtract" )
        {
            std::cout << subtractTimes(argc, argv);
        }


    }
    catch( const std::out_of_range& e )
    {  
        // handle exceptions thrown
        print_usage(argv[0]);
        return 1;
    }
}

//-------------------------------------------------------------------------------------------------

void errorMessage()
{
    std::cout << "Invalid input. Please try again!" << std::endl;
    menu();
}

//-------------------------------------------------------------------------------------------------

void menu()
{
    // Menu to introduce the program
    std::cout << std::endl
    //      0         1         2         3         4         5           
    //      012345678901234567890123456789012345678901234567890
        << "###################################################" << std::endl
        << "                 Time  Calculator                  " << std::endl
        << "                 By Sean Allgaier                  " << std::endl
        << "###################################################" << std::endl;
}

//-------------------------------------------------------------------------------------------------

std::string addTimes(int argc, char **argv)
{
    std::cout << "Chosen algorithm: \"add\"\n\n";
    std::string timeVals = "";
    std::string sumTime = "";
    int addedSeconds = 0;

    
    for (int i = 2; i < argc; i++)
    {
        std::string resultHour, resultMin, resultSec;
        std::string hourStr, minuteStr, secondStr;
        int hours, minutes, seconds;
        
        std::stringstream timeVal(argv[i]);
        
        std::getline(timeVal, hourStr, ':');
        std::getline(timeVal, minuteStr, ':');
        std::getline(timeVal, secondStr);
        
        hours = stod(hourStr);
        minutes = stod(minuteStr);
        seconds = stod(secondStr); 
        
        if (stod(hourStr) < 10 && stod(hourStr) > 0)
            hourStr = singlePadding(hourStr);
        else if (stod(hourStr) == 0)
            hourStr = "00";
        
        if (stod(minuteStr) < 10 && stod(minuteStr) > 0)
            minuteStr = singlePadding(minuteStr);
        else if (stod(minuteStr) == 0)
            minuteStr = "00";
        
        if (stod(secondStr) < 10 && stod(secondStr) > 0)
            secondStr = singlePadding(secondStr);
        else if (stod(secondStr) == 0)
            secondStr = "00";
        
        int timeSeconds = convertTimeToSeconds(hours, minutes, seconds);
        addedSeconds += timeSeconds;
        
        std::string inputTime = "Time " + std::to_string(i-1) + " = " + hourStr + ":" + minuteStr + ":" + secondStr + "\n";
                
        timeVals += inputTime;
    }
    std::string simplifiedTime = simplifyTime(addedSeconds);
    sumTime = "\nResult = " + simplifiedTime + "\n";
    timeVals += sumTime;
    return timeVals;
}
    
//-------------------------------------------------------------------------------------------------
std::string subtractTimes(int argc, char **argv)
{
    std::cout << "Chosen algorithm: \"subtract\"\n\n";
    std::string timeVals = "";
    std::string subtractTime = "";  
    int subtractedSeconds;
    bool firstIterationComplete = 0;

    for (int i = 2; i < argc; i++) 
    {
        std::string resultHour, resultMin, resultSec;
        std::string hourStr, minuteStr, secondStr;
        int hours, minutes, seconds;
        
        std::stringstream timeVal(argv[i]);
        
        std::getline(timeVal, hourStr, ':');
        std::getline(timeVal, minuteStr, ':');
        std::getline(timeVal, secondStr);
        
        hours = stod(hourStr);
        minutes = stod(minuteStr);
        seconds = stod(secondStr); 
        
        if (stod(hourStr) < 10 && stod(hourStr) > 0)
            hourStr = singlePadding(hourStr);
        else if (stod(hourStr) == 0)
            hourStr = "00";
        
        if (stod(minuteStr) < 10 && stod(minuteStr) > 0)
            minuteStr = singlePadding(minuteStr);
        else if (stod(minuteStr) == 0)
            minuteStr = "00";
        
        if (stod(secondStr) < 10 && stod(secondStr) > 0)
            secondStr = singlePadding(secondStr);
        else if (stod(secondStr) == 0)
            secondStr = "00";
        
        int timeSeconds = convertTimeToSeconds(hours, minutes, seconds);
        if (!firstIterationComplete)
        {
            subtractedSeconds = timeSeconds;
            firstIterationComplete = 1;
        }
        else
            subtractedSeconds -= timeSeconds;
        
        std::string inputTime = "Time " + std::to_string(i-1) + " = " + hourStr + ":" + minuteStr + ":" + secondStr + "\n";


        timeVals += inputTime;
        
    }
    std::string errorMsg;
        
    if (subtractedSeconds < 0)
        errorMsg = "\nError: Result cannot be negative\n";
    else
        errorMsg = "";
        
    std::string simplifiedTime = simplifyTime(subtractedSeconds);
    subtractTime = "\nResult = " + simplifiedTime + "\n";
    
    timeVals += subtractTime + errorMsg;
    return timeVals;
        
}
//-------------------------------------------------------------------------------------------------
    
int convertTimeToSeconds(int hrs, int min, int sec)
{
    int convertedHrs = (hrs * 60) * 60;
    int convertedMin = min * 60;
    return convertedHrs + convertedMin + sec;
}

//-------------------------------------------------------------------------------------------------

std::string simplifyTime(int seconds)
{
    // 1. Simplifies the total number of seconds to hrs:min:sec format.
    // 2. Separates the individual values of hours, minutes, and seconds.
    // 3. Concats everything into a single string with the proper formatting and string padding (if necessary).
    //          If result value is between 1 and 9 (inclusive), use the function "singlePadding" to insert a "0" at the beginning of the result value's string.

    int firstQuotient = seconds / 60;
    int resultSeconds = seconds % 60;
    int resultHours = firstQuotient / 60;
    int resultMinutes = firstQuotient % 60;

    std::string hourStr = std::to_string(resultHours), minStr = std::to_string(resultMinutes), secStr = std::to_string(resultSeconds);

    if (resultHours < 10 && resultHours > 0)
        hourStr = singlePadding(hourStr);
    else if (resultHours == 0)
        hourStr = "00";

    if (resultMinutes < 10 && resultMinutes > 0)
        minStr = singlePadding(minStr);
    else if (resultMinutes == 0)
        minStr = "00";

    if (resultSeconds < 10 && resultSeconds > 0)
        secStr = singlePadding(secStr);
    else if (resultSeconds == 0)
        secStr = "00";

    std::string simplifiedTime = hourStr + ":" + minStr + ":" + secStr;
    return simplifiedTime;
}

//-------------------------------------------------------------------------------------------------

std::string singlePadding(std::string timeInput)
{
    // Inserts a "0" to the beginning of the string "timeInput" to make the output text look uniform.
    std::string paddingValue = "0";
    return paddingValue + timeInput[timeInput.size()-1];
}

//-------------------------------------------------------------------------------------------------
