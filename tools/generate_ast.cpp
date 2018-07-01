#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using std::string;

void define_ast(const string output_dir, const string base_name, const vector<string> types);
inline void writeln(std::ofstream &file, const string line) { file << line << std::endl; }

vector<string> types = {
        "Binary   : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token operator, Expr right"
};

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: generate_ast <output directory>" << std::endl;
        exit(1);
    }

    string output_dir(argv[1]);
    define_ast(output_dir, "Test", types);
}

void define_ast(const string output_dir, const string base_name, const vector<string> types) {
    string path = output_dir + "/" + base_name + ".cpp";

    std::ofstream file;
    file.open (path);

    writeln(file, "#include <vector>");
    writeln(file, "");
    writeln(file, "class " + base_name + " {");
    writeln(file, "}");

    file.close();
}