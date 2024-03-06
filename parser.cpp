#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

// Function to split a string into vector of strings based on delimiter
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void printKeyValue(const std::map<std::string, std::vector<std::string> > &keyValues) {
    typedef std::map<std::string, std::vector<std::string> >::const_iterator MapIterator;
    for (MapIterator it1 = keyValues.begin(); it1 != keyValues.end(); ++it1) {
        std::cout << "Key: " << it1->first
        << "\nValue(s): " << std::endl;
        const std::vector<std::string>& values = it1->second;
        for (std::vector<std::string>::const_iterator it2 = values.begin(); it2 != values.end(); ++it2) {
            std::cout << "  " << *it2 << std::endl;
        }
        std::cout << "\n";
    }
}

std::string getValue(const std::map<std::string, std::vector<std::string> > &keyValues, const std::string &key) {
    typedef std::map<std::string, std::vector<std::string> >::const_iterator MapIterator;
    MapIterator it = keyValues.find(key);
    if (it != keyValues.end()) {
        const std::vector<std::string>& values = it->second;
        if (!values.empty()) {
            return values.front(); // Return the first value
        }
    }
    return ""; // Return empty string if key not found or no values
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    std::string configFile = argv[1];
    std::ifstream file(configFile.c_str());
    if (!file) {
        std::cerr << "Error opening file: " << configFile << std::endl;
        return 1;
    }

    std::string line;
    std::string configData;
    std::string lastLine;
    while (std::getline(file, line)) {
        std::size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // Trim leading whitespace
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // Trim trailing whitespace

        // If the line ends with a space, concatenate with the next line
        if (!line.empty() && line[line.size() - 1] == ' ') {
            lastLine += line.substr(0, line.size() - 1) + " ";
        } else {
            if (!lastLine.empty()) {
                lastLine += line;
                configData += lastLine + "\n";
                lastLine.clear();
            } else {
                configData += line + "\n";
            }
        }
    }
    // Append the last line if it's not empty
    if (!lastLine.empty()) {
        configData += lastLine;
    }

    std::vector<std::string> lines = split(configData, '\n');
    std::map<std::string, std::vector<std::string> > keyValues;

    std::string currentSection = "";
    for (std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
        std::string trimmedLine = *it;
        trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t\n\r\f\v"));
        trimmedLine.erase(trimmedLine.find_last_not_of(" \t\n\r\f\v") + 1);

        if (trimmedLine.empty()) {
            continue;  // Skip empty lines
        }

        // Check for start of a new section
        if (trimmedLine[trimmedLine.size() - 1] == '{') {
            currentSection = trimmedLine.substr(0, trimmedLine.size() - 1);
        }
        // Check for end of a section
        else if (trimmedLine == "}") {
            size_t lastDot = currentSection.find_last_of('.');
            if (lastDot != std::string::npos) {
                currentSection = currentSection.substr(0, lastDot);
            } else {
                currentSection = "";
            }
        }
        // Regular key-value pair
        else {
            std::vector<std::string> tokens = split(trimmedLine, ' ');
            if (tokens.size() >= 2) {
                std::string key = tokens[0];
                std::string value = tokens[1];
                // Combine all remaining tokens as the value
                for (size_t i = 2; i < tokens.size(); ++i) {
                    value += " " + tokens[i];
                }
                if (!currentSection.empty()) {
                    keyValues[currentSection + "." + key].push_back(value);
                } else {
                    keyValues[key].push_back(value); // For keys not inside a section
                }
            }
        }
    }

    // Print the result
    printKeyValue(keyValues);

    // Get value by key example
    std::string value = getValue(keyValues, "worker_processes");
    std::cout << "Value for 'worker_processes': " << value << std::endl;

    return 0;
}
