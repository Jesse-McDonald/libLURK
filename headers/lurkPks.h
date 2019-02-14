#ifndef LURKPKS_H
#define LURKPKS_H

#include <map>
#include <network.h>
#include <bitset>

namespace LURK{
 	class Pkg;//this is a wraper for pkg
	class pkg;
	typedef void* (*handlerFunc)(pkg*,void*);
	class pkg{//base
		private:
			static handlerFunc _handler;

		public:
			static std::map<int,pkg*> packages;
			friend Pkg;
			virtual pkg& selfCast(pkg*&);
			virtual pkg* clone();
			pkg();
			virtual ~pkg();
			virtual pkg& registerHandler(handlerFunc);
			virtual pkg& registerPkg(int,pkg*);
			//yah, the previous line is supose to be a function that takes a
			//function that takes only a pkg& as an argument, and a void* for class
			//pointer if neaded, as an argument
			virtual void* handle(void* object);//this will take the object and if it exists call the
			//function on the packet
			virtual pkg& send(Network network,bool sendType=true);
			virtual pkg& receive(Network network,bool readType=true);
			virtual pkg& receive(pkg*& self, Network network,bool readType=true);

			uint8_t type;
	};

	class msgPkg:public pkg{	//type 1
		private:
			static handlerFunc _handler;
		public:
			virtual msgPkg* clone();
			virtual void* handle(void* object);
			virtual msgPkg& registerHandler(handlerFunc);
			virtual msgPkg& receive(Network network,bool readType=true);
			virtual msgPkg& send(Network network,bool sendType=true);
			std::string recName;
			std::string sender;
			std::string msg;
			msgPkg();
	};

	class chRoomPkg:public pkg{	//type 2
		private:
			static handlerFunc _handler;
		public:
			virtual chRoomPkg* clone();
			virtual void* handle(void* object);
			virtual chRoomPkg& registerHandler(handlerFunc);
			virtual chRoomPkg& receive(Network network,bool readType=true);
			virtual chRoomPkg& send(Network network,bool sendType=true);
			uint16_t number;
			chRoomPkg();
	};

	class fightPkg:public pkg{	//type 3
		private:
			static handlerFunc _handler;
		public:
			virtual fightPkg* clone();
			virtual void* handle(void* object);
			virtual fightPkg& registerHandler(handlerFunc);
			virtual fightPkg& receive(Network network,bool readType=true);
			virtual fightPkg& send(Network network,bool sendType=true);
			fightPkg();
		//no extra data contained in fight packages
	};

	class pvpPkg:public pkg{	//type 4
		private:
			static handlerFunc _handler;
		public:
			virtual pvpPkg* clone();
			virtual void* handle(void* object);
			virtual pvpPkg& registerHandler(handlerFunc);
			virtual pvpPkg& receive(Network network,bool readType=true);
			virtual pvpPkg& send(Network network,bool sendType=true);
			std::string target;
			pvpPkg();
	};

	class lootPkg:public pkg{	//type 5
		private:
			static handlerFunc _handler;
		public:
			virtual lootPkg* clone();
			virtual void* handle(void* object);
			virtual lootPkg& registerHandler(handlerFunc);
			virtual lootPkg& receive(Network network,bool readType=true);
			virtual lootPkg& send(Network network,bool sendType=true);
			std::string target;
			lootPkg();
	};

	class startPkg:public pkg{//type 6
		private:
			static handlerFunc _handler;
		public:
			virtual startPkg* clone();
			virtual void* handle(void* object);
			virtual startPkg& registerHandler(handlerFunc);
			virtual startPkg& receive(Network network,bool readType=true);
			virtual startPkg& send(Network network,bool sendType=true);
			startPkg();
		//no extra data contained in fight packages
	};

	class errorPkg:public pkg{	//type 7
		private:
			static handlerFunc _handler;
		public:
			virtual errorPkg* clone();
			virtual void* handle(void* object);
			virtual errorPkg& registerHandler(handlerFunc);
			virtual errorPkg& receive(Network network,bool readType=true);
			virtual errorPkg& send(Network network,bool sendType=true);
			uint8_t code;
			std::string msg;
			errorPkg();

	};

	class accPkg:public pkg{	//type 8
		private:
			static handlerFunc _handler;
		public:
			virtual accPkg* clone();
			virtual void* handle(void* object);
			virtual accPkg& registerHandler(handlerFunc);
			virtual accPkg& receive(Network network,bool readType=true);
			virtual accPkg& send(Network network,bool sendType=true);
			uint8_t accType;
			accPkg();
	};

	class roomPkg:public pkg{	//type 9
		private:
			static handlerFunc _handler;
		public:
			virtual roomPkg* clone();
			virtual void* handle(void* object);
			virtual roomPkg& registerHandler(handlerFunc);
			virtual roomPkg& receive(Network network,bool readType=true);
			virtual roomPkg& send(Network network,bool sendType=true);
			uint16_t number;
			std::string name;
			std::string description;
			roomPkg();
	};

	class charPkg:public pkg{	//type 10
		private:
			static handlerFunc _handler;
		public:
			virtual charPkg* clone();
			virtual void* handle(void* object);
			virtual charPkg& registerHandler(handlerFunc);
			virtual charPkg& receive(Network network,bool readType=true);
			virtual charPkg& send(Network network,bool sendType=true);
			void setFlag(int index,bool set);//QOL function to ease setting a specific bit in flags
			bool getFlag(int index);//QOL function to ease getting a specific bit in flags
			std::string name;
			uint8_t flags;//alive,pvp,monster,started,ready,reserved,reserved,reserved
			uint16_t atk;
			uint16_t def;
			uint16_t reg;
			signed short health;
			uint16_t gold;
			uint16_t room;
			std::string description;
			charPkg();
	};

	class gamePkg:public pkg{	//type 11
		private:
			static handlerFunc _handler;
		public:
			virtual gamePkg* clone();
			virtual void* handle(void* object);
			virtual gamePkg& registerHandler(handlerFunc);
			virtual gamePkg& receive(Network network,bool readType=true);
			virtual gamePkg& send(Network network,bool sendType=true);
			uint16_t init;
			uint16_t statMax;
			std::string description;
			gamePkg();
	};

	class leavePkg:public pkg{	//type 12
		private:
			static handlerFunc _handler;
		public:
			virtual leavePkg* clone();
			virtual void* handle(void* object);
			virtual leavePkg& registerHandler(handlerFunc);
			virtual leavePkg& receive(Network network,bool readType=true);
			virtual leavePkg& send(Network network,bool sendType=true);
			leavePkg();
		//no extra data contained in fight packages
	};

	class connectionPkg:public pkg{	//type 9
		private:
			static handlerFunc _handler;
		public:
			virtual connectionPkg* clone();
			virtual void* handle(void* object);
			virtual connectionPkg& registerHandler(handlerFunc);
			virtual connectionPkg& receive(Network network,bool readType=true);
			virtual connectionPkg& send(Network network,bool sendType=true);
			uint16_t number;
			std::string name;
			std::string description;
			connectionPkg();
	};
	class Pkg{
			int* copies;//track how many copies of PKG exist so we can delete (or not) the pkg when needed
			void deInstance();
	public:
			Pkg();

			Pkg(const Pkg& other);
			Pkg& operator=(const Pkg& other);
			~Pkg();
			pkg* data;
			Pkg& receive(Network,bool readType=true);
			Pkg& send(Network,bool writeType=true);
			void* handle(void* object);
	};
}
#endif // LURK_H
