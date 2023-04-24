/*
	Program 2: Wumpus (bats, arrow, and all arrays are dynamic)

	Course: CS 211, Fall 2022. Wed 12pm lab
  System: Replit
  Author: Lily Eap

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>		// for srand
//--------------------------------------------------------------------------------
void displayCave()
{
    printf( "\n"
			"       ______18______             \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}


//--------------------------------------------------------------------------------
void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
        	"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        	"2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        	"   fly you to some random room, which could be troublesome.  Then those bats go \n"
        	"   to a new room different from where they came from and from the other bats.   \n"
    		"3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        	"   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        	"    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        	"    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        	"    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        	"    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        	"    room, he snaps your neck and you die!                                       \n"
        	"                                                                                \n"
        	"Moves:                                                                          \n"
        	"On each move you can do the following, where input can be upper or lower-case:  \n"
        	"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        	"   then a room number.                                                          \n"
        	"2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        	"   you specify.  Your arrow ends up in the final room.                          \n"
        	"   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        	"   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        	"   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        	"   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        	"   continues doing this until it has traveled the designated number of rooms.   \n"
        	"   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        	"   automatically pick up the arrow if you go through a room with the arrow in   \n"
        	"   it.                                                                          \n"
        	"3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        	"4. Enter 'C' to cheat and display current board positions.                      \n"
        	"5. Enter 'D' to display this set of instructions.                               \n"
        	"6. Enter 'P' to print the maze room layout.                                     \n"
        	"7. Enter 'X' to exit the game.                                                  \n"
        	"                                                                                \n"
        	"Good luck!                                                                      \n"
        	" \n\n");
}//end displayInstructions()

/*sets room randomly and checks to make sure that the room is not already being used.*/
void setRooms(int occupiedRoomPtr[], int index){
  int object = rand() % 20 + 1;  
  int emptyRoom = 0;
  LOOP: do{
    for (int i = 0; i < index+1; i++){
      if (occupiedRoomPtr[i] == object){
        object = rand() % 20 + 1;
        goto LOOP;
      }
    }
    occupiedRoomPtr[index] = object;
    emptyRoom = 1;
  } while  (emptyRoom == 0);
}

/*checks if parity of the room that wumpus is in. if odd, wumpus moves. return 2 to let main() know to move wumpus. if even, wumpus kills player. return 1 to kill player*/
int wumpusRoom(int* occupiedRoomPtr){
  if(occupiedRoomPtr[1] % 2 == 1){
    printf( "You hear a slithering sound, as the Wumpus slips away. \n"
    "Whew, that was close! \n");
    return 2;
  } else{
    printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n" "It is over.\n");
    return 1;
  }
}

/*after the bats move the player to a new room, the bats will move to a 
random room themselves that is different from the player and other bats.*/
void newBatRoom(int* occupiedRoomPtr, int bats){
  int newRoom = rand() % 20 + 1;
  int emptyRoom = 0;
  LOOP: do{
    if (occupiedRoomPtr[bats] == newRoom || occupiedRoomPtr[0] == newRoom){
      newRoom = rand() % 20 + 1;
      goto LOOP;
    }
    occupiedRoomPtr[bats] = newRoom;
    emptyRoom = 1;
  } while  (emptyRoom == 0);
}

/*checks the current room to see if there is anything present. if so, then print notification. function returns 0 if the player is alive*/
int checkCurrentRoom(int* occupiedRoomPtr){
  //checking for wumpus
  if (occupiedRoomPtr[0] == occupiedRoomPtr[1]){
    return wumpusRoom(occupiedRoomPtr);

  //checking for pit
  } else if(occupiedRoomPtr[0] == occupiedRoomPtr[2] || occupiedRoomPtr[0] == occupiedRoomPtr[3]){
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n");
    printf("Exiting Program ... \n");
    exit(0);
    
  //arrow is in your room
  } else if (occupiedRoomPtr[0] == occupiedRoomPtr[6]){
    printf("Congratulations, you found the arrow and can once again shoot.	\n");
    //set arrow value to -1 b/c player has it now
    occupiedRoomPtr[6] = -1;
    
  //checking for bats
  } else if (occupiedRoomPtr[0] == occupiedRoomPtr[4] || occupiedRoomPtr[0] == occupiedRoomPtr[5]){
    int ogRoom = occupiedRoomPtr[0];
    int roomX = rand() % 20 + 1; // = 11
    printf("Woah... you're flying! \nYou've just been transported by bats to room %d. \n", roomX);
    occupiedRoomPtr[0] = roomX;
    //checks the current room after being transported by bats 
    checkCurrentRoom(occupiedRoomPtr);
    //bats fly to a new random room
    if (ogRoom == occupiedRoomPtr[4]){
      newBatRoom(occupiedRoomPtr, 4);
    } else {
      newBatRoom(occupiedRoomPtr, 5);
    }
    return 0;
    
  //nothing is present in the room
  } else {
    return 0;
  }
}

