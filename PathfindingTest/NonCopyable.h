#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class NonCopyable
{
protected:
    NonCopyable () {}
    ~NonCopyable () {} // Protected non-virtual destructor
private:
	// Explicitly block copy/assign operations
	NonCopyable( const NonCopyable& );
	NonCopyable& operator=( const NonCopyable& );
};

#endif