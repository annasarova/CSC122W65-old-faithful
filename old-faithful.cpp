#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string filePath;

    // Ask the user for the CSV file location
    std::cout << "Enter the path to the file: ";
    std::cin >> filePath;

    std::ifstream inputFile;

    inputFile.open(filePath);

    // Check if the file opened successfully
    if (!inputFile)
    {
        std::cout << "Error opening file." << std::endl;
    }
    else
    {
        std::ofstream outputFile;

        double eruption;
        double waiting;
        double eruptionTotal = 0;
        double waitingTotal = 0;
        int count = 0;
        char comma; // Variable used to read the comma between CSV values

        std::string header;
        std::getline(inputFile, header);

        outputFile.open("faithful_updated.csv");

        // Write header for the new CSV file
        outputFile << header << ",Short Wait Time\n";

        // Read data from the CSV file. Format: eruption,waiting
        while (inputFile >> eruption >> comma >> waiting)
        {
            eruptionTotal += eruption;
            waitingTotal += waiting;

            count++;

            // Variable for the new column
            char shortWait;

            // Determine if wait time is short
            if (waiting <= 60)
            {
                shortWait = 'T';
            }
            else
            {
                shortWait = 'F';
            }

            // Write row to new CSV file
            outputFile << eruption << "," << waiting << "," << shortWait << std::endl;
        }

        inputFile.close();
        outputFile.close();

        // Calculate averages
        double avgEruption = eruptionTotal / count;
        double avgWaiting = waitingTotal / count;

        // Print results to console
        std::cout << "The average eruption length is " << avgEruption << " minutes." << std::endl;
        std::cout << "The average eruption wait time is " << avgWaiting << " minutes." << std::endl;

        std::cout << std::endl;
        std::cout << "Writing a new CSV file called faithful_updated.csv." << std::endl;
    }

    return 0;
}