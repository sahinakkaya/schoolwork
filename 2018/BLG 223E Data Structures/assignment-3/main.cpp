/*
 * main.cpp
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */

#include <iostream>
#include <fstream>

typedef int CardNumber;

using namespace std;

class Node {
   public:
    CardNumber data;
    Node* next;
};

class Stack {
    Node* head;
    int nodecount;

   public:
    void create();
    bool is_empty();
    int get_nodecount();
    void push(CardNumber);
    CardNumber pop();
    CardNumber peek();
    void close();
};
/*
  /brief initialize the stack
*/ 
void Stack::create() {
    head = NULL;
    nodecount = 0;
};

/*
  /return true if stack is empty, false otherwise
*/
bool Stack::is_empty() {
    return !head;
};

/*
  /return number of nodes in the stack
*/
int Stack::get_nodecount() {
    return nodecount;
};

/*
  /brief add given data to the stack as a top element
  /param data a CardNumber type of argument
*/
void Stack::push(CardNumber data) {
    Node* newnode = new Node;
    newnode->data = data;
    newnode->next = head;
    head = newnode;
    nodecount++;
};

/*
  /brief remove the top element from stack and return it's data
  /return data of the top element
*/
CardNumber Stack::pop() {
    Node* node = head;
    CardNumber data = node->data;
    head = head->next;
    delete node;
    nodecount--;
    return data;
};

/*
  /brief return the top element's data without removing it
  /return top element's data
*/
CardNumber Stack::peek() {
    return head->data;
};

/*
  /brief remove all elements in the stack
*/
void Stack::close() {
    Node* d;
    while(head){
        d = head;
        head = head->next;
        delete d;
        nodecount--;
    }   
};
/*
  /brief read given file and initialize the stacks with the data from file.
  /param filename a character pointer that keeps the name of the file
  /param first_players_deck--------\ 
  /param second_players_deck -----> reference to a Stack
  /param table_deck----------------/
  /return false if file cannot be opened, true otherwise
*/
bool read_file_and_initialize_stacks(const char* filename, Stack& first_players_deck, Stack& second_players_deck, Stack& table_deck)
{
    // Initialize stacks.
    first_players_deck.create();
    second_players_deck.create();
    table_deck.create();

    // Open file...
    ifstream file(filename);
    
    if(file.fail()){ // If cannot opened,
        cerr << "Cannot open file '" << filename << "'. No such file." << endl;
        return false;
    }
    
    int tableDeckCount, playerDeckCount;
    file >> tableDeckCount >> playerDeckCount;

    // Prepare table deck
    CardNumber number;
    while(tableDeckCount--){
        file >> number;
        table_deck.push(number);
    }
    // Prepare first player's deck
    while(playerDeckCount--){
        file >> number;
        first_players_deck.push(number);
    }
    // Prepare second player's deck
    playerDeckCount = first_players_deck.get_nodecount();
    while(playerDeckCount--){
        file >> number;
        second_players_deck.push(number);
    }

    file.close();
    
    return true;
}



int main(int argc, char* argv[])
{
    if(argc!=2){
        cerr << "You entered " << argc << " argument" << (argc == 1 ? "" : "s") << "." << endl;
        cerr << "Please enter exactly 2 arguments." << endl;
        return EXIT_FAILURE;
    }
    
    // ************************************************************************** //
    // Declare all variables and initialize them for the game.
    
    Stack player_decks[2];
    Stack table_deck;
    
    Stack* first_p_deck = &player_decks[0];
    Stack* second_p_deck = &player_decks[1];

    if(!read_file_and_initialize_stacks(argv[1], *first_p_deck, *second_p_deck, table_deck)) return EXIT_FAILURE;
    
    Stack* current_players_deck; // s is for ownership (like current player's deck.), not for making the "player" plural
    Stack* other_players_deck; 

    int turn = 0, cards_thrown_away = 0;
    bool end = table_deck.is_empty() || first_p_deck->is_empty();

    // ************************************************************************** //

    while(!end){ // While the game is not ended...

        // Update the current and other players based on turn.
        current_players_deck = &player_decks[turn % 2];
        other_players_deck = &player_decks[(turn + 1) % 2]; 

        // Take a card from table deck.
        CardNumber n_cards_to_taken_or_given = table_deck.pop(); 

        if (n_cards_to_taken_or_given > 0){ // If the number is bigger than 0

            // current player will take n cards from other player.
            while (!end && n_cards_to_taken_or_given--){ // While the game is not ended and there are cards to taken...

                CardNumber card_to_be_taken = other_players_deck->pop(); // Take a card from other player
                CardNumber top_card = current_players_deck->peek();      // Look at the top card of the current player

                if(card_to_be_taken > top_card)                   // If top card is smaller,
                    current_players_deck->push(card_to_be_taken); // accept the card that is coming from other player
                else
                    cards_thrown_away++;                          // otherwise, throw it to the bin.
                    
                end = other_players_deck->is_empty();  // Check if other player is out of cards.
            }
        }else{

            // Current player will give n cards to other player.
            while(!end && n_cards_to_taken_or_given++){ // While the game is not ended and there are cards to given...

                CardNumber card_to_be_given = current_players_deck->pop(); // Take a card from the current player
                CardNumber top_card = other_players_deck->peek();          // Look at the top card of other player

                if(card_to_be_given > top_card)                 // If top card is smaller,
                    other_players_deck->push(card_to_be_given); // give the card to other player
                else 
                    cards_thrown_away++;                        // otherwise, throw it to the bin.
                    
                end = current_players_deck->is_empty(); // Check if current player is out of cards.
            }
        }
        
        // Update turn and check if any deck is empty.
        turn++;
        end = end || table_deck.is_empty();
    }

    /* Print the result and tidy out the cards for the next game :)
    (return back dynamically allocated memory to the system) */
    cout << cards_thrown_away << endl;
    first_p_deck->close();
    second_p_deck->close();
    table_deck.close();

    return EXIT_SUCCESS;
}
