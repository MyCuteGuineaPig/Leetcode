class OrderManagementSystem {
public:
    OrderManagementSystem() {
        
    }
    
    void addOrder(int orderId, string orderType, int price) {
        price_to_id[price][orderType].insert(orderId);
        order_to_price[orderId] = {price, orderType};
    }
    
    void modifyOrder(int orderId, int newPrice) {
        auto[old_price, type] =  order_to_price[orderId];
        if (old_price == newPrice) return;
        order_to_price[orderId] = {newPrice, type};
        price_to_id[old_price][type].erase(orderId);
        price_to_id[newPrice][type].insert(orderId);
    }
    
    void cancelOrder(int orderId) {
        auto[price, type]= order_to_price[orderId];
        order_to_price.erase(orderId);
        price_to_id[price][type].erase(orderId);
        if (price_to_id[price][type].empty()) {
            price_to_id[price].erase(type);
        }
    }
    
    vector<int> getOrdersAtPrice(string orderType, int price) {
        return vector<int>(price_to_id[price][orderType].begin(), price_to_id[price][orderType].end());
    }

private:
    unordered_map<int, unordered_map<string, unordered_set<int>>> price_to_id;
    unordered_map<int, pair<int, string>> order_to_price;
};
