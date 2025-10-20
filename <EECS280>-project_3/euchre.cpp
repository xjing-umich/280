#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Player.hpp"
#include "Pack.hpp"
#include "Card.hpp"
using namespace std;

      
class Game {
public:
    Game(istream& pack_input, string shuffle, int points_to_win,
         vector<string> player_info) : pack(pack_input),
    point_win(points_to_win),
        dealer_index(0), shuffle_or_not(shuffle){

        int length = player_info.size() / 2;
        for (int i = 0; i < length; i++) {
            players.push_back(Player_factory(player_info[i], player_info[i + length]));
            player_score.push_back(0);
        };
    }


    void play() {
        int hand_number = 0;
        while ((player_score[0] + player_score[2]) / 2 < point_win &&
            (player_score[1] + player_score[3]) / 2 < point_win) {
            cout << "Hand " << hand_number << endl;
            cout << players[dealer_index]->get_name() << " deals" << endl;

            deal();
            make_trump();
            play_hand();
            print_game_status();

            dealer_index = (dealer_index + 1) % 4;
            hand_number++;
        }

        determine_player();
    }

private:
    vector<Player*> players;
    Pack pack;
    int point_win;
    int dealer_index;
    vector<int> player_score;
    Suit trump;
    int trump_player;
    string shuffle_or_not;

    void determine_player() {
        if ((player_score[0] + player_score[2]) / 2 >= point_win) {
            cout << players[0]->get_name() << " and " << players[2]->get_name()
                << " win!" << endl;
        }
        else {
            cout << players[1]->get_name() << " and " << players[3]->get_name()
                << " win!" << endl;
        }

        for (Player* player : players) {
            delete player;
        }
    }

