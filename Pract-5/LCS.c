#include <stdio.h>
#include <string.h>

#define MAX 100

// Directions for path tracking
#define DIAG 1   // ↖
#define UP 2     // ↑
#define LEFT 3   // ←

typedef struct {
    int cost;
    int dir;
} Cell;

void printCostDirectionMatrix(Cell matrix[][MAX], int m, int n, char X[], char Y[]) {
    printf("Cost and Direction matrix:\n   ");
    printf("    ");
    for (int j = 0; j < n; j++) {
        printf("  %c  ", Y[j]);
    }
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i == 0)
            printf("  ");
        else
            printf("%c ", X[i-1]);

        for (int j = 0; j <= n; j++) {
            const char *c;  
            switch(matrix[i][j].dir) {
                case DIAG: c = "\\"; break;  
                case UP: c = "|"; break;
                case LEFT: c = "-"; break;
                default: c = " ";
            }
            printf("%2d%s   ", matrix[i][j].cost, c);
        }
        printf("\n");
    }
    printf("\n");
}


void printLCS(Cell matrix[][MAX], char X[], int m, int n) {
    int i = m, j = n;
    char lcs[MAX];
    int index = 0;

    while (i > 0 && j > 0) {
        if (matrix[i][j].dir == DIAG) {
            lcs[index++] = X[i-1];
            i--;
            j--;
        } else if (matrix[i][j].dir == UP) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS is: ");
    for (int k = index - 1; k >= 0; k--) {
        printf("%c", lcs[k]);
    }
    printf("\n");
}

int main() {
    char X[] = "AGCCCTAAGGGCTACCTAGCTT";
    char Y[] = "GACAGCCTACAAGCGTTAGCTTG";
    int m = strlen(X);
    int n = strlen(Y);
    Cell matrix[MAX][MAX];

    for(int i = 0; i <= m; i++) {
        matrix[i][0].cost = 0;
        matrix[i][0].dir = 0;
    }
    for(int j = 0; j <= n; j++) {
        matrix[0][j].cost = 0;
        matrix[0][j].dir = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                matrix[i][j].cost = matrix[i-1][j-1].cost + 1;
                matrix[i][j].dir = DIAG;
            } else if (matrix[i-1][j].cost >= matrix[i][j-1].cost) {
                matrix[i][j].cost = matrix[i-1][j].cost;
                matrix[i][j].dir = UP;
            } else {
                matrix[i][j].cost = matrix[i][j-1].cost;
                matrix[i][j].dir = LEFT;
            }
        }
    }

    printCostDirectionMatrix(matrix, m, n, X, Y);

    printf("Length of LCS: %d\n", matrix[m][n].cost);
    printLCS(matrix, X, m, n);

    return 0;
}
