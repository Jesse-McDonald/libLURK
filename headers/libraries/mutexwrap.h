#ifndef WRAPMUTEX
#define WRAPMUTEX
#include <mutex>
class WrapMutex{
	private:
		std::mutex* mutex;//active mutex
		int* copies;//number of copies of this mutex
		void deInstance();
	public:
		WrapMutex();
		WrapMutex(const WrapMutex& other);
		WrapMutex& operator=(const WrapMutex& other);
		~WrapMutex();
		WrapMutex& lock();
		WrapMutex& unlock();
		bool try_lock();
};
#endif//WRAPMUTEX
