//dahin
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
void print_array(int n, int m, double a[][4]) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            printf("%8.2f ", a[i][j]); // 8 zaitai, 2 orongiin nariibchiltai kheblekh
        }
        printf("\n");
    }
}
bool all_positive(int n, double a[][4]) {
    for (int i=0; i<n-1; i++) {
        if (a[i][3]<0) {
            return false;
        }
    }
    return true;
}

void find_pivot(int n, int m, double a[][m], int *pivot_row, int *pivot_col, double *pivot_element) {
    int i, j;
    *pivot_row=-1;
    *pivot_col=-1;
    *pivot_element=0;

    // 1. Surug sul gishuun bukhii muriig olokh
    int selected_row=-1;
    for (i=0; i<n-1; i++) {
        if (a[i][m-1]<0) {  //Sul gishuun surug baikh
            selected_row=i;
            break; 
        }
    }

    //Khereb bukh sul gishuun eyreg baibal tulguur shiid n shuud sul gishuud n baina
    if (selected_row==-1) {
        printf("Bodlogiin khyazgaraltiin systemiin tulguur shiiduud n sul gishuud n baina\n");
        return;
    }

    // 2.Yalgagch baganiig songokh (Surug element bukhii bagniig olokh)
    for (j=0; j<m-1; j++) {
        if (a[selected_row][j]<0) {  //Surug coffisent bukhii bagana olokh
            *pivot_col=j;
            break; //Khamgiin ekhnii oldson baganiig songono
        }
    }

    //Khereb surug element oldoogui bol asuudal
    if (*pivot_col==-1) {
        printf("Songogdson murund surug element baikhgui baina\n");
        return;
    }

    // 3. Simplex hartsaa tootsolokh ba yalgagch muriig olokh
    double min_ratio=DBL_MAX;
    for (i=0; i<n-1; i++) {
        if (selected_row<=i) {
            if (a[i][*pivot_col]!=0) { // 0-eer huviarlakhaas zails khiikh
            double ratio=fabs(a[i][m-1]/a[i][*pivot_col]); //Module ashiglakh
            if (ratio<min_ratio) {
                min_ratio=ratio;
                *pivot_row=i;
            }
            } 
        }
        *pivot_row=selected_row;
    }


    //Khereb yalgagch mur oldooogui bol shiid baikhgui
    if (*pivot_row==-1) {
        printf("Shiid baikhgui (Bukh sul gishuud 0 esbel surug baina).\n");
        return;
    }

    // 4.Gol element olokh
    *pivot_element=a[*pivot_row][*pivot_col];

    printf("\nYalgagch mur: %d\n", *pivot_row + 1);
    printf("Yalgagch bagana: %d\n", *pivot_col + 1);
    printf("Gol element: %.2f\n", *pivot_element);
}

void jordan_transformation(int n, int m, int pivot_row, int pivot_col, double a[][m]) {
    double pivot=a[pivot_row][pivot_col];
    double temp[n][m];
    
    //Gol elemnt khuvirgalt
    temp[pivot_row][pivot_col]=1/pivot;
    
    //Busad elementiig huvirgalt
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (i==pivot_row && pivot_col!=j) {
                temp[i][j]=a[i][j]/pivot;
            } else if (j==pivot_col && pivot_row!=i) {
                temp[i][j]=-a[i][j]/pivot; //Gol elementiin bagand urbuug ashiglakh
            } else if (pivot_col!=j && pivot_row!=i){
                temp[i][j]=a[i][j]-(a[i][pivot_col]*a[pivot_row][j]/pivot);
            }
        }
    }
    
    // New khusnegt
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            a[i][j]=temp[i][j];
        }
    }
}


int main() {
    int n=4, m=4;
    double a[4][4]; // 4x4 hemjeetei husnegt
    bool b[4];
    
    printf("4 tegshitgeliin 3 khuvtsagch bolon sul gishuuniig oruulna uu:\n");
    for (int i=0; i<3; i++) {
        printf("%d-r tegshitgeliin koffitsentuudiig oruulna uu (a1 a2 a3 b):\n", i + 1);
        for (int j=0; j<4; j++) {
            scanf("%lf", &a[i][j]);
        }
    }
    
    printf("Zorilgiin funktsiin koffitsentuudiig oruulna uu (c1 c2 c3 d):\n");
    for (int j=0; j<4; j++) {
        scanf("%lf", &a[3][j]);
    }
    
    printf("\n Oruulsan husnegt:\n");
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            printf("%8.2f ", a[i][j]);
        }
        printf("\n");
    }
    printf("1-r husnegt:\n");
    print_array(n, m, a);

    int pivot_row, pivot_col;
    double pivot_element;
    int i=0;
    while (!all_positive(n, a)) {
        for (i=0; i<n; i++) {
            find_pivot(n, m, a, &pivot_row, &pivot_col, &pivot_element);
            if (pivot_row==-1 || pivot_col==-1) {
                break;
            }
            printf("\nPivot mur: %d, Pivot bagana: %d, Gol element: %.2f\n", pivot_row + 1, pivot_col + 1, pivot_element);
            jordan_transformation(n, m, pivot_row, pivot_col, a);
            printf("Shine husnegt:\n");
            print_array(n, m, a);
        }break;
        
    }


}
