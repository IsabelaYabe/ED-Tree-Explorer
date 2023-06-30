#pragma once

// This is a tree's Node
struct TreeNode
{
  int iData;
  struct TreeNode *ptrLeft;
  struct TreeNode *ptrRight;
};

// This is a list's Node
struct ListNode
{
  int iData;
  struct ListNode *ptrPrev;
  struct ListNode *ptrNext;
};

struct ListNode* newListNode(int);

struct ListNode* insertNode(struct ListNode*, int);

void printList(struct ListNode*);

struct ListNode* insertCurrentLevel(struct ListNode*, struct TreeNode*, int);

struct ListNode* insertBFS(struct TreeNode*);

int getLength(struct ListNode*);

struct ListNode* getNodeByIndex(struct ListNode*, int);

void swapNodes(struct ListNode**, struct ListNode*, struct ListNode*);

void selectionSort(struct ListNode**);

void insertionSort(struct ListNode**);

void shellSort(struct ListNode**);

void bubbleSort(struct ListNode**);

struct TreeNode* newTreeNode(int);

struct TreeNode* insertNode(struct TreeNode*, int);

int getHeight(struct TreeNode*);

void printCurrentLevel(struct TreeNode*, int);

void traverseBFS(struct TreeNode*);