
#include <lurkPks.h>
#include <LURK.h>
namespace LURK{
//GOTO PKG
	
	handlerFunc pkg::_handler=0;
	std::map<int,pkg*> pkg::packages=std::map<int,pkg*>();

	pkg::pkg(){
			type=0;
	}

	pkg::~pkg(){}
	pkg& pkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	pkg& pkg::registerPkg(int key,pkg* package){
		packages.insert(std::pair<int,pkg*>(key,package));
		return *this;
	}
	void* pkg::handle(void* object){
		return _handler(this,object);
	}
	pkg& pkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		//no extra data sent
		return *this;
	}
	pkg& pkg::receive(Network network,bool readType){
		type=0;
		if (readType){
			network>>type;
		}
		//no extra data received
		return *this;
	}
	pkg& pkg::receive(pkg*& self, Network network,bool readType){
		type=0;
		if (readType){
			network>>type;
			selfCast(self);
			self->receive(network,false);
		}
		return *this;
	}
	pkg* pkg::clone(){
		return new pkg();
	}
	pkg& pkg::selfCast(pkg*& self){
		pkg* temp=self->packages[self->type];
		if(!temp) temp=new pkg();//theoreticaly this if will trigger if the pkg does not exist and trigger the default	
		temp->type=self->type;
		delete self;
		self=temp->clone();
		self->type=temp->type;
	}
//GOTO MSGPKG
	msgPkg::msgPkg(){
		type=1;
	}
	msgPkg* msgPkg::clone(){
		return new msgPkg();
	}
	msgPkg& msgPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* msgPkg::handle(void* object){
		return _handler(this,object);
	}
	msgPkg& msgPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		uint16_t len;
		network>>len;
		network.read(recName,32);
		network.read(sender,32);
		network.read(msg,len);
		return *this;
	}
	msgPkg& msgPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		uint16_t len=msg.length();;
		network<<len;
		network.write(recName,32);
		network.write(sender,32);
		network.write(msg,len);
		return *this;
	}
	handlerFunc msgPkg::_handler=0;
//GOTO CHROOMPKG
	chRoomPkg::chRoomPkg(){
		type=2;
	}
	chRoomPkg* chRoomPkg::clone(){
		return new chRoomPkg();
	}
	chRoomPkg& chRoomPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* chRoomPkg::handle(void* object){
		return _handler(this,object);
	}
	chRoomPkg& chRoomPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network>>this->number;
		return *this;
	}
	chRoomPkg& chRoomPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network<<number;
		return *this;
	}
	handlerFunc chRoomPkg::_handler=0;
//GOTO FIGHTPKG
	fightPkg::fightPkg(){
		type=3;
	}
	fightPkg* fightPkg::clone(){
		return new fightPkg();
	}
	fightPkg& fightPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* fightPkg::handle(void* object){
		return _handler(this,object);
	}
	fightPkg& fightPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		//no extra data received
		return *this;
	}
	fightPkg& fightPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		//no extra data received
		return *this;
	}
	handlerFunc fightPkg::_handler=0;
//GOTO PVPPKG
	pvpPkg::pvpPkg(){
		type=4;
	}
	pvpPkg* pvpPkg::clone(){
		return new pvpPkg();
	}
	pvpPkg& pvpPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* pvpPkg::handle(void* object){
		return _handler(this,object);
	}
	pvpPkg& pvpPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network.read(this->target,32);
		return *this;
	}
	pvpPkg& pvpPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network.write(this->target,32);
		return *this;
	}
	handlerFunc pvpPkg::_handler=0;
//GOTO LOOTPKG
	lootPkg::lootPkg(){
		type=5;
	}
	lootPkg* lootPkg::clone(){
		return new lootPkg();
	}
	lootPkg& lootPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* lootPkg::handle(void* object){
		return _handler(this,object);
	}
	lootPkg& lootPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network.read(this->target,32);
		return *this;
	}
	lootPkg& lootPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network.write(this->target,32);
		return *this;
	}
	handlerFunc lootPkg::_handler=0;
//GOTO STARTPKG
	startPkg::startPkg(){
		type=6;
	}
	startPkg* startPkg::clone(){
		return new startPkg();
	}
	startPkg& startPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* startPkg::handle(void* object){
		return _handler(this,object);
	}
	startPkg& startPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		//no extra data received
		return *this;
	}
	startPkg& startPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		//no extra data received
		return *this;
	}
	handlerFunc startPkg::_handler=0;
//GOTO ERRORPKG
	errorPkg::errorPkg(){
		type=7;
	}
	errorPkg* errorPkg::clone(){
		return new errorPkg();
	}
	errorPkg& errorPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* errorPkg::handle(void* object){
		return _handler(this,object);
	}
	errorPkg& errorPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network>>this->code;
		unsigned short len;
		network>>len;
		network.read(this->msg,len);
		return *this;
	}
	errorPkg& errorPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network<<this->code;
		unsigned short len=msg.length();
		network<<len;
		network.write(this->msg,len);
		return *this;
	}
	handlerFunc errorPkg::_handler=0;
//GOTO ACCPKG
	accPkg::accPkg(){
		type=8;
	}
	accPkg* accPkg::clone(){
		return new accPkg();
	}
	accPkg& accPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* accPkg::handle(void* object){
		return _handler(this,object);
	}
	accPkg& accPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network>>this->accType;
		return *this;
	}
	accPkg& accPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network<<this->accType;
		return *this;
	}
	handlerFunc accPkg::_handler=0;
