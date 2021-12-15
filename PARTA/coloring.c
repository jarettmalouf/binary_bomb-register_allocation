#include"coloring.h"
#include <math.h>

#define DOUBLE(ptr,nmemb) realloc (ptr, (nmemb *= 2) * sizeof(*ptr))
#define STACK_SIZE 1000

/*
 * Init Function : Initializes basic global variables.
 */

void Init(char* inputFile)
{
	FILE* fp;
	char line[LINE_SIZE];
	fp = fopen(inputFile, "r");
	if(fp == NULL)
	{
					printf("\nInput file does not exist!!!!!");
					exit(0);
	}
	fgets(line, sizeof(line), fp);
	sscanf(line, "%d", &k);
	while(!feof(fp))
	{
		fgets(line,sizeof(line),fp);
		vertices++;
	}
	--vertices; 
}

/*
 * TO FILL - ReadInput function : This function should read the input into the graph data structure.
 */
void ReadInput(int G[vertices][vertices], char* inputFile)
{
	FILE* fp;
	fp = fopen(inputFile, "r");
	if(fp == NULL)
	{
		printf("\nInput file does not exist!!!!!");
		exit(0);
	}

	char line[LINE_SIZE];
	fgets(line, sizeof(line), fp);
	for (int i = 0; i < vertices; i++) {
		fgets(line, sizeof(line), fp);
		for (int j = 0; j < vertices; j++) {
			sscanf(line + j * 2, "%d", &G[i][j]);
		}
	}

	// CheckInput(G);
	fclose(fp);
}


/*
 * CheckInput Function : Utility function to check if the input you read into the data structure is correct.
 * 
 */
void CheckInput(int G[vertices][vertices])
{
	int i, j;
	printf("\n vertices is : %d\n", vertices);
	for (i = 0; i < vertices; i++)
	{
		for (j = 0; j < vertices; j++)
		{
			printf("\t %d", G[i][j]);
		}
		printf("\n");
	}

}



// array_t

struct array_t {
	int *arr;
	int capacity;
	int size;
};

struct array_t GetNewArray(int capacity) {
	struct array_t a;
	a.arr = (int *) malloc (sizeof(int) * capacity);
	a.capacity = capacity;
	a.size = 0;
	return a;
}

// stack

struct array_t stack[STACK_SIZE];         
int top = -1;  
bool IsEmpty() { return top == -1; }
struct array_t Pop() { return stack[top--]; }
void Push(struct array_t a) { stack[++top] = a; }

struct array_t GetNextArray(struct array_t curr, int num) {
	struct array_t a = GetNewArray(curr.size + 1);
	int i;
	for (i = 0; i < curr.size; i++) a.arr[i] = curr.arr[i];
	a.arr[i] = num;
	a.size = ++i;
	return a;
}

bool IsValidGraph(struct array_t colors, int G[vertices][vertices]) {
	for (int i = 0; i < colors.size; i++) {
		for (int j = 0; j < colors.size; j++) {
			if (G[i][j] == 1 && colors.arr[i] == colors.arr[j]) return false;
		}
	}
	return true;
}

bool KColorable(int k, int v, int G[vertices][vertices]) {
	Push(GetNewArray(0));
	while (!IsEmpty()) {
		struct array_t curr = Pop();
		if (curr.size == v) return true;
		for (int i = 0; i < k; i++) {
			struct array_t next = GetNextArray(curr, i);
			if (IsValidGraph(next, G)) Push(next);
		}
	}
	return false;
}

void ColorGraph(int G[vertices][vertices]) {
	printf("%c\n", KColorable(k, vertices, G) ? 'Y' : 'N');
}