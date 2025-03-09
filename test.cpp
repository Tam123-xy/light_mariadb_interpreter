#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
using namespace std;

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


int main() {
    std::vector<std::string> a = {"abc", "123", "1"};
    std::vector<std::variant<int, std::string>> result;

    for (int i = 0; i < a.size(); i++) {
        if (i % 2 == 0) {
            result.push_back(a[i]);  // 直接存 string
        } else {
            try {
                result.push_back(std::stoi(a[i]));  // 转换 string -> int
            } catch (const std::exception& e) {
                std::cerr << "Error converting '" << a[i] << "' to int: " << e.what() << std::endl;
            }
        }
    }

    // 输出结果
    for (const auto& item : result) {
        std::visit([](const auto& value) { std::cout << value << " "; }, item);
    }

    return 0;
}


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