/*checks adjoining rooms to see if there is anything present. if so, then print notification */
void checkAdjacentRooms(int **totalRooms, int* occupiedRoomPtr){
  int room1 = totalRooms[occupiedRoomPtr[0]-1][0];
  int room2 = totalRooms[occupiedRoomPtr[0]-1][1];
  int room3 = totalRooms[occupiedRoomPtr[0]-1][2];

  if( room1 == occupiedRoomPtr[1] || room2 == occupiedRoomPtr[1] || room3 == occupiedRoomPtr[1]) {
      printf("You smell a stench. ");
  }
  
  if( room1 == occupiedRoomPtr[2] || room1 == occupiedRoomPtr[3] ||
      room2 == occupiedRoomPtr[2] || room2 == occupiedRoomPtr[3] ||
      room3 == occupiedRoomPtr[2] || room3 == occupiedRoomPtr[3]
    ) {
      printf("You feel a draft. ");
  }

  if( room1 == occupiedRoomPtr[3] || room1 == occupiedRoomPtr[4] ||
      room2 == occupiedRoomPtr[3] || room2 == occupiedRoomPtr[4] ||
      room3 == occupiedRoomPtr[3] || room3 == occupiedRoomPtr[4]
    ) {
      printf("You hear rustling of bat wings. ");
  }
}

