template<typename T>
struct Command {
    std::string name;
    int requiredArgs;
    T hook;
};