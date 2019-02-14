#ifndef LURK_H
#define LURK_H

#include <thread>
#include <queue>
#include <network.h>
#include <mutexwrap.h>
#include <map>
#include <bitset>
#include <lurkPks.h>
#ifdef MAIN
	#define EXTERN
	#else
	#define EXTERN extern
#endif
//server functionality not currently implimented
namespace LURK{
 
	class LURK{

		private:
			std::thread reader;
			WrapMutex readLock;
			WrapMutex handleLock;	
			WrapMutex sendLock;
			bool closeThread=false;
		public:
			void* gameObj;
			LURK();
			LURK(void* obj);
			Pkg cPak;
			std::queue<Pkg> pks;
			Network network;

			int connect(std::string ip, std::string port);
			int startServer(std::string port);
			LURK& disconnect();
			
			Pkg receive();
			LURK& readPkg();

			LURK& send(Pkg &pkg);

			LURK& handle(Pkg& pkg);
			
			LURK& send(pkg &pkg);
			LURK& handle(pkg& pkg);
			LURK& handleAll();
			LURK& handleLoop();
			LURK& readAndHandle();
			LURK& startHandler();//mutualy exclusive
			LURK& startReader();

			LURK& stop();
			~LURK();


	};
}
#endif // LURK_H
