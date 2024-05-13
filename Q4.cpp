//QUESTION 4

void Game::addItemToPlayer(const std::string & recipient, uint16_t itemId)
{
    Player* player = g_game.getPlayerByName(recipient);
    //declare a boolean to check if a new player object was created
    bool newPlayerCreated = false;

    if (!player) {
        player = new Player(nullptr);
        if (!IOLoginData::loadPlayerByName(player, recipient)) {
            //to free memory, we need to delete the new Player object before the method returns
            delete player;
            return;
        }
        //record that a new player object was created
        newPlayerCreated = true;
    }

    Item* item = Item::CreateItem(itemId);
    if (!item) {
        if (newPlayerCreated) {
            //to free memory, we need to delete the new Player object before the method returns
            //but only if new player object was created, otherwise player does not exist
            delete player;
        }
        return;
    }

    g_game.internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT);

    if (player->isOffline()) {
        IOLoginData::savePlayer(player);
    }

    if (newPlayerCreated) {
        //we no longer need the new player object after the method finishes, delete it to free memory
        delete player;
    }
}