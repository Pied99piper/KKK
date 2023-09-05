#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *mom;
    struct node *right_sib;
    struct node *childs;
} node_t ;

typedef node_t tree_t;

typedef struct queue_node{
    tree_t *data;
    struct queue_node *next;
} queue_node_t;

typedef struct queue{
    queue_node_t *front;
    queue_node_t *rear;
} queue_t;

// for_help
tree_t *search_func(tree_t *t,int v)
{
    if (t == NULL){
        return t;
    }
    if (t->data == v){
        return t;
    }
    tree_t *pos = search_func(t->childs,v);
    if (pos != NULL){
        return pos;
    }
    else
        return search_func(t->right_sib,v);
}
queue_t	*createQueue()
{
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    q->front = q->rear = NULL;
    return q;
}
void enqueue(queue_t *q, tree_t *data)
{
    queue_node_t *newQueueNode = (queue_node_t*)malloc(sizeof(queue_node_t));
    newQueueNode->data = data;
    newQueueNode->next = NULL;
    if (q->rear == NULL)
	{
        q->front = q->rear = newQueueNode;
        return ;
    }
    q->rear->next = newQueueNode;
    q->rear = newQueueNode;
}
tree_t	*dequeue(queue_t *q)
{
    if (q->front == NULL)
        return NULL;
    queue_node_t *temp = q->front;
    tree_t	*data = temp->data;
    q->front = q->front->next;
    if (!q->front)
        q->rear = NULL;
    free(temp);
    return data;
}

