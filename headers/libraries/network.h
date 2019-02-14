#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <netinet/ip.h>
#include <unistd.h>
#include <cstdint>

class Network{//simple network wrapper
	private:
		struct sockaddr_in sad;
		struct hostent* entry;
		struct in_addr **addr_list;
		struct in_addr* c_addr;
		int skt=0;
		
		Network& operator>>(std::string out){return *this;}
	public:
		bool connected;
		int error;
		Network();
		Network(std::string ip, std::string port);
		template<typename T> Network& operator>>(T& in){
			::read(skt,&in,sizeof(in));
			return *this;
		}
		template<typename T> Network& operator<<(T out){
			::write(skt,&out,sizeof(out));
			return *this;
		}		
		Network& operator<<(std::string out);
		Network& disconnect();
		Network& read(void *data,size_t count);
		Network& write(void *data,size_t count);
		Network& read(std::string& data,size_t count);
		Network& write(std::string data,size_t count);
		int connect(std::string ip, std::string port);
		int listen(std::string port);
};
#endif
