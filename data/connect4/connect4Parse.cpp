#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

int main() {

    ifstream inFile("connect-4.data");
    ofstream outFile("connect4.train");

    string line;
    int index = 0;
    while (getline(inFile, line)) {
        if (index % 2 == 0) {
            vector<string> tokens = split(line, ',');
            // Get inputs
            for (int i = 0; i < 42; ++i) {
                if (tokens[i] == "b") {
                    outFile << "0.000" << " ";
                } else if (tokens[i] == "x") {
                    outFile << "0.500" << " ";
                } else if (tokens[i] == "o") {
                    outFile << "1.000" << " ";
                }
            }
            if (tokens[42] == "draw") {
                outFile << "0 0" << endl;
            } else if (tokens[42] == "win") {
                outFile << "0 1" << endl;
            } else if (tokens[42] == "loss") {
                outFile << "1 0" << endl;
            }
        }

        ++index;
    }

    inFile.close();
    outFile.close();

    return 0;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
