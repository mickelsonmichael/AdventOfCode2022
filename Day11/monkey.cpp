#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <regex>
#include <utility>

#define COMMON_MULTIPLE 9699690

long long reduce(const long long &n)
{
    if (n <= COMMON_MULTIPLE)
    {
        return n;
    }

    long long result = n;
    while (result > COMMON_MULTIPLE)
    {
        result -= COMMON_MULTIPLE;
    }
    
    return result;
}

class Monkey
{
private:
    const int _id;
    std::vector<long long> _items;
    std::function<long long(long long)> _operation;
    int _test;
    int _on_pass;
    int _on_fail;
    size_t _inspections = 0;

public:
    Monkey(
        const int id,
        const std::vector<long long> items,
        const std::function<long long(long long)> operation,
        const int test,
        const int test_true,
        const int test_false) : _id(id), _items(items), _operation(operation),
                                                _test(test), _on_pass(test_true), _on_fail(test_false){};

    std::vector<std::pair<long long, int>> throw_items(const std::function<long long(long long)> &relief_func)
    {
        std::vector<std::pair<long long, int>> result;

        for (long long worry_level : _items)
        {
            _inspections += 1;

            long long new_worry = relief_func(_operation(worry_level));

            int throw_to = new_worry % _test == 0 ? _on_pass : _on_fail;

            std::pair<long long, int> action(new_worry, throw_to);

            result.push_back(action);
        }

        _items.clear();

        return result;
    }

    void catch_item(std::pair<long long, int> item)
    {
        if (item.second != _id)
        {
            std::cout << "Monkey " << _id << " caught an item meant for " << item.second << '\n';
            exit(1);
        }

        _items.push_back(item.first);
    }

    int id() const
    {
        return _id;
    }

    size_t num_inspections() const
    {
        return _inspections;
    }

    int get_test() const
    {
        return _test;
    }
};

int parse_id(const std::string &line)
{
    const std::regex pattern("Monkey ([0-9]+):");
    std::smatch match;

    if (!std::regex_search(line, match, pattern))
    {
        std::cout << "Invalid monkey ID: " << line << '\n';

        exit(1);
    }

    return stoi(match[1]);
}

std::vector<long long> parse_items(std::string line)
{
    std::vector<long long> items;

    const std::regex pattern("(-?[0-9]+)+");
    std::regex_iterator<std::string::iterator> from(line.begin(), line.end(), pattern);
    std::regex_iterator<std::string::iterator> to;

    for (; from != to; ++from)
    {
        items.push_back(std::stoll(from->str()));
    }

    return items;
}

std::function<long long(long long)> parse_operation(const std::string &line)
{
    const std::regex pattern("Operation: new = old ([+\\-*/]) (old|\\-?[0-9]+)");
    std::smatch match;

    if (!std::regex_search(line, match, pattern) || match.size() != 3)
    {
        std::cout << "Invalid operation: " << line << '\n';

        exit(1);
    }

    const std::string op = match[1];

    if (match[2] == "old")
    {
        if (op == "+")
            return [](long long old)
            { return old + old; };
        if (op == "-")
            return [](long long old)
            { return old - old; };
        if (op == "*")
            return [](long long old)
            { return old * old; };
        if (op == "/")
            return [](long long old)
            { return old / old; };
    }

    const long long n = std::stoll(match[2]);

    if (op == "+")
        return [n](long long old)
        { return old + n; };
    if (op == "-")
        return [n](long long old)
        { return old - n; };
    if (op == "*")
        return [n](long long old)
        { return old * n; };
    if (op == "/")
        return [n](long long old)
        { return old / n; };

    std::cout << "Invalid operation type: " << op << '\n';
    exit(1);
}

int parse_test(const std::string &line)
{
    const std::regex pattern("Test: divisible by ([0-9]+)");
    std::smatch match;

    if (!std::regex_search(line, match, pattern) || match.size() != 2)
    {
        std::cout << "Invalid test: " << line << '\n';
        exit(1);
    }

    return std::stoi(match[1]);
}

int parse_to(const std::string &line)
{
    const std::regex pattern("If (?:true|false): throw to monkey ([0-9]+)");
    std::smatch match;

    if (!std::regex_search(line, match, pattern) || match.size() != 2)
    {
        std::cout << "Invalid monkey: " << line << '\n';
        exit(1);
    }

    return std::stoi(match[1]);
}

Monkey parse_monkey(const std::vector<std::string> &lines)
{
    if (lines.size() != 6)
    {
        std::cout << "Monkey input must be six lines\n";

        exit(1);
    }

    const int id = parse_id(lines[0]);
    const std::vector<long long> starting_items = parse_items(lines[1]);
    const std::function<long long(long long)> operation = parse_operation(lines[2]);
    const int test = parse_test(lines[3]);
    const int on_true = parse_to(lines[4]);
    const int on_false = parse_to(lines[5]);

    Monkey m(id, starting_items, operation, test, on_true, on_false);

    return m;
}
