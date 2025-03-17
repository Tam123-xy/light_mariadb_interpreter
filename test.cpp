// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <string>
// #include <sstream>
// #include <variant>
// #include <algorithm>
// using namespace std;

// int main(){
//     int num;
//     string target ="VALUES(";
    
//     vector <string> word ={"customer",
//                             "(na",
//                             "me,add",
//                             "ress,id)VAL",
//                             "UES",
//                             "(xin",
//                             "yi",
//                             ",kuala",
//                             "lumpur,1);"};

//     string plus = word[0];
//     vector <string> result;

//     for (int i=0; i<word.size(); i++){
//         if(plus.find(target)!= string::npos){

//             size_t start = plus.find("VALUES(") + 7;
//             string values = plus.substr(start);
//             values = values.substr(0, values.size());
//             // cout << values<< " values";
//             num = i;
//             result.push_back(values);
//             break;
//         }
//         else{
//             plus+=word[i];
//         }

//     }

//     for(num; num<word.size(); num++){

//         if(num == word.size() -1){
//             string w = word[ word.size() -1];

//             size_t end = w.find(");");
//             string values = w.substr(0, end);
//             values = values.substr(0, values.size());
//             result.push_back(values);

//         }
//         else{
//             result.push_back(word[num]);
//         }
        
//     }

//     for(int i =0; i<result.size(); i++){
//         cout << result[i]<< endl;
//     }

// }

// vector<string> splitString(const string& str, char delimiter) {
//     vector<string> result;
//     stringstream ss(str);
//     string token;

//     while (getline(ss, token, delimiter)) {
//         if (!result.empty()) {
//             token = "," + token;  // Add back the delimiter except for the first element
//         }
//         result.push_back(token);
//     }

//     return result;
// }

// int main() {
//     string c, previous_c,r,plus ;
//     vector<string> abc;
//     // string vecc = "xinyi,kualalumpur,1";
    
//     vector<string> words = {"xin","yi",",kuala","lumpur,1"};
//     vector<string> vec = {"xinyi",",kualalumpur",",1"};

//     string result =words[0];
//     bool same=false;

   
    
//     for(int i=0; i<words.size();i++){
//         for(int j=0;j<vec.size();j++){

//             if(result.find(vec[j])!= string::npos){
//                 if(!same&& !c.empty()){
//                     int s = abc.size();
//                     if(c!= previous_c){
//                         abc.push_back(c);
//                         previous_c =c;
//                         c.clear();
//                     }
                    
//                 }
//                 result.clear();
//                 result = words[i];
//             }

            
//             else{
//                 if (i < words.size() - 1){
//                     result+=words[i+1];
//                     c= words[i]+ " "+words[i+1];
                   
//                 }
//                 same =false;
                
//             }
//         }
//     }

//     for(int i=0;i<abc.size();i++){
//         r+=abc[i];
//     }

//     // cout<<r;

    
// }



    


// int main() {
//     std::vector<std::string> cor_att = {"id", "name", "address"}; // 正确顺序
//     std::vector<std::string> att = {"name", "id", "address"};      // 乱序
//     std::vector<std::string> values = {"xinyi", "2", "kulai"};     // 对应 att

//     // 建立 att -> values 的映射
//     std::unordered_map<std::string, std::string> value_map;
//     for (size_t i = 0; i < att.size(); i++) {
//         value_map[att[i]] = values[i];
//     }

//     // 按 cor_att 的顺序重新排列 values
//     std::vector<std::string> sorted_values;
//     for (const auto& key : cor_att) {
//         sorted_values.push_back(value_map[key]);
//     }

//     // 输出结果
//     std::cout << "Sorted values: ";
//     for (const auto& v : sorted_values) {
//         std::cout << v << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }

// int main() {
//     string tablename = "Table 1";
//     std::vector<std::variant<std::string, std::vector<std::variant<int, std::string>>>> tables;

//     // 存储一个字符串
//     tables.push_back("Table 1");

//     // 存储一个包含整数和字符串的 2D 结构
//     tables.push_back(std::vector<std::variant<int, std::string>>{
//         42, "Alice", 25, "Bob"
//     });

//     if (get<string>(tables[0]) == tablename){
//         cout << "true'";
//     }

//     // 访问数据
//     for (const auto& item : tables) {
//         if (std::holds_alternative<std::string>(item)) {
//             std::cout << "String: " << std::get<std::string>(item) << std::endl;
//         } else if (std::holds_alternative<std::vector<std::variant<int, std::string>>>(item)) {
//             std::cout << "Table Data: ";
//             for (const auto& cell : std::get<std::vector<std::variant<int, std::string>>>(item)) {
//                 if (std::holds_alternative<int>(cell)) {
//                     std::cout << std::get<int>(cell) << " ";
//                 } else {
//                     std::cout << std::get<std::string>(cell) << " ";
//                 }
//             }
//             std::cout << std::endl;
//         }
//     }

