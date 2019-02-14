#ifndef LURK_WORLD_H 
#define LURK_WORLD_H
#include<vector>
#include<queue>
#include<lurkPks.h>
#include<LURK.h>
#include<string>
#include<unordered_map>
namespace LURK{
	class World{
		public:
		LURK lurk;//the LURK instance, it shouldnt be used, but there are times when it may need to be
		bool roomUpdated=false;//this is for the client so its easy to check if it needs to update everything,  it is up to the client to set this to false, but we will set it to true when the room needs updated
		//all following attributes are used by the client to determin the current state of the world
		roomPkg room;//the current room the player is in
		charPkg player;//the character pkg of the current player
		gamePkg game;//the initial game package sent by the server
		std::vector<connectionPkg> connections;//all current connections to the room
		std::vector<charPkg> players;//all players in the room
		std::vector<charPkg> monsters;//all monsters in the room
		std::vector<charPkg> lootables;//all lootables in the room
		std::unordered_map<std::string,charPkg> allPlayers;//all players encountered on the server this session
		std::vector<msgPkg> chat; //a queue of all chat messages sent or received in chronological order (also some error messages encoded as msgPkg
		std::vector<errorPkg> error;//all unhandled errors that the player may wish to know about
		

		//The following functions are used by the clent to send network packages
		bool changeRoom(int index);//index: index in connections to change to, returns false if out of range
		bool fight(int index=-1);//index: index of player to pvp fight, if -1 a fight package will be sent instead of pvpFight.  Returns false if index is out of range or 0
		bool loot(int index=-1);//index: index of the entity in loot to loot, if -1 a loot package will be sent to "".  returns false if out of range and not -1
		void start();//sends a start package to the server
		bool message(std::string message, int index=-1);//sends a messagae to player in the player array at index, if index is -1 the message is sent to no character.  Returns false if the index is not -1 and is out of bounds
		void message(std::string message, std::string target);//send a message to the target player, if this fails the error should appear in the error vector
		void sendCharacter();//sends the current player pkg to the server
		void disconnect();//sends a leave package if connected to a server and then cleans up the network
		bool connect(std::string ip, std::string port);//takes the ip or url of the server followed by the port, returns false if the server can not be found
		bool connect(std::string ipPort);//takes the ip or url and port in 1 line with the port following a : (example.com:5191),
		//this function also supports a user name before the ip sepperated by a @ (username@example.com:5191)
		//The username will be automatically converted to the initial name of the player
		//returns false if the server can not be found
		
		
		//The following functions are to be called from lurk handlers to update internal status 
		void handle(msgPkg message);//appends message to chat, no error checking on target is performed
		void handle(errorPkg err);//append error to the error list, also converts relevent errors to messages and appends to messages
		void handle(accPkg pkg);//receives accept packages, but for not ignores most of them
		void handle(roomPkg room);//changes current room to reflect the sent room
		void handle(charPkg chr);//updates current character if certain conditions are met, otherwise it appends to the players, monsters, or loot lists as needed.
		void handle(gamePkg game);//updates or sets the game package
		void handle(connectionPkg connection);//appends connection to the connections queue
		void handle(pkg pak);//handles any packets that should not be sent by the server by converting them into error codes and informing the user that the server may not be stable.		


		//constructors
		World();//prep empty lurk instance
		World(std::string ip, std::string port);//takes the ip or url of the server followed by the port
		World(std::string ipPort);//takes ip or url and port in 1 line, see connect(std::string ipPort)
		
		//internal functions for helping, not priviate because they could be usefull and wont be harmfull of externaly used		
		void handleLoot(charPkg);
		void handleMonster(charPkg);
		void handlePlayer(charPkg);
		int findChr(std::vector<charPkg>& array, charPkg target);
	};

};


#endif
