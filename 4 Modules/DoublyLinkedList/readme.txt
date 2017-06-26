Commands:
  Q: Exit program
  H: Print help
  P: Toggle printing of memory after every command
  F: Free all memory
  [0-9]P: Print what's inside item [0-9]
  [0-9]F: Free what's inside item [0-9]
  [0-9]M[Int]: Allocate [Int] bytes to item [0-9]
Usage:
  > make run
  The program will ask you how many bytes of simulation memory you want, then it will allow you to type commands. You have 10 pointers labeled 0 to 9 to allocate memory to, and the program will not stop you from creating a fake memory leak by allocating memory to a pointer twice. For this reason there is a free all command which will free all memory, but will unfortunatly not update your pointers.
Testing:
  > make test
  This will run a small test program.


