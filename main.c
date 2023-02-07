/**
 *Imanuel Chatur
 * Shopping List app
 * Feb 15
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Define constants
#define MAX 10
#define MIN 1
typedef struct item{
    int id;
    char name[10];
    double price;
    int quantity;
}Item;

typedef struct node{
    Item data;
    struct node *next;
}Node, *NodePtr;
//Nodes
NodePtr top = NULL, tail = NULL;
NodePtr cartList;

//Functions--------------
NodePtr makeNode();
void addItem();
void updateQuantity();
void deleteItemID();
void displayItems();
double computePayment();
void saveItems();
//------------------------

//Main program
int main(){
    bool loop = true;
    int option;
    char itemNames[15][15] = {"", "Carrot", "Apple", "Orange", "Parsnip", "Avocado", "Blueberry", "Cherry",
                              "Asparagus", "Cabbage", "Celery"};
    double itemPrice[15] = {0, 1.5, 2.25, 2.75, 1.25, .99, 1.25, 2.25, 2, 3.5, 1.25};
    int r;
    //Create random list
    for (int i = 0; i < MAX; ++i) {
        r = (rand() % (MAX - MIN + 1)) + MIN;
        printf(itemNames[r]);
        addItem(r, itemNames[r], itemPrice[r], 10);
    }

    while(loop){
        printf("---------------------------------\nWelcome to the Farmers Market!\n---------------------------------\n");
        printf("1. Insert Items\n2. Update Item Quantity\n3. Delete Item\n4. Display Items\n5. Compute Payment\n"
               "6. Save Items to a File\n7. Exit\nEnter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("What item do you want to add?");
                int id;
                scanf("%d", &id);
                addItem(id, itemNames[id], itemPrice[id], 1);
                break;
            case 2:
                updateQuantity();
                break;
            case 3:
                deleteItemID();
                break;
            case 4:
                displayItems();
                break;
            case 5:
                printf("Total is %.2f\n", computePayment());
                break;
            case 6:
                saveItems();
                break;
            case 7:
                loop = false;
                break;
        }
    }
    return 0;
}
//Create an empty node
NodePtr makeNode(){
    cartList =(NodePtr) malloc(sizeof(Node));
    cartList->next=NULL;
    return cartList;
}
//Add item to linked list
void addItem(int id, char name[10], double price, int quantity){
    //Create new node and insert data
    cartList = makeNode();
    (cartList->data).id = id;
    strcpy((cartList->data).name, name);
    (cartList->data).price = price;
    (cartList->data).quantity = quantity;

    //if top pointer is empty, set all 3 to the same
    if(top==NULL)
        top = tail = cartList;
    else { //Add next item to the end
        tail->next = cartList;
        tail = cartList;
    }
}
//Display linked list
void displayItems(){
    int count;
    if(top==NULL){
        printf("EMTPY");
    }else{
        cartList = top;
        printf("Item-ID\tItem-Name\tPrice\t   Quantity\n");
        while(cartList != NULL){
            printf("%5d%15s%14.2f %10d\n", (cartList->data).id,(cartList->data).name,
                   (cartList->data).price,(cartList->data).quantity);
            cartList = cartList->next;
        }
        printf("Total: $%.2f\n", computePayment());
    }
}
//Compute the total
double computePayment(){
    double total = 0;
    cartList = top;
    while(cartList != NULL){
        total+=(cartList->data.price) * cartList->data.quantity;
        cartList = cartList->next;
    }
    return total;
}
//Search for id in linked list
NodePtr search(int id){
    if(top == NULL) //return null if list empty
        return NULL;
    else{
        cartList = top;
        while(cartList != NULL){
            if((cartList->data.id) == id){
                return cartList;
            }
            cartList = cartList->next;
        }
        return NULL;
    }
}
//Update the quantity of an item
void updateQuantity(){
    int id;
    int quant;
    printf("Which item do you want to update? ");
    scanf("%d", &id);
    cartList = search(id);
    if(cartList == NULL)
        printf("Sorry, your cart is empty!");
    else{
        printf("update quantity amount: ");
        scanf("%d", &quant);
        cartList->data.quantity = quant;

    }
}
//Delete an item
void deleteItemID(){
    int id;
    printf("What do you wanna delete: ");
    scanf("%d", &id);

    NodePtr searchResult = search(id);
    if(searchResult == NULL)
        printf("No results");
    else{
        cartList = top;
        if(cartList->next == NULL){
            top = tail = NULL;
            free(cartList);
        }else {
            while (cartList->next != searchResult){
                cartList = cartList->next;
            }
            NodePtr temp = cartList->next;
            printf("REMOVED THING");
            free(temp);
        }
    }
}
//Save to reciepts
void saveItems(){
    FILE*fp;
    fp=fopen("reciept.txt", "w+");
    fputs("SHOPPING RECIEPT\n", fp);
    fputs("Item-ID\tItem-Name\tPrice\t   Quantity\n",fp);
    cartList = top;

    while(cartList != NULL){
        fprintf(fp,"%5d%15s%14.2f %10d\n",cartList->data.id,cartList->data.name,cartList->data.price,cartList->data.quantity);
        cartList=cartList->next;
    }
    fprintf(fp, "Total: $%.2f\n", computePayment());
    fclose(fp);
}