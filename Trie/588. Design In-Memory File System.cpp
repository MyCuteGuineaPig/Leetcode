class FileSystem {
private: 
    struct File{
        unordered_map<string, File*> kids;
        unordered_map<string,string>content;
    };
    
public:
    File* sys;
    
    FileSystem() {
        sys = new File();
    }
    
    vector<string>Parse(string path){
        vector<string>res;
        string cur;
        for(int i = 1; i<path.size(); ++i){
            if(path[i] == '/'){
                res.push_back(cur);
                cur = "";
            }
            else
                cur+=path[i];
            
            if(i == path.size()-1)
                res.push_back(cur);
        }
        return res;
    }
    
    vector<string> ls(string path) {
        vector<string> paths = Parse(path);
        vector<string>res;
        
        auto tmp = sys;
        if(paths.empty()){ //if paths is empty(), it is directory
            for(auto it: tmp->kids)
                res.push_back(it.first);
            for(auto it: tmp->content)
                res.push_back(it.first);
            sort(res.begin(), res.end());
            return res;
        }
        
        for(int i = 0; i<(int)paths.size()-1; ++i){
            if(tmp->kids.count(paths[i]))
                tmp = tmp->kids[paths[i]];
            else
                return {};
        }
        if(tmp->kids.count(paths.back())){
            tmp = tmp->kids[paths.back()];
            for(auto it: tmp->kids)
                res.push_back(it.first);
            for(auto it: tmp->content)
                res.push_back(it.first);
        }
        else if(tmp->content.count(paths.back())){
            res.push_back(paths.back());
        }
        sort(res.begin(), res.end());
        return res;
    }
    
    void mkdir(string path) {
        vector<string> paths = Parse(path);
        auto tmp = sys;
        for(int i = 0; i<paths.size(); ++i){
            if(tmp->kids.count(paths[i])==0)
                tmp->kids[paths[i]] = new File();
            tmp = tmp->kids[paths[i]];
        }
    }
    
    void addContentToFile(string filePath, string content) {
        vector<string> paths = Parse(filePath);
        File* tmp = sys;
        for(int i = 0; i<(int)paths.size()-1; ++i){
            if(tmp->kids.count(paths[i])==0)
                tmp->kids[paths[i]] = new File();
            tmp = tmp->kids[paths[i]];
        }
        tmp->content[paths.back()] += content;
    }
    
    string readContentFromFile(string filePath) {
        vector<string> paths = Parse(filePath);
        File* tmp = sys;
        for(int i = 0; i<(int)paths.size()-1; ++i){
            if(tmp->kids.count(paths[i])==0)
                return {};
            tmp = tmp->kids[paths[i]];
        }
        
        return tmp->content[paths.back()];
    }
};




class FileSystem {
private:
    struct TrieNode {
        bool isFile;
        string content;
        unordered_map<string, TrieNode *> children;
        TrieNode() : isFile(false) {}
    };

    TrieNode *root;
    
public:
    FileSystem() {
        root = new TrieNode();
    }
    
    vector<string> getStrs(string &path) {
        vector<string> ans;
        int i = 1, j = 1;
        while (j <= path.length()) {
            if (i != j && (j == path.length() || path[j] == '/')) {
                ans.push_back(path.substr(i, j - i));
                i = j + 1;
            }
            ++j;
        }
        return ans;
    }
    
    vector<string> ls(string path) {
        vector<string> strs = getStrs(path);
        TrieNode *curr = root;
        for (string &str : strs)
            curr = curr->children[str];
        
        if (curr->isFile)
            return {strs.back()};
        
        vector<string> ans;
        for (auto &p : curr->children)
            ans.push_back(p.first);
        sort(ans.begin(), ans.end());
        return ans;
    }
    
    void mkdir(string path) {
        vector<string> strs = getStrs(path);
        TrieNode *curr = root;
        for (string &str : strs) {
            if (!curr->children.count(str))
                curr->children[str] = new TrieNode();
            curr = curr->children[str];
        }
    }
    
    void addContentToFile(string filePath, string content) {
        vector<string> strs = getStrs(filePath);
        TrieNode *curr = root;
        for (string &str : strs) {
            if (!curr->children.count(str))
                curr->children[str] = new TrieNode();
            curr = curr->children[str];
        }
        curr->isFile = true;
        curr->content += content;
    }
    
    string readContentFromFile(string filePath) {
        vector<string> strs = getStrs(filePath);
        TrieNode *curr = root;
        for (string &str : strs)
            curr = curr->children[str];
        return curr->content;
    }
};