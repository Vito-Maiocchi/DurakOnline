#pragma once

#include "card_manager.hpp"
#include "../../Networking/include/Networking/util.hpp"
#include "../../Networking/include/Networking/message.hpp"
#include "battle.hpp"

#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <optional>

using player_id = unsigned int;
//class Battle; //forward declaration to avoid circular dependencies

class Game{

    private:
        // vector of pairs containing the player ids and their roles
        // has to be stored here because battle might be destructed
        std::map<ClientID, PlayerRole> player_roles_;

        //current battle
        std::optional<Battle> current_battle_ = std::nullopt;
        //card manager
        CardManager card_manager_;

        std::set<ClientID> finished_players_;

    public:
        // constructor taking in an array of player ids
        Game(std::set<ClientID> &players);

        //add friend class
        friend class DurakGameTest;

        void createBattle();
        bool isStarted();
        bool endGame();
        bool resetGame();
        void updateTurnOrder();
        bool handleClientActionEvent(std::unique_ptr<Message> message, ClientID client);
        ClientID handleClientCardEvent(std::unique_ptr<Message> message, ClientID client);
        void updateFinishedPlayers();
        ClientID findlastplayer();

        //getter function for testing purposes
        Battle* getCurrentBattle(){ return &current_battle_.value();}
        CardManager* getCardManager(){ return &card_manager_;}
        std::map<ClientID, PlayerRole> getPlayerRoles(){ return player_roles_;}

};
