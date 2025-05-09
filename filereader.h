#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

class FileReader {
private:
    std::ifstream file;
    std::string fileName;
public:
    /**
     * @brief loadFile
     * Loads a file
     *
     * Loads a .dat or .txt file to read.
     *
     * @param argFileName Name of the file and/or path for the file
     * @return bool Returns true if the file has been successfully found and open
     */
    bool loadFile(std::string argFileName);

    /**
     * @brief unloadFile
     * Unloads the file previously open
     *
     * Deletes the file and its content from memory
     */
    void unloadFile(void);
    /**
     * @brief readRealVariable
     * Finds the value of a variable
     *
     * Looks for a double precision float variable with a given name in the opened file
     * @param argVariableName Name of the variable that is being looked for in the file
     * @return double Value of the variable found in the search
     */
    double readRealVariable(std::string argVariableName);
    /**
     * @brief readIntegerVariable
     * Finds the value of a variable
     *
     * Looks for an integer variable with a given name in the opened file.
     * @param argVariableName Name of the variable that is being looked for in the file
     * @return integer Value of the variable found in the search
     */
    int readIntegerVariable(std::string argVariableName);
    /**
     * @brief readStringVariable
     * Finds the value of a variable
     *
     * Looks for a string variable with a given name in the opened file.
     * @param argVariableName Name of the variable that is being looked for in the file
     * @return std::string Value of the variable found in the search
     */
    std::string readStringVariable(std::string argVariableName);
    /**
     * @brief readRealMatrix
     * Finds the values of an array
     *
     * Looks for an array of arrays of double precision floating point values with a given name in the opened file.
     * @param argMatrixName Name of the array that is being looked for in the file
     * @return std::vector<std::vector<double>> Vector of Vectors of "double" values
     */
    std::vector<std::vector<double>> readRealMatrix(std::string argMatrixName);
    /**
     * @brief readIntegerMatrix
     * Finds the values of an array
     *
     * Looks for an array of arrays of integer values with a given name in the opened file.
     * @param argMatrixName Name of the array that is being looked for in the file
     * @return std::vector<std::vector<int>> Vector of Vectors of integer values
     */
    std::vector<std::vector<int>> readIntegerMatrix(std::string argMatrixName);

    void writetoCSV(std::map<const std::string, std::vector<double>>& mapa);
};

#endif // FILEREADER_H
