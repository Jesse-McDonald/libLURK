#include "mutexwrap.h"
void WrapMutex::deInstance(){
	(*copies)--;
	if ((*copies)<1){ 
		delete copies;
		delete mutex;//only if we are out of copies do we delete mutex			
	}
}

WrapMutex::WrapMutex(){
	mutex=new std::mutex();
	copies=new int(1);

}
WrapMutex::WrapMutex(const WrapMutex& other){
	copies=other.copies;
	mutex=other.mutex;
	(*copies)++;

	//deInstance();
	

}
WrapMutex& WrapMutex::operator=(const WrapMutex& other){
	deInstance();
	copies=other.copies;
	mutex=other.mutex;
	(*copies)++;
	
	//deInstance();
	
	
}
WrapMutex::~WrapMutex(){
	deInstance();
}
WrapMutex& WrapMutex::lock(){
	mutex->lock();
	return *this;
}
WrapMutex& WrapMutex::unlock(){
	mutex->unlock();
	return *this;
}
bool WrapMutex::try_lock(){
	return mutex->try_lock();
}
