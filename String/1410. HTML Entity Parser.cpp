class Solution {
public:
    string entityParser(string text) {    
        vector<pair<string,char>> encoded[8] = {{}, {}, {}, {}, {{"&gt;", '>'}, {"&lt;", '<'}},
            {{"&amp;", '&'}}, {{"&quot;", '"'}, {"&apos;", '\''}}, {{"&frasl;", '/'}}};
        int st = 0, p = 0;
        for (auto i = 0; i < text.size(); ++i, ++p) {
            text[p] = text[i];
            if (text[p] == '&')
                st = p;
            if (text[p] == ';') { 
                auto sz = p - st + 1;
                if (sz >= 4 && sz <= 7)
                    for (auto &[enc, dec] : encoded[sz]) {
                        if (text.compare(st, sz, enc) == 0) {
                            p = st;
                            text[p] = dec;
                            break;
                        }
                    }
                st = p + 1;
            }
        }
        text.resize(p);
        return text;
    }
};


class Solution {
public:
    string entityParser(string text) 
    {
        replaceString(text, "&quot;", "\"");
        replaceString(text, "&apos;", "\'");
        replaceString(text, "&amp;", "&");
        replaceString(text, "&gt;", ">");
        replaceString(text, "&lt;", "<");
        replaceString(text, "&frasl;", "/");
        return text;
    }

    void replaceString(string& text, const string& search, const string& replace)
    {
        auto i = 0;
        while((i = text.find(search, i)) != string::npos)
        {
            text.replace(i, search.length(), replace);
            i += replace.size();
        }
    }
};


//Suffix Trie

class Solution {
public:
    struct Trie {
        Trie * chars[26] = {};
        char symbol = 0;
        void insert(string &w, char ch, int p = 0) {
            if (p == w.size())
                symbol = ch;
            else {
                if (chars[w[p] - 'a'] == nullptr)
                    chars[w[p] - 'a'] = new Trie();
                chars[w[p] - 'a']->insert(w, ch, p + 1);
            }
        }
        char check(string &w, int p, int sz) {
            if (sz == 0 && symbol != 0)
                return symbol;
            if (w[p] < 'a' || w[p] > 'z' || chars[w[p] - 'a'] == nullptr)
                return 0;
            return chars[w[p] - 'a']->check(w, p + 1, sz - 1);
        }
    };
    vector<pair<string, char>> special = {{"gt", '>'}, {"lt", '<'},
        {"amp", '&'}, {"quot", '"'}, {"apos", '\''}, {"frasl", '/'}};
    
    string entityParser(string &text) {
        Trie root;
        for (auto &[str, ch] : special)
            root.insert(str, ch);
        int st = 0, p = 0;
        for (auto i = 0; i < text.size(); ++i, ++p) {
            text[p] = text[i];
            if (text[p] == '&')
                st = p;
            if (text[p] == ';') {
                auto ch = root.check(text, st + 1, p - st - 1);
                if (ch != 0) {
                    p -= p - st;
                    text[p] = ch;
                }
                st = p + 1; 
                //"&amp;amp;"
                // 避免 return &, 应该返回&amps; 在第一个&amp;后, 把st 放到1, 
            }
        }
        text.resize(p);
        return text;
    }
};