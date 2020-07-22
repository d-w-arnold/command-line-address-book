#include <stdio.h>
#include <string.h>

#define MAX 1000

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
    struct address address;
};

int loadRecords(FILE *read, char path[], struct contact *records);

int getStdIn(int fun);

void invalidInput();

void printMenu(struct contact *records, int *index);

void printSearchMenu();

void addContact(struct contact *records, int *index);

void removeContact(struct contact *records, int *index);

void invalidRemoveInput();

void searchFirstName();

void searchOtherNames();

void searchEmailAddress();

void searchTelephone();

void searchTown();

void searchCountry();

void writeRecords(char path[], struct contact *list, int index); // Write records to file on exit

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
    char path[] = "/Users/David/Desktop/technical_test_Netduma/records.txt";
    struct contact records[MAX];
    FILE *read;
    if ((read = fopen(path, "r")) != NULL) {
        int index;
        index = loadRecords(read, path, records);
        printMenu(records, &index);
        writeRecords(path, records, index);
    } else {
        printf("*** No input file found ***\n");
    }
    fclose(read);

    return 0;
}

// Reload records when the program next executes.
int loadRecords(FILE *read, char path[], struct contact *records) {
    printf("\n");
    printf("Loading records from '%s' ...\n", path);
    printf("\n");
    struct address tmpA;
    struct contact tmpC;
    int index = 0;
    while (fscanf(read, "%s %s %s %s %s %s %s", &tmpC.firstName, &tmpC.otherNames, &tmpC.emailAddress, &tmpC.telephone,
                  &tmpA.street, &tmpA.town, &tmpA.country) == 7) {
        tmpC.address = tmpA;
        records[index] = tmpC;
        index++;
    }
    return index; // The last index populated in the list of structs.
}

// Main menu of the command line address book.
void printMenu(struct contact *records, int *index) {
    while (1) {
        printf("-- Welcome to your command line Address Book --\n");
        printf("-- (Main Menu) --\n");
        printf("Please choose an option:\n");
        printf("0: Exit\n");
        printf("1: Add a contact from Address Book\n");
        printf("2: Remove a contact from Address Book\n");
        printf("3: Search for a contact in the Address Book\n");
        printf("\n");
        switch (getStdIn(1)) {
            case 0:
                return;
            case 1:
                addContact(records, index);
                break;
            case 2:
                removeContact(records, index);
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
    switch (getStdIn(1)) {
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

void addContact(struct contact *records, int *index) {
    printf("addContact\n");
    struct address tmpA;
    struct contact tmpC;
    printf("First Name: ");
    scanf("%s", &tmpC.firstName);
    printf("Other Names: ");
    scanf("%s", &tmpC.otherNames);
    printf("Email Address: ");
    scanf("%s", &tmpC.emailAddress);
    printf("Telephone: ");
    scanf("%s", &tmpC.telephone);
    printf("(Address)\n");
    printf("Street: ");
    scanf("%s", &tmpA.street);
    printf("Town: ");
    scanf("%s", &tmpA.town);
    printf("Country: ");
    scanf("%s", &tmpA.country);
    printf("\n");
    tmpC.address = tmpA;
    int i = *index;
    records[i] = tmpC;
    *index = i + 1;
}

void removeContact(struct contact *records, int *index) {
    printf("removeContact\n");
    char email[128];
    printf("Email address of contact to be removed: ");
    scanf("%s", &email);
    int indexToRemove = -1;
    for (int i = 0; i < index; i++) {
        struct contact tmpC = records[i];
        if (strcmp(tmpC.emailAddress, email) == 0) {
            indexToRemove = i;
            break;
        }
    }
    while (1) {
        if (indexToRemove != -1) {
            int size = *index;
            for (int i = indexToRemove; i < size - 1; i++) {
                if (strcmp(records[i].emailAddress,"") == 0) {
                    break;
                }
                records[i] = records[i + 1];
            }
            int i = *index;
            *index = i - 1;
            break;
        } else {
            invalidRemoveInput();
        }
    }
}

void invalidRemoveInput() {
    printf("*** Cannot find matching contact, please try again ***\n");
    printf("\n");
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
void writeRecords(char path[], struct contact *list, int index) {
    printf("writeRecords\n");
    FILE *write;
    if ((write = fopen(path, "w")) != NULL) {
        for (int i = 0; i < index; i++) {
            struct contact tmpC = list[i];
            struct address tmpA = tmpC.address;
            fprintf(write, "%s %s %s %s %s %s %s\n", &tmpC.firstName, &tmpC.otherNames, &tmpC.emailAddress,
                    &tmpC.telephone,
                    &tmpA.street, &tmpA.town, &tmpA.country);
        }
    } else {
        printf("*** No file to write to ***\n");
    }
}
