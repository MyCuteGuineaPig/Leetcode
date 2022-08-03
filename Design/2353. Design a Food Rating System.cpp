class FoodRatings {
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for(int i = 0; i<foods.size(); ++i){
            ratings_[cuisines[i]][ratings[i]].insert(foods[i]);
            categories_[foods[i]]  = {cuisines[i], ratings[i]};
        }
    }
    
    void changeRating(string food, int newRating) {
        string category = categories_[food].first; 
        int oldrating =  categories_[food].second; 
        ratings_[category][oldrating].erase(food);
        if (ratings_[category][oldrating].empty()) {
            ratings_[category].erase(oldrating);
        }
        ratings_[category][newRating].insert(food);
        categories_[food] = {category, newRating};
    }
    
    string highestRated(string cuisine) {
        return *((*(ratings_[cuisine]).rbegin()).second).begin();
    }
private: 
    unordered_map<string,map<int, set<string>>>ratings_;
    unordered_map<string,pair<string,int>>categories_;
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */


class FoodRatings {
public:
    unordered_map<string, set<pair<int, string>>> cuisine_ratings;
    unordered_map<string, string> food_cuisine;
    unordered_map<string, int> food_rating;
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for (int i = 0; i < foods.size(); ++i) {
            cuisine_ratings[cuisines[i]].insert({ -ratings[i], foods[i] });
            food_cuisine[foods[i]] = cuisines[i];
            food_rating[foods[i]] = ratings[i];
        }
    }
    void changeRating(string food, int newRating) {
        auto &cuisine = food_cuisine.find(food)->second;
        cuisine_ratings[cuisine].erase({ -food_rating[food], food });
        cuisine_ratings[cuisine].insert({ -newRating, food });
        food_rating[food] = newRating;
    }
    string highestRated(string cuisine) {
        return begin(cuisine_ratings[cuisine])->second;
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */