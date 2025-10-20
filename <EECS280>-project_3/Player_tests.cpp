#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_simple_player_get_name) {
    Player* player = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", player->get_name());
    delete player;
}
TEST(test_simple_player_add_card) {
    Player* player = Player_factory("Bob", "Simple");
    Card card1(NINE, SPADES);
    Card card2(TEN, HEARTS);

    player->add_card(card1);
    player->add_card(card2);

    Suit order_up_suit;
    bool result = player->make_trump(card1, false, 1, order_up_suit);
    ASSERT_FALSE(result);

    delete player;
}

TEST(test_simple_player_add_and_discard) {
    Player* player = Player_factory("Alice", "Simple");
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, SPADES));

    Card upcard(ACE, HEARTS);
    player->add_and_discard(upcard);

    bool nine_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, SPADES), HEARTS);
        if (played.get_rank() == NINE && played.get_suit() == SPADES) {
            nine_discarded = false;
        }
    }
    ASSERT_TRUE(nine_discarded);
    delete player;

    player = Player_factory("Dana", "Simple");
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, SPADES));

    Card upcard2(ACE, HEARTS);
    player->add_and_discard(upcard2);

    Suit order_up_suit;
    bool result = player->make_trump(upcard2, false, 1, order_up_suit);
    ASSERT_TRUE(result);

    delete player;

    player = Player_factory("Eve", "Simple");
    player->add_card(Card(TEN, CLUBS));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(ACE, CLUBS));

    Card upcard3(NINE, HEARTS);
    player->add_and_discard(upcard3);

    bool ten_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, SPADES), HEARTS);
        if (played.get_rank() == TEN && played.get_suit() == CLUBS) {
            ten_discarded = false;
        }
    }
    ASSERT_TRUE(ten_discarded);
    delete player;

    player = Player_factory("Frank", "Simple");
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, CLUBS));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(KING, SPADES));

    Card upcard4(ACE, CLUBS);
    player->add_and_discard(upcard4);

    bool JACK_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, SPADES), CLUBS);
        if (played.get_rank() == JACK && played.get_suit() == HEARTS) {
            JACK_discarded = false;
        }
    }
    ASSERT_TRUE(JACK_discarded);
    delete player;

    player = Player_factory("Grace", "Simple");
    player->add_card(Card(NINE, DIAMONDS));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, DIAMONDS));

    Card upcard5(ACE, SPADES);
    player->add_and_discard(upcard5);

    bool nine_diamonds_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, SPADES), DIAMONDS);
        if (played.get_rank() == NINE && played.get_suit() == DIAMONDS) {
            nine_diamonds_discarded = false;
        }
    }
    ASSERT_TRUE(nine_diamonds_discarded);
    delete player;

    player = Player_factory("Hank", "Simple");
    player->add_card(Card(TWO, SPADES));
    player->add_card(Card(THREE, SPADES));
    player->add_card(Card(FOUR, SPADES));
    player->add_card(Card(FIVE, SPADES));
    player->add_card(Card(SIX, SPADES));

    Card upcard6(ACE, SPADES);
    player->add_and_discard(upcard6);

    bool two_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, SPADES), SPADES);
        if (played.get_rank() == TWO && played.get_suit() == SPADES) {
            two_discarded = false;
        }
    }
    ASSERT_TRUE(two_discarded);
    delete player;

    player = Player_factory("Ivy", "Simple");
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(TEN, HEARTS));

    Card upcard7(NINE, CLUBS);
    player->add_and_discard(upcard7);

    bool nine_clubs_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, CLUBS), HEARTS);
        if (played.get_rank() == TEN && played.get_suit() == HEARTS) {
            nine_clubs_discarded = false;
        }
    }
    ASSERT_TRUE(nine_clubs_discarded);
    delete player;

    player = Player_factory("Jake", "Simple");
    player->add_card(Card(ACE, DIAMONDS));
    player->add_card(Card(KING, CLUBS));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(TEN, DIAMONDS));

    Card upcard8(NINE, SPADES);
    player->add_and_discard(upcard8);

    bool ten_diamonds_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, SPADES), DIAMONDS);
        if (played.get_rank() == TEN && played.get_suit() == DIAMONDS) {
            ten_diamonds_discarded = false;
        }
    }
    ASSERT_TRUE(ten_diamonds_discarded);
    delete player;

    player = Player_factory("Karen", "Simple");
    player->add_card(Card(ACE, SPADES));
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(ACE, DIAMONDS));
    player->add_card(Card(ACE, CLUBS));
    player->add_card(Card(KING, SPADES));

    Card upcard9(NINE, CLUBS);
    player->add_and_discard(upcard9);

    bool ninetrial_discarded = true;
    for (int i = 0; i < 5; ++i) {
        Card played = player->play_card(Card(NINE, CLUBS), SPADES);
        if (played.get_rank() == KING && played.get_suit() == SPADES) {
            ninetrial_discarded = false;
        }
    }
    ASSERT_TRUE(ninetrial_discarded);
    delete player;
}

