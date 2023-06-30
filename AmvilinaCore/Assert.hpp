#ifndef Assert_hpp
#define Assert_hpp

class AssertException{};

#define ASSERT(a) if(!(a)) throw(AssertException())

#endif
