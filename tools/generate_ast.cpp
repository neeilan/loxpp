#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::vector;
using std::string;

void define_ast(const string output_dir, const string base_name, const vector<string> types);
void define_type(std::ofstream &file, const string &base_name, const string &class_name, const string &field_names);

inline void writeln(std::ofstream &file, const string line) { file << line << std::endl; }
inline vector<string> split(const string s, const char delim) {
    vector<string> result; string curr; std::stringstream ss(s);
    while(std::getline(ss, curr, delim)) result.push_back(curr);
    return result;
}

vector<string> types = {
        "Binary:Expr left,Token op,Expr right",
        "Grouping:Expr expression",
        "Literal:LiteralValue value",
        "Unary:Token op,Expr right"
};

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: generate_ast <output directory>" << std::endl;
        exit(0);
    }

    string output_dir(argv[1]);
    define_ast(output_dir, "Test", types);

    return 0;
}

void define_ast(const string output_dir, const string base_name, const vector<string> types) {
    string path = output_dir + "/" + base_name + ".cpp";

    std::ofstream file;
    file.open (path);

    writeln(file, "#include <vector>");
    writeln(file, "");
    writeln(file, "#include \"expr.hpp\"");
    writeln(file, "#include \"token.hpp\"");
    writeln(file, "#include \"literal_value.hpp\"");

    writeln(file, "");
    writeln(file, "namespace AST {");
    writeln(file, "");

    writeln(file, "  class " + base_name + " {");
//    writeln(file, "  public:");
    writeln(file, "  };");



    // The AST classes
    for (const string &type : types) {
        string class_name = split(type, ':')[0];
        string fields = split(type, ':')[1];
        define_type(file, base_name, class_name, fields);
    }

    writeln(file, "};");

    file.close();
}


void define_type(std::ofstream &file, const string &base_name, const string &class_name, const string &field_names) {

    writeln(file, "  class " + class_name + " : public " + base_name + " {");
    writeln(file, "  public:");

    const vector<string> fields = split(field_names, ',');

    // Fields
    for (string field : fields) {
        writeln(file, "    "  + field + ";");
    }

    writeln(file, "");

    // Constructor
    writeln(file, "    " + class_name + "(" + field_names + ") { ");


    for (string field : fields) {
        string name = split(string(field), ' ')[1];
        writeln(file, "      this->" + name + " = " + name + ";");
    }

    writeln(file, "    }");
    writeln(file, "  };");
    writeln(file, "");
}