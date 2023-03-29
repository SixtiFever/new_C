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

// int penalty(Player *player1, Player *player2, Deck **pile, int top_index, bool *completed) {
//     printf("%d %d\n",player1->player_number,player2->player_number);
//     printf("%p %d\n", **pile, pile->cards[top_index].value);
//     // printf("Player %d place a %d. Now player %d must place down %d cards\n", player1->player_number, pile->cards[top_index].value, player2->player_number, (pile->cards[top_index].value) % 10);
    
//     return 1;
// }

// completes one round of the game
void complete_round(Player *players, int player_count, Deck *pile, int *pile_counter) {
    for ( int i = 0; i < player_count; i++ ) {
        pile->cards[*pile_counter].value = players[i].hand[0];
        printf("Adding %d to the pile from player %d\n", pile->cards[*pile_counter].value, players[i].player_number );
        players[i].hand[0] = 0;
        remove_zeros(&players[i].hand[0]);
        
        /* if a penalty card do something */
        if( pile->cards[i].value > 10 ) {
            
            bool completed = false;

            while(!completed) {
                int penalty_card_val = pile->cards[i].value;
                int penalty_count = penalty_card_val % 10;
                Player penalised_player = players[i+1];

                for( int j = 0; j < penalty_card_val % 10; j++ ) {
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
    for (int i = 0; i < num_players; i++) {
        for (int j = 0; j < hand_size; j++) {
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
    
    for( int j = 0; j < 20; j++ ) {
        printf("Round %d\n",j);
        complete_round(players, num_players, &pile, &pile_counter);
        print_hands(num_players, hand_size, players);
        print_pile(pile);
        printf("\n\n");
    }

    
    // Free memory allocated for players' hands and player array.
    for (int i = 0; i < num_players; i++) {
        free(players[i].hand);
    }
    free(players);

    return 0;
}
