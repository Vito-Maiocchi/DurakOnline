#include "../include/game.hpp"
#include "../include/battle.hpp"
#include "../include/card_manager.hpp"

Game::Game(std::vector<ClientID> player_ids){
    // What does need to happen when a game of durak is created?
        // - Create a deck of 52 cards              //
        // - Shuffle the deck                       //
        // - Determine the trump suit               // 
        // - Distribute 6 cards to each player      // all done in the constructor of the card_manager
        card_manager_ = new CardManager(player_ids);
        // - Determine the first attacker
        Suit trump = card_manager_->getTrump();
        Card current_lowest_trump = Card(RANK_ACE, trump);
        // iterate through all players and find the one with the lowest trump card
        ClientID first_attacker = -1; // -1 means no one has a trump
        for(auto i : player_ids){
            std::vector<Card> hand = card_manager_->getPlayerHand(i);
            // iterate through hand
            for(unsigned j = 0; j < hand.size(); j++){
                if(hand[j].suit == trump && hand[j].rank <= current_lowest_trump.rank){
                    current_lowest_trump = hand[j];
                    first_attacker = i;
                }
            }
        }
        if(first_attacker == -1){
            // no one has a trump, choose a random player as the first attacker
            first_attacker = rand() % player_ids.size();
        }
        ClientID first_defender = (first_attacker + 1) % player_ids.size();
        ClientID second_attacker = (first_attacker + 2) % player_ids.size();
    // set private member player_roles_
    for(auto i : player_ids){
        if(i == first_attacker){
            player_roles_[i] = ATTACKER;
        }
        else if(i == first_defender){
            player_roles_[i] = DEFENDER;
        }
        else if(i == second_attacker){
            player_roles_[i] = CO_ATTACKER;
        }
        else{
            player_roles_[i] = IDLE;
        }
    }
    // - Start the first battle
    // only decomment this when constructor of battle user map
    // current_battle_ = new Battle(true, player_roles_, *card_manager_);
}

bool Game::createBattle(){
    // What does need to happen when a new battle is created?
        // - Check if the game is over
        // - Check if the game is started
        // - Check if the game is in the endgame
        // - Check if the game is in the reset state
        // - Check if the turn order needs to be updated
        // - Check if a client action event needs to be handled
        // - Check if a client card event needs to be handled
        // - Create a new battle
    return false;
}

bool Game::isStarted(){
    return false;
}

bool Game::endGame(){
    return false;
}

bool Game::resetGame(){
    return false;
}

bool Game::updateTurnOrder(){
    return false;
}

bool Game::handleClientActionEvent(){
    return false;
}

bool Game::handleClientCardEvent(){
    return false;
}
