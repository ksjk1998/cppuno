// the rules were based off of this link https://en.wikipedia.org/wiki/Uno_(card_game) all house rules are planned to make it in the final version
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <ctime> 
#include <bits/stdc++.h>

using namespace std;

class Card {

public:

 Card(char t, char c) :
  type(t),
  color(c)
  
  {}
  
 char getType() {
  return type;
 }
 char getColor() {
  return color;
 }
 char getBoth() {
  return type, color;
 }
 void changeColor(char c) {
  color = c;
 }
 char type;
 char color;
};

class Player {
public:
 Player(vector<Card> c) :
  cards(c)

  {}

  vector<Card> getCards() {
   return cards;
  }
  void dealCard(int index) {
   cards.erase(cards.begin() + index);
  }
  void drawCard(Card c) {
   cards.push_back(c);
  }

 vector<Card> cards;
};


class tradAi: public Player {
  /* The ai should be good enough to strip the population of  *
   * overly zealous drawers by beating them, but not too good *
   * that the ML ai never beats it after getting over that.   *
   * it may also be used for testing until the ML ai is made. */
  int getValue(Card& card) {
    int cType = card.getType();
    if (cType-48<9&&cType>47) return cType-47;
    else switch (int(cType)) {
      case '/':
      case '%':
	return 10;
	break;
      case '&':
	return 20;
	break;
      case '*':
	return 30;
	break;
      case '@':
	return 40;
      }
  }
  int bestCard(vector<Card> cards) {
    int best;
    char highestValue;
    for (int i = 0;i < cards.size();i++) {
      if (getValue(cards[i])>highestValue) best=i, highestValue=getValue(cards[i]);
    }
    return best;
  }
  int cSize(vector<Card> cards) {
    int out = 0;
    for (Card x : cards) out++;
    return out;
  }
  int totalValue(vector<Card> cards) {
    int value;
    for (Card x : cards) {
      value+=getValue(x);
    }
    return value;
  }
  int deckValue(vector<Card> centerPile, vector<Card> hand) {
    return 960-(totalValue(hand)+totalValue(centerPile)); 
  }
  vector<int> handSizes(vector<Player> players) {
    vector<int> sizes;
    for (Player& x : players) sizes.push_back(cSize(x.cards));
    return sizes;
  }
  vector<string> move() {
    
  }
};
// /=10 %=10 &=20 *=30 @=40 85*2=10+80*2=170 170*4=340*2=680 4*30=120 4*40=160 680+120=800 800+160=960
vector<Card> deck{Card('0', 'R'), Card('1', 'R'), Card('2', 'R'), Card('3', 'R'), Card('4', 'R'), Card('5', 'R'), Card('6', 'R'), Card('7', 'R'), Card('8', 'R'), Card('9', 'R'), Card('/', 'R'), Card('%', 'R'), Card('&', 'R'), Card('0', 'Y'), Card('1', 'Y'), Card('2', 'Y'), Card('3', 'Y'), Card('4', 'Y'), Card('5', 'Y'), Card('6', 'Y'), Card('7', 'Y'), Card('8', 'Y'), Card('9', 'Y'), Card('/', 'Y'), Card('%', 'Y'), Card('&', 'Y'), Card('0', 'G'), Card('1', 'G'), Card('2', 'G'), Card('3', 'G'), Card('4', 'G'), Card('5', 'G'), Card('6', 'G'), Card('7', 'G'), Card('8', 'G'), Card('9', 'G'), Card('/', 'G'), Card('%', 'G'), Card('&', 'G'), Card('0', 'B'), Card('1', 'B'), Card('2', 'B'), Card('3', 'B'), Card('4', 'B'), Card('5', 'B'), Card('6', 'B'), Card('7', 'B'), Card('8', 'B'), Card('9', 'B'), Card('/', 'B'), Card('%', 'B'), Card('&', 'B'), Card('1', 'R'), Card('2', 'R'), Card('3', 'R'), Card('4', 'R'), Card('5', 'R'), Card('6', 'R'), Card('7', 'R'), Card('8', 'R'), Card('9', 'R'), Card('/', 'R'), Card('%', 'R'), Card('&', 'R'), Card('1', 'Y'), Card('2', 'Y'), Card('3', 'Y'), Card('4', 'Y'), Card('5', 'Y'), Card('6', 'Y'), Card('7', 'Y'), Card('8', 'Y'), Card('9', 'Y'), Card('/', 'Y'), Card('%', 'Y'), Card('&', 'Y'), Card('1', 'G'), Card('2', 'G'), Card('3', 'G'), Card('4', 'G'), Card('5', 'G'), Card('6', 'G'), Card('7', 'G'), Card('8', 'G'), Card('9', 'G'), Card('/', 'G'), Card('%', 'G'), Card('&', 'G'), Card('1', 'B'), Card('2', 'B'), Card('3', 'B'), Card('4', 'B'), Card('5', 'B'), Card('6', 'B'), Card('7', 'B'), Card('8', 'B'), Card('9', 'B'), Card('/', 'B'), Card('%', 'B'), Card('&', 'B'), Card('*', 'N'), Card('*', 'N'), Card('*', 'N'), Card('*', 'N'), Card('@', 'N'), Card('@', 'N'), Card('@', 'N'), Card('@', 'N')};


