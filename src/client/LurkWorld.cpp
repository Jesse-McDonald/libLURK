#include <LurkWorld.h>
namespace LURK{

	//The following functions are used by the clent to send network packages		
	bool World::changeRoom(int index){
		if(index<0||index>=connections.size()){
			return false;
		}
		chRoomPkg con;
		con.number=connections[index].number;
		lurk.send(con);
		return true;
	}
	bool World::fight(int index){
		if(index<-1||index>=players.size()){
			return false;
		}else if(index==-1){
			fightPkg fight;
			lurk.send(fight);
		}else{
			pvpPkg pvp;
			pvp.target=players[index].name;
			lurk.send(pvp);
		}
		return true;
	}
	bool World::loot(int index){
		if(index<-1||index>=lootables.size()){
			return false;
		}else if(index==-1){
			for(int i=0;i<lootables.size();i++){
				loot(i);
			}
		}else{
			lootPkg loot;
			loot.target=lootables[index].name;
			lurk.send(loot);
		}
		return true;
	}
	void World::start(){
		startPkg start;
		lurk.send(start);
	}
	bool World::message(std::string mesg, int index){
		if(index<-1||index>=players.size()){
			return false;
		}else if(index==-1){
			message(mesg,"");
		}else{
			message(mesg,players[index].name);
		}
		return true;
	}
	void World::message(std::string message, std::string target){
		msgPkg msg;
		msg.sender=player.name;
		msg.recName=target;
		msg.msg=message;
		lurk.send(msg);
		chat.push_back(msg);
	}
	void World::sendCharacter(){
		lurk.send((pkg&)player);
	}
	void World::disconnect(){
		lurk.disconnect();
		lurk.stop();
	}
	bool World::connect(std::string ip, std::string port){
		lurk.connect(ip,port);
		lurk.startHandler();
	}
	bool World::connect(std::string ipPort){
		std::string ip;
		std::string port;
		std::string username;
		std::string parse;
		for(int i=0;i<0;i++){
			if(ipPort[i]=='@'){
				ip=parse;
				parse=std::string();
			}else if(ipPort[i]=':'){
				username=parse;
				parse=std::string();
			}else{
				parse+=ipPort[i];
			}
		}
		port=parse;
		player.name=username;
		return connect(ip, port);
	}


	//The following functions are to be called from lurk handlers to update internal status 
	void World::handle(msgPkg message){
		chat.push_back(message);
	}
	void World::handle(errorPkg err){
		error.push_back(err);
		msgPkg msg;
		msg.sender="ERROR";
		msg.recName=player.name;
	
		if(err.code==0){
			msg.msg="Received an error of type 0 (unspecefied type) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==1){
			msg.msg="Received an error of type 1 (Attempt to change to an inappropriate room) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==2){
			msg.msg="Received an error of type 2 (Attempt to create a player that already exists) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==3){
			msg.msg="Received an error of type 3 (Attempt to loot a nonexistent or not present monster) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==4){
			msg.msg="Received an error of type 4 (Attempt to set iappropriate player stats) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==5){
			msg.msg="Received an error of type 5 (Not ready) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==6){
			msg.msg="Received an error of type 6 (Target Player is not in this room) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==7){
			msg.msg="Received an error of type 7 (Fight Failed) from server:\nMessage sent was: "+err.msg;
		}else if(err.code==8){
			msg.msg="Received an error of type 8 (PVP Dissabled) from server:\nMessage sent was: "+err.msg;
		}else{
			msg.msg="Received an error of type "+std::to_string(err.code)+" (Non-standard type) from server:\nMessage sent was: "+err.msg;
		}
		chat.push_back(msg);
	}
	void World::handle(accPkg pkg){
		// I dont really handle accept packages at this point
	}
	void World::handle(roomPkg rm){
		connections.clear();
		players.clear();
		monsters.clear();
		lootables.clear();
		room=rm;
	}
	void World::handleLoot(charPkg loot){
		int index=findChr(lootables,loot);
		if(index!=-1){//the item is already in lootables
			if(loot.room!=room.number){//the item moved out of the room, delete it
				lootables[index]=lootables[lootables.size()];//swap and pop deletion
				lootables.pop_back();
			}else{//the item has been updated
				lootables[index]=loot;
			}
		}else{//the item is not in lootables
			lootables.push_back(loot);
			if(loot.getFlag(2)){//the item was a monster
				index=findChr(monsters,loot);//find the monster
				if(index!=-1){//monster found, delete it
					monsters[index]=monsters[monsters.size()];//swap and pop deletion
					monsters.pop_back();
				}
			}else{//the item was a player
				index=findChr(players,loot);//find the player
				if(index!=-1){//player found, delete it
					players[index]=players[players.size()];//swap and pop deletion
					players.pop_back();
				}
			}
		}
	}
	void World::handleMonster(charPkg monster){
		int index=findChr(monsters,monster);
		if(index!=-1){//new monster
			if(monster.room==room.number){//is it in the room?
				monsters.push_back(monster);
			}
		}else{//update monster
			if(monster.room==room.number){//is it in the room?
				monsters[index]=monster;
			}else{//it left
				monsters[index]=monsters[monsters.size()];
				monsters.pop_back();
			}
		}
	}
	void World::handlePlayer(charPkg givenPlayer){
		int index=findChr(players,givenPlayer);
		if(index!=-1){//new monster
			if(givenPlayer.room==room.number){//is it in the room?
				players.push_back(givenPlayer);
			}
		}else{//update monster
			if(player.room==room.number){//is it in the room?
				players[index]=givenPlayer;
			}else{//it left
				players[index]=players[players.size()];
				players.pop_back();
			}
		}
	}
	void World::handle(charPkg chr){
		if(chr.getFlag(2)&&chr.name==player.name){//uh oh, thats us
			player=chr;
		}
		if(chr.getFlag(0)){//its alive!
			if(chr.getFlag(2)){//its a monster
				handleMonster(chr);
			}else{//its a player
				handlePlayer(chr);
			}
		}else{//its dead
			handleLoot(chr);
		}
	}
	void World::handle(gamePkg gm){
		game=gm;
	}
	void World::handle(connectionPkg connection){
		connections.push_back(connection);
	}	
	void World::handle(pkg pak){//handle non-standard packages
		msgPkg msg;
		msg.sender="ERROR";
		msg.recName=player.name;
		msg.msg="Received Nonstandard packaged from server of type "+std::to_string(pak.type);
	}	
	int World::findChr(std::vector<charPkg>& array, charPkg target){//find if the target has an entity with the same name in the vector
		for(int i=0;i<array.size();i++){
			if(array[i].name==target.name){
				return i;
			}
		}
		return -1;
	}

	//constructors
	World::World(){

	}

	World::World(std::string ip, std::string port) : World(){
		connect(ip,port);
	}

	World::World(std::string ipPort){
		connect(ipPort);
	}

}//namespace end
