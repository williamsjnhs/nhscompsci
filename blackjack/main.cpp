#include <algorithm>
#include <iostream>
#include <vector> 
#include <random>
#include <chrono> 

/*
 *  The main function below runs a game of blackjack which
 *  calls a "play" function.  Make a copy of this code and 
 *  write your function here at the top.  If your code 
 *  works, you should see an output that tells you if 
 *  you've won or lost.  
 */ 

bool play(std::vector <char> hand, char dealer_card, std::vector <char> other_cards) {
  // YOUR CODE HERE 
  // YOUR CODE HERE 
  // YOUR CODE HERE 
  return false; 
}

int value(std::vector <char> hand) {
  int value = 0;
  for (char card: hand) {
    switch (card) {
      case '2': value += 2; break; 
      case '3': value += 3; break; 
      case '4': value += 4; break; 
      case '5': value += 5; break; 
      case '6': value += 6; break; 
      case '7': value += 7; break; 
      case '8': value += 8; break; 
      case '9': value += 9; break; 
      case 'T': value += 10; break; 
      case 'J': value += 10; break; 
      case 'Q': value += 10; break; 
      case 'K': value += 10; break; 
      case 'A': value += 11; break; 
    }
  }
  // Handle the aces 
  if (value > 21) {
    for (char card: hand) {
      if (card=='A' && value > 21) {
        value -= 10; 
      }
    }
  }
  return value; 
}

float play_blackjack(int number_of_decks) {
  // Returns the result: player wins -> 1
  //                     player loss -> -1
  //                     draw -> 0
  //                     player blackjack -> 1.5

  // Create and combine number_of_decks decks
  std::vector <char> deck = {};  
  for (int i=0; i<number_of_decks; i++) {
    for (int c=2; c<10; c++) {
      deck.push_back( 48 + c);  // ASCII offset 
    }
    for (int j=0; j<4; j++) { deck.push_back('T'); }
    for (int j=0; j<4; j++) { deck.push_back('J'); }
    for (int j=0; j<4; j++) { deck.push_back('Q'); }
    for (int j=0; j<4; j++) { deck.push_back('K'); }
    for (int j=0; j<4; j++) { deck.push_back('A'); }
  }

  // Shuffle the deck 
  auto rng = std::default_random_engine {};
  rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
  std::shuffle(std::begin(deck), std::end(deck), rng);

  // Deal two cards to player 
  std::vector <char> player_hand = {};
  player_hand.push_back( deck[0] );   
  deck.erase(deck.begin()); 
  player_hand.push_back( deck[0] );   
  deck.erase(deck.begin()); 

  // Deal to dealer 
  std::vector <char> dealer_hand = {}; 
  dealer_hand.push_back( deck[0] ); 
  deck.erase(deck.begin()); 
  dealer_hand.push_back( deck[0] ); 
  deck.erase(deck.begin()); 

  std::vector <char> other_cards = {};  // For now, an empty vector 

  while ( true ) {
    if ( play( player_hand, dealer_hand[1], other_cards) ) {
      player_hand.push_back( deck[0] ); 
      deck.erase(deck.begin()); 
    } else { 
      break; 
    }
  }

  float result = 0.0; 

  // If player busts, 
  if ( value(player_hand)>21 ) {
    result = -1.0; 
  }
  // If player and dealer both have blackjack, it is a tie. 
  if ( value(player_hand)==21 && player_hand.size()==2 && value(dealer_hand)==21 ) {
    result = 0.0; 
  } 
  // If player has blackjack and dealer doesn't, player wins 1.5 to 1
  if ( value(player_hand)==21 && player_hand.size()==2 && value(dealer_hand)!=21 ) {
    result = 1.5; 
  }
  // If dealer has blackjack and player doesn't, player loses 
  if ( value(dealer_hand)==21 && !(player_hand.size()==2 && value(player_hand)==21) ) {
    result = -1.0; 
  }
  if ( result==0.0 and !(value(player_hand)==21 && player_hand.size()==2 && value(dealer_hand)==21) ) {
    // Dealer must take a card until the total is 17 or more,
    // at which point they must stand. 
    while ( value(dealer_hand) < 17 ) {   // Note lack of soft-17
      dealer_hand.push_back( deck[0] );
      deck.erase(deck.begin()); 
    }
    if ( value(player_hand) == value(dealer_hand) ) {
      result = 0.0; 
    }
    if ( value(player_hand) > value(dealer_hand) ) {
      result = 1.0; 
    }
    if ( value(player_hand) < value(dealer_hand) ) {
      result = -1.0; 
    }
  }
  
  // Display results 
  std::cout << "Player: "; 
  for (char card : player_hand) { std::cout << card << ' '; } std::cout << '\n'; 
  std::cout << "Dealer: "; 
  for (char card : dealer_hand) { std::cout << card << ' '; } std::cout << '\n'; 
  std::cout << "  result: " << result << '\n'; 

  return result; 
}

int main() {
  const int number_of_games = 20; 
  const int number_of_decks = 4;
  
  for (int game=0; game<number_of_games; game++) {
    std::cout << play_blackjack(number_of_decks) << '\n'; 
  }

  return 0; 
}