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