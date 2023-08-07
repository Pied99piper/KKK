#include<stdio.h>
#include <stdlib.h>

typedef struct node {
    int limit;
    int person;
    struct node *next;
} node_t;

node_t *append(node_t *startNode,int i)
{
    int n;
    node_t *ptr, *temp;
    scanf("%d", &n);
    temp = (node_t *)malloc(sizeof(node_t));
    if (startNode != NULL){
        ptr = startNode;
        while (ptr->next != startNode){
            ptr = ptr->next;
        }
        temp->limit = n;
        temp->person = i;
        temp->next = ptr->next;
        ptr->next = temp;
        return startNode;
    }
    else 
        startNode = (node_t *)malloc(sizeof(node_t));
        startNode->limit = n;
        startNode->person = i;
        startNode->next = startNode;
        return startNode;
}

node_t *del(node_t *ptr,node_t *startNode)
{
    ptr->next = startNode->next;
    free(startNode);
    return ptr;
}

int main()
{
    int n,k,i,count = 1;
    node_t *startNode;
    node_t *ptr;
    startNode = NULL;
    scanf("%d %d", &n, &k);
    for (i = 1 ; i <= n ; ++i) {
        startNode = append(startNode,i);
    }
    ptr = startNode;
    while ((startNode->next)->person != startNode->person) {
        if ((count%k == 0) || (count%10 == k) || ((count%100)/10 == k) || (count/100 == k)){
            startNode->limit -= 1;
            if (startNode->limit == -1) {
                startNode = del(ptr,startNode);
            }
        }
        ptr = startNode;
        startNode = startNode->next;
        count++;
    }
    printf("%d", startNode->person);
}