#include <stdio.h>
#include <stdlib.h>


#define TABLE_SIZE 100


typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *list[TABLE_SIZE];
} HashTable;

HashTable* createHashTable() {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->list[i] = NULL;
    }
    return table;
}

unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(HashTable *table, int key, int value) {
    int index = hash(key);
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table->list[index];
    table->list[index] = newNode;
}

int search(HashTable *table, int key) {
    int index = hash(key);
    Node *list = table->list[index];
    while (list) {
        if (list->key == key) {
            return list->value;
        }
        list = list->next;
    }
    return -1; // 如果找不到，返回-1
}
void delete(HashTable *table, int key) {
    int index = hash(key);
    Node *list = table->list[index];
    Node *prev = NULL;
    while (list) {
        if (list->key == key) {
            if (prev) {
                prev->next = list->next;
            } else {
                table->list[index] = list->next;
            }
            free(list);
            return;
        }
        prev = list;
        list = list->next;
    }
}
int main() {
    HashTable *table = createHashTable();
    insert(table, 1, 10);
    insert(table, 2, 20);
    insert(table, 3, 30);

    printf("Key: 2, Value: %d\n", search(table, 2));

    delete(table, 2);

    printf("Key: 2, Value: %d\n", search(table, 2));


    free(table);

    return 0;
}
