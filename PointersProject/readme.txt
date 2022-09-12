-------THIS IS THE README FILE-------

How to compile the code ->
Firstly unzip the file in order to access the code inside of it.
Move the folder onto a compiler so that it will be easier to run it
After the file has unzipped and been added to the directory, use the GCC complier to run the code
Use the gcc compiler on "adventure.zip" like this:

gcc adventure.zip
(You can also make an executable file by running the command-> 'gcc -o adventure.c' instead)

If the code has no errors it will compile.
After it is compiled call the main method by running the following command:

./a.out

After this, you can enjoy the game!

-------------------------------------------------------------------------------------
This project is a text adventure game of a very popular boardgame - Clue
In this game you are an investigator and are in a house of 3x3 grid rooms.
You are supposed to go in each room and find clues in order to prove who is the murderer.

We have used pointers and structs in this code
Pointers have been used so that we can make it easier to reference each of the rooms to its adjacent ones.
Structs have been used to store the various random values in this game.
After all this is a detective game so there has to be a lot of randomization
There is one board whose memory has been allocated by a 9-length pointer array
This array is used for reference everywhere

---------------------------------------------------------------------------------------

The user is supposed to put at most only a two word input while playing this game
This game will be played until all ten tries after using the word command have been exhausted without finding the actual answer
The game will end after the correct answer is found within ten tries

ENJOY!


