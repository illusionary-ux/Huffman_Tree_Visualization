#include<iostream>
using namespace std;

#include <iostream>
#include <cstring>

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

// 递归生成哈夫曼编码
void generateCodes(HuffmanNode *root, const char *code, char huffmanCodes[256][256])
{
    if (!root)
        return;
    if (root->ch != 0)
    { // 叶子节点
        strcpy(huffmanCodes[root->ch], code);
    }
    char leftCode[256], rightCode[256];
    strcpy(leftCode, code);
    strcat(leftCode, "0");
    generateCodes(root->left, leftCode, huffmanCodes);

    strcpy(rightCode, code);
    strcat(rightCode, "1");
    generateCodes(root->right, rightCode, huffmanCodes);
}

// 哈夫曼编码
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
        // 找到频率最小的两个节点
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

        // 合并两个最小频率的节点
        HuffmanNode *left = nodes[min1];
        HuffmanNode *right = nodes[min2];
        HuffmanNode *mergedNode = new HuffmanNode(left->freq + right->freq, left, right);

        // 将合并后的节点替换原来的两个节点
        nodes[min1] = mergedNode;
        nodes[min2] = nodes[nodeCount - 1];
        nodeCount--;
    }

    // 根节点
    HuffmanNode *root = nodes[0];
    generateCodes(root, "", huffmanCodes);
}

// 哈夫曼解码
void huffmanDecoding(const char *encodedStr, char *decodedStr, HuffmanNode *root)
{
    int i = 0, j = 0;
    HuffmanNode *current = root;

    while (encodedStr[i] != '\0')
    {
        // 遍历编码字符串
        if (encodedStr[i] == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        // 如果当前节点是叶子节点，输出字符并重置到根节点
        if (current->ch != 0)
        {
            decodedStr[j++] = current->ch;
            decodedStr[j] = '\0';
            current = root; // 返回根节点重新开始
        }
        i++;
    }
}

int main()
{
    freopen("word.in", "r", stdin);
    freopen("result.out", "w", stdout);
    char input[1024];
    scanf("%s", input);

    char huffmanCodes[256][256] = {0};
    huffmanEncoding(input, huffmanCodes);

    // 输出哈夫曼编码
    //cout << "\n哈夫曼编码结果：\n";
    //printf("\n哈夫曼编码结果：\n");
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
    //printf("\n编码后的字符串: %s\n", encodedStr);

    // 用户输入待解码的字符串
    /*char toDecode[1024];
    cout << "\n请输入一段编码过的文字进行哈夫曼解码：";
    cin.getline(toDecode, 1024);*/

    // 创建哈夫曼树以便解码
    HuffmanNode *nodes[256];
    int freq[256] = {0};
    int nodeCount = 0;

    // 计算频率并创建节点
    for (int i = 0; i < strlen(input); i++)
    {
        freq[(unsigned char)input[i]]++;
    }

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

    // 获取根节点
    HuffmanNode *root = nodes[0];

    // 解码
    char decodedStr[1024] = {0};
    // huffmanDecoding(toDecode, decodedStr, root);

    //cout << "\n解码后的字符串: " << decodedStr << endl;
    //printf("\n解码后的字符串: %s\n", decodedStr);
    return 0;
}
