#ifndef MATAM_EXERCISE_4_EXCEPTION_H
#define MATAM_EXERCISE_4_EXCEPTION_H
#include <exception>
#include <string>

using std::string;

class Invalid_File : public std::exception {
    std::string massage;
public:
    Invalid_File(string massage):massage(massage){};
    const char* what() const noexcept override {
        return massage.c_str();
    }
};
#endif //MATAM_EXERCISE_4_EXCEPTION_H
