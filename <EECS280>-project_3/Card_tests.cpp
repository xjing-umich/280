#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <sstream>

using namespace std;

TEST(test_return_suit) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(c.get_suit(), HEARTS);
    Suit trump = DIAMONDS;
    Card c2(JACK, HEARTS);
    ASSERT_EQUAL(c2.get_suit(trump), trump);

}
TEST(test_card_initialize) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card d(TWO, CLUBS);
    ASSERT_EQUAL(TWO, d.get_rank());
    ASSERT_EQUAL(CLUBS, d.get_suit());

    Card c1(KING, HEARTS);
    ASSERT_EQUAL(KING, c1.get_rank());
    ASSERT_EQUAL(HEARTS, c1.get_suit());

    Card c2(KING, DIAMONDS);
    ASSERT_EQUAL(KING, c2.get_rank());
    ASSERT_EQUAL(DIAMONDS, c2.get_suit());

    Card c3(KING, CLUBS);
    ASSERT_EQUAL(KING, c3.get_rank());
    ASSERT_EQUAL(CLUBS, c3.get_suit());

    Card c4(KING, SPADES);
    ASSERT_EQUAL(KING, c4.get_rank());
    ASSERT_EQUAL(SPADES, c4.get_suit());
}


TEST(test_card_default_constructor) {
    Card c2;
    ASSERT_EQUAL(c2.get_rank(), TWO);
    ASSERT_EQUAL(c2.get_suit(), SPADES);
}

TEST(test_card_comparison_less) {
    Card c1(QUEEN, HEARTS);
    Card c2(KING, HEARTS);
    ASSERT_TRUE(c1 < c2);


    Card c3(JACK, DIAMONDS);
    Card c4(JACK, DIAMONDS);
    ASSERT_FALSE(c3 < c4);

    Card c5(JACK, SPADES);
    Card c6(JACK, HEARTS);
    ASSERT_TRUE(c5 < c6);
}
TEST(test_card_comparison_less_equal) {
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, DIAMONDS);
    ASSERT_TRUE(c1 <= c2);

    Card c3(QUEEN, CLUBS);
    Card c4(KING, CLUBS);
    ASSERT_TRUE(c3 <= c4);

    Card c5(JACK, SPADES);
    Card c6(JACK, HEARTS);
    ASSERT_TRUE(c5 <= c6);
}

TEST(test_card_comparison_greater) {
    Card c1(KING, CLUBS);
    Card c2(QUEEN, CLUBS);
    ASSERT_TRUE(c1 > c2);

    Card c3(JACK, DIAMONDS);
    Card c4(JACK, DIAMONDS);
    ASSERT_FALSE(c3 > c4);

    Card c5(JACK, HEARTS);
    Card c6(JACK, SPADES);
    ASSERT_TRUE(c5 > c6);
}
TEST(test_card_comparison_greater_equal) {
    Card c1(KING, CLUBS);
    Card c2(QUEEN, CLUBS);
    ASSERT_TRUE(c1 >= c2);

    // Case 2: Same card
    Card c3(JACK, HEARTS);
    Card c4(JACK, HEARTS);
    ASSERT_TRUE(c3 >= c4);
    Card c5(JACK, HEARTS);
    Card c6(JACK, SPADES);
    ASSERT_TRUE(c5 >= c6);

}
TEST(test_card_comparison_equality) {
    Card c1(TEN, DIAMONDS);
    Card c2(TEN, DIAMONDS);
    ASSERT_TRUE(c1 == c2);
    ASSERT_FALSE(c1 != c2);

    Card c3(NINE, HEARTS);
    Card c4(TEN, HEARTS);
    ASSERT_FALSE(c3 == c4);
    ASSERT_TRUE(c3 != c4);

    Card c5(QUEEN, SPADES);
    Card c6(QUEEN, HEARTS);
    ASSERT_FALSE(c5 == c6);
    ASSERT_TRUE(c5 != c6);

    Card c7(THREE, CLUBS);
    Card c8(FIVE, DIAMONDS);
    ASSERT_FALSE(c7 == c8);
    ASSERT_TRUE(c7 != c8);
}

TEST(test_card_comparison_inequality) {
    Card c1(TWO, SPADES);
    Card c2(THREE, SPADES);
    ASSERT_TRUE(c1 != c2);

    Card c3(QUEEN, CLUBS);
    Card c4(QUEEN, DIAMONDS);
    ASSERT_TRUE(c3 != c4);

    Card c5(ACE, HEARTS);
    Card c6(JACK, SPADES);
    ASSERT_TRUE(c5 != c6);

    Card c7(KING, DIAMONDS);
    ASSERT_FALSE(c7 != c7);

}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);

    ASSERT_EQUAL(Suit_next(Suit_next(Suit_next(Suit_next(CLUBS)))), CLUBS);

}

