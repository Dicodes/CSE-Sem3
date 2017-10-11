#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct tnode
{
	int rollNo;
	char name[20];
	char section;
	float CGPA;
	char phoneNumber[20];
	struct tnode *lchild;
	struct tnode *rchild;
} TNode;

TNode * getNode()
{
	TNode *root = (TNode *) malloc (sizeof(TNode));
	root->lchild = root->rchild = NULL;
	return root;
}

TNode *insertBST (TNode *root, int r, float c, char p[], char s, char n[])
{
	if (root == NULL)
	{
		root = getNode();
		root->rollNo = r;
		root->section = s;
		root->CGPA = c;
		strcpy (root->name, n);
		strcpy (root->phoneNumber, p);
		return root;
	}
	else if (r < root->rollNo)
	{
		root->lchild = insertBST(root->lchild, r, c, p, s, n);
	}
	else if (root->rollNo < r)
	{
		root->rchild = insertBST(root->rchild, r, c, p, s, n);
	}
	return root;
}

int search (TNode *root, int item)
{
	if (root == NULL)
	{
		return 0;
	}
	else if (root->rollNo == item)
	{
		return 1;
	}
	else if (item < root->rollNo)
	{
		search(root->lchild, item);
	}
	else if (root->rollNo < item)
	{
		search(root->rchild, item);
	}
}

TNode *delete (TNode *root, int roll) 
{
	if (root == NULL)
		return root;
	
	if (roll < root->rollNo)
		root->lchild = delete(root->lchild, roll);
	else if (roll > root->rollNo)
		root->rchild = delete(root->rchild, roll);
	
	else 
	{
		if (root->lchild == NULL) 
		{
			TNode *temp = root->rchild;
			free(root);
			return temp;
		}
		else if (root->rchild == NULL) 
		{
			TNode *temp = root->lchild;
			free(root);
			return temp;
		}
		
		TNode *temp = root;
		while (temp->lchild != NULL)
			temp = temp->lchild;
		root->rollNo = temp->rollNo;
		strcpy (root->name, temp->name);
		strcpy (root->phoneNumber, temp->phoneNumber);
		root->CGPA = temp->CGPA;
		root->section = temp->section;
		root->rchild = delete(root->rchild, temp->rollNo);
	}
	return root;
}

void printDetails (TNode *root)
{
	printf("Student details are\nRoll Number:%d\nName:%s\nCGPA:%.2f\nPhone:%s\nSection:%c\n", root->rollNo, root->name, root->CGPA, root->phoneNumber, root->section);
}


void preorder (TNode *root)
{
  if (root != NULL)
    {	
      printDetails(root);
      preorder (root->lchild);
      preorder (root->rchild);
    }
}

int main()
{
	TNode *root;
	root = NULL;
	int roll;
	float cgpa;
	char sec;
	char name[20];
	char phone[20];
	int el, delEle, rEle, ch, x;
	while (1)
    {
      	printf("1 to insert record\n2. List Records\n3.Search (Roll Number)\n4.Delete Record\n0.Exit Program.\n");
      	scanf(" %d", &ch);
      	switch(ch)
		{
			case 1:
	  			printf("Enter record:\n");
	  			printf("Enter name, roll number, cgpa, phone number, section in order:\n");
	  			scanf(" %s %d %f %s %c", name, &roll, &cgpa, phone, &sec);
	  			root = insertBST(root, roll, cgpa, phone, sec, name);
	 			break;
			case 2:
				preorder(root);
				printf("*****\n");
				break;
			case 3:
				printf("Enter roll to be searched\n");
				scanf("%d", &rEle);
				x = search(root, rEle);
				if (x == 1)
					printf("Student found!\n");
				else
					printf("Student with roll number %d does not exist\n", rEle);
				break;
			case 4:
				printf("Enter item to be deleted\n");
				scanf("%d", &delEle);
				TNode *element = getNode();
				element->rollNo = search(root, delEle);
				if (element != NULL) 
				{
					delete(root, delEle);
				}
				else
					printf("%d is not present in the tree.", delEle);
				break;
			case 0:
				exit(0);
		}
	}
	return 0;
}