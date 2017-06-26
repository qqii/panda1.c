Simple Reverse Polish Notation Calculator with Basic Arithmetic Functions

	Reverse Polish Notation
		"Reverse Polish notation (RPN) is a mathematical notation in which every operator follows all of its operands, in contrast to Polish notation, which puts the operator in the prefix position. It is also known as postfix notation and is parenthesis-free as long as operator arities are fixed."

		Taken from https://en.wikipedia.org/wiki/Reverse_Polish_notation

	Usage:
		The program accepts integers and decimals and will return what is at the top of the stack at the end of the calculation. This means "./rpncalc.o 9 7 10 5 -" will return 5. Decimals have the same precision as the double type therefore this program not be used if precise calculations are needed. 

	Accepted Arithmetic Functions:
		Addition		+
		Subtraction		-
		Multiplication	"*"
		Division		/

		Currently because *nux may expand the "*" into the list of files in the current directory, you need to put it in quotes like I have done above.

		Currently it is very easy to allow you to edit the code and add your own aliases for each of the functions.

	Adding New Functions
		All functions take a Stack* as the only argument. Functions can call pop if they want to pop what is at the top of the stack, dblpush if they want to push a double onto the stack and strpush if they want to push a string (used if they need to push another function). They should not return anything and calculated values should be pushed back onto the stack.

		Currently all functions are stored as a struct called StackFunction which contains matching string and a function pointer. They are stored in a global array called stackfuncarr. Currently new functions are added into this array in the calculate function.

		To add your own function:
			1. Increase FUNCTION_ARRAY_LENGTH by the number of functions you are going to add.
			2. Add your function after the "StackFunctions:" comment.
			3. Create a new StackFunction in the calculate function (here is where you define the string your looking for).
			4. Add the StackFunction to the stackfuncarr.

		To add an alias, ignore step 2 and create a new StackFunction with the same function pointer but different matching string.

	Possible Improvements
		There are some possible improvements that could be made to the code in this program. For some of them, I will try to go over each of them and why they are as they are at the moment.

		#define FUNCTION_ARRAY_LENGTH 4
		StackFunction stackfuncarr[FUNCTION_ARRAY_LENGTH];
			Instead of defining the FUNCTION_ARRAY_LENGTH as a preprocessor value, creating a new struct may be a much better method. It is also not ideal that there is no function to add functions to the stackfuncarr and they have to be added manually in the calculate function. 

		void dblpush(Stack *stack, double number);
		void strpush(Stack *stack, char *string);
			Since there is no function overloading in C, I have had to create two functions to push things onto the stack. It is also not ideal to convert a number into a string just to call strpush.

		double calculate(int argc, char **argv) does not provide any way to inspect the stack
			For larger calculations, people may want the ability to see the stack at every point in the calculation. It also does not provide any error if there are things on the stack at the end of calculation.
			Currently there is a function called debug_stack which I have commented out which can print the stack but as I am not happy with the way it prints the stack I have not included these features.

		if((float)(long long int)result == result){
        printf("%lld\n", (long long int)result);
        	This nasty hack prints integers without the unnecessary trailing zeros. I was going to use the floor function from math.h but I have not managed to get it to compile without errors. A superior system would be to have converted the result into a string then truncate any trailing zeros.

        lack of functions
        	Like above, did not include any other functions because I could not get any functions from math.h to work properly. 






