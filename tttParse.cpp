#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

int main() {

	bool test = true;
    ifstream inFile("ttt.data");

	string outExt = (test ? "test" : "train");
    ofstream outFile("ttt." + outExt);

    string line;
    int index = 0;
    while (getline(inFile, line)) {
        if (index % 2 == (test ? 1 : 0)) {
            vector<string> tokens = split(line, ',');
            // Get inputs
            for (int i = 0; i < 9; ++i) {
                if (tokens[i] == "b") {
                    outFile << "0.000" << " ";
                } else if (tokens[i] == "x") {
                    outFile << "0.500" << " ";
                } else if (tokens[i] == "o") {
                    outFile << "1.000" << " ";
                }
            }
            if (tokens[9] == "negative") {
                outFile << "0" << endl;
            } else if (tokens[9] == "positive") {
                outFile << "1" << endl;
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
