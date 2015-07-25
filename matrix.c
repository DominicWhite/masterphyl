#include <stdio.h>

typedef struct partitionTag {
    int data_type, nchar, ntaxa;
    int *segments;
    float *states;
} partition;

partition new_partition(int d, int c, int t, int *segs, float *s){
    return (partition){.data_type=d, .ntaxa=t, .nchar=c, .segments=segs, .states=s};
}



typedef struct matrixTag {
    int ntaxa, npart;
    partition *partitions[10]; // discrete, continuous, and serial
} matrix;

matrix new_matrix(int t){
    return (matrix){.ntaxa=t, .npart=0, .partitions=NULL};
}


int add_partition(matrix *m, partition p){
    if (m->ntaxa != p.ntaxa){ // check that no. of taxa match
        printf("Numbers of taxa don't match\n");
        return 1;
    }
    // check that there is space for partitions in the matrix
    if (m->ntaxa > 10){
        printf("There are too many partitions (max 10)\n");
        return 1;
    }
    
    // check each taxon has the same number of characters
    
    // check that there are the right number of taxa
    
    // finally, add matrix
    m->partitions[m->npart] = &p; //pointer to partition struct
    printf("    Num. chars: %i\n", m->partitions[0]->nchar);
    printf("    First state: %f\n", *(m->partitions[0])->states );
    m->npart = m->npart + 1;
    
    return 0;
}


void print_matrix(matrix m){
    printf("Taxa:%i, Partitions: %i\n", m.ntaxa, m.npart);
    for(int p_count=0; p_count < m.npart; p_count++){
        printf("  Partition %i\n", p_count+1);
        printf("    Num. chars: %i\n", m.partitions[p_count]->nchar);
        printf("    First state: %f\n", *((m.partitions[p_count])->states) );
    }
}


void main(){
    int t = 10, c = 100;
    matrix m = new_matrix(t);
    print_matrix(m);
    int seg_counts[10] = {3,4,2};
    float ss[2][2] = {{1,2},{3,4}};
    partition pp = new_partition(0, 10, 10, &seg_counts[0], &ss[0][0]);
    add_partition(&m, pp);
    printf("Added partition\n");
    print_matrix(m);
    printf("\n");
}