//     return 0;
// }


// int main() {
//     std::vector<std::string> a = {"abc", "123", "1"};
//     std::vector<std::variant<int, std::string>> result;

//     for (int i = 0; i < a.size(); i++) {
//         if (i % 2 == 0) {
//             result.push_back(a[i]);  // 直接存 string
//         } else {
//             try {
//                 result.push_back(std::stoi(a[i]));  // 转换 string -> int
//             } catch (const std::exception& e) {
//                 std::cerr << "Error converting '" << a[i] << "' to int: " << e.what() << std::endl;
//             }
//         }
//     }

//     // 输出结果
//     for (const auto& item : result) {
//         std::visit([](const auto& value) { std::cout << value << " "; }, item);
//     }

//     return 0;
// }


// int main() {
//     std::vector<std::variant<std::string, std::vector<std::variant<int, std::string>>>> tables;

//     // 存储一个字符串
//     tables.push_back("Table 1");

//     // 存储一个包含整数和字符串的 2D 结构
//     tables.push_back(std::vector<std::variant<int, std::string>>{
//         42, "Alice", 25, "Bob"
//     });

//     // 访问数据
//     for (const auto& item : tables) {
//         if (std::holds_alternative<std::string>(item)) {
//             std::cout << "String: " << std::get<std::string>(item) << std::endl;
//         } else if (std::holds_alternative<std::vector<std::variant<int, std::string>>>(item)) {
//             std::cout << "Table Data: ";
//             for (const auto& cell : std::get<std::vector<std::variant<int, std::string>>>(item)) {
//                 if (std::holds_alternative<int>(cell)) {
//                     std::cout << std::get<int>(cell) << " ";
//                 } else {
//                     std::cout << std::get<std::string>(cell) << " ";
//                 }
//             }
//             std::cout << std::endl;
//         }
//     }

//     return 0;
// }

// int main() {
//     vector<string> a ={"abc","2","c","12"};
//     std::vector<std::variant<int, std::string>> result;

//   for(int i; i<a.size(); i++){
//     if(i%2==0){
//         result.push_back(a[i]);
//     }

//     else{
//         result.push_back(stoi(a[i]));
//     }
//   }

//     // 遍历输出
//     for (const auto& item : result) {
//         std::visit([](const auto& value) {
//             if constexpr (std::is_same_v<std::decay_t<decltype(value)>, int>) {
//                 std::cout << "int: " << value << std::endl;
//             } else {
//                 std::cout << "string: " << value << std::endl;
//             }
//         }, item);
//     }

//     return 0;
// }

// for (size_t j = 0; j < update.length(); j++) {

//     if (update[j] == '=' && repeat_equal_sign == true) {
//         final_sql += "==";  
//     } 

//     else if(update[j] == '=' && repeat_equal_sign == false){
//         final_sql += update[j];
//         repeat_equal_sign = true;

//     }

//     else{
//         final_sql += update[j];  
//     }
// }

// cout << final_sql << endl;

// #include <iostream>
// #include <vector>
// #include <algorithm>

// int main() {
//     std::vector<std::string> a = {"1", "2", "'Cherry'"};

//     for (std::string &s : a) {
//         s.erase(remove(s.begin(), s.end(), '\''), s.end());  // 删除所有 '"'
//     }

//     // 输出结果
//     for (int i=0; i<a.size(); i++){
//         cout<< a[i]<< endl;
//     }

//     return 0;
// }

#include <iostream>
#include <vector>
#include <variant>
#include <string>

using namespace std;

using InnerVector = vector<variant<int, string>>;
using Table = vector<variant<string, InnerVector>>;

int main() {
    Table table = {
        "customer",
        InnerVector{"name", "id", "address"},
        InnerVector{"xinyi", 1, "kulai"},
        InnerVector{"tommy", 2, "kuala lumpur"}
    };

    int rowIndex = 2;  // 目标行索引
    int colIndex = 1;  // 目标列索引
    int int_val = 99;  // 新的整数值
    string update_att_value = "updated_name";  // 新的字符串值

    // 确保索引有效
    if (rowIndex < table.size() && holds_alternative<InnerVector>(table[rowIndex])) {
        InnerVector& row = get<InnerVector>(table[rowIndex]);  // 获取该行

        if (colIndex < row.size()) {
            if (auto* num = get_if<int>(&row[colIndex])) {  
                cout << "旧值：" << *num << endl;
                *num = int_val;  // ✅ 正确修改 int
                cout << "新值：" << *num << endl;
            } 
            else if (auto* str = get_if<string>(&row[colIndex])) {  
                cout << "旧值：" << *str << endl;
                *str = update_att_value;  // ✅ 正确修改 string
                cout << "新值：" << *str << endl;
            }
        } else {
            cout << "错误：列索引超出范围！" << endl;
        }
    } else {
        cout << "错误：行索引无效！" << endl;
    }

    return 0;
}

