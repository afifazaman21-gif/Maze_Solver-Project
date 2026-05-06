#ifndef EXCEPTIONS_H // Prevents multiple inclusion of header file
#define EXCEPTIONS_H

#include <exception>
// Provides the standard C++ exception base class (std::exception)

#include <string>
// Provides the std::string class used to store error messages

using namespace std;


// Base Exception Class: MazeException ,parent exception class for all project-related errors
// It inherits from std::exception so it can be caught as a standard exception.
class MazeException : public exception {
protected:
    string message;   // Stores the error message

public:
    // Parameterized constructor to initialize the error message
    MazeException(const string& msg) : message(msg) {}

    // what() is a virtual function from std::exception
    // It returns the error message as a C-style string
    // noexcept means this function will not throw exceptions
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Derived exception class for file-related errors
// Example: file not found, cannot open file, file read/write error
class FileException : public MazeException {
public:
    // Calls base class constructor and adds "FILE ERROR" prefix
    FileException(const string& msg) : MazeException("FILE ERROR: " + msg) {}
};

// Derived exception class for login/registration errors
// Example: incorrect password, user not found, invalid login attempt
class LoginException : public MazeException {
public:
    // Calls base class constructor and adds "LOGIN ERROR" prefix
    LoginException(const string& msg) : MazeException("LOGIN ERROR: " + msg) {}
};

// Derived exception class for maze logic errors
// Example: invalid maze size, out-of-bounds access, missing start/end

class MazeLogicException : public MazeException {
public:
    // Calls base class constructor and adds "MAZE ERROR" prefix
    MazeLogicException(const string& msg) : MazeException("MAZE ERROR: " + msg) {}
};
#endif