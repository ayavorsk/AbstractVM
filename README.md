# AbstractVM
#run ./abstract abstract_vm
#or ./abstract
#   some command
#   exit
#   ;;
#   ;; = end read in std::cin
AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.
These arithmetic expressions are provided to the machine as basic assembly programs.

Comments: Comments start with a ’;’ and finish with a newline. A comment can
be either at the start of a line, or after an instruction.

• push v: Pushes the value v at the top of the stack. The value v must have one of
the following form:
◦ int8(n) : Creates an 8-bit integer with value n.
◦ int16(n) : Creates a 16-bit integer with value n.
◦ int32(n) : Creates a 32-bit integer with value n.
◦ float(z) : Creates a float with value z.
◦ double(z) : Creates a double with value z.

• pop: Unstacks the value from the top of the stack. If the stack is empty, the
program execution must stop with an error.

• dump: Displays each value of the stack, from the most recent one to the oldest
one WITHOUT CHANGING the stack. Each value is separated from the next one
by a newline.

• assert v: Asserts that the value at the top of the stack is equal to the one passed
as parameter for this instruction. If it is not the case, the program execution must
stop with an error. The value v has the same form that those passed as parameters
to the instruction push.

• add: Unstacks the first two values on the stack, adds them together and stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

• sub: Unstacks the first two values on the stack, subtracts them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

• mul: Unstacks the first two values on the stack, multiplies them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

• div: Unstacks the first two values on the stack, divides them, then stacks the result.
If the number of values on the stack is strictly inferior to 2, the program execution
must stop with an error. Moreover, if the divisor is equal to 0, the program execution
must stop with an error too. Chatting about floating point values is relevant a this
point. If you don’t understand why, some will understand. The linked question is
an open one, there’s no definitive answer.

• mod: Unstacks the first two values on the stack, calculates the modulus, then
stacks the result. If the number of values on the stack is strictly inferior to 2, the
program execution must stop with an error. Moreover, if the divisor is equal to 0,
the program execution must stop with an error too. Same note as above about fp
values.

• print: Asserts that the value at the top of the stack is an 8-bit integer. (If not,
see the instruction assert), then interprets it as an ASCII value and displays the
corresponding character on the standard output.

• exit: Terminate the execution of the current program. If this instruction does not
appears while all others instruction has been processed, the execution must stop
with an error.
