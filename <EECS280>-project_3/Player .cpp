#include "Player.hpp"
#include <iostream>
#include <algorithm>
using namespace std;



class SimplePlayer : public Player {
private:
    string name;
    vector<Card> hand;

public:
    SimplePlayer(const string& name) : name(name) {}

    const string& get_name() const override {
        return name;
    }

    void add_card(const Card& c) override {
        if (hand.size() < MAX_HAND_SIZE) {
            hand.push_back(c);
        }
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, Suit& order_up_suit) const override {
        int face_or_ace_count = 0;
        Suit upcard_suit = upcard.get_suit();

        if (round == 1) {
            for (size_t i = 0; i < hand.size(); ++i) {
                const Card& c = hand[i];
                if ((c.is_face_or_ace() && c.get_suit(upcard_suit) == upcard_suit)
                    || c.is_right_bower(upcard_suit)) {
                    face_or_ace_count++;
                }
            }
            if (face_or_ace_count >= 2) {
                order_up_suit = upcard_suit;
                return true;
            }
        }
        else if (round == 2) {
            Suit next_suit = Suit_next(upcard_suit);
            for (size_t i = 0; i < hand.size(); ++i) {
                const Card& c = hand[i];
                if ((c.is_face_or_ace() && c.get_suit(next_suit) == next_suit)
                    || c.is_right_bower(next_suit)) {
                    order_up_suit = next_suit;
                    return true;
                }
            }
            if (is_dealer) {
                order_up_suit = next_suit;
                return true;
            }
        }
        return false;
    }

    void add_and_discard(const Card& upcard) override {
        hand.push_back(upcard);
        int min_index = 0;

        for (int i = 1; i < hand.size(); ++i) {
            if (Card_less(hand[i], hand[min_index], upcard.get_suit())) {
                min_index = i;
            }
        }

        hand.erase(hand.begin() + min_index);
    }

    Card lead_card(Suit trump) override {
        Card play;
        int index = 0;
        bool exist_non_trump = false;
        vector<int> non_trump;
        for (int i = 0; i < hand.size(); i++) {
            if (!hand[i].is_trump(trump)) {
                exist_non_trump = true;
                non_trump.push_back(i);
            }
        }

        if (exist_non_trump) {
            play = hand[non_trump[0]];
            index = non_trump[0];
            for (int j = 0; j < non_trump.size(); j++) {
                if (Card_less(play, hand[non_trump[j]], trump)) {
                    play = hand[non_trump[j]];
                    index = non_trump[j];
                }
            }
        }
        else {
            play = hand[0];
            index = 0;
            for (int j = 0; j < hand.size(); j++) {
                if (Card_less(play, hand[j], trump)) {
                    play = hand[j];
                    index = j;
                }
            }
        }
        hand.erase(hand.begin() + index);
        return play;

    }

    Card play_card(const Card& led_card, Suit trump) override {
        Suit led_suit = led_card.get_suit(trump);
        Card play;
        int index = 0;
        bool exist_led = false;
        vector<int> led_cards;

        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].get_suit(trump) == led_suit) {
                exist_led = true;
                led_cards.push_back(i);
            }
        }

        if (exist_led) {
            play = hand[led_cards[0]];
            index = led_cards[0];
            for (int j = 1; j < led_cards.size(); j++) {
                if (Card_less(play, hand[led_cards[j]], trump)) {
                    play = hand[led_cards[j]];
                    index = led_cards[j];
                }
            }
        }
        else {
            play = hand[0];
            for (int j = 1; j < hand.size(); j++) {
                if (Card_less(hand[j], play, trump)) {
                    play = hand[j];
                    index = j;
                }
            }
        }

        hand.erase(hand.begin() + index);
        return play;
    }
};








class HumanPlayer : public Player {
private:
    string name;
    vector<Card> hand;

    void print_hand() const {
        for (size_t i = 0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
    }

public:
    HumanPlayer(const std::string& name) : name(name) {}

    const std::string& get_name() const override {
        return name;
    }

    void add_card(const Card& c) override {
        if (hand.size() < MAX_HAND_SIZE) {
            hand.push_back(c);
        }
        std::sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, Suit& order_up_suit) const override {
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

        string user_input;
        cin >> user_input;

        if (user_input != "pass") {
            order_up_suit = string_to_suit(user_input);
            
            return true;
        }
        else {
            return false;
        }
    }

    void add_and_discard(const Card& upcard) override {
        print_hand();
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        int decision;
        cin >> decision;
        if (decision == -1) {
            return;
        }
        hand.erase(hand.begin() + decision);
        add_card(upcard);
    }

    Card lead_card(Suit trump) override {
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        int num;
        cin >> num;
        Card temp = hand[num];
        hand.erase(hand.begin() + num);
        return temp;
    }

    Card play_card(const Card& led_card, Suit trump) override {
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        int num;
        cin >> num;
        Card temp = hand[num];
        hand.erase(hand.begin() + num);
        return temp;
    }
};



Player* Player_factory(const string& name, const string& strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    else if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    else {
        throw invalid_argument("Unknown strategy: " + strategy);
    }
}


ostream& operator<<(ostream& os, const Player& p) {
    os << p.get_name();
    return os;
}
