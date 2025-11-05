template<typename T>
struct Command {
    std::string name;
    int numArgs;
    T hook;
};