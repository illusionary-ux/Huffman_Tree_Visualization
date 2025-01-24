#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

// 哈夫曼树的节点
struct HuffmanNode
{
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(int f, HuffmanNode *l, HuffmanNode *r) : ch(0), freq(f), left(l), right(r) {}
};

// 哈夫曼编码（从叶子到根）
void generateCodesFromLeafToRoot(HuffmanNode *root, char huffmanCodes[256][256])
{
    if (!root)
        return;

    vector<pair<char, string>> codes;          // 临时存储字符和编码
    vector<pair<HuffmanNode *, string>> stack; // 模拟栈 {节点, 当前路径编码}

    stack.push_back({root, ""});

    while (!stack.empty())
    {
        auto [node, path] = stack.back();
        stack.pop_back();

        if (node->ch != 0)
        { // 叶子节点
            string reversedCode = path;
            reverse(reversedCode.begin(), reversedCode.end());
            strcpy(huffmanCodes[node->ch], reversedCode.c_str());
        }

        if (node->left)
        {
            stack.push_back({node->left, path + "0"});
        }
        if (node->right)
        {
            stack.push_back({node->right, path + "1"});
        }
    }
}

// 哈夫曼树构建与编码
void huffmanEncoding(const char *input, char huffmanCodes[256][256])
{
    int freq[256] = {0};
    int length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        freq[(unsigned char)input[i]]++;
    }

    HuffmanNode *nodes[256];
    int nodeCount = 0;

    // 创建所有的哈夫曼树节点
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            nodes[nodeCount++] = new HuffmanNode((char)i, freq[i]);
        }
    }

    // 构建哈夫曼树
    while (nodeCount > 1)
    {
        int min1 = 0, min2 = 1;
        if (nodes[min1]->freq > nodes[min2]->freq)
        {
            swap(min1, min2);
        }

        for (int i = 2; i < nodeCount; i++)
        {
            if (nodes[i]->freq < nodes[min1]->freq)
            {
                min2 = min1;
                min1 = i;
            }
            else if (nodes[i]->freq < nodes[min2]->freq)
            {
                min2 = i;
            }
        }

        HuffmanNode *left = nodes[min1];
        HuffmanNode *right = nodes[min2];
        HuffmanNode *mergedNode = new HuffmanNode(left->freq + right->freq, left, right);

        nodes[min1] = mergedNode;
        nodes[min2] = nodes[nodeCount - 1];
        nodeCount--;
    }

    HuffmanNode *root = nodes[0];
    generateCodesFromLeafToRoot(root, huffmanCodes);
}

// 主程序
int main()
{
    freopen("word.in", "r", stdin);
    freopen("result.out", "w", stdout);
    char input[1024];
    //cout << "请输入一段文字进行哈夫曼编码：";
    //cin.getline(input, 1024);
    scanf("%s", input);
    char huffmanCodes[256][256] = {0};
    huffmanEncoding(input, huffmanCodes);

    // 输出哈夫曼编码
    //cout << "\n哈夫曼编码结果（从叶子到根）：\n";
    for (int i = 0; i < 256; i++)
    {
        if (huffmanCodes[i][0] != '\0')
        {
            cout << (char)i << ": " << huffmanCodes[i] << endl;
        }
    }

    // 编码字符串
    char encodedStr[1024] = {0};
    for (int i = 0; i < strlen(input); i++)
    {
        strcat(encodedStr, huffmanCodes[(unsigned char)input[i]]);
    }

    //cout << "\n编码后的字符串: " << encodedStr << endl;
    return 0;
}