    void deal() {
        pack.reset();
        if (shuffle_or_not == "shuffle") {
            pack.shuffle();
        }
        int player_index = (dealer_index + 1) % 4;
        
        int deal_pattern[2][4] = { {3, 2, 3, 2}, {2, 3, 2, 3} };

        for (int round = 0; round < 2; round++) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < deal_pattern[round][i]; j++) {
                    players[player_index]->add_card(pack.deal_one());
                }
                player_index = (player_index + 1) % 4;
            }
        }
    }

    void make_trump() {
        Card upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
        Suit order_up_suit = upcard.get_suit();
        
        for (int round = 1; round <= 2; ++round) {
            if (try_to_make_trump(upcard, order_up_suit, round)) {
                return;
            }
        }

        force_dealer_to_choose(upcard, order_up_suit);
    }

    
    bool try_to_make_trump(const Card& upcard, Suit order_up_suit, int round) {
        for (int i = 1; i <= 4; ++i) {
            int player_index = (dealer_index + i) % 4;
            if (players[player_index]->make_trump(upcard, 
                player_index == dealer_index, round, order_up_suit)) {
                set_trump(player_index, order_up_suit, upcard, round);
                return true;
            }
            cout << players[player_index]->get_name() << " passes" << endl;
        }
        return false;
    }

   
    void set_trump(int player_index, Suit order_up_suit, const Card& upcard, int round) {
        trump = order_up_suit;
        trump_player = player_index;
        cout << players[player_index]->get_name() << " orders up " << trump << endl;
        
        if (round == 1) {
            players[dealer_index]->add_and_discard(upcard);
        }
    }

    
    void force_dealer_to_choose(const Card& upcard, Suit order_up_suit) {
        trump_player = dealer_index;
        trump = Suit_next(order_up_suit);
        cout << players[dealer_index]->get_name() 
        << " is forced to order up " << trump << endl;
    }

    void play_hand() {
        int leader = (dealer_index + 1) % 4;
        vector<int> team_tricks(2, 0);

        Card led_card;
        Card card_played;
        vector<Card> played_cards;
        int trick_winner;
        int winner_index;
        for (int i = 0; i < 5; i++) {
            played_cards.clear();

            led_card = players[leader]->lead_card(trump);
            played_cards.push_back(led_card);
            cout << led_card << " led by " << players[leader]->get_name() << endl;

            for (int j = 0; j < 3; j++) {
                int current_player = (leader + j + 1) % 4;
                card_played = players[current_player]->play_card(led_card, trump);
                played_cards.push_back(card_played);
                cout << card_played << " played by "
                    << players[current_player]->get_name() << endl;
            }

            trick_winner = determine_trick_winner(played_cards, trump, led_card);
            winner_index = (leader + trick_winner) % 4;

            cout << players[winner_index]->get_name() << " takes the trick"
                << endl << endl;
            team_tricks[winner_index % 2]++;
            leader = winner_index;
        }

        print_trick_result(team_tricks);

    }

    void print_trick_result(vector<int> team_tricks) {
        if (team_tricks[0] > team_tricks[1]) {
            if (trump_player == 0 || trump_player == 2) {
                if (team_tricks[0] == 3 || team_tricks[0] == 4) {
                    cout << players[0]->get_name() << " and "
                        << players[2]->get_name() << " win the hand" << endl;
                    player_score[0] += 1;
                    player_score[2] += 1;
                }
                else {
                    cout << players[0]->get_name() << " and "
                        << players[2]->get_name() << " win the hand" << endl;
                    player_score[0] += 2;
                    player_score[2] += 2;
                    cout << "march!" << endl;
                }
            }
            else {
                cout << players[0]->get_name() << " and "
                    << players[2]->get_name() << " win the hand" << endl;
                player_score[0] += 2;
                player_score[2] += 2;
                cout << "euchred!" << endl;
            }
        }
        else {
            if (trump_player == 1 || trump_player == 3) {
                if (team_tricks[1] == 3 || team_tricks[1] == 4) {
                    cout << players[1]->get_name() << " and "
                        << players[3]->get_name() << " win the hand" << endl;
                    player_score[1] += 1;
                    player_score[3] += 1;
                }
                else {
                    cout << players[1]->get_name() << " and "
                        << players[3]->get_name() << " win the hand" << endl;
                    player_score[1] += 2;
                    player_score[3] += 2;
                    cout << "march!" << endl;
                }
            }
            else {
                cout << players[1]->get_name() << " and "
                    << players[3]->get_name() << " win the hand" << endl;
                player_score[1] += 2;
                player_score[3] += 2;
                cout << "euchred!" << endl;
            }
        }
    }

    int determine_trick_winner
    (const vector<Card>& played_cards, Suit trump, Card led_card) {
        int best_index = 0;
        for (int i = 1; i < 4; ++i) {
            if (Card_less(played_cards[best_index], played_cards[i], led_card, trump)) {
                best_index = i;
            }
        }
        return best_index;
    }

    void print_game_status() {
        cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " have " << (player_score[0] + player_score[2]) / 2 << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " have " << (player_score[1] + player_score[3]) / 2 << " points" << endl;
    }



};


int main(int argc, char* argv[]) {


    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;

    bool condition = true;
    if (argc != 12) {
        condition = false;
    }

    string points_str = argv[3];
    int points_to_win = stoi(points_str);
    if (points_to_win < 1 || points_to_win > 100) {
        condition = false;
    }

    string shuffle_or_not = argv[2];
    if (shuffle_or_not != "shuffle" && shuffle_or_not != "noshuffle") {
        condition = false;
    }

    if (!condition) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return -1;
    }

    ifstream input_file(argv[1]);
    if (!input_file) {
        cout << "Error opening " << argv[1] << endl;
        return -1;
    }

    vector<string> players = { argv[4],argv[6],argv[8]
        ,argv[10],argv[5],argv[7],argv[9],argv[11] };

    Game game(input_file, shuffle_or_not, stoi(argv[3]), players);
    game.play();
    return 0;
}

