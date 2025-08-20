#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 5  // B-tree derecesi
#define MIN_ENTRIES ((ORDER + 1) / 2 - 1)  // Minimum anahtar sayısı
#define MAX_ENTRIES (ORDER - 1)  // Maksimum anahtar sayısı

// B-tree düğüm yapısı
typedef struct BTNode {
    int keys[MAX_ENTRIES];          // Anahtarlar
    struct BTNode* children[ORDER]; // Alt düğümler
    int numKeys;                    // Mevcut anahtar sayısı
    bool isLeaf;                   // Yaprak düğüm mü?
} BTNode;

// B-tree yapısı
typedef struct {
    BTNode* root;
} BTree;

// Yeni düğüm oluşturma
BTNode* createNode(bool isLeaf) {
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    node->numKeys = 0;
    node->isLeaf = isLeaf;
    
    for (int i = 0; i < ORDER; i++) {
        node->children[i] = NULL;
    }
    
    return node;
}

// B-tree başlatma
BTree* createBTree() {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

// Düğümde arama
int searchInNode(BTNode* node, int key) {
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) {
        i++;
    }
    return i;
}

// B-tree'de arama
bool search(BTree* tree, int key) {
    return searchNode(tree->root, key);
}

bool searchNode(BTNode* node, int key) {
    if (node == NULL) return false;
    
    int i = searchInNode(node, key);
    
    // Anahtar bulundu
    if (i < node->numKeys && node->keys[i] == key) {
        return true;
    }
    
    // Yaprak düğümde bulunamadı
    if (node->isLeaf) {
        return false;
    }
    
    // Alt düğümde ara
    return searchNode(node->children[i], key);
}

// Düğümü böl
void splitChild(BTNode* parent, int index) {
    BTNode* fullChild = parent->children[index];
    BTNode* newChild = createNode(fullChild->isLeaf);
    
    // Orta noktayı bul
    int mid = MIN_ENTRIES;
    
    // Yeni düğüme sağ yarıyı kopyala
    newChild->numKeys = MIN_ENTRIES;
    for (int i = 0; i < MIN_ENTRIES; i++) {
        newChild->keys[i] = fullChild->keys[mid + 1 + i];
    }
    
    // Eğer yaprak değilse, alt düğümleri de kopyala
    if (!fullChild->isLeaf) {
        for (int i = 0; i <= MIN_ENTRIES; i++) {
            newChild->children[i] = fullChild->children[mid + 1 + i];
        }
    }
    
    // Eski düğümün boyutunu güncelle
    fullChild->numKeys = MIN_ENTRIES;
    
    // Ebeveynde yer aç
    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;
    
    // Orta anahtarı ebeveyne taşı
    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = fullChild->keys[mid];
    parent->numKeys++;
}

