/*
 * This program is poc for list_head. Operations like adding , deleting, moving,
 * replacing nodes in data structure is done by using list.h's inbuilt
 * functions. Indeed its cool stuff to use, not only it reduces the
 * code redudancy but also provides an easy way to handle and play with linked
 * list.
 */


#include <stdio.h>
#include <stdlib.h>

#include "list.h"


/* cell_phone is our main structure with in which all info is stored */

typedef struct cell_phone {
	char brand[50];
	float price;
	char model_no[50];
	int ram_in_gb;
	struct list_head list1;
        int node_no;
} my_cell_phone;

/* cell_phone_handler is doing nothing but handling cell_phone data structure */

typedef struct cell_phone_handler {
    int nodecount;
    struct list_head list_handler;
} handle_t;

handle_t t1;

/* For Initializing handle_t variable. */

void init_handler () {
        t1.nodecount = 0;
        INIT_LIST_HEAD (&(t1.list_handler));
}

/* To initialize a new node */

void init_node (my_cell_phone * temp) {

        static int count = 0;

        printf("enter brand name : ");
	scanf("%s",&(temp->brand));
	
	printf("enter price : ");
	scanf("%f",&(temp->price));
	
	printf("enter model no. : ");
	scanf("%s",&(temp->model_no));
	
	printf("enter ram in gb : ");
	scanf("%d", &(temp->ram_in_gb));
        printf("\n");
        
        count++;
        temp->node_no = count;

	INIT_LIST_HEAD(&(temp->list1));
}

/* Allocating memory for my_cell_phone */

my_cell_phone *  memory_allocation () {
        my_cell_phone * temp = (my_cell_phone *) malloc(sizeof(my_cell_phone));
        init_node(temp);
        return temp;
}

/* Starting from Head, traverse untill end */

void traverse_node () {
        my_cell_phone * p1 = NULL;
        struct list_head * pos = NULL;
        
        printf ("\nTotal no. of nodes : %d\n", t1.nodecount);

        list_for_each (pos, &(t1.list_handler)) {
                p1 = list_entry (pos, my_cell_phone, list1);
                printf ("Current Node no. : %d\n", p1->node_no);
                printf("Brand Name : %s\n",p1->brand);
                printf ("Price : %f\n", p1->price);
                printf("Model No. : %s\n",p1->model_no);
                printf ("RAM (in gb) : %d\n", p1->ram_in_gb);
                printf ("\n");
        }

}

/* Adding new node in two ways : before head and after head */

int add_node () {

        int subchoice = 0;

        printf("\nPress 1 for adding node in head i.e. after head (HEAD -> NODE_LATEST -> ....-> NODE_OLDEST)\n");
        printf("Press 2 for adding node in tail i.e. before head ( NODE_LATEST <- ....<- NODE_OLDEST <- HEAD)\n ");
        scanf("%d", &subchoice);

        my_cell_phone * temp = memory_allocation();
            
        if (subchoice == 1) {
                list_add (&(temp->list1), &(t1.list_handler));
        }
        else if (subchoice == 2) {
                list_add_tail (&(temp->list1), &(t1.list_handler));
        }
        else {
                printf ("\nWrong choice\n");
                exit (0);
        }

        t1.nodecount++;

        return 1;
        
}

/* Replacing old node with the new one */

int replace_node () {
        int node_no = 0;
        int status = 0;
        my_cell_phone * m1 = NULL ;        
        my_cell_phone * temp_i = NULL;
        struct list_head * h1 = NULL;

        printf ("Enter the node which you want to replace\n");
        scanf ("%d", &node_no);

        printf ("Enter data in new node, by which you want to replace the old node\n");
        temp_i = memory_allocation();
        
        list_for_each (h1, &(t1.list_handler)) {
               m1 = list_entry (h1, my_cell_phone, list1);
               if (m1->node_no == node_no) {
                        temp_i->node_no = m1->node_no;
                        list_replace_init (h1, &(temp_i->list1));
                        free (m1);
                        status = 1;  
                        goto do_return;
               }
        }
        
        goto do_return;

do_return :
                return status;
}

/* Deleting the desired node on basis of node no. */

int delete_node () {
        int node_no;
        struct list_head * h1 = NULL;
        my_cell_phone * m1 = NULL ;        

        printf ("\nEnter the node number which you want to delete\n");
        scanf ("%d", &node_no);
        
        list_for_each (h1, &(t1.list_handler)) {
               m1 = list_entry (h1, my_cell_phone, list1);
               if (m1->node_no == node_no) {
                        list_del_init (h1);
                        free (m1);
                        return 1;
               } else {
                        printf ("Node not found\n");    
                        return 0;
               }
        }
}

/* Moving desired node to HEAD. Now the HEAD is pointing to moved node. */

int move_node () {
        int node_no = 0;
        int status = 0;
        struct list_head * h1 = NULL;
        my_cell_phone * m1 = NULL ;        

        printf ("Enter the node which you want to move\n");
        scanf ("%d", &node_no);

        list_for_each (h1, &(t1.list_handler)) {
               m1 = list_entry (h1, my_cell_phone, list1);
               if (m1->node_no == node_no) {
                    list_move (h1, &(t1.list_handler));
                    status = 1;  
                    goto do_return;
               }
        }
        
        goto do_return;

do_return :
                return status;
        
}

/* Displaying a menu, listing operations user can perform :)*/

int choice() {
        int choice = 0;
        int ret = 0 ;
        do {
                printf ("\nPress 1 to add node\n");
                printf ("Press 2 to delete node\n");
                printf ("Press 3 to move node\n");
                printf ("Press 4 to replace node\n");
                printf ("Press 5 to traverse linked list\n");
                printf ("Press 6 to exit\n");
                scanf ("%d",&choice);
        
                if (choice == 1)
                       ret = add_node ();
                else if (choice == 2) 
                        ret =  delete_node (); 
                else if (choice == 3) 
                        ret = move_node ();
                else if (choice == 4)
                        ret = replace_node ();
                else if (choice == 5)
                        traverse_node ();
                else if (choice == 6)
                        exit (1);

                goto out;

out :
        if (ret)
                printf ("Desired operation done successfully\n");
        else
                printf ("Node not found. Worries Not. Try again :)\n");
        } while (choice);


}

int main (){
        init_handler ();
	choice ();
}
