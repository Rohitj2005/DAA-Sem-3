#include <stdio.h>
#include <limits.h>

#define MAX 100

void optimalBST(float p[], float q[], int n) {
    float e[MAX][MAX], w[MAX][MAX];
    int root[MAX][MAX];
    
    for (int i = 0; i <= n; i++) {
        e[i][i] = q[i];
        w[i][i] = q[i];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
            
            for (int r = i + 1; r <= j; r++) {
                float t = e[i][r - 1] + e[r][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("Minimum expected cost of OBST: %.4f", e[0][n]);
}

int main() {
    int n;
    printf("Enter number of book IDs: ");
    scanf("%d", &n);

    int keys[MAX];
    float p[MAX], q[MAX];

    printf("Enter the sorted book IDs:");
    for (int i = 0; i < n; i++) scanf("%d", &keys[i]);

    printf("Enter probabilities of successful searches (pi):");
    for (int i = 0; i < n; i++) scanf("%f", &p[i]);

    printf("Enter probabilities of unsuccessful searches (qi):");
    for (int i = 0; i <= n; i++) scanf("%f", &q[i]);

    optimalBST(p, q, n);
    return 0;
}