//--------------------------------------------------------------------------------
int main(void) {
  // srand(time(0));
  srand(1);
  //sets random numbers into a dynamically allocated array of current game objects
  int* occupiedRoomPtr;
  int n = 7;
  occupiedRoomPtr = (int*)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++){
    setRooms(occupiedRoomPtr, i);
  }
  //dynamically allocate and set values of array that holds room numbers & their adjacent rooms
  int r = 20, c = 3;
  int** RoomPtr = (int**)malloc(r * sizeof(int*));
  for (int i = 0; i < r; i++){
    RoomPtr[i] = (int*)malloc(c * sizeof(int));
  }

  //room 1
  RoomPtr[0][0] = 2;
  RoomPtr[0][1] = 5;
  RoomPtr[0][2] = 8;

  //room 2
  RoomPtr[1][0] = 3;
  RoomPtr[1][1] = 10;
  RoomPtr[1][2] = 1;

  //room 3
  RoomPtr[2][0] = 2;
  RoomPtr[2][1] = 4;
  RoomPtr[2][2] = 12;

  //room 4
  RoomPtr[3][0] = 3;
  RoomPtr[3][1] = 5;
  RoomPtr[3][2] = 14;

  //room 5
  RoomPtr[4][0] = 1;
  RoomPtr[4][1] = 4;
  RoomPtr[4][2] = 6;

  //room 6
  RoomPtr[5][0] = 5;
  RoomPtr[5][1] = 7;
  RoomPtr[5][2] = 15;

  //room 7
  RoomPtr[6][0] = 6;
  RoomPtr[6][1] = 8;
  RoomPtr[6][2] = 17;

  //room 8
  RoomPtr[7][0] = 1;
  RoomPtr[7][1] = 7;
  RoomPtr[7][2] = 9;

  //room 9
  RoomPtr[8][0] = 8;
  RoomPtr[8][1] = 10;
  RoomPtr[8][2] = 18;

  //room 10
  RoomPtr[9][0] = 2;
  RoomPtr[9][1] = 9;
  RoomPtr[9][2] = 11;
  
  //room 11
  RoomPtr[10][0] = 10;
  RoomPtr[10][1] = 12;
  RoomPtr[10][2] = 19;

  //room 12
  RoomPtr[11][0] = 3;
  RoomPtr[11][1] = 11;
  RoomPtr[11][2] = 13;

  //room 13
  RoomPtr[12][0] = 12;
  RoomPtr[12][1] = 14;
  RoomPtr[12][2] = 20;

  //room 14
  RoomPtr[13][0] = 4;
  RoomPtr[13][1] = 13;
  RoomPtr[13][2] = 15;

  //room 15
  RoomPtr[14][0] = 6;
  RoomPtr[14][1] = 14;
  RoomPtr[14][2] = 16;

  //room 16
  RoomPtr[15][0] = 15;
  RoomPtr[15][1] = 17;
  RoomPtr[15][2] = 20;

  //room 17
  RoomPtr[16][0] = 7;
  RoomPtr[16][1] = 16;
  RoomPtr[16][2] = 18;

  //room 18
  RoomPtr[17][0] = 9;
  RoomPtr[17][1] = 17;
  RoomPtr[17][2] = 19;

  //room 19
  RoomPtr[18][0] = 11;
  RoomPtr[18][1] = 18;
  RoomPtr[18][2] = 20;

  //room 20
  RoomPtr[19][0] = 13;
  RoomPtr[19][1] = 16;
  RoomPtr[19][2] = 19;

  //⭐⭐⭐⭐⭐GAME STARTS⭐⭐⭐⭐⭐
  // when the player loses the game, the bool gameOn will be set to false and everything in the while loop will seize and game ends
  bool gameOn = true;
  int turnCount = 1;
  int repeatAdjRoom = 0;
  
  while(gameOn == true){
    printf("You are in room %d. ", occupiedRoomPtr[0]);

    //checking adjacent rooms to the player's current room:
    checkAdjacentRooms(RoomPtr, occupiedRoomPtr);


    //takes player's desired game choice:
    printf("\n\n%d. Enter your move (or 'D' for directions): ", turnCount);
    char choice;
    scanf(" %c", &choice);

    //⭐ = explanation of player's choice
    //⭐ if the user types 'd', then the program will display the cave and instructions to play the game 
    if (choice == 'd' || choice == 'D'){
      printf("\n");
      displayCave();
      displayInstructions();
      continue;

    //⭐ if the user types 'x', then the program will exit
    } else if (choice == 'x' || choice == 'X'){
	    printf("\nExiting Program ...\n");
      exit(0);

    //⭐ if the user types 'c', then all object locations will be outputted
    }  else if (choice == 'c' || choice == 'C'){
    	printf( "Cheating! Game elements are in the following rooms: \n"
        		"Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
        		"%4d %5d %6d %5d %5d %5d %5d \n\n", 
    occupiedRoomPtr[0], occupiedRoomPtr[1], occupiedRoomPtr[2], occupiedRoomPtr[3], occupiedRoomPtr[4], occupiedRoomPtr[5], occupiedRoomPtr[6]
    		);
      continue;

    //⭐ if the user types 'p', then the program will display the cave
    } else if (choice == 'p' || choice == 'P'){
      printf("\n");
      displayCave();
      continue;

    //⭐ if the user types 'm', then it will check if it is a valid room to move to --> it will move the player if it is valid. then it will check whether the room is normal or not --> depending on the normality, the player may die or continue 
    } else if (choice == 'm' || choice == 'M'){
      //takes input of desired room
      int newRoom;
      scanf(" %d", &newRoom);

      //check room validity, turn count increases if room is valid:
      int valid = 0;
      for (int i = 0; i < 3; i++){
        if (newRoom == RoomPtr[occupiedRoomPtr[0]-1][i]){
          valid++;
        }
      }   
      if (valid != 0){
        turnCount++;
        //update values of moved room and previous room:
        occupiedRoomPtr[0] = newRoom;
        
        //checks room's contents.
        int roomStatus = checkCurrentRoom(occupiedRoomPtr);
        if (roomStatus == 1){
          //player dies
          printf("\nExiting Program ...\n");
          exit(0);
        } else if (roomStatus == 2){
          //wumpus moves
          occupiedRoomPtr[1] = RoomPtr[(occupiedRoomPtr[1]-1)][0];
          continue;
        } else { 
          //player is safe and no objects in the room
          continue;
        }
        
      } else {
        printf("Invalid move.  Please retry. \n");
        continue;
      }
      
    //⭐ if the user types 'r', then it will set new locations of the objects
    } else if (choice == 'r' || choice == 'R'){
 	    printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow:  \n");
      int player, wumpus, pit1, pit2, bats1, bats2, arrowRoom;
      scanf(" %d %d %d %d %d %d %d", &player, &wumpus, &pit1, &pit2, &bats1, &bats2, &arrowRoom);
      occupiedRoomPtr[0] = player; 
      occupiedRoomPtr[1] = wumpus; 
      occupiedRoomPtr[2] = pit1; 
      occupiedRoomPtr[3] = pit2; 
      occupiedRoomPtr[4] = bats1; 
      occupiedRoomPtr[5] = bats2; 
      occupiedRoomPtr[6] = arrowRoom; 
      printf("\n");
      continue;

    //⭐ if the user types 'g', then the user will guess where wumpus is
    } else if (choice == 'g' || choice == 'G'){
      int guess;
      printf("Enter room (1..20) you think Wumpus is in: ");
      scanf(" %d", &guess);
      if (guess == occupiedRoomPtr[1]){
        printf("You won!\n");
        printf("\nExiting Program ...\n");
        gameOn = false;
      } else {
        printf("You lost.\n");
        printf("\nExiting Program ...\n");
        gameOn = false;
      }
      
    //⭐ if the user types 's', then the user will input desired shooting rooms
    } else if (choice == 's' || choice == 'S'){
      turnCount++;

      int valid = 0;
      //if the person does not have an arrow, then they cannot shoot
      if (occupiedRoomPtr[6] != -1){
        valid = -1;
      }
      if (valid == -1){
        printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
        continue;
      }
      
      //takes input of desired shooting rooms
      printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
      int amountOfRooms;
      scanf(" %d", &amountOfRooms);

      //stores the rooms into a dynamically allocated array
      int *shootRoomPtr;
      shootRoomPtr = (int*)malloc(amountOfRooms * sizeof(int));
      for (int i = 0; i < amountOfRooms; i++){
        int shootRoom;
        scanf(" %d", &shootRoom);
        shootRoomPtr[i] = shootRoom;
      }
      
      //arrow starts in the player's room
      int *currentArrowRoom = RoomPtr[occupiedRoomPtr[0]-1];
      
      //for loop for each room that the arrow goes through
      for (int nextRoom = 0; nextRoom < amountOfRooms; nextRoom++){
        //check if the shoot room is adjacent to the room the arrow is currently in
        bool adjRoom = false;
        for (int i = 0; i < 3; i++){
          if (shootRoomPtr[nextRoom] == currentArrowRoom[i]){
            adjRoom = true;
          }
        }  

        //if the room is not adjacent then arrow ricochets to the lowest adjoining room of where it is currently
        if (adjRoom == false){
          printf("Room %d is not adjacent. Arrow ricochets...	\n", shootRoomPtr[nextRoom]);

          //if the arrow ricochets first room, then the current arrow room is where the player is, and will change to where it ricochets to
          if (occupiedRoomPtr[6] == -1){
            occupiedRoomPtr[6] = occupiedRoomPtr[0];
          }
          //set the arrow room to the lowest adjoining room
          occupiedRoomPtr[6] = RoomPtr[occupiedRoomPtr[6]-1][0];
          
          //check if the arrow ricocheted into wumpus
          if (occupiedRoomPtr[6] == occupiedRoomPtr[1]){
            // Arrow ricochets, and kills Wumpus
          	printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                      "Accidental victory, but still you win!\n");
            printf("Exiting Program ...\n");
            exit(0);
            
          //check if the arrow ricocheted into person
          } else if (occupiedRoomPtr[6] == occupiedRoomPtr[0]){
            // Arrow ricochets, and kills person
          	printf( "You just shot yourself, and are dying.\n"
                      "It didn't take long, you're dead.\n");
            printf("Exiting Program ...\n");
            exit(0);
            
          //nothing in the room, arrow stops moving, loop is broken
          } else {
            break;
            
          }
        } 
          
          //if the room IS adjacent, check the room contents it shot into
        else {
          //update values in our overall game object array and the loop's pointer variable for the next loop
          occupiedRoomPtr[6] = shootRoomPtr[nextRoom];
          currentArrowRoom = RoomPtr[shootRoomPtr[nextRoom]-1];
          
          //check if the arrow shot into wumpus
          if (occupiedRoomPtr[6] == occupiedRoomPtr[1]){
            // Arrow killed Wumpus
            printf( "Wumpus has just been pierced by your deadly arrow! \n"
                  "Congratulations on your victory, you awesome hunter you.\n");
            printf("Exiting Program ...\n");
            exit(0);
            
          //check if the arrow shot into player
          } else if (occupiedRoomPtr[6] == occupiedRoomPtr[0]){
	          // Arrow killed player
          	printf( "You just shot yourself.  \n"
                      "Maybe Darwin was right.  You're dead.\n");
            printf("Exiting Program ...\n");
            exit(0);
          } 
          //nothing in the room, loop continues
        }
      }
          
    //since the arrow is shot and wumpus has not been hit, wumpus moves to the lowest adjoining room
    occupiedRoomPtr[1] = RoomPtr[occupiedRoomPtr[1]-1][0];
    continue;
    }
    
  return 0;

}
  }

	