#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

template<typename T> void stringSeparation(std::string s, T& parts);
template<>
void stringSeparation(std::string s, std::vector<std::string>& parts)
{
    char separator = ',';
    int token_begin = 0;
    for(int i = 0; i < s.size(); ++i)
    {
        if( s[i] == separator)
        {
           parts.push_back(s.substr(token_begin, i - token_begin ));
           token_begin = i + 1;
        }
    }
    parts.push_back(s.substr(token_begin, s.size() - token_begin));
}

template<>
void stringSeparation(std::string s, std::vector<double>& parts)
{
    char separator = ',';
    int token_begin = 0;
    for(int i = 0; i < s.size(); ++i)
    {
        if( s[i] == separator)
        {
          parts.push_back(std::stod(s.substr(token_begin, i - token_begin )));
          token_begin = i + 1;
        }
    }
    parts.push_back(std::stod(s.substr(token_begin, s.size() - token_begin )));
}

int main() {
    std::ifstream data("data.txt");
    if (data.is_open()){
        // std::cout << "Файл открыт" << std::endl;
    }
    std::string line;
    data >> line;
    std::vector<std::string> names;
    stringSeparation(line, names);

    int numOfColumns = names.size();

    std::vector<std::vector<double>> values;

    try {
        while (data >> line)
        {
            std::vector<double> row;
            stringSeparation(line, row);
            if (row.size() != numOfColumns)
            {
                throw 1;
            }
            values.push_back(row);
        }
    }
    catch (int err) {
        switch (err) {
            case 1:
                std::cout << "Invalid number of elements in a row" << std::endl;
                return 1;
        }

    }

    //printing
    for (int i=0; i < numOfColumns; ++i)
    {
        std::cout << names[i] << ' ';
    }
    std::cout<<std::endl;
    for (int i=0; i < values.size(); ++i)
    {
        for (int j=0; j < numOfColumns; ++j)
        {
            std::cout << std::setw(names[j].size());
            std::cout << values[i][j] << ' ';
        }
        std::cout<<std::endl;
    }
    return 0;
}