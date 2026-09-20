# A Crude Stack-Based Calculator

It's a very crude stack-based calculator (like dc) written in C.

To make it, `make main` to output a `main` program.
Feel free to modify the name or move it somewhere else.

To use it, pass numbers (in base ten) to add them to a stack.
Then, pass `add`, `sub`, `mul`, or `div` to take the top two numbers
and operate on them. Pass `print` to view what's currently on the stack.

Pass `help` for a small help command.

The first operand to the operation is the second-to-top number on the stack,
and the second operation is the top number on the stack. This is done to make
it in-line with what you see when you pass `print`.

For now, only integers (specifically of type `ssize_t`) are supported. Written
for Unix-like operating systems.