//GOTO ROOMPKG
	roomPkg::roomPkg(){
		type=9;
	}
	roomPkg* roomPkg::clone(){
		return new roomPkg();
	}
	roomPkg& roomPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* roomPkg::handle(void* object){
		return _handler(this,object);
	}
	roomPkg& roomPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network>>this->number;
		network.read(this->name,32);
		unsigned short len;
		network>>len;
		network.read(this->description,len);		
		return *this;
	}
	roomPkg& roomPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network<<this->number;
		network.write(this->name,32);
		unsigned short len=description.length();
		network<<len;
		network.write(this->description,len);
		return *this;
	}
	handlerFunc roomPkg::_handler=0;
//GOTO CHARPKG
	charPkg::charPkg(){
		type=10;
	}
	charPkg* charPkg::clone(){
		return new charPkg();
	}
	charPkg& charPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* charPkg::handle(void* object){
		return _handler(this,object);
	}
	charPkg& charPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network.read(this->name,32);
		network>>this->flags;
		network>>this->atk;
		network>>this->def;
		network>>this->reg;
		network>>this->health;
		network>>this->gold;
		network>>this->room;
		unsigned short len;
		network>>len;
		network.read(this->description,len);
		return *this;
	}
	charPkg& charPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network.write(this->name,32);
		network<<this->flags;
		network<<this->atk;
		network<<this->def;
		network<<this->reg;
		network<<this->health;
		network<<this->gold;
		network<<this->room;
		unsigned short len=description.length();
		network<<len;
		network.write(this->description,len);
		return *this;
	}
	void charPkg::setFlag(int index, bool set){
		if(index>=0&&index<8){		
			uint8_t mask=1<<(8-index);//set mask index from the right
			this->flags=flags&(mask^0xff);//use the mask to clear the bit in question by inverting the mask and anding by it
			if (set) this->flags=flags|mask;//set flag to true if required
		}
	}
	bool charPkg::getFlag(int index){
		if(index>=0&&index<8){		
			uint8_t mask=1<<(8-index);//set mask index from the right
			return this->flags&mask;//use mask to determin state of bit		
		}
		return false;
	}
	handlerFunc charPkg::_handler=0;
//GOTO GAMEPKG
	gamePkg::gamePkg(){
		type=11;
	}
	gamePkg* gamePkg::clone(){
		return new gamePkg();
	}
	gamePkg& gamePkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* gamePkg::handle(void* object){
		return _handler(this,object);
	}
	gamePkg& gamePkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network>>this->init;
		network>>this->statMax;
		unsigned short len;
		network>>len;
		network.read(this->description,len);
		return *this;
	}
	gamePkg& gamePkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network<<this->init;
		network<<this->statMax;
		unsigned short len=description.length();
		network<<len;
		network.write(this->description,len);
		return *this;
	}
	handlerFunc gamePkg::_handler=0;
//GOTO LEAVEPKG
	leavePkg::leavePkg(){
		type=12;
	}
	leavePkg* leavePkg::clone(){
		return new leavePkg();
	}
	leavePkg& leavePkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* leavePkg::handle(void* object){
		return _handler(this,object);
	}
	leavePkg& leavePkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		//no extra data received
		return *this;
	}
	leavePkg& leavePkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		//no extra data received
		return *this;
	}
	handlerFunc leavePkg::_handler=0;
//GOTO CONNECTIONPKG
	connectionPkg::connectionPkg(){
		type=13;
	}
	connectionPkg* connectionPkg::clone(){
		return new connectionPkg();
	}
	connectionPkg& connectionPkg::registerHandler(handlerFunc pkgHandler){
		_handler=pkgHandler;
		return *this;
        }
	void* connectionPkg::handle(void* object){
		return _handler(this,object);
	}
	connectionPkg& connectionPkg::receive(Network network,bool readType){
		if (readType){
			network>>type;	
		}
		network>>this->number;
		network.read(this->name,32);
		unsigned short len;
		network>>len;
		network.read(this->description,len);
		return *this;
	}
	connectionPkg& connectionPkg::send(Network network,bool sendType){
		if (sendType) network<<type;
		network<<this->number;
		network.write(this->name,32);
		unsigned short len=description.length();
		network<<len;
		network.write(this->description,len);
		return *this;
	}
	handlerFunc connectionPkg::_handler=0;
//GOTO PKGWRAPPER
	void Pkg::deInstance(){
		(*copies)--;
		if ((*copies)<1){ 

			delete data;//only if we are out of copies do we delete pkg	
			delete copies;//dont forget to delete copies too		
		}
	}


	Pkg::Pkg(const Pkg& other){
		copies=other.copies;
		data=other.data;
		(*copies)++;

		//deInstance();
	

	}
	Pkg& Pkg::operator=(const Pkg& other){
		deInstance();
		copies=other.copies;
		data=other.data;
		(*copies)++;
	
		//deInstance();
	}

	Pkg::Pkg(){
		data=new pkg();
		copies=new int(1);
	}
	Pkg::~Pkg(){
		deInstance();
	}
	Pkg& Pkg::receive(Network network,bool readType){
		data->receive(data,network,readType);
		return *this;
	}
	Pkg& Pkg::send(Network network,bool writeType){
		data->send(network,writeType);
		return *this;
	}
	void* Pkg::handle(void* object){
		return data->handle(object);
	}

}//namespace end
