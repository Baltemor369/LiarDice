#include <iostream>
#include <random>
#include <cctype>
#include <chrono>
#include "inc/Player.h"
#include "const.h"

using namespace std;

bool isEmpty(int values[2]){
    return values[0] == NULL_INT && values[1] == NULL_INT  ;
}

int main(){
    // variables declaration
    char choice;
    bool running = true;
    int counter;
    int playerLeft = 4;
    int eliminated=0;
    // random generator
    auto now = std::chrono::high_resolution_clock::now();
    auto seed = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    random_device rd; 
    std::mt19937 gen(seed);
    uniform_int_distribution<> dis(1, 6);
    // list pseudos players
    string pseudos[4];
    // list players in game
    vector<Player*> players;
    // bet[0] = quantity, bet[1] = value
    int bet[2] = {NULL_INT,NULL_INT};

    // ask pseudos players
    cout << "Bienvenue dans le jeu Liar!"<<endl;
    for (int i = 0; i < 4; ++i) {
        cout << "Entrez le pseudo " << i + 1 << " : ";
        cin >> pseudos[i];
        players.push_back(new Player(pseudos[i]));
    }
    
    cout << "initialisation des des" << endl;
    // cout << players[0]->info()<<endl;
    // init dea for players
    for (size_t i = 0; i < playerLeft; i++) {
        for (size_t j = 0; j < MAX_QT_DEA; j++)
        {
            players[i]->addDea(dis(gen));
        }
    }
    
    cout << "\nLe jeu Liar peut commencer."<<endl;

    // display info players
    for(auto it : players){
        cout << it->info() << endl;
    }
    
    // game loop
    while (running)
    {
        for (size_t i = 0; i < 4; i++)
        {
            bool played = false;
            int index;
            while (!played){
                if (players[i]->getEliminated()!=0)
                {
                    ++i;
                    continue;
                }
                
                cout << endl << players[i]->getName() << ", Veuillez choisir une action : (M)enteur, (R)egarder ses des, augmenter (V)aleur, augmenter (Q)uantite, (S)ortir : ";
                cin >> choice;
                switch (toupper(choice))
                {
                case 'M':
                    if (isEmpty(bet))
                    {
                        break;
                    }
                    cout << players[i]->getName() << " dit que " << players[(i-1+4)%4]->getName() << " est un menteur\n";
                    // Check up
                    counter = 0;
                    // counting frequency value
                    for (int dea : players[i]->getDeas())
                    {
                        if (dea == bet[1]) ++counter;
                    }
                    // check bet said
                    if (counter == bet[0]){
                        // menteur echoué -1 dé pour l'accuseur
                        cout << players[(i-1+4)%4]->getName() << " n'a pas menti." << endl;
                        players[i]->removeDea();
                        // player no dea
                        if (!players[i]->hasDeas())
                        {
                            // player eliminated (jack)
                            cout << players[i]->getName() << " est elimine." << endl;
                            ++eliminated;
                            players[i]->setEliminated(eliminated);
                            --playerLeft;
                        }
                        
                    }else{
                        index = ((i-1+4)%4);
                        // menteur réussi -1 dé pour l'accusé
                        cout << players[index]->getName() << " a menti." << endl;
                        players[index]->removeDea();
                        // verifier si le joueur a encore des des
                        if (!players[index]->hasDeas())
                        {
                            cout << players[index]->getName() << " est elimine." << endl;
                            ++eliminated;
                            players[index]->setEliminated(eliminated);
                            --playerLeft;
                        }
                    }
                    // reroll deas for players
                    for (size_t i = 0; i < playerLeft; i++)
                    {
                        for (int j=0; j < players[i]->getQt(); j++)
                        {
                            players[i]->setDea(j, dis(gen));
                        }
                    }
                    bet[0] = NULL_INT;
                    bet[1] = NULL_INT;

                    played = true;
                    break;
                case 'V':
                    if (isEmpty(bet))
                    {
                        bool condition;
                        do
                        {
                            cout << "Entrer la quantite de cette valeur : ";
                            cin >> bet[0];
                            condition = (bet[0] >= MIN_QT_DEA && bet[0] <= MAX_QT_DEA);

                            cout << "Entrer la valeur des des : ";
                            cin >> bet[1];
                            condition = condition && (bet[1] >= MIN_VAL_DEA && bet[1] <= MAX_VAL_DEA);

                        } while (!condition);
                        played = true;
                        cout << "\n\n" << players[i]->getName() << " a " << bet[0] << " " << bet[1] << endl;
                    }else {
                        // augmente la valeur de 1
                        if (bet[1]<MAX_VAL_DEA+1)
                        {
                            ++bet[1];
                            played = true;
                            cout << "\n\n" << players[i]->getName() << " a " << bet[0] << " " << bet[1] << endl;
                        }
                    }
                    
                    break;
                case 'Q':
                    if (isEmpty(bet))
                    {
                        bool condition = false;
                        do
                        {
                            cout << "Entrer la quantite de cette valeur : ";
                            cin >> bet[0];
                            condition = (bet[0] >= MIN_QT_DEA && bet[0] <= MAX_QT_DEA);

                            cout << "Entrer la valeur des des : ";
                            cin >> bet[1];
                            condition = condition && (bet[1] >= MIN_VAL_DEA && bet[1] <= MAX_VAL_DEA);
                        } while (!condition);
                        played = true;
                        cout << "\n\n" << players[i]->getName() << " a " << bet[0] << " " << bet[1] << endl;
                    }else {
                        // augmente la quantité de 1
                        if (bet[0]<MAX_QT_DEA+1)
                        {
                            ++bet[0];
                            played = true;
                            cout << "\n\n" << players[i]->getName() << " a " << bet[0] << " " << bet[1] << endl;
                        }
                    }
                    break;
                case 'R':
                    for (size_t j = 0; j < players[i]->getQt(); j++)
                    {
                        cout << players[i]->getDea(j) << " ";
                    }
                    cout << endl;                
                    break;
                case 'S':
                    running = false;
                    played = true;
                    break;
                case 'P':
                    for (auto player : players)
                    {
                        if (player->getEliminated()==0)
                        {
                            cout << player->getName() << endl;
                        }
                    }
                    break;
                case 'C':
                    index = ((i-1+4)%4);
                    // menteur réussi -1 dé pour l'accusé
                    cout << players[index]->getName() << " a menti." << endl;
                    players[index]->removeDea();
                    // verifier si le joueur a encore des des
                    if (!players[index]->hasDeas())
                    {
                        cout << players[index]->getName() << " est elimine." << endl;
                        ++eliminated;
                        players[index]->setEliminated(eliminated);
                        --playerLeft;
                    }
                    break;
                default:
                    break;
                }
            }
            if (!running) break;
        }
    }
    

    return 0;
}