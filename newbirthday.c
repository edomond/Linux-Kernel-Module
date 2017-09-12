#include <linux/module.h>  
#include <linux/kernel.h>   
#include <linux/init.h>  
#include <linux/list.h>    
#include <linux/types.h>    
#include <linux/slab.h>    

#define NUMBER_OF_BIRTHDAYS    6

/* Birthday */
typedef struct _birthday {
    
    int day;
    int month;
    int year;
    struct list_head list;

}birthday;

/* Declare and initialize the head of the list. */
LIST_HEAD(birthday_list);


int birthdayList_init(void) {
    int i = 0;
    birthday *myptr;

    birthday *person;
    printk(KERN_INFO "Loading Module\n");
	
    /* Allocate 5 birthdays from kernel */
    for(i = 0; i < NUMBER_OF_BIRTHDAYS; i++) {
       
        person = kmalloc(sizeof(*person), GFP_KERNEL);

        /* Values for my linked list */
        person->day = 10 + i;
        person->month = 2 + i;
        person->year = 1997 + i;

        /* Initialize the list within the struct. */
        INIT_LIST_HEAD(&person->list);

        /* Add this struct to the tail of the list. */
        list_add_tail(&person->list, &birthday_list);

    }

    /* Go through the list and print the 5 different values. */

    list_for_each_entry(myptr, &birthday_list, list) {

        printk(KERN_INFO "Birthday: Month %d Day %d Year %d\n",
                myptr->month,
                myptr->day,
                myptr->year);
    }

           return 0;
}

/* Prints list and deletes it from th kernel's memory*/

void birthdayList_exit(void) {

    birthday *myptr; 
    birthday *next;

    printk(KERN_INFO "Removing Module\n");

    list_for_each_entry_safe(myptr, next, &birthday_list, list) {

        printk(KERN_INFO "Removing Birthday: Month %d Day %d Year %d\n",
                myptr->month,
                myptr->day,
                myptr->year);

        list_del(&myptr->list);
        /*free list memory*/
        kfree(myptr);
    
    }

    printk(KERN_INFO "Done!\n");

}

/* Macros for module entry/exit points. */
module_init(birthdayList_init);
module_exit(birthdayList_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BIRTHDAY MODULE");
MODULE_AUTHOR("Elisabeth Domond");
