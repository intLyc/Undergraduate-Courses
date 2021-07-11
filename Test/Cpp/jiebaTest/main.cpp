#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cppjieba/include/cppjieba/Jieba.hpp"
using namespace std;

const char *const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
const char *const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
const char *const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
const char *const IDF_PATH = "cppjieba/dict/idf.utf8";
const char *const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";

const int readFilesNum = 3; // ��ȡ�ļ��ĸ���
//const string readFiles[] = {"C3-Art0002.txt", "C3-Art0003.txt", "C3-Art0005.txt"}; // ��ȡ���ļ�
const string readFiles[] = {"a1.txt", "a2.txt", "a3.txt"}; // ��ȡ���ļ�
const string writeFile = "b.txt";                          // д����ļ�
const int topk = 5;                                        // Խ�߹ؼ���Խ��

class InvertedIndexPoint
{ // ���������ڵ���
public:
    string keyword;         // �ؼ���
    vector<string> fileVec; // ��Ӧ�ļ�vector
    InvertedIndexPoint() {} // Ĭ�Ϲ��캯��
    InvertedIndexPoint(string keyword, string filename)
    { // ���ݴ�����keyword�������filename����
        this->keyword = keyword;
        fileVec.push_back(filename);
    }
    void appendFile(string file)
    { // ����������ļ�
        // // �������
        // for (int i = 0; i < fileVec.size(); i++)
        // {
        //     if (file.compare(fileVec[i]) == 0)
        //     { // �ҵ�����ͬ�ļ�
        //         return;
        //     }
        // }
        fileVec.push_back(file);
    }
};

class InvertedIndexList
{ // ����������
public:
    vector<InvertedIndexPoint> list;                     //�ڵ�vector
    int getIndex(string keyword);                        // ���������Ƿ���ڣ������򷵻ض�Ӧ�±�
    void addKeyFile(string keyword, string filename);    // ��ӹؼ��ʺͶ�Ӧ�ļ�
    void getFilesVec(string keyword, vector<string> &v); // ���ҹؼ������ڵ��ļ�
    void printToFile(string filename);                   // ��ӡ���
};

int InvertedIndexList::getIndex(string keyword)
{ // ���������Ƿ���ڣ������򷵻ض�Ӧ�±꣬�����ڷ���-1
    for (int i = 0; i < list.size(); i++)
    {
        if (!keyword.compare(list[i].keyword)) // ���
        {
            return i;
        }
    }
    return -1;
}

void InvertedIndexList::addKeyFile(string keyword, string filename)
{ // ��ӹؼ��ʺͶ�Ӧ�ļ�
    int index = getIndex(keyword);
    if (index != -1)
    { // �����ǰ����keyword��������ļ�
        list[index].appendFile(filename);
    }
    else
    { // ���������keyword���򴴽�����
        InvertedIndexPoint p(keyword, filename);
        list.push_back(p);
    }
}

void InvertedIndexList::getFilesVec(string keyword, vector<string> &v)
{ // ���ҹؼ������ڵ��ļ�
    int index = getIndex(keyword);
    if (index != -1)
    {
        // // ����vector
        // for (int i = 0; i < list[index].fileVec.size(); i++)
        // {
        //     v.push_back(list[index].fileVec[i]);
        // }
        v = list[index].fileVec;
    }
}

void InvertedIndexList::printToFile(string filename)
{ // ������ļ�
    ofstream out;
    out.open(filename);

    for (int i = 0; i < list.size(); i++)
    {
        out << list[i].keyword << ":";
        for (int j = 0; j < list[i].fileVec.size(); j++)
        {
            out << " " << list[i].fileVec[j];
        }
        out << endl;
    }

    out.close();
}

void extractFileKeywords(cppjieba::Jieba &jieba, vector<cppjieba::KeywordExtractor::Word> &keywords, string filename)
{ // ���ļ����йؼ��ʷ��������عؼ�������
    // ��ȡ�ļ�
    ifstream in;
    in.open(filename);
    string readString, s;
    while (!in.eof())
    {
        in >> s;
        readString += s;
    }
    in.close();

    jieba.extractor.Extract(readString, keywords, topk); // ִ�йؼ�����ȡ
}

int main(int argc, char const *argv[])
{
    // ����jieba��
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);

    // ����������������
    InvertedIndexList iil;

    // ��ÿ���ļ����йؼ��ʷ���
    for (int i = 0; i < readFilesNum; i++)
    {
        vector<cppjieba::KeywordExtractor::Word> fileKeywords;  // ��ȡ�ؼ��ε�vector
        extractFileKeywords(jieba, fileKeywords, readFiles[i]); // ���ļ������ؼ���

        for (int j = 0; j < fileKeywords.size(); j++)
        {
            iil.addKeyFile(fileKeywords[j].word, readFiles[i]); // ��ӹؼ��ʺ��ļ���

            // ���Զ�ȡ�ļ�ĳ�ֽ�
            ifstream iff;
            iff.open(readFiles[i]);
            iff.clear();
            iff.seekg(fileKeywords[j].offsets[0], ios::cur);
            string a;
            iff >> a;
            iff.close();
            ofstream off;
            off.open("x.txt", ios::app);
            off << readFiles[i] << ":" << fileKeywords[j].word << ":";
            off << a << endl;
            off.close();

            // // ����getFilesVec
            // vector<string> v;
            // iil.getFilesVec(fileKeywords[j].word, v);
            // ofstream testo;
            // testo.open("x.txt", ios::app);
            // testo << fileKeywords[j].word << ":";
            // for (int x = 0; x < v.size(); x++)
            // {
            //     if (v.size() > 0)
            //     {
            //         testo << " " << v[x];
            //     }
            // }
            // testo << endl;
            // testo.close();
        }

        // // ÿ���ļ��Ĺؼ����������
        // ofstream out;
        // out.open("x.txt", ios::app);
        // for (int j = 0; j < fileKeywords.size(); j++)
        // {
        //     out << fileKeywords[j].word << " ";
        // }
        // out << endl;
        // out.close();
    }

    iil.printToFile(writeFile); // �����ǰ��������

    return 0;
}
