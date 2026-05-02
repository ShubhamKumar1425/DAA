#include <stdio.h>
#include <stdlib.h>

/* ---- input item ---- */
typedef struct {
    char alphabet;
    int  frequency;
} SYMBOL;

/* ---- tree node ---- */
typedef struct Node {
    char ch;                // alphabet at leaf; '\0' for internal nodes
    int  freq;              // frequency (sum for internal nodes)
    int  seq;               // sequence number to break ties deterministically
    struct Node *left, *right;
} Node;

/* ---- Min-heap of Node* keyed by (freq, seq) ---- */
typedef struct {
    Node **a;
    int size, cap;
} MinHeap;

static int less(Node *x, Node *y) {
    if (x->freq != y->freq) return x->freq < y->freq;
    return x->seq < y->seq;               // tie-breaker keeps build deterministic
}

static MinHeap *heap_create(int cap) {
    MinHeap *h = (MinHeap*)malloc(sizeof(MinHeap));
    h->a = (Node**)malloc(sizeof(Node*) * cap);
    h->size = 0; h->cap = cap;
    return h;
}

static void heap_swap(Node **x, Node **y) { Node *t = *x; *x = *y; *y = t; }

static void heap_push(MinHeap *h, Node *v) {
    int i = h->size++;
    h->a[i] = v;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!less(h->a[i], h->a[p])) break;
        heap_swap(&h->a[i], &h->a[p]);
        i = p;
    }
}

static Node* heap_pop(MinHeap *h) {
    if (h->size == 0) return NULL;
    Node *minv = h->a[0];
    h->a[0] = h->a[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, m = i;
        if (l < h->size && less(h->a[l], h->a[m])) m = l;
        if (r < h->size && less(h->a[r], h->a[m])) m = r;
        if (m == i) break;
        heap_swap(&h->a[i], &h->a[m]);
        i = m;
    }
    return minv;
}

/* ---- Node helper ---- */
static Node* make_leaf(char ch, int freq, int seq) {
    Node *u = (Node*)malloc(sizeof(Node));
    u->ch = ch; u->freq = freq; u->seq = seq;
    u->left = u->right = NULL;
    return u;
}
static Node* make_internal(Node *l, Node *r, int seq) {
    Node *u = (Node*)malloc(sizeof(Node));
    u->ch = '\0'; u->freq = l->freq + r->freq; u->seq = seq;
    u->left = l; u->right = r;
    return u;
}

/* ---- Build Huffman tree from symbols ---- */
static Node* build_huffman(SYMBOL sym[], int n) {
    MinHeap *h = heap_create(2*n + 5);
    int seq = 0;

    // push all leaves
    for (int i = 0; i < n; ++i) {
        heap_push(h, make_leaf(sym[i].alphabet, sym[i].frequency, seq++));
    }

    // combine two min nodes each step
    while (h->size > 1) {
        Node *x = heap_pop(h);   // smallest
        Node *y = heap_pop(h);   // next smallest
        // x is left, y is right (keeps in-order stable)
        heap_push(h, make_internal(x, y, seq++));
    }

    Node *root = heap_pop(h);
    free(h->a); free(h);
    return root;
}

/* ---- In-order print: print only leaves (alphabets) ---- */
static void inorder_leaves(Node *u) {
    if (!u) return;
    inorder_leaves(u->left);
    if (u->left == NULL && u->right == NULL) {
        printf("%c  ", u->ch);   // two spaces to match sample style
    }
    inorder_leaves(u->right);
}

/* ---- (Optional) free tree ---- */
static void free_tree(Node *u) {
    if (!u) return;
    free_tree(u->left);
    free_tree(u->right);
    free(u);
}

int main(void) {
    int n;
    printf("Enter the number of distinct alphabets: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    SYMBOL *arr = (SYMBOL*)malloc(sizeof(SYMBOL) * n);

    printf("Enter the alphabets: \t");
    for (int i = 0; i < n; ++i) {
        scanf(" %c", &arr[i].alphabet);   // leading space skips any whitespace
    }

    printf("Enter its frequencies:\t");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i].frequency);
    }

    Node *root = build_huffman(arr, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorder_leaves(root);
    printf("\n");

    free_tree(root);
    free(arr);
    return 0;
}
