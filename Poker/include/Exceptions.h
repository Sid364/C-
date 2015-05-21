#ifndef _H_EXCEPTIONS_
#define _H_EXCEPTIONS_

#include <exception>

class InvalidAccess : public std::exception {
public:
	InvalidAccess() {}
    const char * what() const throw() { return "Invalid action";}

};

#endif //_H_EXCEPTIONS_