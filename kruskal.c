//
// Created by fitli on 08.05.22.
//
#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int start;
    int end;
    int cost;
};

struct Edge edges[1000000];
int components[1000000];
int component_sizes[1000000];

int get_component(int node) {
    if(components[node] == node) {
        return node;
    }
    int result = get_component(components[node]);
    components[node] = result;
    return result;
}

int cmp_edges(const void * elem1, const void * elem2) {
    return (*(struct Edge*) elem1).cost - (*(struct Edge*) elem2).cost;
}

void join_components(int comp1, int comp2) {
    if(component_sizes[comp1] > component_sizes[comp2]) {
        components[comp2] = comp1;
        component_sizes[comp1] += component_sizes[comp2];
    }
    else {
        components[comp1] = comp2;
        component_sizes[comp2] += component_sizes[comp1];
    }
}

int one_input() {
    int n, m;
    int a = scanf("%d %d", &n, &m);
    if(a <= 0) {
        return 0;
    }
    int orig_cost = 0;
    int optim_cost = 0;
    int num_unused_zeroes = 0;
    int minimal_edges = 0;

    for (int i = 0; i < n; i++) {
        components[i] = i;
        component_sizes[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].start, &edges[i].end, &edges[i].cost);
        orig_cost += edges[i].cost;
    }

    qsort(edges, m, sizeof(struct Edge), cmp_edges);

    for(int i = 0; i < m; i++) {
        int start = edges[i].start;
        int end = edges[i].end;
        int cost = edges[i].cost;

        int comp_start = get_component(start);
        int comp_end = get_component(end);
        if(comp_start == comp_end && cost >= 0) {
            if(edges[i].cost == 0) {
                num_unused_zeroes++;
            }
            continue;
        }

        join_components(comp_start, comp_end);
        optim_cost += cost;
        minimal_edges++;
    }

    //printf("%d\n", orig_cost - optim_cost);
    printf("%d %d %d\n", optim_cost, minimal_edges, minimal_edges + num_unused_zeroes);
    return 1;
}

int main() {
    while (one_input() > 0);
}