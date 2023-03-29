#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define DECK_SIZE (NUM_RANKS * NUM_SUITS)


// The Card struct represents a playing card.
typedef struct Card {
    int value;   // value of the card (2-14)
} Card;

// The Player struct represents a player in the game.
typedef struct Player {
    int player_number;    // player number (1 to N)
    int *hand;            // array of cards in hand
} Player;

// The Deck struct represents a deck of cards.
typedef struct Deck {
    Card cards[DECK_SIZE];  // array of cards in deck
} Deck;

void shuffle_deck(Deck*);

// prints players hands
void print_hands(int num_players, int hand_size, Player *players) {
    // Print out the cards in each player's hand.
    for (int i = 0; i < num_players; i++) {
        printf("Player %d hand: ", players[i].player_number);
        for (int j = 0; j < hand_size; j++) {
            printf("%d ", players[i].hand[j]);
        }
        printf("\n");
    }
}

// prints players hands
void print_pile(Deck pile) {
    // Print out the cards in each player's hand.
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("%d ", pile.cards[i].value);
    }
    printf("\n");
}
// remove zeros from hand
void remove_zeros(int *hand) {
    int i, j;
    for (i = 0, j = 0; i < DECK_SIZE; i++) {
        if (hand[i] != 0) {
            hand[j] = hand[i];
            j++;
        }
    }
    // Fill the rest of the array with 0's
    for (; j < DECK_SIZE; j++) {
        hand[j] = 0;
    }
}

// create pile with all 0 values
Deck create_pile() {
    Deck pile;
    for( int i = 0; i < DECK_SIZE; i++ ) {
        pile.cards[i].value = 0;
    }
    return pile;
}

// Creates a new deck of cards, in ascending order.
Deck create_deck() {
    Deck deck;
    int index = 0;
    for (int value = 2; value <= 14; value++) {
        for (int suit = 0; suit < NUM_SUITS; suit++) {
            deck.cards[index].value = value;
            index++;
        }
    }
    shuffle_deck(&deck);
    return deck;
}

// Shuffles the given deck of cards
void shuffle_deck(Deck *deck) {
    //srand(time(NULL));
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

// Creates an array of N players and allocates 52/N cards in each player's hand array.
Player *create_players(int num_players) {
    Player *players = malloc(num_players * sizeof(Player));
    int hand_size = DECK_SIZE;
    for (int i = 0; i < num_players; i++) {
        players[i].player_number = i + 1;
        players[i].hand = malloc(hand_size * sizeof(int));
        for (int j = 0; j < hand_size; j++) {
            players[i].hand[j] = 0;  // initialize hand to 0
        }
    }
    return players;
}

// completes one round of the game
void complete_round(Player *players, int player_count, Deck *pile, int *pile_counter) {
    for ( int i = 0; i < player_count; i++ ) {
        pile->cards[*pile_counter].value = players[i].hand[0];
        players[i].hand[0] = 0;
        remove_zeros(&players[i].hand[0]);
        (*pile_counter)++;
    }
}

int main() {
    // create decks
    Deck deck = create_deck();
    Deck pile = create_pile();
    // create players
    int num_players = 4;
    Player *players = create_players(num_players);
    
    // deal hands to players
    int hand_size = DECK_SIZE / num_players;
    int card_index = 0;
    for (int i = 0; i < num_players; i++) {
        for (int j = 0; j < hand_size; j++) {
            players[i].hand[j] = deck.cards[card_index].value;
            card_index++;
        }
    }

    int *pile_counter = 0;
    print_pile(pile);
    print_hands(num_players, hand_size, players);
    complete_round(players, num_players, &pile, pile_counter);
    printf("Pile counter: %d\n", pile_counter);
    complete_round(players, num_players, &pile, pile_counter);
    printf("Pile counter: %d\n", pile_counter);
    complete_round(players, num_players, &pile, pile_counter);
    printf("Pile counter: %d\n", pile_counter);
    print_pile(pile);
    print_hands(num_players, hand_size, players);
    // Free memory allocated for players' hands and player array.
    for (int i = 0; i < num_players; i++) {
        free(players[i].hand);
    }
    free(players);

    return 0;
}