TEST(test_simple_player_make_trump2) {
    Player* player = Player_factory("Charlie", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit = SPADES;
    bool order_up;

    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    order_up = player->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(HEARTS, order_up_suit);
    delete player;

    player = Player_factory("Dave", "Simple");
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(NINE, DIAMONDS));
    player->add_card(Card(TEN, CLUBS));
    order_up = player->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(order_up);
    delete player;

    player = Player_factory("Eve", "Simple");
    player->add_card(Card(ACE, DIAMONDS));
    player->add_card(Card(KING, DIAMONDS));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(TEN, CLUBS));
    order_up = player->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);
    delete player;

    player = Player_factory("Frank", "Simple");
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(KING, SPADES));
    order_up = player->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(order_up);
    order_up = player->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_FALSE(order_up);
    delete player;

    player = Player_factory("Grace", "Simple");
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(TEN, HEARTS));
    order_up = player->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(HEARTS, order_up_suit);
    delete player;

    player = Player_factory("Helen", "Simple");
    player->add_card(Card(ACE, DIAMONDS));
    player->add_card(Card(KING, DIAMONDS));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(TEN, DIAMONDS));
    order_up = player->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(order_up);
    order_up = player->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);
    delete player;

    player = Player_factory("Ivy", "Simple");
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, CLUBS));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, CLUBS));
    order_up = player->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(order_up);
    order_up = player->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_FALSE(order_up);
    delete player;

    player = Player_factory("Jack", "Simple");
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(KING, SPADES));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(TEN, CLUBS));
    order_up = player->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(order_up);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);
    delete player;

    player = Player_factory("Kevin", "Simple");
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, CLUBS));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, CLUBS));
    order_up = player->make_trump(upcard, true, 2, order_up_suit);
    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);
    delete player;

    player = Player_factory("Liam", "Simple");
    player->add_card(Card(NINE, DIAMONDS));
    player->add_card(Card(TEN, DIAMONDS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(KING, DIAMONDS));
    order_up = player->make_trump(upcard, true, 2, order_up_suit);
    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);
    delete player;
}



TEST(test_simple_player_make_trump) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob makes tump
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = bob->make_trump(
        nine_spades,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete bob;
}

TEST(test_simple_player_lead_card) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
        Card(NINE, HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led, ace_spades); //check led card

    delete bob;
}

TEST(test_simple_player_play_card) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob plays a card
    Card nine_diamonds(NINE, DIAMONDS);
    Card card_played = bob->play_card(
        nine_diamonds,  // Nine of Diamonds is led
        HEARTS    // Trump suit
    );

    // Verify the card Bob played
    ASSERT_EQUAL(card_played, Card(NINE, SPADES));
    delete bob;
}

TEST(test_simple_player_lead_card2) {
    Player* player = Player_factory("George", "Simple");
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(TEN, CLUBS));
    player->add_card(Card(KING, DIAMONDS));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(NINE, CLUBS));
    Card lead = player->lead_card(SPADES);
    ASSERT_EQUAL(Card(ACE, HEARTS), lead);
    delete player;

    player = Player_factory("Helen", "Simple");
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(KING, SPADES));
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, SPADES));
    lead = player->lead_card(SPADES);
    ASSERT_EQUAL(Card(JACK, SPADES), lead);
    delete player;

    player = Player_factory("Ivy", "Simple");
    player->add_card(Card(NINE, DIAMONDS));
    player->add_card(Card(TEN, CLUBS));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(KING, CLUBS));
    lead = player->lead_card(HEARTS);
    ASSERT_EQUAL(Card(KING, CLUBS), lead);
    delete player;

    player = Player_factory("Jack", "Simple");
    player->add_card(Card(ACE, CLUBS));
    player->add_card(Card(KING, CLUBS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(TEN, CLUBS));
    lead = player->lead_card(DIAMONDS);
    ASSERT_EQUAL(Card(ACE, CLUBS), lead);
    delete player;

    player = Player_factory("Kevin", "Simple");
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(KING, SPADES));
    player->add_card(Card(ACE, SPADES));
    player->add_card(Card(TEN, SPADES));
    lead = player->lead_card(SPADES);
    ASSERT_EQUAL(Card(JACK, SPADES), lead);
    delete player;

    player = Player_factory("Liam", "Simple");
    player->add_card(Card(NINE, HEARTS));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(KING, HEARTS));
    lead = player->lead_card(HEARTS);
    ASSERT_EQUAL(Card(JACK, HEARTS), lead);
    delete player;

    player = Player_factory("Mason", "Simple");
    player->add_card(Card(ACE, DIAMONDS));
    player->add_card(Card(KING, DIAMONDS));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(TEN, DIAMONDS));
    lead = player->lead_card(CLUBS);
    ASSERT_EQUAL(Card(ACE, DIAMONDS), lead);
    delete player;

    player = Player_factory("Nina", "Simple");
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, SPADES));
    lead = player->lead_card(DIAMONDS);
    ASSERT_EQUAL(Card(KING, SPADES), lead);
    delete player;

    player = Player_factory("Oscar", "Simple");
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(TEN, HEARTS));
    lead = player->lead_card(SPADES);
    ASSERT_EQUAL(Card(ACE, HEARTS), lead);
    delete player;

    player = Player_factory("Paul", "Simple");
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(KING, SPADES));
    lead = player->lead_card(CLUBS);
    ASSERT_EQUAL(Card(KING, SPADES), lead);
    delete player;
}


