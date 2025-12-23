for(auto aa: dp)
{
    for(auto bb: aa){
        cout<< bb<<", ";
    }
    cout<<endl;
}


template<typename... Args> 
void printt(const Args&... args) {
    ((cout<< args << " "), ...);
    cout <<endl;
}


template <typename... Args>
void print_fmt(std::string_view fmt, Args&&... args) {
    std::cout << std::format(fmt, std::forward<Args>(args)...);
}

int main() {
    int x = 10;
    double y = 3.14159;
    std::string name = "Alice";

    print_fmt("x = {}, y = {:.2f}, name = {}\n", x, y, name);
}