#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX 1000
#define CHAR_SIZE 128

struct address {
    char street[CHAR_SIZE];
    char town[CHAR_SIZE];
    char country[CHAR_SIZE];
};

struct contact {
    char firstName[CHAR_SIZE];
    char otherNames[CHAR_SIZE];
    char emailAddress[CHAR_SIZE];
    char telephone[CHAR_SIZE];
    struct address address;
};

int loadRecords(FILE *read, char path[], struct contact *records);

void printMenu(struct contact *records, int *index);

void printSearchMenu(struct contact *records, int *index);

void addContact(struct contact *records, int *index);

void removeContact(struct contact *records, int *index);

void searchFirstName(struct contact *records, const int *index);

void searchOtherNames(struct contact *records, const int *index);

void searchEmailAddress(struct contact *records, const int *index);

void searchTelephone(struct contact *records, const int *index);

void searchTown(struct contact *records, const int *index);

void searchCountry(struct contact *records, const int *index);

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
    char path[] = "/Users/David/Library/Mobile Documents/com~apple~CloudDocs/"
                  "projects/Command_Line_Address_Book/records.txt";
    struct contact records[MAX];
    FILE *read;
    if ((read = fopen(path, "r")) != NULL) {
        int index;
        index = loadRecords(read, path, records);
        printMenu(records, &index);
        writeRecords(path, records, index);
    } else {
        printf("\n");
        printf("*** No input file found, check line 75 in 'main.c' is the correct "
               "absolute path for './records.txt' ***\n");
        printf("\n");
    }
    fclose(read);

    return 0;
}

// Reload records when the program next executes.
int loadRecords(FILE *read, char path[], struct contact *records) {
    printf("\n");
    printf("Loading records from ...\n'%s'\n", path);
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

void invalidInput() {
    printf("\n");
    printf("*** Invalid input, please try again ***\n");
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

// Main menu of the command line address book.
void printMenu(struct contact *records, int *index) {
    while (1) {
        printf("-- Welcome to your command line Address Book --\n");
        printf("-- (Main Menu) --\n");
        printf("Please choose an option:\n");
        printf("0: Exit\n");
        printf("1: Add a contact to Address Book\n");
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
                printSearchMenu(records, index);
                break;
        }
        printf("\n");
    }
}

// Main menu for searching the records in the address book.
void printSearchMenu(struct contact *records, int *index) {
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
            searchFirstName(records, index);
            break;
        case 2:
            searchOtherNames(records, index);
            break;
        case 3:
            searchEmailAddress(records, index);
            break;
        case 4:
            searchTelephone(records, index);
            break;
        case 5:
            searchTown(records, index);
            break;
        case 6:
            searchCountry(records, index);
            break;
    }
    printf("\n");
}

int validateHelper(const char reg_exp[], char str[]) {
    regex_t preg;
    int rc;
    rc = regcomp(&preg, reg_exp, REG_EXTENDED | REG_NOSUB);
    if (rc != 0) {
        if (rc == REG_BADPAT || rc == REG_ECOLLATE)
            fprintf(stderr, "Bad Regex/Collate\n");
        if (rc == REG_ECTYPE)
            fprintf(stderr, "Invalid Char\n");
        if (rc == REG_EESCAPE)
            fprintf(stderr, "Trailing \\\n");
        if (rc == REG_ESUBREG || rc == REG_EBRACK)
            fprintf(stderr, "Invalid number/[] error\n");
        if (rc == REG_EPAREN || rc == REG_EBRACE)
            fprintf(stderr, "Paren/Bracket error\n");
        if (rc == REG_BADBR || rc == REG_ERANGE)
            fprintf(stderr, "{} content invalid/Invalid endpoint\n");
        if (rc == REG_ESPACE)
            fprintf(stderr, "Memory error\n");
        if (rc == REG_BADRPT)
            fprintf(stderr, "Invalid regex\n");
        fprintf(stderr, "%s: Failed to compile the regular expression:%d\n", __func__, rc);
    }
    rc = regexec(&preg, str, (size_t) 0, NULL, 0);
    if (rc == 0) {
        regfree(&preg);
        return 0;
    } else {
        regfree(&preg);
        return 1;
    }
}

