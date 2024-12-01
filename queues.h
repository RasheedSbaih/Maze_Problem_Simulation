#ifndef HEADERS_H
#define HEADERS_H

typedef enum Heading {NORTH, WEST, SOUTH, EAST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;


typedef struct coord {
    int x;
    int y;
} coord;
typedef struct neighbor {
    coord coord;
    Heading heading;
    int streak;
} neighbor;

typedef neighbor item_type;
typedef struct _queue* queue;
queue queue_create();
void queue_destroy(queue q);
void queue_push(queue q, item_type elem);
item_type queue_pop(queue q);
item_type queue_first(queue q);
int queue_is_empty(queue q);
int queue_size(queue q);
void queue_clear(queue q);
struct node {
    item_type data;
    struct node* next;
};

#endif