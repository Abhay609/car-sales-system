#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constants
#define MAX_FEEDBACK_LENGTH 500
#define MAX_CUSTOMERS 120
#define CAR_MODELS 3
#define INITIAL_STOCK 10

char choice;
int i;
int p;

typedef struct {
    char customerName[90];
    int customerAge;
    char carModel[90];
    int carYear;
    float price;
    int isMember;
    float discountApplied;
    float discountValue;
     char purchaseDate[20];
    int starRating;
    char feedback[MAX_FEEDBACK_LENGTH];
} Sale;
Sale sales[MAX_CUSTOMERS];
int saleCount = 0;

//STOCK
char carModels[4][CAR_MODELS][90] = {
{"M4 COMPETITION", "G63", "PORSCHE 911"},
{"M4 COMPETITION", "G63", "PORSCHE 911"},
{"M4 COMPETITION", "G63", "PORSCHE 911"},
    {"M4 COMPETITION", "G63", "PORSCHE 911"}
};

float carPrice[4][CAR_MODELS] = {
{100000, 135000, 155000},
{95000, 130000, 135000},
{85000, 120000, 120000},
{75000, 110000, 110000}
};
int carYear[4] = {2025, 2024, 2023, 2022};
int carStock[4][CAR_MODELS] = {
{INITIAL_STOCK, INITIAL_STOCK, INITIAL_STOCK},
{INITIAL_STOCK, INITIAL_STOCK, INITIAL_STOCK},
{INITIAL_STOCK, INITIAL_STOCK, INITIAL_STOCK},
{INITIAL_STOCK, INITIAL_STOCK, INITIAL_STOCK}
};

//functions
void saveSalesData();
void loadSalesData();
void saveCarStock();
void loadCarStock();
void displayCarStocks();
void purchaseCar();
void displaySales();
void checkFeedbacks();
void sortStockByYearDescending();
void checkRating();
void giveFeedback();
void clearInputBuffer();
int main()
{
    loadSalesData();
    loadCarStock();

    do {
        system("clear");

        //main menu
        // greetings
        printf("Welcome to the ALV Car Sales office!\n\n");
        printf("MENU\n");
        printf("a.VIEW CAR STOCKS.\nb.CAR PURCHASING.\nc.SALES STATUS.\nd.CHECK STAR RATING.\ne.GIVE FEEDBACK\nf.CHECK CUSTOMER FEEDBACK.'\nx.EXIT.\n");
        int validChoice = 0;
        do {
            printf("Enter your choice (a, b, c, d,e,f x): ");
            if (scanf(" %c", &choice) == 1) {
                choice = tolower(choice);//for removing case sensitivity
                if (strchr("abcdefx", choice)) {
                    validChoice = 1;
                } else {
                    printf("Invalid input. Please enter one of the options: a, b, c, d, e, f or x.\n");
                }
            } else {
                printf("Invalid input. Please enter one of the options: a, b, c, d, e, f or x.\n");
                clearInputBuffer();
            }
        } while (!validChoice);


        switch (choice){
            case 'a':
               displayCarStocks();
                break;
            case 'b':
                purchaseCar();
                saveSalesData();
                saveCarStock();
                break;
            case 'c':
                displaySales();
            break;
            case 'd':
                checkRating();
            break;
            case 'e':
                giveFeedback();
                saveSalesData();
            break;
            case 'f':
                checkFeedbacks();
                break;
            case 'x':
                //exit option
                    printf("THANK YOU!\nHAVE A NICE DAY");
            break;
            default:
                printf("invalid choice");
        }
        if (choice == 'x') {
            printf("\n\n press enter to exit");
        }
        else {
            printf("\npress enter to return to the main menu\n");
        }
        getchar();

    } while (choice != 'x');


return 0;
}

// displaying stocks