int validateEmail(char str[]) {
    const char *reg_exp = "^([a-z0-9])(([-a-z0-9._])*([a-z0-9]))*@([a-z0-9])(([a-z0-9-])*([a-z0-9]))+(.([a-z0-9])([-a-z0-9_-])?([a-z0-9])+)+$"; // Email address regex
    return validateHelper(reg_exp, str);
}

int validateTelephone(char str[]) {
    const char *reg_exp = "^0[0-9]{10}$";
    return validateHelper(reg_exp, str);
}

void addContact(struct contact *records, int *index) {
    printf("-- (Adding contact) --\n");
    struct address tmpA;
    struct contact tmpC;
    while (1) {
        printf("First Name (2 or more characters): ");
        scanf("%s", &tmpC.firstName);
        if (strlen(tmpC.firstName) >= 2) {
            break;
        } else {
            invalidInput();
        }
    }
    while (1) {
        printf("Other Names (2 or more characters): ");
        scanf("%s", &tmpC.otherNames);
        if (strlen(tmpC.otherNames) >= 2) {
            break;
        } else {
            invalidInput();
        }
    }
    while (1) {
        printf("Email Address: ");
        scanf("%s", &tmpC.emailAddress);
        if (validateEmail(tmpC.emailAddress) == 0) {
            break;
        } else {
            invalidInput();
        }
    }
    while (1) {
        printf("Telephone (UK only, e.g. 07123456789): ");
        scanf("%s", &tmpC.telephone);
        if (validateTelephone(tmpC.telephone) == 0) {
            break;
        } else {
            invalidInput();
        }
    }
    printf("(Address)\n");
    printf("Street: ");
    scanf("%s", &tmpA.street);
    printf("Town: ");
    scanf("%s", &tmpA.town);
    printf("Country: ");
    scanf("%s", &tmpA.country); // TODO: (?) Add validation for countries
    printf("\n");
    tmpC.address = tmpA;
    int i = *index;
    records[i] = tmpC;
    *index = i + 1;
}

void validRemoveInput(char email[]) {
    printf("\n");
    printf("*** Removed contact with the email address: %s ***\n", email);
    printf("\n");
}

void invalidRemoveInput() {
    printf("\n");
    printf("*** Cannot find matching contact, please try again ***\n");
    printf("\n");
}

void removeContact(struct contact *records, int *index) {
    printf("-- (Removing contact) --\n");
    char email[CHAR_SIZE];
    int validRemoval = 0;
    while (validRemoval == 0) {
        printf("Email address of contact to be removed: ");
        scanf("%s", &email);
        printf("\n");
        int indexToRemove = -1;
        for (int i = 0; i < *index; i++) {
            struct contact tmpC = records[i];
            if (strcmp(tmpC.emailAddress, email) == 0) {
                indexToRemove = i;
                break;
            }
        }
        if (0 <= indexToRemove && indexToRemove <= *index) {
            for (int i = indexToRemove; i < *index - 1; i++) {
                if (strcmp(records[i].emailAddress, "") == 0) {
                    break;
                }
                records[i] = records[i + 1];
            }
            int i = *index;
            *index = i - 1;
            validRemoval = 1;
            validRemoveInput(email);
        } else {
            invalidRemoveInput();
        }
    }
}

void printResult(struct contact record) {
    struct address tmpA = record.address;
    printf("\n");
    printf("*** Result found ***\n");
    printf("\n");
    printf("First Name: %s\n", record.firstName);
    printf("Other Names: %s\n", record.otherNames);
    printf("Email Address: %s\n", record.emailAddress);
    printf("Telephone: %s\n", record.telephone);
    printf("(Address)\n");
    printf("Street: %s\n", tmpA.street);
    printf("Town: %s\n", tmpA.town);
    printf("Country: %s\n", tmpA.country);
    printf("\n");
}

void noResult() {
    printf("\n");
    printf("*** No matching result found ***\n");
    printf("\n");
}

