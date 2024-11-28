#include <stdio.h>
#include <stdlib.h>

struct listnode{
    int data;
    listnode* link;
};
listnode *head = NULL;

// implement the prototypes
listnode* Add(listnode* head, int x);
listnode* Delete(listnode* head, int deletePosition);
listnode* Insert(listnode* head, int insertNumber, int insertPosition);
void Edit(listnode* head, int editNumber, int editPosition);
listnode* Inverse(listnode* head);
int Length(listnode* );
listnode* Combine(listnode* head, listnode* head2);
void Show(listnode* head);

int main (){
    head = NULL; //initialize the head to NULL
    int choice, x, position;
    listnode* head2 = NULL;

    while(1) {
        printf("\nLinked List Operations:\n");
        printf("1. Add a node\n");
        printf("2. Delete a node\n");
        printf("3. Insert a node\n");
        printf("4. Edit a node\n");
        printf("5. Inverse the list\n");
        printf("6. Get length\n");
        printf("7. Combine two lists\n");
        printf("8. Show list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter number to add: ");
                scanf("%d", &x);
                head = Add(head, x);
                break;

            case 2:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                head = Delete(head, position);
                break;

            case 3:
                printf("Enter number to insert: ");
                scanf("%d", &x);
                printf("Enter position: ");
                scanf("%d", &position);
                head = Insert(head, x, position);
                break;

            case 4:
                printf("Enter new number: ");
                scanf("%d", &x);
                printf("Enter position: ");
                scanf("%d", &position);
                Edit(head, x, position);
                break;

            case 5:
                head = Inverse(head);
                printf("List inverted\n");
                break;

            case 6:
                printf("Length of list: %d\n", Length(head));
                break;

            case 7:
                printf("Creating second list for combining...\n");
                printf("Enter number to add to second list (enter -1 to stop): ");
                scanf("%d", &x);
                while(x != -1) {
                    head2 = Add(head2, x);
                    printf("Enter number (-1 to stop): ");
                    scanf("%d", &x);
                }
                head = Combine(head, head2);
                break;

            case 8:
                Show(head);
                break;

            case 9:
                printf("Exiting program\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

//adding a new node at the end of the list
listnode* Add(listnode* head, int x){
    listnode *temp = (listnode*)malloc(sizeof(listnode)); //allocate memory for the new node
    temp->data = x;
    temp->link = NULL;

    if (head == NULL){ //if the list is empty, the new node is the head
        head = temp;
        return head;
    }
    listnode *current = head;
    while (current->link != NULL){ //traverse the list to find the last node
        current = current->link;
    }
    current->link = temp; //link the last node to the new node
    return head;
}

listnode *Delete(listnode* head, int deletePosition){

    listnode *temp = head;
    listnode *prev = NULL; //pointer to the previous node

    if (deletePosition == 1){ //if the node to be deleted is the head
        head = temp->link;
        free(temp);
        return head;
    }

    for (int i = 1; temp != NULL && i < deletePosition - 1; i++){
        prev = temp;
        temp = temp->link;
    }   

    if (temp == NULL)
    {
        printf("Position does not exist\n");    
        return head;
    }

    prev->link = temp->link;
    free(temp);
    return head;
}

listnode *Insert(listnode* head, int insertNumber, int insertPosition){
    listnode *temp = (listnode*)malloc(sizeof(listnode));
    temp->data = insertNumber;
    temp->link = NULL;

    if (insertPosition == 1){
        temp->link = head;
        return head;
    }   

    listnode *current = head;
    for (int i = 1; i < insertPosition - 1 && current != NULL; i++){
        current = current->link;
    }
    
    if (current == NULL){
        printf("Invalid position\n");
        return head;
    }   

    temp->link = current->link;
    current->link = temp;

    return head;
}

void Edit(listnode* head, int editNumber, int editPosition){
    listnode *current = head;
    for (int i = 1; i < editPosition && current != NULL; i++){
        current = current->link;
    }

    if (current != NULL){
        current->data = editNumber;
    }   

    current->data = editNumber;
}   

listnode* Inverse(listnode* head){
    listnode *prev = NULL;
    listnode *current = head;
    listnode *next = NULL;  

    while (current != NULL){
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }

    return prev;
}

int Length(listnode* head){
    int count = 0;
    listnode *current = head;
    while (current != NULL){
        count++;
        current = current->link;
    }
    return count;
}   

listnode* Combine(listnode* head, listnode* head2){
    listnode *current = head;
    while (current->link != NULL){
        current = current->link;
    }
    current->link = head2;
    return head;
}

void Show(listnode* head){
    listnode *current = head;
    while (current != NULL){
        printf("%d->", current->data);
        if (current->link == NULL){
            printf("NULL");
        }
        current = current->link;
    }
    printf("\n");   
}    
