#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct HuffmanNode {
    char ch;
    int weight;
    HuffmanNode* left = nullptr;
    HuffmanNode* right = nullptr;

    HuffmanNode(char c, int w, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr) : ch(c), weight(w), left(l), right(r) {}
    HuffmanNode() = default;
};

struct comp {
    bool operator()(HuffmanNode* a, HuffmanNode* b) { return a->weight > b->weight; }
};

HuffmanNode* buildHuffmanTree(const vector<HuffmanNode*> nodes) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, comp> pq(nodes.begin(), nodes.end());
    while (pq.size() > 1) {
        auto r1 = pq.top();
        pq.pop();
        auto r2 = pq.top();
        pq.pop();
        pq.push(new HuffmanNode(0, r1->weight + r2->weight, r1, r2));
    }
    return pq.empty() ? nullptr : pq.top();
}

void genCodes(HuffmanNode* r, const string& code, map<char, string>& huffmanCode) {
    if (!r) return;
    if (r->ch) huffmanCode[r->ch] = code;
    else {
        if (r->left) genCodes(r->left, code + "0", huffmanCode);
        if (r->right) genCodes(r->right, code + "1", huffmanCode);
    }
}


/**
 * @brief 漂亮地打印树的结构
 * @param node 当前节点
 * @param prefix 前缀，用于绘制树形结构
 * @param isLeft 是否是左子节点
 */
void printTree(HuffmanNode* node, const string& prefix = "", bool isLeft = true) {
    if (node == nullptr) {
        return;
    }
    
    cout << prefix;
    cout << (isLeft ? "├──" : "└──" );

    // 打印节点信息
    if (node->ch != 'N') {
        // 叶子节点：打印字符和权重
        cout << "'" << node->ch << "' (" << node->weight << ")" << endl;
    } else {
        // 内部节点：只打印权重
        cout << "Node (" << node->weight << ")" << endl;
    }

    // 递归打印子节点
    printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
}


// --- 测试主函数 ---

int main() {
    cout << "--- 霍夫曼树构建测试 ---" << endl;

    // 1. 创建样本数据 (叶子节点)
    vector<HuffmanNode*> nodes = {
        new HuffmanNode('a', 45),
        new HuffmanNode('b', 13),
        new HuffmanNode('c', 12),
        new HuffmanNode('d', 16),
        new HuffmanNode('e', 9),
        new HuffmanNode('f', 5)
    };

    cout << "\n初始字符和权重:" << endl;
    for (const auto& node : nodes) {
        cout << "字符: " << node->ch << ", 权重: " << node->weight << endl;
    }

    // 2. 打印霍夫曼树结构
    HuffmanNode* root = buildHuffmanTree(nodes);
    cout << "\n霍夫曼树结构:" << endl;
    printTree(root, "", false);


    // 3. 生成并打印霍夫曼编码
    cout << "\n生成的霍夫曼编码:" << endl;
    map<char, string> huffmanCodes;
    genCodes(root, "", huffmanCodes);

    for (const auto& pair : huffmanCodes) {
        cout << "字符: '" << pair.first << "' -> 编码: " << pair.second << endl;
    }
}