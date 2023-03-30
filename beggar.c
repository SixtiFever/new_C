#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// prints players hands. Arguments are number of player, hand_sizes
// and the players. 
void print_hands(int num_players, int hand_size, Player *players) {
    // Print out the cards in each player's hand.
    int i, j;
    for (i = 0; i < num_players; i++) {
        printf("Player %d hand: ", players[i].player_number);
        for (j = 0; j < hand_size; j++) {
            printf("%d ", players[i].hand[j]);
        }
        printf("\n");
    }
}

// prints the current pile that players
// are placing cards onto. Takes in the pile
// as an argument. Returns void.
void print_pile(Deck pile) {
    // Print out the cards in each player's hand.
    int i;
    for (i = 0; i < DECK_SIZE; i++) {
        printf("%d ", pile.cards[i].value);
    }
    printf("\n");
}

// Removes zeros from player hand after they have
// placed a card. Then moves all non-zero cards
// in their hand forward. Takes hand as an 
// argument.
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

// Creates the initial pile of 52 cards
// all of which are assigned 0 value.
// Returns a Deck struct.
Deck create_pile() {
    Deck pile;
    int i;
    for( i = 0; i < DECK_SIZE; i++ ) {
        pile.cards[i].value = 0;
    }
    return pile;
}

// Creates a new deck of cards, in ascending order.
// Deck is then shuffled. Returns an instance of Deck struct.
Deck create_deck() {
    Deck deck;
    int index = 0;
    int value;
    for ( value = 2; value <= 14; value++ ) {
        for (int suit = 0; suit < NUM_SUITS; suit++) {
            deck.cards[index].value = value;
            index++;
        }
    }
    shuffle_deck(&deck);
    return deck;
}

// Shuffles the deck of cards. Takes in a pointer to a
// deck as an argument, and shuffles the deck. Returns
// void.
void shuffle_deck(Deck *deck) {
    int i;
    for ( i = DECK_SIZE - 1; i > 0; i-- ) {
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

// Creates the initial players in the game. Takes 
// in the number of players, and allocates memoryfrom the heap
// for all players.
Player *create_players(int num_players) {
    Player *players;
    if( !( players = malloc(num_players * sizeof(Player) ) ) ) {
        printf("Error assigning memory for players\n");
    }
    //malloc(num_players * sizeof(Player));
    int hand_size = DECK_SIZE;
    int i, j;
    for ( i = 0; i < num_players; i++ ) {
        players[i].player_number = i + 1;
        if( !( players[i].hand = malloc(hand_size * sizeof(int) ) ) ) {
            printf("Error assigning mempory for hand in create_players()\n");
        }
        //players[i].hand = malloc(hand_size * sizeof(int));
        for ( j = 0; j < hand_size; j++ ) {
            players[i].hand[j] = 0;  // initialize hand to 0
        }
    }
    return players;
}

// completes one round of the game. Takes in pointer to players, the number of players
// a pointer to the pile and a pointer to a variable that is tracking the top of the pile.
void complete_round(Player *players, int player_count, Deck *pile, int *pile_counter) {
    int i;
    for ( i = 0; i < player_count; i++ ) {
        pile->cards[*pile_counter].value = players[i].hand[0];
        printf("Adding %d to the pile from player %d\n", pile->cards[*pile_counter].value, players[i].player_number );
        players[i].hand[0] = 0;
        remove_zeros(&players[i].hand[0]);
        
        /* if a penalty card do something */
        if( pile->cards[i].value > 10 ) {
            int j;
            bool completed = false;

            while(!completed) {
                int penalty_card_val = pile->cards[i].value;
                int penalty_count = penalty_card_val % 10;
                Player penalised_player = players[i+1];

                for( j = 0; j < penalty_card_val % 10; j++ ) {
                    (*pile_counter)++;
                    pile->cards[*pile_counter].value = players[i+1].hand[j];
                    printf("Adding %d to the pile from player %d\n", pile->cards[*pile_counter].value, players[i+1].player_number );
                    players[i+1].hand[j]= 0;
                    //remove_zeros(&players[i+1].hand[0]);
                    
                    // if another penalty card is placed
                    if( players[i+1].hand[j] > 10) {
                        players[i+1].hand[j] = 0;
                        remove_zeros(&players[i+1].hand[0]);
                        i++;
                        break;
                    }
                    
                    
                    

                    if( j == penalty_count -1 ) {
                        remove_zeros(&players[i+1].hand[0]);
                        //i++;
                        break;
                    }
                }
                
                completed = true;
            }
        }
        
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
    int i, j;
    for ( i = 0; i < num_players; i++ ) {
        for ( j = 0; j < hand_size; j++ ) {
            players[i].hand[j] = deck.cards[card_index].value;
            card_index++;
        }
    }

    int *pile_counter = 0;
    printf("Initial pile\n");
    print_pile(pile);
    printf("Initial hands\n");
    print_hands(num_players, hand_size, players);
    printf("\n\n");
    
    int k;
    for( k = 0; k < 20; k++ ) {
        printf("Round %d\n",k);
        complete_round(players, num_players, &pile, &pile_counter);
        print_hands(num_players, hand_size, players);
        print_pile(pile);
        printf("\n\n");
    }

    int f;
    // Free memory allocated for players' hands and player array.
    for ( f = 0; f < num_players; f++) {
        free(players[i].hand);
    }
    free(players);

    return 0;
}
