#include "Pack.hpp"
// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on. 
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack() {
	int num = 0;
	next = 0;
	for (int s = SPADES; s <= DIAMONDS; ++s) {
		Suit suit = static_cast<Suit>(s);
		for (int i = NINE; i <= ACE; i++) {
			Rank rank = static_cast<Rank>(i);
			Card card = Card(rank, suit);
			cards[num] = card;
			num += 1;
		}
	}
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input) {
	Pack::next = 0;
	Card card;
	for (int i = 0; i < PACK_SIZE; i ++) {
		pack_input >> card;
		cards[i] = card;
	}
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
	next += 1;
	return cards[next - 1];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
	next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.

void Pack::shuffle() {
	int num = 0;
	for (int i = 0; i < 7; i++) {
		std::array<Card, PACK_SIZE> temp_card;
		num = 0;
		for (int index = 0; index < PACK_SIZE / 2; index++) {
			temp_card[num] = cards[index + PACK_SIZE / 2];
			temp_card[num + 1] = cards[index];
			num += 2;
		}
		cards = temp_card;
	}
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
	if (next == 24) {
		return true;
	}
	else {
		return false;
	}
}

