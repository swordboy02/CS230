#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms.h"   //imports rooms.h from the same directory
#include "items.h"   //imports items.h from the same directory


struct Room* mainBoard;   //this struct will be used for the main game
struct Room* answer;      //this struct will store the answer(random)
int curRoom;

struct Room* boardGenerator(){	  //this method generates the playing board, randomizing rooms, items and characters
  int numRooms = 9;
  int numItems = 7;
  curRoom = rand()%7;
 
  struct Room* roomData = (struct Room*)malloc(sizeof(struct Room) * numRooms);    // this line of code helps use allocate memory for the array
  char* avatars[] = {"Jake","Amy","Charles","Terry","Rosa","Scully"};
  char* items[] = {"Knife","Bat","Stick","Club","Gun","Rope","Hammer"};
  char* roomType[] = {"Kitchen","Hall","Ballroom","Cellar","Billiard Room","Library","Lounge","Study","Conservatory"};
 
  for(int i=0;i<9;i++){    //for loop to point each room in the direction we need to as per a 3x3 grid
    
    roomData[i].name = roomType[i];

    if(i>2){  						//dont assign NORTH rooms to the first three rooms
      roomData[i].North = &roomData[i-3];
      }
    if(i%3 != 0){					//dont assign WEST rooms to the left(0,3,6) rooms
      roomData[i].West = &roomData[i-1];
      }
    if(i<6){						//dont assign SOUTH rooms to the last three rooms
      roomData[i].South = &roomData[i+3];
      }
    if( i!=2 || i!=5 || i!=8 ){				//dont assing EAST rooms to the right(2,5,8) rooms
      roomData[i].East = &roomData[i+1];
      }
    }

  for(int i=0;i<6;i++){
    roomData[i].character = avatars[i];
  }

  for(int i=0;i<7;i++){
    roomData[i].itemEnt = items[i];
  }
    answer = &roomData[rand()%7];			//the answer is in a random room

    return roomData;
}

void instructions(){	//this is the first thing the player sees when starting the game

  printf("WELCOME TO CLUE\nPLEASE READ THE INSTRUCTIONS BELOW\n\n");
  printf("YOU ARE A DETECTIVE AND YOUR AIM IS TO FIND THE MURDERER, THE WEAPON AND THE ROOM WHERE THE MURDER HAPPENED\n\n");
  printf("LETS BEGIN YOUR ADVENTURE........START BY LOOKING WHERE YOU ARE\n\n");
}

void commands(){	//this method is mostly the main place the game takes place, with user entered words being used to affect the game
  char choice[10];
  char dir[10];

  printf("Choose Your Action:\n1)HELP\n2)LIST\n3)LOOK\n4)GO\n5)TAKE\n6)DROP\n7)INVENTORY\n8)CLUE\n\n");
  scanf("%[^\n]%*c",choice);
  printf("\n");

  switch(choice[0]){		//we use the first letter of the choice entered by the users
    case 'H':
      commands();
      break;
    case 'L':				
      if(choice[1]=='I'){	//as 'L' has two, we use an if-else to differ them
        printf("ROOM NAMES: ");
        for(int i=0;i<9;i++){
            printf("%s ",mainBoard[i].name);
          }
        printf("\n");
        printf("CHARACTERS: ");
        for(int i=0;i<6;i++){
            printf("%s ",mainBoard[i].character);
          }
        printf("\n");
        printf("ITEMS: ");
        for(int i=0;i<7;i++){
            printf("%s ",mainBoard[i].itemEnt);
          }
        printf("\n\n");
        }
      else if(choice[1] == 'O'){
          printf("You are in the %s\n",mainBoard[curRoom].name);
          printf("You see %s\n",mainBoard[curRoom].character);
          printf("You also find a %s there\n\n", mainBoard[curRoom].itemEnt);
          printf("The room to the North is the %s\n",mainBoard[curRoom-3].name);
          printf("The room to the South is the %s\n",mainBoard[curRoom+3].name);
          printf("The room to the East is the %s\n",mainBoard[curRoom-1].name);
          printf("The room to the West is the %s\n",mainBoard[curRoom+1].name);
        }
      else{
        printf("HMM I AM CONFUSED CAN YOU TRY AGAIN\n\n");
        }
      commands();
      break;
    case 'G':
      printf("WHICH WAY DO YOU WANT TO GO?\nNORTH\nSOUTH\nEAST\nWEST\n");
      scanf("%[^\n]%*c",dir);
      switch(dir[0]){
        case 'N':
          printf("Travelling North....");
          curRoom -= 3;					//used a 3x3 grid as reference
          break;
        case 'S':
          printf("Travelling South....");
          curRoom += 3;					//used a 3x3 grid as reference
          break;
        case 'E':
          printf("Travelling East....");
          curRoom -= 1;					//used a 3x3 grid as reference
          break;
        case 'W':
          printf("Travelling West....");
          curRoom += 1;					//used a 3x3 grid as reference
          break; 
      }
      commands();
      break;
    case 'T':
      commands();
      break;
    case 'D':
      commands();
      break;
    case 'I':
      commands();
      break;
    case 'C':
      commands();
      break;
    case 'E':
      exit(1);
      break;
    default:
      printf("HMM I AM CONFUSED CAN YOU TRY AGAIN\n\n");
      commands();					//if something not on the menu is entered, give the commands again
  }
}

int main(){     //the main function where the method functions are called
  mainBoard = boardGenerator();
  instructions();
  commands();
  return 0; 
}