void displayCarStocks() {
    sortStockByYearDescending();
    printf("     CAR STOCK     \n");
    for (i=0; i < 4; i++) {
        printf("Year: %d\n", carYear[i]);
        for (int j = 0; j < CAR_MODELS; j++) {
            printf("%s - %.2f (stock: %d)\n",carModels[i][j], carPrice[i][j], carStock[i][j]);
        }
    }
}

// arranging  the cars in descending order
void sortStockByYearDescending() {
    for (int pass = 0; pass < 3; pass++) {
        for (int current = 0; current < 3 - pass; current++) {
            if (carYear[current] < carYear[current + 1]) {

                int tempYr = carYear[current];
                carYear[current] = carYear[current + 1];
                carYear[current + 1] = tempYr;

                for (int modelIdx = 0; modelIdx < CAR_MODELS; modelIdx++) {

                    char tempModelName[90];
                    strcpy(tempModelName, carModels[current][modelIdx]);
                    strcpy(carModels[current][modelIdx], carModels[current + 1][modelIdx]);
                    strcpy(carModels[current + 1][modelIdx], tempModelName);

                    float tempCost = carPrice[current][modelIdx];
                    carPrice[current][modelIdx] = carPrice[current + 1][modelIdx];
                    carPrice[current + 1][modelIdx] = tempCost;

                    int tempStock = carStock[current][modelIdx];
                    carStock[current][modelIdx] = carStock[current + 1][modelIdx];
                    carStock[current + 1][modelIdx] = tempStock;
                }
            }
        }
    }
}

//displaying total cars sold and total cost of the cars that were sold
// Function to display all recorded car sales with totals
void displaySales() {
    if (saleCount == 0) {
        printf("\nThere are no car sales recorded yet.\n");
        return;
    }

    printf("\n======= Car Sales Report =======\n");
    printf("%-20s %-12s %-17s %-8s %s\n", "Customer Name", "Age", "Car Model", "Year", "Price (£)");

    float revenueTracker[CAR_MODELS] = {0};
    int unitTracker[CAR_MODELS] = {0};

    for (int idx = 0; idx < saleCount; idx++) {
        printf("%-20s %-12d %-17s %-8d £%.2f\n",
               sales[idx].customerName,
               sales[idx].customerAge,
               sales[idx].carModel,
               sales[idx].carYear,
               sales[idx].price);

        for (int m = 0; m < CAR_MODELS; m++) {
            if (strcmp(sales[idx].carModel, carModels[0][m]) == 0) {
                unitTracker[m]++;
                revenueTracker[m] += sales[idx].price;
                break;
            }
        }
    }

    // totals per model and overall
    printf("\n------- Totals by model -------\n");
    int totalUnits = 0;
    float totalRevenue = 0;
    for (int m = 0; m < CAR_MODELS; m++) {
        printf("%-17s %3d sold   £%.2f\n", carModels[0][m], unitTracker[m], revenueTracker[m]);
        totalUnits += unitTracker[m];
        totalRevenue += revenueTracker[m];
    }
    printf("%-17s %3d sold   £%.2f\n", "ALL MODELS", totalUnits, totalRevenue);
}