vector<Card> centerPile;
vector<Player> players;
bool playerHasWon = false;
bool valid;
bool playersTurn = true;
bool isReversed =false;
int turns = 0;
int cardsToDraw = 0;
string line;
string event;

int main() {
 srand (time(NULL));
 random_shuffle(deck.begin(), deck.end());
 
 vector<Card> hand;
 for (int i = 0; i < 10; i++) {
  for (int j = 0; j < 7; j++) {
   hand.push_back(deck.back());
   deck.pop_back();
  }
  players.push_back(Player(hand));
  hand.clear();
 }
 centerPile.push_back(deck.back());
 deck.pop_back();

 string event;
 string choice;
 while (!playerHasWon) {
   playersTurn = true;
   if (event == "+4") {
    cardsToDraw += 4;
    playersTurn = false;
   }
   else if (event == "+2") {
    cardsToDraw += 2;
    playersTurn = false;
   }
   else if (event == "cancel") {
    playersTurn = false;
   }
   // option to 'jump in' must check all players to see if they have at least one card that perfectly matches the top card in the center pile
   // then each player must have the option to place that card in the center pile regardless if it is the players turn
   
   // option to challenge opponent (+4) and/or deal the same card to the center pile, stacking the number of cards to draw
   
   for (int i = 0; i < cardsToDraw;i++) {
    players.at(turns % players.size()).drawCard(deck.back());
    deck.pop_back();
   }
   cardsToDraw = 0;
   event = "none";
   choice = "";
   valid == false;
   do {
    cout << "player " << turns % players.size() << " turn: ";
    getline(cin, choice);
    vector<string> tokens;
    stringstream check1(choice);
    string intmd;
    
    while(getline(check1, intmd, ' ')) {
     tokens.push_back(intmd);
    }
    if (tokens.at(0) == "table") {

     cout << "your cards: ";

     for (Card c: players.at(turns % players.size()).getCards())
      cout << c.getType() << c.getColor() << ", ";
     cout << endl;

     for (int i = 0; i < players.size();i++) {
      cout << "player " << (i + 1) << " has " << players.at(i).getCards().size() << " cards \n";
     }

     cout << "cards in the center pile: ";
     for (Card c: centerPile) {
      cout << c.getType();
      cout << c.getColor() << " ";
     }

     cout << endl;

      cout << "the deck has " <<  deck.size() << " cards in it \n";
    }
    else if (tokens.at(0) == "deal") {
     try {
       int toke = stoi(tokens.at(1));
       if (players.at(turns % players.size()).getCards().at(toke).getType() == centerPile.back().getType() || players.at(turns % players.size()).getCards().at(toke).getColor() == centerPile.back().getColor() || players.at(turns % players.size()).getCards().at(toke).getColor() == 'N') {
       valid = true;
       switch (int(players.at(turns % players.size()).getCards().at(toke).getType())) {
       case '/':
	 event = "cancel";
	 break;
       case '%':
	 event = "reverse";
	 break;
       case  '&':
	 event = "+2";
	 break;
       case '*':
	 // change color based off of token 2
	 break;
       case '@':
         // change color based off of token 2
	 event = "+4";
       }

       centerPile.push_back(players.at(turns % players.size()).getCards().at(toke));
       players.at(turns % players.size()).dealCard(toke);
       }

      else {
       valid = false;
      }
     }
     catch (...) {
      cout << "incorrect token(s) \n";
      valid == false;
     }
   }
   else if (tokens.at(0) == "draw") {
    players.at(turns % players.size()).drawCard(deck.back());
    deck.pop_back();
    valid = false;
   }
   else {
    cout << "try again \n";
    valid == false;
   }

   if (players.at(turns % players.size()).getCards().size() == 0) {
    playerHasWon = true;
   }
  } while (!valid && playersTurn);

  if (deck.size() == 0) {
   deck = centerPile;
   random_shuffle(deck.begin(), deck.end());
   centerPile.clear();
  }
  if (isReversed) {
   turns--;
  }
  else if (isReversed && players.size() == 2) {
   event = "cancel";
   turns++;
   isReversed = false;
  }
  else {
   turns++;
  }
 }
 return 0;
}//
