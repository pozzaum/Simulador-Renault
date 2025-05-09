#include "filereader.h"

bool FileReader::loadFile(std::string argFileName)
{
    fileName = argFileName;
    file.open(fileName.c_str());
    return((file.is_open()));
}

void FileReader::unloadFile(void)
{
    file.close();
    fileName.clear();
}

double FileReader::readRealVariable(std::string argVariableName)
{
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string readString, variableName;
    size_t startPosition, endPosition;

    do
    {
        getline(file, readString);
        startPosition = readString.find_first_not_of(" \t");
        if (startPosition < std::string::npos)
        {
            endPosition = readString.find_first_of(" \t", startPosition);
            variableName = readString.substr(startPosition, endPosition - startPosition);
            if (variableName == argVariableName)
            {
                startPosition = readString.find_first_not_of(" \t", endPosition);
                if (startPosition < std::string::npos)
                {
                    endPosition = readString.find_first_of(" \t", startPosition);
                    return atof(readString.substr(startPosition, endPosition - startPosition).c_str());
                }

            }

        }

    } while (!file.eof());

    std::cout << "Variable " << argVariableName << " not found in file " << fileName << std::endl;

    return 0;
}

int FileReader::readIntegerVariable(std::string argVariableName)
{
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string readString, variableName;
    size_t startPosition, endPosition;

    do
    {
        getline(file, readString);
        startPosition = readString.find_first_not_of(" \t");
        if (startPosition < std::string::npos)
        {
            endPosition = readString.find_first_of(" \t", startPosition);
            variableName = readString.substr(startPosition, endPosition - startPosition);
            if (variableName == argVariableName)
            {
                startPosition = readString.find_first_not_of(" \t", endPosition);
                if (startPosition < std::string::npos)
                {
                    endPosition = readString.find_first_of(" \t", startPosition);
                    return atoi(readString.substr(startPosition, endPosition - startPosition).c_str());
                }

            }

        }

    } while (!file.eof());

    std::cout << "Variable " << argVariableName << " not found in file " << fileName << std::endl;

    return 0;
}

std::string FileReader::readStringVariable(std::string argVariableName){
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string readString, variableName;
    size_t startPosition, endPosition;

    do
    {
        getline(file, readString);
        startPosition = readString.find_first_not_of(" \t");
        if (startPosition < std::string::npos)
        {
            endPosition = readString.find_first_of(" \t", startPosition);
            variableName = readString.substr(startPosition, endPosition - startPosition);
            if (variableName == argVariableName)
            {
                startPosition = readString.find_first_not_of(" \t", endPosition);
                if (startPosition < std::string::npos)
                {
                    endPosition = readString.find_first_of(" \t", startPosition);
                    return readString.substr(startPosition, endPosition - startPosition).c_str();
                }

            }

        }

    } while (!file.eof());

    std::cout << "Variable " << argVariableName << " not found in file " << fileName << std::endl;

    return 0;
}

std::vector<std::vector<double>> FileReader::readRealMatrix(std::string argMatrixName){
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string readString, matrixName;
    size_t startPosition, endPosition;

    std::vector<double> readLine;
    std::vector<std::vector<double>> readMatrix;

    do
    {
        getline(file, readString);
        startPosition = readString.find_first_not_of(" \t");
        if (startPosition < std::string::npos)
        {
            endPosition = readString.find_first_of(" \t", startPosition);
            matrixName = readString.substr(startPosition, endPosition - startPosition);
            if (matrixName == argMatrixName)
            {
                do
                {
                    getline(file, readString);
                    startPosition = readString.find_first_not_of(" \t");
                    if (startPosition < std::string::npos)
                    {
                        endPosition = readString.find_first_of(" \t", startPosition);
                        if (readString.substr(startPosition, endPosition - startPosition) == "end")
                        {
                            return readMatrix;
                        }
                        else
                        {
                            do
                            {
                                readLine.push_back(atof(readString.substr(startPosition, endPosition - startPosition).c_str()));
                                startPosition = readString.find_first_not_of(" \t", endPosition);
                                endPosition = readString.find_first_of(" \t", startPosition);
                            } while (startPosition  < std::string::npos);
                        }
                    }
                    readMatrix.push_back(readLine);
                    readLine.clear();

                } while (!file.eof());

            }

        }

    } while (!file.eof());

    std::cout << "Matrix " << argMatrixName << " not found in file " << fileName << std::endl;

    return {};
}



std::vector<std::vector<int>> FileReader::readIntegerMatrix(std::string argMatrixName){
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string readString, matrixName;
    size_t startPosition, endPosition;

    std::vector<int> readLine;
    std::vector<std::vector<int>> readMatrix;

    do
    {
        getline(file, readString);
        startPosition = readString.find_first_not_of(" \t");
        if (startPosition < std::string::npos)
        {
            endPosition = readString.find_first_of(" \t", startPosition);
            matrixName = readString.substr(startPosition, endPosition - startPosition);
            if (matrixName == argMatrixName)
            {
                do
                {
                    getline(file, readString);
                    startPosition = readString.find_first_not_of(" \t");
                    if (startPosition < std::string::npos)
                    {
                        endPosition = readString.find_first_of(" \t", startPosition);
                        if (readString.substr(startPosition, endPosition - startPosition) == "end")
                        {
                            return readMatrix;
                        }
                        else
                        {
                            do
                            {
                                readLine.push_back(atoi(readString.substr(startPosition, endPosition - startPosition).c_str()));
                                startPosition = readString.find_first_not_of(" \t", endPosition);
                                endPosition = readString.find_first_of(" \t", startPosition);
                            } while (startPosition < std::string::npos);
                        }
                    }
                    readMatrix.push_back(readLine);
                    readLine.clear();

                } while (!file.eof());

            }

        }

    } while (!file.eof());

    std::cout << "Matrix " << argMatrixName << " not found in file " << fileName << std::endl;

    return {};
}

void FileReader::writetoCSV(std::map<const std::string, std::vector<double>>& mapa){
    std::ofstream out_file("results.csv");
    std::map<std::string, std::vector<double>>::iterator it;
    for(it = mapa.begin(); it != mapa.end(); it++){
        out_file << it->first << ",";
        for(size_t i = 0; i < it->second.size(); i++){
            out_file << it->second.at(i) << ",";
        }
        out_file << "\n";
    }
    out_file.close();
}
