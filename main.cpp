#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>

void menu();
std::string addTimes(std::string time1, std::string time2);
std::string subtractTimes(std::string time1, std::string time2);
double convertTimeToSeconds(double hrs, double min, double sec);
std::string simplifyTime(double seconds);
void errorMessage();
bool verifyTimeFormat(std::string inputtedTimeVal);
void print_error(std::string errorVal);

//-------------------------------------------------------------------------------------------------

bool verifyTimeFormat(std::string inputtedTimeVal)
{
    double hours, minutes, seconds;
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

    // Verify that the proper number of arguments were passed
    if ( argc < 4 )
    {
        std::string errorVal = "Not enough arguments.";
        print_usage(argv[0]);
        print_error(errorVal);
        return 1;
    }

    else if ( argc > 4 )
    {
        std::string errorVal = "Too many arguments.";
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

    // Verify that the inputted time values are valid
    if ( !verifyTimeFormat(argv[2]) || !verifyTimeFormat(argv[3]) )
    {
        std::string errorVal = "Invalid time format.";
        print_usage(argv[0]);
        print_error(errorVal);
        return 1;
    }

    try
    {
        // select and perform the chosen time calculation algorithm
        //  (or throw an exception if the argument is bad)
        menu();

        if ( inputtedAlgorithm == "--add" )
        {
            std::cout << addTimes(argv[2], argv[3]);
        }
        else if ( inputtedAlgorithm == "--subtract" )
        {
            std::cout << subtractTimes(argv[2], argv[3]);
        }


    }
    catch( const std::out_of_range& e )
    {  // handle exceptions thrown
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

std::string addTimes(std::string time1, std::string time2)
{
    std::cout << "Chosen algorithm: \"add\"\n";
    std::string addTimesResultVal;
    std::string resultHour, resultMin, resultSec;

    std::string hours1str, minutes1str, seconds1str;
    std::string hours2str, minutes2str, seconds2str;

    double hours1, minutes1, seconds1;
    double hours2, minutes2, seconds2;
    
    std::stringstream time1Val(time1);
    std::stringstream time2Val(time2);

    std::getline(time1Val, hours1str, ':');
    std::getline(time1Val, minutes1str, ':');
    std::getline(time1Val, seconds1str);

    std::getline(time2Val, hours2str, ':');
    std::getline(time2Val, minutes2str, ':');
    std::getline(time2Val, seconds2str);

    hours1 = stod(hours1str);
    minutes1 = stod(minutes1str);
    seconds1 = stod(seconds1str);

    hours2 = stod(hours2str);
    minutes2 = stod(minutes2str);
    seconds2 = stod(seconds2str);


    if (stod(hours1str) < 10 && stod(hours1str) > 0)
    {
        hours1str = "0" + hours1str;
    }
    else if (stod(hours1str) == 0)
        hours1str = "00";

    if (stod(minutes1str) < 10 && stod(minutes1str) > 0)
    {
        minutes1str = "0" + minutes1str;
    }
    else if (stod(minutes1str) == 0)
        minutes1str = "00";

    if (stod(seconds1str) < 10 && stod(seconds1str) > 0)
    {
        seconds1str = "0" + seconds1str;
    }
    else if (stod(seconds1str) == 0)
        seconds1str = "00";

    if (stod(hours2str) < 10 && stod(hours2str) > 0)
    {
        hours2str = "0" + hours2str;
    }
    else if (stod(hours2str) == 0)
        hours2str = "00";

    if (stod(minutes2str) < 10 && stod(minutes2str) > 0)
    {
        minutes2str = "0" + minutes2str;
    }
    else if (stod(minutes2str) == 0)
        minutes2str = "00";

    if (stod(seconds2str) < 10 && stod(seconds2str) > 0)
    {
        seconds2str = "0" + seconds2str;
    }
    else if (stod(seconds2str) == 0)
        seconds2str = "00";


    double time1seconds = convertTimeToSeconds(hours1, minutes1, seconds1);
    double time2seconds = convertTimeToSeconds(hours2, minutes2, seconds2);
    double addedSeconds = time1seconds + time2seconds;


    // Debugging message
    // std::cout << "Converted seconds = " << time1seconds << " + " << time2seconds << " = " << addedSeconds << "\n";

    std::string simplifiedTime = simplifyTime(addedSeconds);

    // Debugging message
    // std::cout << "Simplified time = " << simplifiedTime << "\n";


    std::string inputTime1 = "\nTime1 = " + hours1str + ":" + minutes1str + ":" + seconds1str + "\n";
    std::string inputTime2 = "Time2 = " + hours2str + ":" + minutes2str + ":" + seconds2str + "\n";
    std::string sumTime = "\nResult = " + simplifiedTime + "\n";

    std::string timeVals = inputTime1 + inputTime2 + sumTime;
    return timeVals;
}

//-------------------------------------------------------------------------------------------------

std::string subtractTimes(std::string time1, std::string time2)
{
    std::cout << "Chosen algorithm: \"subtract\"\n";
    std::string subtractTimesResultVal;
    std::string resultHour, resultMin, resultSec;

    std::string hours1str, minutes1str, seconds1str;
    std::string hours2str, minutes2str, seconds2str;

    double hours1, minutes1, seconds1;
    double hours2, minutes2, seconds2;
    
    std::stringstream time1Val(time1);
    std::stringstream time2Val(time2);

    std::getline(time1Val, hours1str, ':');
    std::getline(time1Val, minutes1str, ':');
    std::getline(time1Val, seconds1str);

    std::getline(time2Val, hours2str, ':');
    std::getline(time2Val, minutes2str, ':');
    std::getline(time2Val, seconds2str);

    hours1 = stod(hours1str);
    minutes1 = stod(minutes1str);
    seconds1 = stod(seconds1str);

    hours2 = stod(hours2str);
    minutes2 = stod(minutes2str);
    seconds2 = stod(seconds2str);

    if (stod(hours1str) < 10 && stod(hours1str) > 0)
    {
        hours1str = "0" + hours1str;
    }
    else if (stod(hours1str) == 0)
        hours1str = "00";

    if (stod(minutes1str) < 10 && stod(minutes1str) > 0)
    {
        minutes1str = "0" + minutes1str;
    }
    else if (stod(minutes1str) == 0)
        minutes1str = "00";

    if (stod(seconds1str) < 10 && stod(seconds1str) > 0)
    {
        seconds1str = "0" + seconds1str;
    }
    else if (stod(seconds1str) == 0)
        seconds1str = "00";

    if (stod(hours2str) < 10 && stod(hours2str) > 0)
    {
        hours2str = "0" + hours2str;
    }
    else if (stod(hours2str) == 0)
        hours2str = "00";

    if (stod(minutes2str) < 10 && stod(minutes2str) > 0)
    {
        minutes2str = "0" + minutes2str;
    }
    else if (stod(minutes2str) == 0)
        minutes2str = "00";

    if (stod(seconds2str) < 10 && stod(seconds2str) > 0)
    {
        seconds2str = "0" + seconds2str;
    }
    else if (stod(seconds2str) == 0)
        seconds2str = "00";


    double time1seconds = convertTimeToSeconds(hours1, minutes1, seconds1);
    double time2seconds = convertTimeToSeconds(hours2, minutes2, seconds2);
    double subtractedSeconds = time1seconds - time2seconds;

    // Debugging message
    // std::cout << "Converted seconds = " << time1seconds << " - " << time2seconds << " = " << subtractedSeconds << "\n";
    std::string inputTime1 = "\nTime1 = " + hours1str + ":" + minutes1str + ":" + seconds1str + "\n";
    std::string inputTime2 = "Time2 = " + hours2str + ":" + minutes2str + ":" + seconds2str + "\n";

    std::string sumTime;

    if (subtractedSeconds < 0)
    {
        sumTime = "\nError: Result cannot be negative\n";
    }
    else
    {
        std::string simplifiedTime = simplifyTime(subtractedSeconds);

        // Debugging message
        // std::cout << "Simplified time = " << simplifiedTime << "\n";
        sumTime = "\nResult = " + simplifiedTime + "\n";
    }

    std::string timeVals = inputTime1 + inputTime2 + sumTime;
    return timeVals;

}

//-------------------------------------------------------------------------------------------------

double convertTimeToSeconds(double hrs, double min, double sec)
{
    double convertedHrs = (hrs * 60) * 60;
    double convertedMin = min * 60;
    return convertedHrs + convertedMin + sec;
}

//-------------------------------------------------------------------------------------------------

std::string simplifyTime(double seconds)
{
    int firstQuotient = seconds / 60;
    int resultSeconds = (int)seconds % 60;
    int resultHours = firstQuotient / 60;
    int resultMinutes = firstQuotient % 60;

    std::string hourStr = std::to_string(resultHours), minStr = std::to_string(resultMinutes), secStr = std::to_string(resultSeconds);

    if (resultHours < 10 && resultHours >= 0)
    {
        // Add single leading 0 to the string "resultHours" 
        hourStr = "0" + std::to_string(resultHours);
    }
    else if (resultHours == 0)
    {
        hourStr = "00" + std::to_string(resultHours);
    }

    if (resultMinutes < 10 && resultMinutes >=0)
    {
        minStr = "0" + std::to_string(resultMinutes);
    }
    else if (resultMinutes == 0)
    {
        hourStr = "00" + std::to_string(resultHours);
    }

    if (resultSeconds < 10 && resultSeconds >= 0)
    {
        secStr = "0" + std::to_string(resultSeconds);
    }
    else if (resultSeconds == 0)
    {
        hourStr = "00" + std::to_string(resultHours);
    }

    std::string simplifiedTime = hourStr + ":" + minStr + ":" + secStr;
    return simplifiedTime;
}

//-------------------------------------------------------------------------------------------------
