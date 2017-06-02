#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct listnode {
	unsigned long int data;
	struct listnode *next;
} ListNode;

int main(void)
{
 	int N, i, max;
	ListNode *head;
	ListNode *last;
	ListNode *current;
	ListNode *ptr;
 	while((scanf("%d", &N)) != EOF)
	{
		max = 0;
		last = NULL;
		for (i = 0; i < N; i++)
		{
			if(i <= 1)
			{
				head = (ListNode *)malloc(sizeof(ListNode));
                assert(head != NULL);
				head->data = 1;
				head->next = last;
				if (last == NULL)
					last = head;
			}
			else
			{
				ptr = head;
				while(ptr == head)
				{
					current = (ListNode *)malloc(sizeof(ListNode));
					assert(current != NULL);
					current->data = ptr->data + (ptr->next)->data;
					current->next = ptr->next;
					ptr->next = current;
					ptr = current->next;
				}
				while(ptr->next != NULL)
				{
					ptr->data += (ptr->next)->data;
					ptr = ptr->next;
				}
			}
			for (ptr = head; ptr != NULL; ptr = ptr->next)
			{
				printf("%d", ptr->data);
				max = (max > ptr->data)? max: ptr->data;
				if (ptr->next != NULL)
                    printf(" ");
			}
			printf("\n");
		}
		printf("%d\n", max);
	}
  return 0;
}
