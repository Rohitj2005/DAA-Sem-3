#include <stdio.h>
#include <string.h>

#define MAX 100

int LRS(char str[]) {
    int n = strlen(str);
    int dp[MAX][MAX];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j)
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    int index = dp[n][n];
    char lrs[index + 1];
    lrs[index] = '\0'; 

    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (str[i - 1] == str[j - 1] && i != j) {
            lrs[--index] = str[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Longest Repeating Subsequence is: %s\n", lrs);
    return dp[n][n];
}

int main() {
    char str[] = "AABCBDC";
    printf("Length of Longest Repeating Subsequence: %d\n", LRS(str));
    return 0;
}
