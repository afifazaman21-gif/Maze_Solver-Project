#include <iostream>

using namespace std;

// ============================================================
// Custom Exception Classes
// ============================================================
class MazeException : public exception {
protected:
    string message;
public:
    MazeException(const string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileException : public MazeException {
public:
    FileException(const string& msg) : MazeException("FILE ERROR: " + msg) {}
};

class LoginException : public MazeException {
public:
    LoginException(const string& msg) : MazeException("LOGIN ERROR: " + msg) {}
};

class MazeLogicException : public MazeException {
public:
    MazeLogicException(const string& msg) : MazeException("MAZE ERROR: " + msg) {}
};

int main() {
    cout << "=============================================\n";
    cout << "       MAZE SOLVER - CS112 Project          \n";
    cout << "=============================================\n";
    return 0;
}