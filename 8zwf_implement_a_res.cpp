// 8zwf_implement_a_res.cpp

// INCLUDES
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

// MOBILE APP PARSER CLASS
class MobileAppParser {
private:
    std::string appName;
    std::string appVersion;
    std::string appPackage;
    std::vector<std::string> permissions;

public:
    MobileAppParser(std::string filePath) {
        parseAppFile(filePath);
    }

    void parseAppFile(std::string filePath) {
        std::ifstream fileStream(filePath);
        std::string line;

        if (fileStream.is_open()) {
            while (std::getline(fileStream, line)) {
                if (line.find("application-label:") != std::string::npos) {
                    appName = extractValue(line, "application-label:");
                } else if (line.find("version:") != std::string::npos) {
                    appVersion = extractValue(line, "version:");
                } else if (line.find("package:") != std::string::npos) {
                    appPackage = extractValue(line, "package:");
                } else if (line.find("uses-permission:") != std::string::npos) {
                    permissions.push_back(extractValue(line, "uses-permission:"));
                }
            }
            fileStream.close();
        }
    }

    std::string extractValue(std::string line, std::string prefix) {
        size_t start = line.find(prefix) + prefix.length();
        size_t end = line.find(" ", start);
        return line.substr(start, end - start);
    }

    void displayAppInfo() {
        std::cout << "App Name: " << appName << std::endl;
        std::cout << "App Version: " << appVersion << std::endl;
        std::cout << "App Package: " << appPackage << std::endl;
        std::cout << "Permissions: " << std::endl;
        for (const auto& permission : permissions) {
            std::cout << "  - " << permission << std::endl;
        }
    }
};

int main() {
    MobileAppParser parser("app.txt");
    parser.displayAppInfo();
    return 0;
}