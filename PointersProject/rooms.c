struct Room{ 
  char* name;
  struct Room * North;
  struct Room * South;
  struct Room * East; 
  struct Room * West; 
  struct Item * itemList;
  char *itemEnt;
  char *character;
};

