#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define STACK_MAX_SIZE (ssize_t)128

/* stack definition */
struct stack {
	ssize_t size;
	ssize_t n[STACK_MAX_SIZE];
};
typedef struct stack stack_t;

/* method declarations */
void init_stack(stack_t *);
ssize_t stack_push(stack_t *, ssize_t);
ssize_t stack_pull(stack_t *);
/* calculator parts */
ssize_t operate(stack_t *, ssize_t (*)(ssize_t, ssize_t));
ssize_t add(ssize_t, ssize_t);
ssize_t sub(ssize_t, ssize_t);
ssize_t mul(ssize_t, ssize_t);
ssize_t div(ssize_t, ssize_t);
/* debug methods */
void debug_print_stack(stack_t *);
/* help */
void help();


int main() {
	stack_t s;
	init_stack(&s);

	char input[128];

	while (1) {
		ssize_t nread = read(STDIN_FILENO, input, 128);
		if (nread < 0) {
			if (errno == EINTR) continue;
			perror("read");
			return 1;
		}

		// force a C string
		input[nread - 1] = '\0';

		if (!strcmp(input, "quit")) break;

		int n;
		nread = sscanf(input, " %d", &n);
		if (nread == 1) {
			stack_push(&s, (ssize_t)n);
			printf("Pushed %ld onto the stack.\n", (ssize_t)n);
		}

		if (!strcmp(input, "help")) {
			help();
		}

		if (!strcmp(input, "pull")) {
			printf("Pulled %ld from the stack.\n", stack_pull(&s));
		}

		if (!strcmp(input, "print")) {
			printf("stack: ");
			debug_print_stack(&s);
			printf("\n");
		}

		if (!strcmp(input, "add")) {
			printf("Result: %ld\n", operate(&s, add));
		}

		if (!strcmp(input, "sub")) {
			printf("Result: %ld\n", operate(&s, sub));
		}

		if (!strcmp(input, "mul")) {
			printf("Result: %ld\n", operate(&s, mul));
		}

		if (!strcmp(input, "div")) {
			printf("Result: %ld\n", operate(&s, div));
		}

		printf("\n");
	}

	return 0;
}


/* method definitions */
void debug_print_stack(stack_t *stack) {
	for (ssize_t i = 0; i < stack->size; i++) {
		printf("%ld ", stack->n[i]);
	}
}

void init_stack(stack_t *stack) {
	stack->size = 0;
	return;
}

ssize_t stack_push(stack_t *stack, ssize_t n) {
	if (stack->size >= STACK_MAX_SIZE) {
		fprintf(stderr, "ERR: Stack is full (%lu items)! %ld not added to stack.\n", stack->size, n);
		return 1;
	}

	stack->n[stack->size] = n;
	stack->size += 1;

	return 0; // success
}

ssize_t stack_pull(stack_t *stack) {
	if (stack->size == 0) { // early return on empty stack
		fprintf(stderr, "WRN: Stack is empty! Pulled an imaginary 0 from the stack.\n");
		return 0;
	}

	stack->size -= 1;
	return stack->n[stack->size];
}

ssize_t operate(stack_t *stack, ssize_t (*f)(ssize_t, ssize_t)) {
	if (stack->size < 2) {
		fprintf(stderr, "WRN: Operating on stack with size less than two.\n");
	}
	
	ssize_t n = stack_pull(stack);
	return f(stack_pull(stack), n);
}

ssize_t add(ssize_t a, ssize_t b) {
	return a + b;
}

ssize_t sub(ssize_t a, ssize_t b) {
	return a - b;
}
ssize_t mul(ssize_t a, ssize_t b) {
	return a * b;
}

ssize_t div(ssize_t a, ssize_t b) {
	if (b == 0) b = 1;

	return a / b;
}

void help() {
	printf("operations: help | some_integer | print | (add|sub|mul|div)\n");
}
