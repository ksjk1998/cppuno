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

vector<Card> deck{Card('0', 'R'), Card('1', 'R'), Card('2', 'R'), Card('3', 'R'), Card('4', 'R'), Card('5', 'R'), Card('6', 'R'), Card('7', 'R'), Card('8', 'R'), Card('9', 'R'), Card('/', 'R'), Card('%', 'R'), Card('&', 'R'), Card('0', 'Y'), Card('1', 'Y'), Card('2', 'Y'), Card('3', 'Y'), Card('4', 'Y'), Card('5', 'Y'), Card('6', 'Y'), Card('7', 'Y'), Card('8', 'Y'), Card('9', 'Y'), Card('/', 'Y'), Card('%', 'Y'), Card('&', 'Y'), Card('0', 'G'), Card('1', 'G'), Card('2', 'G'), Card('3', 'G'), Card('4', 'G'), Card('5', 'G'), Card('6', 'G'), Card('7', 'G'), Card('8', 'G'), Card('9', 'G'), Card('/', 'G'), Card('%', 'G'), Card('&', 'G'), Card('0', 'B'), Card('1', 'B'), Card('2', 'B'), Card('3', 'B'), Card('4', 'B'), Card('5', 'B'), Card('6', 'B'), Card('7', 'B'), Card('8', 'B'), Card('9', 'B'), Card('/', 'B'), Card('%', 'B'), Card('&', 'B'), Card('1', 'R'), Card('2', 'R'), Card('3', 'R'), Card('4', 'R'), Card('5', 'R'), Card('6', 'R'), Card('7', 'R'), Card('8', 'R'), Card('9', 'R'), Card('/', 'R'), Card('%', 'R'), Card('&', 'R'), Card('1', 'Y'), Card('2', 'Y'), Card('3', 'Y'), Card('4', 'Y'), Card('5', 'Y'), Card('6', 'Y'), Card('7', 'Y'), Card('8', 'Y'), Card('9', 'Y'), Card('/', 'Y'), Card('%', 'Y'), Card('&', 'Y'), Card('1', 'G'), Card('2', 'G'), Card('3', 'G'), Card('4', 'G'), Card('5', 'G'), Card('6', 'G'), Card('7', 'G'), Card('8', 'G'), Card('9', 'G'), Card('/', 'G'), Card('%', 'G'), Card('&', 'G'), Card('1', 'B'), Card('2', 'B'), Card('3', 'B'), Card('4', 'B'), Card('5', 'B'), Card('6', 'B'), Card('7', 'B'), Card('8', 'B'), Card('9', 'B'), Card('/', 'B'), Card('%', 'B'), Card('&', 'B'), Card('*', 'N'), Card('*', 'N'), Card('*', 'N'), Card('*', 'N'), Card('@', 'N'), Card('@', 'N'), Card('@', 'N'), Card('@', 'N')};


vector<Card> centerPile;
vector<Player> players;
bool playerHasWon = false;
bool valid;
bool playersTurn = true;
bool isReversed =false;
int turns = 0;
int cardsToDraw = 0;


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
   // then cach player must have the option to place that card in the center pile regardless if it is the players turn
   
   // option to challenge opponent or deal the same card to the center pile, stacking the number of cards to draw
   
   for (int i = 0; i < cardsToDraw;i++) {
    players.at(turns % players.size()).drawCard(deck.back());
    deck.pop_back();
   }
   cardsToDraw = 0;
   event = "none";
   choice = "";
   valid == false;
   while (!valid && playersTurn) {
    cin >> choice;
    vector<string> tokens;
    stringstream check1(choice);
    string intermediate;
    while(getline(check1, intermediate, ' ')) {
        tokens.push_back(intermediate);
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
     for (Card c: centerPile)

      cout << c.getType() << endl;

     cout << endl;

      cout << "the deck has " <<  deck.size() << " cards in it \n";
    }
    else if (tokens.at(0) == "deal") {
     try {

       string toke = tokens.at(1);
       if (players.at(turns % players.size()).getCards().at((int)toke[0]).getType() == centerPile.back().getType() || players.at(turns % players.size()).getCards().at((int)toke[0]).getColor() == centerPile.back().getColor() || players.at(turns % players.size()).getCards().at((int)toke[0]).getColor() == 'N') {
       valid = true;
       switch (int(players.at(turns % players.size()).getCards().at((int)toke[0]).getType())) {
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
	 event = "wheel";
	 break;
       case '@':
	 event = "+4";
       }

       centerPile.push_back(players.at(turns % players.size()).getCards().at((int)toke[0]));
       players.at(turns % players.size()).dealCard((int)toke[0]);
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

   if (players.at(turns % players.size()).getCards().size() == 0) {
    playerHasWon = true;
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
  }

  if (deck.size() == 0) {

   deck = centerPile;
   random_shuffle(deck.begin(), deck.end());
   centerPile.clear();
  }
  if (isReversed) {
   turns--;
  }
  else {
   turns++;
  }
 }
 return 0;
}//
