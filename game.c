/*
Numero de cardas
-2: 3
0: 11
-1, 1-12: 7

Total: 105
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_deck
{
    int total_cards;
    int *cards;
    int is_shown[12];
} t_deck;


#define M_2_MAX  3
#define CERO  11
#define NORMAL  7



char *show_deck(t_deck *deck)
{
    int iter;

    iter = 0;
    printf("cardas:");
    while (iter < deck->total_cards)
    {
        printf("%i, ", deck->cards[iter]);
        iter++;
    }
    printf("\n");
}

int find_card_deck(t_deck *deck, int number)
{
    int iter;

    iter = 0;
    if (!deck || number > 12 || number < -2)
        return (404);
    while(iter < deck->total_cards)
    {
        if (deck->cards[iter] == number)
            return (iter);
        iter++;
    }
    return (404);
}

void remove_card_deck(t_deck **deck, int number)
{
    int *new_cards;
    int n_cards;
    int pos_num_rem;
    int iter_new;

    if (!(*deck))
        return ;
    n_cards = (*deck)->total_cards;
    new_cards = (int *)malloc(sizeof(int) * (n_cards - 1));
    if (!new_cards)
        return ;
    pos_num_rem = find_card_deck(*deck, number);
    if (pos_num_rem == 404)
        return ;
    iter_new = 0;
    for(int iter = 0; iter < n_cards; iter++)
    {
        if (iter != pos_num_rem)
            new_cards[iter_new++] = (*deck)->cards[iter];
    }     
    free((*deck)->cards);
    (*deck)->cards = new_cards;
    (*deck)->total_cards--;
}

void append_card_deck(t_deck **deck, int number)
{
    int *new_cards;
    int n_cards;
    int iter;

    if (!(*deck))
        return ;
    n_cards = (*deck)->total_cards;
    new_cards = (int *)malloc(sizeof(int) * (n_cards + 1));
    if (!new_cards)
        return ;
    iter = 0;
    while (iter < n_cards)
    {
        new_cards[iter] = (*deck)->cards[iter];
        iter++;
    }
    new_cards[iter++] = number;
    if ((*deck)->cards)
        free((*deck)->cards);
    (*deck)->cards = new_cards;
    (*deck)->total_cards++;
}

void init_deck(t_deck **deck)
{
    *deck = NULL;
    *deck = malloc(sizeof(t_deck));
    if (!(*deck))
        return;
    (*deck)->total_cards = 0;
    (*deck)->cards = NULL;
    (*deck)->is_shown = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1];

    for(int number = -1; number < 13; number++)
    {
        if (number == 0)
            continue;
        for(int cantidad = 0; cantidad < NORMAL; cantidad++)
        {
            append_card_deck(deck, number);
        }
    }

    for(int iter = 0; iter < CERO; iter++)
    {
        append_card_deck(deck, 0);
    }

    for(int iter = 0; iter < M_2_MAX; iter++)
    {
        append_card_deck(deck, -2);
    }
}

int get_random_card(t_deck **deck)
{
    int num;

    srand(time(NULL));
    num = (*deck)->cards[rand() % (*deck)->total_cards];
    remove_card_deck(deck, num);
    return (num);
}

void create_player_deck(t_deck **table_deck, t_deck **player_deck)
{
    int iter;

    *player_deck = NULL;
    *player_deck = malloc(sizeof(t_deck));
    if (!(*player_deck))
        return;
    (*player_deck)->total_cards = 0;
    (*player_deck)->cards = NULL;
    (*player_deck)->is_shown = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    
    (*player_deck)->cards = malloc(sizeof(int) * 12);
    if (!(*player_deck)->cards)
    {
        free(*player_deck);
        *player_deck = NULL;
        return ;
    }
    iter = 0;
    while(iter < 12)
    {
        (*player_deck)->cards[iter] = get_random_card(table_deck);
        iter++;
    }
    (*player_deck)->total_cards = 12;
}   

void show_player_deck(t_deck *deck)
{
    int row;
    int col;
    int iter;
    int hided1;
    int hided2;

    iter = 0;
    row = 0;
    hided1 = rand() % 12;
    hided2 = (rand() % 12);
    if (hided1 == hided2)
        hided2 = rand() % 12;
    deck->is_shown[hided1] = 1;
    deck->is_shown[hided2] = 1;
    while(row < 3 && iter < deck->total_cards)
    {
        col = 0;
        while(col < 4 && iter < deck->total_cards)
        {
            if (!deck->is_shown[iter])
                printf("X\t");
            else
                printf("%i\t", deck->cards[iter]);
            iter++;
            col++;
        }
        printf("\n");
        row++;
    }
}
/*
    Crear una t_deck para la baraja del centro 
    y tambien un t_deck para cada jugador y actualizamos su valor en ¡
    base a las que quitamos del centro.
*/
int main(void)
{
    t_deck *central_deck;
    t_deck *player_one;

    init_deck(&central_deck);

    create_player_deck(&central_deck, &player_one);

    show_player_deck(player_one);


    // show_deck(central_deck);
    // show_deck(player_one);
    // printf("num_cards:%i\n", player_one->cards[0]);
    // free(central_deck);
    return 0;
}