TEST(test_card_less_trump) {
    Card c1(QUEEN, HEARTS);
    Card c2(JACK, CLUBS);
    ASSERT_TRUE(Card_less(c1, c2, CLUBS));

    Card c3(ACE, HEARTS);
    Card c4(ACE, HEARTS);
    ASSERT_FALSE(Card_less(c3, c4, CLUBS));



    Card c5(SEVEN, HEARTS);
    Card c6(NINE, DIAMONDS);
    ASSERT_TRUE(Card_less(c5, c6, CLUBS));

    Card c7(TWO, SPADES);
    Card c8(THREE, CLUBS);
    ASSERT_TRUE(Card_less(c7, c8, CLUBS));

}

TEST(test_card_less_trump_only) {
    Suit trump = HEARTS;

    Card right_bower(JACK, HEARTS);
    Card left_bower(JACK, DIAMONDS);
    Card trump_ace(ACE, HEARTS);
    Card non_trump_king(KING, SPADES);

    ASSERT_FALSE(Card_less(right_bower, left_bower, trump));
    ASSERT_TRUE(Card_less(left_bower, right_bower, trump));

    ASSERT_FALSE(Card_less(left_bower, trump_ace, trump));
    ASSERT_TRUE(Card_less(trump_ace, left_bower, trump));

    ASSERT_FALSE(Card_less(trump_ace, non_trump_king, trump));
    ASSERT_TRUE(Card_less(non_trump_king, trump_ace, trump));

    Card queen_spades(QUEEN, SPADES);
    ASSERT_FALSE(Card_less(non_trump_king, queen_spades, trump));
    ASSERT_TRUE(Card_less(queen_spades, non_trump_king, trump));
}

TEST(test_card_less_trump_and_led) {
    Suit trump = CLUBS;
    Card led_card(NINE, SPADES);

    Card right_bower(JACK, CLUBS);
    Card left_bower(JACK, SPADES);
    Card trump_king(KING, CLUBS);
    Card led_ace(ACE, SPADES);
    Card non_trump_queen(QUEEN, HEARTS);

    ASSERT_FALSE(Card_less(right_bower, left_bower, led_card, trump));
    ASSERT_TRUE(Card_less(left_bower, right_bower, led_card, trump));
    ASSERT_FALSE(Card_less(left_bower, trump_king, led_card, trump));
    ASSERT_TRUE(Card_less(trump_king, left_bower, led_card, trump));
    ASSERT_FALSE(Card_less(led_ace, non_trump_queen, led_card, trump));
    ASSERT_TRUE(Card_less(non_trump_queen, led_ace, led_card, trump));
    ASSERT_FALSE(Card_less(trump_king, led_ace, led_card, trump));
    ASSERT_TRUE(Card_less(led_ace, trump_king, led_card, trump));

    Card led_king(KING, SPADES);
    ASSERT_FALSE(Card_less(led_ace, led_king, led_card, trump));
    ASSERT_TRUE(Card_less(led_king, led_ace, led_card, trump));
}


TEST(test_card_stream_output) {
    Card c1(ACE, HEARTS);
    ostringstream oss;
    oss << c1;
    ASSERT_EQUAL(oss.str(), "Ace of Hearts");


    Card c2(JACK, DIAMONDS);
    oss.str(""); oss.clear();
    oss << c2;
    ASSERT_EQUAL(oss.str(), "Jack of Diamonds");

    Card c3(TWO, CLUBS);
    oss.str(""); oss.clear();
    oss << c3;
    ASSERT_EQUAL(oss.str(), "Two of Clubs");

    Card c4(FIVE, SPADES);
    oss.str(""); oss.clear();
    oss << c4;
    ASSERT_EQUAL(oss.str(), "Five of Spades");

    Card c5(SEVEN, HEARTS);
    oss.str(""); oss.clear();
    oss << c5;
    ASSERT_EQUAL(oss.str(), "Seven of Hearts");

    Card c6(NINE, CLUBS);
    oss.str(""); oss.clear();
    oss << c6;
    ASSERT_EQUAL(oss.str(), "Nine of Clubs");

    Card c7(KING, DIAMONDS);
    oss.str(""); oss.clear();
    oss << c7;
    ASSERT_EQUAL(oss.str(), "King of Diamonds");
}



TEST_MAIN()
