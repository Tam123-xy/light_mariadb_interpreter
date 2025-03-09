#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <unordered_map>
using namespace std;
namespace fs = std::filesystem;

void print_table(const vector<variant<string, vector<variant<int, string>>>>& table)
{
    vector<string> lines;    // saves the table's lines
    for (int i = 1; i < table.size(); i++)
    {

        // Get the row as a vector of integers or strings
        const auto& row = get<vector<variant<int, string>>>(table[i]);
        string line;  // String to store the current row

        for (const auto& cell : row)
        {
            if (holds_alternative<string>(cell))
            { // if cell is a string, then get it as string
                cout << get<string>(cell);
                line += get<string>(cell);
            }
            else
            {
                cout << get<int>(cell);   // if cell is an integer, then get it as integer
                line += to_string(get<int>(cell));
            }

            if (&cell != &row.back())
            {   // compare the address of the cell with the address of the last cell in the row
                cout << ","; // Print separator if cell is not the last one
                line += ",";
            }
        }

        cout << endl;
        lines.push_back(line);

    }
}

int main() {
    vector<variant<string, vector<variant<int, string>>>> table;
    vector<variant<int,string>> daT_values;
    vector<std::string> inputfiles;
    string path = R"(C:\Users\User\Downloads\mariadb)";  // Change this to your folder path
    string line;
    vector<string> words;
    vector<string> word;
    vector<string> attribute_dataType;
    vector<string> attribute;
    vector<string> dataType;
    // vector<string> value;
    int j;
    bool datatype= false;
    bool insert = true;
    string tableName, file_outputName, type, insert_value,insert_table;
    string insert_into;
   
    // Detect file txt 
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mdb") {  
            inputfiles.push_back(entry.path().filename().string());
        }
    }
   
    // No file txt founded
    if (inputfiles.size() == 0){
        cout << "No file input";
    }

    else{

        // Loop each file
        for (size_t i = 0; i < inputfiles.size(); ++i) {
            ifstream dataIn(inputfiles[i]);

            // Check file is empty
            if (dataIn.peek() == ifstream::traits_type::eof()) {
                cout << inputfiles[i] << " is empty!" << endl;}

            else {

                // Loop each line to put into variable line
                while (std::getline(dataIn, line)){

                    // Loop each word to put into vector words
                    // words = split(line,' ');

                    stringstream ss(line);
                    string theline;
                    while (getline(ss, theline, ' ')) {
                        words.push_back(theline);}
                }

                //remove spaces form each element
                for (int i = 0; i < words.size(); i++) {
                    string results; 
                    for (char c : words[i]) {
                        if (c != ' ') {
                            results += c;
                        }
                    }
                    if (!results.empty()) { 
                        word.push_back(results);
                    }
                }
            
                // for (int i = 0; i < word.size(); i++) {
                //     cout << '"' << word[i] << '"' << endl;
                // }
                
                // Loop vector words
                for (i=0; i < word.size(); i++){

                    // Handle CREATE
                    if (word[i] == "CREATE"){

                        // Create file output
                        if (word[i+1].find(".txt;")!= string::npos ){
                            for (char c : word[i+1]) {
                                if (c != ';') { 
                                    file_outputName += c;}}
                            ofstream file(file_outputName);}
                           

                        // Obtain table name
                        else if (word[i+1].find("TABLE")!= string::npos){
                            for (char c : word[i+2]) {
                                if (c != '(') { 
                                    tableName += c;} //table name
                            }

                            table.push_back(tableName);

                            // cout <<" tableName " <<'"' << tableName<< '"';

                            // Put only atribute and data type into vector table
                            for (j = i+3; j < word.size(); j++){
                                if (word[j] == ");"){ break;};
                                attribute_dataType.push_back(word[j]);}

                            // Obtain attribute and data type
                            for (j = 0; j < attribute_dataType.size(); j++){
                                // cout <<'"'<< table[j]<<"'"<< endl;

                                if (datatype == false){
                                    attribute.push_back(attribute_dataType[j]);
                                    datatype = true;
                                }

                                else if (datatype == true){

                                if(attribute_dataType[j] == "TEXT," || attribute_dataType[j] == "TEXT"){ 
                                        type = "string";}
                                else if (attribute_dataType[j] == "INT," || attribute_dataType[j] == "INT"){
                                        type = "int";}

                                else {
                                    cout << "Unsupport data type of " << attribute_dataType[j];
                                    exit(0);

                                }

                                    dataType.push_back(type); 
                                    datatype = false;

                                }
                            }
                        }
                    }

                    // Handle INSERT INTO
                    else if (word[i] == "INSERT" && word[i+1]== "INTO"){
                        // cout <<"hi"<<endl;
                        j=0;

                        for (j=i+2; j<word.size(); j++){
                            // cout << word[j];
                            

                            if (insert == true){
                                insert_into+=word[j];

                                if (word[j].find(";") != string::npos) {
                                    insert = false;
                                }
                            }
                        }
                        insert = true;

                        // cout <<endl;

                        // cout << insert_into<<" insert_into"<<endl;
                        

                        
                        for (char c : insert_into) {
                            if (c != '(') { 
                                insert_table += c;} //table name

                            else{break;}
                        }

                        
                        // cout << insert_table<< " table name"<< endl;

                        if(insert_table == get<string>(table[0])){

                            insert_table.clear();

                            size_t start = insert_into.find("(") + 1;
                            size_t end = insert_into.find(")");
                            string insert_att = insert_into.substr(start, end - start);
                            insert_att = insert_att.substr(0, insert_att.size());

                            // cout<< values;

                            vector<string> insert_attr;  // Vector to store split values
                            stringstream ss(insert_att);
                            string token;

                            // Split string using ',' as the delimiter
                            while (getline(ss, token, ',')) {
                                insert_attr.push_back(token);
                            }

                            // for (size_t i = 0; i < insert_attt.size(); i++) {
                            //     cout << '"' << insert_attt[i] << '"' << endl;
                            // }

                            start = insert_into.find("VALUES(") + 7;
                            end = insert_into.find(");");
                            string values = insert_into.substr(start, end - start);
                            values = values.substr(0, values.size());

                            // cout<< values;

                            vector<string> value;  // Vector to store split values
                            stringstream sss(values);

                            // Split string using ',' as the delimiter
                            while (getline(sss, token, ',')) {
                                value.push_back(token);
                            }
                            
                            // Sort the value by following the oder of attribute.
                            unordered_map<string, string> value_map;
                            for (size_t j = 0; j < insert_attr.size(); j++) {
                                value_map[insert_attr[j]] = value[j];
                            }

                            std::vector<std::string> sorted_values;
                            for (const auto& key : attribute) {
                                sorted_values.push_back(value_map[key]);
                            }

                            // for (size_t i = 0; i < sorted_values.size(); i++) {
                            //     cout << '"' << sorted_values[i] << '"' << endl;
                            // }

                            for(size_t j =0; j<dataType.size(); j++){
                                if(dataType[j] == "int"){
                                    daT_values.push_back(stoi(sorted_values[j]));
                                }
                                else{daT_values.push_back(sorted_values[j]);}
                            }

                            // for(j=0;j<daT_values.size();j++){
                            //     table.push_back(std::vector<std::variant<int, std::string>>{daT_values[j]});
                            // }
                            table.push_back(daT_values);

                            daT_values.clear();
                            insert_into.clear();
                            
                            // for (const auto& item : table) {
                            //     if (std::holds_alternative<std::string>(item)) {
                            //         std::cout << "String: " << std::get<std::string>(item) << std::endl;
                            //     } else if (std::holds_alternative<std::vector<std::variant<int, std::string>>>(item)) {
                            //         std::cout << "Table Data: ";
                            //         for (const auto& cell : std::get<std::vector<std::variant<int, std::string>>>(item)) {
                            //             if (std::holds_alternative<int>(cell)) {
                            //                 std::cout << std::get<int>(cell) << " int ";
                            //             } else {
                            //                 std::cout << std::get<std::string>(cell) << " string ";
                            //             }
                            //         }
                            //         std::cout << std::endl;
                            //     }
                            // }

                            
                            
                        }

                        else{
                            cout<<"Error, "<< insert_table << " table dosen't exit."<< endl;
                            
                        }

                        // print_table(table);

                   

                    
                    }

                    

                }

                
            }

            for (const auto& row : table) {
                if (holds_alternative<string>(row)) {
                    // 如果当前行是字符串（标题）
                    cout << "Title: " << get<string>(row) << endl;
                } else if (holds_alternative<vector<variant<int, string>>>(row)) {
                    // 如果当前行是数据行
                    cout << "Data: ";
                    for (const auto& item : get<vector<variant<int, string>>>(row)) {
                        if (holds_alternative<int>(item)) {
                            cout << get<int>(item) << " ";
                        } else if (holds_alternative<string>(item)) {
                            cout << get<string>(item) << " ";
                        }
                    }
                    cout << endl;
                }
            }
        }
    }


    return 0;
}

