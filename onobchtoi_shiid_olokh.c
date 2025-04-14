//Onovchtoi shiid olokh algoretm 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
void print_array(int n, int m, double a[][4]) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            printf("%f ", a[i][j]); // 8 zaitai, 2 orongiin nariibchiltai kheblekh
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
bool all_objective_positive(int m, double a[m]) {
    for (int j = 0; j < m - 1; j++) {
        if (a[j] > 0) {
            printf("zorilgiin funktsiin %d-r coffitsent eyreg baina \n",j+1);
            return false;
        }
        else if (a[j]<0) {
            printf("Zorilgiin funktsiin %d-r coffitsent surug baina \n",j+1);
        }
    }
    printf("Zorilgiin funktsiin coffitsentuud bugd eyereg bish baina.");
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
        i=0;
        printf("tulguur shiid n: ");
        for ( int i=0; i<n-1; i++) {
            printf("%8.2f",a[i][m-1]);
        }
        printf("\n");
        printf("zorilgiin funktsiin utga: %8.2f", a[n-1][m-1]);
        printf("\n");
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
    printf("simplex hartsaanuud: ");
    double z=a[0][m-1]/a[0][*pivot_col];
    printf("%f, ",z);
    for (i=0; i<n-1; i++) {
        if (selected_row<=i) {
            if (a[i][*pivot_col]!=0) { // 0-eer huviarlakhaas zails khiikh
            double ratio=(a[i][m-1]/a[i][*pivot_col]);
            if ( ratio>=0) {
               printf("%f, ",ratio);//Module ashiglakh
            if (ratio<min_ratio) {
                min_ratio=ratio;
                *pivot_row=i;
            } 
            }
            } 
        }
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
void two_pivot(int n, int m, double a[][m], int *pivot_row, int *pivot_col, double *pivot_element) {
    int i, j;
    *pivot_row=-1;
    *pivot_col=-1;
    *pivot_element=0;

    // 1. Eyreg koeffitsent bukhii baganiig olokh
    int selected_cols=-1;
    for (j=0; j<m-1; j++) {
        if (a[n-1][j]>0) {  //zorilgiin funktsiin koeffitsent eyreg baikh
            selected_cols=j;
            break; 
        }
    }

    //Khereb bukh koeffitsentuud surug baibal tulguur shiid n shuud onovchtoi shiid bolno
    if (selected_cols==-1) {
        printf("Bodlogiin khyazgaraltiin systemiin tulguur shiiduud onovchtoi shiiduud bolj baina\n");
        i=0;
        printf("onovchtoi shiid uud n: ");
        for ( int i=0; i<n-1; i++) {
            printf("%8.2f",a[i][m-1]);
        }
        printf("\n");
        printf("zorilgiin funktsiin utga: %8.2f", a[n-1][m-1]);
        printf("\n");
        return;
    }

    // 2.Yalgagch baganiig songokh (Eyreg koeffitsent bukhii bagniig olokh)
    for (j=0; j<m-1; j++) {
        for (i=0; i<n-1; i++) {
            if (a[i][selected_cols]>0) {  //eyereg coffisent bukhii muriig olokh
            *pivot_col=j;
            break; //yadaj neg eyereg element oldoj baibal khangalttai
        }
        }
    }

    //Khereb eyereg element oldoogui bol asuudal
    if (*pivot_col==-1) {
        printf("Songogdson bagand eyereg element baikhgui baina. \n Iimd zorilgiin funktsiin utga dooroosoo zaaglagdaagui baina\n");
        return;
    }
    // 3. Simplex hartsaa tootsolokh ba yalgagch muriig olokh
    double min_ratio=DBL_MAX;
    printf("simplex hartsaanuud: ");
    double z=a[0][m-1]/a[0][*pivot_col];
    printf("%f, ",z);
    for (i=0; i<n-1; i++) {
        if (selected_cols<=j) {
            if (a[i][*pivot_col]!=0) { // 0-eer huviarlakhaas zails khiikh
            double ratio=(a[i][m-1]/a[i][*pivot_col]);
            if ( ratio>=0) {
               printf("%f, ",ratio);//Module ashiglakh
            if (ratio<min_ratio) {
                min_ratio=ratio;
                *pivot_row=i;
            } 
            }
            } 
        }
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
    int n, m;
    printf("Zorilgiin funktsiig oruulaagui muriin toog oruulna uu: ");
    scanf("%d", &n);
    printf("Sul gishuuniig oruulaagui bagniin toog oruulna uu: ");
    scanf("%d", &m);
    int rows = n + 1;
    int cols = m + 1;
    double a[rows][cols];
    bool b[4];
    
    printf("%d simplex husnegtiin %d huvsagch bolon sul gishuuniig oruulna uu:\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("simplex husnegtiin %d-r muriin koeffitsentuudiig oruulna uu( suuliikhen sul gishuun):\n", i + 1);
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &a[i][j]);
        }
    }
    
    printf("Zorilgiin funktsiin koeffitsentuudiig oruulna uu:\n");
    for (int j = 0; j < cols; j++) {
        scanf("%lf", &a[n][j]);
    }
    
    printf("\n Oruulsan husnegt:\n");
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }
    printf("1-r husnegt:\n");
    print_array(rows, cols, a);

    int pivot_row, pivot_col;
    double pivot_element;
    int i=0;
    while (!all_positive(rows, a)) {
        for (i=0; i<rows; i++) {
            find_pivot(rows, cols, a, &pivot_row, &pivot_col, &pivot_element);
            if (pivot_row==-1 || pivot_col==-1) {
                break;
            }
            printf("\nPivot mur: %d, Pivot bagana: %d, Gol element: %.2f\n", pivot_row + 1, pivot_col + 1, pivot_element);
            jordan_transformation(rows, cols, pivot_row, pivot_col, a);
            printf("Shine husnegt:\n");
            print_array(rows, cols, a);
        }
        if (all_objective_positive(cols, a[n])) {
            printf("\nZorilgiin funktsiin buh koeffitsentuud surug bolson. Tulguur shiid oldlon.\n");
            } else {
                printf("\nZorilgiin funktsiin koeffitsentuud dund eyereg koeffitsentuud baina.\n");
            }
        for (int j=0; j<cols; j++) {
            two_pivot(rows, cols, a, &pivot_row, &pivot_col, &pivot_element);
            if (pivot_row==-1 || pivot_col==-1) {
                break;
            }
            jordan_transformation(rows, cols, pivot_row, pivot_col, a);
            printf("shine hunsegt:\n");
            print_array(rows, cols, a);
            if (all_objective_positive(cols, a[n])) {
                printf("\nZorilgiin funktsiin buh koeffitsentuud surug bolson tul Onovchtoi shiid oldson\n");
                printf("\n Onovchtoi shiiduud: ");
                for (int i = 0; i < rows-1; i++) {
                    printf("%lf ",a[i][m]);
                }
                printf("\n");
                printf("onovchtoi shiid ni x*=( x1=%lf; x2=0; x3=0; x4=%lf; x5=%lf )",a[0][m],a[1][m],a[2][m]);
                printf("Fmin=%lf",a[n][cols-1]);
                break;
            } else {
                printf("\nZorilgiin funktsiin koeffitsentuud dund eyereg koeffitsentuud baina.\n");
            }
        }
        
        break;
        
    }
    


}
