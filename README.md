# A Crude Stack-Based Calculator

It's a very crude stack-based calculator (like dc) written in C.

To make it, `make main` to output a `main` program.
Feel free to modify the name or move it somewhere else.

To use it, pass numbers (in base ten) to add them to a stack.
Then, pass `add`, `sub`, `mul`, or `div` to take the top two numbers
and operate on them. Pass `print` to view what's currently on the stack.

Input `help` for a small help command.

The first operand to the operation is the second-to-top number on the stack,
and the second operation is the top number on the stack. This is done to make
it in-line with what you see when you pass `print`, as well as the order in
which integers that are input are sent to the stack.

This calculator also supports a variable to store the answer and a variable to
store one integer pulled from the stack. Input `ans` to push the previous result
of an operation to the top of the stack, and input `pull` to take the top of the
stack and put it in the "mem" variable; input `mem` to push whatever is in the
"mem" variable onto the top of the stack.

For now, only integers (specifically of type `ssize_t`) are supported. Written
for Unix-like operating systems.
