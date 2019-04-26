#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list_tag2 {
	int input;
	struct list_tag2 * next;
} QListNode;

typedef struct {
	QListNode * first;
	QListNode * last;
} queue, queueDList;

typedef struct list_tag1 {
	int index, input, output;
	char letter;
	queueDList q;
	struct list_tag1 * next;
	struct list_tag1 * prev;
} DListNode;

typedef struct {
	DListNode * first;
	DListNode * last;
} dlist;


void queueInit(queue * qp);
void queuePrint(queue q);
void queueInsert(queue * qp, int in);
void queueRemove(queue * qp);
void dlistInsert(dlist * lp, int i, char c, queue q);
void dlistInit(dlist * lp);
void dcalc(dlist lp);

int main()
{
	dlist my_dlist;
	queue my_queue;
	queueInit(&my_queue);
	dlistInit(&my_dlist);
	FILE *fp;
	char letter;
	int index, n, input, i, flag = 0;

	fp = fopen("file_milestone4.txt", "r");

	if (fp == NULL)
	{
		printf("Error opening file\n");
		system("pause");
	}
	fscanf(fp, "%d", &n);
	for (i = 0; i < n; i++)
	{
		int count = 0;
		if (!flag)
			fscanf(fp, "%d: %c %d", &index, &letter, &input);
		else
		{
			index = input;
			fscanf(fp, ": %c %d", &letter, &input);
		}

		printf("%d: %c %d", index, letter, input);
		while (input < index)
		{
			flag = 1;
			if (input != 0)
			{
				queueInsert(&my_queue, input);
				count++;
			}

			if (fscanf(fp, " %d", &input) == -1)
				break;
			if (input < index)
				printf(" %d", input);
		}

		queuePrint(my_queue);
		printf("\n");
		dlistInsert(&my_dlist, index, letter, my_queue);
		queueInit(&my_queue);

		if (letter == 'Q')
		{
			break;
		}
	}
	printf("Calculate...\n");
	dcalc(my_dlist);
	system("pause");
	fclose(fp);
	return 0;
}
void queueInit(queue * qp) {
	qp->first = NULL;
	qp->last = NULL;
}
void dlistInit(dlist * lp) {
	lp->first = NULL;
	lp->last = NULL;
}

void dlistInsert(dlist * lp, int i, char c, queue q) {
	DListNode * n = (DListNode *)malloc(sizeof(DListNode));
	if (n == NULL)
	{
		printf("Out of memory\n");
		exit(1);
	}
	n->index = i;
	n->letter = c;
	n->q = q;

	if (lp->first == NULL)
	{
		n->prev = n->next = NULL;
		lp->first = lp->last = n;
	}
	else
	{
		n->prev = lp->last;
		n->next = NULL;
		lp->last->next = n;
		lp->last = n;
	}
}
void queueInsert(queue * qp, int in)
{
	QListNode * qn = (QListNode *)malloc(sizeof(QListNode));

	if (qn == NULL)
	{
		printf("Out of memory\n");
		exit(1);
	}

	qn->input = in;
	qn->next = NULL;

	if (qp->last == NULL)
		qp->first = qp->last = qn;
	else
	{
		qp->last->next = qn;
		qp->last = qn;
	}
}

void queueRemove(queue * qp) {
	QListNode* n;
	int result;
	if (qp->first == NULL)
	{
		printf("emptyqueue\n"); exit(1);
	}
	n = qp->first;
	result = qp->first->input;
	qp->first = qp->first->next;
	free(n);
	if (qp->first == NULL)
		qp->last = NULL;
}
void queuePrint(queue q) {
	QListNode * n;
	if (q.first != NULL)
		printf("\nQueue: ");

	for (n = q.first; n != NULL; n = n->next)
	{
		printf("%d ", n->input);
	}
}

void dcalc(dlist my_dlist) {
	DListNode * n, *tmp;
	QListNode *qn;
	int bin, flag = 0, temp = 0;
	n = my_dlist.first;
	qn = my_dlist.first->q.first;
	while (n != NULL)
	{
		if (n->letter == 'I') {
			do {
				printf("Enter a binary value (1 or 0) as input.\n");
				scanf("%d", &bin);
			} while (bin != 0 && bin != 1);
			n->output = bin;
		}
		else if (n->letter == 'N') {
			tmp = my_dlist.first;

			for (qn = n->q.first; qn != NULL; qn = qn->next) 
			{
				tmp = my_dlist.first;
				while (tmp->index != qn->input)
				{
					tmp = tmp->next;
				}
			}
			int value1 = tmp->output;
			n->output = not_gate(value1);
		}
		else if (n->letter == 'A') {
			{
				tmp = my_dlist.first;
				for (qn = n->q.first; qn != NULL; qn = qn->next)
				{
					tmp = my_dlist.first;
					while (tmp->index != qn->input)
					{

						tmp = tmp->next;
					}
					temp = and_gate(1, tmp->output);
					if (temp == 0)
						flag++;
				}
				if (flag == 0)
					n->output = 1;
				else
					n->output = 0;
			}
		}
		else if (n->letter == 'O') {
			tmp = my_dlist.first;
			flag = 0;
			for (qn = n->q.first; qn != NULL; qn = qn->next)
			{
				tmp = my_dlist.first;
				while (tmp->index != qn->input)
				{
					tmp = tmp->next;
				}
				temp = or_gate(0, tmp->output);
				if (temp != 0)
					flag++;
			}
			if (flag == 0)
				n->output = 0;
			else
				n->output = 1;
		}
		else if (n->letter == 'X') {
			tmp = my_dlist.first;
			qn = n->q.first; 
			while (tmp->index != qn->input)
			{
				tmp = tmp->next;
			}
			int value1 = tmp->output;
			tmp = my_dlist.first;
			qn = n->q.first->next; 
			while (tmp->index != qn->input)
			{
				tmp = tmp->next;
			}
			int value2 = tmp->output;
			n->output = xor_gate(value1, value2);
		}

		else if (n->letter == 'Q') {
			tmp = my_dlist.first;
			qn = n->q.first;				
			while (tmp->index != qn->input)
			{
				tmp = tmp->next;
			}
			int value1 = tmp->output;
			n->output = (value1);
		}

		printf("ID:%d TYPE:%c VALUE:%d \n", n->index, n->letter, n->output);
		n = n->next;
	}

}