TEST(test_simple_player_play_card2) {
    Player* player = Player_factory("Ivan", "Simple");
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, SPADES));
    Card led_card(NINE, HEARTS);
    Card played = player->play_card(led_card, DIAMONDS);
    ASSERT_EQUAL(Card(KING, HEARTS), played);
    delete player;

    player = Player_factory("Jack", "Simple");
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(KING, CLUBS));
    led_card = Card(NINE, HEARTS);
    played = player->play_card(led_card, DIAMONDS);
    ASSERT_EQUAL(Card(NINE, CLUBS), played);
    delete player;

    player = Player_factory("Kevin", "Simple");
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(KING, CLUBS));
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, DIAMONDS));
    led_card = Card(NINE, CLUBS);
    played = player->play_card(led_card, SPADES);
    ASSERT_EQUAL(Card(KING, CLUBS), played);
    delete player;

    player = Player_factory("Liam", "Simple");
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(TEN, CLUBS));
    led_card = Card(NINE, HEARTS);
    played = player->play_card(led_card, SPADES);
    ASSERT_EQUAL(Card(ACE, HEARTS), played);
    delete player;

    player = Player_factory("Mason", "Simple");
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(KING, SPADES));
    player->add_card(Card(ACE, SPADES));
    led_card = Card(NINE, SPADES);
    played = player->play_card(led_card, DIAMONDS);
    ASSERT_EQUAL(Card(ACE, SPADES), played);
    delete player;

    player = Player_factory("Nina", "Simple");
    player->add_card(Card(NINE, HEARTS));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, SPADES));
    led_card = Card(NINE, HEARTS);
    played = player->play_card(led_card, DIAMONDS);
    ASSERT_EQUAL(Card(TEN, HEARTS), played);
    delete player;

    player = Player_factory("Oscar", "Simple");
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, CLUBS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, CLUBS));
    led_card = Card(NINE, CLUBS);
    played = player->play_card(led_card, HEARTS);
    ASSERT_EQUAL(Card(KING, CLUBS), played);
    delete player;

    player = Player_factory("Paul", "Simple");
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, SPADES));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(KING, CLUBS));
    led_card = Card(NINE, SPADES);
    played = player->play_card(led_card, DIAMONDS);
    ASSERT_EQUAL(Card(JACK, SPADES), played);
    delete player;

    player = Player_factory("Quinn", "Simple");
    player->add_card(Card(NINE, HEARTS));
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(QUEEN, SPADES));
    player->add_card(Card(KING, DIAMONDS));
    led_card = Card(NINE, HEARTS);
    played = player->play_card(led_card, SPADES);
    ASSERT_EQUAL(Card(NINE, HEARTS), played);
    delete player;

    player = Player_factory("Ryan", "Simple");
    player->add_card(Card(ACE, DIAMONDS));
    player->add_card(Card(KING, DIAMONDS));
    player->add_card(Card(QUEEN, HEARTS));
    player->add_card(Card(JACK, CLUBS));
    player->add_card(Card(TEN, SPADES));
    led_card = Card(NINE, DIAMONDS);
    played = player->play_card(led_card, HEARTS);
    ASSERT_EQUAL(Card(ACE, DIAMONDS), played);
    delete player;

    player = Player_factory("Steve", "Simple");
    player->add_card(Card(NINE, CLUBS));
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(QUEEN, DIAMONDS));
    player->add_card(Card(KING, CLUBS));
    led_card = Card(NINE, SPADES);
    played = player->play_card(led_card, HEARTS);
    ASSERT_EQUAL(Card(TEN, SPADES), played);
    delete player;

    player = Player_factory("Tom", "Simple");
    player->add_card(Card(ACE, SPADES));
    player->add_card(Card(KING, SPADES));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(JACK, HEARTS));
    player->add_card(Card(TEN, CLUBS));
    led_card = Card(NINE, SPADES);
    played = player->play_card(led_card, DIAMONDS);
    ASSERT_EQUAL(Card(ACE, SPADES), played);
    delete player;

    player = Player_factory("Frank", "Simple");
    player->add_card(Card(NINE, SPADES));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(QUEEN, CLUBS));
    player->add_card(Card(KING, SPADES));

    led_card = Card(NINE, SPADES);
    Suit trump = HEARTS;
    played = player->play_card(led_card, trump);

    ASSERT_EQUAL(KING, played.get_rank());
    ASSERT_EQUAL(SPADES, played.get_suit());

    Card new_led_card(ACE, HEARTS);
    played = player->play_card(new_led_card, trump);

    if (played.get_suit(trump) == new_led_card.get_suit(trump)) {
        ASSERT_EQUAL(JACK, played.get_rank());
        ASSERT_EQUAL(DIAMONDS, played.get_suit());
    }
    else {
        ASSERT_EQUAL(NINE, played.get_rank());
    }

    delete player;
}
TEST_MAIN()
