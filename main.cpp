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
 for (int i = 0; i < 2; i++) {
  for (int j = 0; j < 7; j++) {
   hand.push_back(deck.back());
   deck.pop_back();
  }
  players.push_back(Player(hand));
  hand.clear();
 }
 centerPile.push_back(deck.back());
 deck.pop_back();
 if (centerPile.at(0).getColor() == 'N') {
  int r = rand() % 3;
  if (r == 0) 
   centerPile.at(0).changeColor('Y');
  else if (r == 1) 
   centerPile.at(0).changeColor('G');
  else if (r == 2) 
   centerPile.at(0).changeColor('B');
  else if (r == 3) 
   centerPile.at(0).changeColor('R');
 }

 string event;
 string choice;
 vector<string> tokens;
 tokens.clear();
 do {
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
   tokens.clear();
   int jumpInCounter = players.size();
   int tickFoward = 0;
   while ((event == "none" || event =="cancel") && jumpInCounter > 0) {
    jumpInCounter = players.size();
    for (int i = turns; i < turns + players.size();i++) {
     int canJumpIn = NULL;
     for (int j = 0; j < players.at(i % players.size()).getCards().size();j++) {
      if (players.at(i % players.size()).getCards().at(j).getType() == centerPile.back().getType() && players.at(i % players.size()).getCards().at(j).getColor() == centerPile.back().getColor()) {
       canJumpIn = j;
      }
     }
     if (canJumpIn == NULL) {
      canJumpIn = -1;
      jumpInCounter--;
     }
     if (canJumpIn > -1) {
      cout << "your cards: ";
      for (Card c: players.at(i % players.size()).getCards())
       cout << c.getType() << c.getColor() << ", ";
      cout << endl;
 
      cout << "cards in the center pile: ";
      for (Card c: centerPile) {
       cout << c.getType();
       cout << c.getColor() << ", ";
      }

      cout << "player " << i % players.size() << " can jump in with a " << players.at(i % players.size()).getCards().at(canJumpIn).getType() << players.at(i % players.size()).getCards().at(canJumpIn).getColor() << " card \nwould you like to jump in?(yes): ";
   
      getline(cin, choice);
      stringstream check1(choice);
      string intmd;
     
      while(getline(check1, intmd, ' ')) {
       tokens.push_back(intmd);
      }
      if (tokens.at(0) == "yes") {
       cout << "the card will be played \n";
       centerPile.push_back(players.at(i % players.size()).getCards().at(canJumpIn));
       players.at(i % players.size()).dealCard(canJumpIn);
       tickFoward = i;
      }
      else {
       cout << "you chose to let the oppurtunity pass \n";
       jumpInCounter--;
      }
      tokens.clear();
     }
    }
   }
   turns += tickFoward;

   while (event == "+4" || event == "+2") {
    int prev = 0;
    if (isReversed) {
     prev = 1;
    }
    else {
     prev = -1;
    }

    int playerHasCard;
    for (int i = 0; i < players.at(turns % players.size()).getCards().size();i++)
     if (players.at(turns % players.size()).getCards().at(i).getType() == centerPile.back().getType())
      playerHasCard = i;
    if (playerHasCard == NULL)
     playerHasCard = -1; 
      
    bool prevPlayerCouldvePlayedAnotherCard;
    for (Card c:players.at(turns + prev % players.size()).getCards())
     if(c.getColor() == centerPile.at(centerPile.size() - 1).getColor() || c.getType() == centerPile.at(centerPile.size() - 1).getType() || c.getType() == '*')
      prevPlayerCouldvePlayedAnotherCard = true;
    if (prevPlayerCouldvePlayedAnotherCard == NULL)
     prevPlayerCouldvePlayedAnotherCard = false;

    cout << "your cards: ";
    for (Card c: players.at(turns % players.size()).getCards())
     cout << c.getType() << c.getColor() << ", ";
    cout << endl;

    cout << "cards in the center pile: ";
    for (Card c: centerPile) {
     cout << c.getType();
     cout << c.getColor() << ", ";
    }

    cout << "player " << turns % players.size() << " will have to draw " << cardsToDraw << " cards \nwould you like to challenge this move?(yes) or would you like to deal your +4 card?(deal): ";
   
    getline(cin, choice);
    stringstream check1(choice);
    string intmd;
    
    while(getline(check1, intmd, ' ')) {
     tokens.push_back(intmd);
    }
    if (tokens.at(0) == "yes" && event == "+4" && prevPlayerCouldvePlayedAnotherCard) {
     cout << "your challenge was correct, previous player must now draw your cards to draw +2, and it is your turn. But, the card in the center does not get withdrawn\n";
     playersTurn = false;
     turns -= prev;
     cardsToDraw += 2;
    }
    else if (tokens.at(0) == "yes" && event == "+4" && !(prevPlayerCouldvePlayedAnotherCard)) {
     cout << "your challenge was incorrect, you must now draw your cards to draw +2, and it is not your turn\n";
     cardsToDraw += 2;
     event = "none";
    }
    else if (tokens.at(0) == "yes" && event != "+4") {
     cout << "you can only do that to +4 cards, continuing...\n";
     event = "none";
    }
    else if (tokens.at(0) == "deal" && playerHasCard > -1) {
     cout << "you will deal the matching card you have\n";
     centerPile.push_back(players.at(turns % players.size()).getCards().at(playerHasCard));
     players.at(turns % players.size()).dealCard(playerHasCard);
     if (event == "+4") 
      cardsToDraw += 4;
     else if (event == "+2")
      cardsToDraw += 2;
     turns -= prev;
    }
    else if (tokens.at(0) == "deal" && playerHasCard == -1) {
     cout << "you have no matching cards in your deck, continuing...\n";
     event = "none";
    }
    else {
     cout << "you have chosen to accept the move and do nothing of note\n";
     event = "none";
    }
   }
   tokens.clear();
   for (int i = 0; i < cardsToDraw;i++) {
    players.at(turns % players.size()).drawCard(deck.back());
    deck.pop_back();
   }
   cout << "player " << turns % players.size() << " has picked up " << cardsToDraw << " cards \n";
   cardsToDraw = 0;
   event = "none";
   choice = "";
   valid = false;
   do {
    cout << "player " << turns % players.size() << " turn: ";
    getline(cin, choice);
    vector<string> tokens;
    stringstream check1(choice);
    string intmd;
    
    while(getline(check1, intmd, ' ')) {
     tokens.push_back(intmd);
    }
    for (string s: tokens)
     cout << s << endl;
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
      cout << c.getColor() << ", ";
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
         players.at(turns % players.size()).getCards().at(toke).changeColor(tokens.at(2)[0]);
	 break;
       case '@': 
         players.at(turns % players.size()).getCards().at(toke).changeColor(tokens.at(2)[0]);
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
      valid = false;
     }
   }
   else if (tokens.at(0) == "draw") {
    players.at(turns % players.size()).drawCard(deck.back());
    deck.pop_back();
    valid = false;
   }
   else {
    cout << "try again \n";
    valid = false;
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
  if (playerHasWon) {}
  else if (isReversed) {
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
 } while (!playerHasWon);
 cout << "player " << turns % players.size() << " Has won the game\n";
 return 0;
}
