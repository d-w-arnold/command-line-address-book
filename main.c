#include <stdio.h>

struct address {
    char street[128];
    char town[128];
    char country[128]; // TODO: (?) validate
};

struct contact {
    char firstName[128]; // TODO validate length
    char otherNames[128]; // TODO validate length
    char emailAddress[128]; // TODO: validate email address format on entry
    char telephone[128]; // TODO: validate telephone number format on entry
    struct address;
};

int getStdIn(int fun);

void invalidInput();

void printMenu();

void printSearchMenu();

void addContact();

void removeContact();

void searchFirstName();

void searchOtherNames();

void searchEmailAddress();

void searchTelephone();

void searchTown();

void searchCountry();

void writeRecords(); // Write records to file on exit

/**
 * The task is to create an Address Book in C or C++ (your choice).
 * You will see the fields we need in the attached spec
 *
 * You have 4 hours to do the task, but this may not be enough time to get everything done
 * to the level you like. So focus on writing good code and making the core functionality
 *
 * Where possible, please avoid using external libraries as we want to see your code,
 * not your ability to integrate libraries. Libraries that come with the language are permitted,
 * for example, using the STL Library in C++ is completely fine
 *
 * When you've finished, could you send me your code and include
 * a README which explains any bugs you know you have,
 * or problems you encountered - we know that bugs happen,
 * especially when you have to make something in just four hours,
 * so we like to see that you are aware of your errors.
 * Also in the README could you say how you would improve your program
 * e.g. if you had 2 weeks on this task, what would you do?
 *
 * When sending me your code there's a small chance my email client
 * will block it because it detects a script (for example) and thinks it is malicious.
 * If this happens, upload your code to a file sharing service like Dropbox and
 * send me the download link instead
 *
 * See PDF in project root directory for more details.
 *
 * @return return code
 */
int main() {
    // Reload records when the program next executes.
    char path[] = "/Users/David/Desktop/technical_test_Netduma/records.txt";
    printf("\n");
    printf("Loading records from '%s' ...\n", path);
    printf("\n");
    FILE *read;
    read = fopen(path, "r"); // Open read stream
    if (read == NULL) { // Defensive programming - checking to see if input file exists for reading.
        printf("*** No input file found ***\n");
    } else {
        printMenu();
        writeRecords();
    }
    fclose(read);

    return 0;
}

// Main menu of the command line address book.
void printMenu() {
    while (1) {
        printf("-- Welcome to your command line Address Book --\n");
        printf("-- (Main Menu) --\n");
        printf("Please choose an option:\n");
        printf("0: Exit\n");
        printf("1: Add a contact from Address Book\n");
        printf("2: Remove a contact from Address Book\n");
        printf("3: Search for a contact in the Address Book\n");
        printf("\n");
        switch(getStdIn(1)) {
            case 0:
                return;
            case 1:
                addContact();
                break;
            case 2:
                removeContact();
                break;
            case 3:
                printSearchMenu();
                break;
        }
        printf("\n");
    }
}

// Main menu for searching the records in the address book.
void printSearchMenu() {
    printf("-- (Search Menu) --\n");
    printf("Please choose which field to search by:\n");
    printf("0: Return to Main Menu\n");
    printf("1: First name\n");
    printf("2: Other names\n");
    printf("3: Email Address\n");
    printf("4: Telephone Number\n");
    printf("5: Town\n");
    printf("6: Country\n");
    printf("\n");
    switch(getStdIn(1)) {
        case 0:
            return;
        case 1:
            searchFirstName();
            break;
        case 2:
            searchOtherNames();
            break;
        case 3:
            searchEmailAddress();
            break;
        case 4:
            searchTelephone();
            break;
        case 5:
            searchTown();
            break;
        case 6:
            searchCountry();
            break;
    }
    printf("\n");
}

int getStdIn(int fun) {
    int n;
    int valid = 0;
    while (valid == 0) {
        printf("Type here: ");
        scanf("%d", &n);
        printf("\n");
        if (fun == 0) { // printMenu
            if (0 <= n && n <= 3) {
                valid = 1;
            } else if (n != '\n') { // Check for '\n' which proceeds a int from stdin.
                invalidInput();
            }
        } else if (fun == 1) { // printSearchMenu
            if (0 <= n && n <= 6) {
                valid = 1;
            } else if (n != '\n') { // Check for '\n' which proceeds a int from stdin.
                invalidInput();
            }
        }
    }
    return n;
}

void invalidInput() {
    printf("*** Invalid input, please try again ***\n");
    printf("\n");
}

void addContact() {
    printf("addContact\n");
}

void removeContact() {
    printf("removeContact\n");
}

void searchFirstName() {
    printf("searchFirstName\n");
}

void searchOtherNames() {
    printf("searchOtherNames\n");
}

void searchEmailAddress() {
    printf("searchEmailAddress\n");
}

void searchTelephone() {
    printf("searchTelephone\n");
}

void searchTown() {
    printf("searchTown\n");
}

void searchCountry() {
    printf("searchCountry\n");
}

// Write records to file on exit
void writeRecords() {
    printf("writeRecords\n");
}