void searchFirstName(struct contact *records, const int *index) {
    printf("-- (Search by first name) --\n");
    char str[CHAR_SIZE];
    printf("Type here: ");
    scanf("%s", &str);
    printf("\n");
    int found = 0;
    for (int i = 0; i < *index; i++) {
        struct contact tmpC = records[i];
        char *ptr = strstr(tmpC.firstName, str);
        if (strcmp(str, tmpC.firstName) == 0 || ptr != NULL) {
            printResult(tmpC);
            found = 1;
        }
    }
    if (found == 0) {
        noResult();
    }
}

void searchOtherNames(struct contact *records, const int *index) {
    printf("-- (Search by other names) --\n");
    char str[CHAR_SIZE];
    printf("Type here: ");
    scanf("%s", &str);
    printf("\n");
    int found = 0;
    for (int i = 0; i < *index; i++) {
        struct contact tmpC = records[i];
        char *ptr = strstr(tmpC.otherNames, str);
        if (strcmp(str, tmpC.otherNames) == 0 || ptr != NULL) {
            printResult(tmpC);
            found = 1;
        }
    }
    if (found == 0) {
        noResult();
    }
}

void searchEmailAddress(struct contact *records, const int *index) {
    printf("-- (Search by email address) --\n");
    char str[CHAR_SIZE];
    printf("Type here: ");
    scanf("%s", &str);
    printf("\n");
    int found = 0;
    for (int i = 0; i < *index; i++) {
        struct contact tmpC = records[i];
        char *ptr = strstr(tmpC.emailAddress, str);
        if (strcmp(str, tmpC.emailAddress) == 0 || ptr != NULL) {
            printResult(tmpC);
            found = 1;
        }
    }
    if (found == 0) {
        noResult();
    }
}

void searchTelephone(struct contact *records, const int *index) {
    printf("-- (Search by telephone) --\n");
    char str[CHAR_SIZE];
    printf("Type here: ");
    scanf("%s", &str);
    printf("\n");
    int found = 0;
    for (int i = 0; i < *index; i++) {
        struct contact tmpC = records[i];
        char *ptr = strstr(tmpC.telephone, str);
        if (strcmp(str, tmpC.telephone) == 0 || ptr != NULL) {
            printResult(tmpC);
            found = 1;
        }
    }
    if (found == 0) {
        noResult();
    }
}

void searchTown(struct contact *records, const int *index) {
    printf("-- (Search by town) --\n");
    char str[CHAR_SIZE];
    printf("Type here: ");
    scanf("%s", &str);
    printf("\n");
    int found = 0;
    for (int i = 0; i < *index; i++) {
        struct contact tmpC = records[i];
        char *ptr = strstr(tmpC.address.town, str);
        if (strcmp(str, tmpC.address.town) == 0 || ptr != NULL) {
            printResult(tmpC);
            found = 1;
        }
    }
    if (found == 0) {
        noResult();
    }
}

void searchCountry(struct contact *records, const int *index) {
    printf("-- (Search by telephone) --\n");
    char str[CHAR_SIZE];
    printf("Type here: ");
    scanf("%s", &str);
    printf("\n");
    int found = 0;
    for (int i = 0; i < *index; i++) {
        struct contact tmpC = records[i];
        char *ptr = strstr(tmpC.address.country, str);
        if (strcmp(str, tmpC.address.country) == 0 || ptr != NULL) {
            printResult(tmpC);
            found = 1;
        }
    }
    if (found == 0) {
        noResult();
    }
}

// Write records to file on exit
void writeRecords(char path[], struct contact *list, int index) {
    printf("\n");
    printf("Writing records to ...\n'%s'\n", path);
    printf("\n");
    FILE *write;
    if ((write = fopen(path, "w")) != NULL) {
        for (int i = 0; i < index; i++) {
            struct contact tmpC = list[i];
            struct address tmpA = tmpC.address;
            fprintf(write, "%s %s %s %s %s %s %s\n", &tmpC.firstName, &tmpC.otherNames, &tmpC.emailAddress,
                    &tmpC.telephone, &tmpA.street, &tmpA.town, &tmpA.country);
        }
    } else {
        printf("\n");
        printf("*** No file to write to ***\n");
        printf("\n");
    }
}