//function start here
tree_t *attach(tree_t *t,int par, int child)
{
    tree_t *pos = search_func(t,par); 
    tree_t *chicharito;
    chicharito = (tree_t *)malloc(sizeof(tree_t));
    chicharito->data = child;
    chicharito->mom = NULL;
    chicharito->childs = NULL;
    chicharito->right_sib = NULL;
    if (par == -1){
        return chicharito;
    }
    if (pos->childs == NULL){
        chicharito->mom = pos;
        pos->childs = chicharito;
        return t;
    }
    else {
        chicharito->mom = pos;
        pos = pos->childs;
        while (pos->right_sib != NULL){
            pos = pos->right_sib;
        }
        pos->right_sib = chicharito;
        return t;
    }
}
void delete(tree_t *v)
{
    if (v == NULL)
		return;
	delete(v->childs);
	delete(v->right_sib);
	free(v);
	return;
}
tree_t *detach(tree_t *t, int v)
{
    tree_t	*start, *pre;
	start = search_func(t, v);
	if (!start)
		return (t);
	pre = (start->mom)->childs;
	if (pre->data == start->data)
		(start->mom)->childs = start->right_sib;
	else
	{
		while (pre->right_sib && (pre->right_sib)->data != start->data)
			pre = pre->right_sib;
		pre->right_sib = start->right_sib;
	}
	start->right_sib = NULL;
	delete(start);
	return (t);
}
int search(tree_t *t, int v)
{
    if (!t)
		return (0);
	if (t->data == v)
		return (1);
	if (search(t->childs, v))
		return (1);
	return (search(t->right_sib, v));
}
int degree(tree_t *t, int v)
{
    int de = 0;
    tree_t *pos;
    pos = search_func(t,v);
    if (pos == NULL){
        return de;
    }
    else if (pos->childs == NULL){
        return de;
    }
    else {
        pos = pos->childs; 
        while (pos->right_sib != NULL){
            de++;
            pos = pos->right_sib;
        }
        de++;
        return de;
    }
}
int is_root(tree_t *t, int v)
{
    if (t->data == v){
        return 1;
    }
    else 
        return 0;
}
int is_leaf(tree_t *t, int v)
{
    tree_t *pos;
    pos = search_func(t,v);
    if (pos->childs == NULL){
        return 1;
    }
    else
        return 0;
}
void siblings(tree_t *t, int v)
{
    tree_t *pos = search_func(t,v);
    tree_t *find = pos->mom;
    if (find == NULL){
        printf("\n");
        return;
    }
    find = find->childs;
    while (find != NULL){
        if(find->data != v){
            printf("%d ",find->data);
            find = find->right_sib;
        }
        else
            find = find->right_sib;
    }
    printf("\n");
}
int depth(tree_t *t, int v)
{
    int dep = 1;
    tree_t *pos = search_func(t,v);
    pos = pos->mom;
    if (pos == NULL){
        return 0;
    }
    else{
        while (pos->mom != NULL){
            dep++;
            pos = pos->mom;
        }
        return dep;
    }
}
void find_mypath(tree_t *t,int start)
{
    if (t->data == start){
        printf("%d ",t->data);
        return;
    }
    find_mypath(t->mom,start);
    printf("%d ",t->data);    
}
void print_path(tree_t *t, int start, int end)
{
    tree_t *pos = search_func(t,end);
    find_mypath(pos,start); 
    printf("\n");
}
int path_length(tree_t *t, int start, int end)
{
    int length = 0;
    tree_t *pos = search_func(t,end);
    while (pos->data != start){
        length++;
        pos = pos->mom;
    }
    length++;
    return length;
}
void find_ances(tree_t *t)
{
    if (t->mom == NULL){
        printf("%d ",t->data);
        return;
    }
    find_ances(t->mom);
    printf("%d ",t->data);    
}
void ancestor(tree_t *t, int v)
{
    tree_t *pos = search_func(t,v);
    find_ances(pos);
    printf("\n");
}
void bfs(tree_t *t)
{
    if (!t)
        return;
    queue_t *q = createQueue();
    enqueue(q, t);
    while (q->front != NULL)
	{
        tree_t *current = dequeue(q);
        printf("%d ", current->data);
        tree_t *pos = current->childs;
        while (pos != NULL) {
            enqueue(q, pos);
            pos = pos->right_sib;
        }
    }
    printf("\n");
    free(q);
}
void descendant(tree_t *t, int v)
{
    bfs(search_func(t,v));
}
void for_dfs(tree_t *t)
{
    if (t == NULL){
        return ;
    }
    printf("%d ",t->data);
    for_dfs(t->childs);
    for_dfs(t->right_sib); 
}
void dfs(tree_t *t)
{
    for_dfs(t);
    printf("\n");
}
int n = 0;
void print_tree(tree_t *t)
{
    if (t == NULL){
        return;
    }
    printf("%*d\n", n,t->data);
    n += 4;
    print_tree(t->childs);
    n -= 4;
    print_tree(t->right_sib);
}

int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
    scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d %d", &parent, &child);
                t = attach(t, parent, child);
                break;
            case 2:
                scanf("%d", &node);
                t = detach(t, node);
                break;
            case 3:
                scanf("%d", &node);
                printf("%d\n", search(t, node));
                break;
            case 4:
                scanf("%d", &node);
                printf("%d\n", degree(t, node));
                break;
            case 5:
                scanf("%d", &node);
                printf("%d\n", is_root(t, node));
                break;
            case 6:
                scanf("%d", &node);
                printf("%d\n", is_leaf(t, node));
                break;
            case 7:
                scanf("%d", &node);
                siblings(t, node);
                break;
            case 8:
                scanf("%d", &node);
                printf("%d\n", depth(t, node));
                break;
            case 9:
                scanf("%d %d", &start, &end);
                print_path(t, start, end);
                break;
            case 10:
                scanf("%d %d", &start, &end);
                printf("%d\n",
                    path_length(t, start, end));
                break;
            case 11:
                scanf("%d", &node);
                ancestor(t, node);
                break;
            case 12:
                scanf("%d", &node);
                descendant(t, node);
                break;
            case 13:
                bfs(t);
                break;
            case 14:
                dfs(t);
                break;
            case 15:
                print_tree(t);
                break;
        }
    }
    return 0;
}