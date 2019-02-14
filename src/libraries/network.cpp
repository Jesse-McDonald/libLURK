#include <network.h>
#include <netdb.h>
#include <stdexcept>
#include <cstring>
#include <debug.h>
Network::Network(){
	debug("why u no work here?");
}
Network::Network(std::string ip, std::string port): Network(){
	sad.sin_port=htons(stoi(port));
	sad.sin_family=AF_INET;

	skt=socket(AF_INET,SOCK_STREAM,0);

	entry = gethostbyname(ip.c_str());
	if(!entry) {
		throw std::runtime_error("Get host by name -> null");
	} 
	addr_list = (struct in_addr**)entry->h_addr_list;
	c_addr = addr_list[0];
	sad.sin_addr=*c_addr;
	error=::connect(skt, (struct sockaddr*)&sad, sizeof(struct sockaddr_in));
}

Network& Network::operator<<(std::string out){
	::write(skt,out.c_str(),out.length());
	return *this;
}
Network& Network::disconnect(){
	connected=false;	
	close(skt);
	return *this;
}
Network& Network::read(void *data,size_t count){
	::read(skt,data,count);
	return *this;
}
Network& Network::write(void *data,size_t count){
	::write(skt,data,count);
	return *this;
}
Network& Network::read(std::string& data,size_t count){
	char buffer[count+1];	
	::read(skt,buffer,count);
	buffer[count]=0;
	data=std::string(buffer);
	return *this;
}
Network& Network::write(std::string data,size_t count){
	char buffer [count+1]={0};
	memcpy(buffer,data.c_str(),count);
	buffer[count]=0;
	::write(skt,buffer,count);
	return *this;
}
int Network::connect(std::string ip, std::string port){
	sad.sin_port=htons(stoi(port));
	sad.sin_family=AF_INET;

	skt=socket(AF_INET,SOCK_STREAM,0);

	entry = gethostbyname(ip.c_str());
	if(!entry) {
		throw std::runtime_error("Get host by name -> null");
	}
	addr_list = (struct in_addr**)entry->h_addr_list;
	c_addr = addr_list[0];
	sad.sin_addr=*c_addr;
	
	error= ::connect(skt, (struct sockaddr*)&sad, sizeof(struct sockaddr_in));
	if (!error){
		connected=true;
	}
	return error;

}
