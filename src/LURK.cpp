
#include <lurkPks.h>
#include <LURK.h>
#include <debug.h>
namespace LURK{
//GOTO LURK
	LURK::LURK(){
		gameObj=this;
	}
	LURK::LURK(void* obj){
		gameObj=obj;
	}

	int LURK::connect(std::string ip,std::string port){//probiably finished
		debug("starting connect");
		debug(ip);
		debug(port);
		network=Network();
		debug("network created");
	    	return network.connect(ip,port);
	}
	
   
 	LURK& LURK::disconnect(){//change to only run if the network is connected
		network<<12;
		network.disconnect();
		return *this;
	}


	Pkg LURK::receive(){

		unsigned char type;
		Pkg ret;
		readLock.lock();				
		ret.receive(network);//this 1 line replaced about 100 or so
		readLock.unlock();
		
		return ret;
	}

	LURK& LURK::startReader(){
		if(!reader.joinable()){
			this->closeThread=false;
			reader =std::thread(&LURK::readPkg, this);
		}	
		return *this;
		
	}
	LURK& LURK::readAndHandle(){
		while(!closeThread){
			Pkg pkg;
			pkg.receive(network);
			pkg.handle(gameObj);
		} 
		return *this;
	}
	LURK& LURK::startHandler(){
		if(!reader.joinable()){
			this->closeThread=false;
			reader =std::thread(&LURK::readAndHandle, this);
		}	
		return *this;
	}
	LURK& LURK::stop(){
		this->closeThread=true;
		reader.join();
		return *this;
	}

	LURK& LURK::readPkg(){
		while(!(this->closeThread)){
			Pkg temp=this->receive();
			handleLock.lock();
			cPak=temp;
			pks.push(temp);
			handleLock.unlock();
		}
		return *this;
	}
	LURK& LURK::handleLoop(){
		while(!(this->closeThread)){
			Pkg temp=this->receive();//call the LURK functions instead of the Pkg functions as LURK will engage the mutex 
			handle(temp);
		}
		return *this;
	}
	LURK& LURK::handleAll(){
		handleLock.lock();	
		while (!pks.empty()){
			pks.front().handle(gameObj);
			pks.pop();
		}
		handleLock.unlock();
		return *this;
	}
	LURK& LURK::handle(Pkg &pkg){
		handleLock.lock();	
		pkg.handle(gameObj);
		handleLock.unlock();
		return *this;	
	}
	LURK& LURK::handle(pkg &pkg){
		handleLock.lock();	
		pkg.handle(gameObj);
		handleLock.unlock();
		return *this;	
	}
	LURK::~LURK(){
		if(network.connected){
			this->disconnect();
		}
	}
	LURK& LURK::send(Pkg &pkg){
		sendLock.lock();
		pkg.send(network);
		sendLock.unlock();
		return *this;
	}
	LURK& LURK::send(pkg &pkg){
		sendLock.lock();
		pkg.send(network);
		sendLock.unlock();
		return *this;
	}

}//namespace end
