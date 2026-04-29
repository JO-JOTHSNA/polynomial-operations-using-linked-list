#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node {
    int coef;
    int exp;
    struct node* next;
};

// Create new node
struct node* createNode(int coef, int exp) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Insert node in sorted order (descending exponent)
struct node* insertNode(struct node* head, int coef, int exp) {
    if (coef == 0) return head; // skip zero terms

    struct node* newNode = createNode(coef, exp);

    // Insert at beginning
    if (head == NULL || exp > head->exp) {
        newNode->next = head;
        return newNode;
    }

    struct node* temp = head;

    // Traverse to correct position
    while (temp->next != NULL && temp->next->exp > exp) {
        temp = temp->next;
    }

    // If same exponent exists ? add coefficients
    if (temp->next != NULL && temp->next->exp == exp) {
        temp->next->coef += coef;
        free(newNode);

        // Remove node if coefficient becomes 0
        if (temp->next->coef == 0) {
            struct node* del = temp->next;
            temp->next = del->next;
            free(del);
        }
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }

    return head;
}

// Create polynomial
struct node* createPolynomial() {
    struct node* head = NULL;
    int n, coef, exp;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coef, &exp);
        head = insertNode(head, coef, exp);
    }

    return head;
}

// Display polynomial
void displayPolynomial(struct node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    struct node* temp = head;

    while (temp != NULL) {
        if (temp->coef > 0 && temp != head)
            printf(" + ");
        else if (temp->coef < 0)
            printf(" - ");

        int absCoef = abs(temp->coef);

        if (temp->exp == 0)
            printf("%d", absCoef);
        else if (temp->exp == 1)
            printf("%dx", absCoef);
        else
            printf("%dx^%d", absCoef, temp->exp);

        temp = temp->next;
    }
    printf("\n");
}

// Add polynomials
struct node* addPolynomials(struct node* p1, struct node* p2) {
    struct node* result = NULL;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            result = insertNode(result, p1->coef + p2->coef, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            result = insertNode(result, p1->coef, p1->exp);
            p1 = p1->next;
        } else {
            result = insertNode(result, p2->coef, p2->exp);
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        result = insertNode(result, p1->coef, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        result = insertNode(result, p2->coef, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Main
int main() {
    struct node *poly1, *poly2, *result;

    printf("\n--- Polynomial Addition Using Linked List ---\n\n");

    printf("Enter Polynomial 1:\n");
    poly1 = createPolynomial();

    printf("\nEnter Polynomial 2:\n");
    poly2 = createPolynomial();

    printf("\nPolynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    result = addPolynomials(poly1, poly2);

    printf("Sum: ");
    displayPolynomial(result);

    return 0;
}
