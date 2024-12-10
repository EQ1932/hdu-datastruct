#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CHAR 256  // 最大字符集大小

// 哈夫曼树的节点
typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

// 哈夫曼编码的表
char huffmanCodes[MAX_CHAR][MAX_CHAR];

// 最小堆的结构体
typedef struct MinHeap {
    int size;
    Node* heap[MAX_CHAR];
} MinHeap;

// 优先队列（最小堆）操作
MinHeap* createMinHeap() {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    return heap;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->heap[left]->frequency < heap->heap[smallest]->frequency)
        smallest = left;
    if (right < heap->size && heap->heap[right]->frequency < heap->heap[smallest]->frequency)
        smallest = right;
    
    if (smallest != idx) {
        swap(&heap->heap[idx], &heap->heap[smallest]);
        heapify(heap, smallest);
    }
}

Node* extractMin(MinHeap* heap) {
    if (heap->size <= 0)
        return NULL;
    
    Node* root = heap->heap[0];
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    
    return root;
}

void insertMinHeap(MinHeap* heap, Node* node) {
    heap->size++;
    int idx = heap->size - 1;
    heap->heap[idx] = node;

    while (idx && heap->heap[idx]->frequency < heap->heap[(idx - 1) / 2]->frequency) {
        swap(&heap->heap[idx], &heap->heap[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

MinHeap* buildMinHeap(char* characters, int* frequencies, int n) {
    MinHeap* heap = createMinHeap();
    for (int i = 0; i < n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->character = characters[i];
        newNode->frequency = frequencies[i];
        newNode->left = newNode->right = NULL;
        insertMinHeap(heap, newNode);
    }
    return heap;
}

// 构建哈夫曼树
Node* buildHuffmanTree(char* characters, int* frequencies, int n) {
    MinHeap* heap = buildMinHeap(characters, frequencies, n);

    while (heap->size > 1) {
        Node* left = extractMin(heap);
        Node* right = extractMin(heap);
        
        Node* internalNode = (Node*)malloc(sizeof(Node));
        internalNode->character = '\0';  // 内部节点没有字符
        internalNode->frequency = left->frequency + right->frequency;
        internalNode->left = left;
        internalNode->right = right;
        
        insertMinHeap(heap, internalNode);
    }

    return extractMin(heap);
}

// 递归生成哈夫曼编码
void generateHuffmanCodes(Node* root, char* code, int top) {
    if (root->left) {
        code[top] = '0';
        generateHuffmanCodes(root->left, code, top + 1);
    }

    if (root->right) {
        code[top] = '1';
        generateHuffmanCodes(root->right, code, top + 1);
    }

    if (!root->left && !root->right) {
        code[top] = '\0';
        strcpy(huffmanCodes[root->character], code);
    }
}

// 编码
void encode(char* input, FILE* output) {
    for (int i = 0; input[i] != '\0'; i++) {
        fprintf(output, "%s", huffmanCodes[input[i]]);
    }
}

// 译码
void decode(Node* root, FILE* input, FILE* output) {
    Node* current = root;
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch == '0')
            current = current->left;
        else if (ch == '1')
            current = current->right;

        if (!current->left && !current->right) {
            fputc(current->character, output);
            current = root;
        }
    }
}

// 打印哈夫曼树
void printTree(Node* root, int indent) {
    if (root != NULL) {
        if (root->right) {
            printTree(root->right, indent + 4);
        }

        if (indent) {
            for (int i = 0; i < indent; i++)
                printf(" ");
        }

        if (root->character != '\0') {
            printf("%c: %d\n", root->character, root->frequency);
        } else {
            printf("*: %d\n", root->frequency);
        }

        if (root->left) {
            printTree(root->left, indent + 4);
        }
    }
}

int main() {
    // 输入字符集大小、字符和权值
    int n = 27;
    //printf("Enter number of characters: ");
    //scanf("%d", &n);

    //char characters[n];
    //int frequencies[n];
    
    //printf("Enter the characters and their frequencies:\n");
    //for (int i = 0; i < n; i++) {
        //scanf(" %c %d", &characters[i], &frequencies[i]);
    //}
    char characters[] = { ' ','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int frequencies[] = { 186,64, 13, 22, 32, 103, 21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 };
    // 构建哈夫曼树
    Node* root = buildHuffmanTree(characters, frequencies, n);

    // 生成哈夫曼编码
    char code[MAX_CHAR];
    generateHuffmanCodes(root, code, 0);

    // 存储哈夫曼树到文件
    FILE* treeFile = fopen("hfmTree", "w");
    if (treeFile == NULL) {
        printf("Error opening file hfmTree\n");
        return -1;
    }
    printTree(root, 0);
    fclose(treeFile);

    // 进行编码
    char input[] = "THIS PROGRAM IS MY FAVORITE";  // 示例输入
    FILE* codeFile = fopen("CodeFile", "w");
    encode(input, codeFile);
    fclose(codeFile);

    // 进行译码
    FILE* codeInput = fopen("CodeFile", "r");
    FILE* textOutput = fopen("TextFile", "w");
    decode(root, codeInput, textOutput);
    fclose(codeInput);
    fclose(textOutput);

    // 打印编码文件
    FILE* codePrinFile = fopen("CodePrin", "w");
    FILE* codeFileRead = fopen("CodeFile", "r");
    char c;
    int count = 0;
    while ((c = fgetc(codeFileRead)) != EOF) {
        fputc(c, codePrinFile);
        count++;
        if (count % 50 == 0) {
            fputc('\n', codePrinFile);
        }
    }
    fclose(codeFileRead);
    fclose(codePrinFile);

    return 0;
}