// Dolu olmayan düğüme ekleme
void insertNonFull(BTNode* node, int key) {
    int i = node->numKeys - 1;
    
    if (node->isLeaf) {
        // Yaprak düğümde doğru yere ekle
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        // Doğru alt düğümü bul
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        
        // Alt düğüm doluysa böl
        if (node->children[i]->numKeys == MAX_ENTRIES) {
            splitChild(node, i);
            if (node->keys[i] < key) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// B-tree'ye ekleme
void insert(BTree* tree, int key) {
    if (tree->root == NULL) {
        // İlk düğümü oluştur
        tree->root = createNode(true);
        tree->root->keys[0] = key;
        tree->root->numKeys = 1;
    } else {
        // Kök doluysa yeni kök oluştur
        if (tree->root->numKeys == MAX_ENTRIES) {
            BTNode* newRoot = createNode(false);
            newRoot->children[0] = tree->root;
            splitChild(newRoot, 0);
            tree->root = newRoot;
        }
        insertNonFull(tree->root, key);
    }
}

// Düğümden anahtar silme
void removeFromLeaf(BTNode* node, int index) {
    for (int i = index + 1; i < node->numKeys; i++) {
        node->keys[i - 1] = node->keys[i];
    }
    node->numKeys--;
}

// İç düğümden anahtar silme
void removeFromNonLeaf(BTNode* node, int index) {
    int key = node->keys[index];
    
    // Sol alt ağaçta yeterli anahtar varsa
    if (node->children[index]->numKeys >= MIN_ENTRIES + 1) {
        // Predecessor bul ve değiştir
        int pred = getPredecessor(node, index);
        node->keys[index] = pred;
        deleteKey(node->children[index], pred);
    }
    // Sağ alt ağaçta yeterli anahtar varsa
    else if (node->children[index + 1]->numKeys >= MIN_ENTRIES + 1) {
        // Successor bul ve değiştir
        int succ = getSuccessor(node, index);
        node->keys[index] = succ;
        deleteKey(node->children[index + 1], succ);
    }
    // Her iki alt ağaçta da minimum sayıda anahtar varsa birleştir
    else {
        merge(node, index);
        deleteKey(node->children[index], key);
    }
}

// Predecessor bulma
int getPredecessor(BTNode* node, int index) {
    BTNode* current = node->children[index];
    while (!current->isLeaf) {
        current = current->children[current->numKeys];
    }
    return current->keys[current->numKeys - 1];
}

// Successor bulma
int getSuccessor(BTNode* node, int index) {
    BTNode* current = node->children[index + 1];
    while (!current->isLeaf) {
        current = current->children[0];
    }
    return current->keys[0];
}

// Düğümleri birleştirme
void merge(BTNode* parent, int index) {
    BTNode* child = parent->children[index];
    BTNode* sibling = parent->children[index + 1];
    
    // Ebeveynden anahtarı al
    child->keys[MIN_ENTRIES] = parent->keys[index];
    
    // Kardeşten anahtarları kopyala
    for (int i = 0; i < sibling->numKeys; i++) {
        child->keys[i + MIN_ENTRIES + 1] = sibling->keys[i];
    }
    
    // Kardeşten alt düğümleri kopyala
    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->numKeys; i++) {
            child->children[i + MIN_ENTRIES + 1] = sibling->children[i];
        }
    }
    
    // Ebeveynden anahtarı kaldır
    for (int i = index + 1; i < parent->numKeys; i++) {
        parent->keys[i - 1] = parent->keys[i];
    }
    
    // Ebeveynden alt düğüm pointer'ını kaldır
    for (int i = index + 2; i <= parent->numKeys; i++) {
        parent->children[i - 1] = parent->children[i];
    }
    
    child->numKeys += sibling->numKeys + 1;
    parent->numKeys--;
    
    free(sibling);
}

// Anahtar silme
void deleteKey(BTNode* node, int key) {
    int index = searchInNode(node, key);
    
    // Anahtar bu düğümde bulundu
    if (index < node->numKeys && node->keys[index] == key) {
        if (node->isLeaf) {
            removeFromLeaf(node, index);
        } else {
            removeFromNonLeaf(node, index);
        }
    }
    // Anahtar bu düğümde yok
    else {
        if (node->isLeaf) {
            printf("Anahtar %d ağaçta bulunamadı.\n", key);
            return;
        }
        
        bool isLastChild = (index == node->numKeys);
        
        // Alt düğümde yeterli anahtar yoksa düzenle
        if (node->children[index]->numKeys < MIN_ENTRIES + 1) {
            fill(node, index);
        }
        
        // İndeks değişmiş olabilir
        if (isLastChild && index > node->numKeys) {
            deleteKey(node->children[index - 1], key);
        } else {
            deleteKey(node->children[index], key);
        }
    }
}

// Ağacı yazdırma
void printBTree(BTNode* node, int level) {
    if (node != NULL) {
        printf("Seviye %d: ", level);
        for (int i = 0; i < node->numKeys; i++) {
            printf("%d ", node->keys[i]);
        }
        printf("\n");
        
        if (!node->isLeaf) {
            for (int i = 0; i <= node->numKeys; i++) {
                printBTree(node->children[i], level + 1);
            }
        }
    }
}

// Test fonksiyonu
int main() {
    BTree* tree = createBTree();
    
    printf("B-Tree Örneği (Derece: %d)\n", ORDER);
    printf("==========================\n\n");
    
    // Test verileri ekleme
    int testData[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int dataSize = sizeof(testData) / sizeof(testData[0]);
    
    printf("Ekleme işlemleri:\n");
    for (int i = 0; i < dataSize; i++) {
        printf("%d ekleniyor...\n", testData[i]);
        insert(tree, testData[i]);
        printBTree(tree->root, 0);
        printf("\n");
    }
    
    printf("Arama işlemleri:\n");
    printf("12 aranıyor: %s\n", search(tree, 12) ? "Bulundu" : "Bulunamadı");
    printf("15 aranıyor: %s\n", search(tree, 15) ? "Bulundu" : "Bulunamadı");
    
    return 0;
}