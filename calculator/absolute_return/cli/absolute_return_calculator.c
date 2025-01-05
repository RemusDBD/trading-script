#include <stdio.h>

// Function to calculate percentage return
double calculateReturn(double oldValue, double newValue) {
    return ((newValue - oldValue) / oldValue) * 100;
}

// Function to display and calculate returns for the portfolio and indexes
void calculatePortfolioAndIndexReturns() {
    double portfolioOldValue, portfolioNewValue;
    double ixicOldValue, ixicNewValue;
    double spxOldValue, spxNewValue;
    double djiOldValue, djiNewValue;

    // Collect portfolio data from the user
    printf("Enter portfolio old value: ");
    scanf("%lf", &portfolioOldValue);
    printf("Enter portfolio new value: ");
    scanf("%lf", &portfolioNewValue);

    // Collect SPX data from the user
    printf("Enter SPX old close price: ");
    scanf("%lf", &spxOldValue);
    printf("Enter SPX new close price: ");
    scanf("%lf", &spxNewValue);

    // Collect IXIC data from the user
    printf("Enter IXIC old close price: ");
    scanf("%lf", &ixicOldValue);
    printf("Enter IXIC new close price: ");
    scanf("%lf", &ixicNewValue);

    // Collect DJI data from the user
    printf("Enter DJI old close price: ");
    scanf("%lf", &djiOldValue);
    printf("Enter DJI new close price: ");
    scanf("%lf", &djiNewValue);

    // Calculate returns
    double portfolioReturn = calculateReturn(portfolioOldValue, portfolioNewValue);
    double spxReturn = calculateReturn(spxOldValue, spxNewValue);
    double ixicReturn = calculateReturn(ixicOldValue, ixicNewValue);
    double djiReturn = calculateReturn(djiOldValue, djiNewValue);

    // Display results
    printf("\n==== Portfolio and Index Absolute Returns ====\n");
    printf("Portfolio : %.2f%%\n", portfolioReturn);
    printf("SPX : %.2f%%\n", spxReturn);
    printf("IXIC : %.2f%%\n", ixicReturn);
    printf("DJI : %.2f%%\n", djiReturn);
	printf("=============================================\n");
}

int main() {
    printf(" | Portfolio and Index Return Calculator | \n");
	printf(" > Author: RemusDBD < \n");
	printf(" ! Ensure opening this program with cmd not double clicks ! \n");
    printf("=============================================\n");
    
    calculatePortfolioAndIndexReturns();

    return 0;
}