//function for buying cars
void purchaseCar() {
    if (saleCount >= MAX_CUSTOMERS) {
        printf("Maximum number of transactions have been made\n");
        return;
    }

    int yearChoice, modelChoice, purchaseCount;

    int validYearChoice = 0;
    while (!validYearChoice) {
        printf("Choose the year of manufacturing:\n1. 2025\n2. 2024\n3. 2023\n4. 2022\n");//year of manufacturing
        if (scanf("%d", &yearChoice) != 1 || yearChoice < 1 || yearChoice > 4) {
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            clearInputBuffer();
        } else {
            validYearChoice = 1;
        }
    }

    int validModelChoice = 0;
    while (!validModelChoice) {
        printf("Select the car model:\n1. M4 COMPETITION\n2. G63\n3. PORSCHE 911\n");// select car model
        if (scanf("%d", &modelChoice) != 1 || modelChoice < 1 || modelChoice > 3) {
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
            clearInputBuffer();
        } else {
            validModelChoice = 1;
        }
    }

    int validPurchaseCount = 0;
    while (!validPurchaseCount) {
        printf("How many units do you want to purchase? ");// amount of cars customer want to purchase
        if (scanf("%d", &purchaseCount) != 1 || purchaseCount <= 0 || purchaseCount > MAX_CUSTOMERS - saleCount) {
            printf("Invalid quantity. Please enter a valid number.\n");
            clearInputBuffer();
        } else if (purchaseCount > carStock[yearChoice - 1][modelChoice - 1]) {
            printf("Sorry, only %d units available in stock.\n", carStock[yearChoice - 1][modelChoice - 1]);
        } else {
            validPurchaseCount = 1;
        }
    }

    Sale newSale;
    clearInputBuffer();
    printf("Enter your name: ");// customer's name
    fgets(newSale.customerName, sizeof(newSale.customerName), stdin);
    newSale.customerName[strcspn(newSale.customerName, "\n")] = '\0';

    int validAge = 0;
    while (!validAge) {
        printf("Enter your age (1-100): ");// customer's age
        if (scanf("%d", &newSale.customerAge) != 1 || newSale.customerAge < 1 || newSale.customerAge > 100) {
            printf("Invalid age. Please enter a valid number between 1 and 100.\n");
            clearInputBuffer();
        } else {
            validAge = 1;
        }
    }

    int validMemberInput = 0;
    while (!validMemberInput) {
        printf("Are you a Car Club member? (1 for Yes, 0 for No): ");// conformation for car club member
        if (scanf("%d", &newSale.isMember) == 1 && (newSale.isMember == 0 || newSale.isMember == 1)) {
            validMemberInput = 1;
        } else {
            printf("Invalid input. Enter 1 for Yes or 0 for No.\n");
            clearInputBuffer();
        }
    }

    char confirm;
    printf("\nYou are purchasing %d unit(s) of %s (%d) at £%.2f each.\n",
           purchaseCount,
           carModels[yearChoice - 1][modelChoice - 1],
           carYear[yearChoice - 1],
           carPrice[yearChoice - 1][modelChoice - 1]);
    printf("Confirm purchase? (y/n): ");
    scanf(" %c", &confirm);
    if (tolower(confirm) != 'y') {
        printf("Transaction cancelled.\n");
        return;
    }

    int starRating = 0;
    int feedbackDecision = -1;
    char feedbackInput[MAX_FEEDBACK_LENGTH] = "No feedback given.";

    // take ratings from the customer
    while (feedbackDecision != 0 && feedbackDecision != 1) {
        printf("Would you like to give a star rating? (1 for Yes, 0 for No): ");
        if (scanf("%d", &feedbackDecision) != 1 || (feedbackDecision != 0 && feedbackDecision != 1)) {
            printf("Invalid input. Enter 1 or 0.\n");
            clearInputBuffer();
        }
    }

    if (feedbackDecision == 1) {
        while (starRating < 1 || starRating > 5) {
            printf("Rate your purchase experience (1 to 5 stars): ");
            if (scanf("%d", &starRating) != 1 || starRating < 1 || starRating > 5) {
                printf("Invalid rating. Enter a number between 1 and 5.\n");
                clearInputBuffer();
            }
        }
    }

    float totalCost = 0;
    for (p = 0; p < purchaseCount; p++) {
        Sale individualSale = newSale;
        strcpy(individualSale.carModel, carModels[yearChoice - 1][modelChoice - 1]);
        individualSale.carYear = carYear[yearChoice - 1];
        individualSale.price = carPrice[yearChoice - 1][modelChoice - 1];
        individualSale.discountApplied = 0;
        individualSale.discountValue = 0;

        if (individualSale.isMember == 1) {
            individualSale.discountApplied = 1;
            individualSale.discountValue = individualSale.price * 0.10;
            individualSale.price -= individualSale.discountValue;
        }

        individualSale.starRating = starRating;
        strcpy(individualSale.feedback, feedbackInput);

        sales[saleCount++] = individualSale;
        totalCost += individualSale.price;
    }

    carStock[yearChoice - 1][modelChoice - 1] -= purchaseCount;

    printf("Purchase successful! Total cost: £%.2f\n", totalCost);
}

//checking customer rating
void checkRating() {
        printf("\n======= CUSTOMER STAR RATINGS =======\n");
        int shown = 0;
        for (int i = 0; i < saleCount; i++) {
            if (sales[i].starRating > 0) {
                shown = 1;
                printf("%s - %s (%d): %d stars\n", sales[i].customerName, sales[i].carModel, sales[i].carYear, sales[i].starRating);
            }
        }
        if (!shown) {
            printf("No ratings available.\n");
        }
    }

//giving feedbacks
void giveFeedback() {
    if (saleCount == 0) {
        printf("No purchases found. You must purchase a car before giving feedback.\n");
        return;
    }

    char name[90];
    printf("Enter your name to give feedback: ");
    clearInputBuffer();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < saleCount; i++) {
        if (strcasecmp(sales[i].customerName, name) == 0) {
            if (strlen(sales[i].feedback) > 0 && strcmp(sales[i].feedback, "No feedback given.") != 0) {
                printf("You have already submitted feedback for %s (%d).\n", sales[i].carModel, sales[i].carYear);
                return;
            }

            found = 1;
            printf("Leave your feedback for %s (%d):\n", sales[i].carModel, sales[i].carYear);
            printf("Your feedback: ");
            fgets(sales[i].feedback, MAX_FEEDBACK_LENGTH, stdin);
            sales[i].feedback[strcspn(sales[i].feedback, "\n")] = '\0';
            printf("Thank you for your feedback!\n");
            break;
        }
    }

    if (!found) {
        printf("No matching customer record found.\n");
    }
}

// to display feedbacks given by a customer
void checkFeedbacks() {
    if (saleCount == 0) {
        printf("\nThere are no reviews yet. Be the first to leave your feedback!\n");
        return;
    }

    printf("\n========== CUSTOMER FEEDBACK ==========\n");

    int feedbackShown = 0;
    int feedbackNumber = 1;

    for (int i = 0; i < saleCount; i++) {
        if (strlen(sales[i].feedback) > 0 && strcmp(sales[i].feedback, "No feedback given.") != 0) {
            feedbackShown = 1;
            printf("\nFeedback #%d\n", feedbackNumber++);
            printf("Customer Name : %s\n", sales[i].customerName);
            printf("Car Model     : %s (%d)\n", sales[i].carModel, sales[i].carYear);
            printf("Feedback      : %s\n", sales[i].feedback);
        }
    }

    if (!feedbackShown) {
        printf("\nThere are currently no written feedback entries.\n");
    }
}


//storing the sales ccc
void saveSalesData() {
    FILE *file = fopen("sale_data.txt", "wb");
    if (!file) return;
    fwrite(&saleCount, sizeof(int), 1, file);
    fwrite(sales, sizeof(Sale), saleCount, file);
    fclose(file);
}

//displaying the previous data
void loadSalesData() {
    FILE *file = fopen("sale_data.txt", "rb");
    if (!file) return;
    fread(&saleCount, sizeof(int), 1, file);
    fread(sales, sizeof(Sale), saleCount, file);
    fclose(file);
}

// storing the car stocks
void saveCarStock() {
    FILE *file = fopen("car_stocks.txt", "wb");
    if (!file) return;
    fwrite(carStock, sizeof(carStock), 1, file);
    fclose(file);
}

//displaying the previous stocks
void loadCarStock() {
    FILE *file = fopen("car_stocks.txt", "rb");
    if (!file) return;
    fread(carStock, sizeof(carStock), 1, file);
    fclose(file);
}

// to flush out invalid inputs
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
